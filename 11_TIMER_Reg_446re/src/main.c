
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

uint16_t count = 0;

void TIM_Config()
{
	RCC -> APB1ENR |= 1 << 0; // Timer2 clock enable

	TIM2 -> CR |= 0 << 4; // upcounter selected
	TIM2 -> CR |= 0 << 5; // Center aligned mode edge-aligned mode selected
	TIM2 -> CR |= 0 << 8; // set clock division to 1
	TIM2 -> SMCR |= 0 << 0; //internal source clock
	TIM2 -> EGR |= 1 << 0; // timer update generation
	TIM2 -> PSC = 41999; // 84 Mhz / prescaler + 1
	TIM2 -> ARR = 2000; // 1 sn de 1 2000 olacak
	TIM2 -> CR1 |= 1 << 0; // Counter enable
}


int main(void)
{
	Rcc_Config();
	TIM_Config();

  while (1)
  {
	  count = TIM2 -> CNT;
  }
}
