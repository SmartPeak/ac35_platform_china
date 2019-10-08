#include "bwsdk_api.h"
#include "applib_def.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "AppCallBack.h"
#include "EmvKernel.h"
#include "EmvTag.h"
#include "EmvCtKernelL2.h"

#include "EmvKernel.h"
#include "Emv_Callback.h"
#include "Emv_Utile.h"
#include "Emv_Param.h"
#include "Emv_CL_Callback.h"
#include "Emv_CT_Callback.h"

#include "trans.h"

#define DEBUG_EMV_CONFIG        0
#if DEBUG_EMV_CONFIG
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG __func__
#endif

extern TRANS_HANDLE _TRANS_HANDLE;
extern char *trans_GetTransName(int transType);

int EMV_TagPackProcess(unsigned int iTag, unsigned char type, unsigned char *pData, unsigned int iMaxLen, unsigned int iDataLen)
{
    unsigned char mBuf[64];
    unsigned int mBufLen;

    if (iTag == 0x9F1E)
    {
        if ((iDataLen+3+8) > iMaxLen)
            return iDataLen;

        mBufLen = sizeof(mBuf);
        memset(mBuf, 0, sizeof(mBuf));
        memcpy(mBuf, "\x30\x30\x30\x30\x30\x30\x30\x31", 8);
        mBufLen = 8;
        iDataLen = TlvAppend(0x9F1E, mBuf, 0, pData, iDataLen, (int)mBufLen);
    }
    else if (iTag == 0x9F02 && type == 1)
    {
        if ((iDataLen+3+6) > iMaxLen)
            return iDataLen;

        mBufLen = sizeof(mBuf);
        memset(mBuf, 0, sizeof(mBuf));
        memcpy(mBuf, "\x00\x00\x00\x00\x00\x00", 6);
        mBufLen = 6;
        iDataLen = TlvAppend(0x9F02, mBuf, 0, pData, iDataLen, (int)mBufLen);
    }
    else if (iTag == 0x9F26 && ExtraData.uc9F26Flag && _TRANS_HANDLE.ARPCLen) {
        if ((iDataLen+3+8) > iMaxLen)
            return iDataLen;

        iDataLen = TlvAppend(0x9F26, _TRANS_HANDLE.ARPC, 0, pData, iDataLen, 8);
    }
    else
    {
        mBufLen = sizeof(mBuf);
        memset(mBuf, 0, sizeof(mBuf));
        if (EMV_OK == EMV_GetTransData((EMV_TAG)iTag, (LP_EMV_BYTE)mBuf, &mBufLen))
        {
            if ((iDataLen+3+mBufLen) > iMaxLen)
                return iDataLen;

            iDataLen = TlvAppend(iTag, mBuf, 0, pData, iDataLen, (int)mBufLen);
        }
        else if (iTag == 0x9F27)
        {
            mBufLen = 1;
            if ((iDataLen+3+mBufLen) > iMaxLen)
                return iDataLen;

            iDataLen = TlvAppend(iTag, mBuf, 0, pData, iDataLen, (int)mBufLen);
        }
        else if (iTag == 0xDf31) {
            mBufLen = sizeof(mBuf);
            if ((iDataLen+3+mBufLen) > iMaxLen)
                return iDataLen;

            if (EMV_OK == EMV_Contact_GetScriptResult((LP_EMV_CHAR)mBuf, (EMV_INT32)mBufLen)) {
                iDataLen = TlvAppend(iTag, mBuf, 0, pData, iDataLen, strlen((char *)mBuf));
            }
        }

#if DEBUG_EMV_CONFIG
        LOGD("%x", iTag);
        logger_serial_dump_buff("Data:", mBuf, mBufLen);
#endif
    }
    return iDataLen;
}

