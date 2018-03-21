#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f4xx.h"

extern unsigned char Time_statr_flag;	//启动定时标志
extern unsigned char Time_out_flag;		//超时标志
extern unsigned int Time_wait_cnt;		//等待时间

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























