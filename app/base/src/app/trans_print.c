/*****************************************************************************
*  QR and P90 Basic applib configuration definition header                   *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*                                                                            *
*  @file     trans_print                                                     *
*  @brief    print transaction processing                                    *
*  Details.                                                                  *
*  @author   chengyang geng                                                  *
*  @date     2019-01-24                                                      *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "mmi_printer.h"
#include "uFile.h"

#include "trans.h"

#define PRINT_LOG_ENABLE    0
#if PRINT_LOG_ENABLE
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "trans_print.c"
#endif

///< bank name array
struct BankName BankNameTab[] =
{
    {"0100", AMSG_Bank_PSBC},
    {"0102", AMSG_Bank_ICBC},
    {"0103", AMSG_Bank_ABC},
    {"0104", AMSG_Bank_BOC},
    {"0105", AMSG_Bank_CBC},
    {"0301", AMSG_Bank_BCM},
    {"0302", AMSG_Bank_CITIC},
    {"0303", AMSG_Bank_CEB},
    {"0304", AMSG_Bank_HXB},
    {"0305", AMSG_Bank_CMBC},
    {"0306", AMSG_Bank_GDB},
    {"0307", AMSG_Bank_PABC},
    {"0308", AMSG_Bank_CMB},
    {"0309", AMSG_Bank_CIB},
    {"0310", AMSG_Bank_SPDB},
    {"4802", AMSG_Bank_UMS},
    {"0401", AMSG_Bank_BKSH},
    {"1438", AMSG_Bank_HNRC},
    {"0570", AMSG_Bank_HRXJB},
    {"0461", AMSG_Bank_BKCS},
    {"0425", AMSG_Bank_BKDG},
    {"0489", AMSG_Bank_GDNYB},
    {"0403", AMSG_Bank_BOB},
    {"1418", AMSG_Bank_BJRCB},
    {"1401", AMSG_Bank_SHRCB},
    {"6403", AMSG_Bank_BOB},
    {"0410", AMSG_Bank_PABC},
    {"0413", AMSG_Bank_BKGZ},
    {"0437", AMSG_Bank_CRB},
    {"6489", AMSG_Bank_GDNYB},
    {"0495", AMSG_Bank_LZCCB},
    {"0505", AMSG_Bank_BKDG},
    {"1405", AMSG_Bank_GZRCB},
    {"6505", AMSG_Bank_GZRCB},
    {"1407", AMSG_Bank_NHRC},
    {"1408", AMSG_Bank_SDRCB},
    {"6508", AMSG_Bank_SDRCB},
    {"1415", AMSG_Bank_DGRCB},
    {"1421", AMSG_Bank_SSRC},
    {"1425", AMSG_Bank_XHRCB},
    {"1426", AMSG_Bank_ZQRC},
    {"1427", AMSG_Bank_FSRC},
    {"1431", AMSG_Bank_ZHRC},
    {"1432", AMSG_Bank_ZSRC},
    {"1450", AMSG_Bank_GDRC},
    {"6413", AMSG_Bank_BKGZ},
    {"0578", AMSG_Bank_HXB2}
};

int transPrint_Start(void)
{
    int iRet;

    iRet = printer_check();
    if (PRINTER_RET_OK == iRet) {
        iRet = printer_open();
    }

    if (PRINTER_RET_OK != iRet) {
        printer_close();
        return transErr_SetSubErrCode(ERR_PRINTER, iRet);
    }
    return iRet;
}

int transPrint_End(void)
{
    int iRet;

    iRet = printer_close();
#if PRINT_LOG_ENABLE
    LOGD("printer_close = %d\r\n", iRet);
#endif

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Line2, DISP_HCenter, AMSG_PrintEnd);
    mmi_display(DISP_Line3, DISP_HCenter, AMSG_EnterKeyExit);
    mmi_inputWaitKeypress(3);
    return iRet;
}

/**
 * @brief start print sheet
 */
int startPrintData(int errCode)
{
    extern const char *transErr_GetPrintErrMsg(int);
    int iRet = 0;

    if (SUCCESS != errCode) {
        iRet = errCode;
        goto ERR;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Line2, DISP_HCenter, AMSG_Print_Printing);
    mmi_display(DISP_Line3, DISP_HCenter, AMSG_PleaseWait);

    iRet = printer_print();
#if PRINT_LOG_ENABLE
    LOGD("printer_print = %d\r\n", iRet);
#endif
    switch(iRet)
    {
    case PRINTER_RET_OK:
        return SUCCESS;
    case PRINTER_ERR_NO_PRINTER:
    case PRINTER_ERR_NO_FONT:
        printer_close();
        return transErr_SetSubErrCode(ERR_PRINTER, iRet);
    case PRINTER_ERR_PRINTING:
    case PRINTER_ERR_CACHING:
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line2, DISP_HCenter, transErr_GetPrintErrMsg(iRet));
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_EnterKeyContinue);
        break;
    case PRINTER_ERR_NO_PAPER:
    case PRINTER_ERR_OVERHEAT:
    case PRINTER_ERR_LOW_BATTERY:
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line2, DISP_HCenter, transErr_GetPrintErrMsg(iRet));
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_EnterKeyReprint);
        break;
    default:
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line2, DISP_HCenter, transErr_GetPrintErrMsg(PRINTER_ERR_CACHE));
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_EnterKeyReprint);
        break;
    }

    while (1) {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_ENTER:
            return KEY_ENTER;
        case KEY_NONE:
            printer_close();
            return ERR_TIMEOUT;
        case KEY_CANCEL:
            printer_close();
            return ERR_CANCEL;
        default:
            break;
        }
    }

ERR:
    printer_close();
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_PrintFormatErr);
    mmi_inputWaitKeypress(5);
    return transErr_SetSubErrCode(ERR_PRINTER, iRet);;
}

///< get bank name
void getBankName(unsigned char *lpOut, unsigned char *lpBankCode)
{
    unsigned short i = 0;
    unsigned short k = 0;

    if ((NULL == lpOut) || (NULL == lpBankCode))
    {
        return;
    }
    
    k = sizeof(BankNameTab) / sizeof(BankNameTab[0]);
    for (i = 0; i < k; i++)
    {
        if (!memcmp(BankNameTab[i].BankCode, lpBankCode, 4))
        {
            strcpy((char *)lpOut, (char *)BankNameTab[i].BankName);
            
            return;
        }
    }

    strcpy((char *)lpOut, (char *)lpBankCode);
    return;
}

