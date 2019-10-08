#ifndef _EMV_STORAGE_H_
#define _EMV_STORAGE_H_

//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// @file     emv_storage
/// @brief    �������û�����ն˲����ļ�,����ȳ�ʼ��
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

#include "EmvTransHandle.h"

extern EMV_TERMINAL_INFO    TERMINAL_INFO;      // �ն˲���
extern EMV_KERNEL_CONFIG    KERNEL_CONFIG;      // �ں�����
extern QPBOC_PARAM			_QPBOC_PARAMETER;
extern EXPRESS_PARAM		_AMEX_PARAMETER;
extern QVSDC_PARAM			_QVSDC_PARAMETER;
extern DISCOVER_PARAM		_DISCOVER_PARAMETER;
extern MIR_PARAMETER		_MIR_PARAMETER;
extern MASTRT_PARAM			_MASTRT_PARAM;

extern EMV_KERNEL_CONFIG_ICC KERNEL_CONFIG_ICC;// �Ӵ�����

#ifdef __cplusplus
extern   "C"
{
#endif

    /*�����ն��ں˲���*/
    void EMV_LoadParameters(void);

    /*�����ں˲���(����֮ǰ��ɾ���ļ�)*/
    void EMV_SaveParameters(void);

    /*ɾ��aid�ļ�*/
    void EMV_DeleteAidParam(void);

    /*����aid���ļ���(����֮ǰ��ɾ���ļ�)*/
    void EMV_SaveAidParam(void);

    /*ɾ�����չ�Կ�ļ�*/
    void EMV_DeleteIpkParam(void);

    /*������չ�Կ���ļ���*/
    void EMV_SaveIpkParam(void);

    /*ɾ���������ļ�*/
    void EMV_DeleteExtParam(void);

    /*����������������ļ�(����֮ǰ��ɾ���ļ�)*/
    void EMV_SaveExtParam(void);

    /*ɾ��capk�ļ�*/
    void EMV_DeleteCapkParam(void);

    /*����capk���ļ���(����֮ǰ��ɾ���ļ�)*/
    void EMV_SaveCapkParam(void);

    /*����aid,capk,ipk,expfile ����*/
    void EMV_LoadCount(void);

    /*����ʱ,��ʼ������*/
    void CT_Start_Trans_InitParam(void);

#ifdef __cplusplus
}
#endif

#endif

