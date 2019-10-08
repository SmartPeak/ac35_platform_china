/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     emv_cl_callback                                                 *
*  @brief    QPBOC processing                                                *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "EmvTag.h"
#include "Kernel_Main.h"
#include "EmvKernel.h"
#include "Emv_Callback.h"
#include "Emv_CL_Callback.h"

#include "emv_ct_storage.h"
#include "Emv_Trans.h"

#include "trans.h"

#define DEBUG_EMV_CL_CALLBACK       0
#if DEBUG_EMV_CL_CALLBACK
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_CL_Callback.c"
#endif

extern int EMV_Get_TransType(void);
KERNEL_MODE_TYPE m_KernelMode;

///< APDU
int Kernel_CL_ExchangeApdu(const unsigned char *pApdu,
                           unsigned short uiApdu,
                           unsigned char *pResponse,
                           unsigned short *uiResponse,
                           unsigned char *pSW)
{
    int ierror = 0;

    if (uiApdu < 4) {
        return EMV_FALSE;
    }

    ierror = PiccApduExchange(pApdu, (unsigned int)uiApdu, pResponse, pSW);
#if DEBUG_EMV_CL_CALLBACK
    LOGD(">>>PiccApduExchange(): %d", ierror);
#endif
    if (0 < ierror)
    {
        *uiResponse = ierror;
#if IS_LOG
        {
            char SendBuff[266] = { 0 };
            unsigned int uiSendBuff = 255;
            char RespBuff[266] = { 0 };
            unsigned int uiRespBuff = 255;

            BytesToHexString((const char *)pApdu, (unsigned int)uiApdu, SendBuff, &uiSendBuff);
            LOGD("APDU T [ %s ]", SendBuff);

            BytesToHexString((const char *)pResponse, (unsigned int)*uiResponse, RespBuff, &uiRespBuff);
            LOGD("APDU C [ %s ]", RespBuff);
        }
#endif
        return EMV_TRUE;
    }
    return EMV_FALSE;
}

///< 显示交易结果
void Kernel_CL_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
    LOGD("[%5d]%d>>>", __LINE__, uiErrorCode);
    LOGD("[%5d]%d>>>", __LINE__, bSignatureNeeded);
#endif

    switch(uiErrorCode)
    {
    case EMV_APPROVED_OFFLINE:  ///< 脱机接受
        transUtil_LED_TransFinish();
        iRet = SUCCESS;
        break;
    case EMV_APPROVED_ONLINE:   ///< 联机接受
        transUtil_LED_TransFinish();
        EMV_GetICCardInfo();
        iRet = SUCCESS;
        break;
    default:
        if (SUCCESS == iRet) {
            iRet = EMVErr_SetCLErrCode(uiErrorCode);
        }
        break;
    }
    _TRANS_HANDLE.ret = iRet;
}