/**
 * @brief 对于刷卡的交易，应在交易类型之后打印"（S）"       \n
    对于芯片卡接触式插入交易，应在交易类型之后打印"（I）"   \n
    对于芯片卡非接触式挥卡交易，应在交易类型之后打印"（C）" \n
    对于手输卡号交易，应在交易类型之后打印"（M）"           \n
    对于无卡交易，应在交易类型之后打印"（N）"
*/
void GetTradeUseCardType(unsigned char ucCardInputType, unsigned char *ucUseCardType)
{    
    if (NULL == ucUseCardType) {
        return;
    }
    
    if (InputMode_Manual == ucCardInputType)
    {
        memcpy(&ucUseCardType[0], "  M", 3);
    }
    else if (InputMode_Mag == ucCardInputType)
    {
        memcpy(&ucUseCardType[0], "  S", 3);
    }
    else if (InputMode_ICC == ucCardInputType)
    {
        memcpy(&ucUseCardType[0], "  I", 3);
    }
    else if (InputMode_QICC == ucCardInputType)
    {
        memcpy(&ucUseCardType[0], "  C", 3);
    }
    else
    {
        memcpy(&ucUseCardType[0], "  N", 3);
    }
}

/**
 * @brief form merchant information
 */
int formMerchantInfo(void)
{
    char temp[128] = {0}, buf[128] = {0};
    ts_printer_para stPrinterPara;
    int iRet = 0;

    ///< get & set printer parameter
    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_get_para(&stPrinterPara);

    ///< merchant name
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_MerchantName);
    }

    ///< merchant name value
    if (PRINTER_RET_OK == iRet && strlen((const char *)DataConstant.merchantName) > 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, (const char *)DataConstant.merchantName);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }
    
    ///< merchant no.
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memcpy(temp, DataConstant.MID, sizeof(DataConstant.MID));
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s%s", AMSG_Print_MerchantNO, temp);
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }
    
    ///< terminal no.
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memcpy(temp, DataConstant.TID, sizeof(DataConstant.TID));
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s%s", AMSG_Print_TerminalNo, temp);
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%s%s", AMSG_Print_Operator, DataChange.cashierNo);
        iRet = printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }
    return iRet;
}

/**
 * @brief form emv param sheet data
 */
static int formEmvParam(tsTransData *pstTransData)
{
    int iRet = SUCCESS;
    char buf[128] = {0}, temp[128] = {0};
    ts_printer_para stPrinterPara;

    if (NULL == pstTransData) {
        return ERR_PARAM;
    }

    if ((InputMode_ICC != pstTransData->cardInputType)
     && (InputMode_QICC != pstTransData->cardInputType))
    {
        return iRet;
    }

    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_get_para(&stPrinterPara);
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_SMALL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 4;

        ///< ARQC
        memset(buf, 0, sizeof(buf));
        if (strlen((char *)pstTransData->aucARQC) > 0) {
            snprintf(buf, sizeof(buf), "ARQC:%s", pstTransData->aucARQC);
        }
        else {
            strcpy(buf, "ARQC:");
        }
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< AID
    if (PRINTER_RET_OK == iRet) {
        memset(buf, 0, sizeof(buf));
        if (strlen((char *)pstTransData->aucAID) > 0) {
            snprintf(buf, sizeof(buf), "AID:%s", pstTransData->aucAID);
        }
        else {
            strcpy(buf, "AID:");
        }
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< TVR & TSI & ATC
    ///< TVR
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        if (memcmp(pstTransData->bcdTVR, "\x00\x00\x00\x00\x00", 5)) {
            vOneTwo(pstTransData->bcdTVR, 5, (unsigned char *)temp);
        }
        else {
            memset(temp, '0', 10);
        }
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "TVR:%s", temp);
        ///< TSI
        memset(temp, 0, sizeof(temp));
        if (memcmp(pstTransData->bcdTSI, "\x00\x00", 2)) {
            vOneTwo(pstTransData->bcdTSI, 2, (unsigned char *)temp);
        }
        else {
            memset(temp, '0', 4);
        }
        strcat(buf, "  ");
        strcat(buf, "TSI:");
        strcat(buf, temp);
        ///< ATC
        memset(temp, 0, sizeof(temp));
        if (memcmp(pstTransData->bcdATC, "\x00\x00", 2)) {
            vOneTwo(pstTransData->bcdATC, 2, (unsigned char *)temp);
        }
        else {
            memset(temp, '0', 4);
        }
        strcat(buf, "   ");
        strcat(buf, "ATC:");
        strcat(buf, temp);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< APPLAB & APPNAME
    ///< APPLAB
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        if (strlen((const char *)pstTransData->aucAPPLAB) > 0) {
            strcpy(temp, (const char *)pstTransData->aucAPPLAB);
        }
        else {
            strcpy(temp, "            ");
        }
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "APPLAB:%s", temp);

        ///< APPNAME
        strcat(buf, "    ");
        strcat(buf, "APPNAME:");
        strcat(buf, (const char *)pstTransData->aucAPPNAME);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }
    return iRet;
}

/*============================================
 * 返回值: 持卡人签名(0-不打印, 1-打印)
 * ucSignature : 0-非免签交易,   1-免签交易
 * ucPin:        0-非免密交易,   1-免密交易
 * ucCDCVM:      0-非CDCVM交易, 1-CDCVM交易
 *
 *=========================================== */
