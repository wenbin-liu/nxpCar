#include "uart.h"
#include "ics.h"
#include "i2c.h"
#include <stdio.h>
#include "mpu6050.h"

#define PRINTF_UART UART2

int fputc(int c,FILE *fp)
{
	UART_PutChar(PRINTF_UART,c);
	return c;
}

int main(void)
{
	
    /* Perform processor initialization */
    	ICS_ConfigType ICS_set={0};		/* Declaration of ICS_setup structure */
    	ICS_set.u8ClkMode=ICS_CLK_MODE_FEE; /* ICS in FLL engaged internal mode*/
    	ICS_set.bdiv=0;					/* bdiv bit equals 0, prescaler=1*/
    	ICS_set.oscConfig.bEnable=1;	/* Osc enabled*/
    	ICS_set.oscConfig.bRange=1;		/* High frequency range 4-24 MHz*/
    	ICS_set.oscConfig.bIsCryst=1;	/* Oscillator clock source is selected*/
    	ICS_set.oscConfig.u32OscFreq=16000 ; /* 16 MHz crystal, crytal is in KHz*/

    	ICS_Init(&ICS_set);            		/*Initialization of core clock at 40MHz, bus clock 20 MHz*/



		UART_ConfigType UART_Config={{0}};

		UART_Config.sctrl1settings.bits.bM=0;  	/* 8 bit mode*/
		UART_Config.sctrl1settings.bits.bPe=0;	/* No hardware parity generation or checking*/
		UART_Config.bSbns=0;					/* One stop bit*/
		UART_Config.sctrl2settings.bits.bRe=1;	/* Enable Receiver*/
		UART_Config.sctrl2settings.bits.bTe=1;	/* Enable Transmitter*/
		UART_Config.u32SysClkHz = 20000000;   	/* Bus clock in Hz*/
		UART_Config.u32Baudrate = 115200;     	/* UART baud rate */

		UART_Init(UART2,&UART_Config);			/*Initialization of UART utilities*/
	
		
		MPU_Init();
		
		printf("MPU6050 is waking\r\n");
		MPU_WakeUp();
		printf("MPU6050 is working\r\n");
		MPU_SetScale(GYRO_SCALE_500,ACC_SCALE_2G);
		int16_t ax;
		
		
		
	while(1)
	{
		MPU_ReadAx(&ax);
		printf("%d\r\n",ax);
	}
}