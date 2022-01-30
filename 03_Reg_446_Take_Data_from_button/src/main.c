#include "stm32f4xx.h"

void delay(uint32_t time)
{
	while(--time)
		;
}

void RCC_Config()
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
	RCC -> AHB1ENR |= (5 << 0);
	GPIOA -> MODER |= (1 << 10); // output yaptik
	GPIOA -> OTYPER |= 0x00000000;
	GPIOA -> OSPEEDR |= (1 << 10 | 1 << 11);
	GPIOA -> PUPDR |= (1 << 10);

}
int count  = 0;
int main(void)
{

	RCC_Config();
	GPIO_Config();
  while (1)
  {
	  if(GPIOC -> IDR & 1 << 13)
	  {
		  while(GPIOC -> IDR & 1 << 13)
			  ;
		  delay(1000000);
		  ++count;
	  }
	  if(count % 2 == 1)
		  GPIOA -> BSRR |= 1 << 5;
	  	  //GPIOA -> ODR |= 1 << 5;
	  else
		  GPIOA -> BSRR |= (1 << 5) << 16;
	  	  //GPIOA -> ODR &= ~(1 << 5);
  }
}
