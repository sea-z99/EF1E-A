/*
 * Work.c
 *
 *  Created on: 2020-10-7
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "includes.h"
#include "PinConfig.h"
#include "Work.h"
#include "Led.h"
#include "SoftSpi.h"
#include "timer.h"

uint8_t PastMode=0;
uint8_t NowMode=0;
uint8_t ActMode=0;
uint8_t RT_PastMode=0;
uint8_t RT_NowMode=0;
uint8_t RT_ActMode=0;

volatile unsigned char LED_Stop_PWM_Flag,PWM_Timer_Flag,RT_Timer_Flag =0;
volatile unsigned int Stop_High_Addr,Stop_Low_Addr=0;
volatile unsigned int RT_High_Addr,RT_Low_Addr=0;
volatile unsigned char Tail_Status,Stop_Status,RT_Status,Fail_Status,RT_EN_Status=0;

extern unsigned int Stop_PWM_H1,Stop_PWM_L1,Stop_PWM_H2,Stop_PWM_L2;
struct Timer pwm;
uint64_t Time_Counter = 0;
void Time_Increase(void)
{
	Time_Counter++;
}
void Time_Clear(void)
{
	Time_Counter=0;
}
void Timer1_Init(void)
{
	T1CTL2 = 0x0C;	//	ʱ��Դ��SCLK/4��8��Ƶ
	T1H=0;
	T1L=0;
	PWMMODE = 1;	//ʹ������
	PP2=0x03;		//1000
	PP1=0xE8;
	T1CS =0;
	Change_PWM_5();
}
void Timer1_Start(void)
{
	T1ON = 1;		//T1��ʱ������
	T1IF = 0;
	T1IE = 1;	//ʹ��T1��ʱ�����жϹ���
}
void Timer2_Init(void)
{
	T2CTL0 = 0x0B;	//	Ԥ��Ƶ16�����Ƶ2
	T2CTL1 = 0x02; //���ϼ���,ʱ��Դ��SCLK-32M��
	T2H=0;
	T2L=0;
	PP60H=0x03;		//1000
	PP60L=0xE8;
}
void Timer2_Start(void)
{
	T2ON = 1;		//T2��ʱ������
	T2IF = 0;
	T2IE = 1;	//ʹ��T2��ʱ�����жϹ���
}
void RT_Check_Input(void)
{
	RT_Status = RT;
	RT_EN_Status = RT_EN;
	if(RT_Status==0)		//ת��͹ص�
	{
		RT_PastMode = RT_NowMode;RT_NowMode = RT_Mode1_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}
	if(RT_Status==1&&RT_EN_Status==1)		//ת��ߣ�ת��ʹ�ܸߣ�����
	{
		RT_PastMode = RT_NowMode;RT_NowMode = RT_Mode2_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}
	if(RT_Status==1&&RT_EN_Status==0)		//ת��ߣ�ת��ʹ�ܵͣ���ˮ
	{
		RT_PastMode = RT_NowMode;RT_NowMode = RT_Mode3_Status;
		if(RT_NowMode==RT_PastMode)
		{
			RT_ActMode=0;
		}
		else
		{
			RT_ActMode=RT_NowMode;
		}
	}

	RT_Mode_Act();
}
void RT_Mode_Act(void)
{
	switch(RT_ActMode)
	{
		case RT_Mode1_Status:
			Led_RT_AllClose();		//ת��ͣ�ת��ʹ�ܵͣ��ص�
			break;
		case RT_Mode2_Status:
			Led_RT_AllOpen();		//ת��ߣ�ת��ʹ�ܸߣ�����
			break;
		case RT_Mode3_Status:
			Led_RT_WaterOpen();		//ת��ߣ�ת��ʹ�ܵͣ���ˮ
			break;
		default:break;
	}
}
void Tail_Stop_Check_Input(void)
{
	Tail_Status = TAIL;
	Stop_Status = STOP;

	if(Tail_Status==0&&Stop_Status==0)//λ�õͣ��ƶ���
	{
		PastMode = NowMode;NowMode = Mode1_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	if(Tail_Status==1&&Stop_Status==0)//λ�øߣ��ƶ���
	{
		PastMode = NowMode;NowMode = Mode2_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	if(Tail_Status==0&&Stop_Status==1)//λ�õͣ��ƶ���
	{
		PastMode = NowMode;NowMode = Mode3_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	if(Tail_Status==1&&Stop_Status==1)//λ�øߣ��ƶ���
	{
		PastMode = NowMode;NowMode = Mode4_Status;
		if(NowMode==PastMode)
		{
			ActMode=0;
		}
		else
		{
			ActMode=NowMode;
		}
	}
	Mode_Act();
}
void Mode_Act(void)
{
	switch(ActMode)
	{
	case Mode1_Status:
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		LED_Stop_AllClose();	//�ƶ���ȫ�ر�
		break;
	case Mode2_Status:
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		LED_Stop_PWMOpen();		//�ƶ���5%PWM����
		break;
	case Mode3_Status:
		Led_Tail_AllClose();	//λ�õ�ȫ�ر�
		LED_Stop_AllOpen();		//�ƶ���ȫ����
		break;
	case Mode4_Status:
		Led_Tail_AllOpen();		//λ�õ�ȫ����
		LED_Stop_AllOpen();		//�ƶ���ȫ����
		break;
	default:break;
	}
}
extern unsigned int Stop_PWM_H1,Stop_PWM_L1,Stop_PWM_H2,Stop_PWM_L2=0;
void Timer_PWM_Callback(void)
{
	if(PWM_Timer_Flag)
	{
		PWM_Timer_Flag =0;
		PP2=Stop_PWM_H1;		//250
		PP1=Stop_PWM_L1;
		if(Stop_High_Addr & ADDR1)
			STOP_1=1;
		if(Stop_High_Addr & ADDR2)
			STOP_2=1;
		if(Stop_High_Addr & ADDR3)
			STOP_3=1;
		if(Stop_High_Addr & ADDR4)
			STOP_4=1;
	}
	else
	{
		PWM_Timer_Flag =1;
		PP2=Stop_PWM_H2;		//4750
		PP1=Stop_PWM_L2;
		if(Stop_Low_Addr & ADDR1)
			STOP_1=0;
		if(Stop_Low_Addr & ADDR2)
			STOP_2=0;
		if(Stop_Low_Addr & ADDR3)
			STOP_3=0;
		if(Stop_Low_Addr & ADDR4)
			STOP_4=0;
	}
}
void RT_PWM_Callback(void)
{
	if(RT_Timer_Flag)
	{
		RT_Timer_Flag =0;
		PP60H=0x0A;		//250
		PP60L=0xBE;
		if(RT_High_Addr & ADDR1)
			RT_1=1;
		if(RT_High_Addr & ADDR2)
			RT_2=1;
		if(RT_High_Addr & ADDR3)
			RT_3=1;
	}
	else
	{
		RT_Timer_Flag =1;
		PP60H=0x08;		//4750
		PP60L=0xCA;
		if(RT_High_Addr & ADDR1)
			RT_1=0;
		if(RT_High_Addr & ADDR2)
			RT_2=0;
		if(RT_High_Addr & ADDR3)
			RT_3=0;
	}
}
void Led_Hello(void)
{
	Led_RT_WaterOpen();//280
	delay_ms(200);
	Led_RT_AllClose();
	delay_ms(300);
	Led_RT_WaterOpen();//280
	delay_ms(200);
	Led_RT_AllClose();
	delay_ms(300);
	delay_ms(2600);
	Tail_LowWater_Open();//400
	delay_ms(700);
	Tail_HighWater_Open();//1450
	Stop_HighBackWater_Open();//300
	delay_ms(3660);
	Tail1_FullBackWater_Open();//1500
	delay_ms(2000);
	Tail2_Stop_FullWater_Open();
	for(;;);
}
void Led_Bye(void)
{
	Led_Tail_AllOpen();
	LED_Stop_AllOpen();
	delay_ms(1000);
	Led_RT_WaterOpen();
	delay_ms(200);
	Led_RT_AllClose();
	delay_ms(200);
	/*Tail_LowWater_Blinky();
	delay_ms(1700);
	Tail1_2_Stop_BackWater_Close();
	delay_ms(1160);
	Tail1_2_Stop_FullWater_Close();
	delay_ms(1000);
	Tail12_Breath_Close();*/
	Tail_Single_Low_water();
	Tail_whole_Low_water_reverse();
	Tail_Single_Out_water_reverse();
	Random_flash();

	for(;;);
}
void Led_Hello_Check(void)
{
	Tail_Status = TAIL;
	Stop_Status = STOP;
	RT_Status = RT;
	RT_EN_Status = RT_EN;
	if(Tail_Status==1&&Stop_Status==1&&RT_Status==1&&RT_EN_Status==0)
	{
		Led_Hello();
	}
	if(Tail_Status==1&&Stop_Status==1&&RT_Status==1&&RT_EN_Status==1)
	{
		Led_Bye();
	}
}


