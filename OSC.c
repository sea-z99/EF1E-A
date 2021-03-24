/*
 * OSC.c
 *
 *  Created on: 2019-9-27
 *      Author: charles_cai
 */
#include "main.h"

#ifndef OSC_C_
#define OSC_C_

void delay_ms(unsigned int num)
{
	unsigned int i,j;
	for(i=0;i<num;i++)
	{
		j=569;
		while(j--);
	}
}

/***************************************
 * 程序功能：提供4种不同的时钟源初始化模式
 * 输入：mode。
 * 			1-使用外部晶振做为时钟源，经过PLL倍频得到48MUPCK，UPCK做为系统时钟。
 * 			2-使用内部晶振做为时钟源，经过PLL倍频得到48MUPCK，UPCK做为系统时钟。
 * 			3-使用外部晶振做为系统时钟源，不分频，得到16M系统时钟。
 * 			4-使用内部晶振做为系统时钟源，不分频，得到16M系统时钟。
 * 输出：无
 ***************************************/
void Init_OSC(unsigned char mode)
{
	if(mode == 1)	//外部16M晶振做为时钟源，使用PLL倍频到32M
	{
		PLLCTL =0x03; //PLL时钟源选择外部高频晶振，PLL使能，PLL2倍频，PLL时钟源不分频,此时PLL时钟是16M，UPCK是32M，
		delay_ms(1);
		SCLKCTL =0x7C; //系统时钟源由SCKS决定，1:1分频，系统时钟源选择UPCK，
		HFCKCTL =0xCE; //UPCK选择PLL的倍频作为时钟源，使能高频外设时钟，分频比1:1，时钟源选择内部高频时钟。
	}
	else if(mode == 2) //内部16M晶振做为时钟源，使用PLL倍频到32M
	{
		PLLCTL =0x02; //PLL时钟源选择内部高频晶振，PLL使能，PLL2倍频，PLL时钟源不分频,此时PLL时钟是16M，UPCK是32M，
		delay_ms(1);
		SCLKCTL =0x7C; //系统时钟源由SCKS决定，1:1分频，系统时钟源选择UPCK，
		HFCKCTL =0xCE; //UPCK选择PLL的倍频作为时钟源，使能高频外设时钟，分频比1:1，时钟源选择内部高频时钟。
	}
	else if(mode == 3) //外部16M晶振做为时钟源，直接做为系统时钟
	{
		SCLKCTL =0X7A;//禁止输出时钟，选择外部高频作为时钟源，分频器1:1分频
		delay_ms(1);
		HFCKCTL =0x82;//使能高频外设时钟，INTHF/64,
	}
	else if(mode == 4) //内部16M晶振做为时钟源，直接做为系统时钟
	{
		SCLKCTL =0X78;//禁止输出时钟，选择内部高频作为时钟源，分频器1:1分频
		delay_ms(1);
		HFCKCTL =0x82;//使能高频外设时钟，外设时钟为INTHF/64,
	}
}

#endif /* OSC_C_ */
