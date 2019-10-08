#ifndef _APP_CALL_BACK_HEAD_H
#define _APP_CALL_BACK_HEAD_H


//#define KERNEL_VS_VERSION   // ʹ��vs����


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

// �Ӵ�����
typedef char(*Fn_Kernel_SaveTransLog)(unsigned char* bPanNo, int uiPanNo, 
	unsigned char* bPanSeq, int uiPanSeq, unsigned int pAuthAmt);

typedef unsigned int(*Fn_Kernel_GetTransLogAmt)(unsigned char* bPanNo, int uiPanNo, unsigned char*
	bPanSeq, int uiPanSeq, unsigned int pAuthAmt);


// �ѻ�����pin
typedef char(*Fn_Kernel_Contact_GetPlainTextPin)(unsigned char bAllowBypass, char* pszPIN,unsigned short uiPinBuffSize,
	char bPinTryCnt, int *bVerifyPinTryCnt,LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// ��������pin
typedef char(*Fn_Kernel_Contact_GetOnlinePin)(unsigned char bAllowBypass,const char* pszPAN, char* pszPinBlock,
	unsigned short uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// �ѻ�����pin
typedef char(*Fn_Kernel_Contact_GetOfflineCipherPin)(unsigned char bAllowBypass,
	LP_PIN_OFF_CIPHER_ITEM pPinCipherItem, char bPinTryCnt, int *bVerifyPinTryCnt, char* pszPinBlock,
	unsigned short uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// �ֿ���֤����֤
typedef char(*Fn_Kernel_Contact_GetHolderCert)(const char* pConfirmMsg, int uiConfirmMsg, const char * pHoldCert,
	int uiHoldCert);

// �����ο�(����)
typedef char(*Fn_Kernel_Contact_PanConfirm)(const char* pPAN);

// Ӧ��ѡ��ʧ��
typedef char(*Fn_Kernel_Contact_SelAppErr)(void);

typedef char(*Fn_Kernel_MagStripe_OnlineRequeset)(char* pOnlinePin, char* pResCode);

typedef char(*Fn_Kernel_Contact_SM2VerifySign)(unsigned char* pSMPubKey,
	unsigned char* bVerifyData, int uiVerifyData, unsigned char* bSignature, int uiSignature);

typedef char(*Fn_Kernel_Contact_SM3Hash)(unsigned char*  pVerifySM3,
	int uiVerifySM3, unsigned char* pSM3Hash, int * uiSM3Hash);

/*�Ӵ��ں˼쿨*/
typedef CT_DETECT_MODE(*Fn_Kernel_Contact_DetectCard)(char bFallBackFlag, char bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData);

/*
*�Ӵ�������ʾ����
*pPanNo:����
*/
typedef char(*Fn_Kernel_Contact_ShowPanNo)(char *pPanNo);

struct KERNEL_CALLBACK_FUNCS {
    Fn_Kernel_Log_Print m_Log_Print;//��ӡ��־
    Fn_Kernel_GetCurrentTime m_GetCurrentTime;//��ȡ�ն�ʱ��
    Fn_Kernel_GetRandomData m_GenerateRandomData;//��ȡ�����

    Fn_Kernel_DetectBreak m_DetectBreak;//�࿨��� . �жϵ�ǰ�Ƿ���ִ�зǽӿ�����
    Fn_Kernel_ExchangeApdu m_ExchangeApdu;// APDU ͨѶ
    Fn_Kernel_SelectApplication m_SelectApplication; //ѡ��Ӧ��
    Fn_Kernel_CardHolderConfirm m_CardHolderConfirm;//ȷ������
    Fn_Kernel_TryOtherApplication m_TryOtherApplication;//Ӧ������

    Fn_Kernel_EnterAmount m_EnterAmount; //������
    Fn_Kernel_GetPlainTextPin m_GetPlainTextPin; //���ı����� ,�����ѻ�PINʹ��
    Fn_Kernel_GetOnlinePin m_GetOnlinePin; // ����PIN
    Fn_Kernel_Display_Pin_Verify_Status m_Display_Pin_Verify_Status;//��ȡ�ѻ�״̬
    Fn_Kernel_Display_Trans_Report m_Display_Trans_Report;//���׽��
    Fn_Kernel_AskRemoveCard m_AskRemoveCard;// �ƿ�

    Fn_Kernel_AuthorisationRequest m_AuthorisationRequest;//��������
    Fn_Kernel_FinacialTransactionRequest m_FinacialTransactionRequest;//�ѻ����ݴ���
    Fn_Kernel_SecondTapCard m_SecondTapCard;//�����Ŀ�. �ű�����.

	Fn_Kernel_KernelMode m_KernelMode;
	Fn_Kernel_KernelViewMode m_KernelViewMode;

	// add by wl �����ص�
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

//------------------------------------ �ص�����------------------------------------------------//

//struct KERNEL_CALLBACK_FUNCS __CALL_BACK_KERNEL; //�ں˻ص����ⲿCӦ��ʹ��

#ifdef __cplusplus
}
#endif

#endif


