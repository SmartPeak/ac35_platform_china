#ifndef EMV_CL_CALL_BACK_H_
#define EMV_CL_CALL_BACK_H_

extern KERNEL_MODE_TYPE m_KernelMode; //执行内核版本

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

    ///< 联机处理(接触,非接VISA,QPBOC,AMEX,D-PAS)
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

    ///< 交易结果 Mastrt,MIR 联机,脱机处理 按照返回值处理
    void Kernel_CL_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded);

    ///< 多卡检查 . 判断当前是否在执行非接卡交易
    unsigned char Kernel_CL_DetectBreak_Callback(void);

    ///< 移卡
    void Kernel_CL_AskRemoveCard(void);

    ///< 二次拍卡
    char Kernel_CL_SecondTapCard(void);

    ///< 联机PIN
    char Kernel_CL_GetOnlinePin(unsigned char bAllowBypass,
                                const char* pszPAN,
                                char* pszPinBlock,
                                unsigned short uiPinBlockBuffSize,
                                unsigned char * pbBypass);

#ifdef __cplusplus
}
#endif

#endif
