#ifndef EMV_CT_KERNEL_L2_H_
#define EMV_CT_KERNEL_L2_H_


#include "EmvTransHandle.h"
#ifdef __cplusplus
extern   "C"
{
#endif

/*定义接触内核的配置*/
typedef enum
{
	EMV_KERNEL_CONTACT_MODE_ALL = 0,// 全配置
	EMV_KERNEL_CONTACT_MODE_CONFIG_2C_PBOC,// pboc内核,
	EMV_KERNEL_CONTACT_MODE_CONFIG_3C,//不支持no cvm
	EMV_KERNEL_CONTACT_MODE_CONFIG_4C,//不支持脱机pin
	EMV_KERNEL_CONTACT_MODE_CONFIG_5C,//只支持no cvm
	EMV_KERNEL_CONTACT_MODE_CONFIG_6C,//仅脱机,不支持磁条,联机pin,不支持强制联机
	// 以下暂时保留
	EMV_KERNEL_CONTACT_MODE_CONFIG_7C,
	EMV_KERNEL_CONTACT_MODE_CONFIG_8C,
	EMV_KERNEL_CONTACT_MODE_CONFIG_9C,
}EMV_KERNEL_CONTACT_CONFIG_MODE;

typedef EMV_KERNEL_CONTACT_CONFIG_MODE *LP_EMV_KERNEL_CONTACT_CONFIG_MODE;
//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 上海盛本智能科技股份有限公司
/// All rights reserved.
/// 
/// @file     EMVCtKernelL2
/// @brief    用于接触流程的 处理
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

#define	EMV_KERNEL_USE_AUTH_TEST  // 用于部分参数使用aid而不是使用终端参数

#define EMV_BASE 0

#define EMV_ICC_RESET_ERR     					EMV_BASE-1 //IC卡复位失败
#define EMV_ICC_CMD_ERR       					EMV_BASE-2 //IC命令失败
#define EMV_ICC_BLOCK         					EMV_BASE-3 //IC卡锁卡    
#define EMV_ICC_RSP_ERR       					EMV_BASE-4 //IC返回码错误
#define EMV_ICC_APP_BLOCK     					EMV_BASE-5 //应用已锁
#define EMV_ICC_NO_APP              			EMV_BASE-6	// 卡片里没有EMV应用
#define EMV_ICC_USER_CANCEL   					EMV_BASE-7 //用户取消当前操作或交易
#define EMV_ICC_TIME_OUT      					EMV_BASE-8 //用户操作超时
#define EMV_ICC_DATA_ERR      					EMV_BASE-9 //卡片数据错误
#define EMV_ICC_NOT_ACCEPT   					EMV_BASE-10 //交易不接受
#define EMV_ICC_DENIAL        					EMV_BASE-11 //交易被拒绝
#define EMV_ICC_INVALID_TLV         			EMV_BASE-12 // 无效tlv
#define EMV_ICC_PIN_BLOCK     					EMV_BASE-13 // pin锁定
#define EMV_ICC_NEEDUSERSEL	  					EMV_BASE-14	//需要用户选择  
#define EMV_ICC_CARD_READ_ERROR   				EMV_BASE-15	//卡片读取错误
#define EMV_ICC_USE_MAG_STRIPE 					EMV_BASE-16	//降级
#define EMV_ICC_DATA_EXIST    					EMV_BASE-17 // 数据不存在
#define EMV_ICC_CVM_DATA_ERR					EMV_BASE-18	//cvm(8e)数据错误
#define EMV_ICC_NO_TRANS_LOG					EMV_BASE-19	//没有交易log
#define EMV_ICC_RECORD_NOTEXIST					EMV_BASE-20	//记录不存在
#define EMV_ICC_MULT_SEL_REE					EMV_BASE-21	//多应用选择错误
#define EMV_ICC_AUTH_RECOVER_CERT_ERR			EMV_BASE-22	//恢复证书失败
#define EMV_ICC_AUTH_SDA_AUTH_ERR				EMV_BASE-23	//sda验证失败
#define EMV_ICC_AUTH_DDA_AUTH_ERR				EMV_BASE-24	//dda验证失败
#define EMV_ICC_AUTH_CDA_AUTH_ERR				EMV_BASE-25	//cda验证失败
#define EMV_ICC_AUTH_VERIFY_HASH_ERR			EMV_BASE-26	//验证hash错误
#define EMV_ICC_DEAL_CVM_ERR					EMV_BASE-27	//处理cvm列表失败
#define EMV_ICC_MAG_FAIL						EMV_BASE-28	//磁条卡失败
#define EMV_ICC_RSP_6985  						EMV_BASE-29 // 返回6985
#define EMV_ICC_NO_RECORD 						EMV_BASE-30 // 没记录
#define EMV_ICC_CID_ERR       					EMV_BASE-31 // CDA认证时,恢复的CID与卡片回送的CID信息不一致
#define EMV_ICC_EC_BALANCE_LIMIT    			EMV_BASE-32 // 纯电子现金余额不足



#define POS_ENTRY_MODE_MAG_STRIPE  "02" // 磁条
#define POS_ENTRY_MODE_CONTACT  "05" // 接触
#define POS_ENTRY_MODE_QPBOC  "07" // qpboc
#define POS_ENTRY_MODE_CONTACTLESS_PBOC  "08" // 非接借贷记

#define POS_ENTRY_MODE_MAG_FAIL_TO_IC   "80" // 降级的pos输入方式 由0x92->0x80

/**
* 获取接触内核版本
*/
EMV_INT32 Contact_Get_Version_Kernel(char * pBuffer, int uiBufferSize);


/*
启动内核交易
bEMVSimpleFlag:是否为简单流程
pMagTrack:磁条卡数据
pContactDetect:其他卡检检测
*/
EMV_INT32 Contact_Start_EMV_Kernel(EMV_CHAR bEMVSimpleFlag, LP_MAG_TRACK_DATA pMagTrack,
	Fn_EMV_Contact_DetectCard pContactDetect);

/*保存配置参数*/
EMV_VOID EMV_Cantact_Kernel_Set_Config(LP_EMV_KERNEL_CONFIG_ICC pContactConfigIcc);


/*获取接触配置参数*/
EMV_VOID EMV_Cantact_Kernel_Get_Config(LP_EMV_KERNEL_CONFIG_ICC pContactConfigIcc);


/**
创建应用列表,用于读取卡片日志,
return:EMV_OK->suc(调用EMV_Contact_ReadCardLog)
*/
EMV_INT32 EMV_Contact_AppListNoGPO(void);

/**
读取卡片日志
bRecordNO:序号
pLogFormatList:获取卡片日志格式9f4f
uiLogFormatList:
pReadCardLog:返回读记录
uiReadCardLog:返回记录长
return:EMV_OK->suc,EMV_ICC_RECORD_NOTEXIST:无记录,EMV_ICC_NO_TRANS_LOG->记录不存在,
EMV_ICC_DATA_ERR->数据错误
*/
EMV_INT32 EMV_Contact_ReadCardLog(EMV_INT32 bRecordNO, EMV_BYTE *pLogFormatList, LP_EMV_INT32 uiLogFormatList,
	EMV_BYTE *pReadCardLog, LP_EMV_INT32 uiReadCardLog);


/*获取电子现金余额*/
EMV_INT32 EMV_Contact_ReadEcBanlance(EMV_INT32 *pECBanlance);


/*获取内核的配置checksum*/
EMV_VOID EMV_Contact_CfgCheckSum(LP_EMV_CHAR pCheckSum, EMV_INT32 uiCheckSumSize);

/*
获取内核的checksum
tips:此EMV_Contact_CfgCheckSum
	方法获取不同内核配置的checksum,配置不同sum值,可多个sum值
	EMV_Contact_KernelCheckSum 获取内核的sum,一般一个内核只有一个sum值
*/
EMV_VOID EMV_Contact_KernelCheckSum(LP_EMV_CHAR pKernelCheckSum, EMV_INT32 uiKernelCheckSumSize);


/*获取电子现金余额*/
EMV_VOID EMV_Contact_GetECBanlance(EMV_INT32 *pECBanlance);

/*获取是否打印收据的标志位*/
EMV_BOOL EMV_Contact_GetPrintReceipt(EMV_VOID);


/*
获取脚本结果(str)
*/
EMV_UINT32 EMV_Contact_GetScriptResult(LP_EMV_CHAR pScript, EMV_INT32 uiScriptSize);


/*
用于验证脱机pinlock是否正常
pClipherPinFlag:是否为密文pin验证
pPinBlock:要验证的pinblock
uiPinBlock:
*/
EMV_INT32 EMV_Contact_Verify(EMV_BOOL pCipherPinFlag, LPC_EMV_BYTE pPinBlock, EMV_INT32 uiPinBlock, EMV_BYTE pVerifySW[2]);

/*设置内核配置*/
EMV_VOID EMV_Contact_SetKernelCfg(EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);


/*设置当前内核配置*/
EMV_VOID EMV_Contact_GetKernelCfg(LP_EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*
获取发卡行认证指示位
pResp:响应数据
uiResp:响应长指针
*/
EMV_INT32 EMV_Cantact_Kernel_GetIssuerAuthFlag(LP_EMV_BYTE pResp, LP_EMV_INT32 uiResp);

#ifdef __cplusplus
}
#endif

#endif

