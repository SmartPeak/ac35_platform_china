/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     emv_ct_callback                                                 *
*  @brief    PBOC processing                                                *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "applib_def.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "EmvCtKernelL2.h"
#include "EmvKernel.h"
#include "EmvTag.h"
#include "Emv_Callback.h"
#include "Emv_CT_Callback.h"
#include "Emv_Trans.h"

#include "Pos_Menu.h"
#include "trans_err.h"

#define DEBUG_EMV_CT_CALLBACK           0
#if DEBUG_EMV_CT_CALLBACK
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_CT_Callback.c"
#endif

///< APDU
int Kernel_CT_ExchangeApdu(const unsigned char* pApdu,
                           unsigned short uiApdu,
                           unsigned char* pResponse,
                           unsigned short* uiResponse)
{
    unsigned char SW[2] = { 0 };
    int uiRespApud = 0;

    if (uiApdu < 4){
        return EMV_FALSE;
    }

    uiRespApud = IccApduTransmitExt(pApdu, (unsigned int)uiApdu, pResponse, SW, 8*1000);
    if (uiRespApud >= 0) {
        if (*uiResponse >= uiRespApud+2) { //判断buff是否足量
            memcpy(pResponse+uiRespApud, SW, 2);// 有sw返回时,认为成功
            *uiResponse = uiRespApud + 2;
            return EMV_TRUE;
        }
    }

    *uiResponse = 0;
    return EMV_FALSE;
}

/*多应用选择*/
char Kernel_CT_SelectApplication(const char **ppAppNames, const char **ppAppAids, unsigned short uiAppCount, unsigned short *puiSelected)
{
    int uiRetal = EMV_FALSE;
    int iSelected = 0;

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
    for (int i = 0; i < uiAppCount; i++){
        LOGD("ppAppNames;%s", ppAppNames[i]);
        LOGD("ppAppAids;%s", ppAppAids[i]);
    }
#endif

    iSelected = Menu_Select("Multiple application options", uiAppCount, (char *)ppAppNames, iSelected, EMV_TRUE, NULL, NULL);
    if (iSelected >= 0)
    {
        *puiSelected = iSelected;
        uiRetal = EMV_TRUE;
    }

    EMV_DisplayProcessing();
    return uiRetal;
}

///< 显示主账号信息
char Kernel_CT_Display_PanNo(char *pPanNo)
{
    int iRet = Kernel_GetResult();

    if (SUCCESS == iRet) {
        iRet = EMV_DisplayPanNo((char *)pPanNo);
        EMV_DisplayProcessing();
    }

    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< 持卡人确认(暂时没用到)
char Kernel_CT_CardHolderConfirm(const char * pAID, const char * pAppName, const char * pPreferAppName)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_VCenter, DISP_HCenter,"持卡人确认");
    mmi_inputWaitKeypress(60);

    EMV_DisplayProcessing();
    return EMV_TRUE;
}

/*暂时没用到*/
void Kernel_CT_AfterAppSelected(void)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    return;
}

/*暂时没用到*/
char Kernel_CT_LanguageSelect(char * pszLanguages, char bIsPSESelect)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    return EMV_TRUE;
}

/*
*授权请求报文(批捕获)
*pszIssueAuthData:发卡行授权数据
*pszAC:响应码
pszAuthCode:授权响应码
*/
void Kernel_CT_AuthorisationRequest(const char * pszOnlineEncipherPIN,
                                    unsigned char * pOnlineResult,
                                    char *pszIssueAuthData,
                                    unsigned short uiIssueAuthDataBuffSize,
                                    char *pszAC,
                                    unsigned short uiACBuffSize,
                                    char *pszAuthCode,
                                    unsigned short uiAuthCode,
                                    char *pszIssueScript,
                                    unsigned short uiScriptBuffSize)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    return;
}

