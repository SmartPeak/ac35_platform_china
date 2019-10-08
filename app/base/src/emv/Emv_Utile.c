#include "bwsdk_api.h"
#include "logger.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "EmvKernel.h"
#include "Emv_Utile.h"
#include "secretKey.h"
#include "trans_err.h"

#ifdef TAG
#undef TAG
#endif
#define TAG "EMV_Util.c"

#define EMV_L2_DEFAULT_PIN_LIST_4   "\x00\x04\x06\x0C"
#define EMV_L2_DEFAULT_PIN_LIST_5   "\x00\x06\x08\x0C\x0C"
#define EMV_L2_DEFAULT_PIN_LIST_6   "\x00\x04\x06\x08\x0A\x0C"
#define EMV_L2_DEFAULT_PIN_LIST_8   "\x00\x04\x05\x06\x07\x08\x0A\x0C"
#define EMV_L2_DEFAULT_PIN_LIST_9   "\x00\x04\x05\x06\x07\x08\x09\x0A\x0C"
#define EMV_L2_DEFAULT_PIN_LIST_10  "\x00\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C"

/*
*以可识字符显示 "9f3303E0E9C8"
//idx=TlvAppendAscii(0x9f21, buf1, 0,buff,idx,3);
Tag:要封装的tag
srcData:原数据
srcOffset:原数据起始位置
dstData:目的数据
dstOffset:目的数据起始位置
srcLen:原数据长度
以tlv的格式封装数据到buff中,返回值为buff的当前索引
*/
int TlvAppendAscii(unsigned int Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen)
{
    int idx = 0;
    int tagLen = 0;
    unsigned char tmpTag[3] = { 0 }, tmpL[3] = { 0 };
    int lLen = 0, wangLen = 0;

    wangLen = srcLen / 2;
    idx = dstOffset;
    // t
    if (Tag > 0xffff)
    {
        tmpTag[tagLen + 2] = Tag & 0xff;
        Tag >>= 8;
        tmpTag[tagLen + 1] = Tag & 0xff;
        Tag >>= 8;
        tmpTag[tagLen] = Tag & 0xff;
        tagLen += 3;
    }
    else if (Tag > 0xff)
    {
        tmpTag[tagLen + 1] = Tag & 0xff;
        Tag >>= 8;
        tmpTag[tagLen] = Tag & 0xff;
        tagLen += 2;
    }
    else
    {
        tmpTag[tagLen++] = Tag & 0xff;
    }

    vOneTwo(tmpTag, tagLen, dstData + idx);
    idx += tagLen * 2;
    // l
    if (wangLen <= 0x7f)
    {
        tmpL[lLen++] = wangLen & 0xff;
    }
    else if (wangLen <= 0xff)
    {
        tmpL[lLen++] = 0x81;
        tmpL[lLen++] = wangLen & 0xff;
    }
    else
    {
        tmpL[lLen++] = 0x82;
        tmpL[lLen++] = wangLen / 256;
        tmpL[lLen++] = wangLen % 256;
    }
    vOneTwo(tmpL, lLen, dstData + idx);
    idx += lLen * 2;
    //	v
    memcpy(dstData + idx, srcData + srcOffset, srcLen);
    return idx + srcLen;
}

int TlvAppend(unsigned long Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen)
{
    int idx = 0;

    idx = dstOffset;
    // t
    if (Tag > 0xffff)
    { // 3字节
        dstData[idx + 2] = Tag & 0xff;
        Tag >>= 8;
        dstData[idx + 1] = Tag & 0xff;
        Tag >>= 8;
        dstData[idx] = Tag & 0xff;
        idx += 3;
    }
    else if (Tag > 0xff)
    {
        dstData[idx + 1] = Tag & 0xff;
        Tag >>= 8;
        dstData[idx] = Tag & 0xff;
        idx += 2;
    }
    else
    {
        dstData[idx++] = Tag & 0xff;
    }

    // l
    if (srcLen <= 0x7f)
    {
        dstData[idx++] = srcLen & 0xff;
    }
    else if (srcLen <= 0xff)
    {
        dstData[idx++] = 0x81;
        dstData[idx++] = srcLen & 0xff;
    }
    else
    {
        dstData[idx++] = 0x82;
        dstData[idx++] = srcLen / 256;
        dstData[idx++] = srcLen % 256;
    }
    //	v
    memcpy(dstData + idx, srcData + srcOffset, srcLen);
    return idx + srcLen;
}

