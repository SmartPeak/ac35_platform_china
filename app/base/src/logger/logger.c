//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     logger.c
/// @brief    LOG�ӿڷ�װ
/// @author   Cedar.Diao
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     01/28/2018
//////////////////////////////////////////////////////////////////////////////
#include "MercurySystem.h"
#include "bwsdk_api.h"
#include "logger.h"

#ifdef LOG_DISABLE
// LOG�رպ�˽ӿڲ�ʵ��

#else

// ����˺����ʱ���Ϊ�������
//#define LOG_MS_TIMESTAMP
// ����˺����ʱ���ΪDateTime��Ms
#define LOG_DT_MS_TIMESTAMP
// ����˺�ʱ���ʱ���ΪDateTime
//#define LOG_DT_TIMESTAMP


// ����˺꽫ʹlog��USB��DIAG�����
//#define LOG_OUTPUT_TO_USB_DIAG

// ����˺꽫ʹlog��USB��AT�����
// ע��:
//  1.���û��SDM����, LOGռ��AT�ں󣬻ᵼ��fastboot�޷�����ʹ��,����AutoRunApp
//  2.�����SDM������AT��ӡLOG��Ӱ������, ��SDM����Ӧ����, ���ʱLOG�������.
#define LOG_OUTPUT_TO_USB_AT

// ����˺꽫ʹlog��UART1���
//#define LOG_SERIAL_PORT   1


//����˺꽫log�Ȼ�����RAM��,��ͨ���߳����
#define LOG_OUTPUT_BY_THREAD


#if defined(LOG_MS_TIMESTAMP)
#define LOGGER_NONE_FORMAT "%07d %c/%s: "
#elif defined (LOG_DT_MS_TIMESTAMP)
#define LOGGER_NONE_FORMAT "%02d-%02d %02d:%02d:%02d.%03d %c/%s: "
#else
#define LOGGER_NONE_FORMAT "%04d-%02d-%02d %02d:%02d:%02d %c/%s: "
#endif

// ������ӡLOG��Ҫ����ʱ
#define LOG_DELAY_MS 0

// LOG�����С
#define LOG_BUFF_SIZE 1024

// log����
static char log_buf[LOG_BUFF_SIZE];
static unsigned char gucLoggerInit = 0;
static CRITICAL_SECTION log_section;

#ifdef LOG_OUTPUT_TO_USB_AT
#define LOGGER_TO_AT_WAIT_MS    10000
TIMER_PTR hLogWaitTmr = NULL;
unsigned char gucLogToAtEn = 1;

static void LogWaitTimerCb(ULONG param)
{
    gucLogToAtEn = 1;
}

void LogToATPortEnable(int en)
{
    if (en != 0) {
        if (hLogWaitTmr != NULL) {
            if (IsTimerActive(hLogWaitTmr)) {
                DeactiveTimer(hLogWaitTmr);
            }
            ChangeTimer(hLogWaitTmr, LogWaitTimerCb, LOGGER_TO_AT_WAIT_MS);
            ActiveTimer(hLogWaitTmr);
        }
    } else {
        gucLogToAtEn = 0;
    }
}
#else
void LogToATPortEnable(int en)
{
    (void) en;
}
#endif


#ifdef LOG_OUTPUT_BY_THREAD
#define LOG_CACHE_SIZE          0x1000
#define LOG_CACHE_MASK          0x0FFF
static unsigned char gaucLogCache[LOG_CACHE_SIZE];
static unsigned int guiLogIn = 0;
static unsigned int guiLogOut = 0;
static HANDLE hLogThread;

static VOID LogThreadHandler(ULONG argc, LPVOID lpThreadParameter)
{
    unsigned int uiAvai;

    while (1) {
        if (guiLogIn == guiLogOut) {
            Sleep(5);
        } else {
            if (guiLogOut > guiLogIn) {
                uiAvai = (LOG_CACHE_SIZE - guiLogOut);
#if defined(LOG_SERIAL_PORT)
                COM_Write(LOG_SERIAL_PORT, &gaucLogCache[guiLogOut], uiAvai);
#elif defined(LOG_OUTPUT_TO_USB_AT)
                if (gucLogToAtEn == 1) {
                    USBATSend(&gaucLogCache[guiLogOut], uiAvai);
                }
#elif defined(LOG_OUTPUT_TO_USB_DIAG)
                MercuryDebug(&gaucLogCache[guiLogOut], uiAvai);
#else

#endif
                guiLogOut += uiAvai;
                guiLogOut &= LOG_CACHE_MASK;
            }
            uiAvai = (guiLogIn - guiLogOut);
#if defined(LOG_SERIAL_PORT)
            COM_Write(LOG_SERIAL_PORT, &gaucLogCache[guiLogOut], uiAvai);
#elif defined(LOG_OUTPUT_TO_USB_AT)
            if (gucLogToAtEn == 1) {
                USBATSend(&gaucLogCache[guiLogOut], uiAvai);
            }
#elif defined(LOG_OUTPUT_TO_USB_DIAG)
            MercuryDebug(&gaucLogCache[guiLogOut], uiAvai);
#else

#endif
            guiLogOut += uiAvai;
            guiLogOut &= LOG_CACHE_MASK;
        }
    }
}

