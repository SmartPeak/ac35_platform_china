#ifndef EMV_CALL_BACK_H_
#define EMV_CALL_BACK_H_

typedef enum{
    DEVICC = 0x00,
    DEVPICC,
    DEVMAG
} DEV_MODE;


#define TRANS_HANDLE_FF         0xfffff

typedef struct{
    int         ret;
    DEV_MODE    drvMode;

    unsigned char   bEmvInputPINBypass;
    unsigned char   *ARPC;          ///< 后台返回的临时ARPC
    unsigned short  ARPCLen;        ///< 后台返回的临时ARPC长度
    //
    unsigned char *pScriptData;
    unsigned int scriptDataLen;
    int (*ScriptResultSave)(void);
    void (*getErrCode)(int iResCode, char *resCode);
} TRANS_HANDLE;


extern TRANS_HANDLE _TRANS_HANDLE;

#ifdef __cplusplus
extern   "C"
{
#endif

    ///< 内核日志打印
    void Kernel_Log_Printf(const char * pszMessage, unsigned int len);

    ///< 获取终端时间
    void Kernel_GetCurrentTime(LP_EMV_TIME pCurrentTime);

    ///< 获取随机数
    void Kernel_GetRandomData(unsigned char* pRandBuff, unsigned short uiSize);

    ///< SM2加密
    char Kernel_SM2VerifySign(unsigned char* pSMPubKey,
                              unsigned char* bVerifyData,
                              int uiVerifyData,
                              unsigned char* bSignature,
                              int uiSignature);

    ///< SM3哈希加密
    char Kernel_SM3Hash(unsigned char* pVerifySM3,
                        int uiVerifySM3,
                        unsigned char* pSM3Hash,
                        int *uiSM3Hash);

    char Kernel_ExchangeApdu(const unsigned char *pApdu,
                             unsigned short uiApdu,
                             unsigned char *pResp,
                             unsigned short *uiResp);

    ///< 交易结果 Mastrt,MIR 联机,脱机处理 按照返回值处理
    void Kernel_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded);

    ///< 联机处理(接触,非接VISA,QPBOC,AMEX,D-PAS)
    void Kernel_FinacialTransactionRequest(const char* pszOnlineEncipherPIN,
                                           unsigned char* pOnlineResult,
                                           char *pszIssueAuthData,
                                           unsigned short uiIssueAuthDataBuffSize,
                                           char* pszAC,
                                           unsigned short uiACBuffSize,
                                           char* pszAuthCode,
                                           unsigned short uiAuthCode,
                                           char* pszIssueScript,
                                           unsigned short uiScriptBuffSize);

    ///< 金额输入
    char Kernel_EnterAmount(unsigned int *pAmount, unsigned int *pAmountOther);

    ///< 指示当前是ic、picc或磁条
    void Kernel_CL_KernelMode(unsigned int uiKernelMode);

#ifdef __cplusplus
}
#endif

#endif
