
#include "stm32f4xx.h"


uint8_t m_address = 0x4E, TCS_W_ADDRESS = 0xD0;
void delay(uint32_t time)
{
	while(time--);
}
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
	RCC -> AHB1ENR |= 1 << 2;				//Enable gpioc port
	RCC -> AHB1ENR |= 1 << 1;				//enable GpioB port
	GPIOB -> OTYPER |= 1 << 8 | 1 << 9;	//output type open drain
	GPIOB -> AFR[1] |= 4 << 0 | 4 << 4;	//Alternate func select High i2c

	GPIOB -> MODER |= 2 << 16 | 2 << 18;	//Alternate func selected


}

void I2C_Config()
{
	RCC -> APB1ENR |= 1 << 22; 				//i2c2 clock enable

	I2C2 -> CR2 |= 0x0008; 				//i2c clock 8 Mhz
	I2C2 -> CCR |= 0x0028;				//i2c 100 khz
	I2C2 -> TRISE |= 0x0009;			//trise 9 yaptý
	I2C2 -> CR1 |= 1 << 0;				// i2c2 enable


}

void I2C_Write(uint8_t address, uint8_t data)
{
	I2C2->CR1 |= 0x0100; 		   // START BIT'I Gönder
		while(!(I2C2->SR1 & 0x0001));  // Start kosulunu bekle (SB=1)
		I2C2->DR = 0x4E; 	   		   // Slave adresi. okuma yazma komutu
		while(!(I2C2->SR1 & 0x0002));  // adres gönderimini bekle (ADDR=1)
	    while(!(I2C2->SR2 & 0x0001));  //MSL
		//I2C2->DR = address;		   // Cipin adresi
		while(!(I2C2->SR1 & 0x0080));  // TxE Data Register'in bosalmasini bekle(Txe)
		I2C2->DR = data;			   //Veriyi Yaz
		while(!(I2C2->SR1 & 0x0080));  // TxE Data Register'in bosalmasini bekle(Txe)
		while(!(I2C2->SR1 & 0x0004));  // Verinin gönderimini bekle (BTF)
		I2C2->CR1 |= 0x0200;
}
int i = 0;
int main(void)
{
	Rcc_Config();
	GPIO_Config();
	I2C_Config();

  while (1)
  {
	  if(GPIOC -> IDR & 1 << 13)
	  	  {
	  		  while(GPIOC -> IDR & 1 << 13)
	  			  ;
	  		  delay(1000000);
	  		  ++i;
	  	  }

	 	  switch(i)
	 	  {
	 	  case 0:
	 		  I2C_Write(m_address, 0x00);
	 		  break;
	 	  case 1:
	 		  I2C_Write(m_address, 0x01);
	 		  break;
	 	  case 2:
	 		  I2C_Write(m_address, 0x02);
	 		  break;
	 	  case 3:
	 		  I2C_Write(m_address, 0x04);
	 		  break;
	 	  case 4:
	 		  I2C_Write(m_address, 0x08);
	 		  break;
	 	  case 5:
	 		  I2C_Write(m_address, 0x10);
	 		  break;
	 	  case 6:
	 		  I2C_Write(m_address, 0x20);
	 		  break;
	 	  case 7:
	 		  I2C_Write(m_address, 0x40);
	 		  break;
	 	  case 8:
	 		  I2C_Write(m_address, 0x80);
	 		  break;
	 	  default:
	 		  i=0;
	 		  break;
	 	  }

  }
}
