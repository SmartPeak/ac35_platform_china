#ifndef EMV_CT_KERNEL_MAIN_H_
#define EMV_CT_KERNEL_MAIN_H_

#ifdef __cplusplus
extern   "C"
{
#endif


//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     EMVCtKernelMain
/// @brief    用于接触内核的处理,用于外部的调用
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

/**
* 交易开始
uiTarnsCounter:交易计算器
TransType:交易类型
Amount:交易金额
AmountOther:返现金额
bEMVSimpleFlag:是否是emv简单流程 1->yes
pMagTrack;磁条卡数据
*/
unsigned int Contact_Start_Kernel(unsigned int uiTarnsCounter, unsigned char TransType, unsigned int Amount,
		unsigned int AmountOther, char bEMVSimpleFlag, LP_MAG_TRACK_DATA pMagTrack);

/*清楚交易数据(aid,capk,)*/
void Contact_Start_Clear_Param(void);

#ifdef __cplusplus
}
#endif
#endif

