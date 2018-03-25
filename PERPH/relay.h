/**
  ******************************************************************************
  * @file    relay.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for relay.h module
  ******************************************************************************/

#ifndef _RELAY_H
#define _RELAY_H
#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "stm32f4xx.h"
	/*********¼ÌµçÆ÷****************/
	#define RELAY1_PORT GPIOE
	#define RELAY1_RCC RCC_AHB1Periph_GPIOE
	#define RELAY1_GPIO GPIO_Pin_5
	#define RELAY1_ON_OFF  GPIO_WriteBit(RELAY1_PORT,RELAY1_GPIO,(BitAction)!GPIO_ReadOutputDataBit(RELAY1_PORT,RELAY1_GPIO))
	#define RELAY1_OFF  GPIO_ResetBits(RELAY1_PORT,RELAY1_GPIO)			
	#define RELAY1_ON GPIO_SetBits(RELAY1_PORT,RELAY1_GPIO)	
/***************************/
		void RELAY_Init(void);
	#ifdef __cplusplus
	}
	#endif
#endif
	
	
	
	
	
	
	
	
	
	
	
	