/*
 * KF8_Type_Define.h
 *
 *  Created on: 2019-2-22
 *      Author: admin
 */

#ifndef KF8_TYPE_DEFINE_H_
#define KF8_TYPE_DEFINE_H_

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef		signed  char  		int8;
typedef		signed  short  		int16;
typedef		signed  long 		int32;

typedef 	unsigned  char 		uint8;
typedef 	unsigned  char 		uchar;
typedef 	unsigned  short  	uint16;
typedef 	unsigned  long 		uint32;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}Boolean;

typedef union
{
	struct
	{
			unsigned char byte0;
			unsigned char byte1;
			unsigned char byte2;
			unsigned char byte3;
	};
	unsigned char 	bytes[4];
	unsigned long	value;
}s_uint32;

typedef union
{
	struct
	{
		unsigned char byte0;
		unsigned char byte1;
	};
	unsigned char 	byte[2];
	unsigned short 	value;
}s_uint16;

typedef union
{
	unsigned char 	value;
	struct
	{
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
	};
}s_uint8;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define 	DATAEEPROM_BUFFER_SIZE			16
typedef union
{
	struct  // 自定义协议结构体
	{
			unsigned char byte0;
			unsigned char byte1;
			unsigned char byte2;
			unsigned char byte3;

	};
	unsigned char bytes[DATAEEPROM_BUFFER_SIZE];
}s_Dataeeprom_Buffer;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define 	DATAFLASH_BUFFER_BYTE_SIZE			32  // 注：必须满足Flash自写块特性

//  因为工具的联合体不支持赋初值，建立支持初值的结构体
typedef 	struct  // 自定义协议结构体
{
			uint8 id;
			uint8 type;
			uint8 product[6];
			uint8 index[5];
			uint8 reservation[DATAFLASH_BUFFER_BYTE_SIZE-13];  // 前面占用字节数参与，如这里的13
}s_Dataflash_ConstBuffer;
//  并 根据需要建立flash自写应用的常量到变量的转换需要的联合体
typedef union
{
	unsigned char bytes[DATAFLASH_BUFFER_BYTE_SIZE];   // 无协议结构下的纯数组大小缓存
	struct  // 自定义协议结构体 服务  const对象
	{
				uint8 id;
				uint8 type;
				uint8 product[6];
				uint8 index[5];
				uint8 reservation[DATAFLASH_BUFFER_BYTE_SIZE-13];  // 前面占用字节数参与，如这里的13
	};
}s_Dataeeprom_RAMBuffer;        // 与 const绑定的 读写样例支持,数量类型提示，仍按字节赋值，高位留空即实现原始读取Flash的高位CRET的0xB0占位

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define 	DATAI2C_BUFFER_BYTE_SIZE			10
typedef union
{
	unsigned char bytes[DATAI2C_BUFFER_BYTE_SIZE+5];   // 无协议结构下的纯数组大小缓存
	struct  // 自定义协议结构体 服务  const对象
	{
				uint8 i2cDevAddrL;  // 7位地址或10位地址的低
				uint8 i2cDevAddrH;  // 10地址高
				s_uint8 flag;		//  基于工作条件的标志
				uint8 length;		//  基于工作条件的标志
				uint8 Command;	 	// I2C 的地址资源   或命令字
				uint8 buffer[DATAI2C_BUFFER_BYTE_SIZE];  // 读入数据区或写出数据
	};
}s_I2C_RAMBuffer;

#define 	DATASPI_BUFFER_BYTE_SIZE			10
typedef union
{
	unsigned char bytes[6+DATASPI_BUFFER_BYTE_SIZE];   // 无协议结构下的纯数组大小缓存
	struct  // 自定义协议结构体 服务  const对象
	{
				uint8 head;  		//
				uint8 Command;  	//
				s_uint8 flag;		//  基于工作条件的标志
				uint8 length;		//  数据有效长度
				uint8 buffer[DATASPI_BUFFER_BYTE_SIZE];  // 读入数据区或写出数据
				uint8 checkvalue;  // 数据校验和
				uint8 assistant;
	};
}s_SPI_RAMBuffer;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif /* KF8_TYPE_DEFINE_H_ */