static unsigned char getVoucherPrintStr(char *aucPrintBuf, unsigned char ucSignature, unsigned char ucPin, unsigned long ulAmount, unsigned char ucCDCVM)
{
    unsigned char ucPrintSignature = 0; //默认不打印

    /*==========================================
     * 免签 /免密/CDCVM
     * 0,0,0    无打印提示
     * 0,0,1    移动设备已验证用户，免密免签
     * 0,1,0    交易金额未超B元，无需输密
     * 0,1,1    移动设备已验证用户，免密免签
     * 1,0,0    交易金额未超A元，免签名
     * 1,0,1    移动设备已验证用户，免密免签
     * 1,1,0    交易金额未超XX元，免密免签
     * 1,1,1    移动设备已验证用户，免密免签
     * 2,0,?    电子现金交易,无需签名
     * 3,0,0    扫码交易,免签名
     *========================================*/
    if (ucSignature == 0 && ucPin == 0 && ucCDCVM == 1)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_MobileDeviceVerified);
    }
    else if (ucSignature == 0 && ucPin == 1 && ucCDCVM == 0)
    {
        sprintf((char*)aucPrintBuf, (char*)AMSG_Print_NoPin, ulAmount/100, ulAmount%100);
        ucPrintSignature = 1;
    }
    else if (ucSignature == 0 && ucPin == 1 && ucCDCVM == 1)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_MobileDeviceVerified);
    }
    else if (ucSignature == 1 && ucPin == 0 && ucCDCVM == 0)
    {
        sprintf((char*)aucPrintBuf,(char*)AMSG_Print_NoSignature, ulAmount/100, ulAmount%100);
    }
    else if (ucSignature == 1 && ucPin == 0 && ucCDCVM == 1)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_MobileDeviceVerified);
    }
    else if (ucSignature == 1 && ucPin == 1 && ucCDCVM == 0)
    {
        sprintf((char*)aucPrintBuf,(char*)AMSG_Print_NoPinAndNoSignature, ulAmount/100, ulAmount%100);
    }
    else if (ucSignature == 1 && ucPin == 1 && ucCDCVM == 1)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_MobileDeviceVerified);
    }
    else if (ucSignature == 2 && ucPin == 0)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_IsEcTrade);
    }
    else if (ucSignature == 3 && ucPin == 0 && ucCDCVM == 0)
    {
        sprintf((char*)aucPrintBuf, AMSG_Print_IsScanSale);
    }
    else
    {
        ucPrintSignature = 1;
    }
    return ucPrintSignature;
}

/**
 * @brief get sign data
 * @note 1-need sign, 0-no sign
 */
unsigned char GetNoPinNoSignData(char *plSignData, tsTransData *pTransData)
{
    unsigned char bPrintSign = 1;
    unsigned char bSignatureFlag = 0, bPINFlag = 0, bCDCVMFlag = 0;
    unsigned long ulPinAmount = 0, ulSignAmount = 0;
    
    if (!pTransData) {
        return bPrintSign;
    }

    if (InputMode_Scan == pTransData->cardInputType)
    {
        bSignatureFlag  = 3;
        bPINFlag        = 0;
        bCDCVMFlag      = 0;
    }
    else if ((InputMode_QICC == pTransData->cardInputType)
          && (TRANS_SALE == pTransData->transType))
    {
        bCDCVMFlag = pTransData->ucCDCVM;
        if (DataChange.QPS_Signature_Flag && DataChange.QPS_SignatureAmtLimit >= pTransData->ulAmount) {
            bSignatureFlag = 1;
            ulSignAmount = DataChange.QPS_SignatureAmtLimit;
        }

        if (DataChange.QPS_NoPIN_Flag && !pTransData->isInputPIN && DataChange.QPS_PINAmtLimit >= pTransData->ulAmount) {
            bPINFlag = 1;
            ulPinAmount = DataChange.QPS_PINAmtLimit;
        }
    }
    return getVoucherPrintStr(plSignData, bSignatureFlag, bPINFlag, ulPinAmount < ulSignAmount ? ulPinAmount : ulSignAmount, bCDCVMFlag);
}

/**
 * @brief form the trans print sheet data
 */
