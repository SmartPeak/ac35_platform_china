#ifndef EMVKERNEL_H_
#define EMVKERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "EmvDataType.h"

//编译版本. EMV 模式 商用版本. 其他模式 用于认证. 

#define COMPILE_KERNEL_EMV 			1	 
//#define COMPILE_KERNEL_QUICS			1	
//#define COMPILE_KERNEL_VISA				1		
//#define COMPILE_KERNEL_MASTERCARD			1	  
//#define COMPILE_KERNEL_DISCOVER			1	  
//#define COMPILE_KERNEL_EXPRESS  		1	
//#define COMPILE_KERNEL_MIR				1
//#define COMPILE_KERNEL_JCB  			1	

typedef LP_EMV_VOID * LP_EMV_HANDLE;
typedef LP_EMV_VOID EMV_HANDLE;

#define SUPPORT_VISA
//#define SUPPORT_MASTERCARD
//#define SUPPORT_DISCOVER
//#define SUPPORT_EXPRESS
//#define SUPPORT_MIR				//俄罗斯 MIR卡	
//#define SUPPORT_JCB			//目前不支持JCB.


#define EMV_API

//#define PRT() printf("file[%s]--function[%s()]--line[%d]\n", __FILE__, __FUNCTION__, __LINE__)

#define AMEX_APPROVED			29
#define AMEX_FORCE_APPROVED     30
#define AMEX_DECLINED			31
#define AMEX_DELAYED_APPROVED	32
#define AMEX_ATC_DELAYED        34

#define DISCOVER_TRY_ANOTHER_INTERFACE 33
#define DISCOVER_CARD_EXPIRED   37

#define QVSDC_ONLINE_ODA_FAILED 36 //visa 联机ODA 缺少数据 不进行处理.

#define QPBOC_EXPIRATION_OVERDUE_ONLINE  38//卡片交易属性9F6C第1字节第4位为1,应转入联机流程,并提示"卡片过有效期,交易联机"
#define QPBOC_EXPIRATION_OVERDUE_REFUSE  39//卡片交易属性9F6C第1字节第4位为0,应拒绝交易,并提示"卡片过有效期,交易拒绝"
#define QPBOC_OTHER_INTERFACE_CL		 40//转接触界面.

#define EMV_KERNEL_NOT_SUPPORT			 41//内核不支持.

#define EMV_OK					0
#define EMV_APPROVED_OFFLINE    1  // 脱机接受
#define EMV_APPROVED_ONLINE     2	// 联机接受
#define EMV_DECLINED_OFFLINE    3	// 脱机拒绝
#define EMV_DECLINED_ONLINE     4	// 联机拒绝
#define EMV_NO_ACCEPTED         6	// 不接受
#define EMV_TERMINATED			7	//  终端错误
#define EMV_CARD_BLOCKED        8	// 卡片被锁
#define EMV_APP_BLOCKED         9	// 应用锁
#define EMV_NO_APP              10	// 无应用

#define EMV_CAPK_EXPIRED        11 // 公钥过期
#define EMV_CAPK_CHECKSUM_ERROR 12 // 公钥校验错
#define EMV_AID_DUPLICATE       13 // 应用重复

#define EMV_CERTIFICATE_RECOVER_FAILED 14 // 证书恢复错
#define EMV_DATA_AUTH_FAILED     15 // 认证失败

#define EMV_UN_RECOGNIZED_TAG	16 // 无效tag
#define EMV_DATA_NOT_EXISTS     17 // 数据不存在
#define EMV_DATA_LENGTH_ERROR   18 // 数据长度错
#define EMV_INVALID_TLV         19 // 无效tlv
#define EMV_INVALID_RESPONSE    20 // 无效响应
#define EMV_DATA_DUPLICATE      21 // 数据重复

#define EMV_MEMORY_NOT_ENOUGH	22 // 内存不足
#define EMV_MEMORY_OVERFLOW		23 // 内存溢出
#define EMV_PARAMETER_ERROR     24 // 参数错
#define EMV_ICC_ERROR           25 // icc错误

#define EMV_NO_MORE_DATA        26 // 无更多数据
#define EMV_CAPK_NO_FOUND       27 // 公钥没找到

#define EMV_APP_NOT_ALLOW		28
#define EMV_END_TRANSACTION		29
#define EMV_READ_CARD_LOG       31
#define EMV_CL_TRANS_LIMIT_OVER 32

#define EMV_OTHER_ERROR         255

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef EMV_BYTE EMV_CDA_METHOD;// cda ??
#define	EMV_CDA_MODE1 0x00 //CDA on ARQC _ Req, CDA on 2nd GenAC TC after approved Online authorization
#define	EMV_CDA_MODE2 0x01 //CDA on ARQC _ No Req CDA on 2 2nd Gen Ac TC after appproved online authorization
#define	EMV_CDA_MODE3 0x02 //No Req. CDA on ARQC + No Req CDA on 2nd GenAc after approved Online authorization
#define	EMV_CDA_MODE4 0x03 //No Req CDA on ARQC + req CDA on 2nd GenAcC after approved Online Authorization
typedef EMV_BYTE EMV_DEFAULT_ACTION_CODE_METHOD; // 默认行为代码方式
#define EMV_DEFAULT_ACTION_CODE_BEFOR_GAC1 0x00
#define EMV_DEFAULT_ACTION_CODE_AFTER_GAC1 0x01