///< Get field 55
int EMV_UnpackField55(unsigned char *buff, unsigned int buffSize, unsigned char *pTempBuff, unsigned int tempBuffSize)
{
    unsigned short usLen;

    if (_TRANS_HANDLE.ARPC) {
        _TRANS_HANDLE.ARPCLen = 0;
        EMV_GetTagValueFromStr(buff, buffSize, "\x91", _TRANS_HANDLE.ARPC, &_TRANS_HANDLE.ARPCLen);
#if DEBUG_EMV_CONFIG
        logger_serial_dump_buff("ARPC", _TRANS_HANDLE.ARPC, _TRANS_HANDLE.ARPCLen);
#endif
    }

    ///< 脚本
    if (_TRANS_HANDLE.pScriptData) {
        _TRANS_HANDLE.scriptDataLen = 0;
        ///< 0x71
        usLen = 0;
        memset(pTempBuff, 0, tempBuffSize);
        if (SUCCESS == EMV_GetTagValueFromStr(buff, buffSize, "\x71", pTempBuff, &usLen)) {
            _TRANS_HANDLE.scriptDataLen = TlvAppend(0x71, pTempBuff, 0, _TRANS_HANDLE.pScriptData, _TRANS_HANDLE.scriptDataLen, usLen);
        }
        ///< 0x72
        usLen = 0;
        memset(pTempBuff, 0, tempBuffSize);
        if (SUCCESS == EMV_GetTagValueFromStr(buff, buffSize, "\x72", pTempBuff, &usLen)) {
            _TRANS_HANDLE.scriptDataLen = TlvAppend(0x72, pTempBuff, 0, _TRANS_HANDLE.pScriptData, _TRANS_HANDLE.scriptDataLen, usLen);
        }
#if DEBUG_EMV_CONFIG
        logger_serial_dump_buff("script data:", _TRANS_HANDLE.pScriptData, _TRANS_HANDLE.scriptDataLen);
#endif
    }
    return SUCCESS;
}

///< Set field 55 (type: 1-query)
int EMV_GetField55(unsigned char type, unsigned char *buff, unsigned int buffSize, unsigned int *outLen)
{
    unsigned int iLen = 0;

    memset(buff, 0, buffSize);
    iLen = EMV_TagPackProcess(0x9F26, type, buff, buffSize, iLen);   // 9F26 应用密文
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);   // 9F10 发卡行应用数据
    iLen = EMV_TagPackProcess(0x9F24, type, buff, buffSize, iLen);   // 9F24
    iLen = EMV_TagPackProcess(0x9F27, type, buff, buffSize, iLen);   // 9F27 应用信息数据

    iLen = EMV_TagPackProcess(0x9F37, type, buff, buffSize, iLen);   // 9F37 不可预知数
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);   // 9F36 应用交易计数器
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);   // 95   终端验证结果
    iLen = EMV_TagPackProcess(0x9A,   type, buff, buffSize, iLen);   // 9A   交易日期
    iLen = EMV_TagPackProcess(0x9C,   type, buff, buffSize, iLen);   // 9C   交易类型
    iLen = EMV_TagPackProcess(0x9F02, type, buff, buffSize, iLen);   // 9F02 交易金额
    iLen = EMV_TagPackProcess(0x5F2A, type, buff, buffSize, iLen);   // 5F2A 交易货币代码
    iLen = EMV_TagPackProcess(0x82,   type, buff, buffSize, iLen);   // 82   应用交互特征
    iLen = EMV_TagPackProcess(0x9F1A, type, buff, buffSize, iLen);   // 9F1A 终端国家代码
    iLen = EMV_TagPackProcess(0x9F03, type, buff, buffSize, iLen);   // 9F03 其它金额
    iLen = EMV_TagPackProcess(0x9F09, type, buff, buffSize, iLen);   // 9F09 应用版本号
    iLen = EMV_TagPackProcess(0x9F33, type, buff, buffSize, iLen);   // 9F33 终端性能
    iLen = EMV_TagPackProcess(0x9F34, type, buff, buffSize, iLen);   // 9F34 持卡人验证结果
    iLen = EMV_TagPackProcess(0x9F35, type, buff, buffSize, iLen);   // 9F35 终端类型
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);   // 9F1E 接口设备序列号
    if (!type) {
        iLen = EMV_TagPackProcess(0x84,   type, buff, buffSize, iLen);   // 84
    }
    iLen = EMV_TagPackProcess(0x9F41, type, buff, buffSize, iLen);   // 9F41 交易序列计数器
    iLen = EMV_TagPackProcess(0x9F63, type, buff, buffSize, iLen);   // 9F63 卡产品标识

    *outLen = iLen;

    return SUCCESS;
}

