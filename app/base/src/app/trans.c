#include "bwsdk_api.h"
#include "logger.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "mmi_printer.h"
#include "sysFile.h"
#include "uFile.h"

#include "trans.h"
#include "cashier.h"
#include "EmvKernel.h"
#include "Emv_Trans.h"
#include "Emv_Callback.h"

#ifdef TAG
#undef TAG
#endif
#define TAG "trans"

void msg_displayErr(int _ret)
{
    if (_ret == ERR_END) {
        return;
    }

    if (_ret == SUCCESS) {
        mmi_clearLine(DISP_ClearALL);
        if (ExtraData.transType == TRANS_LOADRF) {
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_DownloadSuccess);
        }
        else {
            mmi_display(DISP_VCenter, DISP_HCenter, "%s %s",
                        trans_GetTransName(ExtraData.transType),
                        AMSG_Success);
        }
        mmi_inputWaitKeypress(5);
        return;
    }
    transErr_DispErrMsg(ExtraData.transType, _ret);
}

int trans_Confirm(const char *title)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, title);
    mmi_display(DISP_VCenter, DISP_HCenter, AMSG_PlzConfirm);
    while(1) {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_NONE:
            return ERR_TIMEOUT;
        case KEY_CANCEL:
            return ERR_CANCEL;
        case KEY_ENTER:
            return SUCCESS;
        default:
            break;
        }
    }
}

static int trans_SaveAndPrint(const char *msg)
{
    int iRet = SUCCESS;

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_VCenter, DISP_HCenter, !msg ? AMSG_Approval : msg);

    ///< save and print
    iRet = transUtil_SaveTrans();
    if (!DataEsign.bisEsPrintVoucher && DataConstant.ucPrintTimes < 1) {
        mmi_inputWaitKeypress(5);
    }

#if defined(P90)
    if (SUCCESS == iRet
#ifdef ENABLE_ESIGN
        && esign_Processing() != SUCCESS
#endif
        && DataConstant.ucPrintTimes > 0)
    {
        ///< print voucher
        iRet = PrintVoucherSheet(&DataTrans, 0, 0);

        ///< update print flag while print success
        if (SUCCESS == iRet) {
            transUtil_UpdatePrintState(1, DataTransDetail.lastTransIndex);
        }
    }
#endif
    return iRet;
}

int trans_Check(void)
{
    int iRet = SUCCESS;
    tsTransData tmpTransData;
    unsigned char transType = DataTrans.transType;
    int iBytesNum = 0;

    ExtraData.transType = DataTrans.transType;
    memset(&tmpTransData, 0, sizeof(tsTransData));
    memcpy(&tmpTransData, &DataTrans, sizeof(tsTransData));

    ///< check trans on-off
    if ((TRANS_QUERY_BAL == ExtraData.transType)
        && !isEnable_inquiry) {
        return ERR_FUNC_CLOSE;
    }
    else if ((TRANS_SALE == ExtraData.transType)
        && !isEnable_sale) {
        return ERR_FUNC_CLOSE;
    }
    else if ((TRANS_VOID_SALE == ExtraData.transType)
        && !isEnable_voidSale) {
        return ERR_FUNC_CLOSE;
    }
    else if ((TRANS_REFUND == ExtraData.transType)
        && !isEnable_refund) {
        return ERR_FUNC_CLOSE;
    }

    ///< check cashier logon state
    if (!DataChange.isCashierLogon) {
        ///< admin cashier can not trans
        if (!memcmp(DataChange.cashierNo, DataCashier.aucSYSCashierNo, CASH_SYSCASHIERNOLEN)) {
            return ERR_ADMIN_LOGON;
        }
        return ERR_NOT_LOGON;
    }
    ///< check logon state
    else if (transType != TRANS_LOGON && !DataChange.isLogon) {
        return ERR_NOT_LOGON;
    }
    ///< check a new batch
    else if (transType != TRANS_LOGON && DataChange.isUpdateBatch) {
        return ERR_BATCH;
    }
    ///< store key err
    else if (transType != TRANS_LOGON && DataChange.isStoreKeyDownRight) {
        return ERR_STORE_KEY;
    }
    ///< check trans num is full
    else if (transType != TRANS_LOGON
          && transType != TRANS_SETTLEMENT
          && transType != TRANS_QUERY_BAL
          && DataTransDetail.transCount >= DataConstant.maxTransNum)
    {
        return ERR_TRANS_FULL;
    }
    ///< 签退检查是否有交易,有交易则提示请先结算
    else if (TRANS_LOGOFF == transType && DataTransDetail.transCount > 0) {
        return ERR_PLZ_SETTLE;
    }
    ///< 检查POS剩余存储空间
    else if ((TRANS_LOGON != transType) && (TRANS_LOGOFF != transType)
            && (TRANS_QUERY_BAL != transType) && (TRANS_SETTLEMENT != transType)) {
        iBytesNum = FsGetFreeSpace();
        ///< 需保证可以容纳一笔交易的极限存储空间包含电签
        if (iBytesNum < (sizeof(tsTransData) + sizeof(tsReverseData) + sizeof(tsScriptData) + 1024)) {
            return ERR_POOR_STORAGE;
        }
    }

    ///< 恢复原交易类型
    memset(&DataTrans, 0, sizeof(tsTransData));
    memcpy(&DataTrans, &tmpTransData, sizeof(tsTransData));
    DataTrans.transType = transType;
    ExtraData.transType = transType;

    return iRet;
}

