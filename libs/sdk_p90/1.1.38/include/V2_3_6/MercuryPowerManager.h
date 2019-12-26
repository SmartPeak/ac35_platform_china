/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_POWER_MANAGER_H_
#define _MERCURY_POWER_MANAGER_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef enum _wakelockmodes {
    LOCK_SCREEN=0,
    LOCK_SLEEP,
    LOCK_NONE,
    MERCURY_ENUM_WAKE_MAX = 0x7fffffff
} WAKE_LOCK_MODES;

typedef enum
{
    ADC_ID_0 = 0,
    ADC_ID_1 = 1,
    ADC_ID_MAX,
    MERCURY_ENUM_ADCID_MAX = 0x7fffffff
} ADC_ID_E;

typedef enum
{
    ADC_SCALE_12BIT_3V = 0,
    ADC_SCALE_12BIT_1V2,
    ADC_SCALE_MAX,
    MERCURY_ENUM_ADCSCALE_MAX = 0x7fffffff
}ADC_SCALE_E;

typedef enum
{
    DEFAULT_AUTO = 0,
    MANUAL_SWITCH_ON,
    MANUAL_SWITCH_OFF,
    MANUAL_SWITCH_MAX
}SWITCH_STATE_E;


typedef enum
{
    CHGMNG_ADP_UNKNOW,
    CHGMNG_ADP_STANDARD,
    CHGMNG_ADP_NONSTANDARD,
    CHGMNG_ADP_USB,
}ADAPTER_TYPE_E;


 
int  WakeLock(WAKE_LOCK_MODES LockMode, const BYTE *LockName);
int  WakeUnlock(WAKE_LOCK_MODES LockMode, const BYTE *LockName);
int  PowerOff(void);
int  PowerReboot(void);
uint32 Power_GetVoltagetoPercent(void);
void SetChgOverHighTemp(uint16 highTemp);
void SetChgOverLowTemp(uint16 lowTemp);
void SetRechgVol(uint16 rechgVol);
void SetChgEndVol(uint16 chg_end_vol);
int SetChgSwtich(SWITCH_STATE_E chgSwitch);
int SetAutoIdentAdp(BOOLEAN autoIdentity);
int GetAdpType(void);
int ADC_GetResult(ADC_ID_E adcID, ADC_SCALE_E adcScale);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MERCURY_POWER_MANAGER_H_

