#ifndef _APP_CALL_BACK_HEAD_H
#define _APP_CALL_BACK_HEAD_H


//#define KERNEL_VS_VERSION   // 使用vs测试


#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvRevocationIPKList.h"
#include "EmvExceptionFileList.h"
#include "EmvTransHandle.h"
#include "EmvCapkList.h"
#include "EmvAidList.h"

typedef void(*Fn_Kernel_Log_Print)(const char * pszMessage, unsigned int len);

typedef void(*Fn_Kernel_GetCurrentTime)(LP_EMV_TIME pCurrentTime);

typedef void(*Fn_Kernel_GetRandomData)(unsigned char *pRandBuff, unsigned short uiSize);

typedef char(*Fn_Kernel_ExchangeApdu)(const unsigned char *pApdu, unsigned short uiApdu,
                                      unsigned char *pResp, unsigned short * puiResp);

typedef unsigned char(*Fn_Kernel_DetectBreak)(void);

typedef char(*Fn_Kernel_SelectApplication)(const char **ppAppNames, const char **ppAppAids,
                                           unsigned short uiAppCount, unsigned short *puiSelected);

typedef char(*Fn_Kernel_CardHolderConfirm)(const char *pAID, const char *pAppName, const char *pPreferAppName);

typedef char(*Fn_Kernel_TryOtherApplication)(void);

typedef char(*Fn_Kernel_EnterAmount)(unsigned int *pAmount, unsigned int *pAmountOther);

typedef char(*Fn_Kernel_GetPlainTextPin)(unsigned char bAllowBypass, char *pszPIN, unsigned short uiPinBuffSize,
                                         unsigned char pbBypass);

typedef char(*Fn_Kernel_GetOnlinePin)(unsigned char bAllowBypass, const char *pszPAN, char *pszPinBlock,
                                      unsigned short uiPinBlockBuffSize, unsigned char * pbBypass);

typedef char(*Fn_Kernel_Display_Pin_Verify_Status)(unsigned char uiRetryTimes);

typedef void(*Fn_Kernel_Display_Trans_Report)(int uiErrorCode, unsigned char bSignatureNeeded);

typedef void(*Fn_Kernel_AskRemoveCard)(void);

typedef void(*Fn_Kernel_AuthorisationRequest)(
        const char *pszOnlineEncipherPIN, unsigned char *pOnlineResult,
        char *pszIssueAuthData, unsigned short uiIssueAuthDataBuffSize,
        char *pszARC, unsigned short uiARCBuffSize, char *pszAuthCode,
        unsigned short uiAuthCode, char *pszIssueScript,
        unsigned short uiScriptBuffSize);

typedef void(*Fn_Kernel_FinacialTransactionRequest)(const char *pszOnlineEncipherPIN,
         unsigned char *pOnlineResult, char *pszIssueAuthData,
         unsigned short uiIssueAuthDataBuffSize, char *pszARC,
         unsigned short uiARCBuffSize, char *pszIssuerAuthCode,
         unsigned short uiIssuerAuthCode, char *pszIssueScript,
         unsigned short uiScriptBuffSize);

typedef char(*Fn_Kernel_SecondTapCard)(void);

typedef void(*Fn_Kernel_KernelMode)(unsigned int uiKernelMode);

typedef void(*Fn_Kernel_KernelViewMode)(unsigned int uiKernelViewMode);


// add by wl 20181122 
typedef void(*Fn_Kernel_AfterAppSelected)(void);

typedef char(*Fn_Kernel_LanguageSelect)(const char * pszLanguages, char bIsPSESelect);

typedef int (*Fn_Kernel_GetTransLogAmount)(char* pszPAN, char* pszPANSeq);

typedef void(*Fn_Kernel_FinancialTransactionConfirmation)(int uiErrorCode);

typedef void(*Fn_Kernel_BatchDataCapture)(char bAdvice, char bForceAccept, char bOnlineDataCapture);

typedef void(*Fn_Kernel_Reversal)(void);
typedef void(*Fn_Kernel_OnlineAdvice)(char bForceAccept, const char* pOnlinePIN);

typedef char(*Fn_Kernel_Issuer_Referral)(char* pszPAN);

// 接触新增
typedef char(*Fn_Kernel_SaveTransLog)(unsigned char* bPanNo, int uiPanNo, 
	unsigned char* bPanSeq, int uiPanSeq, unsigned int pAuthAmt);

typedef unsigned int(*Fn_Kernel_GetTransLogAmt)(unsigned char* bPanNo, int uiPanNo, unsigned char*
	bPanSeq, int uiPanSeq, unsigned int pAuthAmt);


