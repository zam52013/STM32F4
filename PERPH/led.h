/**
  ******************************************************************************
  * @file    led.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for led.h module
  ******************************************************************************/

#ifndef _LED_H
#define _LED_H
#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "stm32f4xx.h"
	
/*********«******************/
#define LED1_PORT GPIOF
#define LED1_RCC RCC_AHB1Periph_GPIOF
#define LED1_GPIO GPIO_Pin_8
#define LED1_ON_OFF  GPIO_WriteBit(LED1_PORT,LED1_GPIO,(BitAction)!GPIO_ReadOutputDataBit(LED1_PORT,LED1_GPIO))
#define LED1_OFF  GPIO_ResetBits(LED1_PORT,LED1_GPIO)			
#define LED1_ON GPIO_SetBits(LED1_PORT,LED1_GPIO)			
/***************************/

/*********«*****************/
#define LED2_PORT GPIOF
#define LED2_RCC RCC_AHB1Periph_GPIOF
#define LED2_GPIO GPIO_Pin_9
#define LED2_ON_OFF  GPIO_WriteBit(LED2_PORT,LED2_GPIO,(BitAction)!GPIO_ReadOutputDataBit(LED2_PORT,LED2_GPIO))
#define LED2_OFF  GPIO_ResetBits(LED2_PORT,LED2_GPIO)			
#define LED2_ON GPIO_SetBits(LED2_PORT,LED2_GPIO)	
/***************************/

/*********«*****************/
#define LED3_PORT GPIOF
#define LED3_RCC RCC_AHB1Periph_GPIOF
#define LED3_GPIO GPIO_Pin_10
#define LED3_ON_OFF  GPIO_WriteBit(LED3_PORT,LED3_GPIO,(BitAction)!GPIO_ReadOutputDataBit(LED3_PORT,LED3_GPIO))
#define LED3_OFF  GPIO_ResetBits(LED3_PORT,LED3_GPIO)			
#define LED3_ON GPIO_SetBits(LED3_PORT,LED3_GPIO)	
/***************************/


void LED_Init(void);  //³õÊ¼»¯
		
		
		#ifdef __cplusplus
		}
	#endif
#endif

		
		
		