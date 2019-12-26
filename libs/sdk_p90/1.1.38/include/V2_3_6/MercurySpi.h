/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_SPI_H__
#define __MERCURY_SPI_H__

#include "MercuryDef.h"

#define DMA_ENABLE   1
#define DMA_DISABLE  0

typedef enum
{
    SPI_GROUP0_LOGIC_0 = 0,
    SPI_GROUP0_LOGIC_1 = 1,
    SPI_GROUP0_LOGIC_2 = 2,
    SPI_GROUP0_LOGIC_3 = 3,
    SPI_GROUP0_LOGIC_4 = 4,
    SPI_GROUP0_LOGIC_5 = 5,
    SPI_GROUP0_LOGIC_MAX,
    MERCURY_ENUM_SPIID_MAX = 0x7fffffff
}MC_SPI_ID_E;

/*spi mode*/
typedef enum
{
    CPOL0_CPHA0 = 0,    //sampling on rising edge, clk idle '0'
    CPOL0_CPHA1,        //sampling on falling edge, clk idle '0'
    CPOL1_CPHA0,        //sampling on falling edge, clk idle '1'
    CPOL1_CPHA1,         //sampling on rising edge, clk idle '1'
    MERCURY_ENUM_SPIMODE_MAX = 0x7fffffff
}SPI_MODE_E;

typedef struct
{
    char openFlag;
    SPI_MODE_E mode;
    uint32 tx_bit_length;
    uint32 freq;
}SPI_CONFIG_S;

typedef struct
{
    int enable;
    int logic_gpio[SPI_GROUP0_LOGIC_MAX]; // 对应logic id 0 ~ 5
}SPI_CS_CFG_S;

/*
CS默认使用的是38decode逻辑

enable 0 使用38decode逻辑,
         logic0_gpio ~ logic5_gpio 无用

enable 1 使用客户配置的gpio
         logic0_gpio ~ logic5_gpio 分别为逻辑通道0 到 通道5的cs gpio引脚
         无用的logic id请配置为-1
注意:
配置前，app需要将将要配置cs引脚的pinmap做相应配置(配置为gpio out模式)
配置完成后，底层会根据配置来操作对应的cs，app层不需要也不能操作cs引脚。
SPI_CsCfg 需要在SPI_Init之前调用
*/
extern int  SPI_CsCfg(SPI_CS_CFG_S* pCsCfg);
extern INT SPI_Init(ULONG id, SPI_CONFIG_S* cfg);
extern INT SPI_Deinit(ULONG id);
extern INT SPI_Config(ULONG id, SPI_CONFIG_S* cfg);
extern INT SPI_Read(ULONG id,BYTE* pTargetBuffer,ULONG BufferLength,char* cmd,ULONG cmdLen);
extern INT SPI_Write(ULONG id,BYTE* pSourceBytes,ULONG NumberOfBytes );

/*
#define DMA_ENABLE   1
#define DMA_DISABLE  0
注意-请再spi init之前做DMA使能或关闭，默认为关闭状态
logid 0-5 只能使用同一个dma模式。
*/
extern INT SPI_DmaStateSet(uint32 enable);
extern INT SPI_DmaStateGet(void);
#endif //__MERCURY_SPI_H__
