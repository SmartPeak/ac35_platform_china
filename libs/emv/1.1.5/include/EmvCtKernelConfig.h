
#ifndef EMV_CONTANT_KERNEL_CONGIF_H
#define EMV_CONTANT_KERNEL_CONGIF_H

#include "EmvCtKernelL2.h"
//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     EMVContantKernelConfig
/// @brief    用于emvL2接触内核的配置
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/*获取内核的checksum*/
EMV_VOID EMV_Kernel_CfgCheckSum(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR pCfgCheckSum, EMV_INT32 uiCfgCheckSumSiz);

/*设置接触内核的配置*/
EMV_VOID EMV_Kernel_Contact_Set_Config(LP_EMV_TRANS_HANDLE pTransHandle, EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*获取接触内核的配置*/
EMV_VOID EMV_Kernel_Contact_Get_Config(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*
获取内核checksum
pKernel内核Version:当前版本
*/
EMV_VOID EMV_Kernel_CheckSum(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR  pKernelVersion, LP_EMV_CHAR pKernelCheckSum, EMV_INT32 uiKernelCheckSumSize);

#endif


