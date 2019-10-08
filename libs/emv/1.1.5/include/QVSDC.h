#ifndef QVSDC_H_
#define QVSDC_H_

#include "EmvKernel.h"


#define QVSDC_AMOUNT_BIG_THAN_CL_LIMIT 	99      //金额超出交易限额
#define QVSDC_OTHER_INTERFACE			100     //其他
#define QVSDC_OTHER_INTERFACE_6984		101     //
#define QVSDC_TERMINATED_CONTACT     	105		// 接触
#define QVSDC_TERMINATED_SWIPE       	106		// 刷卡

#define QVSDC_RETURN_TO_FINAL_SELECTION 107  // 返回到最终选择
#define QVSDC_RETURN_TO_TAP_CARD		108 //  返回到选卡
#define QVSDC_RETURN_TO_2ND_TAP_CARD	109


#define QPBOC_OTHER_INTERFACE			110
#define QPBOC_AMOUNT_BIG_THAN_CL_LIMIT  111
#define QPBOC_IN_EXCEPTION_FILE			112
#define QPBOC_CARD_EXPIRED				113
#define QPBOC_CANT_GO_ONLINE_DECLINE	114
#define QPBOC_RETURN_TO_TAP_CARD_GPO_NULL 118

#define AMEX_TRY_AGAIN					115 //重新挥卡交易
#define AMEX_TRY_ANOTHER_INTERFACE		116 
#define AMEX_END_APPLICATION			117

#define MASTRT_TRY_AGAIN				119

#define MIR_DECLINED					120
#define MIR_APPROVED					121
#define MIR_ONLINE_REQUEST				122
#define MIR_TWO_PRESENTATIONS			123
#define MIR_TRY_ANOTHER_INTERFACE		124
#define MIR_END_APPLICATION				125

//Data error 			‘05’
#define MIR_END_APPLICATION_DATA_ERROR		126
//GEN AC, no answer 	‘06’
#define MIR_END_APPLICATION_GAC_NO_ANSWER	127
//GEN AC, bad answer format ‘07’
#define MIR_END_APPLICATION_GAC_BAD_ANSWER	137
//GEN AC, bad CID value 	  ‘08’
#define MIR_END_APPLICATION_GAC_BAD_CID		128

#define MIR_END_APPLICATION_PERFORM_TRANSACTION_TEARING_RECOVERY			129
#define MIR_END_APPLICATION_PERFORM_TRANSACTION_RECOVERY_LIMIT				130
#define MIR_END_APPLICATION_PERFORM_TRANSACTION_BAD_SW						131
#define MIR_END_APPLICATION_COMPLETE_TRANSACTION_TEARING_RECOVERY			132
#define MIR_END_APPLICATION_COMPLETE_TRANSACTION_RECOVERY_LIMIT				133
#define MIR_END_APPLICATION_COMPLETE_TRANSACTION_BAD_SW						134
#define MIR_END_APPLICATION_READY_RECORD_TEARING_RECOVERY					135
#define MIR_END_APPLICATION_READY_RECORD_RECOVERY_LIMIT						136

//MIR 
#define MIR_PERFORM_TRANSACTION_NO_RESPONSE									138
#define MIR_READY_RECORD_NO_RESPONSE										139




#define QVSDC_ZERO_AMT_GO_ONLINE			EMV_TRUE 
#define QVSDC_ZERO_AMT_GO_OTHERINTERFACE	EMV_FALSE 

#define AMEX_ZERO_AMT_GO_ONLINE				EMV_TRUE 
#define AMEX_ZERO_AMT_GO_OTHERINTERFACE		EMV_FALSE 

#define AMEX_STATUS_CHECK_GO_ONLINE			EMV_TRUE 
#define AMEX_STATUS_CHECK_GO_OTHERINTERFACE EMV_FALSE 

#define FDDA_VERSION_00		0x00
#define FDDA_VERSION_01		0x01


#define PICC_QPBOC						1
#define PICC_MASTER						2
#define PICC_QVSDA						3
#define BCTC_MODE                       EMV_FALSE


