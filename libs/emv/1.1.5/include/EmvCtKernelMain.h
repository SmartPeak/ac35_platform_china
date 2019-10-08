#ifndef EMV_CT_KERNEL_MAIN_H_
#define EMV_CT_KERNEL_MAIN_H_

#ifdef __cplusplus
extern   "C"
{
#endif


//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     EMVCtKernelMain
/// @brief    ���ڽӴ��ں˵Ĵ���,�����ⲿ�ĵ���
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/**
* ���׿�ʼ
uiTarnsCounter:���׼�����
TransType:��������
Amount:���׽��
AmountOther:���ֽ��
bEMVSimpleFlag:�Ƿ���emv������ 1->yes
pMagTrack;����������
*/
unsigned int Contact_Start_Kernel(unsigned int uiTarnsCounter, unsigned char TransType, unsigned int Amount,
		unsigned int AmountOther, char bEMVSimpleFlag, LP_MAG_TRACK_DATA pMagTrack);

/*�����������(aid,capk,)*/
void Contact_Start_Clear_Param(void);

#ifdef __cplusplus
}
#endif
#endif

