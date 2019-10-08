#ifndef EMV_CT_KERNEL_PARAM_H_
#define EMV_CT_KERNEL_PARAM_H_

#include "EmvDataType.h"
#include "AppCallBack.h"

#ifdef __cplusplus
extern   "C"
{
#endif

//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     EMVCtKernelParam 
/// @brief    用于接触内核参数的配置以及设置参数
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/*用于启动交易保存的临时变量*/
typedef struct 
{
	EMV_INT32 m_TarnsCounter;
	EMV_BYTE  m_TransType;
	EMV_INT32 m_Amount;
	EMV_INT32 m_AmountOther;
}CONTACT_INIT;



/**
* 初始化交易参数
* TransType：交易类型
* uiTransCountNumber：交易计算器值
*/
int Contact_Init_Trans_Data(LP_EMV_TRANS_HANDLE pTransHandle,
	EMV_BYTE TransType, EMV_INT32 uiTransCountNumber);


/*初始化参数到结构体变量中*/
void Cantact_Kernel_Set_Trans_Param(EMV_INT32 uiTarnsCounter,
	unsigned char TransType, EMV_INT32 Amount, EMV_INT32 AmountOther);



#ifdef __cplusplus
}
#endif
#endif

