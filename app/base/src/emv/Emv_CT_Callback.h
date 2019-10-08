#ifndef EMV_CT_CALL_BACK_H_
#define EMV_CT_CALL_BACK_H_

#ifdef __cplusplus
extern   "C"
{
#endif

///< APDU
int Kernel_CT_ExchangeApdu(const unsigned char* pApdu,
                           unsigned short uiApdu,
                           unsigned char* pResponse,
                           unsigned short* uiResponse);

///< ��Ӧ��ѡ��
char Kernel_CT_SelectApplication(const char** ppAppNames,
                                 const char** ppAppAids,
                                 unsigned short uiAppCount,
                                 unsigned short* puiSelected);

///< ��ʾ���˺���Ϣ
char Kernel_CT_Display_PanNo(char *pPanNo);

///< �ֿ���ȷ��
char Kernel_CT_CardHolderConfirm(const char* pAID,
                                 const char* pAppName,
                                 const char* pPreferAppName);

void Kernel_CT_AfterAppSelected(void);

char Kernel_CT_LanguageSelect(char* pszLanguages, char bIsPSESelect);

///< ��Ȩ������
void Kernel_CT_AuthorisationRequest(const char* pszOnlineEncipherPIN,
                                    unsigned char* pOnlineResult,
                                    char* pszIssueAuthData,
                                    unsigned short uiIssueAuthDataBuffSize,
                                    char* pszAC,
                                    unsigned short uiACBuffSize,
                                    char* pszAuthCode,
                                    unsigned short uiAuthCode,
                                    char* pszIssueScript,
                                    unsigned short uiScriptBuffSize);

///< ����������
void Kernel_CT_FinacialTransactionRequest(const char* pszOnlineEncipherPIN,
                                          unsigned char* pOnlineResult,
                                          char* pszIssueAuthData,
                                          unsigned short uiIssueAuthDataBuffSize,
                                          char* pszAC,
                                          unsigned short uiACBuffSize,
                                          char* pszAuthCode,
                                          unsigned short uiAuthCode,
                                          char* pszIssueScript,
                                          unsigned short uiScriptBuffSize);

///< ���׽�� Mastrt,MIR ����,�ѻ����� ���շ���ֵ����
void Kernel_CT_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded);

///< �ѻ�����pin
char Kernel_Contact_GetPlainTextPin(unsigned char bAllowBypass,
                                    char* pszPIN,
                                    unsigned short uiPinBuffSize,
                                    char bPinTryCnt,
                                    int* bVerifyPinTryCnt,
                                    LP_EMV_CV_VERIFY_RESULT pVerifyResult);

///< �ѻ�����pin
char Kernel_Contact_GetOfflineCipherPin(unsigned char bAllowBypass,
                                        LP_PIN_OFF_CIPHER_ITEM pPinCipherItem,
                                        char bPinTryCnt,
                                        int* bVerifyPinTryCnt,
                                        char* pszPinBlock,
                                        unsigned short uiPinBlockBuffSize,
                                        LP_EMV_CV_VERIFY_RESULT pVerifyResult);

///< ��������pin
char Kernel_Contact_GetOnlinePin(unsigned char bAllowBypass,
                                 const char* pszPAN,
                                 char* pszPinBlock,
                                 unsigned short uiPinBlockBuffSize,
                                 LP_EMV_CV_VERIFY_RESULT pVerifyResult);

// �ֿ���֤����֤
char Kernel_Contact_GetHolderCert(const char* pConfirmMsg, int uiConfirmMsg, const char* pHoldCert, int uiHoldCert);

// �����ο�(����)
char Kernel_Contact_PanConfirm(const char* pPAN);

char Kernel_Contact_SelAppErr(void);

char Kernel_MagStripe_OnlineRequeset(char* pOnlinePin, char* pResCode);

#ifdef __cplusplus
}
#endif

#endif
