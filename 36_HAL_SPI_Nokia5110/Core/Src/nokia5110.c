/*
 * nokia5110.c
 *
 *  Created on: Feb 2, 2022
 *      Author: ilker TOPAL
 */


#include "nokia5110.h"

bool nokia5110_Init(void)
{
	nokia5110_Reset();


	/*
	 * 	Function set
	 *  0x21 yazarak Additional commads kullanıldı
	 *
	 *  Vop değeri
	 *  0xC0 yazarak 5 volta ayarlamış olduk
	 *
	 *	Temperature control
	 *	0x07 yazarak Vlcd = 3
	 *
	 *	BIAS voltage control
	 *	0x13 yazarak n = 4, 1:48
	 *
	 *	Function set
	 *	0x20 basic mode'a aldık
	 *
	 *	Display Control
	 *	0x0C yazarak display mode normal olarak aktif edildi
	 *
	 */
	if (!nokia5110_Write(0x21, 0)) //ekleme modunda Command Set'i seçmek için 21H komutu göndermek
		return false;
	if (!nokia5110_Write(0xC0, 0))
		return false;
	if (!nokia5110_Write(0x07, 0))
		return false;
	if (!nokia5110_Write(0x13, 0))
		return false;
	if (!nokia5110_Write(0x20, 0))
		return false;
	if (!nokia5110_Write(0x0C, 0))
		return false;
	return true;

}

bool nokia5110_Update()
{
	//move to x = 0
	if (!nokia5110_Write(0x80, 1)) // 1 =  data modu
		return false;
	//move to y = 0
	if (!nokia5110_Write(0x40, 1))
		return false;

	nokia5110_BufferWrite(frameBuffer, 504);

	return true;
}
void nokia5110_SetPixel(uint8_t x, uint8_t y, bool set)
{
	uint8_t Bi; //bit index
	uint8_t By; //bit y

	if (x < 0 || x >= 84 || y < 0 || y >= 84)
		return;

	By = (y / 8) * 84 + x; // yataydaki konum
	Bi = y % 8; // dikeydeki konum


	if(set)
		frameBuffer[By] |= (1 << Bi);
	else
		frameBuffer[By] &= ~(1 << Bi);
}
void nokia5110_BufferWrite(uint8_t* data, uint16_t length)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET); 		//CE pin is low
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  		//DC pin is High

	HAL_SPI_Transmit_DMA(&hspi2, data, length);

}


void nokia5110_Reset(void)
{
	/*
	 * Eğer Reset sinyali 0 olursa (RES = 0)
	 * gönderilen 8 bit (1 byte) iptal edilir
	 * Reset sinyali 1 olursa (RES = 1)
	 * Gönderme işlemi 7. bitten başlayarak gönderilir
	 */

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); //res = low
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); //res = High
}


bool nokia5110_Write(uint8_t data, uint8_t mode)
{

	/*
	 *		CE pini 0 olduğu sürece data transferi gerçekleşir
	 *		DC = 0 ise Command mode'dur
	 *		DC = 1 ise Data mode'tur
	 *		CE pini hala 0 ise gönderme işlemi başarılıdır
	 */

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET); 		//CE pin is low

	if (mode == 0) // DC pini 0 ise
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  	//DC pin is low
	else if (mode == 1) // DC pini 1 ise
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  	//DC pin is High
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET); 		//CE pin is High
		return false;
	}

	HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

	return true;
}