// 小微商户 错误返回值
#define OTHER_ERROR_BASE 300
// 选择错误
#define APP_SELECT_ERROR_6300 0x6300
#define APP_SELECT_ERROR_63C1 0x63C1
#define APP_SELECT_ERROR_6983 0x6983
#define APP_SELECT_ERROR_6984 0x6984
#define APP_SELECT_ERROR_6985 0x6985
#define APP_SELECT_ERROR_6A83 0x6A83
#define APP_SELECT_ERROR_6A88 0x6A88
#define APP_SELECT_ERROR_6283 0x6283
#define APP_SELECT_ERROR_6400 0x6400
#define APP_SELECT_ERROR_6500 0x6500
#define APP_SELECT_ERROR_9001 0x9001
#define APP_SELECT_ERROR_6A82 0x6A82
#define APP_SELECT_ERROR_NO_DOL OTHER_ERROR_BASE-1
#define APP_SELECT_ERROR_NO_9F66 OTHER_ERROR_BASE-2
// gpo返错误
#define APP_GPO_ERROR_6300 0x6300
#define APP_GPO_ERROR_63C1 0x63C1
#define APP_GPO_ERROR_6983 0x6983
#define APP_GPO_ERROR_6984 0x6984
#define APP_GPO_ERROR_6986 0x6986
#define APP_GPO_ERROR_6A81 0x6A81
#define APP_GPO_ERROR_6985 0x6985
#define APP_GPO_ERROR_6A83 0x6A83
#define APP_GPO_ERROR_6A88 0x6A88
#define APP_GPO_ERROR_6283 0x6283
#define APP_GPO_ERROR_6400 0x6400
#define APP_GPO_ERROR_6500 0x6500
#define APP_GPO_ERROR_9001 0x9001
#define APP_GPO_ERROR_9408 0x9408
#define APP_GPO_ERROR_6A82 0x6A82
#define APP_GPO_ERROR_NO_82 OTHER_ERROR_BASE-3
#define APP_GPO_ERROR_NO_9F36 OTHER_ERROR_BASE-4
#define APP_GPO_ERROR_NO_57 OTHER_ERROR_BASE-5
#define APP_GPO_ERROR_NO_9F10 OTHER_ERROR_BASE-6
#define APP_GPO_ERROR_NO_9F26 OTHER_ERROR_BASE-7
#define APP_GPO_ERROR_CARD_DECLINE OTHER_ERROR_BASE-8
#define APP_GPO_ERROR_GPO OTHER_ERROR_BASE-9
#define APP_GPO_ERROR_SFI OTHER_ERROR_BASE-10

//
struct RISK_PARAM {
	//#1
	EMV_BOOL m_ActiveCTLCheck;// 非接交易限额检查
	EMV_UINT32 m_ContactlessTransLimit;// 非接脱机交易限额

	//#2
	EMV_BOOL m_ActiveCVMCheck;// 非接cvm限额
	EMV_UINT32 m_ContactlessCVMLimit;

	//#3
	EMV_BOOL m_ActiveCFLCheck;// 非接最多限额
	EMV_BOOL m_ContactlessFloorLimitExist;
	EMV_BOOL m_FloorlimitCheck;
	EMV_UINT32 m_ContactlessFloorLimit;
	EMV_UINT32 m_FloorLimit;

	//#4
	EMV_BOOL m_ActiveStatusCheck;
	EMV_BOOL m_ActiveStatusPath;

	//#5
	EMV_BOOL m_ActiveZeroAmtCheck;// 零金额检查
	EMV_BOOL m_ZeroAmtPath;
};

typedef struct RISK_PARAM QVSDC_RISK_PARAM;

//
struct RISK_RESULT {
	EMV_BOOL m_isMatched;// 是否全匹配
	EMV_BOOL m_AppNotAllowFlag;// 应用是否允许
	EMV_BOOL m_RequireOnlineFlag;// 请求联机
	EMV_BOOL m_RequireCVMFlag;// 请求cvm
};

typedef struct RISK_RESULT QVSDC_RISK_RESULT;
typedef struct RISK_RESULT * LP_QVSDC_RISK_RESULT;

//
struct RISK_PARAM_FOR_TRANS {
	EMV_BYTE m_TransType;
	QVSDC_RISK_PARAM m_RiskParam;
	QVSDC_RISK_RESULT m_RiskResult;
};

typedef struct RISK_PARAM_FOR_TRANS QVSDC_RISK_PARAM_FOR_TRANS;

//
struct DYNAMIC_READER_LIMIT {
	EMV_BOOL m_Active;
	EMV_BYTE m_AppProgrameID[SIZE_APP_PROGRAM_ID];
	EMV_UINT32 m_APIDLen;
	QVSDC_RISK_PARAM m_RiskParam;
	QVSDC_RISK_RESULT m_RiskResult;
};

typedef struct DYNAMIC_READER_LIMIT QVSDC_DRL;
typedef struct DYNAMIC_READER_LIMIT * LP_QVSDC_DRL;

