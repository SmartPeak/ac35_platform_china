/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_SMARTCARD_H__
#define __MERCURY_SMARTCARD_H__

/**************************************************************************************************
uint8* instr        Ҫ���͵�ָ��
uint32 instrLen     ָ���
uint8* result       �յ��Ļظ�
uint32 resultLen    result���Ŀռ��С
uint32 waitTime     ָ��ͺ󣬵ȴ��ظ�ʱ�䣨0ʹ��Ĭ��ֵ��
return              ʵ�ʽ��ճ���
**************************************************************************************************/
extern uint32 SmartCardSendInstr(uint8* instr,uint32 instrLen,uint8* result,uint32 resultLen,uint32 waitTime);

/**************************************************************************************************
��λsmart��
uint32 Voltage      -------  0:1.8v  1:3.0v
uint8* pAtrInfo     -------  smart card ���ص�atr
uint32  len         -------  pAtrInfo�Ĵ�С
return        smart card ʵ�ʷ��ص�atrinfo����
**************************************************************************************************/
extern uint32 SmartCardReset(uint32 Voltage, uint8* pAtrInfo, uint32  len);

#endif
