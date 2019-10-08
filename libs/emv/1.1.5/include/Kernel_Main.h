#ifndef KERNEL_MAIN_H_
#define KERNEL_MAIN_H_

#include "EmvDataType.h"
#include "Kernel_Param.h"
#include "AppCallBack.h"


extern struct KERNEL_CALLBACK_FUNCS __CALL_BACK_KERNEL; //�ں˻ص����ⲿCӦ��ʹ��

enum STEP_ENTRY_POINT_STEP {
	ENTRY_POINT_START_A = 0xA0,
	ENTRY_POINT_START_B,
	ENTRY_POINT_START_C,
	ENTRY_POINT_START_D,

	ENTRY_POINT_START_DONE,

};

#define TAG_KERNEL_ENTRY_POINT_STATE							0xDF1A

//----------------------------------------------------------------------------------------
#define TAG_CONTAINER											0x7F00
#define TAG_DEK_DET_DATA										0x7F10
#define TAG_TXN_DATA											0x7F11
#define TAG_FCI_DATA											0x7F12
#define TAG_SYNC_DATA											0x7F13
#define TAG_ICS_DATA											0x7F14
//----------------------------------------------------------------------------------------
#define CORRESPONDING_SIGNAL									0xDF71
#define	CORRESPONDING_SIGNAL_ACT								0xA0
#define CORRESPONDING_SIGNAL_STOP								0xA1
#define CORRESPONDING_SIGNAL_CLEAN								0xA2
#define CORRESPONDING_SIGNAL_DET								0xA3
#define CORRESPONDING_SIGNAL_RA									0xA4
#define	CORRESPONDING_SIGNAL_L1RSP								0xA5
#define	CORRESPONDING_SIGNAL_TIMEOUT							0xA6

//----------------------------------------------------------------------------------------
#define CORRESPONDING_SIGNAL_L1RSP_TIME_OUT_ERROR				0xA1
#define CORRESPONDING_SIGNAL_L1RSP_PROTOCOL_ERROR				0xA1
#define CORRESPONDING_SIGNAL_L1RSP_TRANSMISSION_ERROR			0xA1
//----------------------------------------------------------------------------------------
typedef struct {
	unsigned char signal_type; /* DET, RA, STOP, CLEAN, TIMEOUT, ACT */
	unsigned char* syn_data;
	unsigned int syn_data_len;
} Signal_Message; //

//---------------------------------------------------------------------------------------- ����
#define CMD_NOTHING_TO_DO										0xD0
#define CMD_REQUEST_ICS											0xD1
#define CMD_REQUEST_AID_LIST									0xD2
#define CMD_REQUEST_AID_PARAM									0xD3
#define CMD_REQUEST_PKI											0xD4
#define CMD_REQUEST_UNPREDICATABLE_NUMBER						0xD5 //�������ȡ
#define CMD_REQUEST_DETECT_BREAK								0xD6 //�࿨��ͻ

#define CMD_DISPLAY_UIRD_MSG									0xD7  // �ƿ�
#define CMD_DISPLAY_TRANS_REPORT							    0xD8 // ��ʾ���׽��
#define CMD_TRANSACTION_FINACIAL_REQUEST  						0xD9
#define CMD_TRANSACTION_AUTH_REQUSET							0xDA
#define CMD_SECOND_TAP_CARD										0xDB
#define CMD_CVM_ONLINE_PIN										0xDC

#define CMD_TRANSACTION_DECLINED								0xDC
#define CMD_TRANSACTION_TERMINATE								0xDD
#define CMD_TRANSACTION_ITEM_REQUEST							0xDE
#define CMD_TRANSACTION_FIELD_OFF								0xDF
#define CMD_CARDHOLDER_CONFIRMATION								0xE1
#define CMD_CVM_OFFLINE_PIN										0xE2

#define CMD_GET_TXN_LOG											0xE4
#define CMD_GET_TOP_UP_LOG										0xE5
#define CMD_REQUEST_EXCEPTION_FILE								0xE6
#define CMD_GET_BALANCE											0xE7
#define CMD_LED_BLINK											0xE8
#define CMD_REQUEST_PKI_IPK_REVO								0xE9
#define CMD_TRANSMIT_DEK										0xEA
#define CMD_TRANSMIT_APDU_KERNEL								0xF1 // apdu

