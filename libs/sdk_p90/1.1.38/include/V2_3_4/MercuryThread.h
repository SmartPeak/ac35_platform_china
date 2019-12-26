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
    CreateThread ��fdwCreateȡֵ
    fdwCreate = CREATE_SUSPENDED  ----- �̴߳������Զ����У�cbStack����ֵ��Ч��ʹ��Ĭ��ջ��С(8KB)��
    fdwCreate = STACK_SIZE_RESERVATION  ----- �̴߳������Զ����У�cbStack����ֵ��Ч
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
cbStack:��ջ��С�����fdwCreateʹ�ã�NULLʹ��Ĭ��ֵ
lpStartAddr:��ں���
lpvThreadParam:��ں�������
fdwCreate:CREATE_SUSPENDED   STACK_SIZE_PARAM_IS_A_RESERVATION
lpIDThread:�����߳�ID
*/
extern HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpsa,DWORD cbStack,
                                             LPTHREAD_START_ROUTINE lpStartAddr,ULONG argc,LPVOID lpvThreadParam,
                                             DWORD fdwCreate,LPDWORD lpIDThread);
/*
 dwExitCode: null
*/
extern VOID ExitThread(DWORD dwExitCode);
 /*
 �����߳�ID
*/
extern HANDLE GetCurrentThread(void);
  /*
 �����߳�ID
*/
extern DWORD GetCurrentThreadId(void);
  /*
�����߳����ȼ�
*/
extern int GetThreadPriority(HANDLE hThread);

extern DWORD ResumeThread(HANDLE hThread);
/*
�����߳����ȼ�
�˹��ܲ��ṩ
*/
extern BOOL SetThreadPriority(HANDLE hThread,int nPriority);
/*
��λms
*/
extern void Sleep(DWORD dwMilliseconds);
extern DWORD SuspendThread(HANDLE hThread);
extern BOOL TerminateThread(HANDLE hThread,DWORD dwExitCode);

/**************************************************************************************
�ӵ�ǰ�߳����߳�threadID����msg
msg �� threadID ������Ч
**************************************************************************************/
extern int MercurySendMessage(MERCURY_MESSAGE_S* msg, HANDLE threadID);
/**************************************************************************************
�����߳�threadID��msg
�ýӿ�Ϊ����ʽ�ӿڣ����øýӿں�
���threadID����msg����������
���threadID������msg�������ǰ�߳�ֱ��threadID�յ�msg��
**************************************************************************************/
extern int MercuryGetMessage(MERCURY_MESSAGE_S** msg, HANDLE threadID);
/**************************************************************************************
�����߳�threadID��msg
�ýӿ�Ϊ������ʽ�ӿڣ����øýӿں������߳�threadID�Ƿ����msg����������
���threadID����msg�򷵻سɹ�0 �� msg
���threadID������msg���򷵻�-1��msg��������
**************************************************************************************/
extern int MercuryPeekMessage(MERCURY_MESSAGE_S** msg,HANDLE threadID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__MERCURY_THREAD_H__
