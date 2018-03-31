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
int flag=0;
void send_data(u8 data)
{
 		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,data);//发送当前字符
}

void send(float data,float data1)
{
  u8 sum=0;
  u8 data_L,data_H;
  u8 data1_L,data1_H;
  data_H=(((u16)(data*32768/2000))>>8);
  data_L=(((u16)(data*32768/2000))&0x00ff);

  data1_H=(((u16)(data1/1000*32768/2000))>>8);
  data1_L=(((u16)(data1/1000*32768/2000))&0x00ff);
  send_data(0x55);
  sum+=0x55;
  send_data(0x52);
  sum+=0x52;
  send_data(data_L);
  sum+=data_L;
  send_data(data_H);
  sum+=data_H;
  send_data(data1_L);
  sum+=data1_L;
  send_data(data1_H);
  sum+=data1_H;
  send_data(0);
  sum+=0;
  send_data(0);
  sum+=0;
  send_data(0);
  sum+=0;
  send_data(0);
  sum+=0;  
  send_data(sum);
  
}
 int main()
 {	
    //int i=0;
    int count;
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
        
		if(data_flag==1)
		{	
			
		   for(count=0;count<1024;count++)
			{
				I_data[count]=uhADCxConvertedValue_buff1[count]*3.3/4096-3.3/2;
				Q_data[count]=uhADCxConvertedValue_buff2[count]*3.3/4096-3.3/2;
			//	printf("I_data=%f,",I_data[count]);
	     // printf("Q_data=%f\r\n",Q_data[count]);
			}
		    FFT(I_data,Q_data);
			data_flag=0;
			//printf("Q_out_MAX.amp=%f,",Q_out_MAX.amp);
			//printf("Q_out_MAX.fre=%f\r\n",Q_out_MAX.fre);
			
		}
		if(TIME_FLAG.time_sub.flag_1hz)
		{
			TIME_FLAG.time_sub.flag_1hz=FALSE;
			flag=1;
			printf("IQ_out_MAX.amp=%f,",IQ_out_MAX.amp);
			printf("IQ_out_MAX.fre=%f,",IQ_out_MAX.fre);
			printf("Z_out_MAX.amp=%f,",(float)Z_out_MAX.amp);
			printf("Z_out_MAX.fre=%f,",(float)Z_out_MAX.fre);
			printf("db_amp=%f,",db_amp);
			printf("z_dis=%f\r\n",Z_out_MAX.fre*0.001423825344/2);
			printf("dis=%f\r\n",IQ_out_MAX.fre*0.001423825344/2);
			//send(IQ_out_MAX.amp,IQ_out_MAX.fre);
			
	 	}
	 }
 }



