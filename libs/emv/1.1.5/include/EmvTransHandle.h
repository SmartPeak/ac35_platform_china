#ifndef EMV_TRANSACTION_H
#define EMV_TRANSACTION_H

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvKernel.h"
#include "QVSDC.h"

#define LOG_TP_COM 1    // 定义是否打印log


#define MAX_ISSUER_SCRIPT			300
#define MAX_ISSUER_SCRIPT_RESULT	256

#define MAX_RSA_EXPONENTS  3
#define MAX_RSA_MODULES    256

#define OFFLINE_APPROVED   "Y1" // 脱机批准
#define OFFLINE_DECLINE    "Z1" // 脱机拒绝
#define ONLINE_APPROVED    "Y2" // 联机批准
#define ONLINE_DECLINE     "Z2" // 联机拒绝
#define ONLINE_ERROR_OFFLINE_APPROVED "Y3" // 脱机批准，但不能联机
#define ONLINE_ERROR_OFFLINE_DECLINE  "Z3" // 脱机拒绝，但不能联机


//交易类型
enum QVSDC_TRANS_TYPE {
	TRANS_TYPE_PURCHASE = 0x00,
	TRANS_TYPE_CASHBACK,
	TRANS_TYPE_CASH,
	TRANS_TYPE_REFUND,
	
	// qpboc参数
	TRANS_TYPE_CASH1,
	TRANS_TYPE_CASHBACK1,
	TRANS_TYPE_GOODS,
	TRANS_TYPE_SERVICE,
	TRANS_TYPE_INQUIRY,
	TRANS_TYPE_TRANSFER,
	TRANS_TYPE_PAYMENT,
	TRANS_TYPE_ADMIN,
	TRANS_TYPE_DEPOSIT,
	TRANS_TYPE_LOAD_SPEC,
	TRANS_TYPE_LOAD_UNSPEC,
	TRANS_TYPE_LOAD,
	TRANS_TYPE_PREAUTH,
};


/**
 * 公钥
 */
typedef struct  {
	EMV_UINT16 m_iExponentsLen;// 指数长
	EMV_BYTE m_bExponentsValue[MAX_RSA_EXPONENTS];// 指数
	EMV_UINT16 m_iModuleLen;
	EMV_BYTE m_bModuleValue[MAX_RSA_MODULES]; // 膜
}EMV_PUBLIC_KEY;

typedef  EMV_PUBLIC_KEY * LP_EMV_PUBLIC_KEY;
typedef const  EMV_PUBLIC_KEY * LPC_EMV_PUBLIC_KEY;


// * AID 参数
typedef struct{
	//  596
	EMV_UINT16 m_uiAID;
	EMV_BYTE m_AID[MAX_AID];
	EMV_BYTE m_AppVersion[SIZE_APP_VERSION];
	EMV_BOOL m_PartMach;// 0->部分匹配,1->全匹配
	EMV_BYTE m_TerminalAcquireID[SIZE_TERMINAA_ACQUIRE_ID];
	EMV_BYTE m_Default_DDOL[MAX_DATA_SIZE]; //use when DDA
	EMV_UINT32 m_Default_DDOL_Len;
	EMV_BYTE m_Default_TDOL[MAX_DATA_SIZE]; //use when CDA
	EMV_UINT32 m_Default_TDOL_Len;
	
	EMV_UINT32 m_TerminalFloorLimit;
	EMV_UINT32 m_TresholdValue;
	EMV_UINT32 m_TargetPercentage;
	EMV_UINT32 m_MaxTargetPercentage;
	EMV_BOOL m_Priority;          //优先级标志
	
	EMV_BYTE m_TAC_Denial[SIZE_ACTION_CODE];
	EMV_BYTE m_TAC_Online[SIZE_ACTION_CODE];
	EMV_BYTE m_TAC_Default[SIZE_ACTION_CODE];

	EMV_UINT32 m_EC_Trans_Limite; //EC

	EMV_UINT32 m_ContactlessTransLimit; //qPBOC
	EMV_UINT32 m_ContactlessFloorLimit; //qPBOC
	EMV_UINT32 m_ContactlessCVMAmount; //qPBOC

	// 接触用aid参数
	EMV_BOOL m_RiskManData[MAX_RISK_MAN_DATA];   //风险管理数据(1字节长度+数据)
	EMV_BOOL m_MerchCateCode[SIZE_MERCHANT_CATEGORY_CODE];  //商户类别码(没要求可不设置)
	EMV_BOOL m_MerchId[SIZE_MERCHANT_ID];       //商户标志(商户号)  9F16
	EMV_BOOL m_MerchName[SIZE_MERCHANT_LOCATION];    //商户名
	EMV_BOOL m_TermId[SIZE_TERMINAL_ID];         //终端标志(POS号)
	EMV_BOOL m_TransCurrCode[SIZE_TRANS_CURRENCY_CODE];  //交易货币代码
	EMV_BOOL m_TransCurrExp;      //交易货币代码指数
	EMV_BOOL m_ReferCurrCode[SIZE_TRANS_CURRENCY_CODE];  //参考货币代码
	EMV_BOOL m_ReferCurrExp;      //参考货币指数
	
	EMV_BOOL m_OnlinePinSpt;      // 终端联机能力
	// m_EC_Trans_Limite存在时,
	EMV_BOOL m_ucECTSIFlag;   // 电子现金终端支持指示器 = 1,支持（EC Terminal Support Indicator）

	
} EMV_AID_ITEM;

