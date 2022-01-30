
#include "stm32f4xx.h"

uint8_t adc_value;

void Clk_Config()
{
	RCC -> CR |= 0x00010000;
	while(!(RCC -> CR & 0x00020000));

	RCC -> APB1ENR |= 0x10000000;
	PWR -> CR |= 0x0000C000;

	FLASH -> ACR |= (1 << 8) | (1 << 9) | (1 << 10) | (5 << 0);

	RCC -> CFGR &= ~(1 << 4);
	RCC -> CFGR |= 5 << 10;
	RCC -> CFGR |= 4 << 13;

	RCC -> PLLCFGR |= (4 << 0) | (168 << 6) | (2 << 16) | 1 << 22;

	RCC -> CR |= 1 << 24;
	while(!(RCC -> CR & 1 << 25));

	RCC -> CFGR |= 2 << 0;
	while(!(RCC -> CFGR & 2 << 2));
}

void GPIO_Config()
{
	RCC -> AHB1ENR |= 1 << 0;
	GPIOA -> MODER |= 3 << 0;
	GPIOA -> OSPEEDR |= 3 << 0;
}

void ADC_Config()
{
	RCC -> APB2ENR |= 1 << 8;

	ADC1 -> CR1 |= 2 << 24; // Resolution 8 bit
	ADC1 -> CR2 |= 1 << 0;  // ADC enable (ADON bit 1)
	ADC1 -> SMPR2 |= 3 << 15; // 56 cycles  /kaç saykýlda bir iþlem yapsýn diyoruz/
	ADC -> CCR |= 1 << 16; //div 4

}

uint8_t ADC_Read()
{
	uint8_t value;
	ADC1 -> CR2 |= 0x40000000; // Yazýlýmsal olarak ADC'yi baþlattýk

	while(!(ADC1 -> SR & 1 << 1)); //çevrim tamamlanana kadar bekle tamamlanýnca çýk demek

	value = ADC1 -> DR; //okunan deðeri deðiþkene atadýk

	return value;
}

int main(void)
{

	Clk_Config();
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = ADC_Read();
  }
}
