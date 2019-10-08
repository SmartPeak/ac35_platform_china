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
    int logic_gpio[SPI_GROUP0_LOGIC_MAX]; // ��Ӧlogic id 0 ~ 5
}SPI_CS_CFG_S;

/*
CSĬ��ʹ�õ���38decode�߼�

enable 0 ʹ��38decode�߼�,
         logic0_gpio ~ logic5_gpio ����

enable 1 ʹ�ÿͻ����õ�gpio
         logic0_gpio ~ logic5_gpio �ֱ�Ϊ�߼�ͨ��0 �� ͨ��5��cs gpio����
         ���õ�logic id������Ϊ-1
ע��:
����ǰ��app��Ҫ����Ҫ����cs���ŵ�pinmap����Ӧ����(����Ϊgpio outģʽ)
������ɺ󣬵ײ�����������������Ӧ��cs��app�㲻��ҪҲ���ܲ���cs���š�
SPI_CsCfg ��Ҫ��SPI_Init֮ǰ����
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
ע��-����spi init֮ǰ��DMAʹ�ܻ�رգ�Ĭ��Ϊ�ر�״̬
logid 0-5 ֻ��ʹ��ͬһ��dmaģʽ��
*/
extern INT SPI_DmaStateSet(uint32 enable);
extern INT SPI_DmaStateGet(void);
#endif //__MERCURY_SPI_H__
