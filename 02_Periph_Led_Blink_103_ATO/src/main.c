
#include <stddef.h>
#include "stm32f10x.h"

#ifdef USE_STM3210B_EVAL
 #include "stm3210b_eval.h"
 #include "stm3210b_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval.h"
 #include "stm3210e_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval.h"
 #include "stm3210c_eval_lcd.h"
 #include "stm3210c_eval_i2c_ee.h"
 #define USE_BOARD
 #define USE_LED
 #define USE_SEE
#elif defined USE_STM32100B_EVAL
 #include "stm32100b_eval.h"
 #include "stm32100b_eval_lcd.h"
 #define USE_BOARD
 #define USE_LED
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval.h"
 #include "stm32100e_eval_lcd.h"
 #include "stm32100e_eval_i2c_ee.h"
 #define USE_BOARD
 #define USE_LED
 #define USE_SEE
#elif defined USE_STM32_DISCOVERY
 #include "STM32vldiscovery.h"
#elif defined USE_IAR_STM32F103ZE
 #include "board.h"
 #define USE_LED
#elif defined USE_KEIL_MCBSTM32
 #include "board.h"
 #define USE_LED
#endif


/* Private typedef */
/* Private define  */
#ifdef USE_STM3210B_EVAL
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210B-EVAL    "
  #define MESSAGE4   "                    "
#elif defined USE_STM3210E_EVAL
  #define MESSAGE1   " STM32 High Density "
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210E-EVAL    "
  #define MESSAGE4   "                    "
#elif defined USE_STM3210C_EVAL
  #define MESSAGE1   " STM32 Connectivity "
  #define MESSAGE2   " Line Device running"
  #define MESSAGE3   " on STM3210C-EVAL   "
  #define MESSAGE4   "                    "
#elif defined USE_STM32100B_EVAL
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Value Line Device  "
  #define MESSAGE3   "    running on      "
  #define MESSAGE4   "   STM32100B-EVAL   "
#elif defined USE_STM32100E_EVAL
  #define MESSAGE1   " STM32 High Density "
  #define MESSAGE2   " Value Line Device  "
  #define MESSAGE3   "    running on      "
  #define MESSAGE4   "   STM32100E-EVAL   "
#endif
  #define MESSAGE5   " program built with "
  #define MESSAGE6   " Atollic TrueSTUDIO "

void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void Delay(uint16_t d)
{
	for(int i = 0; i < d; ++i)
		;
}


int main(void)
{

#ifdef USE_LED
  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

  /* Turn on LEDs */
  STM_EVAL_LEDOn(LED1);
  STM_EVAL_LEDOn(LED2);
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);

#elif defined USE_STM32_DISCOVERY
  STM32vldiscovery_LEDInit(LED3);
  STM32vldiscovery_LEDInit(LED4);
  STM32vldiscovery_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  STM32vldiscovery_LEDOff(LED3);
  STM32vldiscovery_LEDOff(LED4);
#endif

#ifdef USE_BOARD
  /* Initialize the LCD */
#ifdef USE_STM3210B_EVAL
  STM3210B_LCD_Init();
#elif defined USE_STM3210E_EVAL
  STM3210E_LCD_Init();
#elif defined USE_STM3210C_EVAL
  STM3210C_LCD_Init();
#elif defined USE_STM32100B_EVAL
  STM32100B_LCD_Init();
#endif

  /* Display message on STM3210X-EVAL LCD */
  /* Clear the LCD */
  LCD_Clear(White);

  /* Set the LCD Back Color */
  LCD_SetBackColor(Blue);
  /* Set the LCD Text Color */
  LCD_SetTextColor(White);
  LCD_DisplayStringLine(Line0, (uint8_t *)MESSAGE1);
  LCD_DisplayStringLine(Line1, (uint8_t *)MESSAGE2);
  LCD_DisplayStringLine(Line2, (uint8_t *)MESSAGE3);
  LCD_DisplayStringLine(Line3, (uint8_t *)MESSAGE4);
  LCD_DisplayStringLine(Line4, (uint8_t *)MESSAGE5);
  LCD_DisplayStringLine(Line5, (uint8_t *)MESSAGE6);

  /* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM1, &USART_InitStructure);
#endif


  GPIO_Config();
  /* Infinite loop */
  while (1)
  {
	  GPIO_SetBits(GPIOC,GPIO_Pin_13);
	  Delay(100000);
	  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	  Delay(100000);

#ifdef USE_LED
	STM_EVAL_LEDToggle(LED1);

#elif defined USE_STM32_DISCOVERY
    if(0 == STM32vldiscovery_PBGetState(BUTTON_USER))
    {
      /* Toggle LED3 */
      STM32vldiscovery_LEDToggle(LED3);
      /* Turn Off LED4 */
      STM32vldiscovery_LEDOff(LED4);
    }
    else
    {
      /* Toggle LED4 */
        STM32vldiscovery_LEDToggle(LED4);
      /* Turn Off LED3 */
      STM32vldiscovery_LEDOff(LED3);
    }
#endif
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

