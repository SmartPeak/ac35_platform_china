#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "mmi_printer.h"
#include "uFile.h"
#include "trans.h"
#include "cashier.h"

struct _ErrMsg
{
    int         errIndex;
    char*       errMsg;
};

struct _HostErrMsg
{
    char        errCode[2];
    char*       errMsg;
};

#define MAX_INDEX       0xFFFF
static const struct _ErrMsg errMsgTab[] =
{
    {ERR_END,                    AMSG_Err_End},
    {ERR_CANCEL,                 AMSG_Err_Cancel},
    {ERR_TIMEOUT,                AMSG_Err_Timeout},
    {ERR_PARAM,                  AMSG_Err_ParamErr},
    {ERR_DRV,                    AMSG_Err_DriverErr},
    {ERR_MIF_DRV,                AMSG_Err_MfDriverErr},
    {ERR_ICC_DRV,                AMSG_Err_IccDriverErr},
    {ERR_SCAN_DRV,               AMSG_Err_ScanDriverErr},
    {ERR_MAG_DRV,                AMSG_Err_MagneticTrackDriverErr},
    {ERR_PRINTER,                AMSG_Err_PrinterDriverErr},

    ///< ----
    {ERR_SOCKET,                 AMSG_Err_CommuErr},
    {ERR_HOSTCODE,               AMSG_Err_ServerReturnErr},
    {ERR_COMMU_PARAM,            AMSG_Err_CommuParamErr},
    {ERR_COMMU_CONNECT,          AMSG_Err_NetworkConnectFail},
    {ERR_COMMU_SEND,             AMSG_Err_DataSendFail},
    {ERR_COMMU_RECV,             AMSG_Err_DataReceiveFail},

    ///< ----
    {ERR_SECREKEY_SAVE,          AMSG_Err_KeyStoreFail},
    {ERR_SECREKEY_DATA_ERR,      AMSG_Err_KeyDataErr},
    {ERR_SECREKEY_ENCRYPTION,    AMSG_Err_EncryptionFail},
    {ERR_SAVE_KEY_KCV,           AMSG_Err_KeyCheckErr},
    {ERR_CALC_KEY_KCV,           AMSG_Err_WorkKeyErr},
    {ERR_MAC,                    AMSG_Err_MACCheckErr},

    ///< ----
    {ERR_DATA_OVERFLOW,          AMSG_Err_CacheOverflow},
    {ERR_DATA_INVALID,           AMSG_Err_InvalidData},
    {ERR_DATA_PACK,              AMSG_Err_LoadDataErr},
    {ERR_DATA_UPACK,             AMSG_Err_ParsingDataErr},
    {ERR_SM2_SIGN,               AMSG_Err_AttestationErr},

    {ERR_NOT_LOGON,              AMSG_Err_NotLogon},
    {ERR_PLZ_SETTLE,             AMSG_Err_PleaseSettlement},
    {ERR_ADMIN_LOGON,            AMSG_Err_AdminNotTrade},
    {ERR_BATCH,                  AMSG_Err_BatchMismatch},
    {ERR_STORE_KEY,              AMSG_Err_WorkKeyErr},
    {ERR_TRANS_FULL,             AMSG_Err_TradeFull},
    {ERR_TRANS_EMPTY,            AMSG_Err_TradeEmpty},
    {ERR_TRANS_NOFIND,           AMSG_Err_OriginalTradeNotExist},
    {ERR_TRANS_NOVOID,           AMSG_Err_OriginalTradeVoid},
    {ERR_NEED_REPRINT,           AMSG_Err_LastTradeNotPrinted},
    {ERR_AMOUNT_OVERFLOW,        AMSG_Err_AmountOverlimit},

    {ERR_VOID_CARD_DIFFER,       AMSG_Err_CardNOInconsistent},
    {ERR_PWD_CASH_PASS,          AMSG_Err_WrongPassword},
    {ERR_PWD_PIN_ERR,            AMSG_Err_WrongPassword},
    {ERR_PWD_PIN_BLOCK,          AMSG_Err_WrongPassword},
    {ERR_PWD_OTHER_ERR,          AMSG_Err_WrongPassword},
    {ERR_FUNC_CLOSE,             AMSG_Err_TradeHasBlocked},
    {ERR_FIELD_CMP,              AMSG_Err_BitCheckErr},
    ///<------------add esign----------->///
    {ERR_INPUT_FORMAT,           AMSG_Err_IllFormattedData},
    ///<-------------------------------->///
    {ERR_MSG_CHECK,              AMSG_Err_MsgTypeNotMatch},
    {ERR_AMT_CHECK,              AMSG_Err_AmountNotMatch},
    {ERR_VHN_CHECK,              AMSG_Err_SerialNoNotMatch},
    {ERR_TID_CHECK,              AMSG_Err_TID_NotMatch},
    {ERR_MID_CHECK,              AMSG_Err_MID_NotMatch},
    ///<------------add esign----------->///
    {ERR_NEED_RESIGN,            AMSG_Err_IllFormattedSignatureData},
    ///<-------------------------------->///
    {ERR_POOR_STORAGE,           AMSG_Err_InsufficientStorageSpace},

    {ERR_NO_SETTLE,              AMSG_Err_NotSettled},
    {MAX_INDEX,                  AMSG_Err_UnknownErr},
};