#define	EMV_TRANS_TYPE_GOODS_SERVICE 	0x00	//POS机一般交易都用这个类型 服务
#define	EMV_TRANS_TYPE_CASH			 0x01	//取现，一般用于ATM机
#define 	EMV_TYPE_AUTH					0x03	//预授权
//商户活动，购100元商品，当场返现10，这种交易就是反现，需要输入100和10两个金额
#define	EMV_TRANS_TYPE_CASHBACK		 0x09	 // 返现

#define	EMV_TRANS_TYPE_INQUIRY		 0x31 // 查询
#define	EMV_TRANS_TYPE_TRANSFER		 0x11 // 转让
#define	EMV_TRANS_TYPE_PAYMENT		 0x12 // 付款
#define	EMV_TRANS_TYPE_ADMIN  		 0x13 // 管理
#define	EMV_TRANS_TYPE_DEPOSIT       0x21 // 存款

#define 	EMV_TRANS_TYPE_EC_CASE_LOAD	0x63 // 现金现金圈存
#define 	EMV_TRANS_TYPE_EC_DEFINED_ACCOUNT_LOAD	0x60  // 电子现金指定圈存
#define 	EMV_TRANS_TYPE_EC_UNDEFINED_ACCOUNT_LOAD	0x62 // 电子现金非指定圈存

typedef EMV_BYTE EMV_ONLINE_RESULT;
#define	EMV_ONLINE_APPROVED         0x00 // 联机批准
#define	EMV_ONLINE_REJECT			0x01 // 联机拒绝
#define	EMV_ONLINE_VOICE_PREFER		0x02 // 联机语言优先
#define	EMV_ONLINE_ERROR			0x03 // 联机错误
#define	EMV_ONLINE_TIME_OUT			0x04 // 联机超时
#define	EMV_ONLINE_CONNECT_FAILED	0x05 // 联机连接失败
#define EMV_ONLINE_NULL				0xFF // 

#define PBOC_SIMPLE_PROC 			0			//PBOC 简单流程
#define PBOC_SIMPLE_PROC_AUTH		1			//PBOC简单流程带离线数据认证
typedef EMV_ONLINE_RESULT * LP_EMV_ONLINE_RESULT;
/************************************************************************/
/*                                                                      */
/************************************************************************/
enum KERNEL_MODE{
	KERNEL_NOT = 0x00,
	KERNEL_QUICS,
	KERNEL_VISA,
	KERNEL_MASTERCARD,
	KERNEL_DISCOVER,
	KERNEL_EXPRESS,
	KERNEL_JCB,
	KERNEL_MIR,  
	KERNEL_EMV_ICC
};
typedef enum KERNEL_MODE KERNEL_MODE_TYPE;
typedef enum KERNEL_MODE * LP_KERNEL_MODE_TYPE;

/************************************************************************/
/*  定义内核交易过程中产生界面                                          */
/************************************************************************/
enum KERNEL_VIEW_MODE{
	KERNEL_VIEW_REMOVE_CARD,
	KERNEL_VIEW_ONLINE_DDA_SUCCESS,
	KERNEL_VIEW_ONLINE_DDA_FAIL,
	KERNEL_VIEW_ONLINE_SDA_SUCCESS,
	KERNEL_VIEW_ONLINE_SDA_FAIL

};

typedef enum KERNEL_VIEW_MODE KERNEL_VIEW_MODE_TYPE;

typedef struct {
	EMV_UINT16 m_Year;
	EMV_UINT8 m_Month;
	EMV_UINT8 m_Day;
	EMV_UINT8 m_Hour;
	EMV_UINT8 m_Minute;
	EMV_UINT8 m_Second;
}EMV_TIME;

typedef EMV_TIME * LP_EMV_TIME;

typedef struct  {
	// 48
	EMV_BOOL m_PSE;//是否支持PSE选择方式
	EMV_BOOL m_CardHolderConfirm;//是否支持持卡人确认
	EMV_BOOL m_PreferredDisplayOrder; //NO implemented,按照终端配置的AID顺序显示
	EMV_BOOL m_LanguateSelect;// 是否支持多语言 
	EMV_BOOL m_RevocationOfIssuerPublicKey;//检查发卡行公钥回收 
	EMV_BOOL m_Default_DDOL;//是否支持默认DDOL  
	EMV_BOOL m_Bypass_PIN_Entry;//是否支持绕过pin输入(直接确定) 
	EMV_BOOL m_Subsequent_Bypass_PIN_Entry;// 跳过后续pin
	EMV_BOOL m_Getdata_For_PIN_Try_Counter;// 获取pin尝试次数
	EMV_BOOL m_Floor_Limit_Checking;// 最低限额检查
	EMV_BOOL m_Random_Transaction_Selection; //是否进行随机交易选择
	EMV_BOOL m_Velocity_Checking;// 频度检查
	EMV_BOOL m_TransactionLog;//
	EMV_BOOL m_Exception_File;// 异常文件检查
	EMV_BOOL m_TerminalActionCode;// 是否支持tac
	EMV_DEFAULT_ACTION_CODE_METHOD m_DefaultActionCodeMethod;
	EMV_BOOL m_TAC_IAC_Default_SkipedWhenUnableToGoOnline;
	EMV_BOOL m_CDA_FailureDetectedPriorTerminalActionAnalysis;

	EMV_CDA_METHOD m_CDA_Method;

	EMV_BOOL m_ForcedOnline;// 强制联机
	EMV_BOOL m_ForcedAcceptance;// 强制接受
	EMV_BOOL m_Advices;// 通知
	EMV_BOOL m_Issuer_Referral;// 是否支持发卡行参考
	EMV_BOOL m_BatchDataCapture;// 批上送捕获
	EMV_BOOL m_OnlineDataCapture;// 联机捕获
	EMV_BOOL m_Default_TDOL;// 默认tdol
	EMV_BOOL m_Terminal_SupportAccountTypeSelection; //No Implemented

	EMV_CHAR m_TerminalType[SIZE_TERMINAL_TYPE * 2 + 1];//终端类型
	EMV_CHAR m_TerminalCapabilities[SIZE_TERMINAL_CAPABILITIES * 2 + 1];// 终端性能
	EMV_CHAR m_AddtionalTerminalCapabilities[SIZE_ADDTIONAL_TERMINAL_CAPABILITIES * 2 + 1];// 终端扩展性能

}EMV_KERNEL_CONFIG;

