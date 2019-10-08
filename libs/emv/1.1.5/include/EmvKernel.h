#ifndef EMVKERNEL_H_
#define EMVKERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "EmvDataType.h"

//����汾. EMV ģʽ ���ð汾. ����ģʽ ������֤. 

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
//#define SUPPORT_MIR				//����˹ MIR��	
//#define SUPPORT_JCB			//Ŀǰ��֧��JCB.


#define EMV_API

//#define PRT() printf("file[%s]--function[%s()]--line[%d]\n", __FILE__, __FUNCTION__, __LINE__)

#define AMEX_APPROVED			29
#define AMEX_FORCE_APPROVED     30
#define AMEX_DECLINED			31
#define AMEX_DELAYED_APPROVED	32
#define AMEX_ATC_DELAYED        34

#define DISCOVER_TRY_ANOTHER_INTERFACE 33
#define DISCOVER_CARD_EXPIRED   37

#define QVSDC_ONLINE_ODA_FAILED 36 //visa ����ODA ȱ������ �����д���.

#define QPBOC_EXPIRATION_OVERDUE_ONLINE  38//��Ƭ��������9F6C��1�ֽڵ�4λΪ1,Ӧת����������,����ʾ"��Ƭ����Ч��,��������"
#define QPBOC_EXPIRATION_OVERDUE_REFUSE  39//��Ƭ��������9F6C��1�ֽڵ�4λΪ0,Ӧ�ܾ�����,����ʾ"��Ƭ����Ч��,���׾ܾ�"
#define QPBOC_OTHER_INTERFACE_CL		 40//ת�Ӵ�����.

#define EMV_KERNEL_NOT_SUPPORT			 41//�ں˲�֧��.

#define EMV_OK					0
#define EMV_APPROVED_OFFLINE    1  // �ѻ�����
#define EMV_APPROVED_ONLINE     2	// ��������
#define EMV_DECLINED_OFFLINE    3	// �ѻ��ܾ�
#define EMV_DECLINED_ONLINE     4	// �����ܾ�
#define EMV_NO_ACCEPTED         6	// ������
#define EMV_TERMINATED			7	//  �ն˴���
#define EMV_CARD_BLOCKED        8	// ��Ƭ����
#define EMV_APP_BLOCKED         9	// Ӧ����
#define EMV_NO_APP              10	// ��Ӧ��

#define EMV_CAPK_EXPIRED        11 // ��Կ����
#define EMV_CAPK_CHECKSUM_ERROR 12 // ��ԿУ���
#define EMV_AID_DUPLICATE       13 // Ӧ���ظ�

#define EMV_CERTIFICATE_RECOVER_FAILED 14 // ֤��ָ���
#define EMV_DATA_AUTH_FAILED     15 // ��֤ʧ��

#define EMV_UN_RECOGNIZED_TAG	16 // ��Чtag
#define EMV_DATA_NOT_EXISTS     17 // ���ݲ�����
#define EMV_DATA_LENGTH_ERROR   18 // ���ݳ��ȴ�
#define EMV_INVALID_TLV         19 // ��Чtlv
#define EMV_INVALID_RESPONSE    20 // ��Ч��Ӧ
#define EMV_DATA_DUPLICATE      21 // �����ظ�

#define EMV_MEMORY_NOT_ENOUGH	22 // �ڴ治��
#define EMV_MEMORY_OVERFLOW		23 // �ڴ����
#define EMV_PARAMETER_ERROR     24 // ������
#define EMV_ICC_ERROR           25 // icc����

#define EMV_NO_MORE_DATA        26 // �޸�������
#define EMV_CAPK_NO_FOUND       27 // ��Կû�ҵ�

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
typedef EMV_BYTE EMV_DEFAULT_ACTION_CODE_METHOD; // Ĭ����Ϊ���뷽ʽ
#define EMV_DEFAULT_ACTION_CODE_BEFOR_GAC1 0x00
#define EMV_DEFAULT_ACTION_CODE_AFTER_GAC1 0x01

