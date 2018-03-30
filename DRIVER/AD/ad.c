/**
  ******************************************************************************
  * @file    ad.c 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for ad.c module
  ******************************************************************************/
	#include "ad.h"
	
	__IO uint16_t uhADCxConvertedValue_1[1024] = 0;
	__IO uint16_t uhADCxConvertedValue_2[1024]= 0;
	
	static void ADC_Config(void)
	{
		ADC_InitTypeDef       ADC_InitStructure;
		ADC_CommonInitTypeDef ADC_CommonInitStructure;
		DMA_InitTypeDef       DMA_InitStructure;
		GPIO_InitTypeDef      GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 |ADCx_CHANNEL_GPIO_CLK_1 | ADCx_CHANNEL_GPIO_CLK_2,ENABLE);  
		RCC_APB2PeriphClockCmd(ADCx_CLK_1 | ADCx_CLK_2, ENABLE);

		DMA_InitStructure.DMA_Channel = DMA_CHANNELx_1;  
  		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS_1;
  		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADCxConvertedValue_1;
  		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  		DMA_InitStructure.DMA_BufferSize = 1024;
  		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  		DMA_Init(DMA_STREAMx_1, &DMA_InitStructure);
  		DMA_Cmd(DMA_STREAMx_1, ENABLE);

		DMA_InitStructure.DMA_Channel = DMA_CHANNELx_2;  
  		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS_2;
  		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADCxConvertedValue_2;
  		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  		DMA_InitStructure.DMA_BufferSize = 1024;
  		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  		DMA_Init(DMA_STREAMx_2, &DMA_InitStructure);
  		DMA_Cmd(DMA_STREAMx_2, ENABLE);

		GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PINx_1;
  		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  		GPIO_Init(ADC_GPIO_PORTx_1, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PINx_2;
  		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  		GPIO_Init(ADC_GPIO_PORTx_2, &GPIO_InitStructure);

		/* ADC Common Init **********************************************************/
 		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_18Cycles;
  		ADC_CommonInit(&ADC_CommonInitStructure);

		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  		ADC_InitStructure.ADC_NbrOfConversion = 1;
  		ADC_Init(ADCx_1, &ADC_InitStructure);

		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  		ADC_InitStructure.ADC_NbrOfConversion = 1;
  		ADC_Init(ADCx_2, &ADC_InitStructure);

		ADC_RegularChannelConfig(ADCx_1, ADC_CHANNEL_1, 1, ADC_SampleTime_15Cycles);
		ADC_RegularChannelConfig(ADCx_2, ADC_CHANNEL_2, 1, ADC_SampleTime_15Cycles);
		
		ADC_DMARequestAfterLastTransferCmd(ADCx_1, ENABLE);
		ADC_DMARequestAfterLastTransferCmd(ADCx_2, ENABLE);

		ADC_DMACmd(ADCx_1, ENABLE);
		ADC_DMACmd(ADCx_2, ENABLE);

		ADC_Cmd(ADCx_1, ENABLE);
		ADC_Cmd(ADCx_2, ENABLE);

	}
	
	void ADC_Init_All()
	{
		ADC_Config();
		ADC_SoftwareStartConv(ADCx_1);
		ADC_SoftwareStartConv(ADCx_2);
	}
	