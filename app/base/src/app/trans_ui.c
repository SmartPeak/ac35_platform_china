/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     trans_online                                                    *
*  @brief    on-line transaction processing                                  *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "logger.h"
#include "applib.h"
#include "applib_def.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "uFile.h"
#include "sysFile.h"
#include "trans.h"

#ifdef TAG
#undef TAG
#endif
#define TAG "trans_ui.c"

#define DEBUG_TRANS_UI          0

#define NO_CARD         0
#define HAVE_CARD       1

extern char *trans_GetTransName(int transType);

int transUI_Display(unsigned int line, unsigned int column, int fontColor, int bgColor, char *pszFmt, ...)
{
    char szMsg[255];
    tsDispParam m_DispParam;
    va_list args;

    if (!pszFmt) {
        return line;
    }

    va_start(args, pszFmt);
#ifdef SDK_V1_8_8
    vsnprintf(szMsg, sizeof(szMsg), pszFmt, args);
#else
    vsprintf(szMsg, pszFmt, args);
#endif
    va_end(args);

    memset(&m_DispParam, 0, sizeof(m_DispParam));
    m_DispParam.color = fontColor;
    m_DispParam.fontBackgroundColor = bgColor;
    m_DispParam.backgroundColor = bgColor;
    m_DispParam.alignL = column;
    return mmi_displayEx(&m_DispParam, (DISP_VAlign)line, szMsg);
}

inline int transUI_Input(const char *pCaption, unsigned int inputType, unsigned char *pBuff, int minLen, int maxLen)
{
    unsigned char changeIMNum = 0;

    if (NULL == pCaption || NULL == pBuff) {
        return ERR_PARAM;
    }

    if (((inputType&0xFF) & InputMethod_digital))
        changeIMNum++;
    if (((inputType&0xFF) & InputMethod_lower_abc))
        changeIMNum++;
    if (((inputType&0xFF) & InputMethod_caps_abc))
        changeIMNum++;
    if (((inputType&0xFF) & InputMethod_hex))
        changeIMNum++;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, DISP_Left, pCaption);
    mmi_display(DISP_Line5, DISP_Left, AMSG_InputErrClearKey);
    if (changeIMNum > 1) {
        mmi_displayOfBlackBg(DISP_Bottom2, DISP_Left, AMSG_ChangeIM);
    }
    return mmi_inputString(DISP_Line3, inputType, pBuff, minLen, maxLen, NULL, 60);
}

/**
 * @brief  低电量提示
 */
int transUI_CheckBattery(void)
{
#if defined(HAVE_CHARGING_FEATURE)
    bool bFirst = true;
    EN_BATTERY_STATE batteryState = Normal, listBatteryState = Normal;
    unsigned int listTime = 0;
    static unsigned int mListTime = 0;
    int fontColor = MERCURY_RED;
    int bgColor = MERCURY_WHITE;
    int iKey = -1;

    while(1)
    {
        ///< 获取电池电压等级
        batteryState = AppLib_GetBatteryState();
        if (batteryState == Normal                                          ///< 普通, 退出
        || (batteryState != Forbidden && IsChargerExist() && IsCharging())  ///< 电量不是过低并且正在充电, 退出
        || (KEY_ENTER == iKey && batteryState != Forbidden)
        ) {
            break;
        }
        else if (batteryState != Forbidden && bFirst) {
            if (!mListTime) {
                transUtil_CheckTimeout(&mListTime, 5*(60*1000));
            }
            else if (!transUtil_CheckTimeout(&mListTime, 5*(60*1000))) {
                break;
            }
        }

        if (bFirst) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Warnings);
        }

        if (listBatteryState != batteryState || transUtil_CheckTimeout(&listTime, 500)) {
            if (listBatteryState != batteryState) {
                mmi_clearLine(DISP_Line3);
                transUI_Display(DISP_Line3, DISP_HCenter, fontColor, bgColor, batteryState == Forbidden ? AMSG_BatteryTooLow : AMSG_BatteryLow);
                listBatteryState = batteryState;
            }

            mmi_clearLine(DISP_Line5);
            if (IsBatteryExist() && IsChargerExist() && IsCharging()) {
                transUI_Display(DISP_Line5, DISP_HCenter, fontColor, bgColor, "%s %d%%", AMSG_InCharge, GetBatteryPercent());
            }
            else if (IsBatteryExist()) {
                transUI_Display(DISP_Line5, DISP_HCenter, fontColor, bgColor,
                                batteryState == Forbidden ? AMSG_PlzConnectCharger : AMSG_PlzChargeInTime);
            }
            else {
                transUI_Display(DISP_Line5, DISP_HCenter, fontColor, bgColor, AMSG_PlzPlugInBattery);
            }
        }

        if (bFirst){
            bFirst = false;
            transErr_ErrBeep();
        }

        iKey = -1;
        if (KbHit()) {
            Sleep(100);
            continue;
        }

        iKey = mmi_inputGetKeypress();
        ///< 已警告过
        if (KEY_ENTER == iKey && (Warning == batteryState || Error == batteryState)) {
            transUtil_CheckTimeout(&mListTime, 1);
            break;
        }
    }

    if (false == bFirst) {
        return ERR_END;
    }
