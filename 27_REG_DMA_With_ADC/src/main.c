
#include "stm32f4xx.h"

uint32_t adc;
uint32_t adc1[8];

void Rcc_Config()
{

	//HSE aktif et
	RCC -> CR |= (1 << 16); //hseon bitini enable ettik
	while(!(RCC -> CR & (1 << 17)))
		;

	//Gücü aktifleþtirdik ve voltaj regülatörünü seçtik
	RCC -> APB1ENR |= 1 << 28;
	PWR -> CR |= (3 << 14);

	//Flash ayarlarýný yaptýk Prefetch enable | instruction cache enable | data cache enable | latency 5
	FLASH -> ACR |= ((1 << 8) | (1 << 9) | (1 << 10) | (5 << 0));

	RCC -> CFGR &= ~(1 << 4);
	RCC -> CFGR |= 5 << 10;
	RCC -> CFGR |= 4 << 13;


	// Pll m,n,p deðerlerini girdik
	RCC -> PLLCFGR |= (4 << 0 | 168 << 6 | 2 << 16);

	//pll aktifleþtirildi
	RCC -> CR |= 1 << 24;
	while (!(RCC -> CR & (1 << 25)))
		;

	//Source olarak pll kullandýk
	RCC -> CFGR |= 2 << 0;
	while (!(RCC -> CFGR & (2 << 2)))
		;

}
void GPIO_Config()
{
	RCC->AHB1ENR |= 0x00000001;	// GPIOA Clock Enable

	GPIOA->MODER |= 0x00000003;	// Pin 0 Analog
	GPIOA->OSPEEDR |= 0x00000003;	// Pin 0 100MHz;
}

void ADC_Config()
{
	RCC -> APB2ENR |= 1 << 8; // enable adc1

	ADC1 -> CR1 |= 1 << 8;   // Scan mode enable
	ADC1 -> CR1 |= 0 << 24;  // resolution set 12bit
	ADC1 -> CR2 |= 1 << 0;   //A/D converter enable
	ADC1 -> CR2 |= 1 << 1;	 //Continuous Conversion enable
	ADC1 -> CR2 |= 1 << 8;   //DMA enable
	ADC1 -> CR2 |= 1 << 9;	 //DDS Enable
	ADC1 -> CR2 |= 1 << 10;  //EOC enable
	//ADC1 -> CR2 |= 1 << 30;  //Start converison set 1

	ADC1 -> SQR1 |= 0 << 20; //conversion num 1
	ADC1 -> SQR3 |= 0 << 0;
}

void DMA_Config()
{
	RCC -> AHB1ENR |= 1 << 21;

	while((DMA2_Stream4 -> CR & 1 << 0) == 1)		// wait for stream4 to be 0
		;
	DMA2_Stream4 -> PAR |= (uint32_t)&ADC1 -> DR; //write adc1 address data
	DMA2_Stream4 -> M0AR = (uint32_t) &adc1;
	DMA2_Stream4 -> NDTR = 1;				//1 adc ile çaltýðýmýz için 1 sayýsý girdik
	DMA2_Stream4 -> CR |= 0 << 6;			// Data Transfer direction periphal to memory
	DMA2_Stream4 -> CR |= 1 << 8;			//Circular mode enable
	DMA2_Stream4 -> CR |= 0 << 9;			//peripheral increment mode fixed
	DMA2_Stream4 -> CR |= 1 << 10;			//memory increment mode is incremented
	DMA2_Stream4 -> CR |= 2 << 11;			//periheral data size 32-bit
	DMA2_Stream4 -> CR |= 2 << 13;			//memory data size 32-bit
	DMA2_Stream4 -> CR |= 3 << 16;			//priority level very high
	DMA2_Stream4 -> CR |= 0 << 25;			//channel 0 selected


	DMA2_Stream4 -> FCR |= 0 << 2;			//direct mode enable
	DMA2_Stream4 -> CR |= 1 << 0;
}

int main(void)
{
	Rcc_Config();
	GPIO_Config();
	ADC_Config();
	DMA_Config();
	ADC1->CR2 |= ADC_CR2_SWSTART;  //start conversion
  while (1)
  {
	  adc = adc1[0];
  }
}