int EMV_GetTagValueFromStr(unsigned char* aucTagStr,
                           unsigned int uiTagStrLen,
                           unsigned char* aucTag,
                           unsigned char* aucTagValue,
                           unsigned short* uiTagValueLen)
{
    int iRet = ERR_END;
    unsigned char *pTag, ucTagLen;

    pTag = aucTagStr;
    while(pTag < (aucTagStr+uiTagStrLen))
    {
        ucTagLen = ((*pTag & 0x1F) == 0x1F) ? 2 : 1;
        if(!memcmp(pTag, aucTag, ucTagLen))
        {
            *uiTagValueLen = *(pTag+ucTagLen);
            memcpy(aucTagValue, pTag+ucTagLen+1, *uiTagValueLen);
            iRet = SUCCESS;
            break;
        }
        else
        {
            pTag+=*(pTag+ucTagLen)+ucTagLen+1;
        }
    }
    return iRet;
}

/*联机pin回调*/
static int giPinEvent = PIN_EVENT_NONE;
static int giPinErr = SUCCESS;
static void EMV_UTIL_PinBlockEventCB(Pin_Block_Event event, Pin_Block_Data *data)
{
    if (-1 == data->iErrCode) {
        giPinErr = ERR_TIMEOUT;
    }
    giPinEvent = event;
}

/*脱机pin回调*/
static void EMV_UTIL_PlainEventCB(Pin_Block_Event event, Offline_Pin_Data *data)
{
    if (-1 == data->iErrCode) {
        giPinErr = ERR_TIMEOUT;
    }
    giPinEvent = event;
}