#endif
    return SUCCESS;
}

///< 提示移卡、拔卡
int transUI_RemoveCard(void)
{
#if defined(P90)
    unsigned char bRef = 1;
    unsigned char bBeep = 1;
    unsigned int event = EVENT_ICC_DRV|EVENT_MFR_DRV;
    T_SOFTTIMER tm;
    PiccInfo_T iccInfo;

    memset(&tm, 0, sizeof(tm));
    while(1)
    {
        memset(&iccInfo, 0, sizeof(iccInfo));

        if (0 == IccStatusRev()){
            if (!bBeep && !s_TimerCheck(&tm)) {
                bBeep = 1;
            }

            if (bRef) {
                bRef = 0;
                mmi_clearLine(DISP_ClearALL);
                mmi_display(DISP_VCenter, DISP_HCenter, AMSG_PlzPulloutCard);
            }

            if (bBeep) {
                bBeep = 0;
                SpSysBeepOn(1000, 200);
                s_TimerSet(&tm, 1*1000);
            } else {
                Sleep(10);
            }
            continue;
        }
        break;
    }
    if ((EVENT_MFR_DRV&event)) {
        transUtil_LED_Close();
    }
    mmi_EventClose(event);
#else
    transUtil_LED_Close();
#endif
    return SUCCESS;
}

static unsigned int transUI_GetEventType(void)
{
    unsigned int uiEvent = EVENT_NULL;

    uiEvent = EVENT_MAG_DRV|EVENT_ICC_DRV|EVENT_MFR_DRV;
    switch (ExtraData.transType)
    {
    case TRANS_SALE:
        uiEvent |= EVENT_SCAN_DRV;
        break;
    default:
        break;
    }

    if (!AppLib_GetParam().deviceHwInfo.is_spt_camera) {
        uiEvent &= ~EVENT_SCAN_DRV;
    }
    return uiEvent;
}

static int transUI_InputCardNo(unsigned char firstChar, unsigned char* cardNo, unsigned char* pCardNoLen)
{
    int iRet = SUCCESS;
    unsigned char iLen = 0;
    unsigned char mBuff[21] = {0};

    if (!cardNo) {
        return ERR_PARAM;
    }

    if (firstChar) {
        mBuff[0] = firstChar;
    }

    iRet = transUI_Input(AMSG_InputCardNo, InputMethod_digital, mBuff, 12, 19);
    if (SUCCESS == iRet) {
        iLen = strlen((char *)mBuff);
        tools_asc_bcd(cardNo, (iLen + 1) / 2, mBuff, ((iLen + 1) / 2) * 2);
    }

    if (pCardNoLen) {
        *pCardNoLen = iLen;
    }
    return iRet;
}

/**
 * @brief  刷卡
 * @brief  swipe card
 */
