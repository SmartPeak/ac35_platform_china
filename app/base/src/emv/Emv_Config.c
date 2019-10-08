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

    ///< �ű�
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
    iLen = EMV_TagPackProcess(0x9F26, type, buff, buffSize, iLen);   // 9F26 Ӧ������
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);   // 9F10 ������Ӧ������
    iLen = EMV_TagPackProcess(0x9F24, type, buff, buffSize, iLen);   // 9F24
    iLen = EMV_TagPackProcess(0x9F27, type, buff, buffSize, iLen);   // 9F27 Ӧ����Ϣ����

    iLen = EMV_TagPackProcess(0x9F37, type, buff, buffSize, iLen);   // 9F37 ����Ԥ֪��
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);   // 9F36 Ӧ�ý��׼�����
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);   // 95   �ն���֤���
    iLen = EMV_TagPackProcess(0x9A,   type, buff, buffSize, iLen);   // 9A   ��������
    iLen = EMV_TagPackProcess(0x9C,   type, buff, buffSize, iLen);   // 9C   ��������
    iLen = EMV_TagPackProcess(0x9F02, type, buff, buffSize, iLen);   // 9F02 ���׽��
    iLen = EMV_TagPackProcess(0x5F2A, type, buff, buffSize, iLen);   // 5F2A ���׻��Ҵ���
    iLen = EMV_TagPackProcess(0x82,   type, buff, buffSize, iLen);   // 82   Ӧ�ý�������
    iLen = EMV_TagPackProcess(0x9F1A, type, buff, buffSize, iLen);   // 9F1A �ն˹��Ҵ���
    iLen = EMV_TagPackProcess(0x9F03, type, buff, buffSize, iLen);   // 9F03 �������
    iLen = EMV_TagPackProcess(0x9F09, type, buff, buffSize, iLen);   // 9F09 Ӧ�ð汾��
    iLen = EMV_TagPackProcess(0x9F33, type, buff, buffSize, iLen);   // 9F33 �ն�����
    iLen = EMV_TagPackProcess(0x9F34, type, buff, buffSize, iLen);   // 9F34 �ֿ�����֤���
    iLen = EMV_TagPackProcess(0x9F35, type, buff, buffSize, iLen);   // 9F35 �ն�����
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);   // 9F1E �ӿ��豸���к�
    if (!type) {
        iLen = EMV_TagPackProcess(0x84,   type, buff, buffSize, iLen);   // 84
    }
    iLen = EMV_TagPackProcess(0x9F41, type, buff, buffSize, iLen);   // 9F41 �������м�����
    iLen = EMV_TagPackProcess(0x9F63, type, buff, buffSize, iLen);   // 9F63 ����Ʒ��ʶ

    *outLen = iLen;

    return SUCCESS;
}

///< Set field 55
int EMV_GetReversalField55(unsigned char *buff, unsigned int buffSize, unsigned int *outLen)
{
    unsigned int iLen = 0;
    unsigned char type = 0;

    memset(buff, 0, buffSize);
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);   // 95   �ն���֤���
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);   // 9F1E �ӿ��豸���к�
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);   // 9F10 ������Ӧ������
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);   // 9F36 Ӧ�ý��׼�����

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
    iLen = EMV_TagPackProcess(0x9F33, type, buff, buffSize, iLen);  // 9F33 �ն�����
    iLen = EMV_TagPackProcess(0x95,   type, buff, buffSize, iLen);  // 95   �ն���֤���
    iLen = EMV_TagPackProcess(0x9F37, type, buff, buffSize, iLen);  // 9F37 ����Ԥ֪��
    iLen = EMV_TagPackProcess(0x9F1E, type, buff, buffSize, iLen);  // 9F1E �ӿ��豸���к�
    iLen = EMV_TagPackProcess(0x9F10, type, buff, buffSize, iLen);  // 9F10 ������Ӧ������
    iLen = EMV_TagPackProcess(0x9F26, type, buff, buffSize, iLen);  // 9F26 Ӧ������
    iLen = EMV_TagPackProcess(0x9F36, type, buff, buffSize, iLen);  // 9F36 Ӧ�ý��׼�����
    iLen = EMV_TagPackProcess(0x82,   type, buff, buffSize, iLen);  // 82   Ӧ�ý�������
    iLen = EMV_TagPackProcess(0xDF31, type, buff, buffSize, iLen);  // DF31 �����нű����
    iLen = EMV_TagPackProcess(0x9F1A, type, buff, buffSize, iLen);  // 9F1A �ն˹��Ҵ���
    iLen = EMV_TagPackProcess(0x9A,   type, buff, buffSize, iLen);  // 9A   ��������

    *outLen = iLen;

    return SUCCESS;
}

///< ���ݱ��浽szRealTmpBuf��
#define MAKE_TRANS_DATA_Ex(Tag, _data, _len)   \
    _len = 0; \
    memset(_data, 0, sizeof(_data));    \
    if (EMV_OK == EMV_GetTransDataAsHex(Tag, (char *)_data, sizeof(_data))) \
    {    \
        _len = strlen((const char *)_data); \
    }\
    _len

