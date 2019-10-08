/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_NLED_H_
#define _MERCURY_NLED_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum NLED_ID_E_TAG
{
    LED_1,
    LED_2,
    LED_MAX_NUM,
    MERCURY_ENUM_NLEDID_MAX = 0x7fffffff
}NLED_ID_E;

typedef enum NLED_MODE_E_TAG
{
    NLED_MODE_OFF,
    NLED_MODE_ON,
    NLED_MODE_BLINK,
    NLED_MODE_MAX,
    MERCURY_ENUM_NLEDMODE_MAX = 0x7fffffff
}NLED_MODE_E;


INT NLedInit(NLED_ID_E LedID);

INT NLedDeinit(NLED_ID_E LedID);

INT NLedSetMode(
NLED_ID_E LedID,
INT OffOnBlink, 
LONG TotalCycleTime, 
LONG OnTime, 
LONG OffTime,
INT MetaCycleOn, 
INT MetaCycleOff
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MERCURY_NLED_H_