int transUI_SwipeCard(unsigned long ulAmount)
{
    int iRet = SUCCESS;
    unsigned int uiEvent = EVENT_NULL, uiCurEvent = EVENT_NULL;
    unsigned int drvDataLen;
    unsigned char drvData[1024];
    unsigned char bRef, bRefSwip;
    char dispMsg[32];
    char *pEqual = NULL;

    uiEvent = transUI_GetEventType();
    if ((iRet = mmi_EventOpen(uiEvent)) != SUCCESS) {
        goto ERR;
    }

    if ((EVENT_MFR_DRV&uiEvent)) {
        transUtil_LED_WaitReadCard();
    }

    bRef = 1;
    bRefSwip = 0;
    while(1)
    {
        if (bRef) {
            bRef = 0;

            memset(dispMsg, 0, sizeof(dispMsg));
            if ((uiEvent&EVENT_MFR_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "/");
                }
                strcat(dispMsg, AMSG_TapCard);
            }
            if ((uiEvent&EVENT_ICC_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "/");
                }
                strcat(dispMsg, AMSG_PlugInCard);
            }
            if ((uiEvent&EVENT_MAG_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "/");
                }
                strcat(dispMsg, AMSG_SwipeCard);
            }
            if ((uiEvent&EVENT_MANUAL_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "/");
                }
                strcat(dispMsg, AMSG_HandCardNo);
            }
            if ((uiEvent&EVENT_SCAN_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "/");
                }
                strcat(dispMsg, AMSG_ScanCode);
            }

            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
            if (ulAmount > 0)
            {
                mmi_display(DISP_Line3, DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
            }

            if (bRefSwip) {
                mmi_display(DISP_Line4, DISP_HCenter, AMSG_ReadCardErr);
                mmi_display(DISP_Line5, DISP_HCenter, "%s %s", AMSG_PlzAgain, dispMsg);
            }
            else {
                mmi_display(DISP_Line4, DISP_HCenter, "%s %s", AMSG_Plz, dispMsg);
            }
        }

        bRefSwip = 0;
        drvDataLen = sizeof(drvData);
        memset(drvData, 0, sizeof(drvData));
        uiCurEvent = uiEvent;
        if ((iRet = mmi_EventWait(&uiCurEvent, drvData, &drvDataLen, 60)) != SUCCESS) {
            break;
        }

        if (EVENT_MFR_DRV != uiCurEvent) {
            transUtil_LED_Close();
        }

        if (EVENT_KEY_DRV == uiCurEvent) {
            if (KEY_CANCEL == drvData[0]) {
                iRet = ERR_CANCEL;
                break;
            }
            else if ((uiEvent&EVENT_MANUAL_DRV)
                 && (drvData[0] >= KEY_ASCII0 && drvData[0] <= KEY_ASCII9)) {
                mmi_EventClose(uiEvent);
                uiEvent = EVENT_NULL;

                uiCurEvent = EVENT_MANUAL_DRV;
                iRet = transUI_InputCardNo(drvData[0], drvData, &DataTrans.sourceAccLen);
                ///< get bcd card no.
                if (SUCCESS == iRet) {
                    memcpy(DataTrans.sourceAcc, drvData, (DataTrans.sourceAccLen + 1) / 2);
                    DataTrans.cardInputType = InputMode_Manual;
                }
                break;
            }
        }
        else if (EVENT_ICC_DRV == uiCurEvent) {
            if (IccResetRev(NULL) >= 0)
            {
                if (0 == IccGetResponseEnableRev(1)) {
                    break;
                }
            }
            bRefSwip = 1;

            if ((uiEvent&EVENT_MAG_DRV)) {
                uiCurEvent |= EVENT_MAG_DRV;
            }
            // 复位失败则降级
            bRef = 1;
            mmi_EventClose(uiEvent);

            uiEvent = uiCurEvent;
            mmi_EventOpen(uiCurEvent);
            continue;
        }
        else if (EVENT_MAG_DRV == uiCurEvent) {
            memcpy(&ExtraData.magTrack, drvData, sizeof(ExtraData.magTrack));
            pEqual = strchr((char*)(ExtraData.magTrack.aucTrack2), '=');
            if(pEqual != NULL && (*(pEqual + 5) == '2' || *(pEqual + 5) == '6')) {
                bRef = 1;
                mmi_EventClose(uiEvent);
                uiEvent &= ~EVENT_MAG_DRV;
                mmi_EventOpen(uiEvent);
                if ((uiEvent&EVENT_MFR_DRV)) {
                    transUtil_LED_WaitReadCard();
                }
                continue;
            }
            break;
        }
        else if (EVENT_MFR_DRV == uiCurEvent) {
            break;
        }
        ///< add scan
        else if (EVENT_SCAN_DRV == uiCurEvent) {
            mmi_EventClose(uiCurEvent);         ///< 关闭扫码
            TTS_Abort_OEM();                    ///< 中断语音播报
            AudioDtmfAbort_OEM();
            AudioDtmfPlay_OEM(DTMF_Nine, 1);    ///< 播放扫码完成提示音
            memcpy(DataTrans.ScanCodeC2B, drvData, sizeof(DataTrans.ScanCodeC2B)-1);
            DataTrans.cardInputType = InputMode_Scan;
            Sleep(120);
            break;
        }
    }

ERR:
    if (SUCCESS == iRet) {
        ExtraData.eventType = uiCurEvent;
        uiEvent &= ~uiCurEvent;
    }
    mmi_EventClose(uiEvent);
    return iRet;
}

