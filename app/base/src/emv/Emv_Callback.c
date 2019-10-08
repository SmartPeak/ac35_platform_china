#include "bwsdk_api.h"
#include "applib_tools.h"
#include "EmvKernel.h"
#include "Emv_Callback.h"
#include "Emv_CL_Callback.h"
#include "Emv_CT_Callback.h"

#include "Emv_Param.h"
#include "Emv_Trans.h"
#include "trans_err.h"

#define DEBUG_EMV_CALLBACK      0
#if DEBUG_EMV_CALLBACK
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_Callback.c"
#endif

TRANS_HANDLE _TRANS_HANDLE;

///< 内核日志打印
void Kernel_Log_Printf(const char *pszMessage, unsigned int len)
{
    if (EMV_Get_AbleLog() == EMV_TRUE) {
#if DEBUG_EMV_CALLBACK
        Sleep(100);
        LOGD(pszMessage);
#endif
    }
}

///< 获取终端时间
void Kernel_GetCurrentTime(LP_EMV_TIME pCurrentTime)
{
    tsSysTime pTime;

    memset(&pTime, 0, sizeof(tsSysTime));
    if (!GetSysLocalTime(&pTime)) {
        pCurrentTime->m_Year = pTime.year;
        pCurrentTime->m_Month = pTime.mon;
        pCurrentTime->m_Day = pTime.day;
        pCurrentTime->m_Hour = pTime.hour;
        pCurrentTime->m_Minute = pTime.min;
        pCurrentTime->m_Second = pTime.sec;
        return;
    }

    pCurrentTime->m_Year = 2019;
    pCurrentTime->m_Month = 1;
    pCurrentTime->m_Day = 1;
    pCurrentTime->m_Hour = 0;
    pCurrentTime->m_Minute = 0;
    pCurrentTime->m_Second = 0;
}

///< 获取随机数
void Kernel_GetRandomData(unsigned char* pRandBuff, unsigned short uiSize)
{
    if (!pRandBuff) {
        return;
    }

    if (PedGetRandomRev(pRandBuff, uiSize) < 0) {
        memset(pRandBuff, 0, uiSize);
    }
}

///< SM2加密
/*
*验证国密证书是否成立
*pSMPubKey:国密公钥(64byte)
*bVerifyData:要验证的数据
*uiVerifyData:要验证的数据长
*bSignature:签名值
*uiSignature:签名长(64byte)
*/
char Kernel_SM2VerifySign(unsigned char* pSMPubKey, unsigned char* bVerifyData, int uiVerifyData, unsigned char* bSignature, int uiSignature)
{
    int iRet = SUCCESS;
    int uiDgt = 0;
    unsigned char xA_asc[64 + 1] = { 0 };
    unsigned char yA_asc[64 + 1] = { 0 };
    unsigned char buff[64] = { 0 };

#if DEBUG_EMV_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        vOneTwo(pSMPubKey, 32, xA_asc);
        vOneTwo(pSMPubKey + 32,32, yA_asc);
        uiDgt = SM2_DigestRev((char *)xA_asc, (char *)yA_asc, "1234567812345678", 16, bVerifyData, uiVerifyData, buff);
        if (uiDgt < 0) {
            iRet = ERR_SM2_SIGN;
        }
    }

    if (SUCCESS == iRet) {
        uiDgt = SM2_VerifyRev(buff, uiDgt, bSignature, uiSignature, (char *)xA_asc, (char *)yA_asc);
        if (uiDgt != 0) {
            iRet = ERR_SM2_SIGN;
        }
    }

    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< SM3哈希加密
