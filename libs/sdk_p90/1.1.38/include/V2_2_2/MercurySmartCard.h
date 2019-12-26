/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_SMARTCARD_H__
#define __MERCURY_SMARTCARD_H__

/**************************************************************************************************
uint8* instr        要发送的指令
uint32 instrLen     指令长度
uint8* result       收到的回复
uint32 resultLen    result给的空间大小
uint32 waitTime     指令发送后，等待回复时间（0使用默认值）
return              实际接收长度
**************************************************************************************************/
extern uint32 SmartCardSendInstr(uint8* instr,uint32 instrLen,uint8* result,uint32 resultLen,uint32 waitTime);

/**************************************************************************************************
复位smart卡
uint32 Voltage      -------  0:1.8v  1:3.0v
uint8* pAtrInfo     -------  smart card 返回的atr
uint32  len         -------  pAtrInfo的大小
return        smart card 实际返回的atrinfo长度
**************************************************************************************************/
extern uint32 SmartCardReset(uint32 Voltage, uint8* pAtrInfo, uint32  len);

#endif