int LogToBuffer(unsigned char *sendBuf, int bufLen)
{
    unsigned int uiAvai;

    do {
        uiAvai = ((LOG_CACHE_SIZE + guiLogOut - guiLogIn - 1) & LOG_CACHE_MASK);
        if (uiAvai >= bufLen) {
            break;
        } else {
            Sleep(20);
        }
    } while (1);


    uiAvai = 0;
    if (guiLogIn >= guiLogOut) {
        uiAvai = (LOG_CACHE_SIZE - guiLogIn);
        if (uiAvai > bufLen) {
            uiAvai = bufLen;
        }
        memcpy(&gaucLogCache[guiLogIn], sendBuf, uiAvai);
        guiLogIn += uiAvai;
        guiLogIn &= LOG_CACHE_MASK;
        bufLen -= uiAvai;
    }
    memcpy(&gaucLogCache[guiLogIn], &sendBuf[uiAvai], bufLen);
    guiLogIn += bufLen;
    guiLogIn &= LOG_CACHE_MASK;

    return 0;
}

#endif

static void LogComInit(void)
{
    if (gucLoggerInit == 0) {
#if defined(LOG_SERIAL_PORT)
        COM_CONFIG_T cfg = {BAUD_115200, DISABLE_PARITY, 0, 0, 0};
        COM_Init(LOG_SERIAL_PORT, &cfg);
#elif defined(LOG_OUTPUT_TO_USB_AT)
        if (hLogWaitTmr == NULL) {
            TIMER_CONFIG_S stTmrCfg = {"WtLogTmr", LogWaitTimerCb, NULL, LOGGER_TO_AT_WAIT_MS, 0, 0};
            hLogWaitTmr = CreateTimer(&stTmrCfg);
        }
        USBAT_Init();
#else

#endif

#ifdef LOG_OUTPUT_BY_THREAD
        if (hLogThread == NULL) {
            guiLogIn = 0;
            guiLogOut = 0;
            hLogThread = CreateThread(NULL, 
                                     1024,
                                     LogThreadHandler,
                                     0,
                                     NULL,
                                     STACK_SIZE_RESERVATION,
                                     NULL);
            if (hLogThread != NULL) {
                InitializeCriticalSection(&log_section);
                SetThreadPriority(hLogThread, 250);
            }
        }
#else

#endif
        gucLoggerInit = 1;
    }
}

/**
 * @brief �����������������LOG�˿�
 * @param sendBuf [in] Ҫ���������
 * @param bufLen [in] Ҫ������ֽ���
 * @retval ����ֵ������
 */
int LogComSend(unsigned char *sendBuf, int bufLen)
{

#if defined(LOG_OUTPUT_BY_THREAD)
    LogToBuffer(sendBuf, bufLen);
#else
#if defined(LOG_SERIAL_PORT)
    COM_Write(LOG_SERIAL_PORT, sendBuf, bufLen);
#elif defined(LOG_OUTPUT_TO_USB_AT)
    if (gucLogToAtEn == 1) {
        USBATSend(sendBuf, bufLen);
    }
#elif defined(LOG_OUTPUT_TO_USB_DIAG)
    MercuryDebug(sendBuf, bufLen);
#else

#endif
#endif
    return 0;
}