static int formVoucherSheet(tsTransData *pstTransData, int isErrPrint, int isRePrint, unsigned char ucPrintTimes, unsigned char ucTotalTimes)
{
    char temp[128] = {0}, buf[256] = {0}, printtemp[128] = {0};
    ts_printer_para stPrinterPara;
    int iRet = 0;
    unsigned char printsignflag = 1;

    if (NULL == pstTransData) {
        return ERR_PARAM;
    }

    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_clear();

    ///< get & set printer parameter
    if (PRINTER_RET_OK == iRet) {
        iRet = printer_get_para(&stPrinterPara);
    }

    ///< print title
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_LARGE;
        stPrinterPara.printAlign = ALIGN_CENTER;
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Title);
    }

    ///< divider
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '-', 32);
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.lineSpace = 0;
        stPrinterPara.printAlign = ALIGN_LEFT;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    ///< merchant stub
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        switch (ucPrintTimes)
        {
        case 0:
            strcpy(temp, AMSG_Print_MerchantCopy);
            break;
        case 1:
            if (2 == ucTotalTimes) {
                strcpy(temp, AMSG_Print_CarcHolderCopy);
            }
            else {
                strcpy(temp, AMSG_Print_BankCopy);
            }
            break;
        default:
            if (3 == ucTotalTimes) {
                strcpy(temp, AMSG_Print_CarcHolderCopy);
            }
            else {
                strcpy(temp, AMSG_Print_BankCopy);
            }
            break;
        }
        stPrinterPara.fontSize = PRINT_FONT_SMALL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    ///< divider
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '-', 32);
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    ///< merchant info
    if (PRINTER_RET_OK == iRet) {
        iRet = formMerchantInfo();
    }

    ///< card issuer
    if (PRINTER_RET_OK == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_ISS);
        if (0 != memcmp(pstTransData->issuerID, "\x00\x00\x00\x00", 4))
        {
            memset(printtemp, 0, sizeof(printtemp));
            getBankName((unsigned char *)printtemp, pstTransData->issuerID);
            strncat(buf, printtemp, 8);
        }
        else
        {
            strcat(buf, "        ");
        }

        ///< acquiring bank
        memset(temp, 0, sizeof(temp));
        strcpy(temp, AMSG_Print_ACQ_Institute);
        if (0 != memcmp(pstTransData->acquereID, "\x00\x00\x00\x00", 4))
        {
            memset(printtemp, 0, sizeof(printtemp));
            getBankName((unsigned char *)printtemp, pstTransData->acquereID);
            strncat(temp, printtemp, 8);
        }
        else
        {
            strcat(temp, "        ");
        }
        iRet = printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 384);

        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< add scan
    if (InputMode_Scan == pstTransData->cardInputType && strlen((const char *)pstTransData->ScanCodeC2B)
    )
    {
        ///< scan voucher no.
        if (PRINTER_RET_OK == iRet) {
            iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_PaymentCode);
        }

        if (PRINTER_RET_OK == iRet) {

            memset(buf, 0, sizeof(buf));
            memcpy(buf, pstTransData->ScanCodeC2B, sizeof(buf)-1);
            transUtil_JudgeMaskCardNo(pstTransData->transType, (unsigned char *)buf);
            stPrinterPara.fontSize = PRINT_FONT_NORMAL;
            stPrinterPara.fontEffect = EFFECT_BOLD;
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }
    else if (pstTransData->sourceAccLen > 0 && memcmp(pstTransData->sourceAcc, "\x00\x00\x00", 3))
    {
        ///< card no.
        if (PRINTER_RET_OK == iRet) {
            iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_CardNo);
        }

        if (PRINTER_RET_OK == iRet) {
            memset(buf, 0, sizeof(buf));
            tools_bcd_asc((unsigned char *)buf, pstTransData->sourceAcc,
                          pstTransData->sourceAccLen + (pstTransData->sourceAccLen%2 ? 1 : 0));
            buf[pstTransData->sourceAccLen] = 0x00;
            transUtil_JudgeMaskCardNo(pstTransData->transType, (unsigned char *)buf);
            ///< get trans card type
            memset(temp, 0, sizeof(temp));
            GetTradeUseCardType(pstTransData->cardInputType, (unsigned char *)temp);
            strcat(buf, temp);
            stPrinterPara.fontSize = PRINT_FONT_NORMAL;
            stPrinterPara.fontEffect = EFFECT_BOLD;
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }

    ///< trans type
    ///< get trans type name
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.fontEffect = EFFECT_NONE;

        memset(temp, 0, sizeof(temp));
        ///< add scan
        if (InputMode_Scan == pstTransData->cardInputType && TRANS_SALE == pstTransData->transType) {
            strcpy(temp, AMSG_ScanSale);
        }
        else if (InputMode_Scan == pstTransData->cardInputType && TRANS_VOID_SALE == pstTransData->transType) {
            strcpy(temp, AMSG_ScanSaleVoid);
        }
        else if (InputMode_Scan == pstTransData->cardInputType && TRANS_REFUND == pstTransData->transType) {
            strcpy(temp, AMSG_ScanRefund);
        }
        else {
            GetTradeName((unsigned char *)temp, pstTransData->transType);
        }
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s%s", AMSG_Print_TransType, temp);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< add scan
    if (InputMode_Scan == pstTransData->cardInputType)
    {
        ///< scan voucher no.
        if (PRINTER_RET_OK == iRet) {
            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%s %20.20s", AMSG_Print_ScanVoucherNo, pstTransData->ascScanVoucherNo);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }

        ///< voucher no.
        if (PRINTER_RET_OK == iRet) {
            stPrinterPara.printAlign = ALIGN_LEFT;
            stPrinterPara.lineSpace = 8;

            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%s%6.6s", AMSG_Print_VoucherNo, pstTransData->traceNumber);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }
    else
    {
        ///< exp date
        if (PRINTER_RET_OK == iRet) {
            memset(temp, 0, sizeof(temp));
            if ((strlen((const char *)pstTransData->expiredDate) > 0)
                && (memcmp(pstTransData->expiredDate, "0000", 4)))
            {
                strcat(temp, "20");
                strncat(temp, (char *)pstTransData->expiredDate, 2);        ///< year
                strcat(temp, "/");
                strncat(temp, (char *)(pstTransData->expiredDate + 2), 2);  ///< month
            }
            else
            {
                strcpy(temp, "    ");
            }
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s:%s", AMSG_Print_ExpDate, temp);

            ///< foreign card
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "%s%s", AMSG_Print_CardAssociation, pstTransData->cardType ? "" : "CUP");
            iRet = printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 384);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }

        ///< Batch no. & trace no.
        if (PRINTER_RET_OK == iRet) {
            memset(buf, 0, sizeof(buf));
            memset(temp, 0, sizeof(temp));
            sprintf(buf, "%s%6.6s", AMSG_Print_BatchNo, pstTransData->batchNumber);
            sprintf(temp, "%s%6.6s", AMSG_Print_VoucherNo, pstTransData->traceNumber);
            iRet = printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 384);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }

        ///< auth code
        if (PRINTER_RET_OK == iRet) {
            memset(buf, 0, sizeof(buf));
            sprintf(buf, "%s%6.6s", AMSG_Print_AuthNo, pstTransData->authCode);

            ///< transaction reference no.
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "%s%12.12s", AMSG_Print_ReferNo, pstTransData->refNumber);
            iRet = printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 384);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }

    ///< date & time
    if (PRINTER_RET_OK == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_TransDateTime);
        memset(temp, 0, sizeof(temp));
        ///< year
        strncat(&temp[0], (char *)&pstTransData->date[0], 4);
        ///< date separator
        strncat(&temp[4], "-", 1);
        ///< month
        strncat(&temp[5], (char *)&pstTransData->date[4], 2);
        ///< date separator
        strncat(&temp[7], "-", 1);
        ///< day
        strncat(&temp[8], (char *)&pstTransData->date[6], 2);
        ///< separator
        strncat(&temp[10], " ", 1);
        ///< hour
        strncat(&temp[11], (char *)&pstTransData->time[0], 2);
        ///< time separator
        strncat(&temp[13], ":", 1);
        ///< min
        strncat(&temp[14], (char *)&pstTransData->time[2], 2);
        ///< time separator
        strncat(&temp[16], ":", 1);
        ///< sec
        strncat(&temp[17], (char *)&pstTransData->time[4], 2);
        strcat(buf, temp);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< trans amount
    if (PRINTER_RET_OK == iRet) {
        memset(buf, 0, sizeof(buf));
        if ((TRANS_VOID_SALE == pstTransData->transType)
            || (TRANS_REFUND == pstTransData->transType))
        {
            snprintf(buf, sizeof(buf), "%s -%ld.%02ld", AMSG_Print_TransAmount, pstTransData->ulAmount/100, pstTransData->ulAmount%100);
        }
        else
        {
            snprintf(buf, sizeof(buf), "%s %ld.%02ld", AMSG_Print_TransAmount, pstTransData->ulAmount/100, pstTransData->ulAmount%100);
        }
        ///< large & bold
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.fontEffect = EFFECT_BOLD;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    stPrinterPara.fontSize = PRINT_FONT_NORMAL;
    stPrinterPara.fontEffect = EFFECT_NONE;

    ///< divider
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '-', 32);
        stPrinterPara.lineSpace = 0;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    ///< remark
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Reference);
    }

    stPrinterPara.fontSize = PRINT_FONT_SMALL;
    if (PRINTER_RET_OK == iRet && InputMode_Scan == pstTransData->cardInputType)
    {
        memset(buf, 0, sizeof(buf));
        memcpy(buf, pstTransData->ascScanVoucherNo, 20);
        stPrinterPara.printAlign = ALIGN_CENTER;
        iRet = printer_add_barcode_with_param(&stPrinterPara, BARCODE_TYPE_ANY, 384, 80, buf);

        ///< space
        if (PRINTER_RET_OK == iRet) {
            stPrinterPara.lineSpace = 0;
            stPrinterPara.printAlign = ALIGN_LEFT;
            iRet = printer_add_text_with_param(&stPrinterPara, " ");
        }
        stPrinterPara.lineSpace = 8;
    }

    if (SUCCESS == iRet && DataConstant.posState) {
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg17);
    }

    ///< reprint flag
    if (PRINTER_RET_OK == iRet && isRePrint) {
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg18);
    }

    ///< void trade,print old tracde no.
    if ((TRANS_VOID_SALE == pstTransData->transType))
    {
        if (PRINTER_RET_OK == iRet && strlen((const char *)pstTransData->oldtraceNumber))
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s%6.6s", AMSG_Print_OldVoucher, pstTransData->oldtraceNumber);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }

    if (TRANS_REFUND == pstTransData->transType)
    {
        if (InputMode_Scan != pstTransData->cardInputType)
        {
            if (PRINTER_RET_OK == iRet && strlen((const char *)pstTransData->oldRefNumber))
            {
                memset(buf, 0, sizeof(buf));
                snprintf(buf, sizeof(buf), "%s%12.12s", AMSG_Print_OldRefNo, pstTransData->oldRefNumber);
                iRet = printer_add_text_with_param(&stPrinterPara, buf);
            }
        }

        if (PRINTER_RET_OK == iRet && strlen((const char *)pstTransData->oldDate))
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s%4.4s", AMSG_Print_OldTransDateTime, pstTransData->oldDate);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }

    ///< sale & auth picc
    if (PRINTER_RET_OK == iRet
     && (TRANS_SALE == pstTransData->transType)) {
        iRet = formEmvParam(pstTransData);
    }

    ///< signature
    if (PRINTER_RET_OK == iRet && !isErrPrint && ucPrintTimes == 0)
    {
        ///< print sign flag
        memset(buf, 0, sizeof(buf));
        printsignflag = GetNoPinNoSignData(buf, pstTransData);

        ///<-------------add esign-------------->///
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 8;
        if (PRINTER_RET_OK == iRet && !printsignflag) {
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }

        if (1 == printsignflag)
        {
            if (PRINTER_RET_OK == iRet) {
                iRet = printer_add_text_with_param(&stPrinterPara, AMAG_Print_CardHolderSignature);
            }

#ifdef ENABLE_ESIGN
            ///< add elecsign print bmp data
            if (PRINTER_RET_OK == iRet && DataEsign.bisSupportEs) {
                if (esign_AddPrintBmp() == SUCCESS) {
                    printsignflag = 0;
                }
            }
#endif
            if (PRINTER_RET_OK == iRet && 1 == printsignflag) {
                ///< signature space
                memset(temp, 0, sizeof(temp));
                memset(temp, ' ', 32);
                iRet = printer_add_text_with_param(&stPrinterPara, temp);
            }

            ///< divider
            if (PRINTER_RET_OK == iRet) {
                memset(temp, 0, sizeof(temp));
                memset(temp, '-', 32);
                stPrinterPara.printAlign = ALIGN_CENTER;
                stPrinterPara.lineSpace = 0;
                iRet = printer_add_text_with_param(&stPrinterPara, temp);
            }

            if (PRINTER_RET_OK == iRet) {
                stPrinterPara.fontSize = PRINT_FONT_SMALL;
                iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_I_Acknowledge);
            }
        }
    }

    ///< divider
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '-', 32);
        stPrinterPara.lineSpace = 0;
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    ///< app info
    if (PRINTER_RET_OK == iRet) {
        if (memcmp(_APP_VERSION, "\x00\x00\x00", 3)) {
            memset(temp, 0, sizeof(temp));
            if (memcmp(_APP_BUILD_DATE, "\x00\x00\x00", 3)) {
                snprintf(temp, sizeof(temp), "%s_%s", _APP_VERSION, _APP_BUILD_DATE);
            }
            else {
                strcpy(temp, _APP_VERSION);
            }

            memset(buf, 0, sizeof(buf));
            if ('V' != temp[0] && 'v' != temp[0]) {
                snprintf(buf, sizeof(buf), "V%s", temp);
            }
            else {
                strcpy(buf, temp);
            }
            stPrinterPara.printAlign = ALIGN_LEFT;
            stPrinterPara.fontSize = PRINT_FONT_SMALL;
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }

    ///< feed paper
    if (PRINTER_RET_OK == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '\n', 3);
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }
    return iRet;
}