#define	EMV_TRANS_TYPE_GOODS_SERVICE 	0x00	//POS��һ�㽻�׶���������� ����
#define	EMV_TRANS_TYPE_CASH			 0x01	//ȡ�֣�һ������ATM��
#define 	EMV_TYPE_AUTH					0x03	//Ԥ��Ȩ
//�̻������100Ԫ��Ʒ����������10�����ֽ��׾��Ƿ��֣���Ҫ����100��10�������
#define	EMV_TRANS_TYPE_CASHBACK		 0x09	 // ����

#define	EMV_TRANS_TYPE_INQUIRY		 0x31 // ��ѯ
#define	EMV_TRANS_TYPE_TRANSFER		 0x11 // ת��
#define	EMV_TRANS_TYPE_PAYMENT		 0x12 // ����
#define	EMV_TRANS_TYPE_ADMIN  		 0x13 // ����
#define	EMV_TRANS_TYPE_DEPOSIT       0x21 // ���

#define 	EMV_TRANS_TYPE_EC_CASE_LOAD	0x63 // �ֽ��ֽ�Ȧ��
#define 	EMV_TRANS_TYPE_EC_DEFINED_ACCOUNT_LOAD	0x60  // �����ֽ�ָ��Ȧ��
#define 	EMV_TRANS_TYPE_EC_UNDEFINED_ACCOUNT_LOAD	0x62 // �����ֽ��ָ��Ȧ��

typedef EMV_BYTE EMV_ONLINE_RESULT;
#define	EMV_ONLINE_APPROVED         0x00 // ������׼
#define	EMV_ONLINE_REJECT			0x01 // �����ܾ�
#define	EMV_ONLINE_VOICE_PREFER		0x02 // ������������
#define	EMV_ONLINE_ERROR			0x03 // ��������
#define	EMV_ONLINE_TIME_OUT			0x04 // ������ʱ
#define	EMV_ONLINE_CONNECT_FAILED	0x05 // ��������ʧ��
#define EMV_ONLINE_NULL				0xFF // 

#define PBOC_SIMPLE_PROC 			0			//PBOC ������
#define PBOC_SIMPLE_PROC_AUTH		1			//PBOC�����̴�����������֤
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
/*  �����ں˽��׹����в�������                                          */
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
	EMV_BOOL m_PSE;//�Ƿ�֧��PSEѡ��ʽ
	EMV_BOOL m_CardHolderConfirm;//�Ƿ�֧�ֳֿ���ȷ��
	EMV_BOOL m_PreferredDisplayOrder; //NO implemented,�����ն����õ�AID˳����ʾ
	EMV_BOOL m_LanguateSelect;// �Ƿ�֧�ֶ����� 
	EMV_BOOL m_RevocationOfIssuerPublicKey;//��鷢���й�Կ���� 
	EMV_BOOL m_Default_DDOL;//�Ƿ�֧��Ĭ��DDOL  
	EMV_BOOL m_Bypass_PIN_Entry;//�Ƿ�֧���ƹ�pin����(ֱ��ȷ��) 
	EMV_BOOL m_Subsequent_Bypass_PIN_Entry;// ��������pin
	EMV_BOOL m_Getdata_For_PIN_Try_Counter;// ��ȡpin���Դ���
	EMV_BOOL m_Floor_Limit_Checking;// ����޶���
	EMV_BOOL m_Random_Transaction_Selection; //�Ƿ�����������ѡ��
	EMV_BOOL m_Velocity_Checking;// Ƶ�ȼ��
	EMV_BOOL m_TransactionLog;//
	EMV_BOOL m_Exception_File;// �쳣�ļ����
	EMV_BOOL m_TerminalActionCode;// �Ƿ�֧��tac
	EMV_DEFAULT_ACTION_CODE_METHOD m_DefaultActionCodeMethod;
	EMV_BOOL m_TAC_IAC_Default_SkipedWhenUnableToGoOnline;
	EMV_BOOL m_CDA_FailureDetectedPriorTerminalActionAnalysis;

	EMV_CDA_METHOD m_CDA_Method;

	EMV_BOOL m_ForcedOnline;// ǿ������
	EMV_BOOL m_ForcedAcceptance;// ǿ�ƽ���
	EMV_BOOL m_Advices;// ֪ͨ
	EMV_BOOL m_Issuer_Referral;// �Ƿ�֧�ַ����вο�
	EMV_BOOL m_BatchDataCapture;// �����Ͳ���
	EMV_BOOL m_OnlineDataCapture;// ��������
	EMV_BOOL m_Default_TDOL;// Ĭ��tdol
	EMV_BOOL m_Terminal_SupportAccountTypeSelection; //No Implemented

	EMV_CHAR m_TerminalType[SIZE_TERMINAL_TYPE * 2 + 1];//�ն�����
	EMV_CHAR m_TerminalCapabilities[SIZE_TERMINAL_CAPABILITIES * 2 + 1];// �ն�����
	EMV_CHAR m_AddtionalTerminalCapabilities[SIZE_ADDTIONAL_TERMINAL_CAPABILITIES * 2 + 1];// �ն���չ����

}EMV_KERNEL_CONFIG;