///< 联机处理(接触,非接VISA,QPBOC,AMEX,D-PAS)
void Kernel_CL_FinacialTransactionRequest(const char *pszOnlineEncipherPIN,
                                          unsigned char *pOnlineResult,
                                          char *pszIssueAuthData,
                                          unsigned short uiIssueAuthDataBuffSize,
                                          char *pszAC,
                                          unsigned short uiACBuffSize,
                                          char *pszAuthCode,
                                          unsigned short uiAuthCode,
                                          char *pszIssueScript,
                                          unsigned short uiScriptBuffSize)
{
    int iRet = Kernel_GetResult();
    unsigned char m_IssuerAuthData[101] = { 0 };    // ARPC
//    unsigned char m_IssueScript[1024] = { 0 };      // 发卡行脚本数据

    _TRANS_HANDLE.ARPC = m_IssuerAuthData;
//    _TRANS_HANDLE.pScriptData = m_IssueScript;

#if DEBUG_EMV_CL_CALLBACK
    LOGD("%s[%d]", __func__, __LINE__);
#endif
    if (SUCCESS == iRet) {
        iRet = EMV_TransOnline();
    }

    *pOnlineResult = EMV_ONLINE_CONNECT_FAILED;
    if (SUCCESS == iRet) {   // suc
        ///< bit55 tag 91
        if (_TRANS_HANDLE.ARPC && _TRANS_HANDLE.ARPCLen > 0 && uiIssueAuthDataBuffSize > _TRANS_HANDLE.ARPCLen) {
            vOneTwo(_TRANS_HANDLE.ARPC, _TRANS_HANDLE.ARPCLen, (unsigned char*)pszIssueAuthData);
        }

#if 0
        ///< bit55 tag 89
        if (strlen(bIssuerAuthCode)>0 && uiAuthCode >strlen(bIssuerAuthCode))
        {
            sprintf(pszAuthCode, "%s", "00");
            sprintf(pszAuthCode, "3030");
        }
#endif

        ///< bit 55 tag 71/72
        if (_TRANS_HANDLE.pScriptData && _TRANS_HANDLE.scriptDataLen > 0 && uiScriptBuffSize > _TRANS_HANDLE.scriptDataLen) {

            vOneTwo(_TRANS_HANDLE.pScriptData, _TRANS_HANDLE.scriptDataLen, (unsigned char *)pszIssueScript);
        }

        ///< bit39
        if (pszAC && _TRANS_HANDLE.getErrCode) {
            _TRANS_HANDLE.getErrCode(iRet, pszAC);

            if (strcmp(pszAC, "3030") == 0) {
                *pOnlineResult = EMV_ONLINE_APPROVED;
            }
            else if ((strcmp(pszAC, "3035") == 0)
                  || (strcmp(pszAC, "3531") == 0)) {
                *pOnlineResult = EMV_ONLINE_REJECT;
            }
            else if (strcmp(pszAC, "3031") == 0) {
                *pOnlineResult = EMV_ONLINE_VOICE_PREFER;
            }
        }
    }

#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s>>>iRet:%d", __LINE__, __func__, iRet);
#endif

    _TRANS_HANDLE.ret = iRet;
}

///< 多卡检查 . 判断当前是否在执行非接卡交易
unsigned char Kernel_CL_DetectBreak_Callback(void)
{
#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif

#if DEBUG_EMV_CL_CALLBACK
    LOGD("SysGetCurrentDev:%d", SysGetCurrentDev());
#endif
#if defined(P90)
    switch (SysGetCurrentDev())
    {
    case 0x50:
//        LOGD("TAG_INSERTED_ICCARD");
        return QVSDC_BS_CONTACT;
    case 0x51:
//        LOGD("TAG_SWIPED_MAGCARD");
        return QVSDC_BS_SWIPE;
    case 0x00:
//        LOGD("TAG_INSERTED_PICC");
        return QVSDC_BS_NONE;
    default:
        break;
    }
#endif
    return QVSDC_BS_NONE;
}

///< 移卡
void Kernel_CL_AskRemoveCard(void)
{
#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    //卡片下电 .
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_VCenter, DISP_HCenter, "请移卡");
    PiccRemove('E', 0);
    SpSysBeepOn(1000, 500);
}

///< 联机PIN
char Kernel_CL_GetOnlinePin(unsigned char bAllowBypass,
                            const char * pszPAN,
                            char * pszPinBlock,
                            unsigned short uiPinBlockBuffSize,
                            unsigned char *pbBypass)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (_TRANS_HANDLE.bEmvInputPINBypass) {
        *pbBypass = 2;
        goto END;
    }

    if (SUCCESS == iRet) {
        iRet = EMV_InputOnlinePIN(pszPAN, (unsigned char *)pszPinBlock, &uiPinBlockBuffSize);
        if (SUCCESS == iRet && pbBypass) {
            *pbBypass = EMV_TRUE;
            if (!uiPinBlockBuffSize) {
                *pbBypass = 2; // 非接卡 联机PIN 都移到 卡片通讯完成后在执行.
            }
        }
    }

END:
    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< 二次拍卡
char Kernel_CL_SecondTapCard(void)
{
#if DEBUG_EMV_CL_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    return EMV_FALSE;
}

