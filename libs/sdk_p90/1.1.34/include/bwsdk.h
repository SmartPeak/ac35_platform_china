//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     bwsdk.h
/// @brief    盛本SDK头文件集合
/// @author   Cedar.Diao
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     01/28/2018
//////////////////////////////////////////////////////////////////////////////

#ifndef _BWSDK_H_
#define _BWSDK_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#ifdef BWSDK_BASED_APP_TARGET
#include "bwsdk_api.h"
#else
#include "typedef.h"
#include "hexutile.h"
#include "bw_spdev.h"
#include "port_bridge.h"
#include "softtimer.h"
#include "bwfs.h"
#include "bwfont.h"
#include "bwlcd.h"
#include "bwkb.h"
#include "bwscan.h"
#include "bwpower.h"
#include "bwsys.h"
#include "bwsigverify.h"
#include "bwaudio.h"
#include "bwsn.h"
#include "bw_ped.h"
#include "bw_picc.h"
#include "bw_icc.h"
#include "bw_memic.h"
#include "bw_magcard.h"
#include "bw_printer.h"
#include "bw_sm.h"
#include "bw_spsys.h"
#include "bwnet.h"
#include "bwsimswitch.h"
#include "bwusbat.h"
#include "bwqcmd.h"
#include "bwwlan.h"
#include "bwgprs.h"
#include "bwnv.h"
#include "bwled.h"
#include "bwbt.h"
#include "gbk2utf8.h"
#include "bwfota.h"
#include "bwhid.h"
#include "bwtp.h"
#ifdef HAVE_SDM
#include "bwsdm.h"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