///< ͨ������57��ȡ���źͿ�Ƭ��Ч��
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

///< ��ȡ�û�����Ϣ(���ʺš���Ч�ڡ����кš��ŵ���Ϣ)
static int EMV_GetTrack2Data(void)
{
    int iRet = SUCCESS;
    int iLen = 0;
    unsigned char mBuf[64] = {0};
    unsigned char cardNo[20] = {0}, cardExpDate[5] = {0};

    /*----------------------------------------------
     * MAKE_TRANS_DATA ��������ASCII��������
     *----------------------------------------------*/

    //Tag:5A  Ӧ�����ʺ�PAN
    iLen = MAKE_TRANS_DATA_Ex(TAG_PAN, mBuf, iLen);
    if (iLen > 0)
    {
        // ��ȥ���ŵ����ݵĲ���f�ַ�
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

    //Tag:5F24  ��Ч��
    iLen = MAKE_TRANS_DATA_Ex(TAG_APP_EXPIRATION_DATE, mBuf, iLen);
    if (iLen > 0)
    {
        memcpy(DataTrans.expiredDate, mBuf, min(iLen, sizeof(DataTrans.expiredDate)));
    }

    //Tag:5F34  Ӧ�����ʺ����к�
    iLen = MAKE_TRANS_DATA_Ex(TAG_PAN_SEQ, mBuf, iLen);
    if (iLen > 0)
    {
        memcpy(DataTrans.panSeq, mBuf, min(iLen, sizeof(DataTrans.panSeq)));
    }

    //Tag:57  ��ȡ2�ŵ���Ϣ
    iLen = MAKE_TRANS_DATA_Ex(TAG_TRACK2_EQUIVALENT_DATA, mBuf, iLen);
    if (iLen > 0)
    {
        // ��ȥ���ŵ����ݵĲ���f�ַ�
        if (('f' == mBuf[iLen - 1]) || ('F' == mBuf[iLen - 1])) {
            mBuf[iLen-1] = 0x00;
            iLen -= 1;
        }
        if (iLen > 37) {
            iLen = 37;
        }

        //2�ŵ�
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

        //���ʺ�
        if (!strlen((char *)DataTrans.sourceAcc))
        {
            DataTrans.sourceAccLen = iLen;
            tools_asc_bcd(DataTrans.sourceAcc, (iLen + 1) / 2, cardNo, ((iLen + 1) / 2) * 2);
        }

        //��Ч��
        if (!strlen((char *)DataTrans.expiredDate))
        {
            memcpy(DataTrans.expiredDate, cardExpDate, strlen((char *)cardExpDate));
        }
    }
    return iRet;
}

///< ��ȡIC����,���ڴ�ӡIC��Ϣ
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

///< ��ʾ������
void EMV_DisplayProcessing(void)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, "������");
    mmi_display(DISP_Line3, 0, "���Ե�...");
}

///< EMV�ں˵���-->����
int EMV_InputAmount(unsigned int *amount)
{
    int iRet = SUCCESS;

    if (!DataTrans.ulAmount) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
        mmi_display(DISP_Line2, DISP_Left, "��������");
        mmi_display(DISP_Line5, DISP_Left, "����밴[�����]");
        iRet = mmi_InputAmount(DISP_Line3, 0, 0, &DataTrans.ulAmount, 0, 99999999, 60);
    }

    if (amount) {
        *amount = DataTrans.ulAmount;
    }
    return iRet;
}

///< EMV�ں˵���-->��ʾ���˺�
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
    mmi_display(DISP_Line2, 0, "����:");
    mmi_display(DISP_Line3, 0, (char *)pPanNo);
    mmi_display(DISP_Line5, DISP_Left, "  [ȡ��]");
    mmi_display(DISP_Line5, DISP_Right, "[ȷ��]  ");

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

