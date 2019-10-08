#ifndef EMV_UTILITY_H_
#define EMV_UTILITY_H_

#include "EMVTransHandle.h"


enum compare_result
{
	COMPARE_RESULT_EQUAL = 0,
	COMPARE_RESULT_SMALL,
	COMPARE_RESULT_BIG,
};

struct EMV_TRACK2_INFO {
	EMV_CHAR m_PAN[50];
	EMV_UINT16 ui_PAN;
	EMV_CHAR m_ExpirationDate[8 + 1];
	EMV_CHAR m_ServiceCode[8 + 1];
	EMV_CHAR m_DiscretionaryData[50];
	EMV_CHAR m_IDD[4 + 1];
};

typedef struct EMV_TRACK2_INFO * LP_EMV_TRACK2_INFO;
#ifdef __cplusplus
extern "C" {
#endif

EMV_UINT32 Single_Byte_Set(LP_EMV_TRANS_HANDLE pTransHandle, EMV_TAG tag, EMV_UINT16 uiItem);

EMV_BOOL Single_Byte_Check(LP_EMV_TRANS_HANDLE pTransHandle, EMV_TAG tag, EMV_UINT16 uiItem);

/************************************************************************/
/* TTQ    �ն˽�������                                                            */
/************************************************************************/
#define TTQ_SUPPORT_QVSDC					0x0120
#define TTQ_SUPPORT_CONTACT					0x0110
#define TTQ_SUPPORT_OFFLINE_ONLY			0x0108
#define TTQ_SUPPORT_ONLINE_PIN				0x0104
#define TTQ_SUPPORT_SIGNATURE				0x0102
#define TTQ_SUPPORT_ONLINE_ODA				0x0101
#define TTQ_REQUIRE_ONLINE					0x0280
#define TTQ_REQUIRE_CVM						0x0240
#define TTQ_SUPPORT_ISSUER_SCRIPT_UPDATE	0x0380
#define TTQ_SUPPORT_CDCVM					0x0340

/************************************************************************/
/* CTQ        ��Ƭ��������                                                       */
/************************************************************************/

#define CTQ_REQUIRE_ONLINE_PIN				0x0180
#define CTQ_REQUIRE_SIGNATURE				0x0140
#define CTQ_FDDA_FAIL_GO_ONLINE				0x0120
#define CTQ_FDDA_FAIL_SWITCH_INTERFACE		0x0110
#define CTQ_EXPIRED_GO_ONLINE				0x0108
#define CTQ_CASH_SWITCH_INTERFACE			0x0104
#define CTQ_CASHBACK_SWITCH_INTERFACE		0x0102
#define CTQ_NOT_VALID_FOR_ATM				0x0101

#define CTQ_PERFORM_CDCVM					0x0280
#define CTQ_SUPPORT_ISSUER_SCRIPT			0x0240

/************************************************************************/
/* TVR                                                                  */
/************************************************************************/
#define TVR_RESET                           0xFFFF 
#define TVR_OFFLINE_DATA_AUTH_NOT_PERFORM	0x0180 //δ�����ѻ�������֤
#define	TVR_SDA_FAILED						0x0140 //�ѻ���̬������֤ʧ��
#define	TVR_ICC_DATA_MISSING				0x0120 //IC������ȱʧ
#define	TVR_CARD_APPEARS_ON_EXECPTION_FILE	0x0110  // ��Ƭ�������ն��쳣�ļ���
#define	TVR_DDA_FAILED						0x0108 //�ѻ���̬������֤ʧ��
#define	TVR_CDA_FAILED						0x0104 //cdaʧ��
#define	TVR_SDA_SELECTED					0x0102 //sda-1 ѡ�� ,0 δѡ��(SDA Selected)

#define	TVR_APP_VERSION_IS_NOT_SAME			0x0280 // IC�����ն�Ӧ�ð汾��һ��
#define	TVR_EXPIRED_APPLICATION				0x0240 //Ӧ���ѹ���
#define	TVR_APP_NOT_EFFECTIVE				0x0220 //Ӧ����δ��Ч
#define	TVR_SERVICE_NOT_ALLOWED				0x0210 //��Ƭ������������ķ���
#define	TVR_NEW_CARD						0x0208 //�¿�

#define	TVR_CARDHOLDER_VERIFY_NOT_SUCCESS	0x0380 //�ֿ�����֤ʧ��
#define	TVR_UNRECOGNISED_CVM				0x0340 //δ֪�� CVM
#define	TVR_PIN_TRY_LIMIT_EXCEEDDED			0x0320 //PIN���Դ�������
#define	TVR_NEEDED_PINPAD_NOT_WORKING		0x0310 //Ҫ������ PIN����������̲����ڻ���������
#define	TVR_PIN_WAS_NOT_ENTERED				0x0308 //Ҫ������ PIN�� ������̴��ڣ���δ���� PIN
#define	TVR_ONLINE_PIN_ENTERED				0x0304 // �������� PIN

#define	TVR_EXCEEDS_FLOOR_LIMIT				0x0480 //���׳�������޶� 
#define	TVR_LOWER_OFFLINE_LIMIT_EXCEEDED	0x0440 //���������ѻ���������
#define	TVR_UPPER_OFFLINE_LIMIT_EXCEEDED	0x0420 //���������ѻ���������
#define	TVR_RANDOM_SELECTED_FOR_ONLINE		0x0410 //���ױ����ѡ����������
#define	TVR_FORCE_ONLINE					0x0408 //�̻�Ҫ����������

#define	TVR_DEFAULT_TDOL_USED				0x0580 //ʹ��ȱʡ TDOL
#define	TVR_ISSUER_AUTH_FAILED				0x0540 //��������֤ʧ��
#define	TVR_SCRIPT_FAILED_BEFORE_FINAL_GC	0x0520 //���һ�� GENERATE AC����֮ǰ�ű�����ʧ��
#define	TVR_SCRIPT_FAILED_AFTER_FINAL_GC	0x0510 //���һ�� GENERATE AC����֮��ű�����ʧ��

EMV_UINT32 EMV_TVR_Set(LP_EMV_TRANS_HANDLE pTransHandle, EMV_UINT16 uiItem);
EMV_BOOL EMV_TVR_Get(LP_EMV_TRANS_HANDLE pTransHandle, EMV_UINT16 uiItem);

/************************************************************************/
/* TSI                                                                  */
/************************************************************************/
#define TSI_RESET                           0xFFFF
#define	TSI_OFFLINE_DATA_AUTH_PERFORMED		0x0180 //�ѻ�������֤��ִ��
#define	TSI_CARDHOLDER_VERFIFY_PERFORMED	0x0140 //�ֿ�����֤��ִ��
#define	TSI_CARD_RISK_MAMANGE_PERFORMED		0x0120 //��Ƭ���չ�����ִ��
#define	TSI_ISSUER_AUTH_PERFORMED			0x0110 //��������֤��ִ��
#define	TSI_TERMINAL_RISK_PERFORMED			0x0108 //�ն˷��չ�����ִ��
#define	TSI_SCRIPT_PROCESS_PERFORMED		0x0104 //�ű�������ִ��

EMV_UINT32 EMV_TSI_Set(LP_EMV_TRANS_HANDLE pTransHandle, EMV_UINT16 uiItem);

#define AIP_SDA_SUPPORT						0x0140 // ֧�� SDA
#define AIP_DDA_SUPPORT						0x0120 //֧�� DDA
#define AIP_CVM_SUPPORT						0x0110 //֧�ֳֿ�����֤
#define AIP_TERM_RISKMANAGE_TOBE_PERFORM	0x0108 //ִ���ն˷��չ���
#define AIP_ISSUER_AUTH_SUPPORT				0x0104 //֧�ַ�������֤
#define AIP_CDA_SUPPORT						0x0101 //֧�� CDA

#define	AUC_DOMESTIC_CASH			0x0180 //�����ֽ�����Ч
#define	AUC_INTERNATIONAL_CASH		0x0140 //�����ֽ�����Ч
#define	AUC_DOMESTIC_GOODS			0x0120 //������Ʒ��Ч
#define	AUC_INTERNATIONAL_GOODS		0x0110 //������Ʒ��Ч
#define	AUC_DOMESTIC_SERVICE		0x0108 //���ڷ�����Ч
#define	AUC_INTERNATIONAL_SERVICE	0x0104 //���ʷ�����Ч
#define	AUC_ATM						0x0102 //ATM ��Ч
#define	AUC_TERMINAL				0x0101 //�� ATM ����ն���Ч

#define	AUC_DOMESTIC_CASHBACK		0x0280 //������ڷ���
#define	AUC_INTERNATIONAL_CASHBACK	0x0240 //������ʷ���

// �ն����� 9f33
#define	TERM_CAP_MANUAL_KEY_ENTRY	0x00000180 //�ֹ���������
#define	TERM_CAP_MAGNETIC_STRIPE	0x00000140 //����
#define	TERM_CAP_IC_WITH_CONTACTS	0x00000120 //�Ӵ�ʽ IC��
#define	TERM_CAP_PLAIN_PIN			0x00000280 //IC������ PIN��֤
#define	TERM_CAP_ONLINE_PIN			0x00000240 //���� PIN������֤
#define	TERM_CAP_SIGNATURE			0x00000220 //ǩ����ֽ��
#define	TERM_CAP_ENCIPHER_PIN		0x00000210 //�ѻ�����pin
#define	TERM_CAP_NO_CVM_REQUIRED	0x00000208 //���� CVM
#define TERM_CAP_PBOC_CEHCK_CREDENTIALS 0x00000201 //�ֿ���֤����֤ (pboc����)
#define	TERM_CAP_SDA				0x00000380 //��̬������֤�� SDA��
#define	TERM_CAP_DDA				0x00000340 //��̬������֤�� DDA��
#define	TERM_CAP_CARD_CAPTURE		0x00000320 //�̿�
#define	TERM_CAP_CDA				0x00000308 //CDA

// �ն˸������� 9f40
#define	TERM_CAP_ADDON_CASH			0x00010180 //�ֽ�
#define	TERM_CAP_ADDON_GOODS		0x00010140 //��Ʒ
#define	TERM_CAP_ADDON_SERVICES		0x00010120 //����
#define	TERM_CAP_ADDON_CASHBACK		0x00010110 //����
#define	TERM_CAP_ADDON_INQUIRY		0x00010108 //��ѯ
#define	TERM_CAP_ADDON_TRANSFER		0x00010104 //ת��
#define	TERM_CAP_ADDON_PAYMENT		0x00010102 //����
#define	TERM_CAP_ADDON_ADMIN		0x00010101 //����
#define	TERM_CAP_ADDON_CASH_DEPOSIT	0x00010280 //����

#define	TERM_CAP_ADDON_NUM_KEY				0x00010380 // ���ּ�
#define	TERM_CAP_ADDON_LETTER_AND_CHAR_KEY	0x00010340 // ��ĸ�������ַ���
#define	TERM_CAP_ADDON_CMD_KEY				0x00010320 // �����
#define	TERM_CAP_ADDON_FUNTION_KEY			0x00010310 // ���ܼ�

#define	TERM_CAP_ADDON_PRINT_WAITER			0x00010480 // ��ӡ��������Ա
#define	TERM_CAP_ADDON_PRINT_CARDHOLDER		0x00010440 // ��ӡ�����ֿ���
#define	TERM_CAP_ADDON_DISPLAY_WAITER		0x00010420 // ��ʾ��������Ա
#define	TERM_CAP_ADDON_DISPLAY_CARDHOLDER	0x00010410 // ��ʾ�����ֿ���
#define	TERM_CAP_ADDON_CODE_TABLE10			0x00010402 // ����� 10
#define	TERM_CAP_ADDON_CODE_TABLE9			0x00010401 // ����� 9

#define	TERM_CAP_ADDON_CODE_TABLE8			0x00010580 // ����� 8
#define	TERM_CAP_ADDON_CODE_TABLE7			0x00010540 // ����� 7
#define	TERM_CAP_ADDON_CODE_TABLE6			0x00010530 // ����� 6
#define	TERM_CAP_ADDON_CODE_TABLE5			0x00010510 // ����� 5
#define	TERM_CAP_ADDON_CODE_TABLE4			0x00010508 // ����� 4
#define	TERM_CAP_ADDON_CODE_TABLE3			0x00010504 // ����� 3
#define	TERM_CAP_ADDON_CODE_TABLE2			0x00010502 // ����� 2
#define	TERM_CAP_ADDON_CODE_TABLE1			0x00010501 // ����� 1


EMV_UINT32 AMEX_CVSResult_Set(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE Perform,
	EMV_BYTE Condition, EMV_BYTE Result);

EMV_BOOL EMV_Mobile_CVM_Support(LP_EMV_TRANS_HANDLE pTransHandle,
	EMV_UINT16 uiSupportItem);
	
/*??AIP????*/
EMV_BOOL EMV_AIP_Support(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT16 uiSupportItem);

/*���AUC�Ƿ�֧��*/
EMV_BOOL EMV_AUC_Support(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT16 uiSupportItem);

/*����ն�����(9f33��9f40)�Ƿ�֧��*/
EMV_BOOL EMV_TERM_CAP_Support(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiSupportItem);

/*�ն������Ƿ�֧������(9f35)*/
EMV_BOOL EMV_Term_CanGoOnline(LP_EMV_TRANS_HANDLE pTransHandle);

//�ն������Ƿ�ATM(9f35)
EMV_BOOL EMV_Term_IsATM(LP_EMV_TRANS_HANDLE pTransHandle);

//�ն������Ƿ�ֻ������(9f35)
EMV_BOOL EMV_Term_IsOnlineOnly(LP_EMV_TRANS_HANDLE pTransHandle);


EMV_UINT32 EMV_GetDataFromICC(LP_EMV_TRANS_HANDLE pTransHandle, EMV_TAG TagNum);

EMV_BOOL EMV_IsDataEqual(LP_EMV_TRANS_HANDLE pTransHandle, EMV_TAG TagNum1,
		EMV_TAG TagNum2);

EMV_BOOL EMV_IsDomesticTransaction(LP_EMV_TRANS_HANDLE pTransHandle);

/************************************************************************/
/* RSA                                                                  */
/************************************************************************/
EMV_BOOL RSA_Caculate(LPC_EMV_BYTE pModules, EMV_UINT16 uiModules,
		LPC_EMV_BYTE pExponents, EMV_UINT16 uiExponents,
		LPC_EMV_BYTE pDataInput, EMV_UINT16 uiDataInput,
		LP_EMV_BYTE pDataOutput, LP_EMV_UINT16 puiDataOutput);
/************************************************************************/
/* Format Convert                                                       */
/************************************************************************/
/*
 BIN ����ת����ASCII ��ʽ��16������
 ��:0xAB10 -> ת�����ַ���"AB10"
 Ҳ����������Ӧ��ѹ��BCD ��ʽת������ASCII ��ʽ��16��������
 */
EMV_BYTE EMV_Fmt_HexToNum(EMV_CHAR c);
EMV_BOOL EMV_Fmt_IsHexStr(LPC_EMV_CHAR pszHex);
EMV_BOOL EMV_Fmt_IsDecimalDigits(LPC_EMV_CHAR pszNum);

EMV_UINT32 EMV_Fmt_ByteArrayToInt(LP_EMV_BYTE buf, EMV_UINT16 bufLen);
EMV_UINT16 EMV_Fmt_BinaryToShort(LP_EMV_BYTE pData);
/*
 ASCII ��ʽ��16������ת����BIN ����
 ��:�ַ���"AB10" -> ת����0xAB10
 Ҳ�����ַ���ת����������Ҫ���ѹ��BCD�����ͣ�
 ��ȻBCD ���ַ����ֲ��ᳬ��9��������ܻᳬ��9
 */
EMV_BOOL EMV_Fmt_HexToBinary(LPC_EMV_CHAR pszHex, LP_EMV_BYTE pBuff,
		EMV_UINT16 uiBuffSize);

/*
 BIN ����ת����ASCII ��ʽ��16������
 ��:0xAB10 -> ת�����ַ���"AB10"
 Ҳ����������Ӧ��ѹ��BCD ��ʽת������ASCII ��ʽ��16��������
 */
EMV_VOID EMV_Fmt_BinaryToHex(LPC_EMV_BYTE pData, LP_EMV_CHAR pszHex,
		EMV_UINT16 uiDataSize);

EMV_BOOL EMV_Fmt_CheckDateFormat(LPC_EMV_BYTE pDate, EMV_UINT16 uiDate);
// ������ڸ�ʽ�Ƿ���Ч
EMV_CHAR EMV_CheckDateValid(LPC_EMV_BYTE date);
EMV_BOOL EMV_Fmt_CheckCVMFormat(LPC_EMV_BYTE pCVM, EMV_UINT16 uiCVM);

EMV_BOOL EMV_Date_Expired(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE bYear,
		EMV_BYTE bMonth);
EMV_BOOL EMV_Date_ExpiredEx(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE bYear,
		EMV_BYTE bMonth, EMV_BYTE bDay);
EMV_BOOL EMV_Date_EffectivedEx(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE bYear,
		EMV_BYTE bMonth, EMV_BYTE bDay);
EMV_BOOL EMV_Data_ExpiredFormat(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE bYear,
	EMV_BYTE bMonth, EMV_BYTE bDay);
EMV_BOOL EMV_Data_EffectivedFormat(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE bYear,
	EMV_BYTE bMonth, EMV_BYTE bDay);

EMV_UINT32 EMV_CVSResult_Reset(LP_EMV_TRANS_HANDLE pTransHandle);
EMV_UINT32 EMV_CVSResult_Set(LP_EMV_TRANS_HANDLE pTransHandle, EMV_BYTE Perform,
		EMV_BYTE Condition, EMV_BYTE Result);
EMV_BOOL EMV_IsAttendTerminal(LP_EMV_TRANS_HANDLE pTransHandle);

EMV_UINT32 EMV_PrepareTerminalData(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_BYTE TransType, EMV_UINT32 uiTransCountNumber,
		EMV_BOOL bAccountType, EMV_BYTE AccountType);
// {0x00,0x00,0x03}->3(long)
EMV_UINT64 EMV_StrToLongByLen(LP_EMV_BYTE str, EMV_UINT16  ucLen);
// ���ý��
EMV_UINT32 EMV_SetTransactionAmount(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiAmount, EMV_UINT32 uiAmountOther);

EMV_VOID QVSDC_BitSet(LP_EMV_BYTE pData, EMV_UINT16 bitSet);
EMV_BOOL QVSDC_BitGet(LP_EMV_BYTE pData, EMV_UINT16 bitSet);

EMV_BOOL AMEX_DateLegitimate(EMV_UINT32 year, EMV_UINT32 month, EMV_UINT32 day);
EMV_BOOL AMEX_GetDDfromTrack2(LP_EMV_BYTE pDD, LP_EMV_UINT16 pDDLen);
EMV_BOOL AMEX_GetDDfromTrack1(LP_EMV_BYTE pDD, LP_EMV_UINT16 pDDLen, LP_EMV_BYTE pExpirationData, LP_EMV_UINT16 pEDLen);
EMV_VOID AMEX_CalculationTime(EMV_UINT16 iYear, EMV_UINT16 iMon, EMV_UINT32 PayTimeout, LP_EMV_UINT16 outYear, LP_EMV_UINT16 outMon);

EMV_BYTE Mastrt_GetNonZeroBit(LP_EMV_BYTE data, EMV_UINT16 len);

EMV_BOOL Mastrt_GetDDfromTrack1(LP_EMV_CHAR pDD, LP_EMV_UINT16 pDDLen);
EMV_VOID Mastrt_SetDDToTrack1(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR pDD);
EMV_BOOL Mastrt_GetDDfromTrack2(LP_EMV_BYTE pDD, LP_EMV_UINT16 pDDLen);
EMV_VOID Mastrt_SetDDToTrack2(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_CHAR pStrDD);

EMV_UINT16 Mastrt_CompareAmt(LP_EMV_TRANS_HANDLE pTransHandle, EMV_TAG tagx, EMV_TAG tagy);
EMV_BOOL Mastrt_PCIIAndMaskEqualValue(LP_EMV_TRANS_HANDLE pTransHandle, LP_EMV_BYTE pMask, LP_EMV_BYTE pValue);


EMV_BYTE Discover_TrackLRC(LP_EMV_BYTE data, EMV_INT32 length);

EMV_BOOL Discover_GetTrack(LP_EMV_TRACK2_INFO mTrack2);

#ifdef __cplusplus
}
#endif
#endif
