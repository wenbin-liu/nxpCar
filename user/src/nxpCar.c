#include "uart.h"
#include "ics.h"
#include "i2c.h"
#include <stdio.h>
#include "mpu6050.h"
#include "ftm.h"
#include "adc.h"

#define PRINTF_UART UART2

uint32_t count=0;
int fputc(int c,FILE *fp)
{
	UART_PutChar(PRINTF_UART,c);
	return c;
}


void systickInit(void)
{
	/* SysTick配置
	40Mhz时钟源
	5ms中断中期
	 */
	SysTick->LOAD=200000;
	SysTick->CTRL=SysTick_CTRL_CLKSOURCE_Msk|SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk;
	Enable_Interrupt(SysTick_IRQn);
}

void SysTick_Handler(void)
{
//	int16_t ax;
//	MPU_ReadAx(&ax);
//	printf("%d %d\r\n",ax,count);
//	
	if(ADC_IsFIFOFullFlag(ADC)!=0)
		printf("%d %d %d\r\n",ADC_ReadResultReg(ADC),ADC_ReadResultReg(ADC),ADC_ReadResultReg(ADC));

	
	if(count%100==0)
			GPIOA->PTOR=1<<10;
	count++;
}

void icsInit(void)
{
	/*
	时钟配置
	16Mhz晶振
	40Mhz内核始终
	20Mhz总线时钟
	*/
	    /* Perform processor initialization */
    	ICS_ConfigType ICS_set={0};		/* Declaration of ICS_setup structure */
    	ICS_set.u8ClkMode=ICS_CLK_MODE_FEE; /* ICS in FLL engaged internal mode*/
    	ICS_set.bdiv=0;					/* bdiv bit equals 0, prescaler=1*/
    	ICS_set.oscConfig.bEnable=1;	/* Osc enabled*/
    	ICS_set.oscConfig.bRange=1;		/* High frequency range 4-24 MHz*/
    	ICS_set.oscConfig.bIsCryst=1;	/* Oscillator clock source is selected*/
    	ICS_set.oscConfig.u32OscFreq=16000 ; /* 16 MHz crystal, crytal is in KHz*/

    	ICS_Init(&ICS_set);            		/*Initialization of core clock at 40MHz, bus clock 20 MHz*/

}

void uartInit(void)
{
	/* UART2 引脚
	Tx -> PTD7
	Rx -> PTD6
	 */
		UART_ConfigType UART_Config={{0}};

		UART_Config.sctrl1settings.bits.bM=0;  	/* 8 bit mode*/
		UART_Config.sctrl1settings.bits.bPe=0;	/* No hardware parity generation or checking*/
		UART_Config.bSbns=0;					/* One stop bit*/
		UART_Config.sctrl2settings.bits.bRe=1;	/* Enable Receiver*/
		UART_Config.sctrl2settings.bits.bTe=1;	/* Enable Transmitter*/
		UART_Config.u32SysClkHz = 20000000;   	/* Bus clock in Hz*/
		UART_Config.u32Baudrate = 115200;     	/* UART baud rate */

		UART_Init(PRINTF_UART,&UART_Config);			/*Initialization of UART utilities*/
}

void pwmFtmInit(void)
{
	/*
	四个通道引脚配置如下
	 PS0 -> PTH0
	 PS1 -> PTH1
	 PS2 -> PTD0
	 PS3 -> PTD1
	 */
	SIM->PINSEL1|=SIM_PINSEL1_FTM2PS0(1)|SIM_PINSEL1_FTM2PS1(1)|SIM_PINSEL1_FTM2PS2(1)|SIM_PINSEL1_FTM2PS3(1);

	
	
	FTM_ConfigType FTM2_Config={0};
	FTM_ChParamsType FTM2CH_Config={0};

	FTM2_Config.modulo=999;
	FTM2_Config.clk_source=FTM_CLOCK_SYSTEMCLOCK;
	FTM2_Config.prescaler=FTM_CLOCK_PS_DIV1;
	FTM2_Config.mode=1;
	FTM2_Config.toie=0;


	FTM2CH_Config.ctrl.bits.bMode=FTM_PWMMODE_EDGEALLIGNED;
	FTM2CH_Config.ctrl.bits.bPWMPol=FTM_PWM_HIGHTRUEPULSE;
	FTM2CH_Config.u16CnV=0;


	FTM_ChannelInit(FTM2,0,FTM2CH_Config);
	FTM_ChannelInit(FTM2,1,FTM2CH_Config);
	FTM_ChannelInit(FTM2,2,FTM2CH_Config);
	FTM_ChannelInit(FTM2,3,FTM2CH_Config);
	
	FTM_Init(FTM2,&FTM2_Config);
}

void adcInit(void)
{
	/* ADC 引脚分配
	AD2(原理图上的AD11) -> PTA6
	AD12 -> PTF4
	AD13 -> PTF5
	AD14 -> PTF6
	AD15 -> PTF7
	
	*/
	  ADC_ConfigType  ADC_Config={{0}};

    /* Initialization of ADC module */
    ADC_Config.u8ClockDiv = ADC_ADIV_DIVIDE_1;
    ADC_Config.u8ClockSource = CLOCK_SOURCE_BUS_CLOCK;
    ADC_Config.u8Mode = ADC_MODE_12BIT;
    ADC_Config.sSetting.bIntEn = 0;
		ADC_Config.sSetting.bContinuousEn=1;
    ADC_Config.u8FiFoLevel = ADC_FIFO_LEVEL3;
    ADC_Config.u16PinControl= 0xF<<12; /* Disable I/O control on ADC channel 10*/

    ADC_Init(ADC, &ADC_Config);
}

int main(void)
{
	


		icsInit();
	
		uartInit();
		
//		MPU_Init();
//		
//		printf("MPU6050 is waking\r\n");
//		MPU_WakeUp();
//		printf("MPU6050 is working\r\n");
//		MPU_SetScale(GYRO_SCALE_500,ACC_SCALE_2G);

		pwmFtmInit();
	
		FTM_SetChannelValue(FTM2,3,333);
		adcInit();
		systickInit();
		
		GPIOA->PDDR=1<<10;
		ADC_SetChannel(ADC,ADC_CHANNEL_AD12);
		ADC_SetChannel(ADC,ADC_CHANNEL_AD13);
		ADC_SetChannel(ADC,ADC_CHANNEL_AD14);
	while(1)
	{


	}
}