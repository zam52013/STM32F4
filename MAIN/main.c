 /******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************/
#include "stm32f4xx.h"
 int main()
 {	
		SystemInit();
	 NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//优先级设置  全为抢占式优先级
	 SysTick_Config(SystemCoreClock / 1000);			//uCOS时基1ms
		while(1);
 }



