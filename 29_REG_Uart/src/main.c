
#include "stm32f4xx.h"

unsigned char WAdr, RAdr;
char RxBuf[128];
int j = 0;

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
	RCC -> AHB1ENR |= 1 << 0;				//Enable gpioA port

	GPIOA -> MODER |= 2 << 4 | 2 << 6;		//Alternate func selected
	GPIOA -> AFR[0] |= 7 << 8 | 7 << 12;	//Usart2 selected PA2 & PA3


}

void USART_Config()
{
	RCC -> APB1ENR |= 1 << 17;			//USART2 Enable


	//USART2 -> BRR = 0x1112;				//baudrate 9600
	USART2 -> CR1 |= 1 << 2;			//Rx enable
	USART2 -> CR1 |= 1 << 3;			//Tx enable
	USART2 -> CR1 |= 1 << 5; 			//Rx interrupt enable
	USART2 -> CR1 |= 0 << 10;			//Parity disable
	USART2 -> CR1 |= 0 << 12;			//Word length 8bit
	USART2 -> BRR = 0x1112;
	USART2 -> CR1 |= 1 << 13;			//usart enable

}

void NVIC_Config()
{
	NVIC -> ISER[1] |= 0x80;
}

void SendChar(char Tx)
{
	while (!(USART2 -> SR & 1 << 7)) // Tx buffer dolu ise bekle
		;
	USART2 -> DR = Tx;
}

void SendTxt(char *Pc)
{
	while (*Pc)
	{
		SendChar(*Pc);
		++Pc;
	}
}

char DataReady()
{
	return (WAdr-RAdr);
}

char ReadChar()
{
	char Dat;
	Dat = RxBuf[RAdr];
	RAdr=(RAdr+1)&0x7F;
	return(Dat);
}

void USART2_IRQHandler()
{
	volatile int Sts;
	Sts=USART2->SR;
	RxBuf[WAdr]=USART2->DR;
	WAdr=(WAdr+1)&0x7F;
}
int main(void)
{
	Rcc_Config();
	GPIO_Config();
	USART_Config();
	NVIC_Config();
	SendTxt("Hello World\n");
	for(int i=0;i<0x1000000;i++);
	while(DataReady()) ReadChar();
  while (1)
  {

  }
}