///< 联机PIN输入
int EMV_UTIL_InputOnlinePIN(unsigned int dispLine, unsigned int column, const char* panData, unsigned char *pinBlock, unsigned int *pinBlockSize, unsigned short timeout)
{
    int iRet = ERR_CANCEL;
    char dispBuff[20];
    unsigned char ucPinBlkLen;
    Pin_Block_Material_Type pPinMaterial = { 0 };
    Pin_Block_Data pOnlinePin = { 0 };

    if (!pinBlock || !pinBlockSize) {
        return ERR_PARAM;
    }

    ucPinBlkLen = *pinBlockSize;
    *pinBlockSize = 0;

    giPinErr = SUCCESS;
    giPinEvent = PIN_EVENT_NONE;
    pPinMaterial.KeyArch    = KEY_ARCH_MKSK;
    pPinMaterial.KeyIdx     = 0x06;
    pPinMaterial.Mode       = PINBLOCK_MODE_ISO9564_FMT0; // 计算pinblock的模式
    pPinMaterial.TimeoutMs = timeout*1000;
    pPinMaterial.TradeInfoLen = 0x00;
    ///< exp
    pPinMaterial.ListLen = 10;
    if (pPinMaterial.ListLen > sizeof(pPinMaterial.ExpPinLenList)) {
        return ERR_PARAM;
    }
    memcpy(pPinMaterial.ExpPinLenList, EMV_L2_DEFAULT_PIN_LIST_10, pPinMaterial.ListLen);
    ///< pan
    if (panData) {
        pPinMaterial.PanLen = strlen(panData);
        if (pPinMaterial.PanLen > sizeof(pPinMaterial.Pan)) {
            return ERR_PARAM;
        }
        memcpy(pPinMaterial.Pan, panData, pPinMaterial.PanLen);
    }

    memset(dispBuff, '*', sizeof(dispBuff));
    if (PedGetPinBlockRev(&pPinMaterial, EMV_UTIL_PinBlockEventCB, &pOnlinePin) != 0){
//        PIN输入次数超限，错误码是 -307， 对应的十六进制： FECD
        KbFlush();
        return ERR_DRV;
    }

    while (1)
    {
        if (!GetSysStatus()) {
            PedInputCancelRev();
            iRet = ERR_CANCEL;
            break;
        }

        switch (giPinEvent)
        {
        case PIN_EVENT_NONE:    ///< 无输入
            Sleep(50);
            continue;
        case PIN_EVENT_LEN:     ///< 有输入
            giPinEvent = PIN_EVENT_NONE;

            mmi_clearLine(dispLine);
            mmi_display((DISP_VAlign)dispLine, column, "%*.*s", 0, pOnlinePin.ucPinLen, dispBuff);
            continue;
        case PIN_EVENT_COMPLETE:///< 输入完成
            iRet = SUCCESS;
            break;
        case PIN_EVENT_PINFREE: ///< 直接按确定
            iRet = SUCCESS;
            break;
        case PIN_EVENT_INVALID:
            giPinEvent = PIN_EVENT_NONE;
            continue;
        case PIN_EVENT_EXIT:    ///< 取消
            iRet = ERR_CANCEL;
            break;
        case PIN_EVENT_ERR:
            iRet = ERR_PWD_OTHER_ERR;
            if (giPinErr != SUCCESS) {
                iRet = giPinErr;
            }
            break;
        default:
            iRet = ERR_TIMEOUT;
            break;
        }
        break;
    }

    if (SUCCESS == iRet) {
        if (pOnlinePin.ucPinBlkLen > ucPinBlkLen) {
            return ERR_PARAM;
        }

        if (PIN_EVENT_PINFREE != giPinEvent) {
            *pinBlockSize = pOnlinePin.ucPinBlkLen;
            memcpy(pinBlock, pOnlinePin.aucPinBlock, pOnlinePin.ucPinBlkLen);
        }
    }
    else {
        pOnlinePin.ucPinBlkLen = 0;
        memset(pOnlinePin.aucPinBlock, 0, sizeof(pOnlinePin.aucPinBlock));
    }
    KbFlush();
    return iRet;
}