/**
 * @brief logon processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Logon(void)
{
    int iRet = SUCCESS;

    transUtil_ClearGlobalData();
    DataTrans.transType = TRANS_LOGON;

    ///< check
    iRet = trans_Check();
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< update state
    if (SUCCESS == iRet) {
        iRet = transUtil_UpdateLogonState(1);
    }
    msg_displayErr(iRet);
    return iRet;
}

/**
 * @brief pos logon
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_PosLogon(void)
{
    int iRet = 0;

    ///< cashier no logon
    while (!DataChange.isCashierLogon)
    {
        iRet = trans_CashierLogon();
        if (SUCCESS != iRet) {
            return iRet;
        }
    }
    return trans_Logon();
}

/**
 * @brief logoff processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Logoff(void)
{
    int iRet = SUCCESS;

    DataTrans.transType = TRANS_LOGOFF;

    ///< check
    iRet = trans_Check();
    ///< on-line transaction processing
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< update state
    if (SUCCESS == iRet) {
        iRet = transUtil_UpdateLogonState(0);
    }
    msg_displayErr(iRet);
    return iRet;
}

/**
 * @brief ic card aid download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadAID(void)
{
    int iRet = SUCCESS;

    ExtraData.transType = TRANS_LOADAID;

    ///< on-line transaction processing
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< save flag
    if (SUCCESS == iRet) {
        DataChange.downFlag |= DOWN_PARAM_AID;
        iRet = UFile_WriteFileIndexOf(DB_Change);
    }
    msg_displayErr(iRet);
    return iRet;
}

/**
 * @brief ic card capk download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadCAPK(void)
{
    int iRet = SUCCESS;

    ExtraData.transType = TRANS_LOADCAPK;

    ///< on-line transaction processing
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< save flag
    if (SUCCESS == iRet) {
        DataChange.downFlag |= DOWN_PARAM_CAPK;
        iRet = UFile_WriteFileIndexOf(DB_Change);
    }

    msg_displayErr(iRet);
    return iRet;
}

/**
 * @brief rf parameter download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadRF(void)
{
    int iRet = SUCCESS;

    ExtraData.transType = TRANS_LOADRF;

    ///< on-line transaction processing
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< save flag
    if (SUCCESS == iRet) {
        DataChange.downFlag |= DOWN_PARAM_UNTOUCH;
        iRet = UFile_WriteFileIndexOf(DB_Change);
    }
    msg_displayErr(iRet);
    return iRet;
}

void trans_GetInfo(void)
{
    tsSysTime datime;
    char date[8+1] = {0}, time[6+1] = {0};

    ///< get system date and time
    memset(&datime, 0, sizeof(datime));
    GetSysLocalTime(&datime);
    snprintf((char *)date, sizeof(date), "%04d%02d%02d", datime.year, datime.mon, datime.day);
    snprintf((char *)time, sizeof(time), "%02d%02d%02d", datime.hour, datime.min, datime.sec);

    memset(ExtraData.serialNo, 0, sizeof(ExtraData.serialNo));
    transUtil_GetSN(ExtraData.serialNo, sizeof(ExtraData.serialNo));

    if ((TRANS_VOID_SALE != ExtraData.transType)) {
        memset(DataTrans.batchNumber, 0, sizeof(DataTrans.batchNumber));
        memcpy(DataTrans.batchNumber, DataChange.batchNumber, 6);
    }

    memset(DataTrans.traceNumber, 0, sizeof(DataTrans.traceNumber));
    memcpy(DataTrans.traceNumber, DataChange.traceNumber, 6);
    memcpy(DataTrans.date, date, sizeof(DataTrans.date));
    memcpy(DataTrans.time, time, sizeof(DataTrans.time));
}

/**
 * @brief  standby UI
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_standby(unsigned char *imgData, unsigned short imgW, unsigned short imgH)
{
    extern int posParam_SystemManagement(void);

    int iRet = SUCCESS;
    unsigned int uiEvent = 0, uiCurEvent = 0;
    unsigned int drvDataLen;
    unsigned char drvData[1024];
    unsigned char bRef = 1;
    unsigned char bSleep;
    tsSysTime time;

    bSleep = 0;
    KbFlush();
    uiEvent = EVENT_KEY_DRV|EVENT_MAG_DRV|EVENT_ICC_DRV;

    while(1)
    {
        if (GetSysSleepLevel() != (sleep_level_t)SystemSave.sysSleepType) {
            SetSysSleepLevel((sleep_level_t)SystemSave.sysSleepType);
        }

        if (transUI_CheckBattery()) {
            bRef = 1;
        }

        transUtil_CheckMdmPush();
        bRef = 1;
        /*!< -------------------------------------------------- >!*/
        ///< 进入休眠状态
        if (!GetSysStatus()) {
            Sleep(50);
            if (!bSleep) {
                mmi_EventClose(uiEvent);
            }
            bRef = 0;
            bSleep = 1;
            continue;
        }
        else if (bSleep) {
            bRef = 1;
            bSleep = 0;
            KbFlush();
        }

        /*!< -------------------------------------------------- >!*/
        memset(&time, 0, sizeof(tsSysTime));
        GetSysLocalTime(&time);

        uiCurEvent = uiEvent;
        if (bRef) {
            iRet = mmi_EventOpen(uiEvent);
            if (iRet) {
                msg_displayErr(iRet);
            }

            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_Line2, DISP_Right, "%-*s", (SCREEN_WIDTH/2-8)/2+8, AMSG_Title_Headline);
            mmi_display(DISP_Line3, DISP_Right, "V%-*s", (SCREEN_WIDTH/2-8)/2+7, BCTCVER);
            if (DataChange.isLogon && DataChange.isCashierLogon) {
                mmi_display(DISP_Line4, DISP_Right, "%-*s", (SCREEN_WIDTH/2-8)/2+8, AMSG_Welcome);
            } else {
                mmi_display(DISP_Line4, DISP_Right, "%-*s", (SCREEN_WIDTH/2-8)/2+8, AMSG_NotLogon);
            }
            if ((NULL != imgData) && imgW && imgH) {
                mmi_displayBMP(DISP_Line2, 0, imgData, imgW, imgH);
            }
            bRef = 0;
        }
        mmi_clearLine(DISP_Line6);
        mmi_display(DISP_Line6, DISP_HCenter, "%04d-%02d-%02d %02d:%02d:%02d", time.year, time.mon, time.day, time.hour, time.min, time.sec);

        ///< 读卡
        drvDataLen = sizeof(drvData);
        memset(drvData, 0, sizeof(drvData));
        iRet = mmi_EventWait(&uiCurEvent, drvData, &drvDataLen, 1);
        if (ERR_TIMEOUT == iRet || !GetSysStatus()) {
            continue;
        }
        else if (SUCCESS != iRet) {
            break;
        }

        SetSysSleepLevel(SLEEP_LEVEL_NOSLEEP);
        bRef = 1;
        transUtil_ClearGlobalData();
        if (EVENT_KEY_DRV == uiCurEvent) {
            switch(drvData[0])
            {
            case KEY_ASCII1:
                mmi_EventClose(uiEvent);
                trans_Sale();
                continue;
            case KEY_ENTER:
            case KEY_MENU:
                mmi_EventClose(uiEvent);
                trans_mainMenu();
                continue;
            case KEY_FUNC:  ///< 待机界面增加进入系统管理快捷键
                mmi_EventClose(uiEvent);
                if (SUCCESS == CASH_CheckManagePwd(AMSG_Title_SysManage)) {
                    posParam_SystemManagement();
                }
                continue;
            default:
                break;
            }
        }
        else if (EVENT_ICC_DRV == uiCurEvent) {
            if (IccResetRev(NULL) >= 0 && !IccGetResponseEnableRev(1)) {
                mmi_EventClose((uiEvent&~uiCurEvent));
                ExtraData.entryType = ENTRY_STANDBY;
                ExtraData.eventType = uiCurEvent;
                trans_Sale();
                continue;
            }
        }
        else if (EVENT_MAG_DRV == uiCurEvent) {
            mmi_EventClose(uiEvent);
            ExtraData.entryType = ENTRY_STANDBY;
            ExtraData.eventType = uiCurEvent;
            memcpy(&ExtraData.magTrack, drvData, sizeof(ExtraData.magTrack));
            trans_Sale();
            continue;
        }
        bRef = 0;
    }
    return iRet;
}

