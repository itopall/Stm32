
#include "stm32f4xx.h"
#define PLL_M 	4 // Pll_M degeri sabit olarak Atadik
#define PLL_N 	180 // Pll_N degeri sabit olarak Atadik
#define PLL_P		2	// Pll_P degeri sabit olarak Atadik

void RCC_Config(void)
{
	RCC -> CR |= 1 << 16;
	while(!(RCC -> CR & (1 << 17)));

	RCC -> APB1ENR |= 1 << 28;
	PWR -> CR |= 3 << 14;

	FLASH -> ACR |= (1 << 8 | 1 << 9 | 1 << 10 | 5 << 0);

	RCC -> CFGR &=  ~(1 << 4);
	RCC -> CFGR |= 5 << 10;
	RCC -> CFGR |= 4 << 13;

	RCC -> PLLCFGR |= (PLL_M << 0 | PLL_N << 6 | PLL_P << 16);

	RCC -> CR |= 1 << 24;
	while(!(RCC -> CR & (1 << 25)));

	RCC -> CFGR |= (2 << 0);
	while(!(RCC -> CFGR & (2 << 2)));

}

void GPIO_Config(void)
{
	RCC -> AHB1ENR |= (1 << 0);

	GPIOA -> MODER |= (1 << 10);
	//GPIOA ->PUPDR
	GPIOA -> OTYPER = 0;
	GPIOA -> OSPEEDR = 0;

}

int main(void)
{
	RCC_Config();
	GPIO_Config();
  	while(1)
	{
			GPIOA -> ODR |= (1<<5);// set PA5 pin
			for(int i = 0;i < 100000; ++i);
			GPIOA -> ODR &= ~(1<<5); // reset PA5 pin
			for(int i = 0;i < 100000; ++i);

	}
}