static const struct _ErrMsg cashierErrMsgTab[] =
{
    {CASHIER_DEL_NOT_ALLOW,                  AMSG_CashierErr_DeleteNotAllow},
    {CASHIER_PWD_DIFFER,                     AMSG_CashierErr_EnterPwdNotSame},
    {CASHIER_PWD_CHANGE_NOT_ALLOW,           AMSG_CashierErr_ChangeNotAllow},
    {CASHIER_PWD_CHANGE_FAIL,                AMSG_CashierErr_ChangeFail},
    {CASHIER_ILLEGAL,                        AMSG_CashierErr_CashierIllegal},
    {CASHIER_FULL,                           AMSG_CashierErr_CashierFull},
    {CASHIER_NO_EXIST,                       AMSG_CashierErr_CashierNotExist},
    {CASHIER_EXIST,                          AMSG_CashierErr_CashierExist},
    {MAX_INDEX,                              AMSG_CashierErr_OtherErr},
};

static const struct _ErrMsg fileErrMsgTab[] =
{
    {UFILE_UPDATE_FAIL,                      AMSG_FileErr_FileUpdateFail},
    {UFILE_NO_EXIST,                         AMSG_FileErr_FileNotExist},
    {UFILE_PARAERROR,                        AMSG_FuncParamErr},
    {UFILE_NO_RECORD,                        AMSG_FileErr_RecordNotFound},
    {UFILE_REMOVE_FAIL,                      AMSG_FileErr_FileMoveFail},
    {UFILE_CLOSE_FAIL,                       AMSG_FileErr_FileCloseFail},
    {UFILE_DELETE_FAIL,                      AMSG_FileErr_DeleteRecordFail},
    {UFILE_READ_FAIL,                        AMSG_FileErr_ReadFileFail},
    {UFILE_WRITE_FAIL,                       AMSG_FileErr_WriteFileFail},
    {UFILE_CREATE_FAIL,                      AMSG_FileErr_CreateFileFail},
    {UFILE_OPEN_FAIL,                        AMSG_FileErr_OpenFileFail},
    {MAX_INDEX,                              AMSG_FileErr_FileReadWriteErr},
};

static const struct _ErrMsg printerErrMsgTab[] =
{
    {PRINTER_ERR_NULL_ARG,                   AMSG_FuncParamErr},
    {PRINTER_ERR_GET_INFO,                   AMSG_PrinterErr_GetParamFail},
    {PRINTER_ERR_SET_DEFAULT_PARA,           AMSG_PrinterErr_InitPrinterFail},
    {PRINTER_ERR_IN_PARA,                    AMSG_FuncParamErr},
    {PRINTER_ERR_SET_PARA,                   AMSG_PrinterErr_SetParamFail},
    {PRINTER_ERR_CLEAR,                      AMSG_PrinterErr_ClearCacheFail},
    {PRINTER_ERR_CLOSE,                      AMSG_PrinterErr_CloseFail},
    {PRINTER_ERR_FEED,                       AMSG_PrinterErr_FeedFail},
    {PRINTER_ERR_GET_PRINT_FONT,             AMSG_PrinterErr_GetFontDataFail},
    {PRINTER_ERR_GET_BITMAP_DATA,            AMSG_PrinterErr_GetBitmapDataFail},
    {PRINTER_ERR_ARG_OVER_RANGE,             AMSG_PrinterErr_PrintTxtOver},
    {PRINTER_ERR_GET_LAYOUT,                 AMSG_PrinterErr_PrintQRFail},

    {PRINTER_ERR_CACHE,                      AMSG_PrinterErr_PrintFail},
    {PRINTER_ERR_NO_PAPER,                   AMSG_PrinterErr_NoPaper},
    {PRINTER_ERR_OVERHEAT,                   AMSG_PrinterErr_Overheat},
    {PRINTER_ERR_BMARK,                      AMSG_PrinterErr_ParamError},
    {PRINTER_ERR_COMM,                       AMSG_PrinterErr_CommunicationError},
    {PRINTER_ERR_NO_PRINTER,                 AMSG_PrinterErr_NoPrinterModule},
    {PRINTER_ERR_LOW_BATTERY,                AMSG_PrinterErr_LowBattery},
    {PRINTER_ERR_NO_FONT,                    AMSG_PrinterErr_NotFontFile},
    {PRINTER_ERR_NO_CACHE_MEMORY,            AMSG_PrinterErr_CacheFull},
    {PRINTER_ERR_CACHING,                    AMSG_PrinterErr_Printing},
    {PRINTER_ERR_PRINTING,                   AMSG_PrinterErr_Printing},
    {PRINTER_ERR_NO_BATTERY,                 AMSG_PrinterErr_PlzInstallBattery},
    {MAX_INDEX,                              AMSG_PrinterErr_PrinterFailure},
};

