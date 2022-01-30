
#include "stm32f4xx.h"

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
	RCC -> AHB1ENR |= 1 << 0;

	GPIOA -> MODER |= 2 << 2;
	GPIOA -> MODER |= 2 << 10;
	GPIOA -> AFR[0] |= 1 << 4 | 1 << 20;

}

void Timer_Config()
{
	RCC -> APB1ENR |= 1 << 0;

	TIM2 -> CR1 |= 0 << 4; // set upcounter
	TIM2 -> CR1 |= 0 << 5; // Center-aligned mode set edge-aligned mode
	TIM2 -> CR1 |= 0 << 8; // clock division 1

	TIM2 -> CCMR1 |= 0 << 0; // 2nd channel configured as output
	TIM2 -> CCMR1 |= 0 << 8;
	TIM2 -> CCMR1 |= 6 << 4;
	TIM2 -> CCMR1 |= 6 << 12; // output selected mode pwm mode 2

	TIM2 -> CCER |= 1 << 0;
	TIM2 -> CCER |= 1 << 4;

	TIM2 -> PSC |= 83;
	TIM2 -> ARR |= 99;
	TIM2 -> CCR1 = 2499;
	TIM2 -> CCR2 = 7249;
	TIM2 -> CR1 |= 1 << 0;
}
int main(void)
{

	Rcc_Config();
	GPIO_Config();
  while (1)
  {

		Timer_Config();
  }
}