/**
 * @brief query balance processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_QueryBal(void)
{
    int iRet = SUCCESS;

    DataTrans.transType = TRANS_QUERY_BAL;

    //检查
    iRet = trans_Check();
    ///< 读卡
    if (SUCCESS == iRet) {
        iRet = transUI_SwipeCard(0);
    }
    if (SUCCESS == iRet) {
        iRet = EMV_Trans();
    }
    if (SUCCESS == iRet) {
        transUI_DisplayBalance();
    } else {
        msg_displayErr(iRet);
    }
    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  purchase processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Sale(void)
{
    int iRet = SUCCESS;

    DataTrans.transType = TRANS_SALE;

    ///< 检查交易环境
    iRet = trans_Check();

    ///< 输金额
    if ((SUCCESS == iRet) && !DataTrans.ulAmount) {
        iRet = transUI_inputAmount(AMSG_InputAmount, 1, 999999999, &DataTrans.ulAmount);
    }

    ///< 读卡/扫码
    if ((SUCCESS == iRet) && !ExtraData.eventType) {
        iRet = transUI_SwipeCard(DataTrans.ulAmount);
    }

    ///< online process
    if (SUCCESS == iRet) {
        ///< add scan
        if (EVENT_SCAN_DRV == ExtraData.eventType) {
            iRet = transOnline_process();
        }
        ///< EMV process
        else {
            iRet = EMV_Trans();
        }
    }

    ///< save and print
    if (SUCCESS == iRet) {
        iRet = trans_SaveAndPrint(NULL);
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  cancel purchase processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_VoidSale(void)
{
    int iRet = SUCCESS;
    unsigned char bInputPIN = DataConstant.isVoidInputPIN;
    unsigned char bOnline = 1;
    const char *title = trans_GetTransName(TRANS_VOID_SALE);

    DataTrans.transType = TRANS_VOID_SALE;

    ///< 检查交易环境
    iRet = trans_Check();

    ///< Input Super Password 主管密码
    if ((SUCCESS == iRet) && (DataConstant.bisCheckAdminPwd)) {
        iRet = CASH_CheckAdminPwd(title);
    }

    ///< Input Original Trace Number 输入原凭证号
    if (SUCCESS == iRet) {

        ExtraData.oldTransIndex = 0;
        iRet = transUI_SearchTrans(title, &ExtraData.oldTransIndex);
    }

    ///< Read card 读卡
    if ((SUCCESS == iRet) && DataConstant.isVoidSwipe) {
        iRet = transUI_SwipeCard(DataTrans.ulAmount);
    }

    ///< EMV流程
    if ((SUCCESS == iRet) && DataConstant.isVoidSwipe) {
        bInputPIN = 0;
        bOnline = 0;
        iRet = EMV_Trans();
    }

    ///< Input PIN 输密
    if ((SUCCESS == iRet) && bInputPIN) {
        iRet = transUI_InputCardPIN();
    }

    ///< 联机处理
    if ((SUCCESS == iRet) && bOnline) {
        iRet = transOnline_process();
    }

    ///< save and print
    if (SUCCESS == iRet) {
        iRet = trans_SaveAndPrint(AMSG_VoidSuccess);
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  scan void sale processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_ScanVoidSale(void)
{
    int iRet = SUCCESS;
    const char *title = trans_GetTransName(TRANS_VOID_SALE);

    DataTrans.transType = TRANS_VOID_SALE;

    ///< 检查交易环境
    iRet = trans_Check();

    ///< Input Super Password 主管密码
    if ((SUCCESS == iRet) && (DataConstant.bisCheckAdminPwd)) {
        iRet = CASH_CheckAdminPwd(title);
    }

    ///< search record by Original scan voucher no.
    ///< 根据原付款凭证号查找交易
    if (SUCCESS == iRet) {
        ExtraData.oldTransIndex = 0;
        iRet = transUI_SearchScanTrans(&ExtraData.oldTransIndex);
    }

    ///< online process
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< save and print
    if (SUCCESS == iRet) {
        iRet = trans_SaveAndPrint(AMSG_VoidSuccess);
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  refund process
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Refund(void)
{
    int iRet = SUCCESS;
    DataTrans.transType = TRANS_REFUND;

    ///< 检查交易环境
    iRet = trans_Check();

    ///< Input Super Password 主管密码
    if ((SUCCESS == iRet) && (DataConstant.bisCheckAdminPwd)) {
        ///< check admin pwd first
        iRet = CASH_CheckAdminPwd(trans_GetTransName(TRANS_REFUND));
    }

    ///< Read card 读卡
    if (SUCCESS == iRet) {
        iRet = transUI_SwipeCard(0);
    }

    ///< EMV流程
    if (SUCCESS == iRet)
    {
        _TRANS_HANDLE.bEmvInputPINBypass = 1;
        iRet = EMV_Trans();
    }

    ///< save and print
    if (SUCCESS == iRet) {
        iRet = trans_SaveAndPrint(AMSG_RefundSuccess);
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  scan refund process
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_ScanRefund(void)
{
    int iRet = SUCCESS;
    DataTrans.transType = TRANS_REFUND;
    unsigned char scanCode[256] = {0};

    ///< 检查交易环境
    iRet = trans_Check();

    ///< Input Super Password 主管密码
    if ((SUCCESS == iRet) && (DataConstant.bisCheckAdminPwd)) {
        ///< check admin pwd first
        iRet = CASH_CheckAdminPwd(trans_GetTransName(TRANS_REFUND));
    }

    ///< 输金额
    if ((SUCCESS == iRet) && !DataTrans.ulAmount) {
        iRet = transUI_inputAmount(AMSG_InputAmount, 1, 999999999, &DataTrans.ulAmount);
    }

    ///< 扫码或手输付款凭证号
    if (SUCCESS == iRet) {
        iRet = transUI_ScanCode(AMSG_ScanVoucherNo, NULL, NULL, scanCode, 1);
        if (SUCCESS == iRet) {
            memcpy(DataTrans.ascScanVoucherNo, scanCode, 20);
            ///< 从付款凭证号获取原交易日期
            memcpy(DataTrans.oldDate, &DataTrans.ascScanVoucherNo[4], 4);
            DataTrans.cardInputType = InputMode_Scan;
        }
    }

    ///< online process
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< save and print
    if (SUCCESS == iRet) {
        iRet = trans_SaveAndPrint(AMSG_RefundSuccess);
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    transUI_RemoveCard();
    return iRet;
}

/**
 * @brief  batch settle processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_BatchSettle(void)
{
    extern int transUtil_IncreaseBatchNumber(unsigned long increaseNumber);
    int iRet = SUCCESS;
    const char *title = NULL;

    DataTrans.transType = TRANS_SETTLEMENT;
    title = trans_GetTransName(DataTrans.transType);

    ///< 检查交易环境
    iRet = trans_Check();

    if (SUCCESS == iRet) {
        iRet = trans_Confirm(title);
    }

    ///< 显示交易汇总
    if (SUCCESS == iRet) {
        iRet = search_TradeTotal();
    }

    ///< 联机结算
    if (SUCCESS == iRet) {
        iRet = transOnline_process();
    }

    ///< 保存结算标识
    if (SUCCESS == iRet) {
        if (!DataChange.ucSettleFlag) {
            DataChange.ucSettleFlag = 1;
            iRet = UFile_WriteFileIndexOf(DB_Change);
        }
    }

    ///< 显示结算结果
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SettlementSuccess);
        mmi_inputWaitKeypress(5);
    }

    if (SUCCESS == iRet) {
        iRet = transPrint_PrintSettleSheet();

        ///< 结算成功,清除交易数据
        iRet = transUtil_ClearTrans();
    }

    ///< display err info
    if (SUCCESS != iRet) {
        msg_displayErr(iRet);
    }

    ///< update batch no.
    if (SUCCESS == iRet) {
        transUtil_IncreaseBatchNumber(1);
    }
    return iRet;
}

