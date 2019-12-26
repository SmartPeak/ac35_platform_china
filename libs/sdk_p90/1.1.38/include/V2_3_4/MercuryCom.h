/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/

#ifndef __MERCURY_UART_H__
#define __MERCURY_UART_H__
#include "MercuryDef.h"

typedef enum
{
    COM_ID0 = 0,
    COM_ID1,
    COM_ID_MAX,
    MERCURY_ENUM_COMID_MAX = 0x7fffffff
}COM_ID_E;

#define    DISABLE_PARITY      0
#define    EVEN_PARITY            1
#define    ODD_PARITY              2

#define     DEFAULT_BITS      0   // default is 8bit
#define     FIVE_BITS             1
#define     SIX_BITS               2
#define     SEVEN_BITS           3
#define     EIGHT_BITS           4

#define     DEFAULT_STOP_BIT   0   // 1BIT

#define     NO_FLOW_CONTROL      0
#define     HW_FLOW_CONTROL     1
#define     SW_FLOW_CONTROL     2

typedef struct
{
    ULONG  baud_rate;
    BYTE   parity;
    BYTE   stop_bits;      //stop bits : 1bit,  can not modify
    BYTE   byte_size;
    BYTE   flow_control;
} COM_CONFIG_T;

#define BAUD_1200               0x2A50
#define BAUD_2400               0x1528
#define BAUD_4800               0x0A94
#define BAUD_9600               0x054A
#define BAUD_19200              0x02A5
#define BAUD_38400              0x0152
#define BAUD_57600              0x00E2
#define BAUD_74800               0x00AE
#define BAUD_115200             0x0071
#define BAUD_230400             0x0038
#define BAUD_460800             0x001C
#define BAUD_500000             0x001A
#define BAUD_921600             0x000E
#define BAUD_1000000            0x000D
#define BAUD_1625000            0x8
#define BAUD_3250000            0x4

#define FASTBOOT_RUNNING    0
#define FASTBOOT_STOP           1

extern INT COM_Init(ULONG id, COM_CONFIG_T* cfg);
extern INT COM_Deinit(ULONG id);
extern INT COM_Config(ULONG id, COM_CONFIG_T* cfg);
extern INT COM_Read(ULONG id,BYTE* pTargetBuffer,ULONG BufferLength,ULONG* pBytesRead,ULONG timeout);
extern INT COM_Write(ULONG id,BYTE* pSourceBytes,ULONG NumberOfBytes );

extern INT MercuryFastbootStateSet(uint32 state);
extern uint32 MercuryFastbootStateGet(void);
extern uint32 MercuryUsbRead(const uint8 *buffer,uint32 length);
extern uint32 MercuryUsbWrite(const uint8 *buffer,uint32 length);

#endif  //__MERCURY_UART_H__
