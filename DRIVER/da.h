/**
  ******************************************************************************
  * @file    da.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for da.h module
  ******************************************************************************/
	
	#ifndef __DA_H
	#define __DA_H
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "stm32f4xx.h"
	
	#define DAC_CHANNEL_1              DAC_Channel_2
  #define DACx_CHANNEL_GPIO_CLK_1    RCC_AHB1Periph_GPIOA
  #define DAC_GPIO_PINx_1                 GPIO_Pin_5
  #define DAC_GPIO_PORTx_1                GPIOA


  void DAC_Init_ALL();
   
	#ifdef __cplusplus
	}
	#endif
		
	#endif
	
	
	
	
	