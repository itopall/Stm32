/*
 * BMP180.c
 *
 *  Created on: Jan 24, 2022
 *      Author: ilker TOPAL
 */

#include "BMP180.h"



void BMP180_Init()
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_DEVICE_ADDRESS_WRITE, 1, 100000) != HAL_OK)
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

	BMP180_Get_Calib_Value();
}


void BMP180_Get_Calib_Value()
{
	uint8_t caliBuff[BMP180_CALIBRATION_VALUE_LENGTH] = {0};
	int i = 0;

	//burada device'ın hafızasından okuma yapıyoruz.
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_ADDRESS_READ, BMP180_DEVICE_START_ADDRESS, 1, caliBuff, BMP180_CALIBRATION_VALUE_LENGTH, 100000);

	//caliBuff[i] << 8 => MSB bitini oluşturuyor. caliBuff[i + 1] LSB bitlerini oluşturuyor.
	AC1 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2; //16 bitlik değere datasheet'de yazdığı için dedik
	AC2 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	AC3 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	AC4 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	AC5 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	AC6 = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	B1 	= (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	B2  = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	MB  = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	MC  = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;
	MD  = (int16_t)((caliBuff[i] << 8) | caliBuff[i + 1]); i += 2;

	if (AC1 == 0x0000 || AC1 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (AC2 == 0x0000 || AC2 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (AC3 == 0x0000 || AC3 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (AC4 == 0x0000 || AC4 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (AC5 == 0x0000 || AC5 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (AC6 == 0x0000 || AC6 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (B1 == 0x0000 || B1 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (B2 == 0x0000 || B2 == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (MB == 0x0000 || MB == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (MC == 0x0000 || MC == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	if (MD == 0x0000 || MD == 0xFFFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
}

void BMP180_Get_Temperature()
{
	BMP180_Get_Uncompensated_Temperature();
	tX1 = (int32_t)((unCompTemperature - AC6) * AC5 / pow(2.,15.));
	tX2 = (int32_t)(MC * pow(2., 11.) /(tX1 + MD));
	if (!tX1 && !MD)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		while(1);
	}
	tB5 = tX1 + tX2;
	temperature = ((tB5 + 8) / pow(2., 4.) * .1);
}

void BMP180_Get_Pressure()
{
	BMP180_Get_Uncompensated_Pressure();
	pB6 = tB5 - 4000;
	pX1 = (pB2*(pB6 * pB6 / pow(2., 12.))) / pow(2., 11);
	pX2 = AC2 * pB6 / pow(2., 11.);
	pX3 = pX1 + pX2;
	pB3 = (((AC1 * 4 + pX3) << (uint8_t)BMP180_OSS_Value) + 2) / 4;
	pX1 = AC3 * pB6 / pow(2., 13.);
	pX2 = (pB1 * (pB6 * pB6 / pow(2., 12.))) / pow(2.,12.);
	pX3 = ((pX1 + pX2) + 2) / 4;
	pB4 = AC4 * (unsigned long)(pX3 + 32768) / pow(2.,15.);
	pB7 = ((unsigned long)unCompPressure - pB3) * (50000 >> (uint8_t)BMP180_OSS_Value);

	if (pB7 < 0x80000000)
		p = (pB7 * 2) / pB4;
	else
		p = (pB7 / pB4) * 2;
	pX1 = (p / pow(2., 8.)) * (p / pow(2., 8.));
	pX1 = (pX1 * 3038) / pow(2.,16.);
	pX2 = (-7357 * p) / pow(2., 16.);
	p = p + (pX1 + pX2 + 3791) / pow(2.,4.);
}

void BMP180_Get_Uncompensated_Temperature()
{
	uint8_t rData[2] = {0};
	uint8_t wData[1];
	wData[0] = 0x2E; // bu değeri datasheet'ten aldık
	//0xF4 register'ına 0x2E değerini girdik
	HAL_I2C_Mem_Write(&hi2c1,BMP180_DEVICE_ADDRESS_WRITE , BMP180_Pres_Temp_Write_Register, 1, wData, 1, 100000); //0xF4 değerinide datasheetten aldık
	HAL_Delay(5);
	//0xF6 register'ından 0xF7 register'ına kadar okuma yaptık
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_ADDRESS_READ, BMP180_unComp_PresTemp_Start, 1, rData, 2, 100000);

	unCompTemperature = (int16_t)((rData[0] << 8) | rData[1]);
}

void BMP180_Get_Uncompensated_Pressure()
{
	uint8_t wData[1] = {0};
	uint8_t rData[3] = {0};
	wData[0] = 0x34 | (BMP180_OSS_Value << 6);
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_ADDRESS_WRITE, BMP180_Pres_Temp_Write_Register, 1, wData, 1, 100000);
	HAL_Delay(26);
	HAL_I2C_Mem_Read(&hi2c1, BMP180_DEVICE_ADDRESS_READ, BMP180_unComp_PresTemp_Start, 1, rData, 3, 100000);
	unCompTemperature = ((rData[0] << 16) | (rData[1] << 8) | (rData[2])) >> (8 - (uint8_t)BMP180_OSS_Value);
}

