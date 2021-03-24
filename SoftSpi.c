/*
 * SoftSpi.c
 *
 *  Created on: 2020-10-6
 *      Author: Rick
 */
#include<KF8A200GQS.h>
#include "includes.h"
#include "PinConfig.h"
#include "SoftSpi.h"
#include "Work.h"
void spi_init(void)
{
	TR64 =1;
	TR65 =0;
	TR63 =0;
	APFCTL9 = 0;

	SSCI2EN=0;				//关闭SPI模块，初始化完之后再打开

	SSCI2CTL0=0X01;			//SPI 主控模式，时钟 = 工作时钟/64
	SSCI2CTL1=0X00;
	SSCI2CTL2=0X00;
	SSCI2STA=0X40;  //空闲时为低电平，在SCL下降沿发送数据

	SSCI2EN=1;

	SDB=1;
	Spi_CS_High(0);
}
void Spi_CS_High(char id)
{
	switch(id)
	{
		case 0:U1_CS=1;U2_CS=1;break;
		case 1:U1_CS=1;break;
		case 2:U2_CS=1;break;
	}
}
void Spi_CS_Low(char id)
{
	switch(id)
	{
		case 0:U1_CS=0;U2_CS=0;break;
		case 1:U1_CS=0;break;
		case 2:U2_CS=0;break;
	}
}
void SPI_Write_2Byte(unsigned char id,unsigned char addr,unsigned char dat)
{
	char i=0;
	volatile unsigned buf;
	volatile unsigned char SPI_adr, SPI_data;
	SPI_adr =addr;
	SPI_data =dat;

	Spi_CS_Low(id);
	SSCI2BUFR=SPI_adr; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;

	SSCI2BUFR=SPI_data; //将待发送的字节放入发送缓存中
	while(!SSCI2IF); //等待发送完毕后SSCIIF置位，
	SSCI2IF=0;
	buf =SSCI2BUFR;
	Spi_CS_High(id);
}
void IS31FL3265B_Init(void)
{
	spi_init();
	SPI_Write_2Byte(1,0x00,0x01);
	SPI_Write_2Byte(2,0x00,0x01);
}