///< Set field 55
int EMV_GetReversalField55(unsigned char *buff, unsigned int buffSize, unsigned int *outLen)
{
    unsigned int iLen = 0;
    unsigned char type = 0;

    memset(buff, 0, buffSize);
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);   // 95   终端验证结果
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);   // 9F1E 接口设备序列号
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);   // 9F10 发卡行应用数据
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);   // 9F36 应用交易计数器

    iLen = EMV_TagPackProcess(0xDF31, type, buff, buffSize, iLen);

    *outLen = iLen;

    return SUCCESS;
}

///< Set field 55
int EMV_GetScriptField55(unsigned char *buff, unsigned int buffSize, unsigned int *outLen)
{
    unsigned int iLen = 0;
    unsigned char type = 0;

    memset(buff, 0, buffSize);
    iLen = EMV_TagPackProcess(0x9F33, type, buff, buffSize, iLen);  // 9F33 终端性能
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);  // 95   终端验证结果
    iLen = EMV_TagPackProcess(0x9F37, type, buff, buffSize, iLen);  // 9F37 不可预知数
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);  // 9F1E 接口设备序列号
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);  // 9F10 发卡行应用数据
    iLen = EMV_TagPackProcess(0x9F26, type, buff, buffSize, iLen);  // 9F26 应用密文
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);  // 9F36 应用交易计数器
    iLen = EMV_TagPackProcess(0x82,   type, buff, buffSize, iLen);  // 82   应用交互特征
    iLen = EMV_TagPackProcess(0xDF31, type, buff, buffSize, iLen);  // DF31 发卡行脚本结果
    iLen = EMV_TagPackProcess(0x9F1A, type, buff, buffSize, iLen);  // 9F1A 终端国家代码
    iLen = EMV_TagPackProcess(0x9A,   type, buff, buffSize, iLen);  // 9A   交易日期

    *outLen = iLen;

    return SUCCESS;
}

///< 数据保存到szRealTmpBuf中
#define MAKE_TRANS_DATA_Ex(Tag, _data, _len)   \
    _len = 0; \
    memset(_data, 0, sizeof(_data));    \
    if (EMV_OK == EMV_GetTransDataAsHex(Tag, (char *)_data, sizeof(_data))) \
    {    \
        _len = strlen((const char *)_data); \
    }\
    _len

///< 通过解析57获取卡号和卡片有效期
static void EMV_GetCardNoFor57(char *data57, unsigned char *cardNo, unsigned char *expData)
{
    char *card = NULL;
    int count = 0;

    card = strtok(data57, "D");
    while (card != NULL) {
        count++;
        if (count == 1) {
            memcpy(cardNo, card, strlen(card));
        }
        else if (count == 2) {
            memcpy(expData, card, 4);
        }

        card = strtok(NULL, "D");
    }
}

static int EMV_CompareCardPAN(unsigned char *cardNo, unsigned char *pSrcCardNo, unsigned char srcCardNoLen)
{
    unsigned char mBuf[64] = {0};

    tools_bcd_asc(mBuf, pSrcCardNo, srcCardNoLen + (srcCardNoLen%2 ? 1 : 0));
    mBuf[srcCardNoLen] = 0x00;
    if ((srcCardNoLen != strlen((const char *)cardNo))
        || strcmp((char *)cardNo, (char *)mBuf)) {
        return ERR_VOID_CARD_DIFFER;
    }
    return SUCCESS;
}