/**
 * @brief  display trade info
 */
inline int transUI_DisplayTradeInfo(unsigned char keySwitch, tsTransData *ptsTransData)
{
    int iRet = SUCCESS;
    char mBuf[32] = {0};

    if (NULL == ptsTransData) {
        return ERR_PARAM;
    }

    mmi_clearLine(DISP_ClearALL);
    ///< trade type name
    memset(mBuf, 0, sizeof(mBuf));
    ///< add scan
    if (InputMode_Scan == ptsTransData->cardInputType) {
        switch (ptsTransData->transType) {
            case TRANS_SALE:
                strcpy((char *)mBuf, AMSG_ScanSale);
                break;
            case TRANS_VOID_SALE:
                strcpy((char *)mBuf, AMSG_ScanSaleVoid);
                break;
            case TRANS_REFUND:
                strcpy((char *)mBuf, AMSG_ScanRefund);
                break;
            default:
                GetTradeName((unsigned char *)mBuf, ptsTransData->transType);
                break;
        }
    }
    else {
        GetTradeName((unsigned char *)mBuf, ptsTransData->transType);
    }

    if (ptsTransData->isVoid) {
        strcat((char *)mBuf, AMSG_Revoked);
    }
    mmi_display(DISP_Line1, DISP_Left, mBuf);

    ///< card or pay code no.
    memset(mBuf, 0, sizeof(mBuf));
    ///< add scan
    if (InputMode_Scan == ptsTransData->cardInputType) {
        memcpy(mBuf, ptsTransData->ScanCodeC2B, sizeof(mBuf)-1);
    }
    else {
        tools_bcd_asc((unsigned char *)mBuf, ptsTransData->sourceAcc,
                      ptsTransData->sourceAccLen + (ptsTransData->sourceAccLen%2 ? 1 : 0));
        mBuf[ptsTransData->sourceAccLen] = 0x00;
    }
    transUtil_JudgeMaskCardNo(ptsTransData->transType, (unsigned char *)mBuf);
    mmi_display(DISP_Line2, DISP_Left, mBuf);

    ///< add scan
    ///< scan voucher no.
    if (InputMode_Scan == ptsTransData->cardInputType) {
        mmi_display(DISP_Line3, DISP_Left, AMSG_Print_ScanVoucherNo);
        mmi_display(DISP_Line4, DISP_Left, "%.*s", sizeof(ptsTransData->ascScanVoucherNo), ptsTransData->ascScanVoucherNo);
    }
    else {
        ///< trace no.
        mmi_display(DISP_Line3, DISP_Left, "%s%.*s", AMSG_Print_VoucherNo, sizeof(ptsTransData->traceNumber), ptsTransData->traceNumber);

        ///< auth no.
        mmi_display(DISP_Line4, DISP_Left, "%s%.*s", AMSG_Print_AuthNo, sizeof(ptsTransData->authCode), ptsTransData->authCode);
    }

    ///< date and time
    memset(mBuf, 0, sizeof(mBuf));
    ///< year
    strncat(&mBuf[0], (char *)&ptsTransData->date[0], 4);
    ///< date separator
    strncat(&mBuf[4], "-", 1);
    ///< month
    strncat(&mBuf[5], (char *)&ptsTransData->date[4], 2);
    ///< date separator
    strncat(&mBuf[7], "-", 1);
    ///< day
    strncat(&mBuf[8], (char *)&ptsTransData->date[6], 2);
    ///< separator
    strncat(&mBuf[10], " ", 1);
    ///< hour
    strncat(&mBuf[11], (char *)&ptsTransData->time[0], 2);
    ///< time separator
    strncat(&mBuf[13], ":", 1);
    ///< min
    strncat(&mBuf[14], (char *)&ptsTransData->time[2], 2);
    ///< time separator
    strncat(&mBuf[16], ":", 1);
    ///< sec
    strncat(&mBuf[17], (char *)&ptsTransData->time[4], 2);
    mmi_display(DISP_Line5, DISP_Left, mBuf);

    ///< amount
    mmi_display(DISP_Line6, DISP_Left, AMSG_UI_Msg1, ptsTransData->ulAmount / 100, ptsTransData->ulAmount % 100);

    if (SUCCESS == iRet && keySwitch) {
        while(1) {
            switch(mmi_inputWaitKeypress(60))
            {
            case KEY_ENTER:
                return SUCCESS;
            case KEY_CANCEL:
                return ERR_CANCEL;
            case KEY_NONE:
                return ERR_TIMEOUT;
            default:
                break;
            }
        }
    }
    return iRet;
}