static const struct _HostErrMsg hostErrMsgTab[] =
{
    {"00",  AMSG_HostErr_Approval},
    {"01",  AMSG_HostErr_ReferToIssuer},
    {"02",  AMSG_HostErr_ReferToIssuer},
    {"03",  AMSG_HostErr_InvalidMerchant},
    {"04",  AMSG_HostErr_InvalidCardNO},
    {"05",  AMSG_HostErr_CardholderAuthenticationFailed},
    {"06",  AMSG_HostErr_ReferToIssuer},
    {"07",  AMSG_HostErr_ConfiscateCardContactAcquirer},
    {"09",  AMSG_HostErr_Retry},
    {"10",  AMSG_HostErr_PartialApprovedAmount},
    {"11",  AMSG_HostErr_Successful},
    {"12",  AMSG_HostErr_InvalidTrade},
    {"13",  AMSG_HostErr_InvalidAmount},
    {"14",  AMSG_HostErr_InvalidCardNO},
    {"15",  AMSG_HostErr_NoCardIssuer},
    {"19",  AMSG_HostErr_ReferToIssuer},
    {"20",  AMSG_HostErr_ReferToIssuer},
    {"21",  AMSG_HostErr_CardNotInitialized},
    {"22",  AMSG_HostErr_IncorrectOperation},
    {"23",  AMSG_HostErr_ReferToIssuer},
    {"25",  AMSG_HostErr_NoOriginalDeal},
    {"30",  AMSG_HostErr_PlzTryAgain},
    {"31",  AMSG_HostErr_CardNotAccepted},
    {"33",  AMSG_HostErr_ExpiredCard},
    {"34",  AMSG_HostErr_CheatCard},
    {"35",  AMSG_HostErr_ConfiscateCardContactAcquirer},
    {"36",  AMSG_HostErr_CardSomethingWrong},
    {"37",  AMSG_HostErr_ConfiscateCardContactAcquirer},
    {"38",  AMSG_HostErr_PinRetryOver},
    {"39",  AMSG_HostErr_ReferToIssuer},
    {"40",  AMSG_HostErr_TradeNotSupported},
    {"41",  AMSG_HostErr_TakeLostCard},
    {"42",  AMSG_HostErr_ReferToIssuer},
    {"43",  AMSG_HostErr_TakeStolenCard},
    {"44",  AMSG_HostErr_ReferToIssuer},
    {"45",  AMSG_HostErr_PlzUseChip},
    {"51",  AMSG_HostErr_InsufficientBalance},
    {"52",  AMSG_HostErr_ReferToIssuer},
    {"53",  AMSG_HostErr_ReferToIssuer},
    {"54",  AMSG_HostErr_ExpiredCard},
    {"55",  AMSG_HostErr_IncorrectPIN},
    {"56",  AMSG_HostErr_ReferToIssuer},
    {"57",  AMSG_HostErr_CardTradeNotAllowed},
    {"58",  AMSG_HostErr_BannedDeals},
    {"59",  AMSG_HostErr_CardCheckError},
    {"60",  AMSG_HostErr_ReferToIssuer},
    {"61",  AMSG_HostErr_AmountExceedsLimit},
    {"62",  AMSG_HostErr_RestrictedCard},
    {"63",  AMSG_HostErr_ReferToIssuer},
    {"64",  AMSG_HostErr_AmountMismatch},
    {"65",  AMSG_HostErr_SaleBeyondLimit},
    {"66",  AMSG_HostErr_ContactAcquirer},
    {"67",  AMSG_HostErr_ConfiscateCard},
    {"68",  AMSG_HostErr_TimeoutRetry},
    {"69",  AMSG_HostErr_ReferToIssuer},
    {"70",  AMSG_HostErr_ReferToIssuer},
    {"71",  AMSG_HostErr_ReferToIssuer},
    {"72",  AMSG_HostErr_ReferToIssuer},
    {"73",  AMSG_HostErr_ReferToIssuer},
    {"74",  AMSG_HostErr_ReferToIssuer},
    {"75",  AMSG_HostErr_PinRetryOver},
    {"76",  AMSG_HostErr_TransFail},
    {"77",  AMSG_HostErr_PlzLogon},
    {"78",  AMSG_HostErr_TransFail},
    {"79",  AMSG_HostErr_DuplicateBatch},
    {"80",  AMSG_HostErr_TryAgainLater},
    {"81",  AMSG_HostErr_TryAgainLater},
    {"82",  AMSG_HostErr_TryAgainLater},
    {"83",  AMSG_HostErr_TryAgainLater},
    {"84",  AMSG_HostErr_TryAgainLater},
    {"85",  AMSG_HostErr_TryAgainLater},
    {"86",  AMSG_HostErr_TryAgainLater},
    {"87",  AMSG_HostErr_TryAgainLater},
    {"88",  AMSG_HostErr_TryAgainLater},
    {"89",  AMSG_HostErr_TryAgainLater},
    {"90",  AMSG_HostErr_SystemBatch},
    {"91",  AMSG_HostErr_CardIssuingStateAnomaly},
    {"92",  AMSG_HostErr_CardIssuingLineAnomaly},
    {"93",  AMSG_HostErr_ReferToIssuer},
    {"94",  AMSG_HostErr_RepeatDeal},
    {"95",  AMSG_HostErr_SystemError},
    {"96",  AMSG_HostErr_CenterAnomaly},
    {"97",  AMSG_HostErr_InvalidTerminal},
    {"98",  AMSG_HostErr_CardIssuerTimeout},
    {"99",  AMSG_HostErr_IllFormattedPin},
    {"A0",  AMSG_HostErr_MacError},
    {"A1",  AMSG_HostErr_TransferCurrencyNotAgree},
    {"A2",  AMSG_HostErr_ConfirmBankReceivedFunds},
    {"A3",  AMSG_HostErr_ToAccountBankIncorrect},
    {"A4",  AMSG_HostErr_ConfirmBankReceivedFunds},
    {"A5",  AMSG_HostErr_ConfirmBankReceivedFunds},
    {"A6",  AMSG_HostErr_ConfirmBankReceivedFunds},
    {"A7",  AMSG_HostErr_SecurityHandlingFailed},
    {"FF",  AMSG_HostErr_TradeError}
};