///< 获取用户卡信息(主帐号、有效期、序列号、磁道信息)
static int EMV_GetTrack2Data(void)
{
    int iRet = SUCCESS;
    int iLen = 0;
    unsigned char mBuf[64] = {0};
    unsigned char cardNo[20] = {0}, cardExpDate[5] = {0};

    /*----------------------------------------------
     * MAKE_TRANS_DATA 出来都是ASCII编码数据
     *----------------------------------------------*/

    //Tag:5A  应用主帐号PAN
    iLen = MAKE_TRANS_DATA_Ex(TAG_PAN, mBuf, iLen);
    if (iLen > 0)
    {
        // 除去二磁道数据的补充f字符
        if (('f' == mBuf[iLen - 1]) || ('F' == mBuf[iLen - 1])) {
            mBuf[iLen-1] = 0x00;
            iLen -= 1;
        }
        if (iLen > 37) {
            iLen = 37;
        }

        if ((TRANS_VOID_SALE == ExtraData.transType)) {
            iRet = EMV_CompareCardPAN(mBuf, DataTrans.sourceAcc, DataTrans.sourceAccLen);
            if (iRet != SUCCESS) {
                return iRet;
            }
        }

        if (!strlen((char *)DataTrans.sourceAcc)) {
            DataTrans.sourceAccLen = iLen;
            tools_asc_bcd(DataTrans.sourceAcc, (iLen + 1) / 2, mBuf, ((iLen + 1) / 2) * 2);
        }
    }

    //Tag:5F24  有效期
    iLen = MAKE_TRANS_DATA_Ex(TAG_APP_EXPIRATION_DATE, mBuf, iLen);
    if (iLen > 0)
    {
        memcpy(DataTrans.expiredDate, mBuf, min(iLen, sizeof(DataTrans.expiredDate)));
    }

    //Tag:5F34  应用主帐号序列号
    iLen = MAKE_TRANS_DATA_Ex(TAG_PAN_SEQ, mBuf, iLen);
    if (iLen > 0)
    {
        memcpy(DataTrans.panSeq, mBuf, min(iLen, sizeof(DataTrans.panSeq)));
    }

    //Tag:57  获取2磁道信息
    iLen = MAKE_TRANS_DATA_Ex(TAG_TRACK2_EQUIVALENT_DATA, mBuf, iLen);
    if (iLen > 0)
    {
        // 除去二磁道数据的补充f字符
        if (('f' == mBuf[iLen - 1]) || ('F' == mBuf[iLen - 1])) {
            mBuf[iLen-1] = 0x00;
            iLen -= 1;
        }
        if (iLen > 37) {
            iLen = 37;
        }

        //2磁道
        ExtraData.iso2Len = iLen;
        memset(ExtraData.iso2, 0, sizeof(ExtraData.iso2));
        memcpy(ExtraData.iso2, mBuf, min(iLen, sizeof(ExtraData.iso2)));

        memset(cardNo, 0x00, sizeof(cardNo));
        memset(cardExpDate, 0x00, sizeof(cardExpDate));
        EMV_GetCardNoFor57((char *)mBuf, cardNo, cardExpDate);

        iLen = strlen((char *)cardNo);
        if ((TRANS_VOID_SALE == ExtraData.transType)) {
            iRet = EMV_CompareCardPAN(cardNo, DataTrans.sourceAcc, DataTrans.sourceAccLen);
            if (iRet != SUCCESS) {
                return iRet;
            }
        }

        //主帐号
        if (!strlen((char *)DataTrans.sourceAcc))
        {
            DataTrans.sourceAccLen = iLen;
            tools_asc_bcd(DataTrans.sourceAcc, (iLen + 1) / 2, cardNo, ((iLen + 1) / 2) * 2);
        }

        //有效期
        if (!strlen((char *)DataTrans.expiredDate))
        {
            memcpy(DataTrans.expiredDate, cardExpDate, strlen((char *)cardExpDate));
        }
    }
    return iRet;
}

///< 获取IC数据,用于打印IC信息
void EMV_GetICCardInfo(void)
{
    unsigned short uiLen;

    if (EVENT_MFR_DRV == ExtraData.eventType) {
        ///< AID(16)
        uiLen = sizeof(DataTrans.aucAID);
        EMV_GetTransDataAsHex(TAG_DF_NAME, (char *)DataTrans.aucAID, uiLen);
    }
    else {
        ///< AID(16)
        uiLen = sizeof(DataTrans.aucAID);
        EMV_GetTransDataAsHex(TAG_AID, (char *)DataTrans.aucAID, uiLen);
    }

    ///< AC(16)
    uiLen = sizeof(DataTrans.aucARQC);
    EMV_GetTransDataAsHex(TAG_APP_CRYPTOGRAM, (char *)DataTrans.aucARQC, uiLen);
    ///< TVR(5)
    uiLen = sizeof(DataTrans.bcdTVR);
    EMV_GetTransData(TAG_TVR, DataTrans.bcdTVR, &uiLen);
#if DEBUG_EMV_CONFIG
    logger_serial_dump_buff("TVR:", DataTrans.bcdTVR, uiLen);
#endif
    ///< TSI(2)
    uiLen = sizeof(DataTrans.bcdTSI);
    EMV_GetTransData(TAG_TSI, DataTrans.bcdTSI, &uiLen);
    ///< ATC(2)
    uiLen = sizeof(DataTrans.bcdATC);
    EMV_GetTransData(TAG_ATC, DataTrans.bcdATC, &uiLen);
    ///< APP LIB(16)
    uiLen = sizeof(DataTrans.aucAPPLAB);
    EMV_GetTransData(TAG_APP_LABEL, DataTrans.aucAPPLAB, &uiLen);
    ///< Application Prefer Name(16)
    uiLen = sizeof(DataTrans.aucAPPNAME);
    EMV_GetTransData(TAG_APP_PREFERRED_NAME, DataTrans.aucAPPNAME, &uiLen);

    if (EVENT_ICC_DRV == ExtraData.eventType && memcmp(DataTrans.bcdTVR, "\x00\x00\x00\x00\x00", 5))
    {
        if ((DataTrans.bcdTVR[4]&0x40)) {
            ExtraData.uc9F26Flag = 1;
        }

        DataTrans.field55Len = sizeof(DataTrans.field55Data);
        EMV_GetField55(0, DataTrans.field55Data, sizeof(DataTrans.field55Data), &DataTrans.field55Len);
    }
}