void logger_print_serial_fmt(const char *tag, char level_char, const char *fmt, ...)
{
    SYSTEMTIME tst;
    int i = 0;
    va_list args;

    LogComInit();
    EnterCriticalSection(&log_section);
    // �ȴ�ӡlogͷ:
    GetLocalTime(&tst);
#ifdef LOG_MS_TIMESTAMP
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, GetSysTickCount(), level_char, tag);
#elif defined (LOG_DT_MS_TIMESTAMP)
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, GetSysTickCount()%1000, level_char, tag);
#else
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, level_char, tag);
#endif
    LogComSend((unsigned char *) log_buf, i);

    // �ٴ�ӡ��ʽ�ַ���
    va_start(args, fmt);
    i = vsnprintf(log_buf, sizeof(log_buf), fmt, args);
    va_end(args);
    if (i > sizeof(log_buf)) {
        i = sizeof(log_buf);
    }
    if (i > 0) {
        LogComSend((unsigned char *) log_buf, i);
    }

    // ����ӡ���з�
    LogComSend("\r\n", 2);
    LeaveCriticalSection(&log_section);

#ifdef LOG_OUTPUT_BY_THREAD

#else
    Sleep(LOG_DELAY_MS);
#endif
}

int PrintLogToCom_AppImpl(const char *fmt, ...)
{
    int i;
    va_list args;

    va_start(args, fmt);
    i = vsnprintf(log_buf, sizeof(log_buf), fmt, args);
    va_end(args);

    if (i > 0) {
        LogComSend((unsigned char *) log_buf, i);
#ifdef LOG_OUTPUT_BY_THREAD

#else
        Sleep(LOG_DELAY_MS);
#endif
    }

    return 0;
}

int PrintLogToCom_App(const char *fmt, ...)
{
    int i;
    va_list args;

    LogComInit();
    EnterCriticalSection(&log_section);
    va_start(args, fmt);
    i = vsnprintf(log_buf, sizeof(log_buf), fmt, args);
    va_end(args);

    if (i > 0) {
        LogComSend((unsigned char *) log_buf, i);
#ifdef LOG_OUTPUT_BY_THREAD

#else
        Sleep(LOG_DELAY_MS);
#endif
    }
    LeaveCriticalSection(&log_section);

    return 0;
}


void logger_print_buff_fmt(const char *tag, char level_char, char *title, const unsigned char *buff, unsigned int len)
{
    SYSTEMTIME tst;
    int i = 0;
    unsigned int offset;
    unsigned char *pucBuf;

    LogComInit();
    EnterCriticalSection(&log_section);
    // �ȴ�ӡlogͷ:
    GetLocalTime(&tst);
#ifdef LOG_MS_TIMESTAMP
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, GetSysTickCount(), level_char, tag);
#elif defined (LOG_DT_MS_TIMESTAMP)
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, GetSysTickCount()%1000, level_char, tag);
#else
    i = snprintf(log_buf, sizeof(log_buf), LOGGER_NONE_FORMAT, tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, level_char, tag);
#endif
    LogComSend((unsigned char *) log_buf, i);

    offset = 0;
    if (title != NULL) {
        offset += snprintf(&log_buf[offset], (sizeof(log_buf) - offset), "%s", title);
        LogComSend((unsigned char *)log_buf, offset);
    }
    offset = 0;
    pucBuf = (unsigned char *)buff;
    for (i=0; i<len; i++) {
        if ((i != 0) && (i & 0x0FF) == 0) {
            LogComSend((unsigned char *)log_buf, offset);
            offset = 0;
        }
        offset += snprintf(&log_buf[offset], (sizeof(log_buf) - offset), "%02X", pucBuf[i]);
    }

    if ((i & 0x0FF) != 0) {
        LogComSend((unsigned char *)log_buf, offset);
    }

    // ����ӡ���з�
    LogComSend("\r\n", 2);
    LeaveCriticalSection(&log_section);
}

void logger_serial_dump_buff(char *title, void *buff, unsigned int len)
{
    logger_print_buff_fmt("", "", title, buff, len);
}

#endif

#ifdef TIMEDEBUG
static int TimeTickInit = 0;
static int lastTimeTick = 0;
void sendTimeforNow(char* msg)
{
    char buff[64];
    int tick = GetSysTickCount();
    if(TimeTickInit == 0)
    {        
        QCMD_Init(PORT_USBAT);
        TimeTickInit = 1;
    }
    memset(buff,0,sizeof(buff));
    snprintf(buff, sizeof(buff), "%32s : %7d : %4d\n",msg,tick,tick-lastTimeTick);
    lastTimeTick = tick;
    QCMD_Send(buff,strlen(buff));
}
#else
void sendTimeforNow(char* msg)
{

}
#endif

