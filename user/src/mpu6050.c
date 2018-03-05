#include "mpu6050.h"
#include "i2c.h"

void MPU_Init()
{
    /* 引脚配置
    SCL -> PTA3
    SDA -> PTA2
     */
    I2C_ConfigType  I2C_Config = {{0}};
	I2C_Config.u16Slt = 0;
  	I2C_Config.u16F = 0x10; /* Baud rate at 400 kbit/sec, MULT = 0 , ICR=10*/
    I2C_Config.sSetting.bIntEn = 0;
    I2C_Config.sSetting.bI2CEn = 1;
    I2C_Config.sSetting.bMSTEn = 1;

    I2C_Init(I2C0,&I2C_Config );
		
}

//stop变量无用
void I2C_Transmit(I2C_MemMapPtr I2Cx,uint8_t addr,uint8_t *buff,uint8_t size,uint8_t stop)
{
	I2C_MasterSendWait(I2Cx,addr,buff,size);
}


void I2C_Receive(I2C_MemMapPtr I2Cx,uint8_t addr,uint8_t *buff,uint8_t size,uint8_t stop)
{
   I2C_MasterReadWait(I2Cx,addr,buff,size);
}

void MPU_WriteReg(uint8_t regAddr,uint8_t data)
{
    uint8_t buffer[2]={regAddr,data};
    I2C_Transmit(I2C0,MPU_ADDR,buffer,2,1);
}

void MPU_ReadReg(uint8_t regAddr,uint8_t *data)
{
    I2C_Transmit(I2C0,MPU_ADDR,&regAddr,1,0);
    I2C_Receive(I2C0,MPU_ADDR,data,1,1);
}

void MPU_ReadBytes(uint8_t regAddr,uint8_t *buff,uint16_t size)
{
    I2C_Transmit(I2C0,MPU_ADDR,&regAddr,1,0);
    I2C_Receive(I2C0,MPU_ADDR,buff,size,1);
}

void MPU_ReadReg16(uint8_t regAddr,int16_t *data)
{
    uint8_t *p=(uint8_t *)data;
    MPU_ReadBytes(regAddr,(uint8_t *)data,2);
    uint8_t temp;
    temp=p[0];
    p[0]=p[1];
    p[1]=temp;
}
void MPU_WakeUp()
{
    MPU_WriteReg(MPU_PWR_MGMT1_ADDR,MPU_PWR_MGMT1_WAKEUP);
}

int MPU_isReady()
{
    uint8_t data;
    MPU_ReadReg(MPU_WHO_AM_I,&data);
    return data==MPU_ADDR>>1;
}

void MPU_SetScale(enum GYRO_SCALE gyroscale, enum ACC_SCALE accscale)
{
    MPU_WriteReg(GYRO_SCALE_ADDR,gyroscale);
    MPU_WriteReg(ACC_SCALE_ADDR,accscale);
}
void MPU_ReadAx(int16_t * pax)
{
    MPU_ReadReg16(ACC_X_ADDR,pax);
}
void MPU_ReadAy(int16_t * pay)
{
    MPU_ReadReg16(ACC_Y_ADDR,pay);
}
void MPU_ReadAz(int16_t * paz)
{
    MPU_ReadReg16(ACC_Z_ADDR,paz);
}
void MPU_ReadGx(int16_t * pgx)
{
    MPU_ReadReg16(GYRO_X_ADDR,pgx);
}
void MPU_ReadGy(int16_t * pgy)
{
    MPU_ReadReg16(GYRO_Y_ADDR,pgy);
}
void MPU_ReadGz(int16_t * pgz)
{
    MPU_ReadReg16(GYRO_Z_ADDR,pgz);
}
