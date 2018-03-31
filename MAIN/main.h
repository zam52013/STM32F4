/**
  ******************************************************************************
  * @file    main.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for main.h module
  ******************************************************************************/
	#ifndef __MAIN_H
	#define __MAIN_H
	
 #include "stm32f4xx.h"
 
 #include "ad.h"
 #include "da.h"
 #include "usart.h"
 #include "flash.h"
 #include "delay.h"
 #include "led.h"
 #include "relay.h"
 
 #include "arm_math.h"
 extern int flag;
 void send(float data,float data1);
 #endif
 