// 脱机明文pin
typedef char(*Fn_Kernel_Contact_GetPlainTextPin)(unsigned char bAllowBypass, char* pszPIN,unsigned short uiPinBuffSize,
	char bPinTryCnt, int *bVerifyPinTryCnt,LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 联机加密pin
typedef char(*Fn_Kernel_Contact_GetOnlinePin)(unsigned char bAllowBypass,const char* pszPAN, char* pszPinBlock,
	unsigned short uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 脱机密文pin
typedef char(*Fn_Kernel_Contact_GetOfflineCipherPin)(unsigned char bAllowBypass,
	LP_PIN_OFF_CIPHER_ITEM pPinCipherItem, char bPinTryCnt, int *bVerifyPinTryCnt, char* pszPinBlock,
	unsigned short uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// 持卡人证件验证
typedef char(*Fn_Kernel_Contact_GetHolderCert)(const char* pConfirmMsg, int uiConfirmMsg, const char * pHoldCert,
	int uiHoldCert);

// 联机参考(卡号)
typedef char(*Fn_Kernel_Contact_PanConfirm)(const char* pPAN);

// 应用选择失败
typedef char(*Fn_Kernel_Contact_SelAppErr)(void);

typedef char(*Fn_Kernel_MagStripe_OnlineRequeset)(char* pOnlinePin, char* pResCode);

typedef char(*Fn_Kernel_Contact_SM2VerifySign)(unsigned char* pSMPubKey,
	unsigned char* bVerifyData, int uiVerifyData, unsigned char* bSignature, int uiSignature);

typedef char(*Fn_Kernel_Contact_SM3Hash)(unsigned char*  pVerifySM3,
	int uiVerifySM3, unsigned char* pSM3Hash, int * uiSM3Hash);

/*接触内核检卡*/
typedef CT_DETECT_MODE(*Fn_Kernel_Contact_DetectCard)(char bFallBackFlag, char bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData);

/*
*接触用于显示卡号
*pPanNo:卡号
*/
typedef char(*Fn_Kernel_Contact_ShowPanNo)(char *pPanNo);

struct KERNEL_CALLBACK_FUNCS {
    Fn_Kernel_Log_Print m_Log_Print;//打印日志
    Fn_Kernel_GetCurrentTime m_GetCurrentTime;//获取终端时间
    Fn_Kernel_GetRandomData m_GenerateRandomData;//获取随机数

    Fn_Kernel_DetectBreak m_DetectBreak;//多卡检查 . 判断当前是否在执行非接卡交易
    Fn_Kernel_ExchangeApdu m_ExchangeApdu;// APDU 通讯
    Fn_Kernel_SelectApplication m_SelectApplication; //选择应用
    Fn_Kernel_CardHolderConfirm m_CardHolderConfirm;//确认数据
    Fn_Kernel_TryOtherApplication m_TryOtherApplication;//应用重启

    Fn_Kernel_EnterAmount m_EnterAmount; //输入金额
    Fn_Kernel_GetPlainTextPin m_GetPlainTextPin; //纯文本密码 ,明文脱机PIN使用
    Fn_Kernel_GetOnlinePin m_GetOnlinePin; // 联机PIN
    Fn_Kernel_Display_Pin_Verify_Status m_Display_Pin_Verify_Status;//获取脱机状态
    Fn_Kernel_Display_Trans_Report m_Display_Trans_Report;//交易结果
    Fn_Kernel_AskRemoveCard m_AskRemoveCard;// 移卡

    Fn_Kernel_AuthorisationRequest m_AuthorisationRequest;//联机上送
    Fn_Kernel_FinacialTransactionRequest m_FinacialTransactionRequest;//脱机数据处理
    Fn_Kernel_SecondTapCard m_SecondTapCard;//二次拍卡. 脚本处理.

	Fn_Kernel_KernelMode m_KernelMode;
	Fn_Kernel_KernelViewMode m_KernelViewMode;

	// add by wl 新增回调
	Fn_Kernel_AfterAppSelected m_AfterAppSelected;
	Fn_Kernel_LanguageSelect m_LanguageSelect;
	Fn_Kernel_GetTransLogAmount m_GetTransLogAmount;
	Fn_Kernel_FinancialTransactionConfirmation m_FinancialTransConfirm;
	Fn_Kernel_BatchDataCapture m_BatchDataCapture;
	Fn_Kernel_Reversal m_Reversal;
	Fn_Kernel_OnlineAdvice m_OnlineAdvice;
	Fn_Kernel_Issuer_Referral m_Issuer_Referral;
	Fn_Kernel_SaveTransLog m_SaveTransLog;
	Fn_Kernel_GetTransLogAmt m_GetTransLogAmt;
	Fn_Kernel_Contact_GetPlainTextPin m_ContactGetPlainTextPin;
	Fn_Kernel_Contact_GetOnlinePin m_ContactGetOnlinePin;
	Fn_Kernel_Contact_GetOfflineCipherPin m_ContactGetOffCipherPin;
	Fn_Kernel_Contact_GetHolderCert m_ContactGetHolderCert;
	Fn_Kernel_Contact_PanConfirm m_ContactPanConfirm;
	Fn_Kernel_Contact_SelAppErr m_ContactSelAppErr;
	Fn_Kernel_MagStripe_OnlineRequeset m_MagStripeOnlineRequeset;
	Fn_Kernel_Contact_SM2VerifySign m_ContactSM2VerifySign;
	Fn_Kernel_Contact_SM3Hash m_ContactSM3Hash;
	Fn_Kernel_Contact_DetectCard m_ContactDetectCard;
	Fn_Kernel_Contact_ShowPanNo m_ContactShowPanNo;
};

typedef const struct KERNEL_CALLBACK_FUNCS *LPC_KERNEL_CALLBACK_FUNCS;
typedef struct KERNEL_CALLBACK_FUNCS *LP_KERNEL_CALLBACK_FUNCS;

//------------------------------------ 回调函数------------------------------------------------//

//struct KERNEL_CALLBACK_FUNCS __CALL_BACK_KERNEL; //内核回调给外部C应用使用

#ifdef __cplusplus
}
#endif

#endif