typedef  EMV_KERNEL_CONFIG * LP_EMV_KERNEL_CONFIG;
typedef const  EMV_KERNEL_CONFIG * LPC_EMV_KERNEL_CONFIG;


typedef struct {
	// 315
	EMV_CHAR m_TerminalID[SIZE_TERMINAL_ID + 1]; //�ն˱�־(POS��)m_TermId
	EMV_CHAR m_IFDSerialNumber[SIZE_IFD_SERIAL_NUMBER + 1];// m_IFDSerialNumber�ӿ��豸���к�
	EMV_CHAR m_TerminalCountryCode[SIZE_COUNTRY_CODE * 2 + 1];//m_CountryCode�ն˹��Ҵ���
	EMV_CHAR m_Merchant_ID[SIZE_MERCHANT_ID + 1];//�̻���־(�̻���)m_MerchId
	EMV_CHAR m_Merchant_Category_Code[SIZE_MERCHANT_CATEGORY_CODE * 2 + 1];//m_MerchCateCode�̻������(ûҪ��ɲ�����)
	EMV_CHAR m_Merchant_Location[SIZE_MERCHANT_LOCATION + 1];//�̻���m_MerchName
	EMV_CHAR m_Trans_Currency_Code[SIZE_TRANS_CURRENCY_CODE * 2 + 1];//���׻��Ҵ���m_TransCurrCode
	EMV_UINT8 m_Trans_Currency_Exp;//���׻��Ҵ���ָ��m_TransCurrExp
	EMV_CHAR m_Trans_Ref_Currency_Code[SIZE_TRANS_CURRENCY_CODE * 2 + 1];//m_ReferCurrCode �ο����Ҵ���
	EMV_UINT8 m_Trans_Ref_Currency_Exp;//�ο�����ָ��m_ReferCurrExp
	EMV_CHAR m_TerminalEntryMode[SIZE_TERMINAL_ENTRY_MODE * 2 + 1]; //pos���뷽ʽ 

	// add by wl 
	EMV_UINT32 m_ReferCurrCon; //�ο����Ҵ���ͽ��״����ת��ϵ��(���׻��ҶԲο����ҵĻ���*1000)

}EMV_TERMINAL_INFO;

typedef  EMV_TERMINAL_INFO * LP_EMV_TERMINAL_INFO;
typedef const  EMV_TERMINAL_INFO * LPC_EMV_TERMINAL_INFO;

// ����pin�ķ���ֵ����
typedef enum{
	CV_VERIFY_SUC = 0,
	CV_VERIFY_NO_PINPAD,// û������̻���̲����� 1
	CV_VERIFY_NO_PASSWORD,// û������û��������������� 2
	CV_VERIFY_PIN_ERROR, // ������� 63cx 3
	CV_VERIFY_PIN_BLOCK,// pin������ 4
	// ��4���˳�����
	CV_VERIFY_TIME_OUT,// ���볬ʱ 5
	CV_VERIFY_USER_CANCEL,// �û�ȡ�� 6
	CV_VERIFY_ICC_CMD_ERR,// ����� 7
	CV_VERIFY_RSP_ERR,// ��Ӧ���� 8

	CV_CERIFY_CERT_ERR,// �ֿ���֤������ 9
	CV_CERIFY_DEFAULT_ERR,// Ĭ��ʧ��ֵ 10
}EMV_CV_VERIFY_RESULT;