typedef struct{
	// 1140
	EMV_BOOL m_Support_QVSDC;// visa
	EMV_BOOL m_Support_Contact; // 接触
	EMV_BOOL m_Offline_Only;  // 仅脱机
	EMV_BOOL m_Online_Only;  // 仅联机
	EMV_BOOL m_Support_Online_PIN;  // 联机PIN
	EMV_BOOL m_Support_Signature;  // 签名
	EMV_BOOL m_Support_Online_ODA;  // 联机oda
	EMV_BOOL m_Support_MSD;
	EMV_BOOL m_Support_IssuerScriptUpdate;  // 发卡行脚本更新
	EMV_BOOL m_Support_CDCVM;  // 
	EMV_BOOL m_Support_ExceptionFile;  // 黑名单检查

	EMV_BOOL m_Support_CASH;  // 现金
	EMV_BOOL m_Support_CASHBACK;  // 返现
	EMV_BOOL m_Support_REFUND;   // 退货
	EMV_BOOL m_Support_DRL; // 动态读限检查

	EMV_BOOL m_Support_ProcRestriction_CASH; // 处理限制金额
	EMV_BOOL m_Support_ProcRestriction_CASHBACK; // 处理限制返回金额

	EMV_BOOL m_Support_FDDA;
	EMV_BOOL m_Support_SDA;
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Default; // 默认
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Cash; // 金额
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Cashback; // 返现
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Purchase; // 购买
	QVSDC_DRL m_DRL[MAX_DRL + 1];
}QVSDC_PARAMETER;

typedef QVSDC_PARAMETER QVSDC_PARAM;
typedef QVSDC_PARAMETER * LP_QVSDC_PARAM;


typedef struct  {
	EMV_BOOL m_Support_PBOC; // 借贷记
	EMV_BOOL m_Support_QPBOC; // QPBOC
	EMV_BOOL m_Support_Contactless; // 接触
	EMV_BOOL m_Offline_Only; // 只支持脱机
	EMV_BOOL m_Support_Online_PIN; // 联机PIN
	EMV_BOOL m_Support_Signature; // 签名
	EMV_BOOL m_Support_Online_ODA; // 联机oda
	EMV_BOOL m_Support_Status_Check; // 终端是否支持状态检查，缺省为关闭
	EMV_BOOL m_Support_CDCVM; // 
	EMV_BOOL m_Support_ExceptionFile; // 黑名单检查
	EMV_BOOL m_Support_SM; // 是否支持国密
	EMV_BOOL m_Support_Get_Data_9F51_DF71;
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Default;
}QPBOC_PARAMETER;

typedef QPBOC_PARAMETER QPBOC_PARAM;
typedef QPBOC_PARAMETER * LP_QPBOC_PARAM;

typedef struct  {
	EMV_BOOL m_Support_Express;
	EMV_BOOL m_Support_Contactless;

	EMV_BOOL m_Offline_Only;
	EMV_BOOL m_Online_Only;
	
	EMV_BOOL m_Support_Magstripe_Mode;
	EMV_BOOL m_Support_Emv_Mode; 
	EMV_BOOL m_Support_Delayed_Authorisations; //联机ODA
	
	EMV_BOOL m_Support_Status_Check;
	
	EMV_BOOL m_Support_Online_PIN;
	EMV_BOOL m_Support_Signature;
	EMV_BOOL m_Support_Mobile_Cvm;
	
	EMV_BOOL m_Support_Alternative_Interface;// 
	
	EMV_BOOL m_Support_ExceptionFile;
	EMV_BOOL m_Support_DRL;

	EMV_BOOL m_Support_TerminalOfflineOnly;

	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Default;
	QVSDC_DRL m_DRL[MAX_DRL + 1];
} EXPRESS_PARAMETER;

typedef EXPRESS_PARAMETER EXPRESS_PARAM;
typedef EXPRESS_PARAMETER * LP_EXPRESS_PARAMETER;

typedef struct {
	EMV_BOOL m_Support_Magstripe_Mode;
	EMV_BOOL m_Support_Emv_Mode;
	EMV_BOOL m_Support_Contact;
	EMV_BOOL m_Offline_Only;
	EMV_BOOL m_Support_Online_PIN;
	EMV_BOOL m_Support_Signature;
	EMV_BOOL m_Support_IssuerScriptUpdate;
	EMV_BOOL m_Support_CDCVM;
	EMV_BOOL m_Support_Status_Check; // EMV_TRUE ZIP 模式 , EMV_FALSE D-PAS 模式 
									 // 认证才会使用,正式模式 是执行 D-PAS 模式.
	//CL-ACO
	EMV_BOOL m_Supported_DCVV; //默认打开

	EMV_BOOL m_Support_Alternative_Interface;
	EMV_BOOL m_Support_ExceptionFile;
	QVSDC_RISK_PARAM_FOR_TRANS m_RiskParam_Default;
} DISCOVER_PARAMETER;

typedef DISCOVER_PARAMETER DISCOVER_PARAM;
typedef DISCOVER_PARAMETER * LP_DISCOVER_PARAM;



