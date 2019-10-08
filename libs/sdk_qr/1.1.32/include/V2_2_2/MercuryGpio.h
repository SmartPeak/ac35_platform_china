/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_GPIO_H__
#define __MERCURY_GPIO_H__
#include "MercuryDef.h"

typedef void (*InterruptCallback)(void);

typedef enum
{
    OUTPUT,
    INPUT,
    INVALID_DIR,
    MERCURY_ENUM_DIR_MAX = 0x7fffffff
} MERCURY_DIR_E;

typedef enum
{
    LEVEL,
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGE,
    NO_INT,
    INVALID_INT,
    MERCURY_ENUM_INTERTUPT_MAX = 0x7fffffff
} MERCURY_INTERTUPT_MODE_E;

typedef struct
{
    uint16   default_val;
    MERCURY_DIR_E dir;
    MERCURY_INTERTUPT_MODE_E  int_sense;
    InterruptCallback  fun;
} MERCURY_GPIO_CFG_S;

extern DWORD GIO_Init(void);
extern BOOL GIO_Deinit(void);
extern VOID GIO_SetBit(DWORD id);
extern VOID GIO_ClrBit(DWORD id);
extern DWORD GIO_GetBit(DWORD id);
extern VOID GIO_SetMode(DWORD id, MERCURY_GPIO_CFG_S* pCfg);
extern void GIO_TestMode(uint32 enable);

#endif //__MERCURY_GPIO_H__