typedef EMV_CV_VERIFY_RESULT * LP_EMV_CV_VERIFY_RESULT;

/************�����ѻ�����pin��֤**************/
typedef struct
{
	EMV_INT32 uiCardRnd;
	EMV_BYTE bCardRng[MAX_CARD_RANDOM];// ��Ƭ�����
	EMV_INT32 uiPubExp;
	EMV_BYTE bPubExp[MAX_RSA_EXPONENTS];// ���ܹ�Կָ��
	EMV_INT32 uiPubMod;
	EMV_BYTE bPubMod[MAX_RSA_MODULES];// ���ܹ�Կģ
}PIN_OFF_CIPHER_ITEM;

typedef PIN_OFF_CIPHER_ITEM * LP_PIN_OFF_CIPHER_ITEM;


// �������Ľṹ��
typedef struct {
	EMV_BOOL m_TrackExistFlag;// �ŵ����ݴ��ڵı�־λ
	EMV_BOOL m_FallBackFlag;// �����ı�־λ
	EMV_BYTE m_Track1[MAX_MAG_TRACK1];
	EMV_BYTE m_Track2[MAX_MAG_TRACK2];
	EMV_BYTE m_Track3[MAX_MAG_TRACK3];
}MAG_TRACK_DATA;

typedef MAG_TRACK_DATA *LP_MAG_TRACK_DATA;

/*************************����ص�**************************************/
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

// ���潻�׽��
typedef EMV_BOOL(*Fn_EMV_SaveTransLog)(EMV_UINT32 uiCallBackHandle, LP_EMV_BYTE bPanNo, EMV_INT32 uiPanNo, LP_EMV_BYTE bPanSeq, EMV_INT32 uiPanSeq, EMV_UINT32 pAuthAmt);

// ��ȡ���׵Ľ��
typedef EMV_UINT32(*Fn_EMV_GetTransLogAmt)(EMV_UINT32 uiCallBackHandle, LP_EMV_BYTE bPanNo, EMV_INT32 uiPanNo, LP_EMV_BYTE bPanSeq, EMV_INT32 uiPanSeq, EMV_UINT32 pAuthAmt);

// �ѻ�����pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetPlainTextPin)(EMV_UINT32 uiCallbackHandle, EMV_BOOL bAllowBypass, LP_EMV_CHAR pszPIN,
	EMV_UINT16 uiPinBuffSize, EMV_CHAR bPinTryCnt, LP_EMV_INT32 bVerifyPinTryCnt, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// ��������pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetOnlinePin)(EMV_UINT32 uiCallbackHandle,
	EMV_BOOL bAllowBypass, LPC_EMV_CHAR pszPAN, LP_EMV_CHAR pszPinBlock,
	EMV_UINT16 uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// �ѻ�����pin