struct _TradeName
{
    unsigned char TradeId;
    unsigned char *chName;   ///< Chinese trade name
};

struct _TradeName TradeNameTab[] =
{
    {TRANS_SALE,                AMSG_Title_Sale},
    {TRANS_VOID_SALE,           AMSG_Title_SaleVoid},
    {TRANS_REFUND,              AMSG_Title_Refund},
    {TRANS_SETTLEMENT,          AMSG_Title_Settlement}
};

/**
 * @brief get trade Chinese name or English name
 */
int GetTradeName(unsigned char *lpChOut, unsigned char ucTradeId)
{
    unsigned short i = 0;
    unsigned short k = 0;

    k = sizeof(TradeNameTab) / sizeof(struct _TradeName);

    for (i = 0; i < k; i++)
    {
        if (TradeNameTab[i].TradeId == ucTradeId)
        {
            if (NULL != lpChOut)
            {
                strcpy((char *)lpChOut, (char *)TradeNameTab[i].chName);
            }
            return SUCCESS;
        }
    }
    return ERR_END;
}

static char G_TransName[30] = {0};
char *trans_GetTransName(int transType)
{
    memset(G_TransName, 0, sizeof(G_TransName));
    switch(transType)
    {
    case TRANS_LOGON:
        strcpy(G_TransName, AMSG_Title_Logon);
        break;
    case TRANS_LOGOFF:
        strcpy(G_TransName, AMSG_Title_Logoff);
        break;
    case TRANS_SETTLEMENT:
        strcpy(G_TransName, AMSG_Title_Settlement);
        break;
    case TRANS_LOADAID:
        strcpy(G_TransName, AMSG_Title_LoadAID);
        break;
    case TRANS_LOADCAPK:
        strcpy(G_TransName, AMSG_Title_LoadCAPK);
        break;
    case TRANS_LOADRF:
        strcpy(G_TransName, AMSG_Title_LoadRF);
        break;
    case TRANS_QUERY_BAL:
        strcpy(G_TransName, AMSG_Title_QueryBal);
        break;
    case TRANS_SALE:
        strcpy(G_TransName, AMSG_Title_Sale);
        break;
    case TRANS_VOID_SALE:
        strcpy(G_TransName, AMSG_Title_SaleVoid);
        break;
    case TRANS_REFUND:
        strcpy(G_TransName, AMSG_Title_Refund);
        break;
    case TRANS_REVERSAL:
        strcpy(G_TransName, AMSG_Title_Reversal);
        break;
    case TRANS_SCRIPT_SEND:
        strcpy(G_TransName, AMSG_Title_Upload);
        break;
    default:
        strcpy(G_TransName, " ");
        break;
    }
    return G_TransName;
}

