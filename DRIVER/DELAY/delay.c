#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif
 
#ifdef CPU_CFG_CRITICAL_METHOD   //��CPU_CFG_CRITICAL_METHOD��������˵��ʹ����UCOSIII
#define OS_CRITICAL_METHOD
#define OS_TICKS_PER_SEC  OSCfg_TickRate_Hz
#define OS_TRUE OS_STATE_OS_RUNNING
#define OSLockNesting OSIntNestingCtr
#endif 

static u16  fac_us=0;//us��ʱ������			   
static u32 fac_ms=0;//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

unsigned char Time_statr_flag=0;	//������ʱ��־
unsigned char Time_out_flag=0;		//��ʱ��־
unsigned int Time_wait_cnt=0;		//�ȴ�ʱ��

uint16_t frameCounter = 0;

time_flag TIME_FLAG;

/*--------------------------------------
��������time_tick
�������������ڳ�ʱ����
���룺��
�������
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
��������time_tick
�������������ڳ�ʱ����
���룺��
�������
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

#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
//systick�жϷ�����,ʹ��ucosʱ�õ�
void SysTick_Handler(void)
{				  
	time_tick();
	times_Flag();	
	OSIntEnter();		//�����ж�
    OSTimeTick();       //����ucos��ʱ�ӷ������               
    OSIntExit();        //���������л����ж�
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