///< 脱机明文PIN输入
int EMV_UTIL_InputOffPlainPinPwd(unsigned int dispLine, unsigned int column, char bPinByPass, int *bVerifyPinTryCnt, int timeout)
{
    int iRet = ERR_CANCEL;
    char dispBuff[20];
    Plain_Pin_Material_Type m_plainPinMater = { 0 };
    Offline_Pin_Data m_offPinData = { 0 };

    giPinErr = SUCCESS;
    giPinEvent = PIN_EVENT_NONE;
    m_plainPinMater.Slot = ICC_SLOT;
    m_plainPinMater.Mode = OFFLINE_MODE_DEF;
    m_plainPinMater.TimeoutMs = timeout*1000;
    m_plainPinMater.ListLen = 10;
    if (m_plainPinMater.ListLen > sizeof(m_plainPinMater.ExpPinLenList)) {
        return ERR_PARAM;
    }
    memcpy(m_plainPinMater.ExpPinLenList, EMV_L2_DEFAULT_PIN_LIST_10, m_plainPinMater.ListLen);

    memset(dispBuff, '*', sizeof(dispBuff));
    if (PedVerifyOfflinePlainRev(&m_plainPinMater, EMV_UTIL_PlainEventCB, &m_offPinData) != 0) {
//        PIN输入次数超限，错误码是 -307， 对应的十六进制： FECD
        KbFlush();
        return ERR_DRV;
    }

    while (1)
    {
        if (!GetSysStatus()) {
            PedInputCancelRev();
            iRet = ERR_CANCEL;
            break;
        }

        switch (giPinEvent)
        {
        case PIN_EVENT_NONE:    ///< 无输入
            Sleep(50);
            continue;
        case PIN_EVENT_LEN:     ///< 有输入
            giPinEvent = PIN_EVENT_NONE;

            mmi_clearLine(dispLine);
            mmi_display((DISP_VAlign)dispLine, column, "%*.*s", 0, m_offPinData.ucPinLen, dispBuff);
            continue;
        case PIN_EVENT_COMPLETE:///< 输入完成
            ///< 成功
            if (m_offPinData.aucRespData[0] == 0x90 && m_offPinData.aucRespData[1] == 0x00) {
                iRet = SUCCESS;
            }
            ///< 密码错误
            else if (m_offPinData.aucRespData[0] == 0x63 && (m_offPinData.aucRespData[1] & 0xC0) == 0xC0) {
                iRet = ERR_PWD_PIN_ERR;
                *bVerifyPinTryCnt = m_offPinData.aucRespData[1] & 0x0F;
            }
            ///< 密码错误
            else if (m_offPinData.aucRespData[0] == 0x69
                 && (m_offPinData.aucRespData[1] == 0x83 || m_offPinData.aucRespData[1] == 0x84)){
                iRet = ERR_PWD_PIN_BLOCK;
            }
            else{
                iRet = ERR_PWD_OTHER_ERR;
            }
            break;
        case PIN_EVENT_PINFREE: ///< 直接按确定
            ///< 默认密码错,重新输入
            iRet = ERR_PWD_PIN_ERR;
            if (1 == bPinByPass){
                iRet = ERR_PWD_NO_PASSWORD;
            }
            break;
        case PIN_EVENT_INVALID:
            giPinEvent = PIN_EVENT_NONE;
            continue;
        case PIN_EVENT_EXIT:
            iRet = ERR_CANCEL;
            break;
        case PIN_EVENT_ERR:
            iRet = ERR_PWD_OTHER_ERR;
            if (giPinErr != SUCCESS) {
                iRet = giPinErr;
            }
            break;
        default:
            iRet = ERR_TIMEOUT;
            break;
        }
        break;
    }
    KbFlush();
    return iRet;
}

