#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif
 
#ifdef CPU_CFG_CRITICAL_METHOD   //如CPU_CFG_CRITICAL_METHOD被定义了说明使用了UCOSIII
#define OS_CRITICAL_METHOD
#define OS_TICKS_PER_SEC  OSCfg_TickRate_Hz
#define OS_TRUE OS_STATE_OS_RUNNING
#define OSLockNesting OSIntNestingCtr
#endif 

static u16  fac_us=0;//us延时倍乘数			   
static u32 fac_ms=0;//ms延时倍乘数,在ucos下,代表每个节拍的ms数

unsigned char Time_statr_flag=0;	//启动定时标志
unsigned char Time_out_flag=0;		//超时标志
unsigned int Time_wait_cnt=0;		//等待时间

uint16_t frameCounter = 0;

time_flag TIME_FLAG;

/*--------------------------------------
函数名：time_tick
函数描述：用于超时作用
输入：无
输出：无
;-------------------------------------*/
static void time_tick()
{
	static unsigned int Time_tic_cnt=0;
	if(Time_statr_flag)
	{
			if(Time_tic_cnt>=Time_wait_cnt)
			{
				Time_out_flag=1;
			}
			Time_tic_cnt++;
	}
	else
	{
		Time_tic_cnt=0;
	}
}

/*--------------------------------------
函数名：time_tick
函数描述：用于超时作用
输入：无
输出：无
;-------------------------------------*/
static void times_Flag()
{
	frameCounter++;
	TIME_FLAG.time_sub.flag_1Khz=TRUE;
  if (frameCounter > FRAME_COUNT)
  {
    	frameCounter = 1;
	}
	if ((frameCounter % COUNT_500HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_500hz=TRUE;
	}
	if ((frameCounter % COUNT_100HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_100hz=TRUE;
	}
	if ((frameCounter % COUNT_50HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_50hz=TRUE;
	}
	if ((frameCounter % COUNT_10HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_10hz=TRUE;
	}
	if ((frameCounter % COUNT_5HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_5hz=TRUE;
	}
	if ((frameCounter % COUNT_2HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_2hz=TRUE;
	}
	if ((frameCounter % COUNT_1HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_1hz=TRUE;
	}
	if ((frameCounter % COUNT_0_5HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_0_5hz=TRUE;
	}
}

#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
//systick中断服务函数,使用ucos时用到
void SysTick_Handler(void)
{				  
	time_tick();
	times_Flag();	
	OSIntEnter();		//进入中断
    OSTimeTick();       //调用ucos的时钟服务程序               
    OSIntExit();        //触发任务切换软中断
}
#else
void SysTick_Handler(void)
{				   
	fac_us--;
	fac_ms--;
	time_tick();
	times_Flag();
}
#endif 

void Delay_us(u16 num)
{
	fac_us=num;
	while(fac_us!=0);
}
void Delay_ms(u32 num)
{
	fac_ms=num*1000;
	while(fac_ms!=0);
}