typedef  EMV_KERNEL_CONFIG * LP_EMV_KERNEL_CONFIG;
typedef const  EMV_KERNEL_CONFIG * LPC_EMV_KERNEL_CONFIG;


typedef struct {
	// 315
	EMV_CHAR m_TerminalID[SIZE_TERMINAL_ID + 1]; //终端标志(POS号)m_TermId
	EMV_CHAR m_IFDSerialNumber[SIZE_IFD_SERIAL_NUMBER + 1];// m_IFDSerialNumber接口设备序列号
	EMV_CHAR m_TerminalCountryCode[SIZE_COUNTRY_CODE * 2 + 1];//m_CountryCode终端国家代码
	EMV_CHAR m_Merchant_ID[SIZE_MERCHANT_ID + 1];//商户标志(商户号)m_MerchId
	EMV_CHAR m_Merchant_Category_Code[SIZE_MERCHANT_CATEGORY_CODE * 2 + 1];//m_MerchCateCode商户类别码(没要求可不设置)
	EMV_CHAR m_Merchant_Location[SIZE_MERCHANT_LOCATION + 1];//商户名m_MerchName
	EMV_CHAR m_Trans_Currency_Code[SIZE_TRANS_CURRENCY_CODE * 2 + 1];//交易货币代码m_TransCurrCode
	EMV_UINT8 m_Trans_Currency_Exp;//交易货币代码指数m_TransCurrExp
	EMV_CHAR m_Trans_Ref_Currency_Code[SIZE_TRANS_CURRENCY_CODE * 2 + 1];//m_ReferCurrCode 参考货币代码
	EMV_UINT8 m_Trans_Ref_Currency_Exp;//参考货币指数m_ReferCurrExp
	EMV_CHAR m_TerminalEntryMode[SIZE_TERMINAL_ENTRY_MODE * 2 + 1]; //pos输入方式 

	// add by wl 
	EMV_UINT32 m_ReferCurrCon; //参考货币代码和交易代码的转换系数(交易货币对参考货币的汇率*1000)

}EMV_TERMINAL_INFO;

typedef  EMV_TERMINAL_INFO * LP_EMV_TERMINAL_INFO;
typedef const  EMV_TERMINAL_INFO * LPC_EMV_TERMINAL_INFO;

// 定义pin的返回值类型
typedef enum{
	CV_VERIFY_SUC = 0,
	CV_VERIFY_NO_PINPAD,// 没密码键盘或键盘不可用 1
	CV_VERIFY_NO_PASSWORD,// 没密码或用户忽略了密码输入 2
	CV_VERIFY_PIN_ERROR, // 密码错误 63cx 3
	CV_VERIFY_PIN_BLOCK,// pin被锁定 4
	// 这4个退出流程
	CV_VERIFY_TIME_OUT,// 输入超时 5
	CV_VERIFY_USER_CANCEL,// 用户取消 6
	CV_VERIFY_ICC_CMD_ERR,// 命令错 7
	CV_VERIFY_RSP_ERR,// 响应错误 8

	CV_CERIFY_CERT_ERR,// 持卡人证件错误 9
	CV_CERIFY_DEFAULT_ERR,// 默认失败值 10
}EMV_CV_VERIFY_RESULT;

typedef EMV_CV_VERIFY_RESULT * LP_EMV_CV_VERIFY_RESULT;

/************用于脱机密文pin验证**************/
typedef struct
{
	EMV_INT32 uiCardRnd;
	EMV_BYTE bCardRng[MAX_CARD_RANDOM];// 卡片随机数
	EMV_INT32 uiPubExp;
	EMV_BYTE bPubExp[MAX_RSA_EXPONENTS];// 加密公钥指数
	EMV_INT32 uiPubMod;
	EMV_BYTE bPubMod[MAX_RSA_MODULES];// 加密公钥模
}PIN_OFF_CIPHER_ITEM;

typedef PIN_OFF_CIPHER_ITEM * LP_PIN_OFF_CIPHER_ITEM;


// 磁条卡的结构体
typedef struct {
	EMV_BOOL m_TrackExistFlag;// 磁道数据存在的标志位
	EMV_BOOL m_FallBackFlag;// 降级的标志位
	EMV_BYTE m_Track1[MAX_MAG_TRACK1];
	EMV_BYTE m_Track2[MAX_MAG_TRACK2];
	EMV_BYTE m_Track3[MAX_MAG_TRACK3];
}MAG_TRACK_DATA;

