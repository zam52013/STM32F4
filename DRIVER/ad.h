/**
  ******************************************************************************
  * @file    ad.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for ad.h module
  ******************************************************************************/
	#ifndef __AD_H
	#define __AD_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "stm32f4xx.h"

	 #define ADCx_1                     ADC3
	 #define ADC_CHANNEL_1              ADC_Channel_7
   #define ADCx_CLK_1                 RCC_APB2Periph_ADC3
   #define ADCx_CHANNEL_GPIO_CLK_1    RCC_AHB1Periph_GPIOF
   #define ADC_GPIO_PINx_1                 GPIO_Pin_9
   #define ADC_GPIO_PORTx_1                GPIOF
   #define DMA_CHANNELx_1             DMA_Channel_2
   #define DMA_STREAMx_1              DMA2_Stream0
   #define ADCx_DR_ADDRESS_1          ((uint32_t)0x4001224C)
/*
	 #define ADCx_1                     ADC2
	 #define ADC_CHANNEL_1              ADC_Channel_7
   #define ADCx_CLK_1                 RCC_APB2Periph_ADC3
   #define ADCx_CHANNEL_GPIO_CLK_1    RCC_AHB1Periph_GPIOF
   #define ADC_GPIO_PINx_1                 GPIO_Pin_9
   #define ADC_GPIO_PORTx_1                GPIOF
   #define DMA_CHANNELx_1             DMA_Channel_2
   #define DMA_STREAMx_1              DMA2_Stream0
   #define ADCx_DR_ADDRESS_1          ((uint32_t)0x4001214C)
 */  
	 #define ADCx_2                     ADC1
	 #define ADC_CHANNEL_2              ADC_Channel_7
   #define ADCx_CLK_2                 RCC_APB2Periph_ADC1
   #define ADCx_CHANNEL_GPIO_CLK_2    RCC_AHB1Periph_GPIOA
   #define ADC_GPIO_PINx_2                 GPIO_Pin_7
   #define ADC_GPIO_PORTx_2                GPIOA
   #define DMA_CHANNELx_2             DMA_Channel_0
   #define DMA_STREAMx_2              DMA2_Stream4
   #define ADCx_DR_ADDRESS_2          ((uint32_t)0x4001204C)


   	extern __IO uint16_t uhADCxConvertedValue_1[1024];
	extern __IO uint16_t uhADCxConvertedValue_2[1024];

	void ADC_Init_All();
	#ifdef __cplusplus
		}
	#endif
	
	#endif
	
	