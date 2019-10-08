//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     logger.h
/// @brief    LOG�ӿ�
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
 * ��ӡ������Ϣ��LCD��
 * @author diaoxuesong@basewin.com
 */
#define LCDLOG(...) 

/**
 * ��ӡ������Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGD(...)

/**
 * ��ӡ������Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGE(...)

/**
 * ��ӡ��ͨ��Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGI(...)

/**
 * ��ӡ��ϸ��Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGV(...)

/**
 * ��ӡ����������Ϣ
 */
#define LOGDUMP(...)

/**
 * @author wanglong@basewin.com
 * @brief ���ڴ�ӡ��־
 * @param fmt [in] �䳤��־������д
 */
#define PrintLogToCom_App(...)


/**
 * @author diaoxuesong@basewin.com
 * @brief ���ڴ�ӡ��ʽ����־
 * @param tag [in] TAG��д������15���ַ�
 * @param level_char [in] LOG�ȼ�, E/D/I/V
 * @param fmt [in] �䳤��־������д
 */
#define logger_print_serial_fmt(...)

/**
 * @brief ��������������ʮ�����ƴ�ӡ��������
 * @author diaoxuesong@basewin.com
 * @param title [in] ���⣬����ΪNULL
 * @param buff [in] ������
 * @param len [in] Ҫ��ӡ�Ļ���������
 */
#define logger_serial_dump_buff(title, buffb, len)

/**
 * @brief ��������������ʮ�����ƴ�ӡ��������
 * @param tag [in] TAG��д������15���ַ�
 * @param level_char [in] LOG�ȼ�, E/D/I/V
 * @param title [in] ���⣬����ΪNULL
 * @param buff [in] ������
 * @param len [in] Ҫ��ӡ�Ļ���������
 */
#define logger_print_buff_fmt(...)


/**
 * @�Ƿ�����Log��AT�����
 * @param [in] en  1: �������, 0: ��ֹ���
 */
#define LogToATPortEnable(en)

#else
/**
 * ��ӡ������Ϣ��LCD��
 * @author diaoxuesong@basewin.com
 */
#define LCDLOG(...) do{ScrCls(); ScrGotoXY(0, 24); ScrPrintf(__VA_ARGS__);}while(0)

/**
 * ��ӡ������Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGD(...) logger_print_serial_fmt(TAG, LOGGER_D, __VA_ARGS__)

/**
 * ��ӡ������Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGE(...) logger_print_serial_fmt(TAG, LOGGER_E, __VA_ARGS__)

/**
 * ��ӡ��ͨ��Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGI(...) logger_print_serial_fmt(TAG, LOGGER_I, __VA_ARGS__)

/**
 * ��ӡ��ϸ��Ϣ
 * @author diaoxuesong@basewin.com
 */
#define LOGV(...) logger_print_serial_fmt(TAG, LOGGER_V, __VA_ARGS__)

/**
 * ��ӡ����������Ϣ
 */
#define LOGDUMP(title, buff, len)   logger_print_buff_fmt(TAG, LOGGER_D, title, buff, len)


/**
 * @author wanglong@basewin.com
 * @brief ���ڴ�ӡ��־
 * @param fmt [in] �䳤��־������д
 */
int PrintLogToCom_App(const char *fmt, ...);


/**
 * @author diaoxuesong@basewin.com
 * @brief ���ڴ�ӡ��ʽ����־
 * @param tag [in] TAG��д������15���ַ�
 * @param level_char [in] LOG�ȼ�, E/D/I/V
 * @param fmt [in] �䳤��־������д
 */
void logger_print_serial_fmt(const char *tag, char level_char, const char *fmt, ...);


/**
 * @brief ��������������ʮ�����ƴ�ӡ��������
 * @author diaoxuesong@basewin.com
 * @param title [in] ���⣬����ΪNULL
 * @param buff [in] ������
 * @param len [in] Ҫ��ӡ�Ļ���������
 */
void logger_serial_dump_buff(char *title, void *buff, unsigned int len);

/**
 * @brief ��������������ʮ�����ƴ�ӡ��������
 * @param tag [in] TAG��д������15���ַ�
 * @param level_char [in] LOG�ȼ�, E/D/I/V
 * @param title [in] ���⣬����ΪNULL
 * @param buff [in] ������
 * @param len [in] Ҫ��ӡ�Ļ���������
 */
void logger_print_buff_fmt(const char *tag, char level_char, char *title, const unsigned char *buff, unsigned int len);

/**
 * @�Ƿ�����Log��AT�����
 * @param [in] en  1: �������, 0: ��ֹ���
 */
void LogToATPortEnable(int en);

#endif

void sendTimeforNow(char* msg);

#ifdef __cplusplus
}
#endif

#endif //_LOGGER_H