/**
 * @brief  search trace info
 * @param pTitle [in] title txt
 * @param on_off [in] on-off
                      on_off[0]: 0x01 - re enter
                      on_off[1]: 0x01 - enter keypress last trace
 */
int transUI_SearchTransEx(const char *pTitle, const char on_off[2], unsigned int *pTransIndex, tsTransData *pTransData)
{
    int iRet;
    unsigned char isReInput = on_off[0];
    unsigned char isLastEnable = on_off[1];
    unsigned int index = 0;
    unsigned int inputType = mmi_setInputType(InputMethod_digital, InputMethod_digital|InputMethod_lower_abc|InputMethod_caps_abc);
    unsigned char trace_num[7] = {0};

    ///< 判断一下是否有交易流水
    if (DataTransDetail.transCount <= 0) {
        return ERR_TRANS_EMPTY;
    }

    while(1)
    {
        memset(trace_num, 0, sizeof(trace_num));
        mmi_clearLine(DISP_ClearALL);
        if (pTitle) {
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        }
        mmi_display(DISP_Line2, DISP_Left, AMSG_InputOriginalSerialNo);
        if (isLastEnable) {
            mmi_display(DISP_Line5, DISP_Left, AMSG_PreviousRecord);
        }
        mmi_displayOfBlackBg(DISP_Bottom2, DISP_Left, AMSG_ChangeIM);
        iRet = mmi_inputString(DISP_Line3, inputType, trace_num, isLastEnable ? 0 : 1, 6, NULL, 60);
        if (SUCCESS == iRet) {
            memset(pTransData, 0, sizeof(tsTransData));

            if (isLastEnable && !strlen((char *)trace_num)) {
                index = DataTransDetail.lastTransIndex;
                iRet = UFile_ReadRecordIndexOf(DB_TransTable, index);
            }
            else {
                iRet = transUtil_SearchTrans(pTransData, trace_num, &index);
            }

            if (isReInput && ERR_TRANS_NOFIND == iRet) {
                transErr_DispErrMsg(0, ERR_TRANS_NOFIND);
                continue;
            }
        }
        if (SUCCESS == iRet) {
            if (pTransIndex) {
                *pTransIndex = index;
            }
            else {
                pTransData->isVoid = DataTransDetail.transIndex[index] & TRANS_VOIDSTATE;
            }
        }
        return iRet;
    }
}

/**
 * @brief  查询流水
 * @brief  search trans
 */
int transUI_SearchTrans(const char *pTitle, unsigned int *pTransIndex)
{
    int iRet = SUCCESS;
    tsTransData mNormalTrans, *pCurrTransData = &DataTrans;

    if (!pCurrTransData) {
        return ERR_PARAM;
    }

    memset(&mNormalTrans, 0, sizeof(tsTransData));
    memcpy(&mNormalTrans, pCurrTransData, sizeof(tsTransData));
    memset(pCurrTransData, 0, sizeof(tsTransData));

    iRet = transUI_SearchTransEx(pTitle, "\x00\x01", pTransIndex, pCurrTransData);
    if (SUCCESS == iRet) {
        if (InputMode_Scan == pCurrTransData->cardInputType) {
            iRet = ERR_TRANS_NOVOID;
        }
        else if (TRANS_VOID_SALE == mNormalTrans.transType && TRANS_SALE != pCurrTransData->transType) {
            iRet = ERR_TRANS_NOVOID;
        }
    }

    if (SUCCESS == iRet) {
        if ((DataTransDetail.transIndex[*pTransIndex]&TRANS_VOIDSTATE)) {
            iRet = ERR_TRANS_NOVOID;
        }
    }

    if (SUCCESS == iRet) {
        ///< check old trans type
        memcpy(mNormalTrans.batchNumber, pCurrTransData->batchNumber, sizeof(mNormalTrans.batchNumber));
        memcpy(mNormalTrans.oldtraceNumber, pCurrTransData->traceNumber, sizeof(mNormalTrans.traceNumber));
        memcpy(mNormalTrans.oldRefNumber, pCurrTransData->refNumber, sizeof(mNormalTrans.oldRefNumber));
        memcpy(mNormalTrans.oldAuthCode, pCurrTransData->authCode, 6);
        memcpy(mNormalTrans.oldDate, &pCurrTransData->date[4], 4);

        mNormalTrans.ulAmount = pCurrTransData->ulAmount;
        mNormalTrans.sourceAccLen = pCurrTransData->sourceAccLen;
        memcpy(mNormalTrans.sourceAcc, pCurrTransData->sourceAcc, sizeof(mNormalTrans.sourceAcc));
        memcpy(mNormalTrans.expiredDate, pCurrTransData->expiredDate, sizeof(mNormalTrans.expiredDate));
        memcpy(mNormalTrans.authCode, pCurrTransData->authCode, sizeof(mNormalTrans.authCode));
        mNormalTrans.cardInputType = InputMode_Manual;
        mNormalTrans.cardType = pCurrTransData->cardType;
        iRet = transUI_DisplayTradeInfo(1, pCurrTransData);
    }

    memset(pCurrTransData, 0, sizeof(tsTransData));
    memcpy(pCurrTransData, &mNormalTrans, sizeof(tsTransData));
    return iRet;
}

