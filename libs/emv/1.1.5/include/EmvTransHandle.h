#ifndef EMV_TRANSACTION_H
#define EMV_TRANSACTION_H

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvKernel.h"
#include "QVSDC.h"

#define LOG_TP_COM 1    // �����Ƿ��ӡlog


#define MAX_ISSUER_SCRIPT			300
#define MAX_ISSUER_SCRIPT_RESULT	256

#define MAX_RSA_EXPONENTS  3
#define MAX_RSA_MODULES    256

#define OFFLINE_APPROVED   "Y1" // �ѻ���׼
#define OFFLINE_DECLINE    "Z1" // �ѻ��ܾ�
#define ONLINE_APPROVED    "Y2" // ������׼
#define ONLINE_DECLINE     "Z2" // �����ܾ�
#define ONLINE_ERROR_OFFLINE_APPROVED "Y3" // �ѻ���׼������������
#define ONLINE_ERROR_OFFLINE_DECLINE  "Z3" // �ѻ��ܾ�������������


//��������
enum QVSDC_TRANS_TYPE {
	TRANS_TYPE_PURCHASE = 0x00,
	TRANS_TYPE_CASHBACK,
	TRANS_TYPE_CASH,
	TRANS_TYPE_REFUND,
	
	// qpboc����
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
 * ��Կ
 */
typedef struct  {
	EMV_UINT16 m_iExponentsLen;// ָ����
	EMV_BYTE m_bExponentsValue[MAX_RSA_EXPONENTS];// ָ��
	EMV_UINT16 m_iModuleLen;
	EMV_BYTE m_bModuleValue[MAX_RSA_MODULES]; // Ĥ
}EMV_PUBLIC_KEY;

typedef  EMV_PUBLIC_KEY * LP_EMV_PUBLIC_KEY;
typedef const  EMV_PUBLIC_KEY * LPC_EMV_PUBLIC_KEY;


// * AID ����
typedef struct{
	//  596
	EMV_UINT16 m_uiAID;
	EMV_BYTE m_AID[MAX_AID];
	EMV_BYTE m_AppVersion[SIZE_APP_VERSION];
	EMV_BOOL m_PartMach;// 0->����ƥ��,1->ȫƥ��
	EMV_BYTE m_TerminalAcquireID[SIZE_TERMINAA_ACQUIRE_ID];
	EMV_BYTE m_Default_DDOL[MAX_DATA_SIZE]; //use when DDA
	EMV_UINT32 m_Default_DDOL_Len;
	EMV_BYTE m_Default_TDOL[MAX_DATA_SIZE]; //use when CDA
	EMV_UINT32 m_Default_TDOL_Len;
	
	EMV_UINT32 m_TerminalFloorLimit;
	EMV_UINT32 m_TresholdValue;
	EMV_UINT32 m_TargetPercentage;
	EMV_UINT32 m_MaxTargetPercentage;
	EMV_BOOL m_Priority;          //���ȼ���־
	
	EMV_BYTE m_TAC_Denial[SIZE_ACTION_CODE];
	EMV_BYTE m_TAC_Online[SIZE_ACTION_CODE];
	EMV_BYTE m_TAC_Default[SIZE_ACTION_CODE];

	EMV_UINT32 m_EC_Trans_Limite; //EC

	EMV_UINT32 m_ContactlessTransLimit; //qPBOC
	EMV_UINT32 m_ContactlessFloorLimit; //qPBOC
	EMV_UINT32 m_ContactlessCVMAmount; //qPBOC

	// �Ӵ���aid����
	EMV_BOOL m_RiskManData[MAX_RISK_MAN_DATA];   //���չ�������(1�ֽڳ���+����)
	EMV_BOOL m_MerchCateCode[SIZE_MERCHANT_CATEGORY_CODE];  //�̻������(ûҪ��ɲ�����)
	EMV_BOOL m_MerchId[SIZE_MERCHANT_ID];       //�̻���־(�̻���)  9F16
	EMV_BOOL m_MerchName[SIZE_MERCHANT_LOCATION];    //�̻���
	EMV_BOOL m_TermId[SIZE_TERMINAL_ID];         //�ն˱�־(POS��)
	EMV_BOOL m_TransCurrCode[SIZE_TRANS_CURRENCY_CODE];  //���׻��Ҵ���
	EMV_BOOL m_TransCurrExp;      //���׻��Ҵ���ָ��
	EMV_BOOL m_ReferCurrCode[SIZE_TRANS_CURRENCY_CODE];  //�ο����Ҵ���
	EMV_BOOL m_ReferCurrExp;      //�ο�����ָ��
	
	EMV_BOOL m_OnlinePinSpt;      // �ն���������
	// m_EC_Trans_Limite����ʱ,
	EMV_BOOL m_ucECTSIFlag;   // �����ֽ��ն�֧��ָʾ�� = 1,֧�֣�EC Terminal Support Indicator��

	
} EMV_AID_ITEM;

typedef EMV_AID_ITEM * LP_EMV_AID_ITEM;

typedef const  EMV_AID_ITEM * LPC_EMV_AID_ITEM;

//#endif


/**
 * ���׹����� ����������.
 */
typedef struct  {
	EMV_AID_ITEM m_CurrentApp;// ��ǰaid
	EMV_UINT16 m_SW;// ״̬��

	EMV_BYTE m_SDA_Data[256 * 32];// sda���� 8k
	EMV_UINT16 m_SDA_DataSize;
	EMV_BOOL m_SDARecordIncorrect;// sda�ָ�ʧ��
	EMV_BYTE m_PDOL_Data[MAX_CDA_DATA];// pdol����
	EMV_UINT16 m_PDOL_DataSize;// sda����
	EMV_BYTE m_CDOL1_Data[MAX_CDA_DATA];
	EMV_UINT16 m_CDOL1_DataSize;
	EMV_BYTE m_CDOL2_Data[MAX_CDA_DATA];
	EMV_UINT16 m_CDOL2_DataSize;

	EMV_BOOL m_CAPK_Recovered;// ��Կ�ָ���ʶ
	EMV_PUBLIC_KEY m_CAPK;// ��Կ����
	EMV_BOOL m_IPK_Recovered;//�����й�Կ�ָ���ʶ
	EMV_PUBLIC_KEY m_IPK;// �����й�Կ����
	EMV_BOOL m_ICCPK_Recovered;// ic��Կ�ָ���ʶ
	EMV_PUBLIC_KEY m_ICCPK;// IC����Կ

	EMV_CHAR m_OnlineEncipherPIN[SIZE_PIN_BLOCK * 2 + 1];// ����PINBLOCK
	EMV_CHAR m_IssueScript[MAX_ISSUER_SCRIPT];// �����нű�����
	EMV_UINT16 m_IssueScriptSize;// �����нű����ݳ�
	EMV_BYTE m_ScriptResults[MAX_ISSUER_SCRIPT_RESULT];// �ű����
	EMV_UINT16 m_uiScriptResults;// �ű�����
	EMV_BOOL m_SignatureRequired;// ǩ������
	EMV_BOOL m_OnlinePinRequired;// ����pin����
	
	//�ǽ�ʹ�ò���
	EMV_BOOL m_SmRequired; // ?? SM
	EMV_BOOL m_SkipPINEntry; 
	EMV_BOOL m_OnlineNeeded;
	EMV_BOOL m_AdviceNeeded;

	EMV_ONLINE_RESULT m_OnlineResult;// �������

	EMV_BOOL m_QVSDC_NeedToSaveLog;// ����log
	EMV_UINT32 m_QVSDC_TarnsCounter;// ���׼�����
	EMV_BYTE m_QVSDC_TransType;// ��������
	EMV_UINT32 m_QVSDC_Amount;// ���׽��
	EMV_UINT32 m_QVSDC_AmountOther;// �������

	// VISA
	EMV_BOOL m_QVSDC_Online_Flag;// ������־
	EMV_BOOL m_QVSDC_Decline_Flag;// �ܾ���־
	EMV_BOOL m_QVSDC_AppNotAllow_Flag;// Ӧ�ò�����
	
	// DISCOVER
	EMV_BOOL m_Discover_Emv_Flag;
	EMV_UINT16 m_Discover_UnLen;// PDOL 9F37 ֵ. �ڼ���ŵ���Ϣʱ, ��ʹ�õ�.

	// AMEX
	EMV_BOOL m_AMEX_Expresspay_Emv_Flag; //TRUE(Expresspay EMV Mode Transaction) FALSE (Expresspay Magstripe Mode Transaction)
	EMV_BOOL m_AMEX_Expresspay_Mobile_Flag; //TRUE(Expresspay Mobile) FALSE(Expresspay Card)
	EMV_BOOL m_AMEX_Delayed_Auth_Flag; //TRUE(Delayed Authorisations) FALSE(NOT)
	EMV_BOOL m_AMEX_Alternative_Interface_Flag; //TRUE ����ʧ�ܿ���ִ�������ӿ�.
	EMV_BYTE m_AMEX_ATC[3];
	EMV_UINT16 m_AMEX_ATCLen;

	// MIR
	EMV_BOOL m_MIR_Protocol_Flag; // EMV_TRUE Protocol Id "01" ���ƽ����ģʽ . "02"  MIR Q����
	EMV_UINT32 m_MIR_ODA;//�Ƿ�ִ��ODA

	//QUICS
	EMV_BOOL m_QUICS_OnlineODA;//QUICS ����ODA.

}EMV_TRANSACTION_DATA;

typedef EMV_TRANSACTION_DATA * LP_EMV_TRANSACTION_DATA;

/*****************************���½Ӵ�����*********************************/
// �ն����ò���
typedef struct{
	EMV_BYTE m_SupportSM;			//�Ƿ�֧�ֹ����㷨
	EMV_BYTE m_CardRefer; // �Ƿ�֧�ֿ�Ƭ�ο�
	EMV_BYTE m_EquippedPINPAD; // �Ƿ�����������
	EMV_BYTE m_EnterAmtSamePAD;// ����pin�Ƿ�ͬһ����
	EMV_BYTE m_MagFailtoIC[SIZE_TERMINAL_ENTRY_MODE*2+1]; // ����
	EMV_BYTE m_ActionRequired;// ��Կ����ʧ��,�Ƿ�����
	EMV_BOOL m_AppNotAllow_Flag;// Ӧ�ò�����
	EMV_BOOL m_BlockAddFlag;// ����Ƭ��־ʱ,������Ӧ���Ƿ�����ѡ�б�(1����,0������)
	EMV_BOOL m_ForcePrint;// ǿ�ƴ�ӡ
	EMV_BYTE m_TACDisableFlag;
	EMV_BYTE m_SupprrtShowPan;// �Ƿ�֧����ʾ����
	EMV_BYTE m_PbocHoldCardCheck;// pboc �ֿ���֤�����
	// ��ʱ������������,Ϊ�������Ӳ�������
	EMV_BYTE m_RFU1;
	EMV_BYTE m_RFU2;
	EMV_BYTE m_RFU3;
}EMV_KERNEL_CONFIG_ICC;

typedef EMV_KERNEL_CONFIG_ICC * LP_EMV_KERNEL_CONFIG_ICC;

typedef struct{
	EMV_CHAR m_PreferNameFlag; // �Ƿ����Ӧ���������Ƶı�־9f11
	EMV_BOOL m_NeedToSaveLog;// ����log
	EMV_UINT32 m_TransCounter;// ���׼�����
	EMV_BYTE m_TransType;// ��������
	EMV_UINT32 m_Amount;// ���׽��
	EMV_UINT32 m_AmountOther;// �������
	EMV_BOOL m_Online_Flag;// ������־
	EMV_BOOL m_Decline_Flag;// �ܾ���־
	EMV_BOOL m_PrintReceipt;// �����ӡ��־λ
	EMV_BOOL m_CDAAuthFlag;// �Ƿ�����cda�ı�־λ
	EMV_BOOL m_OfflineApprove;// �ѻ���׼�ı�־λ
	EMV_BYTE m_CDA_Data[MAX_CDA_DATA];// cda����
	EMV_UINT16 m_CDA_DataSize;// cda���ݳ�
	EMV_BYTE m_CardBySM;// ����tag����
	EMV_BYTE m_ECTSIVal;// ��������ֽ��ն�ָʾ����ֵ 9f7a
	EMV_INT32 m_EcBalance;// �����ֽ����
	EMV_UINT32 m_CTKernelCfgMode;// ��ǰ�Ӵ��ں˵�����
	MAG_TRACK_DATA m_MagTrackData;// �ŵ�����
	PIN_OFF_CIPHER_ITEM m_CipherItem;// �ѻ����ĵ�����
	EMV_BOOL m_GACNumCnt;// ��¼gac����,һ�ʽ�����෢��2gac
}EMV_TRANSACTION_ICC_DATA;

typedef EMV_TRANSACTION_ICC_DATA * LP_EMV_TRANSACTION_ICC_DATA;


/******************************************************************************/

/**
 * ���׹��̲���
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
	
	KERNEL_START_TYPE m_KernelStartCode; //����״̬.

	EMV_BOOL m_Discover_DPAS; //ȷ���� D-PAS , ZIP
	
	EMV_BOOL m_Mir_FlashCard;
	EMV_BOOL m_Mir_FlashCardReadRecord;
	EMV_BOOL m_Mir_FlashCardCompleteTransaction;
	EMV_BYTE m_Mir_PerformResp[270];
	EMV_UINT16 m_Mir_PerformRespSize;
	EMV_UINT32 m_MIR_Transaction_Recovery_Counter; //
	
	EMV_BOOL m_Mastrt_NoMsMOde; //���´ﲻ֧��MS.

	EMV_UINT8 m_KernelApplyAid; // �Ƿ�����AID�ǽ��޶�
	EMV_UINT32 m_LogLevel;
	EMV_TRANSACTION_DATA m_TransactionData;
	EMV_KERNEL_CONFIG_ICC m_KernelConfigIcc;// icc���� 
	EMV_TRANSACTION_ICC_DATA m_TransIccData;// icc����

};

typedef struct EMV_TRANS_HANDLE * LP_EMV_TRANS_HANDLE;

#ifdef __cplusplus
}
#endif

#endif
