
#include "stm32f4xx.h"

extern uint32_t SystemCoreClock;

uint32_t systemClock;


void RCC_Congig(void)
{
	RCC -> CR &= ~(1 << 0); // Sadece o biti sýfýrlamaya yarar //HSI'yý 0 yaptýk
	RCC -> CR |= (1 << 16); // O bite öteleme yaptýk //HSE'yi 1 yaptýk
	while(!(RCC -> CR & (1 << 17))); // burasý 6 cycles sonra çýkacak alt satýradan sonra devam edecek
	RCC -> CR |= (1 << 19); // CSSON bitini set ettik güvenlik biti bu
	RCC -> PLLCFGR = 0x00000000; // Tüm bitleri sýfýrladýk.
	RCC -> PLLCFGR |= (1 << 22); // HSE osilatörü kullanmak için source seçtik.
	RCC -> PLLCFGR |= (1 << 4); // PLL_M  deðerini 4 yapmak için 4. biti 4 yaptýk.
	RCC -> PLLCFGR |= (1 << 9); // PLL_N bitlerini 168 sayýsýna denk gelecek þekilde setledik.
	RCC -> PLLCFGR |= (1 << 11);
	RCC -> PLLCFGR |= (1 << 13);
	//RCC -> PLLCFGR |= (168 << 6); // 6. bitten itibaren binary olarak (0010101000) sayýsýný girer yani dec olarak 168
	RCC -> PLLCFGR &= ~(1 << 16); // PLL_P deðerini sýfýra ayarlamak için 16. ve 17. biti 0 yapmalýyýz.
	RCC -> PLLCFGR &= ~(1 << 17);
	RCC -> CR |= (1 << 24); // Pll on yaptýk.
	while(!(RCC -> CR & (1 << 25))); // Pll'i kontrol ediyoruz

	RCC -> CFGR &= ~(1 << 0); // system clock switch 0. bit 0 yapýldý.
	RCC -> CFGR |= (1 << 1); // system clock switch 1. bit 1 yapýldý. Çünkü hangi sinyali kullanacaðýmýzý seçtik biz pll kullanacaðýmýz için '10' yaptýk.
	while(!(RCC -> CFGR & (1 << 3  && ~(1 << 2))));
}

int main(void)
{
	systemClock = SystemCoreClock;
	//RCC_DeInit(); 	//HSIEN PLL OFF

	SystemCoreClockUpdate(); // 16 000 000

	systemClock = SystemCoreClock;
	RCC_Congig();
  int i = 0;

  while (1)
  {
	i++;
  }
}