/**
 * @brief print voucher sheets
 */
int PrintVoucherSheet(tsTransData *pstTransData, int isErrPrint, int isRePrint)
{
    int iRet = 0;
    unsigned int times = 0, totaltimes = 0;
    
    ///< reprint show
    if (isRePrint) {
        if (SUCCESS != (iRet = transUI_DisplayTradeInfo(1, pstTransData))) {
            return iRet;
        }
    }

    ///< print times
    totaltimes = DataConstant.ucPrintTimes;
    if (SUCCESS != (iRet = transPrint_Start())) {
        return iRet;
    }

    for (times = 0; times < totaltimes;)
    {
        while (1)
        {
            ///< form print info
            iRet = formVoucherSheet(pstTransData, isErrPrint, isRePrint, times, totaltimes);
            iRet = startPrintData(iRet);
            if (KEY_ENTER == iRet) {
                continue;
            }
            else if (SUCCESS == iRet)
            {
                break;
            }
            else
            {
                return iRet;
            }
        }

        times++;
        
    #if PRINT_LOG_ENABLE
        LOGD("[%s,%d]print times = %d\r\n", __FUNCTION__, __LINE__, times);
    #endif
        if (times >= totaltimes)
        {
            break;
        }
        else
        {
            if (KEY_NONE != mmi_inputWaitKeypress(2))
            {
                ///< wait keytone finish while kbtone enable
                if (IsKbToneEnable())
                {
                    Sleep(150);
                }
            }
        }
    }

    transPrint_End();
    return SUCCESS;
}

/**
 * @brief reprint the last trade sheet
 */
