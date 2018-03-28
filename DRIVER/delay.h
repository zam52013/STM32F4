#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f4xx.h"

extern unsigned char Time_statr_flag;	//������ʱ��־
extern unsigned char Time_out_flag;		//��ʱ��־
extern unsigned int Time_wait_cnt;		//�ȴ�ʱ��


#define FALSE 0
#define TRUE  1

#define FRAME_COUNT   2000

#define COUNT_500HZ   2         // Number of 1000 Hz frames for 500 Hz Loop
#define COUNT_100HZ   10        // Number of 1000 Hz frames for 100 Hz Loop
#define COUNT_50HZ    20        // Number of 1000 Hz frames for  50 Hz Loop
#define COUNT_10HZ    100       // Number of 1000 Hz frames for  10 Hz Loop
#define COUNT_5HZ     200       // Number of 1000 Hz frames for   5 Hz Loop
#define COUNT_2HZ     500       // Number of 1000 Hz frames for   2 Hz Loop
#define COUNT_1HZ     1000      // Number of 1000 Hz frames for   1 Hz Loop
#define COUNT_0_5HZ     2000      // Number of 1000 Hz frames for   1 Hz Loop


typedef union
{ 
	unsigned char time_all;
  struct
	{
		unsigned flag_1Khz;
		unsigned flag_500hz;
		unsigned flag_100hz;
		unsigned flag_50hz;
		unsigned flag_10hz;
		unsigned flag_5hz;
		unsigned flag_2hz;
		unsigned flag_1hz;
		unsigned flag_0_5hz;
	}time_sub;
}time_flag;

extern time_flag TIME_FLAG;

void Delay_us(u16 num);
void Delay_ms(u32 num);

#endif





























