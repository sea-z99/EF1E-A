/*
 * SoftSpi.h
 *
 *  Created on: 2020-10-6
 *      Author: Rick
 */

#ifndef SOFTSPI_H_
#define SOFTSPI_H_

void Spi_CS_High(char id);
void Spi_CS_Low(char id);

void Spi_Init(void);
int Spi_Read(unsigned char addr);
void SPI_Write_2Byte(unsigned char id,unsigned char addr,unsigned char dat);
void IS31FL3265B_Init(void);

void Tail_One_Init(void);
void Tail_Two_Init(void);
void Rt_One_Init(void);
void Rt_Two_Init(void);

void Tail_One_Work(void);
void Tail_Two_Work(void);
void Rt_One_Work(void);
void Rt_Two_Work(void);
#endif /* SOFTSPI_H_ */
