/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_SYN_H__
#define __MERCURY_SYN_H__

#include "MercuryDef.h"
#include "MercuryThread.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _RTL_CRITICAL_SECTION {
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
} CRITICAL_SECTION, *LPCRITICAL_SECTION;

/*
lpEventAttributes:Ignored. Must be NULL.
bManualReset:
           true --you must use the ResetEvent function to manually reset the state to nonsignaled
           false--the system automatically resets the state to nonsignaled after a single waiting thread has been released
InitialState:TRUE the initial state is signaled; otherwise, it is nonsignaled
lpName:
*/
extern HANDLE CreateEvent( LPSECURITY_ATTRIBUTES lpEventAttributes,
                                            BOOL bManualReset,
                                            BOOL InitialState,
                                            LPTSTR lpName);
extern HANDLE OpenEvent(DWORD dwDesiredAccess,BOOL bInheritHandle, LPCTSTR lpName);
/*
BOOL return 0  success
     return 1  faile   use GetLastError to catch the error num
*/
extern BOOL PulseEvent(HANDLE hEvent);
/*
BOOL return 0  success
     return 1  faile   use GetLastError to catch the error num
*/
extern BOOL ResetEvent(HANDLE hEvent);
/*
BOOL return 0  success
     return 1  faile   use GetLastError to catch the error num
*/
extern BOOL SetEvent(HANDLE hEvent);

extern DWORD WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds);
/*
非空的lpCriticalSection
请将内容初始化为0
*/
extern void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
/*
lpCriticalSection必须被InitializeCriticalSection过
*/
extern void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
/*
lpCriticalSection必须被InitializeCriticalSection过
*/
extern void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
/*
lpCriticalSection必须被InitializeCriticalSection过
*/
extern void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__MERCURY_SYN_H__