typedef struct{
	EMV_BOOL m_Support_Contactless;
	EMV_BOOL m_Offline_Only;
	EMV_BOOL m_Support_Online_PIN;
	EMV_BOOL m_Support_Signature;
	EMV_BOOL m_Support_CDCVM;
	EMV_BOOL m_Delayed_Authorization;
	EMV_BOOL m_Support_ExceptionFile;
	EMV_BOOL m_Unable_Online;
		
	//#1
	EMV_BOOL m_ActiveCTLCheck;
	EMV_UINT32 m_ContactlessTransLimit_NoCvm;
	EMV_UINT32 m_ContactlessTransLimit_Cvm;

	//#2
	EMV_BOOL m_ActiveCVMCheck;
	EMV_UINT32 m_ContactlessCVMLimit;

	//#3
	EMV_BOOL m_ActiveCFLCheck;
	EMV_BOOL m_ContactlessFloorLimitExist;
	EMV_BOOL m_FloorlimitCheck;
	EMV_UINT32 m_ContactlessFloorLimit;
	EMV_UINT32 m_FloorLimit;

	//#4
	EMV_UINT32 m_TransactionRecoveryLimit;

	QVSDC_RISK_RESULT m_RiskResult;
} MIR_PARAMETER;

typedef MIR_PARAMETER MIR_PARAM;
typedef MIR_PARAMETER * LP_MIR_PARAM;

typedef struct{
	//EMV 模式
	EMV_BOOL m_Support_Online_PIN;
	EMV_BOOL m_Support_Signature;
	EMV_BOOL m_Support_NO_CVM;
	
	//MS 模式
	EMV_BOOL m_Support_MS_Online_PIN;
	EMV_BOOL m_Support_MS_Signature;
	EMV_BOOL m_Support_MS_NO_CVM;

	//#1
	EMV_UINT32 m_ContactlessFloorLimit;
	EMV_UINT32 m_ContactlessTransLimitOdCvm;
	EMV_UINT32 m_ContactlessTransLimitNoODCvm;
	EMV_UINT32 m_ContactlessCVMLimit;
	
} MASTRT_PARAMETER;

typedef MASTRT_PARAMETER MASTRT_PARAM;
typedef MASTRT_PARAMETER * LP_MASTRT_PARAM;


enum KERNEL_VERSION{
	KERNEL_VERSION_DEFAULT, // 通用 版本
	KERNEL_VERSION_CERTIFIED, //认证 版本
	KERNEL_VERSION_QUICS, // QUICS 版本
	KERNEL_VERSION_QPBOC,  // QPBOC 版本
	KERNEL_VERSION_QR,//小微商户 测试版本
	KERNEL_VERSION_VISA,
	KERNEL_VERSION_AMEX,
	KERNEL_VERSION_DISCOVER,
	KERNEL_VERSION_MIR // 俄罗斯项目
};

enum KERNEL_START{
	START_CODE_A,
	START_CODE_B,
	START_CODE_C,
	START_CODE_D,
	START_CODE_NA
}; //内核启动状态

typedef enum KERNEL_VERSION KERNEL_VERSION_TYPE;

typedef enum KERNEL_START KERNEL_START_TYPE;
#ifdef __cplusplus
extern "C" {
#endif

typedef EMV_BYTE QVSDC_BREAK_SOURCE;
#define QVSDC_BS_NONE    0x00
#define QVSDC_BS_CONTACT 0x01
#define QVSDC_BS_SWIPE	 0x02

#define TERM_SUPPROT_SM  0x01 //是否支持国密算法

typedef QVSDC_BREAK_SOURCE (*Fn_QVSDC_DetectBreak)(EMV_UINT32 uiCallBackHandle);

EMV_API EMV_UINT32 Set_KernelApplyAid(EMV_UINT8 parameter);


EMV_API EMV_UINT32 QVSDC_Parameter(LP_QVSDC_PARAM parameter);
// 设置QPBOC交易相关参数
EMV_API EMV_UINT32 QPBOC_Parameter(LP_QPBOC_PARAM parameter);

EMV_API EMV_UINT32 AMEX_Parameter(LP_EXPRESS_PARAMETER parameter);

EMV_API EMV_UINT32 DISCOVER_Parameter(LP_DISCOVER_PARAM parameter);

EMV_API EMV_UINT32 MIR_Parameter(LP_MIR_PARAM parameter);

EMV_API EMV_UINT32 MASTRT_Parameter(LP_MASTRT_PARAM parameter);

EMV_API EMV_UINT32 Kernel_Parameter(KERNEL_VERSION_TYPE kernelVersionType,
	KERNEL_START_TYPE StartCode);

EMV_API EMV_UINT32 Kernel_PreProcessing(EMV_UINT32 uiTarnsCounter,
		EMV_BYTE TransType, EMV_UINT32 Amount, EMV_UINT32 AmountOther);

EMV_API EMV_UINT32 Kernel_Transaction(Fn_QVSDC_DetectBreak pFnDetectBreak);

#ifdef __cplusplus
}
#endif
#endif