typedef EMV_BOOL(*Fn_EMV_Contact_GetOfflineCipherPin)(EMV_UINT32 uiCallbackHandle,EMV_BOOL bAllowBypass,
	LP_PIN_OFF_CIPHER_ITEM pPinCipherItem, EMV_CHAR bPinTryCnt, LP_EMV_INT32 bVerifyPinTryCnt,LP_EMV_CHAR pszPinBlock,
	EMV_UINT16 uiPinBlockBuffSize, LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// �ֿ���֤����֤
typedef EMV_BOOL(*Fn_EMV_Contact_GetHolderCert)(EMV_UINT32 uiCallbackHandle,
	LPC_EMV_CHAR pConfirmMsg, EMV_INT32 uiConfirmMsg, LPC_EMV_CHAR pHoldCert,
	EMV_INT32 uiHoldCert);

// ����ȷ��
typedef EMV_BOOL(*Fn_EMV_Contact_PanConfirm)(EMV_UINT32 uiCallbackHandle,LPC_EMV_CHAR pPAN);

// Ӧ��ѡ��ʧ��
typedef EMV_BOOL(*Fn_EMV_Contact_SelAppErr)(EMV_UINT32 uiCallbackHandle);

// ����������������
typedef EMV_BOOL(*Fn_EMV_MagStripe_OnlineRequeset)(EMV_UINT32 uiCallbackHandle,
	LP_EMV_CHAR pOnlinePin, LP_EMV_CHAR pResCode);

/*
*��֤����֤���Ƿ����
*pSMPubKey:���ܹ�Կ(64byte)
*bVerifyData:Ҫ��֤������
*uiVerifyData:Ҫ��֤�����ݳ�
*bSignature:ǩ��ֵ
*uiSignature:ǩ����(63byte)
*/
typedef EMV_BOOL(*Fn_EMV_Contact_SM2VerifySign)(EMV_UINT32 uiCallbackHandle, LP_EMV_BYTE pSMPubKey, 
	LP_EMV_BYTE bVerifyData, EMV_INT32 uiVerifyData,LP_EMV_BYTE bSignature, EMV_INT32 uiSignature);

typedef EMV_BOOL(*Fn_EMV_Contact_SM3Hash)(EMV_UINT32 uiCallbackHandle, LP_EMV_BYTE pVerifySM3, 
	EMV_INT32 uiVerifySM3, LP_EMV_BYTE pSM3Hash, LP_EMV_INT32 uiSM3Hash);

// �ٴμ쿨�ķ���ֵ
typedef enum {
	CT_DETECT_MODE_NONE,
	CT_DETECT_MODE_IC,
	CT_DETECT_MODE_MAG,
} CT_DETECT_MODE; // ������״̬

/*
�Ӵ��ں˼쿨
bFallBackFlag:�Ƿ񽵼�
bInsertCardFlag:�Ƿ���Ҫ�忨
pMagTrackData:�����ˢ��,�򷵻شŵ�����
*/
typedef CT_DETECT_MODE(*Fn_EMV_Contact_DetectCard)(EMV_UINT32 uiCallbackHandle, EMV_CHAR bFallBackFlag,
	EMV_CHAR bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData);

/*
*�Ӵ�������ʾ����
*pPanNo:����
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
	Fn_EMV_AfterAppSelected m_AfterAppSelected; //δʹ��
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
	Fn_EMV_AskRemoveCard m_AskRemoveCard;// �ƿ�

	Fn_EMV_AuthorisationRequest m_AuthorisationRequest;// ��Ȩ����
	Fn_EMV_FinacialTransactionRequest m_FinacialTransactionRequest;// ��Ȩ����ȷ��
	Fn_EMV_FinancialTransactionConfirmation m_FinancialTransactionConfirmation;// ȷ��
	Fn_EMV_BatchDataCapture m_BatchDataCapture;// ������
	Fn_EMV_Reversal m_Reversal;// ����
	Fn_EMV_OnlineAdvice m_OnlineAdvice;// ֪ͨ
	Fn_EMV_Issuer_Referral m_Issuer_Referral;
	Fn_EMV_SecondTapCard m_SecondTapCard;
	
	Fn_EMV_KernelMode m_KernelMode;
	Fn_EMV_KernelViewMode m_KernelViewMode;
	
	Fn_EMV_SaveTransLog m_SaveTransLog; // ���潻����־
	Fn_EMV_GetTransLogAmt m_GetTransLogAmt;// ��ȡ���׽��
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
	ASCII ��ʽ��16������ת����BIN ����
	��:�ַ���"AB10" -> ת����0xAB10
	Ҳ�����ַ���ת����������Ҫ���ѹ��BCD�����ͣ�
	��ȻBCD ���ַ����ֲ��ᳬ��9��������ܻᳬ��9
	*/
	EMV_API EMV_BOOL EMV_Fmt_HexToBinary(LPC_EMV_CHAR pszHex, LP_EMV_BYTE pBuff,
			EMV_UINT16 uiBuffSize);

	/*
	BIN ����ת����ASCII ��ʽ��16������
	��:0xAB10 -> ת�����ַ���"AB10"
	Ҳ����������Ӧ��ѹ��BCD ��ʽת������ASCII ��ʽ��16��������
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