///< 显示处理中
void EMV_DisplayProcessing(void)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, "处理中");
    mmi_display(DISP_Line3, 0, "请稍等...");
}

///< EMV内核调用-->输金额
int EMV_InputAmount(unsigned int *amount)
{
    int iRet = SUCCESS;

    if (!DataTrans.ulAmount) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
        mmi_display(DISP_Line2, DISP_Left, "请输入金额");
        mmi_display(DISP_Line5, DISP_Left, "输错请按[清除键]");
        iRet = mmi_InputAmount(DISP_Line3, 0, 0, &DataTrans.ulAmount, 0, 99999999, 60);
    }

    if (amount) {
        *amount = DataTrans.ulAmount;
    }
    return iRet;
}

///< EMV内核调用-->显示主账号
int EMV_DisplayPanNo(const char* pPanNo)
{
    int iRet;

    if ((TRANS_VOID_SALE == ExtraData.transType)) {
        iRet = EMV_CompareCardPAN((unsigned char *)pPanNo, DataTrans.sourceAcc, DataTrans.sourceAccLen);
        if (iRet != SUCCESS) {
            return iRet;
        }
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, "卡号:");
    mmi_display(DISP_Line3, 0, (char *)pPanNo);
    mmi_display(DISP_Line5, DISP_Left, "  [取消]");
    mmi_display(DISP_Line5, DISP_Right, "[确认]  ");

    while(1)
    {
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

///< 非接免密判断(返回0不输入,返回其他值输密)
static int EMV_MqMm(void)
{
    int iRet = -1;
    unsigned char mCVM[5], mCurrency[10];
    unsigned short mBufLen;
    unsigned char ucByte1Bit8 = 0;
    unsigned char ucByte2Bit8 = 0;

    ///< 不是非接事件的跳过
    if (EVENT_MFR_DRV != ExtraData.eventType) {
        goto END;
    }
    ///< 闪付凭密,需要输密
    if (ENTRY_PUT_CARD == ExtraData.entryType) {
        goto END;
    }

    ///< 非消费、预授权交易跳过
    if (ExtraData.transType != TRANS_SALE) {
        goto END;
    }

    ///< 判断免密开关
    if (DataChange.QPS_NoPIN_Flag != 1 && DataChange.QPS_CDCVM_Flag != 1) {
        goto END;
    }

    ///< 判断 CD-CVM 9F6C
    mBufLen = sizeof(mCVM);
    memset(mCVM, 0, sizeof(mCVM));
    EMV_GetTransData(0x9F6C, (LP_EMV_BYTE)mCVM, &mBufLen);
    ucByte1Bit8 = BitGet(mCVM[0],8);
    ucByte2Bit8 = BitGet(mCVM[1],8);  //卡片CDCVM标志
#if DEBUG_EMV_CONFIG
    logger_serial_dump_buff("CVM:", mCVM, mBufLen);
    LOGD("Byte1Bit8:%d,Byte2Bit8:%d\n", ucByte1Bit8, ucByte2Bit8);
#endif
    if (ucByte2Bit8) {
        DataTrans.ucCDCVM = 1;
    }
    ///< 启用CD-CVM,并无需联机PIN,且免密开启
    if(!ucByte1Bit8 && ucByte2Bit8 && 1 == DataChange.QPS_CDCVM_Flag) {
        return 0;
    }

    ///< 获取货币代码(9F51)
    mBufLen = sizeof(mCurrency);
    memset(mCurrency, 0, sizeof(mCurrency));
    EMV_GetTransData(0x9F51, (LP_EMV_BYTE)mCurrency, &mBufLen);
#if DEBUG_EMV_CONFIG
    logger_serial_dump_buff("9F51:", mCurrency, mBufLen);
#endif

    ///< 内卡判断
    if (!memcmp(mCurrency, "\x01\x56", 2))
    {
        if (DataTrans.ulAmount <= DataChange.QPS_PINAmtLimit) {
            return 0;
        }
        goto END;
    }
    ///< 外卡判断
    else
    {
        if(!ucByte1Bit8) {
            return 0;
        }
    }
END:
    return iRet;
}

bool G_InputPIN = false;
///< 联机PIN输入
int EMV_InputOnlinePIN(const char *panData, unsigned char *pinBlock, unsigned short *pPinBlockBuffSize)
{
    int iRet = SUCCESS;
    unsigned int iLen;
    unsigned int dispLine = DISP_Line2;
    unsigned long ulAmount = DataTrans.ulAmount;

    if (true == G_InputPIN) {
        return SUCCESS;
    }
    G_InputPIN = false;

    if (((TRANS_VOID_SALE == ExtraData.transType)
            && !DataConstant.isVoidInputPIN)
        ) {
        return SUCCESS;
    }

    if (!panData || !pinBlock || !pPinBlockBuffSize) {
        return ERR_PARAM;
    }

    if (!EMV_MqMm()) {
        return SUCCESS;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (ulAmount > 0) {
        mmi_display((DISP_VAlign)(dispLine++), DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
    }
    mmi_display((DISP_VAlign)(dispLine++), 0, "请输入联机密码");
    mmi_display((DISP_VAlign)(dispLine++), 0, "请持卡人输入密码");
    mmi_display((DISP_VAlign)(dispLine--), 0, "无密码请按[确认键]");

    /*!< --------------------------------------------------------------------*/
    ExtraData.inputPINLen = 0;
    memset(ExtraData.PINData, 0, sizeof(ExtraData.PINData));

    iLen = sizeof(ExtraData.PINData);
    iRet = EMV_UTIL_InputOnlinePIN((DISP_VAlign)(dispLine), 0, panData, ExtraData.PINData, &iLen, 60);
    if (SUCCESS == iRet) {
        G_InputPIN = true;
        ExtraData.inputPINLen = iLen;
        if (iLen > 0){
            DataTrans.isInputPIN = 1;
            if (*pPinBlockBuffSize > (iLen * 2))
                vOneTwo((unsigned char*)ExtraData.PINData, iLen, pinBlock);
        }
    }
    *pPinBlockBuffSize = iLen;
    return iRet;
}

///< EMV内核调用-->脱机明文PIN输入
int EMV_InputOffPlainPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt)
{
    unsigned int dispLine = DISP_Line2;
    unsigned long ulAmount = DataTrans.ulAmount;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (ulAmount > 0) {
        mmi_display((DISP_VAlign)(dispLine++), DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
    }
    mmi_display((DISP_VAlign)(dispLine++), 0, "请输入脱机密码");
    if (1 == bPinTryCnt) {
        mmi_display((DISP_VAlign)(dispLine++), 0, "请重新输入");
    }
    else {
        mmi_display((DISP_VAlign)(dispLine++), 0, "请持卡人输入密码");
    }
    mmi_display((DISP_VAlign)(dispLine--), 0, "无密码请按[确认键]");
    return EMV_UTIL_InputOffPlainPinPwd((DISP_VAlign)(dispLine), 0, bPinByPass, bVerifyPinTryCnt, 60);
}

///< 刷卡前处理
int EMV_TransBeforeSwipe(void)
{
    int iRet = SUCCESS;

    switch (ExtraData.transType) {
        case TRANS_REFUND:
            ///< 输入原交易参考号
            if (SUCCESS == iRet) {
               iRet = transUI_inputRefNo("请输入原交易参考号:", DataTrans.oldRefNumber);
            }
            ///< 输入原交易日期
            if (SUCCESS == iRet) {
                iRet = transUI_inputDate("请输入原交易日期[MM/DD]:", DataTrans.oldDate);
            }
            ///< 输入交易金额
            if ((SUCCESS == iRet) && !DataTrans.ulAmount) {
                while (1) {
                    iRet = transUI_inputAmount("请输入金额:", 1, 999999999, &DataTrans.ulAmount);
                    if (SUCCESS == iRet) {
                        iRet = transUI_confirmAmount(NULL, DataTrans.ulAmount);
                        if (ERR_CANCEL == iRet) {
                            continue;
                        }
                    }
                    break;
                }
            }
            break;
        default:
            break;
    }

    ///< Input PIN 输密
    if (SUCCESS == iRet) {
        if (TRANS_REFUND == ExtraData.transType) {
            if (!ExtraData.inputPINLen) {
                iRet = transUI_InputCardPIN();
            }
       }
    }

    return iRet;
}

/**
 * @brief  输入卡片联机密码
 * @brief  input card online pin
 */
int transUI_InputOnlineCardPIN(void)
{
    extern bool G_InputPIN;
    extern int EMV_InputOnlinePIN(const char *panData, unsigned char *pinBlock, unsigned short *pPinBlockBuffSize);

    char cardPan[21] = {0};
    unsigned char pinBlock[30] = {0};
    unsigned short pinBlockBuffSize = 0;

    tools_bcd_asc((unsigned char *)cardPan, DataTrans.sourceAcc,
                  DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
    cardPan[DataTrans.sourceAccLen] = 0x00;

    pinBlockBuffSize = sizeof(pinBlock);
    return EMV_InputOnlinePIN(cardPan, pinBlock, &pinBlockBuffSize);
}

///< EMV内核调用-->脱机密文PIN输入
int EMV_InputOffCipherPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt, unsigned char* pVerifyResult)
{
    unsigned int dispLine = DISP_Line2;
    unsigned long ulAmount = DataTrans.ulAmount;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (ulAmount > 0) {
        mmi_display((DISP_VAlign)(dispLine++), DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
    }

    mmi_display((DISP_VAlign)(dispLine++), 0, "请输入脱机密码");
    if (1 == bPinTryCnt) {
        mmi_display((DISP_VAlign)(dispLine++), 0, "请重新输入");
    }
    else {
        mmi_display((DISP_VAlign)(dispLine++), 0, "请持卡人输入密码");
    }
    mmi_display((DISP_VAlign)(dispLine--), 0, "无密码请按[确认键]");
    return EMV_UTIL_InputOffCipherPinPwd((DISP_VAlign)(dispLine), 0, bPinByPass, bVerifyPinTryCnt, pVerifyResult, 60);
}

///< EMV内核调用-->联机请求
int EMV_TransOnline(void)
{
    int iRet = SUCCESS;

    ///< 获取卡信息
    if (SUCCESS == iRet) {
        iRet = EMV_GetTrack2Data();
    }

    if (SUCCESS == iRet) {
        switch(ExtraData.transType)
        {
        case TRANS_QUERY_BAL:
        case TRANS_SALE:
            if (!ExtraData.inputPINLen) {
                iRet = transUI_InputOnlineCardPIN();
            }
            break;
        case TRANS_VOID_SALE:
            if ((DataConstant.isVoidInputPIN) && !ExtraData.inputPINLen) {
                iRet = transUI_InputOnlineCardPIN();
            }
            break;
        case TRANS_REFUND:
            iRet = EMV_TransBeforeSwipe();
            break;
        default:
            break;
        }
    }

    ///< 联机请求
    if (SUCCESS == iRet) {
        if (EVENT_MFR_DRV == ExtraData.eventType) {
            transUtil_LED_TransOnline(1);
        }
        iRet = transOnline_process();
        if (EVENT_MFR_DRV == ExtraData.eventType) {
            transUtil_LED_TransOnline(0);
        }
    }

    return iRet;
}

int EMV_LoadConfig(void)
{
    G_InputPIN = false;

    _TRANS_HANDLE.getErrCode = trans_GetErrCodeToEmvKernel;
    _TRANS_HANDLE.ScriptResultSave = transOnline_ScriptResultSave;
    if (TRANS_REFUND == ExtraData.transType) {
        _TRANS_HANDLE.bEmvInputPINBypass = 1;
        return EMV_TRUE;
    }
    return SUCCESS;
}

