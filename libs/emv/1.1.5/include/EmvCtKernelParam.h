#ifndef EMV_CT_KERNEL_PARAM_H_
#define EMV_CT_KERNEL_PARAM_H_

#include "EmvDataType.h"
#include "AppCallBack.h"

#ifdef __cplusplus
extern   "C"
{
#endif

//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     EMVCtKernelParam 
/// @brief    ���ڽӴ��ں˲����������Լ����ò���
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/*�����������ױ������ʱ����*/
typedef struct 
{
	EMV_INT32 m_TarnsCounter;
	EMV_BYTE  m_TransType;
	EMV_INT32 m_Amount;
	EMV_INT32 m_AmountOther;
}CONTACT_INIT;



/**
* ��ʼ�����ײ���
* TransType����������
* uiTransCountNumber�����׼�����ֵ
*/
int Contact_Init_Trans_Data(LP_EMV_TRANS_HANDLE pTransHandle,
	EMV_BYTE TransType, EMV_INT32 uiTransCountNumber);


/*��ʼ���������ṹ�������*/
void Cantact_Kernel_Set_Trans_Param(EMV_INT32 uiTarnsCounter,
	unsigned char TransType, EMV_INT32 Amount, EMV_INT32 AmountOther);



#ifdef __cplusplus
}
#endif
#endif