/**
* 用于获取脱机密文pin
*bIccSolt:icc卡槽 0
*bMode:默认为0
*pExpPinLenList:密码输入限制
*uiExpList:最长8字节
*bTimeOut:超时时间
*pMaterial:用于验证密文的信息
*bPinByPass:是否支持pin by pass
*bPinTryCnt:获取pin尝试次数
**bVerifyPinTryCnt:如果pin验证出错,则该值为卡片返回的pin尝试次数
*return :true->密码过程输入成功,false->取消或其他原因
*/
int EMV_UTIL_InputOffCipherPinPwd(unsigned int dispLine,
                                  unsigned int column,
                                  char bPinByPass,
                                  int *bVerifyPinTryCnt,
                                  unsigned char *pinCipherItem,
                                  int timeout)
{
    int iRet;
    char dispBuff[20];
    Cipher_Pin_Material_Type pCipherPinMater = { 0 };
    Offline_Pin_Data pOffCipherPin = { 0 };
    PIN_OFF_CIPHER_ITEM *pPinCipherItem = NULL;

    if (!pinCipherItem) {
        return ERR_PARAM;
    }
    pPinCipherItem = pinCipherItem;

    if (pPinCipherItem->uiPubExp > (sizeof(pPinCipherItem->bPubExp)) ||
        pPinCipherItem->uiPubMod > sizeof(pPinCipherItem->bPubMod) ||
        pPinCipherItem->uiCardRnd > sizeof(pPinCipherItem->bCardRng)){
        return ERR_PARAM;
    }

    giPinErr = SUCCESS;
    giPinEvent = PIN_EVENT_NONE;
    pCipherPinMater.Slot = ICC_SLOT;
    pCipherPinMater.Mode = OFFLINE_MODE_DEF;
    pCipherPinMater.TimeoutMs = timeout*1000;
    pCipherPinMater.ListLen = 10;
    memcpy(pCipherPinMater.ExpPinLenList, EMV_L2_DEFAULT_PIN_LIST_10, pCipherPinMater.ListLen);

    pCipherPinMater.PubModLen = pPinCipherItem->uiPubMod;
    memcpy(pCipherPinMater.PubMod, pPinCipherItem->bPubMod, pCipherPinMater.PubModLen);

    pCipherPinMater.PubExpLen = pPinCipherItem->uiPubExp;
    memcpy(pCipherPinMater.PubExp, pPinCipherItem->bPubExp, pCipherPinMater.PubExpLen);

    pCipherPinMater.CardRndLen = pPinCipherItem->uiCardRnd;
    memcpy(pCipherPinMater.CardRnd, pPinCipherItem->bCardRng, pCipherPinMater.CardRndLen);

    memset(dispBuff, '*', sizeof(dispBuff));
    if (PedVerifyOfflineCipherRev(&pCipherPinMater, EMV_UTIL_PlainEventCB, &pOffCipherPin) != 0) {
//        PIN输入次数超限，错误码是 -307， 对应的十六进制： FECD
        KbFlush();
        return ERR_DRV;
    }

    while (1)
    {
        if (!GetSysStatus()) {
            PedInputCancelRev();
            iRet = ERR_CANCEL;
            break;
        }

        switch (giPinEvent)
        {
        case PIN_EVENT_NONE:    ///< 无输入
            Sleep(50);
            continue;
        case PIN_EVENT_LEN:     ///< 有输入
            giPinEvent = PIN_EVENT_NONE;

            mmi_clearLine(dispLine);
            mmi_display((DISP_VAlign)dispLine, column, "%*.*s", 0, pOffCipherPin.ucPinLen, dispBuff);
            continue;
        case PIN_EVENT_COMPLETE:    ///< 输入完成
            ///< 成功
            if (pOffCipherPin.aucRespData[0] == 0x90 && pOffCipherPin.aucRespData[1] == 0x00){
                iRet = SUCCESS;
            }
            ///< 密码错误
            else if (pOffCipherPin.aucRespData[0] == 0x63 && (pOffCipherPin.aucRespData[1] & 0xC0) == 0xC0){// 密码错误
                iRet = ERR_PWD_PIN_ERR;
                *bVerifyPinTryCnt = pOffCipherPin.aucRespData[1] & 0x0F;
            }
            ///< 密码错误
            else if (pOffCipherPin.aucRespData[0] == 0x69
                 && (pOffCipherPin.aucRespData[1] == 0x83 || pOffCipherPin.aucRespData[1] == 0x84)){
                    iRet = ERR_PWD_PIN_BLOCK;
            }
            else{
                iRet = ERR_PWD_OTHER_ERR;
            }
            break;
        case PIN_EVENT_PINFREE: ///< 直接按确定
            ///< 默认密码错,重新输入
            iRet = ERR_PWD_PIN_ERR;
            if (1 == bPinByPass){
                iRet = ERR_PWD_NO_PASSWORD;
            }
            break;
        case PIN_EVENT_INVALID:
            giPinEvent = PIN_EVENT_NONE;
            continue;
        case PIN_EVENT_EXIT:
            iRet = ERR_CANCEL;
            break;
        case PIN_EVENT_ERR:
            iRet = ERR_PWD_OTHER_ERR;
            if (giPinErr != SUCCESS) {
                iRet = giPinErr;
            }
            break;
        default:
            iRet = ERR_TIMEOUT;
            break;
        }
        break;
    }
    KbFlush();
    return iRet;
}

