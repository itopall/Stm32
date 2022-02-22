
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

void FLASH_Unlocker()
{
	while (FLASH->SR & (1 << 16));


	FLASH->KEYR = 0x45670123; // Write key1 value
	FLASH->KEYR = 0xCDEF89AB; // Write key2 value
}

void FLASH_Erase()
{
	while (FLASH->SR & (1 << 16)); 	// waiting BSY bit

	FLASH->CR |= (1 << 1); 			// SER register writing 1

	FLASH->CR |= (7 << 3);			//Sector 7 selected

	FLASH->CR |= (1 << 16); 		// STRT register writing 1

	while (FLASH->SR & (1 << 16)); 	// waiting BSY bit

	if (FLASH->SR & 0x00000001)
		FLASH->SR |= 0x00000001;
	else
	{
		//deleted is unsuccessful
	}

	FLASH->CR &= ~(1 << 1); 		// SER is reseted;
}

void FLASH_Write(uint32_t address , uint32_t data)
{
	while (FLASH->SR & (1 << 16)); 		// waiting BSY bit

	FLASH->CR |= (1 << 0); 				// PG register is actived

	FLASH->CR |= (2 << 8); 				// PSIZE register is made 32bits

	*(__IO uint32_t*)address = data; 	//Adresin içindeki deðer data olsun dedik

	while (FLASH->SR & (1 << 16)); 		// waiting BSY bit

	if (FLASH->SR & 0x00000001)
		FLASH->SR |= 0x00000001;
	else
	{
		//writing is unsuccessful
	}

	FLASH->CR &= ~(1 << 0); 			//PG is reseted
}

uint32_t FLASH_Read(uint32_t address)
{
	uint32_t myFlashData;

	myFlashData = *(uint32_t *)address;

	return myFlashData;
}


void FLASH_Locker()
{
	while (FLASH->SR & (1 << 16)); 		// waiting BSY bit

	FLASH->CR |= (1 << 31); 			//Lock register is enabled.
}

int main(void)
{
	Rcc_Config();
	FLASH_Unlocker();
	FLASH_Write(0x08060000, 0xCC); 		// Sector 7 address is wrote a 0xCC data;
	FLASH_Locker();
	FLASH_Unlocker();
	FLASH_Read(0x08060000);
	FLASH_Locker();
  while (1)
  {
	i++;
  }
}