typedef EMV_AID_ITEM * LP_EMV_AID_ITEM;

typedef const  EMV_AID_ITEM * LPC_EMV_AID_ITEM;

//#endif


/**
 * 交易过程中 产生的数据.
 */
typedef struct  {
	EMV_AID_ITEM m_CurrentApp;// 当前aid
	EMV_UINT16 m_SW;// 状态字

	EMV_BYTE m_SDA_Data[256 * 32];// sda数据 8k
	EMV_UINT16 m_SDA_DataSize;
	EMV_BOOL m_SDARecordIncorrect;// sda恢复失败
	EMV_BYTE m_PDOL_Data[MAX_CDA_DATA];// pdol数据
	EMV_UINT16 m_PDOL_DataSize;// sda数据
	EMV_BYTE m_CDOL1_Data[MAX_CDA_DATA];
	EMV_UINT16 m_CDOL1_DataSize;
	EMV_BYTE m_CDOL2_Data[MAX_CDA_DATA];
	EMV_UINT16 m_CDOL2_DataSize;

	EMV_BOOL m_CAPK_Recovered;// 公钥恢复标识
	EMV_PUBLIC_KEY m_CAPK;// 公钥对象
	EMV_BOOL m_IPK_Recovered;//发卡行公钥恢复标识
	EMV_PUBLIC_KEY m_IPK;// 发卡行公钥对象
	EMV_BOOL m_ICCPK_Recovered;// ic公钥恢复标识
	EMV_PUBLIC_KEY m_ICCPK;// IC卡公钥

	EMV_CHAR m_OnlineEncipherPIN[SIZE_PIN_BLOCK * 2 + 1];// 联机PINBLOCK
	EMV_CHAR m_IssueScript[MAX_ISSUER_SCRIPT];// 发卡行脚本数据
	EMV_UINT16 m_IssueScriptSize;// 发卡行脚本数据长
	EMV_BYTE m_ScriptResults[MAX_ISSUER_SCRIPT_RESULT];// 脚本结果
	EMV_UINT16 m_uiScriptResults;// 脚本长度
	EMV_BOOL m_SignatureRequired;// 签名请求
	EMV_BOOL m_OnlinePinRequired;// 联机pin请求
	
	//非接使用参数
	EMV_BOOL m_SmRequired; // ?? SM
	EMV_BOOL m_SkipPINEntry; 
	EMV_BOOL m_OnlineNeeded;
	EMV_BOOL m_AdviceNeeded;

	EMV_ONLINE_RESULT m_OnlineResult;// 联机结果

	EMV_BOOL m_QVSDC_NeedToSaveLog;// 保存log
	EMV_UINT32 m_QVSDC_TarnsCounter;// 交易计数器
	EMV_BYTE m_QVSDC_TransType;// 交易类型
	EMV_UINT32 m_QVSDC_Amount;// 交易金额
	EMV_UINT32 m_QVSDC_AmountOther;// 其他金额

	// VISA
	EMV_BOOL m_QVSDC_Online_Flag;// 联机标志
	EMV_BOOL m_QVSDC_Decline_Flag;// 拒绝标志
	EMV_BOOL m_QVSDC_AppNotAllow_Flag;// 应用不允许
	
	// DISCOVER
	EMV_BOOL m_Discover_Emv_Flag;
	EMV_UINT16 m_Discover_UnLen;// PDOL 9F37 值. 在计算磁道信息时, 会使用到.

	// AMEX
	EMV_BOOL m_AMEX_Expresspay_Emv_Flag; //TRUE(Expresspay EMV Mode Transaction) FALSE (Expresspay Magstripe Mode Transaction)
	EMV_BOOL m_AMEX_Expresspay_Mobile_Flag; //TRUE(Expresspay Mobile) FALSE(Expresspay Card)
	EMV_BOOL m_AMEX_Delayed_Auth_Flag; //TRUE(Delayed Authorisations) FALSE(NOT)
	EMV_BOOL m_AMEX_Alternative_Interface_Flag; //TRUE 交易失败可以执行其他接口.
	EMV_BYTE m_AMEX_ATC[3];
	EMV_UINT16 m_AMEX_ATCLen;

	// MIR
	EMV_BOOL m_MIR_Protocol_Flag; // EMV_TRUE Protocol Id "01" 类似借贷记模式 . "02"  MIR Q流程
	EMV_UINT32 m_MIR_ODA;//是否执行ODA

	//QUICS
	EMV_BOOL m_QUICS_OnlineODA;//QUICS 联机ODA.

}EMV_TRANSACTION_DATA;

typedef EMV_TRANSACTION_DATA * LP_EMV_TRANSACTION_DATA;