/*
*金融请求报文
*pszIssueAuthData:发卡行授权数据
*pszAC:响应码
pszAuthCode:授权响应码
*/
void Kernel_CT_FinacialTransactionRequest(const char* pszOnlineEncipherPIN,
                                          unsigned char* pOnlineResult,
                                          char* pszIssueAuthData,
                                          unsigned short uiIssueAuthDataBuffSize,
                                          char* pszAC,
                                          unsigned short uiACBuffSize,
                                          char* pszAuthCode,
                                          unsigned short uiAuthCode,
                                          char* pszIssueScript,
                                          unsigned short uiScriptBuffSize)
{
    int iRet = Kernel_GetResult();
    unsigned char m_IssuerAuthData[101] = { 0 };    // ARPC
    unsigned char m_IssueScript[1024] = { 0 };      // 发卡行脚本数据

    _TRANS_HANDLE.ARPC = m_IssuerAuthData;
    _TRANS_HANDLE.pScriptData = m_IssueScript;

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        iRet = EMV_TransOnline();
        EMV_DisplayProcessing();
    }

    *pOnlineResult = EMV_ONLINE_CONNECT_FAILED;
    if (SUCCESS == iRet){
        ///< bit55 tag 91
        if (_TRANS_HANDLE.ARPC && _TRANS_HANDLE.ARPCLen > 0 && uiIssueAuthDataBuffSize > _TRANS_HANDLE.ARPCLen)
        {
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

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s>>>iRet:%d", __LINE__, __func__, iRet);
#endif

    _TRANS_HANDLE.ret = iRet;
}

/*显示交易结果*/
void Kernel_CT_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s>>>iRet:%d", __LINE__, __func__, iRet);
    LOGD("[%5d]%d>>>", __LINE__, uiErrorCode);
    LOGD("[%5d]%d>>>", __LINE__, bSignatureNeeded);
#endif
    switch(uiErrorCode)
    {
    case 0:     ///< 联机批准
        EMV_GetICCardInfo();
        iRet = SUCCESS;
        break;
    case 5:     ///< 脱机批准
        iRet = SUCCESS;
        break;
    case EMV_ICC_USER_CANCEL:
        if (SUCCESS == iRet) {
            iRet = ERR_CANCEL;
        }
        break;
    default:
        if (SUCCESS == iRet) {
            iRet = EMVErr_SetCTErrCode(uiErrorCode);
        }
        break;
    }

    ///< save script result
    if (_TRANS_HANDLE.ScriptResultSave && _TRANS_HANDLE.scriptDataLen > 0) {
        _TRANS_HANDLE.ScriptResultSave();
    }

    _TRANS_HANDLE.ret = iRet;
}

///< 脱机明文pin
char Kernel_Contact_GetPlainTextPin(unsigned char bAllowBypass,
                                    char* pszPIN,
                                    unsigned short uiPinBuffSize,
                                    char bPinTryCnt,
                                    int *bVerifyPinTryCnt,
                                    LP_EMV_CV_VERIFY_RESULT pVerifyResult)
{
    int iRet = SUCCESS;

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        iRet = EMV_InputOffPlainPinPwd(bAllowBypass, bPinTryCnt, bVerifyPinTryCnt);
        EMV_DisplayProcessing();
    }

    if (SUCCESS == iRet) {
        *pVerifyResult = CV_VERIFY_SUC;
    }
    else if (ERR_PWD_NO_PASSWORD == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PASSWORD;
    }
    else if (ERR_CANCEL == iRet) {
        *pVerifyResult = CV_VERIFY_USER_CANCEL;
    }
    else if (ERR_TIMEOUT == iRet) {
        *pVerifyResult = CV_VERIFY_TIME_OUT;
    }
    else if (ERR_PWD_OTHER_ERR == iRet) {
        *pVerifyResult = CV_VERIFY_RSP_ERR;
    }
    else if (ERR_DRV == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PINPAD;
    }
    else if (ERR_PARAM == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PASSWORD;
    }
    else if (ERR_PWD_PIN_ERR == iRet) {
        *pVerifyResult = CV_VERIFY_PIN_ERROR;
    }
    else if (ERR_PWD_PIN_BLOCK == iRet) {
        *pVerifyResult = CV_VERIFY_PIN_BLOCK;
    }
    else {
        *pVerifyResult = CV_VERIFY_USER_CANCEL;
    }

#if DEBUG_EMV_CT_CALLBACK
    LOGD("pVerifyResult:%d", *pVerifyResult);
#endif
    _TRANS_HANDLE.ret = iRet;
    if (SUCCESS != iRet) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< 脱机密文pin
char Kernel_Contact_GetOfflineCipherPin(unsigned char bAllowBypass,
                                        LP_PIN_OFF_CIPHER_ITEM pPinCipherItem,
                                        char bPinTryCnt,
                                        int *bVerifyPinTryCnt,
                                        char* pszPinBlock,
                                        unsigned short uiPinBlockBuffSize,
                                        LP_EMV_CV_VERIFY_RESULT pVerifyResult)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        iRet = EMV_InputOffCipherPinPwd(bAllowBypass, bPinTryCnt, bVerifyPinTryCnt, (unsigned char *)pVerifyResult);
        EMV_DisplayProcessing();
    }

    if (SUCCESS == iRet) {
        *pVerifyResult = CV_VERIFY_SUC;
    }
    else if (ERR_PWD_NO_PASSWORD == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PASSWORD;
    }
    else if (ERR_CANCEL == iRet) {
        *pVerifyResult = CV_VERIFY_USER_CANCEL;
    }
    else if (ERR_TIMEOUT == iRet) {
        *pVerifyResult = CV_VERIFY_TIME_OUT;
    }
    else if (ERR_PWD_OTHER_ERR == iRet) {
        *pVerifyResult = CV_VERIFY_RSP_ERR;
    }
    else if (ERR_DRV == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PINPAD;
    }
    else if (ERR_PARAM == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PASSWORD;
    }
    else if (ERR_PWD_PIN_ERR == iRet) {
        *pVerifyResult = CV_VERIFY_PIN_ERROR;
    }
    else if (ERR_PWD_PIN_BLOCK == iRet) {
        *pVerifyResult = CV_VERIFY_PIN_BLOCK;
    }
    else {
        *pVerifyResult = CV_VERIFY_USER_CANCEL;
    }