/**
 * @brief  display balance
 */
void transUI_DisplayBalance(void)
{
    unsigned char offset = 7;

    ///< display balance
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line3, DISP_HCenter, AMSG_QuerySuccess);
    mmi_display(DISP_Line4, DISP_HCenter, AMSG_Balance);
    mmi_display(DISP_Line5, DISP_HCenter, "%s%lu.%02ld",
                (ExtraData.balanceInfo[offset] != 'C') ? "-" : " ",
                tools_asc_long(&ExtraData.balanceInfo[offset+1], 10),
                tools_asc_long(&ExtraData.balanceInfo[offset+11], 2));
    mmi_inputWaitKeypress(5);
}

/**
 * @brief scan code
 */
int transUI_ScanCode(const char *caption1, const char *caption2, const unsigned char *speakValue, unsigned char *plOut, int flag)
{
    int iRet = ERR_CANCEL;
    int iKey = KEY_NONE;
    int real_len = 0;
    unsigned char bar_buff[256] = {0};
    T_SOFTTIMER tm;
    unsigned int inputType = 0;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (NULL != caption1) {
        mmi_display(DISP_Line3, DISP_HCenter, caption1);
    }
    if (NULL != caption2) {
        mmi_display(DISP_Line4, DISP_HCenter, caption2);
    }
    ///< 是否支持手输
    if (flag) {
        mmi_display(DISP_Line6, DISP_HCenter, AMSG_ClearManualInput);
    }
    ///< 是否语音提示
    if (NULL != speakValue) {
        TTS_PlayText_OEM(speakValue, strlen((char *)speakValue));
    }

    ///< open scan dev
    iRet = ScanBarStart();
    
    if (SUCCESS == iRet) {
        ///< 打开扫码补偿灯
        ScanBarLightSet(SCANBAR_RLED | SCANBAR_WLED, 1);
        ///< 设置超时时间
        s_TimerSet(&tm, 60*1000);
        KbFlush();
        
        do {
            ///< 获取扫码数据:>0成功，=0超时，<0出错
            iRet = ScanBarGetData(bar_buff, sizeof(bar_buff), 500);
            if (iRet > 0) {                
                TTS_Abort_OEM();                    ///< 中断语音播报
                AudioDtmfAbort_OEM();
                AudioDtmfPlay_OEM(DTMF_Nine, 1);    ///< 播放扫码完成提示音
                real_len = iRet;
                strncpy((char *)plOut, (const char *)bar_buff, real_len);
                iRet = SUCCESS;
                Sleep(120);
                break;
            }
            ///< 扫码出错
            else if (iRet < 0) {
                iRet = ERR_SCAN_DRV;
                break;
            }

            if (KbHit()) {
                Sleep(20);
                continue;
            }

            iKey = mmi_inputGetKeypress();
            if (KEY_NONE == iKey) {
                continue;
            }

            if (KEY_CANCEL == iKey) {
                iRet = ERR_CANCEL;
                break;
            } else if (KEY_CLEAR == iKey) {
                ///< 关闭补偿灯//关闭扫码设备
                ScanBarLightSet(SCANBAR_WLED | SCANBAR_RLED, 0);
                ScanBarPause();
                ///< 手输
                inputType = mmi_setInputType(InputMethod_digital,
                                             InputMethod_digital);
                return transUI_Input(AMSG_InputVoucherNo, inputType, plOut, 1, 20);
            }
        } while (s_TimerCheck(&tm));

        if (!s_TimerCheck(&tm)) {
            iRet = ERR_TIMEOUT;
        }

        ///< 关闭补偿灯//关闭扫码设备
        ScanBarLightSet(SCANBAR_WLED | SCANBAR_RLED, 0);
        ScanBarPause();
    }
    else {
        iRet = ERR_SCAN_DRV;
    }
    return iRet;
}