///< �ǽ������ж�(����0������,��������ֵ����)
static int EMV_MqMm(void)
{
    int iRet = -1;
    unsigned char mCVM[5], mCurrency[10];
    unsigned short mBufLen;
    unsigned char ucByte1Bit8 = 0;
    unsigned char ucByte2Bit8 = 0;

    ///< ���Ƿǽ��¼�������
    if (EVENT_MFR_DRV != ExtraData.eventType) {
        goto END;
    }
    ///< ����ƾ��,��Ҫ����
    if (ENTRY_PUT_CARD == ExtraData.entryType) {
        goto END;
    }

    ///< �����ѡ�Ԥ��Ȩ��������
    if (ExtraData.transType != TRANS_SALE) {
        goto END;
    }

    ///< �ж����ܿ���
    if (DataChange.QPS_NoPIN_Flag != 1 && DataChange.QPS_CDCVM_Flag != 1) {
        goto END;
    }

    ///< �ж� CD-CVM 9F6C
    mBufLen = sizeof(mCVM);
    memset(mCVM, 0, sizeof(mCVM));
    EMV_GetTransData(0x9F6C, (LP_EMV_BYTE)mCVM, &mBufLen);
    ucByte1Bit8 = BitGet(mCVM[0],8);
    ucByte2Bit8 = BitGet(mCVM[1],8);  //��ƬCDCVM��־
#if DEBUG_EMV_CONFIG
    logger_serial_dump_buff("CVM:", mCVM, mBufLen);
    LOGD("Byte1Bit8:%d,Byte2Bit8:%d\n", ucByte1Bit8, ucByte2Bit8);
#endif
    if (ucByte2Bit8) {
        DataTrans.ucCDCVM = 1;
    }
    ///< ����CD-CVM,����������PIN,�����ܿ���
    if(!ucByte1Bit8 && ucByte2Bit8 && 1 == DataChange.QPS_CDCVM_Flag) {
        return 0;
    }

    ///< ��ȡ���Ҵ���(9F51)
    mBufLen = sizeof(mCurrency);
    memset(mCurrency, 0, sizeof(mCurrency));
    EMV_GetTransData(0x9F51, (LP_EMV_BYTE)mCurrency, &mBufLen);
#if DEBUG_EMV_CONFIG
    logger_serial_dump_buff("9F51:", mCurrency, mBufLen);
#endif

    ///< �ڿ��ж�
    if (!memcmp(mCurrency, "\x01\x56", 2))
    {
        if (DataTrans.ulAmount <= DataChange.QPS_PINAmtLimit) {
            return 0;
        }
        goto END;
    }
    ///< �⿨�ж�
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
///< ����PIN����
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
    mmi_display((DISP_VAlign)(dispLine++), 0, "��������������");
    mmi_display((DISP_VAlign)(dispLine++), 0, "��ֿ�����������");
    mmi_display((DISP_VAlign)(dispLine--), 0, "�������밴[ȷ�ϼ�]");

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

///< EMV�ں˵���-->�ѻ�����PIN����
int EMV_InputOffPlainPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt)
{
    unsigned int dispLine = DISP_Line2;
    unsigned long ulAmount = DataTrans.ulAmount;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (ulAmount > 0) {
        mmi_display((DISP_VAlign)(dispLine++), DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
    }
    mmi_display((DISP_VAlign)(dispLine++), 0, "�������ѻ�����");
    if (1 == bPinTryCnt) {
        mmi_display((DISP_VAlign)(dispLine++), 0, "����������");
    }
    else {
        mmi_display((DISP_VAlign)(dispLine++), 0, "��ֿ�����������");
    }
    mmi_display((DISP_VAlign)(dispLine--), 0, "�������밴[ȷ�ϼ�]");
    return EMV_UTIL_InputOffPlainPinPwd((DISP_VAlign)(dispLine), 0, bPinByPass, bVerifyPinTryCnt, 60);
}

///< ˢ��ǰ����
int EMV_TransBeforeSwipe(void)
{
    int iRet = SUCCESS;

    switch (ExtraData.transType) {
        case TRANS_REFUND:
            ///< ����ԭ���ײο���
            if (SUCCESS == iRet) {
               iRet = transUI_inputRefNo("������ԭ���ײο���:", DataTrans.oldRefNumber);
            }
            ///< ����ԭ��������
            if (SUCCESS == iRet) {
                iRet = transUI_inputDate("������ԭ��������[MM/DD]:", DataTrans.oldDate);
            }
            ///< ���뽻�׽��
            if ((SUCCESS == iRet) && !DataTrans.ulAmount) {
                while (1) {
                    iRet = transUI_inputAmount("��������:", 1, 999999999, &DataTrans.ulAmount);
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

    ///< Input PIN ����
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
 * @brief  ���뿨Ƭ��������
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

///< EMV�ں˵���-->�ѻ�����PIN����
int EMV_InputOffCipherPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt, unsigned char* pVerifyResult)
{
    unsigned int dispLine = DISP_Line2;
    unsigned long ulAmount = DataTrans.ulAmount;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (ulAmount > 0) {
        mmi_display((DISP_VAlign)(dispLine++), DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
    }

    mmi_display((DISP_VAlign)(dispLine++), 0, "�������ѻ�����");
    if (1 == bPinTryCnt) {
        mmi_display((DISP_VAlign)(dispLine++), 0, "����������");
    }
    else {
        mmi_display((DISP_VAlign)(dispLine++), 0, "��ֿ�����������");
    }
    mmi_display((DISP_VAlign)(dispLine--), 0, "�������밴[ȷ�ϼ�]");
    return EMV_UTIL_InputOffCipherPinPwd((DISP_VAlign)(dispLine), 0, bPinByPass, bVerifyPinTryCnt, pVerifyResult, 60);
}

///< EMV�ں˵���-->��������
int EMV_TransOnline(void)
{
    int iRet = SUCCESS;

    ///< ��ȡ����Ϣ
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

    ///< ��������
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