#define CMD_TIMER_START											0xF3
#define CMD_TIMER_STOP											0xF4
#define CMD_REQUEST_TORN_BUFFER									0xF5
#define CMD_REQUEST_FAILED_MS_CNTR_BUFFER						0xF6
#define CMD_WAIT_BY_APP_MS										0xF7

#define CMD_OUT_SIGNAL_ENTRYPOINT								0xFE
#define CMD_PRINT_MSG_DEBUG										0xFF

//#define TAG_USER_INTERFACE_REQUEST_DATA							0xDF8116  del by wl 
#define TAG_APDU_EXCHANGE										0xDF01
#define TAG_LCD_MESSAGE_ID										0xDF02
#define TAG_MESSAGE_DEBUG										0xDF03
#define TAG_MESSAGE_DEBUG_HEX									0xDF04
#define TAG_PAN_IN_EXCEPTION_FILE								0xDF05
#define TAG_TIMIEOUT_VALUE										0xDF06
//----------------------------------------------------------------------------------------

//----------------------- ���ؽ��----9f72-------------------------------------------------------------
#define  CONTACTLESS_OPS_LENGTH   (8)
#define  CONTACTLESS_OPS_STATUS_BYTE   (0)
#define  CONTACTLESS_OPS_STATUS_APPROVED   0x10  // �ѻ�����
#define  CONTACTLESS_OPS_STATUS_DECLINED   0x20  // �ѻ��ܾ�
#define  CONTACTLESS_OPS_STATUS_ONLINE_REQUEST   0x30  // ��������
#define  CONTACTLESS_OPS_STATUS_END_APPLICATION   0x40
#define  CONTACTLESS_OPS_STATUS_SELECT_NEXT   0x50
#define  CONTACTLESS_OPS_STATUS_TRY_ANOTHER_INTERFACE   0x60
#define  CONTACTLESS_OPS_STATUS_TRY_AGAIN   0x70
#define  CONTACTLESS_OPS_STATUS_ONLINE_DECLINED   0x80  // �����ܾ�
#define  CONTACTLESS_OPS_STATUS_NA   0xF0
#define  CONTACTLESS_OPS_START_BYTE   (1)
#define  CONTACTLESS_OPS_START_A   0x00
#define  CONTACTLESS_OPS_START_B   0x10
#define  CONTACTLESS_OPS_START_C   0x20
#define  CONTACTLESS_OPS_START_D   0x30
#define  CONTACTLESS_OPS_START_NA   0xF0
#define  CONTACTLESS_OPS_ONLINE_RESPONSE_DATA_BYTE   (2)
#define  CONTACTLESS_OPS_ONLINE_RESPONSE_DATA_NA   0xF0
#define  CONTACTLESS_OPS_CVM_BYTE   (3)
#define  CONTACTLESS_OPS_CVM_NO_CVM   0x00   // no cvm
#define  CONTACTLESS_OPS_CVM_SIGNATURE   0x10  // ǩ��
#define  CONTACTLESS_OPS_CVM_ONLINE_PIN   0x20 // cvm����
#define  CONTACTLESS_OPS_CVM_CONFIRMATION_CODE_VERIFIED   0x30
#define  CONTACTLESS_OPS_CVM_NA   0xF0
#define  CONTACTLESS_OPS_DATA_PRESENCE_BYTE   (4)
#define  CONTACTLESS_OPS_DATA_PRESENCE_MASK_UIR_ON_OUTCOME   0x80
#define  CONTACTLESS_OPS_DATA_PRESENCE_MASK_UIR_ON_RESTART   0x40
#define  CONTACTLESS_OPS_DATA_PRESENCE_MASK_DATA_RECORD   0x20
#define  CONTACTLESS_OPS_DATA_PRESENCE_MASK_DISCRET_DATA   0x10
#define  CONTACTLESS_OPS_DATA_PRESENCE_MASK_RECEIPT   0x08
#define  CONTACTLESS_OPS_ALTERNATIVE_INTERFACE_PREF_BYTE   (5)
#define  CONTACTLESS_OPS_ALTERNATIVE_INTERFACE_PREF_NA   0xF0
#define  CONTACTLESS_OPS_FIELD_OFF_REQUEST_BYTE   (6)
#define  CONTACTLESS_OPS_FIELD_OFF_REQUEST_NA   0xFF
#define  CONTACTLESS_OPS_REMOVAL_TIMEOUT_BYTE   (7)


