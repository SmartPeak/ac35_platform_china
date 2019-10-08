
#ifndef EMV_CONTANT_KERNEL_CONGIF_H
#define EMV_CONTANT_KERNEL_CONGIF_H

#include "EmvCtKernelL2.h"
//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     EMVContantKernelConfig
/// @brief    ����emvL2�Ӵ��ں˵�����
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/*��ȡ�ں˵�checksum*/
EMV_VOID EMV_Kernel_CfgCheckSum(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR pCfgCheckSum, EMV_INT32 uiCfgCheckSumSiz);

/*���ýӴ��ں˵�����*/
EMV_VOID EMV_Kernel_Contact_Set_Config(LP_EMV_TRANS_HANDLE pTransHandle, EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*��ȡ�Ӵ��ں˵�����*/
EMV_VOID EMV_Kernel_Contact_Get_Config(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*
��ȡ�ں�checksum
pKernel�ں�Version:��ǰ�汾
*/
EMV_VOID EMV_Kernel_CheckSum(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR  pKernelVersion, LP_EMV_CHAR pKernelCheckSum, EMV_INT32 uiKernelCheckSumSize);

#endif