typedef MAG_TRACK_DATA *LP_MAG_TRACK_DATA;

/*************************定义回调**************************************/
typedef EMV_VOID (*Fn_EMV_Log_Print)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_CHAR pszFmt,EMV_UINT32 len);
typedef EMV_VOID (*Fn_EMV_GetCurrentTime)(EMV_UINT32 uiCallbackHandle,
		LP_EMV_TIME pCurrentTime);
typedef EMV_VOID (*Fn_EMV_GenerateRandomData)(EMV_UINT32 uiCallbackHandle,
		LP_EMV_BYTE pRandBuff, EMV_UINT16 uiSize);

typedef EMV_BOOL (*Fn_EMV_ExchangeApdu)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_BYTE pApdu, EMV_UINT16 uiApdu, LP_EMV_BYTE pResp,
		LP_EMV_UINT16 puiResp);
typedef EMV_BOOL (*Fn_EMV_IsCashBackTrans)(EMV_UINT32 uiCallbackHandle,
		EMV_BYTE bTransType);
typedef EMV_BOOL (*Fn_EMV_IsCashTrans)(EMV_UINT32 uiCallbackHandle,
		EMV_BYTE bTransType);
typedef EMV_BOOL (*Fn_EMV_IsGoodsServiceTrans)(EMV_UINT32 uiCallbackHandle,
		EMV_BYTE bTransType);

typedef EMV_BOOL (*Fn_EMV_SelectApplication)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_CHAR * ppAppNames, LPC_EMV_CHAR * ppAppAids,
		EMV_UINT16 uiAppCount, LP_EMV_UINT16 puiSelected);

typedef EMV_VOID (*Fn_EMV_AfterAppSelected)(EMV_UINT32 uiCallbackHandle);
typedef EMV_BOOL (*Fn_EMV_CardHolderConfirm)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_CHAR pAID, LPC_EMV_CHAR pAppName, LPC_EMV_CHAR pPreferAppName);
typedef EMV_BOOL (*Fn_EMV_TryOtherApplication)(EMV_UINT32 uiCallbackHandle);
typedef EMV_BOOL (*Fn_EMV_LanguageSelect)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_CHAR pszLanguages, EMV_BOOL bIsPSESelect);
typedef EMV_BOOL (*Fn_EMV_EnterAmount)(EMV_UINT32 uiCallbackHandle,
		LP_EMV_UINT32 pAmount, LP_EMV_UINT32 pAmountOther);
/*

 typedef EMV_BOOL   (*Fn_EMV_CheckExceptionFile)(EMV_UINT32 uiCallbackHandle,
 LPC_EMV_CHAR pszPAN,
 LPC_EMV_CHAR pszPANSeq
 );
 typedef EMV_BOOL   (*Fn_EMV_GetCAPK)(EMV_UINT32 uiCallbackHandle,
 LPC_EMV_CHAR pszRID,
 LPC_EMV_CHAR pszIndex,
 LP_EMV_CHAR  pszModules,
 EMV_UINT32   uiModulesSize,
 LP_EMV_CHAR  pszExponents,
 EMV_UINT32   uiExponents);
 */
typedef EMV_UINT32 (*Fn_EMV_GetTransLogAmount)(EMV_UINT32 uiCallbackHandle,
		LPC_EMV_CHAR pszPAN, LPC_EMV_CHAR pszPANSeq);
typedef EMV_BOOL (*Fn_EMV_GetPlainTextPin)(EMV_UINT32 uiCallbackHandle,
		EMV_BOOL bAllowBypass, LP_EMV_CHAR pszPIN, EMV_UINT16 uiPinBuffSize,
		LP_EMV_BOOL pbBypass);
typedef EMV_BOOL (*Fn_EMV_GetOnlinePin)(EMV_UINT32 uiCallbackHandle,
		EMV_BOOL bAllowBypass, LPC_EMV_CHAR pszPAN, LP_EMV_CHAR pszPinBlock,
		EMV_UINT16 uiPinBlockBuffSize, LP_EMV_BOOL pbBypass);
typedef EMV_BOOL (*Fn_EMV_Display_Pin_Verify_Status)(
		EMV_UINT32 uiCallBackHandle, EMV_UINT8 uiRetryTimes);
typedef EMV_BOOL (*Fn_EMV_Check_Credentials)(EMV_UINT32 uiCallbackHandle,
		EMV_BYTE bCredentialsType, LPC_EMV_CHAR pszCredentialNumber,
		LP_EMV_BOOL pCheckSuccess);

typedef EMV_VOID (*Fn_EMV_Display_Trans_Report)(EMV_UINT32 uiCallBackHandle,
		EMV_INT32 uiErrorCode, EMV_BOOL bSignatureNeeded);
typedef EMV_VOID (*Fn_EMV_AskRemoveCard)(EMV_UINT32 uiCallbackHandle);

typedef EMV_VOID (*Fn_EMV_AuthorisationRequest)(EMV_UINT32 uiCallBackHandle,
		LPC_EMV_CHAR pszOnlineEncipherPIN, LP_EMV_ONLINE_RESULT pOnlineResult,
		LP_EMV_CHAR pszIssueAuthData, EMV_UINT16 uiIssueAuthDataBuffSize,
		LP_EMV_CHAR pszARC, EMV_UINT16 uiARCBuffSize,
		LP_EMV_CHAR pszIssuerAuthCode, EMV_UINT16 uiIssuerAuthCode,
		LP_EMV_CHAR pszIssueScript, EMV_UINT16 uiScriptBuffSize);
