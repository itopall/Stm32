/*
 * nokia5110.h
 *
 *  Created on: Feb 2, 2022
 *      Author: İlker TOPAL
 */

#ifndef INC_NOKIA5110_H_
#define INC_NOKIA5110_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

uint8_t frameBuffer[504];

bool nokia5110_Init(void);
void nokia5110_Reset(void);
bool nokia5110_Update(void);
void nokia5110_Clear(void);
bool nokia5110_Write(uint8_t data, uint8_t mode);
void nokia5110_SetPixel(uint8_t x, uint8_t y, bool set);
void nokia5110_BufferWrite(uint8_t* data, uint16_t length);


#endif /* INC_NOKIA5110_H_ */
