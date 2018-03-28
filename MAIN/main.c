 /******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************/
#include "main.h"
#include <math.h>

#include "fft.h"
#include "da.h"




 int main()
 {	
    //int i=0;
	SystemInit();
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);//优先级设置  全为抢占式优先级
	SysTick_Config(SystemCoreClock / 1000);			//uCOS时基1ms
	Usart_Init_All();
	ADC_Init_All();
	DAC_Init_ALL();
	//LED_Init();
	 RELAY_Init();
	 printf("****************************************\r\n");
	 printf("*              避障雷达                *\r\n");
	 printf("*             版本号V1.0               *\r\n");
	 printf("****************************************\r\n");
	 //for(i=0;i<1024;i++)
	 //	{
	 	// I_data[i]=sin(i*3.14159/1024);
		// Q_data[i]=sin(i*3.14159*16/1024);
	 //	}
	 while(1)
	 {
//		if(TIME_FLAG.time_sub.flag_1hz)
//		{
//			TIME_FLAG.time_sub.flag_1hz=FALSE;
//			LED1_ON_OFF;
//			LED2_ON_OFF;
//			LED3_ON_OFF;
//			//printf("stm32 test ok\r\n");
//			//UART_SendString(UART4,"stm32 test ok\r\n");
//		}
//		if(TIME_FLAG.time_sub.flag_1Khz)
//		{
//			TIME_FLAG.time_sub.flag_1Khz=FALSE;
//		//	if(uhADCxConvertedValue_1<3700&&uhADCxConvertedValue_2<3700)
////				{

////			     i++;
//	//			 if(i>=1024) {i=0;j=1;}
//	//			}
//			
//		}
        
		if(TIME_FLAG.time_sub.flag_10hz&&data_flag==1)
		{
			TIME_FLAG.time_sub.flag_10hz=FALSE;		
		    FFT(I_data,Q_data);
			//printf("I_out_MAX.amp=%f,",I_out_MAX.amp);
			//printf("I_out_MAX.fre=%f\r\n",I_out_MAX.fre);
			//printf("Q_out_MAX.amp=%f,",Q_out_MAX.amp);
			//printf("Q_out_MAX.fre=%f\r\n",Q_out_MAX.fre);
			
		}
	 }
 }