int transPrint_LastTrade(void)
{
    int iRet = 0;

#if PRINT_LOG_ENABLE
    LOGD("transCount = %d, lastTransIndex = %d\r\n",
        DataTransDetail.transCount, DataTransDetail.lastTransIndex);
#endif

    if (DataTransDetail.transCount <= 0) {
        return ERR_TRANS_EMPTY;
    }

    ///< get last trade record
    memset(&DataTrans, 0, sizeof(tsTransData));
    iRet = UFile_ReadRecordIndexOf(DB_TransTable, DataTransDetail.lastTransIndex);

#ifdef ENABLE_ESIGN
    ///<-----------add esign----------->///
    ///< get elecsign data with index, ignore the retval
    if (SUCCESS == iRet && DataEsign.bisSupportEs) {
        esign_GetCompressedFile(DataTransDetail.lastTransIndex);
    }
    ///<------------------------------->///
#endif

    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Title_ReprintLastTrade);
        iRet = PrintVoucherSheet(&DataTrans, 0, 1);
    }

    ///< save print state flag
    if (SUCCESS == iRet) {
        transUtil_UpdatePrintState(1, DataTransDetail.lastTransIndex);
    }
    return iRet;
}

/**
 * @brief reprint any trade sheet
 */
int transPrint_AnyTrade(void)
{
    int iRet = SUCCESS;
    unsigned int index = 0;

    iRet = transUI_SearchTransEx(AMSG_Title_ReprintAnyTrade, "\x01\00", &index, &DataTrans);

#ifdef ENABLE_ESIGN
    ///<-----------add esign-------------->///
    ///< get elecsign data with index, ignore the retval
    if (SUCCESS == iRet && DataEsign.bisSupportEs) {
        esign_GetCompressedFile(index);
    }
#endif

    if (SUCCESS == iRet) {
        iRet = PrintVoucherSheet(&DataTrans, 0, 1);
    }

    ///< save print state flag
    if (SUCCESS == iRet) {
        transUtil_UpdatePrintState(1, index);
    }
    return iRet;
}

/**
 * @brief detail sheet header
 */
int formTradeDetailHeader(char const *lpTitle)
{
    char temp[128] = {0};
    ts_printer_para stPrinterPara;
    int iRet = 0;

    iRet = printer_clear();
    if (SUCCESS == iRet) {
        memset(&stPrinterPara, 0, sizeof(ts_printer_para));
        iRet = printer_get_para(&stPrinterPara);
        stPrinterPara.fontSize = PRINT_FONT_LARGE;
        stPrinterPara.printAlign = ALIGN_CENTER;
        stPrinterPara.lineSpace = 8;
    }

    if (NULL != lpTitle)
    {
        if (SUCCESS == iRet) {
            iRet = printer_add_text_with_param(&stPrinterPara, lpTitle);
        }

        if (SUCCESS == iRet) {
            memset(temp, 0, sizeof(temp));
            memset(temp, '-', 32);
            stPrinterPara.fontSize = PRINT_FONT_NORMAL;
            stPrinterPara.lineSpace = 0;
            iRet = printer_add_text_with_param(&stPrinterPara, temp);
            stPrinterPara.lineSpace = 8;
        }
    }

    ///< Chinese
    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_SMALL;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg19);
    }
    return iRet;
}

/**
 * @brief ptint detail sheet footer
 */
int formTradeDetailFooter(void)
{
    char buf[64] = {0};
    ts_printer_para stPrinterPara;
    int iRet = 0;

    iRet = printer_clear();
    if (SUCCESS == iRet) {
        memset(&stPrinterPara, 0, sizeof(ts_printer_para));
        iRet = printer_get_para(&stPrinterPara);
    }

    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 0;
        memset(buf, '-', 32);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< notice
    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_SMALL;
        stPrinterPara.printAlign = ALIGN_CENTER;
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg20);
    }

    ///< feed paper
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        memset(buf, '\n', 2);
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }
    return iRet;
}

/**
 * @brief print trade detail sheet
 */
int printTradeDetail(tsTransData *pstTransData)
{
    char buf[128] = {0}, temp[128] = {0};
    int iRet = 0;
    int iCurLen = 0, iLen = 0;
    ts_printer_para stPrinterPara;

    if (NULL == pstTransData) {
        return ERR_PARAM;
    }

    ///< 只打印有效正交易
    if (pstTransData->isVoid
        || ((TRANS_SALE != pstTransData->transType)
            && (TRANS_REFUND != pstTransData->transType)))
    {
        return SUCCESS;
    }

PRINT_BEGIN:
    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_get_para(&stPrinterPara);
    if (PRINTER_RET_OK == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_SMALL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 8;
        iRet = printer_clear();
    }

    if (PRINTER_RET_OK == iRet) {
        ///< trace no.
        memset(buf, 0, sizeof(buf));
        memcpy(buf, pstTransData->traceNumber, 6);

        ///< trade type
        memset(temp, 0, sizeof(temp));
        switch (pstTransData->transType)
        {
        case TRANS_SALE:
            memcpy(temp, "S", 1);
            break;
        case TRANS_REFUND:
            memcpy(temp, "R", 1);
            break;
        default:
            memcpy(temp, " ", 1);
            break;
        }
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 8*12);


        strcat(buf, "    ");
        ///< card no.
        memset(temp, 0, sizeof(temp));
        if (InputMode_Scan == pstTransData->cardInputType)
        {
            strcpy(temp, (const char *)pstTransData->ScanCodeC2B);
        }
        else
        {
            tools_bcd_asc((unsigned char *)temp, pstTransData->sourceAcc,
                          pstTransData->sourceAccLen + (pstTransData->sourceAccLen%2 ? 1 : 0));
            temp[pstTransData->sourceAccLen] = 0x00;
        }
        transUtil_JudgeMaskCardNo(pstTransData->transType, (unsigned char *)temp);
        if (strlen(temp) <= 19) ///< fill in blank
        {
            memset(&temp[strlen(temp)], 0x20, 19-strlen(temp));
        }

        strcat(buf, temp);
        strcat(buf, " ");

        ///< amount
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld", pstTransData->ulAmount / 100, pstTransData->ulAmount % 100);

        iCurLen = strlen(buf);
        iLen = strlen(temp);

        /*大部分情况下，金额达到13位的可能性几乎为0，这里以12为作为金额占用区，
          刚好打印一行
        */
        if (iLen <= 9)
        {
            memset(&buf[iCurLen], 0x20, 9);
            memcpy(&buf[iCurLen+9-iLen], temp, iLen);
        }
        else    // 超过只能换行
        {
            memset(&buf[iCurLen], 0x20, 15);
            memcpy(&buf[iCurLen], temp, 15);
        }

        strcat(buf, " ");

        ///< Auth code
        memset(temp, 0, sizeof(temp));
        memcpy(temp, pstTransData->authCode, 6);
        strcat(buf, temp);

        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    iRet = startPrintData(iRet);
    if (KEY_ENTER == iRet) {
        goto PRINT_BEGIN;
    }
    return iRet;
}