typedef EMV_VOID (*Fn_EMV_FinacialTransactionRequest)(
		EMV_UINT32 uiCallBackHandle, LPC_EMV_CHAR pszOnlineEncipherPIN,
		LP_EMV_ONLINE_RESULT pOnlineResult, LP_EMV_CHAR pszIssueAuthData,
		EMV_UINT16 uiIssueAuthDataBuffSize, LP_EMV_CHAR pszARC,
		EMV_UINT16 uiARCBuffSize, LP_EMV_CHAR pszIssuerAuthCode,
		EMV_UINT16 uiIssuerAuthCode, LP_EMV_CHAR pszIssueScript,
		EMV_UINT16 uiScriptBuffSize);
typedef EMV_VOID (*Fn_EMV_FinancialTransactionConfirmation)(
	EMV_UINT32 uiCallBackHandle, EMV_INT32 uiErrorCode);
typedef EMV_VOID (*Fn_EMV_BatchDataCapture)(EMV_UINT32 uiCallBackHandle,
		EMV_BOOL bAdvice, EMV_BOOL bForceAccept, EMV_BOOL bOnlineDataCapture);
typedef EMV_VOID (*Fn_EMV_Reversal)(EMV_UINT32 uiCallBackHandle);
typedef EMV_VOID (*Fn_EMV_OnlineAdvice)(EMV_UINT32 uiCallBackHandle,
	EMV_BOOL bForceAccept, LPC_EMV_CHAR pOnlinePIN);
typedef EMV_BOOL (*Fn_EMV_Issuer_Referral)(EMV_UINT32 uiCallBackHandle,
		LPC_EMV_CHAR pszPAN);
typedef EMV_BOOL (*Fn_EMV_SecondTapCard)(EMV_UINT32 uiCallBackHandle);

typedef EMV_VOID(*Fn_EMV_KernelMode)(EMV_UINT32 uiCallBackHandle, EMV_UINT32 uiKernelMode);

typedef EMV_VOID(*Fn_EMV_KernelViewMode)(EMV_UINT32 uiCallBackHandle, EMV_UINT32 uiKernelViewMode);

// 保存交易金额
typedef EMV_BOOL(*Fn_EMV_SaveTransLog)(EMV_UINT32 uiCallBackHandle, LP_EMV_BYTE bPanNo, EMV_INT32 uiPanNo, LP_EMV_BYTE bPanSeq, EMV_INT32 uiPanSeq, EMV_UINT32 pAuthAmt);

// 获取交易的金额
typedef EMV_UINT32(*Fn_EMV_GetTransLogAmt)(EMV_UINT32 uiCallBackHandle, LP_EMV_BYTE bPanNo, EMV_INT32 uiPanNo, LP_EMV_BYTE bPanSeq, EMV_INT32 uiPanSeq, EMV_UINT32 pAuthAmt);

