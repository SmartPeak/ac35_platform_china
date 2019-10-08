#ifndef _EMV_STORAGE_H_
#define _EMV_STORAGE_H_

//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// @file     emv_storage
/// @brief    用于设置或更新终端参数文件,最好先初始化
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

#include "EmvTransHandle.h"

extern EMV_TERMINAL_INFO    TERMINAL_INFO;      // 终端参数
extern EMV_KERNEL_CONFIG    KERNEL_CONFIG;      // 内核配置
extern QPBOC_PARAM			_QPBOC_PARAMETER;
extern EXPRESS_PARAM		_AMEX_PARAMETER;
extern QVSDC_PARAM			_QVSDC_PARAMETER;
extern DISCOVER_PARAM		_DISCOVER_PARAMETER;
extern MIR_PARAMETER		_MIR_PARAMETER;
extern MASTRT_PARAM			_MASTRT_PARAM;

extern EMV_KERNEL_CONFIG_ICC KERNEL_CONFIG_ICC;// 接触配置

#ifdef __cplusplus
extern   "C"
{
#endif

    /*加载终端内核参数*/
    void EMV_LoadParameters(void);

    /*保存内核参数(保存之前先删除文件)*/
    void EMV_SaveParameters(void);

    /*删除aid文件*/
    void EMV_DeleteAidParam(void);

    /*保存aid到文件中(保存之前先删除文件)*/
    void EMV_SaveAidParam(void);

    /*删除回收公钥文件*/
    void EMV_DeleteIpkParam(void);

    /*保存回收公钥到文件中*/
    void EMV_SaveIpkParam(void);

    /*删除黑名单文件*/
    void EMV_DeleteExtParam(void);

    /*保存黑名单参数到文件(保存之前先删除文件)*/
    void EMV_SaveExtParam(void);

    /*删除capk文件*/
    void EMV_DeleteCapkParam(void);

    /*保存capk到文件中(保存之前先删除文件)*/
    void EMV_SaveCapkParam(void);

    /*加载aid,capk,ipk,expfile 个数*/
    void EMV_LoadCount(void);

    /*交易时,初始化参数*/
    void CT_Start_Trans_InitParam(void);

#ifdef __cplusplus
}
#endif

#endif

