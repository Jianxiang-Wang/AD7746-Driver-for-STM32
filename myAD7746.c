#include "delay.h"
#include "myAD7746.h"
#include "myiic.h"

// Initialize the AD7746，初始化AD7746IIC接口
void AD7746_Init(u8 capsetup, u8 vtsetup, u8 excsetup, u8 conf, u8 capdaca, u8 capdacb)
{
	IIC_Init();
	AD7746_Reset();
	delay_us(200);
	AD7746_WriteCapSetupRegister(capsetup);
  AD7746_WriteVTSetupRegister(vtsetup);
	AD7746_WriteExcSetupRegister(excsetup);
	AD7746_WriteConfigurationRegister(conf);
	AD7746_WriteCapDacARegister(capdaca);		
  AD7746_WriteCapDacBRegister(capdacb);
}


void AD7746_Reset()
{
	IIC_Start();  
	IIC_Send_Byte(AD7746_ADDR);
	IIC_Wait_Ack();
	IIC_Send_Byte(AD7746_RESET);
	IIC_Stop();
}


u8 AD7746_Read_Byte(u8 reg)
{
	u8 res;
	IIC_Start();
	IIC_Send_Byte(AD7746_ADDR_WRITE);
  IIC_Wait_Ack();
	IIC_Send_Byte(reg); 
	IIC_Wait_Ack();
	IIC_Start(); 
	IIC_Send_Byte(AD7746_ADDR_READ);
	IIC_Wait_Ack();
  res=IIC_Read_Byte(0);	
	IIC_Stop();
	return res;
}


u8 AD7746_Write_Byte(u8 reg,u8 data)
{
	IIC_Start();  
	IIC_Send_Byte(AD7746_ADDR_WRITE);
	IIC_Wait_Ack();
	IIC_Send_Byte(reg); 
	IIC_Wait_Ack();
	IIC_Send_Byte(data); 
	IIC_Wait_Ack();  		    	   
  IIC_Stop(); 
	return 0;
}

u32 AD7746_getCapacitance()
{
	u32 capacitance = 0;
	u8	buffer[3];
	buffer[0] = AD7746_Read_Byte(AD7746_ADDR_CAP_DATA_H);
	buffer[1] = AD7746_Read_Byte(AD7746_ADDR_CAP_DATA_M);
	buffer[2] = AD7746_Read_Byte(AD7746_ADDR_CAP_DATA_L);
	capacitance = ((u32)buffer[0] << 16) | ((u32)buffer[1] << 8) | ((u32)buffer[2]);
	return capacitance;
}

float AD7746_CapConvert(u8 capdac)
{
	u32 data;
	float capconvert = 0;
	data = AD7746_getCapacitance();
	capconvert = ((float)data/16777216)*8 + (capdac - 4);
	return capconvert;	
}


u32 AD7746_getTemperature()
{
	u32 temperature = 0;
	u8	 buffer[3];
	buffer[0] = AD7746_Read_Byte(AD7746_ADDR_VT_DATA_H);
	buffer[1] = AD7746_Read_Byte(AD7746_ADDR_VT_DATA_M);
	buffer[2] = AD7746_Read_Byte(AD7746_ADDR_VT_DATA_L);
	temperature = ((u32)buffer[0] << 16) | ((u32)buffer[1] << 8) | ((u32)buffer[2]);
	return temperature;
}

void AD7746_WriteCapSetupRegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_CAP_SETUP, &data,2);
}

void AD7746_WriteVTSetupRegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_VT_SETUP, &data,2);
}

void AD7746_WriteExcSetupRegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_EXC_SETUP, &data,2);
}

void AD7746_WriteConfigurationRegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_CONFIGURATION, &data,2);
}

void AD7746_WriteCapDacARegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_CAP_DAC_A, &data,2);
}

void AD7746_WriteCapDacBRegister(u8 data)
{
	IIC_Write_Len(AD7746_ADDR,AD7746_ADDR_CAP_DAC_B, &data,2);
}

void AD7746_SetCapOffset(u16 offset)
{
	AD7746_Write_Byte(AD7746_ADDR_CAP_OFFSET_H, offset);
}

void AD7746_SetCapGain(u16 gain)
{
	AD7746_Write_Byte(AD7746_ADDR_CAP_GAIN_H, gain);
}

void AD7746_SetVoltGain(u16 gain)
{
	AD7746_Write_Byte(AD7746_ADDR_VOLTAGE_GAIN_H, gain);
}