// ���彻�׽�� 9f72
typedef struct STRUCT_Outcome_Parameter_Set {
	unsigned char Status;
	unsigned char Start;
	unsigned char Online_Response_Data;
	unsigned char CVM;
	unsigned char Presence;
	unsigned char Alternate_Interface_Preference;
	unsigned char Field_Off_Request;
	unsigned char Removal_Timeout;

} STRUCT_Outcome_Parameter_Set;

/*  �ظ�����
#define  CONTACTLESS_OPS_CVM_SIGNATURE						0x10
#define  CONTACTLESS_OPS_CVM_ONLINE_PIN						0x20
#define  CONTACTLESS_OPS_CVM_CONFIRMATION_CODE_VERIFIED		0x30
#define  CONTACTLESS_OPS_CVM_NA								0xF0
*/

//-------------------------------------------------------------------------------------------

//-----------------------------9f73��ʾ�����Ӧ��ֵ--------------------------------------- //������ʾ
#define  CONTACTLESS_UIRD_LENGTH   (22)
#define  CONTACTLESS_UIRD_MESSAGE_ID_BYTE   (0)
#define  CONTACTLESS_UIRD_MESSAGE_ID_PRESENT_CARD   0x15 //Present Card
#define  CONTACTLESS_UIRD_MESSAGE_ID_PROCESSING   0x16
#define  CONTACTLESS_UIRD_MESSAGE_ID_CARD_READ_OK   0x17 // �����ɹ�
#define  CONTACTLESS_UIRD_MESSAGE_ID_TRY_AGAIN   0x21
#define  CONTACTLESS_UIRD_MESSAGE_ID_APPROVED   0x03 // �ѻ�����
#define  CONTACTLESS_UIRD_MESSAGE_ID_APPROVED_SIGN   0x1A  // ǩ��
#define  CONTACTLESS_UIRD_MESSAGE_ID_ONLINE_REQUEST_APPROVED   0x04 // ��������
#define  CONTACTLESS_UIRD_MESSAGE_ID_ONLINE_DECLINED   0x05  // �����ܾ�
#define  CONTACTLESS_UIRD_MESSAGE_ID_OFFLINE_DECLINED   0x06 // �ѻ��ܾ�
#define  CONTACTLESS_UIRD_MESSAGE_ID_DECLINED   0x07
#define  CONTACTLESS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD   0x1C  // ��Ƭ���ݴ���
#define  CONTACTLESS_UIRD_MESSAGE_ID_SEE_PHONE   0x20
#define  CONTACTLESS_UIRD_MESSAGE_ID_AUTHORISING_PLEASE_WAIT   0x1B // ��Ȩ��ȴ�
#define  CONTACTLESS_UIRD_MESSAGE_ID_INSERT_CARD   0x1D  // ��忨
#define  CONTACTLESS_UIRD_MESSAGE_ID_CLEAR_DISPLAY   0x1E // ����
#define  CONTACTLESS_UIRD_MESSAGE_ID_TERMINATED_CONTACT 0x08   // �Ӵ�
#define  CONTACTLESS_UIRD_MESSAGE_ID_TERMINATED_SWIPE   0x09  // ˢ��
#define  CONTACTLESS_UIRD_MESSAGE_ID_NA   0xFF
#define  CONTACTLESS_UIRD_STATUS_BYTE   (1)
#define  CONTACTLESS_UIRD_STATUS_NOT_READY   0x00
#define  CONTACTLESS_UIRD_STATUS_IDLE   0x01
#define  CONTACTLESS_UIRD_STATUS_READY_TO_READ   0x02
#define  CONTACTLESS_UIRD_STATUS_PROCESSING   0x03
#define  CONTACTLESS_UIRD_STATUS_CARD_READ_SUCCESSFULLY   0x04
#define  CONTACTLESS_UIRD_STATUS_PROCESSING_ERROR   0x05
#define  CONTACTLESS_UIRD_STATUS_NA   0xFF
#define  CONTACTLESS_UIRD_HOLD_TIME_OFFSET   (2)
#define  CONTACTLESS_UIRD_HOLD_TIME_LENGTH   (3)
#define  CONTACTLESS_UIRD_LANGUAGE_PREFERENCE_OFFSET   (5)
#define  CONTACTLESS_UIRD_LANGUAGE_PREFERENCE_LENGTH   (8)
#define  CONTACTLESS_UIRD_VALUE_QUALIFIER_BYTE   (13)
#define  CONTACTLESS_UIRD_VALUE_QUALIFIER_NONE   0x00
#define  CONTACTLESS_UIRD_VALUE_QUALIFIER_AMOUNT   0x10
#define  CONTACTLESS_UIRD_VALUE_QUALIFIER_BALANCE   0x20
#define  CONTACTLESS_UIRD_VALUE_OFFSET   (14)
#define  CONTACTLESS_UIRD_VALUE_LENGTH   (6)
#define  CONTACTLESS_UIRD_CURRENCY_CODE_OFFSET   (20)
#define  CONTACTLESS_UIRD_CURRENCY_CODE_LENGTH   (2)



