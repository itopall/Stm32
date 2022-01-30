
#include "stm32f4xx.h"

extern uint32_t SystemCoreClock;

uint32_t systemClock;


void RCC_Congig(void)
{
	RCC -> CR &= ~(1 << 0); // Sadece o biti s�f�rlamaya yarar //HSI'y� 0 yapt�k
	RCC -> CR |= (1 << 16); // O bite �teleme yapt�k //HSE'yi 1 yapt�k
	while(!(RCC -> CR & (1 << 17))); // buras� 6 cycles sonra ��kacak alt sat�radan sonra devam edecek
	RCC -> CR |= (1 << 19); // CSSON bitini set ettik g�venlik biti bu
	RCC -> PLLCFGR = 0x00000000; // T�m bitleri s�f�rlad�k.
	RCC -> PLLCFGR |= (1 << 22); // HSE osilat�r� kullanmak i�in source se�tik.
	RCC -> PLLCFGR |= (1 << 4); // PLL_M  de�erini 4 yapmak i�in 4. biti 4 yapt�k.
	RCC -> PLLCFGR |= (1 << 9); // PLL_N bitlerini 168 say�s�na denk gelecek �ekilde setledik.
	RCC -> PLLCFGR |= (1 << 11);
	RCC -> PLLCFGR |= (1 << 13);
	//RCC -> PLLCFGR |= (168 << 6); // 6. bitten itibaren binary olarak (0010101000) say�s�n� girer yani dec olarak 168
	RCC -> PLLCFGR &= ~(1 << 16); // PLL_P de�erini s�f�ra ayarlamak i�in 16. ve 17. biti 0 yapmal�y�z.
	RCC -> PLLCFGR &= ~(1 << 17);
	RCC -> CR |= (1 << 24); // Pll on yapt�k.
	while(!(RCC -> CR & (1 << 25))); // Pll'i kontrol ediyoruz

	RCC -> CFGR &= ~(1 << 0); // system clock switch 0. bit 0 yap�ld�.
	RCC -> CFGR |= (1 << 1); // system clock switch 1. bit 1 yap�ld�. ��nk� hangi sinyali kullanaca��m�z� se�tik biz pll kullanaca��m�z i�in '10' yapt�k.
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
