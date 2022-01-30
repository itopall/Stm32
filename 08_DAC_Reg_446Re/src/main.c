
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

void DAC1_Config()
{
	RCC -> AHB1ENR |= 0 << 1;
	RCC -> APB1ENR |= 1 << 29;

	DAC -> CR |= 1 << 0;

	DAC -> SWTRIGR = 0x00000000;

	DAC -> DHR12R1 = 0x00000000;
}

int i;

void delay(uint32_t time)
{
	while(time--)
		;
}

int main(void)
{

	Rcc_Config();
	DAC1_Config();
  while (1)
  {
	  for (i = 0; i< 4096;++i)
	  {
		  DAC -> DHR12R1 = i;
		  delay(1000);
	  }
	  i = 0;
  }
}