// ���彻�׽ӿ���ʾ��tag 9f73
typedef struct STRUCT_User_Interface_Request_Data {
	unsigned char MessageIdentifier;// ��Ϣ��ʶ��
	unsigned char Status;// ����״̬
	unsigned char HoldTime[3];// ʱ��
	unsigned char LanguagePreference[8];
	unsigned char ValueQualifier;
	unsigned char Value[6];
	unsigned char CurrencyCode[2];// ���Ҵ���

} STRUCT_User_Interface_Request_Data;


#define	TAG_KERNEL_DATA_RECORD									0x9F71	// ���ڱ��潻��ʹ�õ�tag
#define	TAG_OUTCOME_PARAMETER_SET								0x9F72  // ���ڱ��潻�׽��
#define TAG_USER_INTERFACE_REQUEST_DATA							0x9F73  // ���ڱ��潻��״̬
//-------------------------------------------------------------------------------------------

#define  CONTACTLESS_EI_LENGTH   (6)
#define  CONTACTLESS_EI_L1_BYTE   (0)
#define  CONTACTLESS_EI_L1_OK   0x00
#define  CONTACTLESS_EI_L1_TIMEOUT_ERROR   0x01
#define  CONTACTLESS_EI_L1_TRANSMISSION_ERROR   0x02
#define  CONTACTLESS_EI_L1_PROTOCOL_ERROR   0x03
#define  CONTACTLESS_EI_L2_BYTE   (1)
#define  CONTACTLESS_EI_L2_OK   0x00
#define  CONTACTLESS_EI_L2_CARD_DATA_MISSING   0x01
#define  CONTACTLESS_EI_L2_CAM_FAILED   0x02
#define  CONTACTLESS_EI_L2_STATUS_BYTES   0x03
#define  CONTACTLESS_EI_L2_PARSING_ERROR   0x04
#define  CONTACTLESS_EI_L2_MAX_LIMIT_EXCEEDED   0x05
#define  CONTACTLESS_EI_L2_CARD_DATA_ERROR   0x06
#define  CONTACTLESS_EI_L2_MAGSTRIPE_NOT_SUPPORTED   0x07
#define  CONTACTLESS_EI_L2_NO_PPSE   0x08
#define  CONTACTLESS_EI_L2_PPSE_FAULT   0x09
#define  CONTACTLESS_EI_L2_EMPTY_CANDIDATE_LIST   0x0A
#define  CONTACTLESS_EI_L2_IDS_READ_ERROR   0x0B
#define  CONTACTLESS_EI_L2_IDS_WRITE_ERROR   0x0C
#define  CONTACTLESS_EI_L2_IDS_DATA_ERROR   0x0D
#define  CONTACTLESS_EI_L2_IDS_NO_MATCHING_AC   0x0E
#define  CONTACTLESS_EI_L2_TERMINAL_DATA_ERROR   0x0F
#define  CONTACTLESS_EI_L3_BYTE   (2)
#define  CONTACTLESS_EI_L3_OK   0x00
#define  CONTACTLESS_EI_L3_TIMEOUT   0x01
#define  CONTACTLESS_EI_L3_STOP   0x02
#define  CONTACTLESS_EI_L3_AMOUNT_NOT_PRESENT   0x03
#define  CONTACTLESS_EI_SW12_OFFSET   (3)
#define  CONTACTLESS_EI_SW12_LENGTH   (2)
#define  CONTACTLESS_EI_MSG_ON_ERROR_BYTE   (5)

