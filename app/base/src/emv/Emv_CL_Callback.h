#ifndef EMV_CL_CALL_BACK_H_
#define EMV_CL_CALL_BACK_H_

extern KERNEL_MODE_TYPE m_KernelMode; //ִ���ں˰汾

#ifdef __cplusplus
extern   "C"
{
#endif
    ///< APDU
    int Kernel_CL_ExchangeApdu(const unsigned char *pApdu,
                               unsigned short uiApdu,
                               unsigned char *pResponse,
                               unsigned short *uiResponse,
                               unsigned char *pSW);

    ///< ��������(�Ӵ�,�ǽ�VISA,QPBOC,AMEX,D-PAS)
    void Kernel_CL_FinacialTransactionRequest(const char * pszOnlineEncipherPIN,
                                              unsigned char * pOnlineResult,
                                              char *pszIssueAuthData,
                                              unsigned short uiIssueAuthDataBuffSize,
                                              char *pszAC,
                                              unsigned short uiACBuffSize,
                                              char *pszAuthCode,
                                              unsigned short uiAuthCode,
                                              char *pszIssueScript,
                                              unsigned short uiScriptBuffSize);

    ///< ���׽�� Mastrt,MIR ����,�ѻ����� ���շ���ֵ����
    void Kernel_CL_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded);

    ///< �࿨��� . �жϵ�ǰ�Ƿ���ִ�зǽӿ�����
    unsigned char Kernel_CL_DetectBreak_Callback(void);

    ///< �ƿ�
    void Kernel_CL_AskRemoveCard(void);

    ///< �����Ŀ�
    char Kernel_CL_SecondTapCard(void);

    ///< ����PIN
    char Kernel_CL_GetOnlinePin(unsigned char bAllowBypass,
                                const char* pszPAN,
                                char* pszPinBlock,
                                unsigned short uiPinBlockBuffSize,
                                unsigned char * pbBypass);

#ifdef __cplusplus
}
#endif

#endif
