/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_THREAD_H__
#define __MERCURY_THREAD_H__

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    CreateThread 中fdwCreate取值
    fdwCreate = CREATE_SUSPENDED  ----- 线程创建后不自动运行，cbStack参数值无效，使用默认栈大小(8KB)。
    fdwCreate = STACK_SIZE_RESERVATION  ----- 线程创建后自动运行，cbStack参数值有效
*/
#define CREATE_SUSPENDED             4
#define STACK_SIZE_RESERVATION  0x1000

typedef VOID (*LPTHREAD_START_ROUTINE) (ULONG argc,LPVOID lpThreadParameter);

typedef struct
{
    unsigned short MessageID;
    unsigned int dataLen;
    void* pdata;
}MERCURY_MESSAGE_S;

/*
lpsa: NULL
cbStack:堆栈大小，配合fdwCreate使用，NULL使用默认值
lpStartAddr:入口函数
lpvThreadParam:入口函数参数
fdwCreate:CREATE_SUSPENDED   STACK_SIZE_PARAM_IS_A_RESERVATION
lpIDThread:返回线程ID
*/
extern HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpsa,DWORD cbStack,
                                             LPTHREAD_START_ROUTINE lpStartAddr,ULONG argc,LPVOID lpvThreadParam,
                                             DWORD fdwCreate,LPDWORD lpIDThread);
/*
 dwExitCode: null
*/
extern VOID ExitThread(DWORD dwExitCode);
 /*
 返回线程ID
*/
extern HANDLE GetCurrentThread(void);
  /*
 返回线程ID
*/
extern DWORD GetCurrentThreadId(void);
  /*
返回线程优先级
*/
extern int GetThreadPriority(HANDLE hThread);

extern DWORD ResumeThread(HANDLE hThread);
/*
设置线程优先级
此功能不提供
*/
extern BOOL SetThreadPriority(HANDLE hThread,int nPriority);
/*
单位ms
*/
extern void Sleep(DWORD dwMilliseconds);
extern DWORD SuspendThread(HANDLE hThread);
extern BOOL TerminateThread(HANDLE hThread,DWORD dwExitCode);

/**************************************************************************************
从当前线程往线程threadID发送msg
msg 和 threadID 必须有效
**************************************************************************************/
extern int MercurySendMessage(MERCURY_MESSAGE_S* msg, HANDLE threadID);
/**************************************************************************************
接收线程threadID的msg
该接口为阻塞式接口，调用该接口后，
如果threadID存在msg则立即返回
如果threadID不存在msg，则挂起当前线程直至threadID收到msg。
**************************************************************************************/
extern int MercuryGetMessage(MERCURY_MESSAGE_S** msg, HANDLE threadID);
/**************************************************************************************
接收线程threadID的msg
该接口为非阻塞式接口，调用该接口后，无论线程threadID是否存在msg都立即返回
如果threadID存在msg则返回成功0 和 msg
如果threadID不存在msg，则返回-1，msg不做操作
**************************************************************************************/
extern int MercuryPeekMessage(MERCURY_MESSAGE_S** msg,HANDLE threadID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__MERCURY_THREAD_H__
