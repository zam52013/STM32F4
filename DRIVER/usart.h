/**
  ******************************************************************************
  * @file    usart.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for usart.h module
  ******************************************************************************/
	
	#ifndef __USART_H
	#define __USART_H
	#ifdef __cplusplus
	extern "C" {
	#endif
	#include "stm32f4xx.h"
	
		
	/******缓存大小********/
	#define Usart_size 512
	/***************************/
	#define TRUE 1
	#define FALSE 0
	/* Definition for USARTx resources ******************************************/
  #define USART1BOUND 115200
	#define USARTx_1                           USART1
  #define USARTx_CLK_1                       RCC_APB2Periph_USART1
  #define USARTx_IRQn_1                      USART1_IRQn
  #define USARTx_IRQHandler_1                USART1_IRQHandler

  #define USARTx_TX_PIN_1                   GPIO_Pin_9                
  #define USARTx_TX_GPIO_PORT_1              GPIOA                       
  #define USARTx_TX_GPIO_CLK_1               RCC_AHB1Periph_GPIOA
  #define USARTx_TX_SOURCE_1                 GPIO_PinSource9
  #define USARTx_TX_AF_1                     GPIO_AF_USART1

  #define USARTx_RX_PIN_1                    GPIO_Pin_10                
  #define USARTx_RX_GPIO_PORT_1              GPIOA                    
  #define USARTx_RX_GPIO_CLK_1               RCC_AHB1Periph_GPIOA
  #define USARTx_RX_SOURCE_1                 GPIO_PinSource10
  #define USARTx_RX_AF_1                     GPIO_AF_USART1
	
	
	#define UART4BOUND 9600
	#define UARTx_4                         UART4
  #define UARTx_CLK_4                       RCC_APB1Periph_UART4
  #define UARTx_IRQn_4                      UART4_IRQn
  #define UARTx_IRQHandler_4                UART4_IRQHandler

  #define UARTx_TX_PIN_4                   GPIO_Pin_10                
  #define UARTx_TX_GPIO_PORT_4              GPIOC                       
  #define UARTx_TX_GPIO_CLK_4               RCC_AHB1Periph_GPIOC
  #define UARTx_TX_SOURCE_4                 GPIO_PinSource10
  #define UARTx_TX_AF_4                     GPIO_AF_UART4

  #define UARTx_RX_PIN_4                    GPIO_Pin_11                
  #define UARTx_RX_GPIO_PORT_4              GPIOC                    
  #define UARTx_RX_GPIO_CLK_4               RCC_AHB1Periph_GPIOC
  #define UARTx_RX_SOURCE_4                 GPIO_PinSource11
  #define UARTx_RX_AF_4                     GPIO_AF_UART4
	/******************************************************************************/	
	struct usart_messg
	{
		uint16_t date_lenth;			/*****接收数据长度****/
		unsigned char messg_buff[Usart_size];	/****接收数据缓存*****/
		uint8_t receve_ok;				/*****接收完成标志****/
	};
	extern struct usart_messg USART1_MESSG;
	void UART_SendString(USART_TypeDef* USARTx,char* s);
	void Usart_Init_All();
		
	#ifdef __cplusplus
	}
	#endif
	#endif
	
	
	