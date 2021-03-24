/*
 * Led.h
 *
 *  Created on: 2020-10-9
 *      Author: Rick
 */

#ifndef LED_H_
#define LED_H_

#define LED_Interval	(50)
#define RT_Interval		(20)

#define U1 			1
#define U2 			2

#define OUT1 0x1F
#define OUT2 0x20
#define OUT3 0x21
#define OUT4 0x22
#define OUT5 0x23
#define OUT6 0x24
#define OUT7 0x25
#define OUT8 0x26
#define OUT9 0x27
#define OUT10 0x28
#define OUT11 0x29
#define OUT12 0x2A
#define OUT13 0x2B
#define OUT14 0x2C
#define OUT15 0x2D
#define OUT16 0x2E
#define OUT17 0x2F
#define OUT18 0x30

#define ADDR1 		1<<0
#define ADDR2 		1<<1
#define ADDR3 		1<<2
#define ADDR4 		1<<3

void LED_Stop_AllOpen(void);
void LED_Stop_AllClose(void);
void LED_Stop_PWMOpen(void);
void Led_RT_AllOpen(void);
void Led_RT_AllClose(void);
void Led_RT_WaterOpen(void);
void Led_Tail_AllOpen(void);
void Led_Tail_AllClose(void);
void Tail12_Breath_Open(void);
void Tail12_Breath_Close(void);
void Tail12_Breath_CloseTo10(void);
void Tail_LowWater_Open(void);
void Tail_HighWater_Open(void);
void Stop_HighBackWater_Open(void);
void Tail1_FullBackWater_Open(void);
void Tail2_Stop_FullWater_Open(void);
void Tail_LowWater_Blinky(void);
void Tail1_2_Stop_BackWater_Close(void);
void Tail1_2_Stop_FullWater_Close(void);

#endif /* LED_H_ */