/**
 * @brief  input card pin
 */
int transUI_InputCardPIN(void)
{
    extern bool G_InputPIN;
    extern int EMV_InputOnlinePIN(const char *panData, unsigned char *pinBlock, unsigned short *pPinBlockBuffSize);
    char cardPan[21] = {0};
    unsigned char pinBlock[30] = {0};
    unsigned short pinBlockBuffSize = 0;

    G_InputPIN = false;
    tools_bcd_asc((unsigned char *)cardPan, DataTrans.sourceAcc,
                  DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));

    cardPan[DataTrans.sourceAccLen] = 0x00;
    pinBlockBuffSize = sizeof(pinBlock);
    return EMV_InputOnlinePIN(cardPan, pinBlock, &pinBlockBuffSize);
}

/**
 * @brief  input amount
 */
int transUI_inputAmount(const char* caption, unsigned long mixAmount, unsigned long maxAmount, unsigned long *amount)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, DISP_Left, caption);
    mmi_display(DISP_Line5, DISP_Left, AMSG_InputErrClearKey);
    return mmi_InputAmount(DISP_Line3, 0, 0, amount, mixAmount, maxAmount, 60);
}

/**
 * @brief  input date
 */
int transUI_inputDate(const char* caption, unsigned char *date)
{
    tsSysTime loc_time = {0};
    int iRet = ERR_CANCEL;
    int iKey = KEY_NONE;
    long month = 0;
    long day = 0;
    long year = 0;

FLAG:
    iRet = transUI_Input(caption, InputMethod_digital, date, 4, 4);
    if (SUCCESS != iRet) {
        return iRet;
    }

    ///< 转换日期格式
    month = tools_asc_long(date, 2);
    day = tools_asc_long(date+2, 2);
    GetSysLocalTime(&loc_time);
    year = loc_time.year;   ///< 取当前年份
    
#if DEBUG_TRANS_UI
    LOGD("[%s %d]year %d month=%d day=%d\n", __func__, __LINE__, year, month, day);
#endif

    ///< 校验月份合法性
    if ((month < 1) || (month > 12)) {
        goto INPUTFLAG;
    }
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if ((day < 1) || (day > 31)) {
                goto INPUTFLAG;
            }
            break;
            
        case 4:
        case 6:
        case 9:
        case 11:
            if ((day < 1) || (day > 30)) {
                goto INPUTFLAG;
            }
            break;
            
        case 2:
            ///< 闰年
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
                if ((day < 1) || (day > 29)) {
                    goto INPUTFLAG;
                }
            } else {
                if ((day < 1) || (day > 28)) {
                    goto INPUTFLAG;
                }
            }
            break;
    }

    return iRet;

INPUTFLAG:
    {
        mmi_clearLine(DISP_Line3);
        mmi_display(DISP_Line3, DISP_Left, AMSG_InvalidDateFormat);
        memset(date, 0, 4);
        iKey = mmi_inputWaitKeypress(3);   ///< wait the key event
        if (KEY_CANCEL == iKey) {
            return ERR_CANCEL;
        }
        goto FLAG;
    }
}

/**
 * @brief  input expiredDate
 */
int transUI_inputExpiredDate(const char* caption, unsigned char *expiredDate)
{
    int iRet = ERR_CANCEL;
    int iKey = KEY_NONE;
    long month = 0, year = 0;

FLAG:
    iRet = transUI_Input(caption, InputMethod_digital, expiredDate, 4, 4);
    if (SUCCESS == iRet) {
        year = tools_asc_long(expiredDate, 2);
        month = tools_asc_long(expiredDate+2, 2);

#if DEBUG_TRANS_UI
        LOGE("[%s %d]month=%d year=%d\n", __func__, __LINE__, month, year);
#endif

        if (!((year > -1 && year < 100) && (month > 0 && month < 13))) {
            mmi_clearLine(DISP_Line3);
            mmi_display(DISP_Line3, DISP_Left, AMSG_InvalidDateFormat);
            memset(expiredDate, 0, 4);
            iKey = mmi_inputWaitKeypress(3);   ///< wait the key event
            if (KEY_CANCEL == iKey) {
                return ERR_CANCEL;
            }
            goto FLAG;
        }
    }
    return iRet;
}

