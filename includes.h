/****************************************************************************************

 ****************************************************************************************/
#ifndef  INCLUDES_H_
#define  INCLUDES_H_


#include "KF8_Type_Define.h"

/*SYSCLK系统频率控制寄存器:SCLKCTL --------------------------------------------------------*/
#define SYSYCLK_SEL_SCKS						(0x40) /*!< 0B0100 0000 SCK选择时钟*/
#define SYSYCLK_SEL_FOSC0						(0x00) /*!< 0B0000 0000   配置字选择时钟*/
/*时钟频率选择位SCLKCTL :SCLKDIV<2:0>--------------------------------------------------------*/
#define	SYSCLK_FREQ_DIV1						(0x38) /*!< 0B0011 1000 1:1分频*/
#define	SYSCLK_FREQ_DIV2						(0x30) /*!< 0B0011 0000 1:2分频*/
#define	SYSCLK_FREQ_DIV4						(0x28) /*!< 0B0010 1000 1:4分频*/
#define	SYSCLK_FREQ_DIV8						(0x20) /*!< 0B0010 0000 1:8分频*/
#define	SYSCLK_FREQ_DIV16						(0x18) /*!< 0B0001 1000 1:16分频*/
#define	SYSCLK_FREQ_DIV32						(0x10) /*!< 0B0001 0000 1:32分频*/
#define	SYSCLK_FREQ_DIV64						(0x08) /*!< 0B0000 1000 1:64分频*/
#define	SYSCLK_FREQ_DIV128						(0x00) /*!< 0B0000 0000 1:128分频*/

/*系统时钟源选择位SCLKCTL :SCKS<2:0>--------------------------------------------------------*/
#define	SYSCLK_SCLK_SEL_UPCK					(0x04) /*!< 0B00000100 系统时钟源选择UPCK*/
#define	SYSCLK_SCLK_SEL_INTHF					(0x00) /*!< 0B00000000 系统时钟源选择内部高频时钟*/
#define	SYSCLK_SCLK_SEL_INTLF					(0x01) /*!< 0B00000001 系统时钟源选择内部低频时钟*/
#define	SYSCLK_SCLK_SEL_EXTLF					(0x03) /*!< 0B00000011 系统时钟源选择外部低频时钟*/
#define	SYSCLK_SCLK_SEL_EXTHF					(0x02) /*!< 0B00000010 系统时钟源选择外部高频时钟*/

/*PLLCKS时钟选择位 	--------------------------------------------------------*/
#define	PLL_SEL_EXTHF							(0x01)
#define	PLL_SEL_INTHF							(0x00)
/*PCKHALF时钟预分频选择位 	--------------------------------------------------------*/
#define	PLL_SEL_DIV1							(0x00)
#define	PLL_SEL_DIV2							(0x80)
/*PLLCTL时钟倍频选择 	--------------------------------------------------------*/
#define PLLBIAS_CUR_MAX                         (0x70) /*!< 0B01110000 PLL偏置电流最大*/
#define PLLBIAS_CUR_MIN                         (0x00) /*!< 0B01110000 PLL偏置电流最小*/
#define PLLPMUL_2                               (0x00) /*!< 0B00000000 PLL选择2倍频*/
#define PLLPMUL_3                               (0x04) /*!< 0B00000100 PLL选择3倍频*/
#define PLLPMUL_4                               (0x08) /*!< 0B00001000 PLL选择4倍频*/
#define PLLPMUL_6                               (0x0C) /*!< 0B00001100 PLL选择6倍频*/

#define uint8_t		unsigned char
#define uint16_t	unsigned short
#define uint32_t	unsigned int
#define uint64_t	unsigned long

#ifndef __cplusplus

#define bool uint8_t

#define true 1

#define false 0
#endif
#endif
