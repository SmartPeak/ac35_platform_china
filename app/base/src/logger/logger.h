//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     logger.h
/// @brief    LOG接口
/// @author   HuangChangJiang
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     12/27/2017
//////////////////////////////////////////////////////////////////////////////

#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef __cplusplus
extern   "C"
{
#endif

#define LOGGER_D 'D'
#define LOGGER_E 'E'
#define LOGGER_I 'I'
#define LOGGER_V 'V'

//#define LOG_DISABLE
//#define TIMEDEBUG

#ifdef LOG_DISABLE
/**
 * 打印调试信息到LCD上
 * @author diaoxuesong@basewin.com
 */
#define LCDLOG(...) 

/**
 * 打印调试信息
 * @author diaoxuesong@basewin.com
 */
#define LOGD(...)

/**
 * 打印错误信息
 * @author diaoxuesong@basewin.com
 */
#define LOGE(...)

/**
 * 打印普通信息
 * @author diaoxuesong@basewin.com
 */
#define LOGI(...)

/**
 * 打印详细信息
 * @author diaoxuesong@basewin.com
 */
#define LOGV(...)

/**
 * 打印调试数组信息
 */
#define LOGDUMP(...)

/**
 * @author wanglong@basewin.com
 * @brief 串口打印日志
 * @param fmt [in] 变长日志内容填写
 */
#define PrintLogToCom_App(...)


/**
 * @author diaoxuesong@basewin.com
 * @brief 串口打印格式化日志
 * @param tag [in] TAG填写不超过15个字符
 * @param level_char [in] LOG等级, E/D/I/V
 * @param fmt [in] 变长日志内容填写
 */
#define logger_print_serial_fmt(...)

/**
 * @brief 将缓冲区内容以十六进制打印到串口上
 * @author diaoxuesong@basewin.com
 * @param title [in] 标题，可以为NULL
 * @param buff [in] 缓冲区
 * @param len [in] 要打印的缓冲区长度
 */
#define logger_serial_dump_buff(title, buffb, len)

/**
 * @brief 将缓冲区内容以十六进制打印到串口上
 * @param tag [in] TAG填写不超过15个字符
 * @param level_char [in] LOG等级, E/D/I/V
 * @param title [in] 标题，可以为NULL
 * @param buff [in] 缓冲区
 * @param len [in] 要打印的缓冲区长度
 */
#define logger_print_buff_fmt(...)


/**
 * @是否允许Log从AT口输出
 * @param [in] en  1: 允许输出, 0: 禁止输出
 */
#define LogToATPortEnable(en)

#else
/**
 * 打印调试信息到LCD上
 * @author diaoxuesong@basewin.com
 */
#define LCDLOG(...) do{ScrCls(); ScrGotoXY(0, 24); ScrPrintf(__VA_ARGS__);}while(0)

/**
 * 打印调试信息
 * @author diaoxuesong@basewin.com
 */
#define LOGD(...) logger_print_serial_fmt(TAG, LOGGER_D, __VA_ARGS__)

/**
 * 打印错误信息
 * @author diaoxuesong@basewin.com
 */
#define LOGE(...) logger_print_serial_fmt(TAG, LOGGER_E, __VA_ARGS__)

/**
 * 打印普通信息
 * @author diaoxuesong@basewin.com
 */
#define LOGI(...) logger_print_serial_fmt(TAG, LOGGER_I, __VA_ARGS__)

/**
 * 打印详细信息
 * @author diaoxuesong@basewin.com
 */
#define LOGV(...) logger_print_serial_fmt(TAG, LOGGER_V, __VA_ARGS__)

/**
 * 打印调试数组信息
 */
#define LOGDUMP(title, buff, len)   logger_print_buff_fmt(TAG, LOGGER_D, title, buff, len)


/**
 * @author wanglong@basewin.com
 * @brief 串口打印日志
 * @param fmt [in] 变长日志内容填写
 */
int PrintLogToCom_App(const char *fmt, ...);


/**
 * @author diaoxuesong@basewin.com
 * @brief 串口打印格式化日志
 * @param tag [in] TAG填写不超过15个字符
 * @param level_char [in] LOG等级, E/D/I/V
 * @param fmt [in] 变长日志内容填写
 */
void logger_print_serial_fmt(const char *tag, char level_char, const char *fmt, ...);


/**
 * @brief 将缓冲区内容以十六进制打印到串口上
 * @author diaoxuesong@basewin.com
 * @param title [in] 标题，可以为NULL
 * @param buff [in] 缓冲区
 * @param len [in] 要打印的缓冲区长度
 */
void logger_serial_dump_buff(char *title, void *buff, unsigned int len);

/**
 * @brief 将缓冲区内容以十六进制打印到串口上
 * @param tag [in] TAG填写不超过15个字符
 * @param level_char [in] LOG等级, E/D/I/V
 * @param title [in] 标题，可以为NULL
 * @param buff [in] 缓冲区
 * @param len [in] 要打印的缓冲区长度
 */
void logger_print_buff_fmt(const char *tag, char level_char, char *title, const unsigned char *buff, unsigned int len);

/**
 * @是否允许Log从AT口输出
 * @param [in] en  1: 允许输出, 0: 禁止输出
 */
void LogToATPortEnable(int en);

#endif

void sendTimeforNow(char* msg);

#ifdef __cplusplus
}
#endif

#endif //_LOGGER_H

