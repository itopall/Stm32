/*
 * BMP180.h
 *
 *  Created on: Jan 24, 2022
 *      Author: ilker
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "stm32f4xx_hal.h"
#include <math.h>

extern I2C_HandleTypeDef hi2c1;

//bmp180 device addreses
#define BMP180_DEVICE_ADDRESS_READ			0xEF
#define BMP180_DEVICE_ADDRESS_WRITE			0xEE
#define BMP180_OSS_Value					0x03
#define BMP180_Pres_Temp_Write_Register		0xF4


//bmp180 device start calibration address
#define BMP180_DEVICE_START_ADDRESS		0xAA
#define BMP180_unComp_PresTemp_Start	0xF6

//bmp180 calibration value length
#define BMP180_CALIBRATION_VALUE_LENGTH		22

//Temperature-Pressure values
int16_t unCompTemperature;
int32_t unCompPressure;
float temperature;
float pressure;

//True Temperature values
int32_t tX1;
int32_t tX2;
int32_t tB5;

//True Pressure values
uint32_t pB6,pB1, pB2,pB3,pB4,pB7,p;
int32_t pX1;
int32_t pX2;
int32_t pX3;

//bmp180 calibration values
int16_t AC1;
int16_t AC2;
int16_t AC3;
int16_t AC4;
int16_t AC5;
int16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;

void BMP180_Init(void);
void BMP180_Get_Calib_Value(void);
void BMP180_Get_Uncompensated_Temperature(void);
void BMP180_Get_Temperature(void);
void BMP180_Get_Uncompensated_Pressure(void);
void BMP180_Get_Pressure(void);



#endif /* INC_BMP180_H_ */
