/**
  ******************************************************************************
  * @file    da.c 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for da.c module
  ******************************************************************************/
	
	#include "da.h"

	static void TIM6_Config(void)
	{
  		TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  	/* TIM6 Periph clock enable */
  		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  	/* --------------------------------------------------------
  		TIM3 input clock (TIM6CLK) is set to 2 * APB1 clock (PCLK1), 
  		since APB1 prescaler is different from 1.   
    		TIM6CLK = 2 * PCLK1  
    		TIM6CLK = HCLK / 2 = SystemCoreClock /2 
          
  		TIM6 Update event occurs each TIM6CLK/256 
输出频率=42000000/4096/(TIM_Period+1)
  	Note: 
   			SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
   		Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
   		function to update SystemCoreClock variable value. Otherwise, any configuration
   		based on this variable will be incorrect.    

  		----------------------------------------------------------- */
 	 	/* Time base configuration */
  		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  		TIM_TimeBaseStructure.TIM_Period = 0xF;          
  		TIM_TimeBaseStructure.TIM_Prescaler = 0;       
 	 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
 	 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
 	 	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  		/* TIM6 TRGO selection */
 		TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
 	 	/* TIM6 enable counter */
	  	TIM_Cmd(TIM6, ENABLE);
	}
	static void DAC_Init_IO()
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(DACx_CHANNEL_GPIO_CLK_1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = DAC_GPIO_PINx_1;
 		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  		GPIO_Init(DAC_GPIO_PORTx_1, &GPIO_InitStructure);

		TIM6_Config();
	}
	void DAC_Ch2_TriangleConfig(void)
	{
		DAC_InitTypeDef  DAC_InitStructure;
		DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
		DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
		DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;//设置电压值
		DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
		DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

		/* Enable DAC Channel2 */
		DAC_Cmd(DAC_CHANNEL_1, ENABLE);

		/* Set DAC channel2 DHR12RD register */
		DAC_SetChannel2Data(DAC_Align_12b_R, 0);//设置升值高度
	}

	void DAC_Init_ALL()
	{
		DAC_Init_IO();
		DAC_Ch2_TriangleConfig();
	}
	
	