/*
pVerifyData:要计算hash的数据
uiVerifyData:
pSM3Hash:计算后的hash值
uiSM3Hash:hash长度
*/
char Kernel_SM3Hash(unsigned char* pVerifySM3, int uiVerifySM3, unsigned char* pSM3Hash, int *uiSM3Hash)
{
    int iRet = SUCCESS;
    int uiHash = 0;
    unsigned char bHashBuff[32 + 1] = { 0 };

#if DEBUG_EMV_CALLBACK
    LOGD("[%5d]%s", __LINE__, __func__);
#endif
    if (SUCCESS == iRet) {
        uiHash = SM3Rev(pVerifySM3, uiVerifySM3, bHashBuff);
        if (uiHash < 0 || uiHash != 0x20)
        {
            *uiSM3Hash = 0;
            iRet = ERR_SM2_SIGN;
        }
    }

    if (SUCCESS == iRet) {
        memcpy(pSM3Hash, bHashBuff, uiHash);
        *uiSM3Hash = uiHash;
    }

    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< APDU 通讯
char Kernel_ExchangeApdu(const unsigned char *pApdu, unsigned short uiApdu, unsigned char *pResp, unsigned short *uiResp)
{
    char bRetval = EMV_TRUE;

    if (_TRANS_HANDLE.drvMode == DEVPICC)
    {
        unsigned char SW[2] = { 0 };
        int len = 0;

        if (*uiResp < 2) {
            bRetval = EMV_FALSE;
        }
        else
        {
            *uiResp -= 2;
            bRetval = Kernel_CL_ExchangeApdu(pApdu, uiApdu, pResp, uiResp, SW);
            if (EMV_TRUE == bRetval)
            {
                len = *uiResp;
                memcpy(pResp + len, SW, 2);
                len += 2;
                *uiResp = len;
            }
        }
    }
    else
    {
        bRetval = Kernel_CT_ExchangeApdu(pApdu, uiApdu, pResp, uiResp);
    }
    return bRetval;
}

///< 交易结果 Mastrt,MIR 联机,脱机处理 按照返回值处理
void Kernel_Display_Trans_Report(int uiErrorCode, unsigned char bSignatureNeeded)
{
    if (_TRANS_HANDLE.drvMode == DEVPICC)
    {
        Kernel_CL_Display_Trans_Report(uiErrorCode, bSignatureNeeded);
    }
    else
    {
        Kernel_CT_Display_Trans_Report(uiErrorCode, bSignatureNeeded);
    }
}

///< 联机处理(接触,非接VISA,QPBOC,AMEX,D-PAS)
void Kernel_FinacialTransactionRequest(const char *pszOnlineEncipherPIN,
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
#if defined(P90)
    if (_TRANS_HANDLE.drvMode == DEVICC)
    {
        Kernel_CT_FinacialTransactionRequest(pszOnlineEncipherPIN,
                                             pOnlineResult,
                                             pszIssueAuthData,
                                             uiIssueAuthDataBuffSize,
                                             pszAC,
                                             uiACBuffSize,
                                             pszAuthCode,
                                             uiAuthCode,
                                             pszIssueScript,
                                             uiScriptBuffSize);
        return;
    }
#endif
    Kernel_CL_FinacialTransactionRequest(pszOnlineEncipherPIN,
                                         pOnlineResult,
                                         pszIssueAuthData,
                                         uiIssueAuthDataBuffSize,
                                         pszAC,
                                         uiACBuffSize,
                                         pszAuthCode,
                                         uiAuthCode,
                                         pszIssueScript,
                                         uiScriptBuffSize);
    return;
}

///< 金额输入
char Kernel_EnterAmount(unsigned int *pAmount, unsigned int *pAmountOther)
{
    int iRet = SUCCESS;

    if (SUCCESS == iRet) {
        iRet = EMV_InputAmount(pAmount);
    }

    _TRANS_HANDLE.ret = iRet;
    if (iRet != SUCCESS) {
        return EMV_FALSE;
    }
    return EMV_TRUE;
}

///< 指示当前是ic、picc或磁条
void Kernel_CL_KernelMode(unsigned int uiKernelMode)
{
    switch (uiKernelMode)
    {
    case 1:
        m_KernelMode = KERNEL_QUICS;
        break;
    case 2:
        m_KernelMode = KERNEL_VISA;
        break;
    case 3:
        m_KernelMode = KERNEL_MASTERCARD;
        break;
    case 4:
        m_KernelMode = KERNEL_DISCOVER;
        break;
    case 5:
        m_KernelMode = KERNEL_EXPRESS;
        break;
    case 7:
        m_KernelMode = KERNEL_MIR;
        break;
    default:
        m_KernelMode = KERNEL_NOT;
        break;
    }
}