/**
 * @brief  input Reference Number
 */
int transUI_inputRefNo(const char* caption, unsigned char *refNo)
{
    return transUI_Input(caption, InputMethod_digital, refNo, 12, 12);
}

/**
 * @brief  confirm amount
 */
int transUI_confirmAmount(const char* caption, unsigned long ulAmount)
{
    int iRet = ERR_CANCEL;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (NULL != caption) {
        mmi_display(DISP_Line2, DISP_HCenter, caption);
    } else {
        mmi_display(DISP_Line2, DISP_HCenter, AMSG_ConfirmAmount);
    }
    mmi_display(DISP_Line3, DISP_HCenter, "%ld.%02ld", ulAmount/100, ulAmount%100);
    mmi_display(DISP_Line5, DISP_HCenter, AMSG_CancelEdit);

    while (1) {
        iRet = mmi_inputWaitKeypress(60);
        if (KEY_NONE == iRet) {
            iRet = ERR_TIMEOUT;
            break;
        } else if (KEY_CANCEL == iRet) {
            iRet = ERR_CANCEL;
            break;
        } else if (KEY_ENTER == iRet) {
            iRet = SUCCESS;
            break;
        }
    }
    return iRet;
}

/**
 * @brief  根据付款凭证号查询流水
 * @brief  search trans by scan voucher no.
 */
int transUI_SearchScanTrans(unsigned int *pTransIndex)
{
    int iRet = SUCCESS;
    tsTransData mNormalTrans, *pCurrTransData = &DataTrans;
    unsigned char scanCode[256] = {0};

    if (!pCurrTransData) {
        return ERR_PARAM;
    }
    else if (!DataTransDetail.transCount) {
        return ERR_TRANS_EMPTY;
    }

    ///< 扫描或手输付款凭证号
    iRet = transUI_ScanCode(AMSG_ScanVoucherNo, NULL, NULL, scanCode, 1);
    if (SUCCESS != iRet) {
        return iRet;
    }

    ///< 备份交易数据
    memset(&mNormalTrans, 0, sizeof(tsTransData));
    memcpy(&mNormalTrans, pCurrTransData, sizeof(tsTransData));
    memset(pCurrTransData, 0, sizeof(tsTransData));

    ///< 查找交易记录
    iRet = transUtil_SearchScanTrans(pCurrTransData, scanCode, pTransIndex);
    if (SUCCESS == iRet) {
        ///< check old trans type
        if ((TRANS_VOID_SALE == mNormalTrans.transType)
            && (TRANS_SALE == pCurrTransData->transType)
            && !(DataTransDetail.transIndex[*pTransIndex]&TRANS_VOIDSTATE)) {
            memcpy(mNormalTrans.batchNumber, pCurrTransData->batchNumber, sizeof(mNormalTrans.batchNumber));
            memcpy(mNormalTrans.oldtraceNumber, pCurrTransData->traceNumber, sizeof(mNormalTrans.traceNumber));
            memcpy(mNormalTrans.oldRefNumber, pCurrTransData->refNumber, sizeof(mNormalTrans.oldRefNumber));

            mNormalTrans.ulAmount = pCurrTransData->ulAmount;
            mNormalTrans.sourceAccLen = pCurrTransData->sourceAccLen;
            memcpy(mNormalTrans.sourceAcc, pCurrTransData->sourceAcc, sizeof(mNormalTrans.sourceAcc));
            memcpy(mNormalTrans.expiredDate, pCurrTransData->expiredDate, sizeof(mNormalTrans.expiredDate));
            memcpy(mNormalTrans.authCode, pCurrTransData->authCode, sizeof(mNormalTrans.authCode));
            mNormalTrans.cardInputType = InputMode_Scan;
            mNormalTrans.cardType = pCurrTransData->cardType;

            memcpy(mNormalTrans.ScanCodeC2B, pCurrTransData->ScanCodeC2B, sizeof(mNormalTrans.ScanCodeC2B));
            memcpy(mNormalTrans.ascScanVoucherNo, pCurrTransData->ascScanVoucherNo, sizeof(mNormalTrans.ascScanVoucherNo));

            iRet = transUI_DisplayTradeInfo(1, pCurrTransData);
        }
        else
        {
            iRet = ERR_TRANS_NOVOID;
        }
    }
    memset(pCurrTransData, 0, sizeof(tsTransData));
    memcpy(pCurrTransData, &mNormalTrans, sizeof(tsTransData));

    return iRet;
}