/*****************************以下接触配置*********************************/
// 终端配置参数
typedef struct{
	EMV_BYTE m_SupportSM;			//是否支持国密算法
	EMV_BYTE m_CardRefer; // 是否支持卡片参考
	EMV_BYTE m_EquippedPINPAD; // 是否外接密码键盘
	EMV_BYTE m_EnterAmtSamePAD;// 金额和pin是否同一键盘
	EMV_BYTE m_MagFailtoIC[SIZE_TERMINAL_ENTRY_MODE*2+1]; // 降级
	EMV_BYTE m_ActionRequired;// 公钥更新失败,是否提醒
	EMV_BOOL m_AppNotAllow_Flag;// 应用不允许
	EMV_BOOL m_BlockAddFlag;// 读卡片日志时,锁定的应用是否加入候选列表(1加入,0不加入)
	EMV_BOOL m_ForcePrint;// 强制打印
	EMV_BYTE m_TACDisableFlag;
	EMV_BYTE m_SupprrtShowPan;// 是否支持显示卡号
	EMV_BYTE m_PbocHoldCardCheck;// pboc 持卡人证件检查
	// 暂时保留三个参数,为后续增加参数保留
	EMV_BYTE m_RFU1;
	EMV_BYTE m_RFU2;
	EMV_BYTE m_RFU3;
}EMV_KERNEL_CONFIG_ICC;

typedef EMV_KERNEL_CONFIG_ICC * LP_EMV_KERNEL_CONFIG_ICC;

typedef struct{
	EMV_CHAR m_PreferNameFlag; // 是否存在应用优先名称的标志9f11
	EMV_BOOL m_NeedToSaveLog;// 保存log
	EMV_UINT32 m_TransCounter;// 交易计数器
	EMV_BYTE m_TransType;// 交易类型
	EMV_UINT32 m_Amount;// 交易金额
	EMV_UINT32 m_AmountOther;// 其他金额
	EMV_BOOL m_Online_Flag;// 联机标志
	EMV_BOOL m_Decline_Flag;// 拒绝标志
	EMV_BOOL m_PrintReceipt;// 请求打印标志位
	EMV_BOOL m_CDAAuthFlag;// 是否请求cda的标志位
	EMV_BOOL m_OfflineApprove;// 脱机批准的标志位
	EMV_BYTE m_CDA_Data[MAX_CDA_DATA];// cda数据
	EMV_UINT16 m_CDA_DataSize;// cda数据长
	EMV_BYTE m_CardBySM;// 国密tag返回
	EMV_BYTE m_ECTSIVal;// 保存电子现金终端指示器的值 9f7a
	EMV_INT32 m_EcBalance;// 电子现金余额
	EMV_UINT32 m_CTKernelCfgMode;// 当前接触内核的配置
	MAG_TRACK_DATA m_MagTrackData;// 磁道数据
	PIN_OFF_CIPHER_ITEM m_CipherItem;// 脱机密文的数据
	EMV_BOOL m_GACNumCnt;// 记录gac次数,一笔交易最多发送2gac
}EMV_TRANSACTION_ICC_DATA;

typedef EMV_TRANSACTION_ICC_DATA * LP_EMV_TRANSACTION_ICC_DATA;


/******************************************************************************/

/**
 * 交易过程参数
 *
 */
struct EMV_TRANS_HANDLE{
	EMV_CALLBACK_FUNCS m_CallBacks;
	EMV_TERMINAL_INFO m_TerminalInfo;
	EMV_KERNEL_CONFIG m_KernelConfig;
	DISCOVER_PARAMETER m_Discover_Param;
	QVSDC_PARAMETER m_QVSDC_Param;
	QPBOC_PARAMETER m_QPBOC_Param;
	EXPRESS_PARAMETER m_Express_Param;
	MIR_PARAMETER m_Mir_Param;
	MASTRT_PARAM  m_Mastrt_Param;

	KERNEL_VERSION_TYPE m_KernelVersion;
	KERNEL_MODE_TYPE m_KernelMode;
	
	KERNEL_START_TYPE m_KernelStartCode; //启动状态.

	EMV_BOOL m_Discover_DPAS; //确定走 D-PAS , ZIP
	
	EMV_BOOL m_Mir_FlashCard;
	EMV_BOOL m_Mir_FlashCardReadRecord;
	EMV_BOOL m_Mir_FlashCardCompleteTransaction;
	EMV_BYTE m_Mir_PerformResp[270];
	EMV_UINT16 m_Mir_PerformRespSize;
	EMV_UINT32 m_MIR_Transaction_Recovery_Counter; //
	
	EMV_BOOL m_Mastrt_NoMsMOde; //万事达不支持MS.

	EMV_UINT8 m_KernelApplyAid; // 是否启用AID非接限额
	EMV_UINT32 m_LogLevel;
	EMV_TRANSACTION_DATA m_TransactionData;
	EMV_KERNEL_CONFIG_ICC m_KernelConfigIcc;// icc配置 
	EMV_TRANSACTION_ICC_DATA m_TransIccData;// icc数据

};

typedef struct EMV_TRANS_HANDLE * LP_EMV_TRANS_HANDLE;

#ifdef __cplusplus
}
#endif

#endif