// 脱机明文pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetPlainTextPin)(EMV_UINT32 uiCallbackHandle, EMV_BOOL bAllowBypass, LP_EMV_CHAR pszPIN,
	EMV_UINT16 uiPinBuffSize, EMV_CHAR bPinTryCnt, LP_EMV_INT32 bVerifyPinTryCnt, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 联机加密pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetOnlinePin)(EMV_UINT32 uiCallbackHandle,
	EMV_BOOL bAllowBypass, LPC_EMV_CHAR pszPAN, LP_EMV_CHAR pszPinBlock,
	EMV_UINT16 uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 脱机密文pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetOfflineCipherPin)(EMV_UINT32 uiCallbackHandle,EMV_BOOL bAllowBypass,
	LP_PIN_OFF_CIPHER_ITEM pPinCipherItem, EMV_CHAR bPinTryCnt, LP_EMV_INT32 bVerifyPinTryCnt,LP_EMV_CHAR pszPinBlock,
	EMV_UINT16 uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 持卡人证件验证
typedef EMV_BOOL(*Fn_EMV_Contact_GetHolderCert)(EMV_UINT32 uiCallbackHandle,
	LPC_EMV_CHAR pConfirmMsg, EMV_INT32 uiConfirmMsg, LPC_EMV_CHAR pHoldCert,
	EMV_INT32 uiHoldCert);

// 卡号确认
typedef EMV_BOOL(*Fn_EMV_Contact_PanConfirm)(EMV_UINT32 uiCallbackHandle,LPC_EMV_CHAR pPAN);

// 应用选择失败
typedef EMV_BOOL(*Fn_EMV_Contact_SelAppErr)(EMV_UINT32 uiCallbackHandle);

// 磁条卡的联机请求
typedef EMV_BOOL(*Fn_EMV_MagStripe_OnlineRequeset)(EMV_UINT32 uiCallbackHandle,
	LP_EMV_CHAR pOnlinePin, LP_EMV_CHAR pResCode);

/*
*验证国密证书是否成立
*pSMPubKey:国密公钥(64byte)
*bVerifyData:要验证的数据
*uiVerifyData:要验证的数据长
*bSignature:签名值
*uiSignature:签名长(63byte)
*/
typedef EMV_BOOL(*Fn_EMV_Contact_SM2VerifySign)(EMV_UINT32 uiCallbackHandle, LP_EMV_BYTE pSMPubKey, 
	LP_EMV_BYTE bVerifyData, EMV_INT32 uiVerifyData,LP_EMV_BYTE bSignature, EMV_INT32 uiSignature);

typedef EMV_BOOL(*Fn_EMV_Contact_SM3Hash)(EMV_UINT32 uiCallbackHandle, LP_EMV_BYTE pVerifySM3, 
	EMV_INT32 uiVerifySM3, LP_EMV_BYTE pSM3Hash, LP_EMV_INT32 uiSM3Hash);

// 再次检卡的返回值
typedef enum {
	CT_DETECT_MODE_NONE,
	CT_DETECT_MODE_IC,
	CT_DETECT_MODE_MAG,
} CT_DETECT_MODE; // 磁条卡状态

/*
接触内核检卡
bFallBackFlag:是否降级
bInsertCardFlag:是否需要插卡
pMagTrackData:如果是刷卡,则返回磁道数据
*/
typedef CT_DETECT_MODE(*Fn_EMV_Contact_DetectCard)(EMV_UINT32 uiCallbackHandle, EMV_CHAR bFallBackFlag,
	EMV_CHAR bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData);

/*
*接触用于显示卡号
*pPanNo:卡号
*/
typedef EMV_BOOL(*Fn_EMV_Contact_ShowPanNo)(EMV_UINT32 uiCallbackHandle, LP_EMV_CHAR pPanNo);

typedef struct  {
	EMV_UINT32 m_CallbackHandle;
	Fn_EMV_Log_Print m_Log_Print;
	Fn_EMV_GetCurrentTime m_GetCurrentTime;
	Fn_EMV_GenerateRandomData m_GenerateRandomData;

	Fn_EMV_ExchangeApdu m_ExchangeApdu;
	Fn_EMV_IsCashBackTrans m_IsCashBackTrans; //new
	Fn_EMV_IsCashTrans m_IsCashTrans; //new
	Fn_EMV_IsGoodsServiceTrans m_IsGoodsServiceTrans;

	Fn_EMV_SelectApplication m_SelectApplication;
	Fn_EMV_AfterAppSelected m_AfterAppSelected; //未使用
	Fn_EMV_CardHolderConfirm m_CardHolderConfirm;
	Fn_EMV_TryOtherApplication m_TryOtherApplication;

	Fn_EMV_LanguageSelect m_LanguageSelect;

	Fn_EMV_EnterAmount m_EnterAmount;
	Fn_EMV_GetTransLogAmount m_GetTransLogAmount;
	Fn_EMV_GetPlainTextPin m_GetPlainTextPin;
	Fn_EMV_GetOnlinePin m_GetOnlinePin;
	Fn_EMV_Display_Pin_Verify_Status m_Display_Pin_Verify_Status;
	Fn_EMV_Check_Credentials m_Check_Credentials;
	Fn_EMV_Display_Trans_Report m_Display_Trans_Report;
	Fn_EMV_AskRemoveCard m_AskRemoveCard;// 移卡

	Fn_EMV_AuthorisationRequest m_AuthorisationRequest;// 授权请求
	Fn_EMV_FinacialTransactionRequest m_FinacialTransactionRequest;// 授权请求确认
	Fn_EMV_FinancialTransactionConfirmation m_FinancialTransactionConfirmation;// 确认
	Fn_EMV_BatchDataCapture m_BatchDataCapture;// 批捕获
	Fn_EMV_Reversal m_Reversal;// 冲正
	Fn_EMV_OnlineAdvice m_OnlineAdvice;// 通知
	Fn_EMV_Issuer_Referral m_Issuer_Referral;
	Fn_EMV_SecondTapCard m_SecondTapCard;
	
	Fn_EMV_KernelMode m_KernelMode;
	Fn_EMV_KernelViewMode m_KernelViewMode;
	
	Fn_EMV_SaveTransLog m_SaveTransLog; // 保存交易日志
	Fn_EMV_GetTransLogAmt m_GetTransLogAmt;// 获取交易金额
	Fn_EMV_Contact_GetPlainTextPin m_ContactGetPlainTextPin;
	Fn_EMV_Contact_GetOnlinePin m_ContactGetOnlinePin;
	Fn_EMV_Contact_GetOfflineCipherPin m_ContactGetOffCipherPin;
	Fn_EMV_Contact_GetHolderCert m_ContactGetHolderCert;
	Fn_EMV_Contact_PanConfirm m_ContactPanConfirm;
	Fn_EMV_Contact_SelAppErr m_ContactSelAppErr;
	Fn_EMV_MagStripe_OnlineRequeset m_MagStripeOnlineRequest;
	Fn_EMV_Contact_SM2VerifySign m_ContactSM2VerifySign;
	Fn_EMV_Contact_SM3Hash m_ContactSM3Hash;
	Fn_EMV_Contact_ShowPanNo m_ContactShowPan;
}EMV_CALLBACK_FUNCS;

typedef const EMV_CALLBACK_FUNCS * LPC_EMV_CALLBACK_FUNCS;
typedef EMV_CALLBACK_FUNCS * LP_EMV_CALLBACK_FUNCS;

	/************************************************************************/
	/* Kernel Config                                                        */
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_GetVersion(LP_EMV_CHAR pBuffer, LP_EMV_UINT32 uiBufferSize);

	EMV_API EMV_UINT32 EMV_Initialize(EMV_VOID);

	EMV_API EMV_UINT32 EMV_SetCallbackFunc(LPC_EMV_CALLBACK_FUNCS pCallbackFuncs);
	EMV_API EMV_UINT32 EMV_GetCallbackFunc(LP_EMV_CALLBACK_FUNCS pCallbackFuncs);

	EMV_API EMV_UINT32 EMV_SetKernelType(KERNEL_MODE_TYPE KernelType);
	EMV_API EMV_UINT32 EMV_GetKernelType(LP_KERNEL_MODE_TYPE pKernelType);

	EMV_API EMV_UINT32 EMV_SetKernelConfig(LPC_EMV_KERNEL_CONFIG pKernelConfig);
	EMV_API EMV_UINT32 EMV_GetKernelConfig(LP_EMV_KERNEL_CONFIG pKernelConfig);

	EMV_API EMV_UINT32 EMV_SetTerminalInfo(LPC_EMV_TERMINAL_INFO pTerminalInfo);
	EMV_API EMV_UINT32 EMV_GetTerminalInfo(LP_EMV_TERMINAL_INFO pTerminalInfo);

	/************************************************************************/
	/* Transaction Functions                                                */
	/************************************************************************/

	EMV_API EMV_UINT32 EMV_ClearTransData(EMV_VOID);
	EMV_API EMV_UINT32 EMV_GetTransData(EMV_TAG Tag, LP_EMV_BYTE pValue,
		LP_EMV_UINT16 puiValue);
	EMV_API EMV_UINT32 EMV_GetTransDataAsHex(EMV_TAG Tag, LP_EMV_CHAR pszValue,
		EMV_UINT16 uiBuffSize);
	EMV_API EMV_UINT32 EMV_GetScriptResult(LP_EMV_CHAR pszBuffer,
		EMV_UINT16 uiBuffSize);
	EMV_API EMV_UINT32 EMV_GetLastStatusWord(LP_EMV_UINT16 pSW);

	EMV_API EMV_UINT32 EMV_SelectWithoutGPO(EMV_BOOL bPPSE);

	EMV_API EMV_UINT32 EMV_GetData(EMV_TAG Tag, LP_EMV_BYTE pValue,
			LP_EMV_UINT16 puiValue);

	EMV_API EMV_UINT32 EMV_ReadCardLog(EMV_UINT8 count, LP_EMV_BYTE szTempRecord,
			LP_EMV_UINT8 uiTempRecord);

	/************************************************************************/
	/*   Magnetic stripe card transactions                                  */
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_SetTransInfo(EMV_BYTE uiTransactionCounter,
			EMV_BYTE TransactionType, EMV_BOOL bAccountType, EMV_BYTE AccountType,
			EMV_UINT32 uiAmount, EMV_UINT32 uiAmountOther);
	EMV_API EMV_UINT32 EMV_SetTransData(EMV_TAG Tag, LPC_EMV_BYTE pValue,
			EMV_UINT16 uiValue);
	EMV_API EMV_UINT32 EMV_SetTransDataAsHex(EMV_TAG Tag, LPC_EMV_CHAR pszValue);

	/************************************************************************/
	/* CAPK                                                                 */
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_CAPK_GetCount(LP_EMV_UINT32 puiCount);
	EMV_API EMV_UINT32 EMV_CAPK_Add(LPC_EMV_CHAR pszRID, LPC_EMV_CHAR pszIndex,
			LPC_EMV_CHAR pszModules, LPC_EMV_CHAR pszExponents,
			LPC_EMV_CHAR pszChecksum);
	EMV_API EMV_UINT32 EMV_CAPK_Delete(LPC_EMV_CHAR pszRID, LPC_EMV_CHAR pszIndex);
	EMV_API EMV_UINT32 EMV_CAPK_Clear(EMV_VOID);
	EMV_API EMV_UINT32 EMV_CAPK_GetItem(EMV_UINT32 uiIndex, LP_EMV_CHAR pszRID,
			EMV_UINT32 uiRID, LP_EMV_CHAR pszCPKIndex, EMV_UINT32 uiCPKIndex,
			LP_EMV_CHAR pszModules, EMV_UINT32 uiModules, LP_EMV_CHAR pszExponents,
			EMV_UINT32 uiExponents, LP_EMV_CHAR pszChecksum, EMV_UINT32 uiChecksum);

	/************************************************************************/
	/* AID                                                                  */
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_AID_GetCount(LP_EMV_UINT32 puiCount);
	EMV_API EMV_UINT32 EMV_AID_Add(LPC_EMV_CHAR pszAID, LPC_EMV_CHAR pszAppVer,
			EMV_BOOL bPartMach, LPC_EMV_CHAR pszTerminalAcquireID,
			LPC_EMV_CHAR pszDefault_DDOL, LPC_EMV_CHAR pszDefault_TDOL,
			LPC_EMV_CHAR pszTAC_Denial, LPC_EMV_CHAR pszTAC_Online,
			LPC_EMV_CHAR pszTAC_Default, EMV_UINT32 TerminalFloorLimit,
			EMV_UINT32 TresholdValue, EMV_UINT32 TargetPercentage,
			EMV_UINT32 MaxTargetPercentage, EMV_UINT32 EC_Trans_Limite,
			EMV_UINT32 ContactlessMaxTransAmount, EMV_UINT32 ContactlessFloorLimit,
			EMV_UINT32 ContactlessCVMAmount);
	EMV_API EMV_UINT32 EMV_AID_Delete(LPC_EMV_CHAR pszAID);
	EMV_API EMV_UINT32 EMV_AID_Clear(EMV_VOID);
	EMV_API EMV_UINT32 EMV_AID_GetItem(EMV_UINT32 uiIndex, LP_EMV_CHAR pszAID,
			EMV_UINT32 uiAID, LP_EMV_CHAR pszAppVer, EMV_UINT32 uiAppVer,
			LP_EMV_BOOL pPartMach, LP_EMV_CHAR pszTerminalAcquireID,
			EMV_UINT32 uiTerminaAcquireID, LP_EMV_CHAR pszDefault_DDOL,
			EMV_UINT32 uiDefault_DDOL, LP_EMV_CHAR pszDefault_TDOL,
			EMV_UINT32 uiDefault_TDOL, LP_EMV_CHAR pszTAC_Denial,
			EMV_UINT32 uiTAC_Denial, LP_EMV_CHAR pszTAC_Online,
			EMV_UINT32 uiTAC_Online, LP_EMV_CHAR pszTAC_Default,
			EMV_UINT32 uiTAC_Default, LP_EMV_UINT32 TerminalFloorLimit,
			LP_EMV_UINT32 TresholdValue, LP_EMV_UINT32 TargetPercentage,
			LP_EMV_UINT32 MaxTargetPercentage, LP_EMV_UINT32 EC_Trans_Limite,
			LP_EMV_UINT32 ContactlessMaxTransAmount,
			LP_EMV_UINT32 ContactlessFloorLimit,
			LP_EMV_UINT32 ContactlessCVMAmount);

	/************************************************************************/
	/* Exception File                                                       */
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_ExceptionFile_GetCount(LP_EMV_UINT32 puiCount);
	EMV_API EMV_UINT32 EMV_ExceptionFile_Add(LPC_EMV_CHAR pszPAN,
			LPC_EMV_CHAR pszSeq);
	EMV_API EMV_UINT32 EMV_ExceptionFile_Delete(LPC_EMV_CHAR pszPAN,
			LPC_EMV_CHAR pszSeq);
	EMV_API EMV_UINT32 EMV_ExceptionFile_Clear(EMV_VOID);
	EMV_API EMV_UINT32 EMV_ExceptionFile_GetItem(EMV_UINT32 uiIndex,
			LP_EMV_CHAR pszPAN, EMV_UINT32 uiPAN, LP_EMV_CHAR pszPANSeq,
			EMV_UINT32 uiPANSeq);

	/************************************************************************/
	/* Revocation Issuer Public key                 						*/
	/************************************************************************/
	EMV_API EMV_UINT32 EMV_RevocationIPK_GetCount(LP_EMV_UINT32 puiCount);
	EMV_API EMV_UINT32 EMV_RevocationIPK_Add(LPC_EMV_CHAR pszRID,
			LPC_EMV_CHAR pszCapkIndex, LPC_EMV_CHAR pszSerialNo);
	EMV_API EMV_UINT32 EMV_RevocationIPK_Delete(LPC_EMV_CHAR pszRID,
			LPC_EMV_CHAR pszCapkIndex, LPC_EMV_CHAR pszSerialNo);
	EMV_API EMV_UINT32 EMV_RevocationIPK_Clear(EMV_VOID);
	EMV_API EMV_UINT32 EMV_RevocationIPK_GetItem(EMV_UINT32 uiIndex,
			LP_EMV_CHAR pszRID, EMV_UINT32 uiRID, LP_EMV_CHAR pszCapkIndex,
			EMV_UINT32 uiCapkIndex, LP_EMV_CHAR pszSerialNo, EMV_UINT32 uiSerialNo);

	/************************************************************************/
	/* Utility                                                 				*/
	/************************************************************************/
	EMV_API EMV_BOOL EMV_SHA1_Calc(LPC_EMV_VOID pvData, EMV_UINT32 ulLength,
			EMV_BYTE digits[20]);

	EMV_API EMV_BYTE EMV_Fmt_HexToNum(EMV_CHAR c);
	EMV_API EMV_BOOL EMV_Fmt_IsHexStr(LPC_EMV_CHAR pszHex);
	EMV_API EMV_BOOL EMV_Fmt_IsDecimalDigits(LPC_EMV_CHAR pszNum);

	/*
	ASCII 形式的16进制数转换成BIN 类型
	如:字符串"AB10" -> 转换成0xAB10
	也就是字符串转化成了银联要求的压缩BCD码类型，
	当然BCD 的字符数字不会超过9，这里可能会超过9
	*/
	EMV_API EMV_BOOL EMV_Fmt_HexToBinary(LPC_EMV_CHAR pszHex, LP_EMV_BYTE pBuff,
			EMV_UINT16 uiBuffSize);

	/*
	BIN 类型转化成ASCII 形式的16进制数
	如:0xAB10 -> 转换成字符串"AB10"
	也就是银联对应的压缩BCD 格式转化成了ASCII 形式的16进制数，
	*/
	EMV_API EMV_VOID EMV_Fmt_BinaryToHex(LPC_EMV_BYTE pData, LP_EMV_CHAR pszHex,
			EMV_UINT16 uiDataSize);

	EMV_API EMV_UINT32 EMV_CheckCAPK(LPC_EMV_CHAR pszRID, LPC_EMV_CHAR pszCapkIndex,
			LPC_EMV_CHAR pszModules, LPC_EMV_CHAR pszExponents,
			LPC_EMV_CHAR pszChecksum);

#ifdef __cplusplus
}
#endif

#endif
