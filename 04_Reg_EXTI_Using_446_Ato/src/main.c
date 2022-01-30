
#include "stm32f4xx.h"

void Clk_Config()
{
	//Hse enable and hse ready control
	RCC -> CR |= 1 << 16;
	while(!(RCC -> CR & (1 << 17)))
		;

	//power enable
	RCC -> APB1ENR |= (1 << 28);
	PWR -> CR |= (3 << 14);

	FLASH -> ACR |= ((1 << 8) | (1 << 9) | (1 << 10) | (5 << 0));

	RCC -> CFGR &= ~(1 << 4); // AHB prescaler ilk 4-7 bit 0 oldu
	RCC -> CFGR |= (5 << 10); // APB1 prescaler 4 deðeri oldu
	RCC -> CFGR |= (4 << 13); // APB2 prescaler 2 deðeri oldu

	RCC -> PLLCFGR |= (4 << 0) | (168 << 6) | (2 << 16);

	//pll'i kullanacaðýmýzdan pll'i açtýk ve bayraðý kontrol ettik
	RCC -> CR |= 1 << 24;
	while(!(RCC -> CR & 1 << 25))
		;

	//Source seçtik o da pll yaptýk
	RCC -> CFGR |= 2 << 0;
	while(!(RCC -> CFGR & 2 << 2))
		;


}

void GPIO_Config()
{
	RCC -> AHB1ENR |= 5 << 0;

	GPIOA -> MODER |= 1 << 10;
	GPIOA -> OTYPER |= 0x00000000;
	GPIOA -> OSPEEDR |= 1 << 10 | 1 << 11;
	GPIOA -> PUPDR |= 1 << 10;
}

void EXTI_Config()
{
	RCC -> APB2ENR |= 1 << 14; // 0x00004000;

	SYSCFG->EXTICR[13] = 0x00000010;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);

	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_SetPriority(EXTI1_IRQn,1);

	EXTI -> IMR |= 0x00002000;
	EXTI -> RTSR |= 0x00002000;
}


void delay(uint32_t time)
{
	while(--time);
}
void EXTI0_IRQHandler()
{
	if(EXTI -> PR & 0x00000001)
	{
		GPIOA -> ODR &=  ~(1 << 5);
		delay(100000);
		EXTI -> PR = 0x00000001;
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI -> PR & 0x00000002)
	{
		GPIOA -> ODR |= (1 << 5);
		delay(100000);
		GPIOA -> ODR &= ~(1 << 5);
		delay(100000);
		EXTI -> PR = 0x00000002;
	}
}

int main(void)
{
	Clk_Config();
	GPIO_Config();
	EXTI_Config();
	  while (1)
	  {
		  GPIOA -> ODR |= 1 << 5;
	  }
}
