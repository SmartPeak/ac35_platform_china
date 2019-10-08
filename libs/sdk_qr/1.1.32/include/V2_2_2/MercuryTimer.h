/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_TIMER_H__
#define __MERCURY_TIMER_H__

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_NO_ACTIVATE               0
#define TIMER_AUTO_ACTIVATE           1

#define TIMER_ONCE_TIME                   0
#define TIMER_PERIOD                          1

typedef VOID   (*TIMER_FUN)(ULONG);

typedef struct
{
    const char* timer_name;
    TIMER_FUN timer_fun;
    ULONG input;
    ULONG timer_expire;
    ULONG auto_activate;
    ULONG period;
}TIMER_CONFIG_S;

typedef struct _SYSTEMTIME {
  WORD wYear; //2000 ~ 2049
  WORD wMonth; //1-12
  WORD wDayOfWeek;//0-6
  WORD wDay;//1-31
  WORD wHour;//0-23
  WORD wMinute;//0-59
  WORD wSecond;//0-59
  WORD wMilliseconds;//0-999
}SYSTEMTIME;

TIMER_PTR  CreateTimer(TIMER_CONFIG_S* cfg);
INT ChangeTimer(TIMER_PTR timer_ptr,TIMER_FUN timer_fun,ULONG timer_expire);
INT ActiveTimer(TIMER_PTR timer_ptr);
INT DeactiveTimer(TIMER_PTR timer_ptr);
INT IsTimerActive(TIMER_PTR timer_ptr);
INT DeleteTimer(TIMER_PTR timer_ptr);
INT GetCurrentTime(ULONG* time);
INT GetTickCount(ULONG* tick);

int SetLocalTime(const SYSTEMTIME* lpSystemTime);
void GetLocalTime(SYSTEMTIME* lpSystemTime);









#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif //__MERCURY_TIMER_H__