typedef struct STRUCT_Error_Indication {
	unsigned char L1;
	unsigned char L2;
	unsigned char L3;
	unsigned char SW12[2];
	unsigned char MsgOnError;

} STRUCT_Error_Indication;

/* ------------------------------------------------------------------------------ */

#ifndef WIN32
#define ENTRY_POINT_API
#endif

#ifndef ENTRY_POINT_API
#ifdef KERNEL_ENTRYPOINT_EXPORTS
#define ENTRY_POINT_API __declspec(dllexport)
#else
#define ENTRY_POINT_API __declspec(dllimport)
#endif
#endif


/**
* ��ʼ������
*/
unsigned int Contactless_init_EntryKernel(LPC_KERNEL_CALLBACK_FUNCS pCallbackFuncs);


/**
* ��ʼ���Ӵ��ں˻ص�
*/
EMV_UINT32 Contact_init_EntryKernel(LPC_KERNEL_CALLBACK_FUNCS pCallbackFuncs);

/**
 * ���׿�ʼ
 */
unsigned int Contactless_Start_Kernel(unsigned int uiTarnsCounter,
	unsigned char TransType, unsigned int Amount, unsigned int AmountOther);

/**
 * �������
 */
unsigned int Contactless_Clean_Kernel(void);

/**
 * ���׹����� ��������
 */
unsigned int Contactless_Kernel_Customized(void* buffer);

/**
* ��ȡ�ں˰汾
*/
unsigned int Contactless_Get_VersionKernel(char * pBuffer, unsigned int uiBufferSize);


/**
* �����ں� Ԥ������� �Ƿ�ʹ�� AID �ж���Ĳ���
*/
unsigned int Contactless_Set_KernelApplyAid(int parameter);

/**
* �����ں˰汾 EMV_TRUE Quics EMV_FALSE QPBOC,ֻ���ڹ�����֤. QUICS,QPBOC �л�.
*/
unsigned int Contactless_Set_Kernel_Version(int uiVersion);

/**
* ���׹����л�ȡ����Ƭ��������
*/
unsigned int Contactless_GetTransData(unsigned int Tag, unsigned char* pValue,
	unsigned short * puiValue);

unsigned int Contactless_GetTransDataAsHex(unsigned int Tag, char* pszValue,
	unsigned short uiBuffSize);


//���� PPSE + Select ����
unsigned int Contactless_SelectWithoutGPO(unsigned char bPPSE);

//ִ�и÷�����Ҫ �ȵ��� Contactless_SelectWithoutGPO ���ڵ���.
unsigned int Contactless_ReadCardLog(unsigned char count, unsigned char * szTempRecord, unsigned char * uiTempRecord);

//���� getData APDU ָ���ȡ.
unsigned int Contactless_GetDataFromICC(unsigned int Tag, unsigned char* pValue,
	unsigned short * puiValue);

// ��ȡ����
unsigned int Contactless_GetPAN(char *pszBuff,int uiSize);

/*
�Ӵ��쳣����쿨
bFallBackFlag:����
bInsertCardFlag:�Ƿ��ǲ忨
pMagTrackData:��������
*/
CT_DETECT_MODE EMV_Contact_DetectCard(EMV_UINT32 uiCallbackHandle, EMV_CHAR bFallBackFlag, EMV_CHAR bInsertCardFlag,
	LP_MAG_TRACK_DATA pMagTrackData);

#endif //_ENTRY_POINT_H_