/**
 * @brief print trade detail
 */
int transPrint_DetailTrade(void)
{
    int index = 0;
    int iRet = 0;
    int iKey = KEY_NONE;

    ///< wait keytone finish while kbtone enable
    if (IsKbToneEnable()) {
        Sleep(150);
    }

    if (DataTransDetail.transCount <= 0) {
        return ERR_TRANS_EMPTY;
    }

    iRet = transPrint_Start();
    if (SUCCESS == iRet) {
        while (1)
        {
            iRet = formTradeDetailHeader(AMSG_Print_TXN_LIST);
            iRet = startPrintData(iRet);
            if (KEY_ENTER == iRet) {
                continue;
            }
            break;
        }
    }

    if (SUCCESS == iRet) {
        for (index = 0; index < DataTransDetail.transCount && SUCCESS == iRet; index++)
        {
            if (!KbHit()) {
                if (KEY_CANCEL == mmi_inputGetKeypress())
                {
                    mmi_clearLine(DISP_ClearALL);
                    mmi_display(DISP_Line2, DISP_HCenter, AMSG_Print_NeedAbortPrinting);
                    mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_CancelPrint);
                    mmi_display(DISP_Line4, DISP_HCenter, AMSG_Print_EnterPrint);
                    while(1) {
                        iKey = mmi_inputWaitKeypress(60);
                        if (KEY_ENTER == iKey) {
                            if (IsKbToneEnable()) { ///< wait keytone finish while kbtone enable
                                Sleep(150);
                            }
                            break;
                        }
                        else if (KEY_CANCEL == iKey){
                            printer_close();
                            return ERR_CANCEL;
                        }
                    }
                }
            }

            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_Line2, DISP_HCenter, AMSG_Print_Printing);
            mmi_display(DISP_Line3, DISP_HCenter, AMSG_Print_CancelAbortPrinting);

            ///< get record data
            memset(&DataTrans, 0, sizeof(tsTransData));
            iRet = UFile_ReadRecordIndexOf(DB_TransTable, index);
            if (SUCCESS == iRet) {
                ///< get void state
                DataTrans.isVoid = DataTransDetail.transIndex[index] & TRANS_VOIDSTATE;
                ///< print trade detail
                iRet = printTradeDetail(&DataTrans);
            }
        }
    }

    ///< print trade detail sheet footer
    if (SUCCESS == iRet) {
        while (1)
        {
            iRet = formTradeDetailFooter();
            iRet = startPrintData(iRet);
            if (KEY_ENTER == iRet) {
                continue;
            }
            break;
        }
    }

    if (SUCCESS == iRet) {
        transPrint_End();
    }
    return iRet;
}

/**
 * @brief print total sheet
 */
static int __transPrint_TotalSheet(tsTradeTotalAll *pstAll)
{
    char temp[128] = {0}, buf[128] = {0};
    ts_printer_para stPrinterPara;
    int iRet = 0;

    if (NULL == pstAll) {
        return ERR_PARAM;
    }

    if (SUCCESS != (iRet = transPrint_Start())) {
        return iRet;
    }

PRINT_BEGIN:
    iRet = printer_clear();
    if (SUCCESS == iRet) {
        memset(&stPrinterPara, 0, sizeof(ts_printer_para));
        iRet = printer_get_para(&stPrinterPara);
        stPrinterPara.fontSize = PRINT_FONT_LARGE;
        stPrinterPara.printAlign = ALIGN_CENTER;
        stPrinterPara.lineSpace = 8;
    }

    ///< title
    if (SUCCESS == iRet) {
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_TotalExchange);
    }

    ///< merchant info
    if (SUCCESS == iRet) {
        iRet = formMerchantInfo();
    }

    ///< separater
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        memset(buf, '-', 32);
        stPrinterPara.lineSpace = 0;
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< space bar
    if (SUCCESS == iRet) {
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg1);
    }

    ///< unionpay card info
    if (SUCCESS == iRet) {
        stPrinterPara.printAlign = ALIGN_LEFT;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg2);
    }

    ///< debit
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_Msg3);
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%3d", pstAll->stTotalIn.totalDebitNum);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 18*12);

        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld",
                pstAll->stTotalIn.totalDebitAmount / 100,
                pstAll->stTotalIn.totalDebitAmount % 100);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< credit
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_Msg4);
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%3d", pstAll->stTotalIn.totalCreditNum);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 18*12);

        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld",
                pstAll->stTotalIn.totalCreditAmount / 100,
                pstAll->stTotalIn.totalCreditAmount % 100);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);

        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< foreign card info
    if (SUCCESS == iRet) {
        stPrinterPara.printAlign = ALIGN_LEFT;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg5);
    }

    ///< debit
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_Msg3);
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%3d", pstAll->stTotalOut.totalDebitNum);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 18*12);

        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld",
                pstAll->stTotalOut.totalDebitAmount / 100,
                pstAll->stTotalOut.totalDebitAmount % 100);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< credit
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_Msg4);
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%3d", pstAll->stTotalOut.totalCreditNum);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 18*12);

        ///<
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld",
                pstAll->stTotalOut.totalCreditAmount / 100,
                pstAll->stTotalOut.totalCreditAmount % 100);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);
        ///<
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< feed paper
    if (SUCCESS == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '\n', 2);
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    iRet = startPrintData(iRet);
    if (KEY_ENTER == iRet) {
        goto PRINT_BEGIN;
    }

    if (SUCCESS == iRet) {
        transPrint_End();
    }
    return iRet;
}

/**
 * @brief print trade total
 */
int transPrint_TotalSheet(void)
{
    ///< wait keytone finish while kbtone enable
    if (IsKbToneEnable())
    {
        Sleep(150);
    }

    ///< print total sheet
    return __transPrint_TotalSheet(&DataTransDetail.transDetailData.totalAll);
}

/**
 * @brief form settle info
 */
int FormSettleInfo(unsigned char *asTradeName, unsigned short usNum, unsigned long ulAmount)
{
    int iRet = 0;
    char buf[128] = {0}, temp[128] = {0};
    ts_printer_para stPrinterPara;

    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_get_para(&stPrinterPara);
    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.lineSpace = 8;
    }

    ///< trade num
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        memset(buf, 0x20, 6);
        if (NULL != asTradeName) {
            strcpy(buf, (char *)asTradeName);
        }

        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%3d", usNum);
        printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 20*12);

        ///< trade
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%ld.%02ld", ulAmount/100, ulAmount%100);
        if (strlen(temp) > 11)
        {
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
            memset(buf, 0, sizeof(buf));
        }

        if (SUCCESS == iRet) {
            printer_formblank(ALIGN_RIGHT, buf, temp, PRINT_FONT_NORMAL, 32*12);
            iRet = printer_add_text_with_param(&stPrinterPara, buf);
        }
    }
    return iRet;
}

