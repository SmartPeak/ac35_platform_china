/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_BATTERY_H_
#define _MERCURY_BATTERY_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _BATTERY_FLAG{     
    BATTERY_FLAG_NORMAL,
    BATTERY_FLAG_HIGH,      
    BATTERY_FLAG_LOW,    
    BATTERY_FLAG_CRITICAL, 
    BATTERY_FLAG_CHARGING,       
    BATTERY_FLAG_UNKNOWN,    
    MERCURY_ENUM_BATTERY_MAX = 0x7fffffff
} BATTERY_FLAG;

typedef struct _SYSTEM_POWER_STATUS_EX2 {
  BYTE ACLineStatus;
  BYTE BatteryFlag;
  BYTE BatteryLifePercent;
  BYTE BatteryIsExist;
  DWORD BatteryLifeTime;
  DWORD BatteryFullLifeTime;
  BYTE Reserved2;
  BYTE BackupBatteryFlag;
  BYTE BackupBatteryLifePercent;
  BYTE Reserved3;
  DWORD BackupBatteryLifeTime;
  DWORD BackupBatteryFullLifeTime;
  DWORD BatteryVoltage;
  DWORD BatteryCurrent;
  DWORD BatteryAverageCurrent;
  DWORD BatteryAverageInterval;
  DWORD BatterymAHourConsumed;
  DWORD BatteryTemperature;
  DWORD BackupBatteryVoltage;
  BYTE BatteryChemistry;
  //  Add any extra information after the BatteryChemistry member.
} SYSTEM_POWER_STATUS_EX2, *PSYSTEM_POWER_STATUS_EX2, *LPSYSTEM_POWER_STATUS_EX2;

INT BatteryGetStatus(LPSYSTEM_POWER_STATUS_EX2 pstatus, PBOOL pfBatteriesChangedSinceLastCall);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MERCURY_BATTERY_H_