#if DEBUG_EMV_CT_CALLBACK
    LOGD("pVerifyResult:%d", *pVerifyResult);
#endif
    _TRANS_HANDLE.ret = iRet;
    if (SUCCESS != iRet) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< 联机加密pin
char Kernel_Contact_GetOnlinePin(unsigned char bAllowBypass,
                                 const char* pszPAN,
                                 char* pszPinBlock,
                                 unsigned short uiPinBlockBuffSize,
                                 LP_EMV_CV_VERIFY_RESULT pVerifyResult)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        if (_TRANS_HANDLE.bEmvInputPINBypass) {
            iRet = SUCCESS;
        }
        else {
            iRet = EMV_InputOnlinePIN(pszPAN, (unsigned char *)pszPinBlock, &uiPinBlockBuffSize);
            EMV_DisplayProcessing();
        }
    }

    if (SUCCESS == iRet) {
        *pVerifyResult = CV_VERIFY_SUC;
    }
    else if (ERR_CANCEL == iRet) {
        *pVerifyResult = CV_VERIFY_USER_CANCEL;
    }
    else if (ERR_TIMEOUT == iRet) {
        *pVerifyResult = CV_VERIFY_TIME_OUT;
    }
    else if (ERR_PWD_OTHER_ERR == iRet) {
        *pVerifyResult = CV_VERIFY_RSP_ERR;
    }
    else if (ERR_DRV == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PINPAD;
    }
    else if (ERR_PARAM == iRet) {
        *pVerifyResult = CV_VERIFY_NO_PASSWORD;
    }

#if DEBUG_EMV_CT_CALLBACK
    LOGD("pVerifyResult:%d", *pVerifyResult);
#endif
    _TRANS_HANDLE.ret = iRet;
    return EMV_TRUE;
}

// 持卡人证件验证
char Kernel_Contact_GetHolderCert(const char* pConfirmMsg,
                                  int uiConfirmMsg,
                                  const char * pHoldCert,
                                  int uiHoldCert)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
    LOGD("this Kernel_Contact_GetHolderCert");
    LOGD("pConfirmMsg:%s,uiConfirmMsg:%d", pConfirmMsg, uiConfirmMsg);
    LOGD("pHoldCert:%s,uiHoldCert:%d", pHoldCert, uiHoldCert);
#endif

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Top, DISP_HCenter, "Cardholder ID verification");
    mmi_display(DISP_Line2, 0, "%s", pConfirmMsg);
    mmi_display(DISP_Line4, 0, "%s", pHoldCert);
    while(1)
    {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_CANCEL:
        case KEY_NONE:
            return EMV_FALSE;
        case KEY_ENTER:
            return EMV_TRUE;
        default:
            break;
        }
    }
}

// 联机参考(卡号)
char Kernel_Contact_PanConfirm(const char* pPAN)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Top, DISP_HCenter, "请持卡人与发卡银行联系");
    mmi_display(DISP_Line3, DISP_Left, "%s", pPAN);
    mmi_display(DISP_Line5, DISP_Left,"%s","是");
    mmi_display(DISP_Line5, DISP_Right, "%s", "否");
    while(1)
    {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_CANCEL:
        case KEY_NONE:
            EMV_DisplayProcessing();
            return EMV_FALSE;
        case KEY_ENTER:
            EMV_DisplayProcessing();
            return EMV_TRUE;
        default:
            break;
        }
    }
}

char Kernel_Contact_SelAppErr(void)
{
#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Top, DISP_HCenter, "Multiple application options");
    mmi_display(DISP_Line2, 0, "%s", "Application selection failed, please re-select!");
    while(1)
    {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_CANCEL:
        case KEY_NONE:
            return EMV_FALSE;
        case KEY_ENTER:
            return EMV_TRUE;
        default:
            break;
        }
    }
}

/*磁条卡联机请求*/
char Kernel_MagStripe_OnlineRequeset(char* pOnlinePin, char* pResCode)
{
    int iRet = Kernel_GetResult();

#if DEBUG_EMV_CT_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif

    if (SUCCESS == iRet) {
        iRet = EMV_TransOnline();
        EMV_DisplayProcessing();
    }

    if (pResCode && _TRANS_HANDLE.getErrCode) {
        _TRANS_HANDLE.getErrCode(iRet, pResCode);
    }

    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