/**
 * @brief print settle sheet
 */
int __transPrint_PrintSettleSheet(tsTradeDetail *ptsTradeDetail, int isRePrint)
{
    int iRet = 0;
    char buf[128] = {0}, temp[128] = {0};
    tsTradeTotalForTrade *pstForTrade = NULL;
    ts_printer_para stPrinterPara;

    if (NULL == ptsTradeDetail) {
        return ERR_PARAM;
    }

    if (SUCCESS != (iRet = transPrint_Start())) {
        return iRet;
    }

PRINT_BEGIN:
    iRet = printer_clear();

    ///< printer parameter
    if (SUCCESS == iRet) {
        memset(&stPrinterPara, 0, sizeof(ts_printer_para));
        iRet = printer_get_para(&stPrinterPara);
    }

    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_LARGE;
        stPrinterPara.printAlign = ALIGN_CENTER;
        stPrinterPara.lineSpace = 8;
    }

    ///< title
    if (SUCCESS == iRet) {
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg6);
    }

    ///< merchant info
    if (SUCCESS == iRet) {
        iRet = formMerchantInfo();
    }

    if (SUCCESS == iRet) {
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        stPrinterPara.printAlign = ALIGN_LEFT;

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s%6.6s", AMSG_Print_BatchNo, ptsTradeDetail->SettleBatchNo);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< settle date & time
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, AMSG_Print_Msg7);
        memset(temp, 0, sizeof(temp));
        ///< year
        strncat(&temp[0], (char *)&ptsTradeDetail->SettleDate[0], 4);
        ///< date separator
        strncat(&temp[4], "-", 1);
        ///< month
        strncat(&temp[5], (char *)&ptsTradeDetail->SettleDate[4], 2);
        ///< date separator
        strncat(&temp[7], "-", 1);
        ///< day
        strncat(&temp[8], (char *)&ptsTradeDetail->SettleDate[6], 2);
        ///< separator
        strncat(&temp[10], " ", 1);
        ///< hour
        strncat(&temp[11], (char *)&ptsTradeDetail->SettleTime[0], 2);
        ///< time separator
        strncat(&temp[13], ":", 1);
        ///< min
        strncat(&temp[14], (char *)&ptsTradeDetail->SettleTime[2], 2);
        ///< time separator
        strncat(&temp[16], ":", 1);
        ///< sec
        strncat(&temp[17], (char *)&ptsTradeDetail->SettleTime[4], 2);
        strcat(buf, temp);
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    ///< diliver
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        memset(buf, '-', 32);
        stPrinterPara.lineSpace = 0;
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    if (SUCCESS == iRet) {
        stPrinterPara.lineSpace = 8;
        iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_TotalExchange);
    }

    ///< internal settle
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        if (SETTLE_OK == ptsTradeDetail->InternalSettleFlag) {
            strcpy(buf, AMSG_Print_Msg8);
        }
        else {
            strcpy(buf, AMSG_Print_Msg9);
        }
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    if (SUCCESS == iRet) {
        pstForTrade = &(ptsTradeDetail->totalTrade.stTradeIn);
    }

    if (SUCCESS == iRet) {
        iRet = FormSettleInfo(AMSG_Print_Msg11, pstForTrade->totalSaleNum, pstForTrade->totalSaleAmount);
    }

    if (SUCCESS == iRet) {
        iRet = FormSettleInfo(AMSG_Print_Msg14, pstForTrade->totalRefundNum, pstForTrade->totalRefundAmount);
    }

    ///< foreign settle
    if (SUCCESS == iRet) {
        memset(buf, 0, sizeof(buf));
        if (SETTLE_OK == ptsTradeDetail->ForeignSettleFlag) {
            strcpy(buf, AMSG_Print_Msg15);
        }
        else {
            strcpy(buf, AMSG_Print_Msg16);
        }
        iRet = printer_add_text_with_param(&stPrinterPara, buf);
    }

    if (SUCCESS == iRet) {
        pstForTrade = &(ptsTradeDetail->totalTrade.stTradeOut);
    }

    if (SUCCESS == iRet) {
        iRet = FormSettleInfo(AMSG_Print_Msg11, pstForTrade->totalSaleNum, pstForTrade->totalSaleAmount);
    }

    if (SUCCESS == iRet) {
        iRet = FormSettleInfo(AMSG_Print_Msg14, pstForTrade->totalRefundNum, pstForTrade->totalRefundAmount);
    }

    if (isRePrint) {
        if (SUCCESS == iRet) {
            iRet = printer_add_text_with_param(&stPrinterPara, AMSG_Print_Msg18);
        }
    }

    ///< feed paper
    if (SUCCESS == iRet) {
        memset(temp, 0, sizeof(temp));
        memset(temp, '\n', 2);
        stPrinterPara.printAlign = ALIGN_LEFT;
        stPrinterPara.fontSize = PRINT_FONT_NORMAL;
        iRet = printer_add_text_with_param(&stPrinterPara, temp);
    }

    iRet = startPrintData(iRet);
    if (KEY_ENTER == iRet) {
        goto PRINT_BEGIN;
    }

    ///< update settle print flag
    if (SUCCESS == iRet && !ptsTradeDetail->SettlePrintFlag) {
        ptsTradeDetail->SettlePrintFlag = 1;
        UFile_WriteFileIndexOf(DB_TransDetail);
    }

    if (SUCCESS == iRet) {
        transPrint_End();
    }
    return iRet;
}

/**
 * @brief print settle sheet
 */
int transPrint_PrintSettleSheet(void)
{
    return __transPrint_PrintSettleSheet(&DataTransDetail.transDetailData, 0);
}

/**
 * @brief reprint settle sheet
 */
int transPrint_RePrintSettleSheet(void)
{
    ///< wait keytone finish while kbtone enable
    if (IsKbToneEnable()) {
        Sleep(150);
    }

    ///< have finished settle
    if (0x01 != DataChange.ucSettleFlag) {
        return ERR_NO_SETTLE;
    }
    return __transPrint_PrintSettleSheet(&DataTransDetail.lastTransDetailData, 1);
}

