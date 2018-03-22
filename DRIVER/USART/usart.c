/**
  ******************************************************************************
  * @file    usart.c 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for usart.c module
  ******************************************************************************/
	
	#include "usart.h"
	#include <stdio.h>
	#include <string.h>
	struct usart_messg USART1_MESSG;
	#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
	static void USART_Config(void)
	{	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_AHB1PeriphClockCmd(USARTx_TX_GPIO_CLK_1 | USARTx_RX_GPIO_CLK_1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
		GPIO_PinAFConfig(USARTx_TX_GPIO_PORT_1,USARTx_TX_SOURCE_1,USARTx_TX_AF_1); 
		GPIO_PinAFConfig(USARTx_RX_GPIO_PORT_1,USARTx_RX_SOURCE_1,USARTx_RX_AF_1); 
		
		GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN_1; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(USARTx_TX_GPIO_PORT_1,&GPIO_InitStructure); 
		
		GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN_1; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(USARTx_RX_GPIO_PORT_1,&GPIO_InitStructure);
		
		USART_InitStructure.USART_BaudRate = USART1BOUND;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		
		USART_Init(USARTx_1, &USART_InitStructure);
		USART_Cmd(USARTx_1, ENABLE);  
		USART_ClearFlag(USARTx_1, USART_FLAG_TC);
		
		USART_ITConfig(USARTx_1, USART_IT_RXNE, ENABLE);//开启相关中断

		//Usart1 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	}
	void USART1_IRQHandler(void)
	{
			u8 RES;
			static unsigned char statu=0;
			if(USART_GetITStatus(USART1, USART_IT_RXNE)!=RESET)
			{
				RES =USART_ReceiveData(USART1);
				if(!USART1_MESSG.receve_ok)
				{
					switch(statu)
					{
						case 0:
							memset(&USART1_MESSG.messg_buff[0],0,Usart_size); 
							USART1_MESSG.date_lenth=0;
							statu=1;
							USART1_MESSG.messg_buff[USART1_MESSG.date_lenth]=RES;
							USART1_MESSG.date_lenth++;
							break;
						case 1:
							if(RES==(0x0D))
							{
								statu=2;
								USART1_MESSG.messg_buff[USART1_MESSG.date_lenth]=RES;
								USART1_MESSG.date_lenth++;
							}
							else
							{
								USART1_MESSG.messg_buff[USART1_MESSG.date_lenth]=RES;
								USART1_MESSG.date_lenth++;
							}
							if(USART1_MESSG.date_lenth>Usart_size)
							{
								statu=0;
							}
							break;
						case 2:
							if(RES==(0x0A))
							{
								statu=0;
								USART1_MESSG.receve_ok=TRUE;
								USART1_MESSG.messg_buff[USART1_MESSG.date_lenth]=RES;
								USART1_MESSG.date_lenth++;
							}
							else
							{
								statu=0;
							}
							break;
						default:
							statu=0;
					}
				}
			}
	}
	/*******************************************************************************
* 函数名  : UART_SendString
* 描述    : USART发送字符串
* 输入    : *s字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void UART_SendString(USART_TypeDef* USARTx,char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s);//发送当前字符
		s++;
	}
}
	void Usart_Init_All()
	{
		USART_Config();
	}