static char G_HostErrCode[4] = {0};
static int G_SubErrCode = 0;
void trans_SetErrCode(const char* errCode)
{
    memset(G_HostErrCode, 0, sizeof(G_HostErrCode));
    memcpy(G_HostErrCode, errCode, strlen(errCode));
}

char *trans_GetHostErrMsg(void)
{
    short i;

    for (i = 0; ; i++) {
        if (!memcmp(hostErrMsgTab[i].errCode, "FF", 2)) {
            break;
        }

        if (!memcmp(hostErrMsgTab[i].errCode, G_HostErrCode, 2)) {
            break;
        }
    }
    return hostErrMsgTab[i].errMsg;
}

const char *transErr_GetSubErrMsg(const struct _ErrMsg *pErrMsg, int errCode)
{
    short i;

    for (i = 0; ; i++) {
        if (pErrMsg[i].errIndex == MAX_INDEX) {
            break;
        }

        if (pErrMsg[i].errIndex == errCode) {
            break;
        }
    }
    return pErrMsg[i].errMsg;
}

void trans_GetErrCodeToEmvKernel(int errCode, char *pResCode)
{
    unsigned long ulErrCode;
    unsigned char mBuf[4];

    memset(mBuf, 0, sizeof(mBuf));
    if (errCode == ERR_HOSTCODE) {
        vOneTwo((unsigned char *)G_HostErrCode, 2, (unsigned char*)pResCode);
    }
    else {
        ulErrCode = errCode;
        tools_long_asc(mBuf, 2, &ulErrCode);
        vOneTwo(mBuf, 2, (unsigned char*)pResCode);
    }
}

/*!< ------------------------ 报错函数 ------------------------*/
///< EMV CT报错
extern char *EMVErr_GetCLErrMsg(void);
extern char *EMVErr_GetCTErrMsg(void);

void transErr_ErrBeep(void)
{
    unsigned int uiI;

    for (uiI = 0; uiI < 3; uiI++) {
        SpSysBeepOn(1000, 150);
        Sleep(150);
        SpSysBeepOff();
    }
}

///< 设置子错误码
int transErr_SetSubErrCode(int errCode, int subErrCode)
{
    G_SubErrCode = subErrCode;
    return errCode;
}

const char *transErr_GetErrMsg(int errCode)
{
    switch(errCode)
    {
    case ERR_FILE:
        return transErr_GetSubErrMsg(fileErrMsgTab, UFile_GetErrCode());
    case ERR_CASHIER:
        return transErr_GetSubErrMsg(cashierErrMsgTab, G_SubErrCode);
    case ERR_HOSTCODE:
        return trans_GetHostErrMsg();
    case ERR_EMV_CL:
        return EMVErr_GetCLErrMsg();
    case ERR_EMV_CT:
        return EMVErr_GetCTErrMsg();
    case ERR_PRINTER:
        return transErr_GetSubErrMsg(printerErrMsgTab, G_SubErrCode);
    default:
        return transErr_GetSubErrMsg(errMsgTab, errCode);
    }
}

const char *transErr_GetPrintErrMsg(int errCode)
{
    return transErr_GetSubErrMsg(printerErrMsgTab, errCode);
}

///< 报错
void transErr_DispErrMsg(int transType, int errCode)
{
    transUtil_LED_Error();

    mmi_clearLine(DISP_ClearALL);
    if (transType) {
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(transType));
    }
    mmi_display(DISP_VCenter, DISP_HCenter, transErr_GetErrMsg(errCode));

    transErr_ErrBeep();
    mmi_inputWaitKeypress(5);
    transUtil_LED_Close();
}

