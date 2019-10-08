
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
#include "applib_def.h"
#include "applib_tools.h"
#include "mmi_commu.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "uFile.h"

#include "trans.h"
#include "iso8583_config.h"
#include "secretKey.h"

#include "Emv_DownParam.h"
#include "Emv_Utile.h"
#include "Emv_Trans.h"

#define DEBUG_TRANS_ONLINE      0
#if DEBUG_TRANS_ONLINE
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "trans_online.c"
#endif

extern char *trans_GetTransName(int transType);
static int transOnline_NormalCommon_pack(tsTransData *pTransData);

#define COMM_MAX_LEN    2*1024
static unsigned char g_sendBuff[COMM_MAX_LEN];
static unsigned char g_recvBuff[COMM_MAX_LEN];
static unsigned char g_tempBuff[COMM_MAX_LEN];
static unsigned char g_buff[1024];

typedef struct
{
    unsigned char drvType[2];           //设备类型
    unsigned char serialNo[50+1];       //终端硬件序列号
    unsigned char randomFactor[10+1];   //加密随机因子
    unsigned char mac[8];               //硬件序列号密文数据
    unsigned char appVar[8];            //应用程序版本号
}tsBit59TagA2;


static const char *iotx_ca_crt = \
{
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIIDxzCCAq+gAwIBAgIJANQeF2dWg9WEMA0GCSqGSIb3DQEBBQUAMHoxCzAJBgNV\r\n" \
    "BAYTAklOMQswCQYDVQQIDAJLQTEMMAoGA1UEBwwDQkFOMQ8wDQYDVQQKDAZORVdO\r\n" \
    "RVQxDDAKBgNVBAsMA05TVDEPMA0GA1UEAwwGdGVzdGFnMSAwHgYJKoZIhvcNAQkB\r\n" \
    "FhF0ZXN0YWdAbmV3bmV0LmNvbTAeFw0xNTA5MjIwNjU1MTNaFw0xODA5MjEwNjU1\r\n" \
    "MTNaMHoxCzAJBgNVBAYTAklOMQswCQYDVQQIDAJLQTEMMAoGA1UEBwwDQkFOMQ8w\r\n" \
    "DQYDVQQKDAZORVdORVQxDDAKBgNVBAsMA05TVDEPMA0GA1UEAwwGdGVzdGFnMSAw\r\n" \
    "HgYJKoZIhvcNAQkBFhF0ZXN0YWdAbmV3bmV0LmNvbTCCASIwDQYJKoZIhvcNAQEB\r\n" \
    "BQADggEPADCCAQoCggEBAMMdsjZZI//rruZ4KS2/EYxBel4USSQABLoxlkr0r92s\r\n" \
    "ZqQFeR+poZwedYyv/prQ5TKqYpjfSsiRLgmBc/kbzLK1dYR0KoKvXcnlnNckqkFZ\r\n" \
    "OUdONM2R+g4YA5yiPnM3jAh6056a+yK+I2k2JIrI/CORT60QduzqXAWZ6lG6d2GQ\r\n" \
    "BkNRzjOmKpIEQObnRWZAy+9pPmHeqcrsd0RC6v8zPl5XFrA2UeM9gw0eNXUY+gwb\r\n" \
    "sRLfuYLDejwbmKlb6PtCxrIckIHU5WgFdrqb2WNdU1cwIYaMGLhgNeZgJicwznuh\r\n" \
    "8wxMXaOPUB71dCSg3syzIMbHgW7PSZ8+ri15pObVotMCAwEAAaNQME4wHQYDVR0O\r\n" \
    "BBYEFCKN3/HDTmkrQFhqt/3QcBoJ/2W8MB8GA1UdIwQYMBaAFCKN3/HDTmkrQFhq\r\n" \
    "t/3QcBoJ/2W8MAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQADggEBABYt2GJ5\r\n" \
    "P0HtCfKj4E3dtk/L9OzzDHmp7TDt1265JPpJ7DfF8we9HG+ZNFETJvlar07pP0vy\r\n" \
    "t4/w6Q1KfA8p52Y9BSRvZltoW+SfUNRD96cHm2O77HKeiYcWOHB9CqxUqPsTv8xJ\r\n" \
    "GNd/i9Xw2lcbXEQeaCkOLfdCo2ZVcTReNW9gazTAg4ED+sbQWySMViJwEyhGDpPT\r\n" \
    "Zuu/Sip6Sux2th+s/PSMQFkFmK6Pt/NcL4HUzi51y49r1sxb8ME2kZ4JQq+qMKzn\r\n" \
    "X7kkLE7ECdK2bc8R7rMQ7vttxHeFuyW+P687bD8bGPa/lppZrQ5c/lkVEKm8l7Nc\r\n" \
    "witOy/5bPeoxTPE=\r\n"
    "-----END CERTIFICATE-----"
};


/**
 * @brief init 8583 data and clear data cache
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_Init8583(void)
{
    iso8583_SetISODef(&sIsoDef, SecretKey_MacECB);
    return ISO8583_Clear();
}

void transOnline_http_pack(unsigned char *pInData, unsigned short usInLen, unsigned short *pusOutLen)
{
    unsigned int offset;
    char *pBuf = (char *)g_tempBuff;

    memset(g_tempBuff, 0, sizeof(g_tempBuff));
    offset = 0;
    sprintf(&pBuf[offset], "POST %s %s\r\n", "/mjc/webtrans/VPB_lb", "HTTP/1.1");
    offset = strlen(pBuf);
    sprintf(&pBuf[offset], "HOST:%s:%d\r\n", DataCommu.host, DataCommu.port);
    offset = strlen(pBuf);
    sprintf(&pBuf[offset], "User-Agent:%s\r\n", "Donjin Http 0.1");
    offset = strlen(pBuf);

    sprintf(&pBuf[offset], "Cache-Control:%s\r\n", "no-cache");
    offset = strlen(pBuf);

    sprintf(&pBuf[offset], "Content-Type:%s\r\n", "x-ISO-TPDU/x-auth");
    offset = strlen(pBuf);

    sprintf(&pBuf[offset], "Accept:%s\r\n", "*/*");
    offset = strlen(pBuf);

    sprintf(&pBuf[offset], "Content-Length:%d\r\n", usInLen);
    offset = strlen(pBuf);

    sprintf(&pBuf[offset], "\r\n");
    offset = strlen(pBuf);

    memcpy(&pBuf[offset], pInData, usInLen);
    offset += usInLen;

    memset(g_sendBuff, 0, sizeof(g_sendBuff));
    memcpy(g_sendBuff, pBuf, offset);
    *pusOutLen = offset;
}

/* 不区分大小写的strstr */
char *strncasestr(char *str, char *sub)
{
    if(!str || !sub)
        return NULL;

    int len = strlen(sub);
    if (len == 0)
    {
        return NULL;
    }

    while (*str)
    {
        if (strncasecmp(str, sub, len) == 0)
        {
            return str;
        }
        ++str;
    }
    return NULL;
}

int transOnline_http_unpack(unsigned char *pInData, unsigned short *pOutOffset)
{
    char *str = (char *)pInData;
    char *start = (char *)pInData;
    char *p = NULL;

    p = strncasestr(str, "\r\n\r\n");
    if (p != NULL) {
        *pOutOffset = (p - start) + 4;
        return SUCCESS;
    }
    return ERR_DATA_INVALID;
}

/**
 * @brief data send and recv
 * @param pInData [in] data in
 * @param usInLen [in] data in len
 * @param pOutData [out] out data
 * @param pusOutLen [out] out data len
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_socketSendRev(unsigned char *pInData, unsigned short usInLen, unsigned char *pOutData, unsigned short *pusOutLen)
{
    int iRet = COMMU_RET_OK;
    unsigned int offset, uiI;
    COMMU_PARA ComuPara;

#if DEBUG_TRANS_ONLINE
    logger_serial_dump_buff("Send Data:", pInData, usInLen);
#endif

    memset(&ComuPara, 0x00, sizeof(ComuPara));
    if (DataCommu.sslEnable) {
        ComuPara.commu_mode = COMMU_SSL_SOCKET;
        ComuPara.cacrt_para.cacrt_len = strlen(iotx_ca_crt)+1;
        ComuPara.cacrt_para.p_cacrt = iotx_ca_crt;
    }
    else {
        ComuPara.commu_mode = COMMU_SOCKET;
    }
    ComuPara.is_auto_switch_net = 0;
    ComuPara.commu_timeout = DataConstant.recvTimeout;
    ComuPara.socket_para.socket_type = TCP_SOCKET;
    ComuPara.socket_para.addr_type = IP_ADDR;
    strcpy(ComuPara.server_para.host, DataCommu.host);
    ComuPara.server_para.port = DataCommu.port;

    iRet = commu_set_para(&ComuPara);
    if (SUCCESS != iRet) {
        return ERR_COMMU_PARAM;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, AMSG_ConnectingHost);
    mmi_display(DISP_Line3, 0, AMSG_PleaseWait);
    iRet = commu_connect();
    if (SUCCESS != iRet) {
        iRet = ERR_COMMU_CONNECT;
        goto END;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, AMSG_HostConnected);
    mmi_display(DISP_Line3, 0, AMSG_SendingData);
    mmi_display(DISP_Line4, 0, AMSG_PleaseWait);
    iRet = commu_send(NULL, (const char *)pInData, usInLen);
    if (SUCCESS != iRet) {
        iRet = ERR_COMMU_SEND;
        goto END;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line2, 0, AMSG_HostConnected);
    mmi_display(DISP_Line3, 0, AMSG_ReceivingData);
    mmi_display(DISP_Line4, 0, AMSG_PleaseWait);
    mmi_displayTimerStart(DISP_Line4, 12, 1, DataConstant.recvTimeout);

    offset = 0;
    for (uiI = 0; uiI < 2; uiI++)
    {
        *pusOutLen = 0;
        iRet = commu_recv((char *)&pOutData[offset], pusOutLen, COMM_MAX_LEN);
        if (SUCCESS != iRet) {
            iRet = ERR_COMMU_RECV;
            break;
        }

        if (SUCCESS == iRet) {
            offset += *pusOutLen;
            if (*pusOutLen <= 2) {
                iRet = ERR_COMMU_RECV;
                continue;
            }
            break;
        }
    }
    mmi_displayTimerStop();

    if (SUCCESS == iRet) {
        *pusOutLen = offset;
    }

END:
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (SUCCESS == iRet) {
        mmi_display(DISP_Line2, 0, AMSG_Received);
    }
    mmi_display(DISP_Line3, 0, AMSG_Processing);
    mmi_display(DISP_Line4, 0, AMSG_PleaseWait);

    commu_disconnect();

//    if (iRet != SUCCESS) {
//        iRet = ERR_SOCKET;
//    }

#if DEBUG_TRANS_ONLINE
    if (iRet == SUCCESS) {
        logger_serial_dump_buff("Recv Data:", pOutData, *pusOutLen);
    }
#endif
    return iRet;
}

/**
 * @brief pack socket data
 * @param pInData [in] data in
 * @param usInLen [in] data in len
 * @param pOutData [out] out data
 * @param pusOutLen [out] out data len
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_DataPack_TCPIP(unsigned char *pInData, unsigned short usInLen, unsigned char *pOutData, unsigned short *usOutLen)
{
    int iRet = SUCCESS;
    unsigned char packHead[13];
    unsigned long usOffSet = 0;

    usOffSet = 0;
    ///< len
    usOffSet += 2;
    ///< TPDU
    memcpy(&pOutData[usOffSet], DataConstant.tpdu, TPDU_LEN);
    usOffSet += TPDU_LEN;
    ///< pack head
    memset(packHead, 0x30, sizeof(packHead));
    memcpy(&packHead[0], "60", 2);
    memcpy(&packHead[2], "32", 2);
    packHead[4] = '0';
    memcpy(&packHead[6], BCTCVER, 6);
    tools_asc_bcd(&pOutData[usOffSet], 6, packHead, 12);
    usOffSet += 6;
    ///< pack data
    memcpy(&pOutData[usOffSet], pInData, usInLen);
    usOffSet += usInLen;

    ///< pack data len
    usOffSet -= 2;
    tools_long_hex(&pOutData[0], 2, &usOffSet);
    usOffSet += 2;

    *usOutLen = usOffSet;

    return iRet;
}

/**
 * @brief upack socket data
 * @param pInData [in] data in
 * @param usInLen [in] data in len
 * @param pOutData [out] out data
 * @param pusOutLen [out] out data len
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_DataUPack_TCPIP(unsigned char *pInData, unsigned short usInLen, unsigned char *pOutData, unsigned short *usOutLen)
{
    int iRet = SUCCESS;
    unsigned char packHead[6];
    unsigned int usDataLen = 0;
    unsigned int usOffSet = 0;

    if(usInLen < (TPDU_LEN + 2) || usInLen > COMM_MAX_LEN) {
        return ERR_DATA_OVERFLOW;
    }

    usOffSet = 0;
    usDataLen = usInLen;
    if (SUCCESS == iRet)
    {
        ///< first byte of APTU
        if(pInData[usOffSet] != 0x60 && pInData[usOffSet] != 0x80)
        {
            usOffSet += 2;
        }

        usOffSet += TPDU_LEN;   ///< TPDU

        memset(packHead, 0, sizeof(packHead));
        memcpy(packHead, &pInData[usOffSet], 6);
        usOffSet += 6;          ///< pack head
        if (usDataLen > usInLen) {
            return ERR_DATA_INVALID;
        }

        *usOutLen = usDataLen - usOffSet;
        memcpy(pOutData, &pInData[usOffSet], *usOutLen);
#if DEBUG_TRANS_ONLINE
        LOGD((char *)">>>packHead:%02x", packHead[2]);
#endif
        DataChange.packgeHeadEve = packHead[2]&0x0F;
        UFile_WriteFileIndexOf(DB_Change);
    }
    return iRet;
}

/**
 * @brief pack data and send && recv data and upack data
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_SendRev(void)
{
    int iRet = SUCCESS;
    unsigned short len;
    unsigned short sendLen;
    unsigned short offset = 0;
    unsigned char respNo[4] = {0};

    ///< 8583 data package
    if (SUCCESS == iRet) {
        len = 0;
        memset(g_tempBuff, 0, sizeof(g_tempBuff));
        iRet = ISO8583_Pack(g_tempBuff, &len);
    }

    ///< tcp data package
    if (SUCCESS == iRet) {
        sendLen = 0;
        memset(g_sendBuff, 0, sizeof(g_sendBuff));
        iRet = transOnline_DataPack_TCPIP(g_tempBuff, len, g_sendBuff, &sendLen);
    }

    if (SUCCESS == iRet && DataCommu.sslEnable) {
        transOnline_http_pack(g_sendBuff, sendLen, &sendLen);
    }

    ///< send data and recv data
    if (SUCCESS == iRet) {
        len = 0;
        memset(g_tempBuff, 0, sizeof(g_tempBuff));
        iRet = transOnline_socketSendRev(g_sendBuff, sendLen, g_tempBuff, &len);
    }

    if (SUCCESS == iRet && DataCommu.sslEnable) {
        if ((iRet = transOnline_http_unpack(g_tempBuff, &offset)) == SUCCESS) {
            len -= offset;
#if DEBUG_TRANS_ONLINE
            logger_serial_dump_buff("++Data:", &g_tempBuff[offset], len);
#endif
        }
    }

    ///< tcp data upackage
    if (SUCCESS == iRet) {
        sendLen = 0;
        memset(g_recvBuff, 0, sizeof(g_recvBuff));
        iRet = transOnline_DataUPack_TCPIP(&g_tempBuff[offset], len, g_recvBuff, &sendLen);
    }

    ///< 8583 data upackage
    if (SUCCESS == iRet) {
        iRet = ISO8583_Unpack(g_recvBuff);
        if (ERR_MAC == iRet) {
            ///< 先判断39域
            memset(respNo, 0, sizeof(respNo));
            len = 0;
            if (SUCCESS == ISO8583_GetBit(39, respNo, &len))
            {
                ///< 先判断冲正，非正常结果返回不校验MAC
                if (((TRANS_REVERSAL == ExtraData.transType)
                    && memcmp(respNo, "00", 2)
                    && memcmp(respNo, "12", 2)
                    && memcmp(respNo, "25", 2))
                    ///< 返回A0则不继续计算返回MAC
                    || (!memcmp(respNo, "A0", 2)))
                {
                    iRet = SUCCESS;
                }
            }
        }
    }

#if DEBUG_TRANS_ONLINE
    LOGD((char *)"[%5d]===>iRet:%x", __LINE__, iRet);
#endif

    return iRet;
}

static void transOnline_Bit59TlvAppend(const char* tag,
                                       unsigned char* inData,
                                       unsigned short uiLen,
                                       unsigned char* outData,
                                       unsigned short* uiOutLen)
{
    unsigned char tagData[256];
    unsigned int  tagLen = 0;

    memset(tagData, 0, sizeof(tagData));
    memcpy(&tagData[tagLen], tag, 2);
    tagLen += 2;
    tools_long_asc(&tagData[tagLen], 3, &uiLen);
    tagLen += 3;
    memcpy(&tagData[tagLen], inData, uiLen);
    tagLen += uiLen;
    memcpy(outData, tagData, tagLen);
    *uiOutLen += tagLen;
}

static void transOnline_Bit59TagA2_GetData(tsBit59TagA2 *pBit59TagA2)
{
    unsigned char mKEY[16+1] = {"1234567890123456"};
    unsigned char mBuf[400];
    unsigned short len, offset;

    memset(pBit59TagA2, 0x00, sizeof(tsBit59TagA2));
    //设备类型 AN2(01：ATM, 02：传统POS, 03：MPOS, 04：智能POS)
    memcpy(pBit59TagA2->drvType, "02", 2);

    //终端硬件序列号 ANS…50
    memcpy(&pBit59TagA2->serialNo[0], ExtraData.serialNo, strlen((char *)ExtraData.serialNo));
    //加密随机因子 AN…10 (取值说明：银行卡交易采用2域卡号后6位； 扫码付交易采用C2B码后6位)
    memset(mBuf, 0, sizeof(mBuf));
#if 1 //增加扫码时,可打开修改
    if (InputMode_Scan == DataTrans.cardInputType)
    {
        memcpy(mBuf, DataTrans.ScanCodeC2B, strlen((char *)DataTrans.ScanCodeC2B));
        memcpy(pBit59TagA2->randomFactor, &mBuf[max(strlen((char *)DataTrans.ScanCodeC2B)-6, 0)], 6);
    }
    else
#endif
    {
        tools_bcd_asc(mBuf, DataTrans.sourceAcc, DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
        memcpy(pBit59TagA2->randomFactor, &mBuf[DataTrans.sourceAccLen-6], 6);
    }

#if DEBUG_TRANS_ONLINE
    LOGD("\n(%4d)mBuf:%s\n", __LINE__, mBuf);
    LOGD("\n(%4d)pF59TagA2->randomFactor:%s\n", __LINE__, pBit59TagA2->randomFactor);
#endif
    //硬件序列号密文数据 8字节(B64)[初始数据:硬件序列号+加密随机因子]
    len = 0;
    offset = 0;
    memset(mBuf, 0, sizeof(mBuf));
    //---
    len = strlen((char *)pBit59TagA2->serialNo);
    memcpy(&mBuf[offset], pBit59TagA2->serialNo, len);
    offset += len;
    //---
    len = strlen((char *)pBit59TagA2->randomFactor);
    memcpy(&mBuf[offset], pBit59TagA2->randomFactor, len);
    offset += len;
    len = offset;
    SecretKey_Bit59_CalcMAC(mBuf, len, mKEY, pBit59TagA2->mac);

    //应用程序版本号 ANS8
    sprintf((char *)pBit59TagA2->appVar, "%-8s", BCTCVER);
}

int transOnline_Bit59_pack(void)
{
    int iRet = SUCCESS;
    unsigned char stBuff[256];
    unsigned short uiOffset = 0;
    int iLen = 0;
    tsBit59TagA2 bit59TagA2;

    memset(g_buff, 0, sizeof(g_buff));
    memset(&bit59TagA2, 0x00, sizeof(bit59TagA2));
    transOnline_Bit59TagA2_GetData(&bit59TagA2);
    /*----------------------------------------------------------------------------*/
    uiOffset = 0;
    memset(stBuff, 0, sizeof(stBuff));
    //设备类型 AN2(01：ATM, 02：传统POS, 03：MPOS, 04：智能POS)
    transOnline_Bit59TlvAppend("01", bit59TagA2.drvType, 2, &stBuff[uiOffset], &uiOffset);
    //终端硬件序列号 ANS…50
    transOnline_Bit59TlvAppend("02", bit59TagA2.serialNo, strlen((char *)bit59TagA2.serialNo), &stBuff[uiOffset], &uiOffset);
    //加密随机因子 AN…10 (取值说明：银行卡交易采用2域卡号后6位； 扫码付交易采用C2B码后6位)
    transOnline_Bit59TlvAppend("03", bit59TagA2.randomFactor, strlen((char *)bit59TagA2.randomFactor), &stBuff[uiOffset], &uiOffset);
    //硬件序列号密文数据 8字节(B64)
    if (memcmp(bit59TagA2.mac, "\x00\x00\x00\x00\x00\x00\x00\x00", 8)) {
        transOnline_Bit59TlvAppend("04", bit59TagA2.mac, 8, &stBuff[uiOffset], &uiOffset);
    }
    //应用程序版本号 ANS8
    transOnline_Bit59TlvAppend("05", bit59TagA2.appVar, 8, &stBuff[uiOffset], &uiOffset);
    /*----------------------------------------------------------------------------*/
    transOnline_Bit59TlvAppend("A2", stBuff, uiOffset, g_buff, &iLen);

    ///< add scan
    if (TRANS_SALE == ExtraData.transType && InputMode_Scan == DataTrans.cardInputType
     && strlen((const char *)DataTrans.ScanCodeC2B))
    {
        uiOffset = strlen((const char *)DataTrans.ScanCodeC2B);

        memset(stBuff, 0, sizeof(stBuff));
        memcpy(stBuff, DataTrans.ScanCodeC2B, uiOffset);

        ///< TagA3扫码付信息数据:变长350个字节，目前使用19位C2B码
        transOnline_Bit59TlvAppend("A3", stBuff, uiOffset, &g_buff[iLen], &iLen);
    }

    if (iLen > 0) {
        iRet = ISO8583_SetBit(59, g_buff, iLen);
    }
    return iRet;
}

int transOnline_Bit59_Unpack(const unsigned char *pucIn, unsigned short usInLen, unsigned char *pucOut)
{
    unsigned char bcTag[3] = {0}, asLen[3+1] = {0};
    unsigned short len = 0;
    unsigned char Tag = 0;
    unsigned short usLen = 0;
    int iRet = SUCCESS;

    if ((NULL == pucOut) || (NULL == pucIn) || (usInLen <= 0)) {
        return ERR_PARAM;
    }

#if DEBUG_TRANS_ONLINE
    LOGD("[%s,%d]field59 = %s\r\n", __FUNCTION__, __LINE__, pucIn);
#endif

    while (len < usInLen) {
        memset(bcTag, 0x00, sizeof(bcTag));
        vTwoOne(&pucIn[len], 2, bcTag);
        len += 2;
        Tag = bcTag[0];
    #if DEBUG_TRANS_ONLINE
        LOGD("[%s,%d]Tag = %02X\r\n", __FUNCTION__, __LINE__, Tag);
    #endif

        memset(asLen, 0x00, sizeof(asLen));
        memcpy(asLen, &pucIn[len], 3);
        len += 3;
        usLen = atoi((const char *)asLen);

        if (usLen > (999-5)) {
            iRet = ERR_PARAM;
            break;
        }

        //备注：需考虑平台返回数据有误的情况，判断数据长度的合法性,允许TL格式
        switch (Tag) {
            case 0xA1:
                if (usLen > 16) {
                    iRet = ERR_PARAM;
                } else {
                    ///< GM Pin
                }
                break;

            case 0xA2:
                if (usLen > 128) {
                    iRet = ERR_PARAM;
                } else {
                    ///< SN info
                }
                break;

            case 0xA3:
                if (usLen > 350) {
                    iRet = ERR_PARAM;
                } else {
                    ///< scan info
                }
                break;

            case 0xA4:
                if (usLen > 20) {
                    iRet = ERR_PARAM;
                } else {
                    ///< scan voucher code
                    memcpy(pucOut, &pucIn[len], usLen);
                }
                break;
            default:
                break;
        }

        ///< parse error
        if (SUCCESS != iRet) {
            break;
        }

        len += usLen;
        ///< success
        if (len == usInLen) {
            iRet = SUCCESS;
            break;
        }
    }

    return iRet;
}

//pack bit 60
int transOnline_Bit60_pack(const char *pTransType, const char *pNetInforCode, unsigned char ucTransType)
{
    int iLen = 0;
    unsigned char temp[30];

    /* Set Bit 60*/
    iLen = 0;
    memset(temp, 0, sizeof(temp));
    //交易类型码
    memcpy(&temp[iLen], pTransType, 2);
    iLen += 2;
    //批次号
    memcpy(&temp[iLen], DataChange.batchNumber, 6);
    iLen += 6;
    //网络管理信息码
    memcpy(&temp[iLen], pNetInforCode, 3);
    iLen += 3;
    ///< 终端读取能力,条件代码,支持部分扣款
    if ((ucTransType == TRANS_SALE)
        || (ucTransType == TRANS_VOID_SALE)
        || (ucTransType == TRANS_REFUND)) {
        memcpy(&temp[iLen], "601", 3);
        iLen += 3;
    }
    ///< 终端读取能力,条件代码
    else if ((ucTransType == TRANS_QUERY_BAL))
    {
        memcpy(&temp[iLen], "60", 2);
        iLen += 2;
    }

    return ISO8583_SetBit(60, temp, iLen);
}

/**
 * @brief common data pack
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_CommonPack(void)
{
    int iRet;

    ///< clear 8583 data cache
    iRet = transOnline_Init8583();
    if ((TRANS_LOADAID != ExtraData.transType)
        && (TRANS_LOADCAPK != ExtraData.transType)
        && (TRANS_LOADRF != ExtraData.transType)) {
        ///< Set Bit 11 trace number
        if (SUCCESS == iRet) {
            ISO8583_SetBit(11, DataTrans.traceNumber, 6);
        }
    }

    ///< Set Bit 41 terminal id
    if (SUCCESS == iRet) {
        ISO8583_SetBit(41, DataConstant.TID, 8);
    }

    ///< Set Bit 42  merchant id
    if (SUCCESS == iRet) {
        ISO8583_SetBit(42, DataConstant.MID, 15);
    }

    return iRet;
}

/**
 * @brief common data upack
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_CommonUPack(bool bManage)
{
    extern void trans_SetErrCode(const char* errCode);
    int iRet = SUCCESS;
    int len = 0;
    tsSysTime loc_time = {0};

    iRet = ISO8583_CompareBit(0);

    if (false == bManage)
    {
        ///< Get Bit 02
        if ((TRANS_REVERSAL != ExtraData.transType)
            && (!strlen((const char *)DataTrans.sourceAcc))) {
            len = 0;
            memset(g_buff, 0, sizeof(g_buff));
            if (ISO8583_GetBit(2, g_buff, &len) == SUCCESS)
            {
                DataTrans.sourceAccLen = len;
                memset(DataTrans.sourceAcc, 0, sizeof(DataTrans.sourceAcc));
                tools_asc_bcd(DataTrans.sourceAcc, (len + 1) / 2, g_buff, ((len + 1) / 2) * 2);
            }
        }

        ///< Get Bit 12
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(12, g_buff, &len) == SUCCESS)
        {
            memset(DataTrans.time, 0, sizeof(DataTrans.time));
            memcpy(DataTrans.time, g_buff, 6);
        }
        ///< Get Bit 13
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(13, g_buff, &len) == SUCCESS)
        {
            memset(&loc_time, 0, sizeof(loc_time));
            GetSysLocalTime(&loc_time);
            memset(DataTrans.date, 0, sizeof(DataTrans.date));
            snprintf((char *)DataTrans.date, sizeof(DataTrans.date), "%04d", loc_time.year);
            memcpy(&DataTrans.date[4], g_buff, 4);
        }

        ///< Get Bit 14 card expdate
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(14, g_buff, &len) == SUCCESS) {
            if ((4 == len)
                && (len == strlen((const char *)g_buff))
                && memcmp(g_buff, "0000", 4)) {
                memset(DataTrans.expiredDate, 0, sizeof(DataTrans.expiredDate));
                memcpy(DataTrans.expiredDate, g_buff, len);
            }
        }

        ///< Get Bit 15 settle date
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(15, g_buff, &len) == SUCCESS) {
            memset(DataTrans.settleDate, 0, sizeof(DataTrans.settleDate));
            memcpy(DataTrans.settleDate, g_buff, 4);
        }

        ///< Get Bit 32
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(32, g_buff, &len) == SUCCESS) {
            memcpy(DataTrans.bankID, g_buff, len);
        }

        ///< Get Bit 37 reference number
        if (SUCCESS == iRet) {
            len = 0;
            memset(g_buff, 0, sizeof(g_buff));
            if (ISO8583_GetBit(37, g_buff, &len) == SUCCESS) {
                if ((len > 0) && (strlen((const char *)g_buff) > 0)) {
                    memcpy(DataTrans.refNumber, g_buff, 12);
                }
            }
        }

        ///< Get Bit 38 authorization code
        if (SUCCESS == iRet) {
            len = 0;
            memset(g_buff, 0, sizeof(g_buff));
            if (ISO8583_GetBit(38, g_buff, &len) == SUCCESS) {
                if ((len > 0) && (strlen((const char *)g_buff) > 0)) {
                    memcpy(DataTrans.authCode, g_buff, 6);
                }
            }
        }

        ///< Get Bit 44
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(44, g_buff, &len) == SUCCESS) {
            memcpy(DataTrans.issuerID, &g_buff[0], 11);
            memcpy(DataTrans.acquereID, &g_buff[11], 11);
        }
    }

    if (SUCCESS == iRet && ExtraData.transType != TRANS_SETTLEMENT)
    {
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        iRet = ISO8583_GetBit(39, g_buff, &len);
        if (SUCCESS == iRet)
        {
            if (memcmp(g_buff, "00", 2))
            {
                ///< mac check error, need relogon
                if (!memcmp(g_buff, "A0", 2)) {
                    iRet = ERR_MAC;
                } else {
                    trans_SetErrCode((char *)g_buff);
                    iRet = ERR_HOSTCODE;

                    ///< reversal trans
                    if (TRANS_REVERSAL == ExtraData.transType) {
                        if (!memcmp(g_buff, "12", 2) || !memcmp(g_buff, "25", 2)) {
                            trans_SetErrCode("00");
                            iRet = SUCCESS;
                        }
                    }
                }

                ///< the need reversal trans need clear reversal
                if ((ERR_MAC == iRet) || (ERR_HOSTCODE == iRet)) {
                    if ((TRANS_SALE == ExtraData.transType)
                        || (TRANS_VOID_SALE == ExtraData.transType)) {
                        transUtil_ClearReversal();
                    }
                }

                //repeat trace no.
                if (!memcmp(g_buff, "94", 2))
                {
                    transUtil_IncreaseTraceNumber(50);
                }
            }
        }
    }

    if ((SUCCESS == iRet) && (false == bManage)) {
        iRet = ISO8583_CompareBit(11);
    }
    if (SUCCESS == iRet) {
        iRet = ISO8583_CompareBit(41);
    }
    if (SUCCESS == iRet) {
        iRet = ISO8583_CompareBit(42);
    }

    return iRet;
}

static void transOnline_DispDownParamPro(int iFlag, unsigned int currIndex, unsigned int count)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    if (!iFlag)
    {
#if DEBUG_TRANS_ONLINE
        LOGD("=================== %s%s ==================\n", title, "download search");
#endif
        mmi_display(DISP_Line2, DISP_HCenter, AMSG_DownloadSearch);
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_PleaseWait);
    }
    else if (iFlag == 1)
    {
#if DEBUG_TRANS_ONLINE
        LOGD("=================== %s%s[%d/%d] ==================\n", title, "downloading", currIndex, count);
#endif
        mmi_display(DISP_Line2, DISP_HCenter, "%s  %d/%d", AMSG_Downloading, currIndex, count);
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_PleaseWait);
    }
    else
    {
#if DEBUG_TRANS_ONLINE
        LOGD("=================== %s%s[%d/%d] ==================\n", title, "download end", currIndex, count);
#endif
        mmi_display(DISP_Line2, DISP_HCenter, AMSG_DownloadEnd);
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_PleaseWait);
    }
}

//下载公钥
int transOnline_DownCAPK(unsigned char bSM)
{
    extern void EMV_SaveCapkParam(void);

    int iRet = ERR_CANCEL;
    int iDownRet;
    int iFlag;      //0-查询, 1-下载, 2-下载结束
    int iDownIndex, iDownNum;
    int len = 0, iSendCount;
    CAPK_DOWN_INFO *pCapkInfo = NULL;

    /*_________________ 全量下载(暂时不断点下载)___________________*/
    ExtraData.transType = TRANS_LOADCAPK;

    ///< clear capk list
    if (EMV_DownParam_ClearGlobalData() < 0) {
        goto DO_PACK_ERR;
    }
    EMV_CapkList_Clear_App();

    iFlag = 0;
    iDownIndex = 0;
    iDownNum = 0;
DO_START:
    transOnline_DispDownParamPro(iFlag, iDownIndex+(iDownIndex == iDownNum ? 0 : 1), iDownNum);
    /*!< -------------------------------- pack data ----------------------------------------*/
    Sleep(500); ///< 延时显示下载信息
    iRet = transOnline_CommonPack();
    ///< Set Msg ID
    if (SUCCESS == iRet) {
        switch(iFlag)
        {
        case 0:     //查询
            ISO8583_SetMsgID("0820");
            break;
        default:
            ISO8583_SetMsgID("0800");
            break;
        }
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        switch(iFlag)
        {
        case 0:
            iRet = transOnline_Bit60_pack("00", bSM ? "373" : "372", ExtraData.transType);
            break;
        case 1:
            iRet = transOnline_Bit60_pack("00", "370", ExtraData.transType);
            break;
        default:
            iRet = transOnline_Bit60_pack("00", "371", ExtraData.transType);
            break;
        }
    }

    ///< Set Bit 62
    if (SUCCESS == iRet) {
        if (iFlag == 0)
        {
            len = 0;
            memset(g_buff, 0x00, sizeof(g_buff));
            sprintf((char *)g_buff, "1%02d", iDownNum);
            iRet = ISO8583_SetBit(62, g_buff, 3);
        }
        else if (iFlag == 1 && iDownNum)
        {
            pCapkInfo = EMV_CAPK_GetDownInfo(iDownIndex);

            len = 0;
            memset(g_buff, 0x00, sizeof(g_buff));
            memcpy(&g_buff[len], "\x9F\x06", 2);
            len += 2;
            g_buff[len] = 5;
            len += 1;
            memcpy(&g_buff[len], pCapkInfo ? pCapkInfo->RID : "00000", 5);
            len += 5;
            memcpy(&g_buff[len], "\x9F\x22", 2);
            len += 2;
            g_buff[len] = 1;
            len += 1;
            memcpy(&g_buff[len], pCapkInfo ? &pCapkInfo->CAPKI : "0", 1);
            len += 1;
            iRet = ISO8583_SetBit(62, g_buff, len);
        }
    }
    if (iRet != SUCCESS) {
        goto DO_PACK_ERR;
    }

    iSendCount = 0;
    while(1)
    {
        iRet = transOnline_SendRev();
        if (SUCCESS == iRet) {
            break;
        }
        iSendCount++;
        if (iSendCount > 2) {
            goto DO_EXIT;
        }
    }

    iRet = transOnline_CommonUPack(true);
    if (iRet != SUCCESS) {
        goto DO_EXIT;
    }

    switch(iFlag)
    {
    /*_____________________________ 查询返回 ________________________________*/
    case 0:     //查询
        len = 0;
        memset(g_buff, 0, sizeof(g_buff));
        ISO8583_GetBit(62, g_buff, &len);
        if (len < 1)
            goto DO_UNPACK_ERR;

#if DEBUG_TRANS_ONLINE
        LOGD("[%5d]>>>g_buff[0]:%x\n", __LINE__, g_buff[0]);
#endif
        switch(g_buff[0])
        {
        case '0':   //若没有后续包则退出
            goto DO_END;
        case '1':   //有参数,无继包,下参数
        case '3':
            iDownRet = EMV_CAPK_DownListUnpack(&g_buff[1], len - 1, &iDownNum);
#if DEBUG_TRANS_ONLINE
            LOGD("[%5d]>>>iDownRet:%d\n", __LINE__, iDownRet);
#endif
            break;
        case '2':   //有参数,有继包
            iDownRet = EMV_CAPK_DownListUnpack(&g_buff[1], len - 1, &iDownNum);
#if DEBUG_TRANS_ONLINE
            LOGD("[%5d]>>>iDownRet:%d\n", __LINE__, iDownRet);
#endif
            goto DO_START;
        default:
            goto DO_END;
        }
        break;
    /*_____________________________ 下载返回 ________________________________*/
    case 1:     //下载
        len = 0;
        memset(g_buff, 0x00, sizeof(g_buff));
        ISO8583_GetBit(62, g_buff, &len);
#if DEBUG_TRANS_ONLINE
        LOGD("[%5d]>>>g_buff[0]:%x", __LINE__, g_buff[0]);
#endif
        if (len > 0)
        {
            if (len > 1 && (g_buff[0] == '1'))
            {
                iDownRet = EMV_CAPK_DownUnpack(&g_buff[1], len - 1);
#if DEBUG_TRANS_ONLINE
                LOGD("[%s:%5d]>>>iDownRet:%d", __func__, __LINE__, iDownRet);
#endif
                if (iDownRet < 0) {
                    goto DO_UNPACK_ERR;
                }
            }
            iDownIndex++;
            if (iDownIndex < iDownNum)
            {
                goto DO_START;
            }
        }
        break;
    default:
        break;
    }

#if DEBUG_TRANS_ONLINE
    LOGD("iFlag = [%d],iDownIndex = [%d],iDownNum = [%d]",iFlag, (!iDownIndex ? 1 : iDownIndex), iDownNum);
#endif
    if (iFlag == 1 && iDownIndex && iDownIndex == iDownNum)
    {
        EMV_SaveCapkParam();
    }

    //下载结束
    if (iFlag < 2)
    {
        iFlag++;
        goto DO_START;
    }

DO_END:
    iRet = SUCCESS;
    goto DO_EXIT;

DO_PACK_ERR:
    iRet = ERR_DATA_PACK;
    goto DO_EXIT;

DO_UNPACK_ERR:
    iRet = ERR_DATA_UPACK;
    goto DO_EXIT;

DO_EXIT:
    ISO8583_Free();
    return iRet;
}

//IC参数(AID)下载
int transOnline_DownAID(void)
{
    extern void EMV_SaveAidParam(void);
    int iRet = ERR_CANCEL;
    int iDownRet;
    int iFlag;  //0-查询, 1-下载, 2-下载结束
    int iDownIndex, iDownNum;
    int len = 0, iSendCount;
    AID_DOWN_INFO *pAidInfo = NULL;

    /*_________________ 全量下载(暂时不断点下载)___________________*/
    ExtraData.transType = TRANS_LOADAID;

    ///< clear capk list
    if (EMV_DownParam_ClearGlobalData() < 0) {
        goto DO_PACK_ERR;
    }
    EMV_AidList_Clear_App();

    iFlag = 0;
    iDownIndex = 0;
    iDownNum = 0;
DO_START:
    transOnline_DispDownParamPro(iFlag, iDownIndex+(iDownIndex == iDownNum ? 0 : 1), iDownNum);
    /*!< -------------------------------- pack data ----------------------------------------*/
    Sleep(500); ///< 延时显示下载信息
    iRet = transOnline_CommonPack();
    ///< Set Msg ID
    if (SUCCESS == iRet) {
        switch(iFlag)
        {
        case 0:     //查询
            ISO8583_SetMsgID("0820");
            break;
        default:
            ISO8583_SetMsgID("0800");
            break;
        }
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        switch(iFlag)
        {
        case 0:
            iRet = transOnline_Bit60_pack("00", "382", ExtraData.transType);
            break;
        case 1:
            iRet = transOnline_Bit60_pack("00", "380", ExtraData.transType);
            break;
        default:
            iRet = transOnline_Bit60_pack("00", "381", ExtraData.transType);
            break;
        }
    }

    ///< Set Bit 62
    if (SUCCESS == iRet) {
        if (iFlag == 0)
        {
            len = 0;
            memset(g_buff, 0x00, sizeof(g_buff));
            sprintf((char *)g_buff, "1%02d", iDownNum);
            iRet = ISO8583_SetBit(62, g_buff, 3);
        }
        else if (iFlag == 1 && iDownNum)
        {
            pAidInfo = EMV_AID_GetDownInfo(iDownIndex);

            len = 0;
            memset(g_buff, 0x00, sizeof(g_buff));
            memcpy(&g_buff[len], "\x9F\x06", 2);
            len += 2;
            g_buff[len] = pAidInfo ? pAidInfo->ucLen : 0;
            len += 1;
            memcpy(&g_buff[len],
                   pAidInfo ? pAidInfo->aucAID : 0x00,
                   pAidInfo ? pAidInfo->ucLen : 0);

            len += pAidInfo ? pAidInfo->ucLen : 0;
            iRet = ISO8583_SetBit(62, g_buff, len);
        }
    }

    if (iRet != SUCCESS) {
        goto DO_PACK_ERR;
    }

    iSendCount = 0;
    while(1)
    {
        iRet = transOnline_SendRev();
        if (SUCCESS == iRet) {
            break;
        }
        iSendCount++;
        if (iSendCount > 2) {
            goto DO_EXIT;
        }
    }

    iRet = transOnline_CommonUPack(true);
    if (iRet != SUCCESS) {
        goto DO_EXIT;
    }

    switch(iFlag)
    {
    /*_____________________________ 查询返回 ________________________________*/
    case 0:
        len = 0;
        memset(g_buff, 0x00, sizeof(g_buff));
        ISO8583_GetBit(62, g_buff, &len);
        if (len < 1)
            goto DO_UNPACK_ERR;
#if DEBUG_TRANS_ONLINE
        LOGD("[%5d]>>>g_buff[0]:%x\n", __LINE__, g_buff[0]);
        logger_serial_dump_buff("AID 返回数据:", &g_buff[1], len - 1);
#endif
        switch(g_buff[0])
        {
        case '0':   //若没有后续包则退出
            goto DO_END;
        case '1':   //有参数,无继包,下参数
        case '3':
             iDownRet = EMV_AID_DownListUnpack(&g_buff[1], len - 1, &iDownNum);
#if DEBUG_TRANS_ONLINE
                LOGD("[%5d]>>>iDownRet:%d\n", __LINE__, iDownRet);
#endif
                if (iDownRet < 0) {
                    goto DO_UNPACK_ERR;
                }
            break;
        case '2':   //有参数,有继包
            iDownRet = EMV_AID_DownListUnpack(&g_buff[1], len - 1, &iDownNum);
#if DEBUG_TRANS_ONLINE
            LOGD("[%5d]>>>iDownRet:%d\n", __LINE__, iRet);
#endif
            goto DO_START;
        default:
            goto DO_END;
        }
        break;
    /*_____________________________ 下载返回 ________________________________*/
    case 1:
        len = 0;
        memset(g_buff, 0x00, sizeof(g_buff));
        ISO8583_GetBit(62, g_buff, &len);
#if DEBUG_TRANS_ONLINE
        LOGD("[%5d]>>>g_buff[0]:%x\n", __LINE__, g_buff[0]);
#endif
        if (len > 0)
        {
            if (len > 1 && (g_buff[0] == '1'))
            {
                iDownRet = EMV_AID_DownUnpack(&g_buff[1], len - 1);
#if DEBUG_TRANS_ONLINE
                LOGD("[%5d]>>>iDownRet:%d", __LINE__, iDownRet);
#endif
                if (iDownRet < 0) {
                    goto DO_UNPACK_ERR;
                }
            }

            iDownIndex++;
            if (iDownIndex < iDownNum)
            {
                goto DO_START;
            }
        }
        break;
    default:
        break;
    }

#if DEBUG_TRANS_ONLINE
    LOGD("iFlag = [%d],iDownIndex = [%d],iDownNum = [%d]",iFlag, (!iDownIndex ? 1 : iDownIndex), iDownNum);
#endif
    if (iFlag == 1 && iDownIndex && iDownIndex == iDownNum)
    {
#if DEBUG_TRANS_ONLINE
        LOGD("[%5d]>>>add aid:%d", __LINE__, iRet);
#endif
        EMV_SaveAidParam();
    }

    //下载结束
    if (iFlag < 2)
    {
        iFlag++;
        goto DO_START;
    }

DO_END:
    iRet = SUCCESS;
    goto DO_EXIT;

DO_PACK_ERR:
    iRet = ERR_DATA_PACK;
    goto DO_EXIT;

DO_UNPACK_ERR:
    iRet = ERR_DATA_UPACK;
    goto DO_EXIT;

DO_EXIT:
    ISO8583_Free();
    return iRet;
}

//非接业务参数下载
int transOnline_DownUntouchParam(void)
{
    int iRet = SUCCESS;
    unsigned char iFlag = 0;   //0-下载, 1-下载结束;
    int len = 0, iSendCount;

    ExtraData.transType = TRANS_LOADRF;

BEGIN:
    iRet = transOnline_CommonPack();
    ///< Set Msg ID
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0800");
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        switch(iFlag)
        {
        case 0:
            iRet = transOnline_Bit60_pack("00", "394", ExtraData.transType);
            break;
        default:
            iRet = transOnline_Bit60_pack("00", "395", ExtraData.transType);
            break;
        }
    }

    if (iRet != SUCCESS) {
        goto DO_PACK_ERR;
    }

    iSendCount = 0;
    while(1)
    {
        iRet = transOnline_SendRev();
        if (SUCCESS == iRet) {
            break;
        }
        iSendCount++;
        if (iSendCount > 2) {
            goto DO_EXIT;
        }
    }

    if (!iFlag && SUCCESS == iRet) {
        ///< Get Bit 62
        len = 0;
        memset(g_buff, 0x00, sizeof(g_buff));
        ISO8583_GetBit(62, g_buff, &len);
        if (len > 0) {
            iRet = EMV_Untouch_DownUnpack(g_buff, len);
        }
    }

    //下载结束
    if (iFlag == 0 && iRet == SUCCESS) {
        iFlag = 1;
        goto BEGIN;
    }

    iRet = SUCCESS;
    goto DO_EXIT;

DO_PACK_ERR:
    iRet = ERR_DATA_PACK;
    goto DO_EXIT;

DO_EXIT:
    ISO8583_Free();
    return iRet;
}

//参数下载
static int transOnline_DownParam(unsigned char packgeHeadEve)
{
    int iRet = SUCCESS;
    unsigned char mTransType = ExtraData.transType;

#if 1
    ///< AID下载
    ExtraData.transType = mTransType;
    if (SUCCESS == iRet) {
        //下载终端IC卡参数
        if (packgeHeadEve == 0x05 || !(DataChange.downFlag & DOWN_PARAM_AID))
        {
            iRet = transOnline_DownAID();
            if (SUCCESS == iRet) {
                DataChange.downFlag |= DOWN_PARAM_AID;
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }
#endif

#if 1
    ///< CAPK下载
    ExtraData.transType = mTransType;
    if (SUCCESS == iRet) {
        if (packgeHeadEve == 0x04 || !(DataChange.downFlag & DOWN_PARAM_CAPK))
        {
            iRet = transOnline_DownCAPK(DataConstant.bSM);
            if (SUCCESS == iRet) {
                DataChange.downFlag |= DOWN_PARAM_CAPK;
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }
#endif

#if 0
    //BIN表黑名单
    ExtraData.transType = mTransType;
    if (SUCCESS == iRet) {
        if (packgeHeadEve == 0x07 || DataSave.PosPar.bDownBIN)   //BIN表黑名单
        {
            iRet = TransOnline_DownBIN(0);
            if (iRet == APP_ERR_SUCCESS)
            {
                DataSave.PosPar.bDownBIN = 0;
                WRITE_FV(DataSave);
            }
        }
    }
#endif

#if 1
    ///< 双免参数下载
    ExtraData.transType = mTransType;
    if (SUCCESS == iRet) {
        if (packgeHeadEve == 0x09 || !(DataChange.downFlag & DOWN_PARAM_UNTOUCH))
        {
            iRet = transOnline_DownUntouchParam();
            if (SUCCESS == iRet) {
                DataChange.downFlag |= DOWN_PARAM_UNTOUCH;
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }
#endif

    ExtraData.transType = mTransType;

    commu_disconnect();
    return iRet;
}

/**
 * @brief logon on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_Logon(void)
{
    int iRet = SUCCESS;
    int iFileRet = SUCCESS;
    unsigned short mBufLen, uiOffset;
    tsSysTime datime;
    unsigned char flag = 0;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_CommonPack();
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0800");
    }

    ///< Set Bit 11 trace number
    if (SUCCESS == iRet) {
        ISO8583_DelBit(11);
        iRet = ISO8583_SetBit(11, DataChange.traceNumber, 6);
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(&g_buff[0], "00", 2);
        memcpy(&g_buff[2], DataChange.batchNumber, 6);
        if (DataConstant.encryptType == EncryptSingle) {
            memcpy(&g_buff[8], "001", 3);
        }
        else if (DataConstant.encryptType == EncryptDouble) {
            memcpy(&g_buff[8], "003", 3);
        }
        else {
            memcpy(&g_buff[8], "004", 3);
        }
        iRet = ISO8583_SetBit(60, g_buff, 11);
    }

    ///< Set Bit 62
    if (SUCCESS == iRet) {
        mBufLen = strlen((char *)ExtraData.serialNo);
        uiOffset = 0;
        memset(g_buff, 0, sizeof(g_buff));
        sprintf((char *)&g_buff[uiOffset], "Sequence No");
        uiOffset += 11;
        ///< len
        mBufLen += 4;
        tools_long_asc(&g_buff[uiOffset], 2, &mBufLen);
        mBufLen -= 4;
        uiOffset += 2;
        ///< certificate number
        sprintf((char *)&g_buff[uiOffset], CUP_CERTIFICATE_NO);
        uiOffset += 4;
        ///< DSN
        memcpy(&g_buff[uiOffset], ExtraData.serialNo, mBufLen);
        uiOffset += mBufLen;
        iRet = ISO8583_SetBit(62, g_buff, uiOffset);
    }

    ///< Set Bit 63
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memset(g_buff, 0x20, 3);
        memcpy(g_buff, DataChange.cashierNo, sizeof(DataChange.cashierNo));
        iRet = ISO8583_SetBit(63, g_buff, 3);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
    }
    if (SUCCESS != iRet) {
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(false))) {
        goto END;
    }

    ///< synchronize terminal date and time
    memset(&datime, 0, sizeof(tsSysTime));
    GetSysLocalTime(&datime);   ///< get current system date and time
    ///< Get Bit 12 <time>
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(12, g_buff, &mBufLen) == SUCCESS) {
        datime.hour = (unsigned short)tools_asc_long(&g_buff[0], 2);
        datime.min = (unsigned short)tools_asc_long(&g_buff[2], 2);
        datime.sec = (unsigned short)tools_asc_long(&g_buff[4], 2);
        flag = 1;
    }
    ///< Get Bit 13 <date>
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(13, g_buff, &mBufLen) == SUCCESS) {
        datime.mon = (unsigned short)tools_asc_long(&g_buff[0], 2);
        datime.day = (unsigned short)tools_asc_long(&g_buff[2], 2);
        flag = 1;
    }
    if (flag) {
        SetSysLocalTime(&datime);   ///< set system date and time
    }

    ///< Get Bit 62
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if ((iRet = ISO8583_GetBit(62, g_buff, &mBufLen)) == SUCCESS) {
        switch(DataConstant.encryptType)
        {
        case EncryptSingle:
            iRet = SecretKey_SaveNewKey(EncryptSingle, g_buff, mBufLen);
            break;
        case EncryptDouble:
            iRet = SecretKey_SaveNewKey(EncryptDouble, g_buff, mBufLen);
            break;
        default:
            iRet = SecretKey_SaveNewKey(EncryptDoubleTDK, g_buff, mBufLen);
            break;
        }
    }
    DataChange.isStoreKeyDownRight = (iRet == SUCCESS ? 0 : 1);
    iFileRet = UFile_WriteFileIndexOf(DB_Change);
    if (iFileRet != SUCCESS)
        iRet = iFileRet;

    ///< batch number
    if (SUCCESS == iRet) {
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        if (ISO8583_GetBit(60, g_buff, &mBufLen) == SUCCESS) {
            iRet = transUtil_UpdataBatchNumber((const char *)&g_buff[2]);
        }
    }

END:
    ISO8583_Free();
    return iRet;
}

/**
 * @brief logoff on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_Logoff(void)
{
    int iRet = SUCCESS;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_CommonPack();
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0820");
    }

    ///< Set Bit 11 trace number
    if (SUCCESS == iRet) {
        ISO8583_DelBit(11);
        iRet = ISO8583_SetBit(11, DataChange.traceNumber, 6);
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(&g_buff[0], "00", 2);
        memcpy(&g_buff[2], DataChange.batchNumber, 6);
        memcpy(&g_buff[8], "002", 3);
        iRet = ISO8583_SetBit(60, g_buff, 11);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_CommonUPack(true);
    }

    ISO8583_Free();
    return iRet;
}

static inline int transOnline_NormalCommon_pack(tsTransData *pTransData)
{
    int iRet = SUCCESS;
    unsigned short mBufLen;
    unsigned char bPack2Track = false;

    iRet = transOnline_CommonPack();
    ///< Set Bit 04
    if (SUCCESS == iRet && pTransData->ulAmount > 0) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_long_asc(g_buff, 12, &pTransData->ulAmount);
        iRet = ISO8583_SetBit(4, g_buff, 12);
    }

    ///< Set Bit 14
    if(SUCCESS == iRet && strlen((char *)pTransData->expiredDate)) {
        iRet = ISO8583_SetBit(14, pTransData->expiredDate, 4);
    }

    ///< Set Bit 22
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "0000", 4);
        switch(pTransData->cardInputType)
        {
        case InputMode_Manual:
            g_buff[1] = '1';
            break;
        case InputMode_Mag:
            g_buff[1] = '2';
            break;
        case InputMode_Scan:
            g_buff[1] = '3';
            break;
        case InputMode_ICC:
            g_buff[1] = '5';
            break;
        case InputMode_QICC:
            g_buff[1] = '7';
            break;
        default:
            g_buff[1] = '1';
            break;
        }
        g_buff[2] = (ExtraData.inputPINLen > 0) ? '1' : '2';
        iRet = ISO8583_SetBit(22, g_buff, 3);
    }

    ///< Set Bit 23
    if (SUCCESS == iRet && strlen((char *)pTransData->panSeq)) {
        memset(g_buff, 0, sizeof(g_buff));
        memset(g_buff, 0x30, 4);
        memcpy(&g_buff[2], pTransData->panSeq, 2);
        iRet = ISO8583_SetBit(23, g_buff, 4);
    }

    ///< Set Bit 35
    if (SUCCESS == iRet && ExtraData.iso2Len)
    {
        mBufLen = ExtraData.iso2Len;
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, ExtraData.iso2, ExtraData.iso2Len);
        if (EncryptDoubleTDK == DataConstant.encryptType) {
            iRet = SecretKey_EcryptTrack(g_buff, ExtraData.iso2Len, &mBufLen);
        }

        if (SUCCESS == iRet) {
            bPack2Track = true;
            iRet = ISO8583_SetBit(35, g_buff, mBufLen);
        }
    }

    ///< Set Bit 36
    if (SUCCESS == iRet && ExtraData.iso3Len)
    {
        mBufLen = ExtraData.iso3Len;
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, ExtraData.iso3, ExtraData.iso3Len);
        if (EncryptDoubleTDK == DataConstant.encryptType) {
            iRet = SecretKey_EcryptTrack(g_buff, ExtraData.iso3Len, &mBufLen);
        }

        if (SUCCESS == iRet) {
            bPack2Track = true;
            iRet = ISO8583_SetBit(36, g_buff, mBufLen);
        }
    }

    if(ExtraData.inputPINLen)
    {
        ///< Set Bit 26
        if (SUCCESS == iRet) {
            iRet = ISO8583_SetBit(26, (unsigned char *)"12", 2);
        }

        ///< Set bit 52
        if (SUCCESS == iRet) {
            iRet = ISO8583_SetBit(52, ExtraData.PINData, 8);
        }
    }

    ///< Set Bit 49
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(49, DataConstant.currencyCode, 3);
    }

    ///< Set Bit 53
    if (SUCCESS == iRet && (ExtraData.inputPINLen || true == bPack2Track)) {
        memset(g_buff, 0, sizeof(g_buff));
        memset(g_buff, '0', 16);
        g_buff[0] = ExtraData.inputPINLen ? '2' : '0';
        switch(DataConstant.encryptType)
        {
        case EncryptSingle:
            memcpy(&g_buff[1], "00", 2);
            break;
        case EncryptDouble:
            memcpy(&g_buff[1], "60", 2);
            break;
        default:
            memcpy(&g_buff[1], bPack2Track == true ? "61" : "60", 2);
            break;
        }
        iRet = ISO8583_SetBit(53, g_buff, 16);
    }

    ///< Set Bit 64
    if (SUCCESS == iRet) {
        ISO8583_SetBit(64, "00000000", 8);
    }

    return iRet;
}

/**
 * @brief query balance on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_QueryBal(void)
{
    int iRet = SUCCESS;
    int mBufLen;
    tsTransData *pTransData = &DataTrans;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_NormalCommon_pack(pTransData);
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0200");
    }

    ///< Set Bit 03
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "310000", 6);
//        g_buff[2] = DataTrans.sourceAccType;
        iRet = ISO8583_SetBit(3, g_buff, 6);
    }

    ///< Set Bit 02
    if (SUCCESS == iRet
      && DataTrans.cardInputType != InputMode_Mag
      && DataTrans.sourceAccLen) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_bcd_asc(g_buff, DataTrans.sourceAcc,
                      DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
        iRet = ISO8583_SetBit(2, g_buff, DataTrans.sourceAccLen);
    }

    ///< Set Bit 25
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(25, "00", 2);
    }

    ///< Set Bit 55
    if (SUCCESS == iRet
    && (InputMode_ICC == DataTrans.cardInputType || InputMode_QICC == DataTrans.cardInputType)) {
        memset(g_buff, 0, sizeof(g_buff));
        mBufLen = sizeof(g_buff);
        EMV_GetField55(1, g_buff, sizeof(g_buff), (unsigned int *)&mBufLen);
        iRet = ISO8583_SetBit(55, g_buff, mBufLen);
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        iRet = transOnline_Bit60_pack("01", "000", ExtraData.transType);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
    }
    if (SUCCESS != iRet) {
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(false))) {
//        goto END;
    }

    ///< Get Bit 54
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(54, g_buff, &mBufLen) == SUCCESS) {
        memcpy(ExtraData.balanceInfo, g_buff, min(mBufLen, sizeof(ExtraData.balanceInfo)));
#if DEBUG_TRANS_ONLINE
        LOGD((char *)">>>balanceInfo:%s", ExtraData.balanceInfo);
#endif
    }

    ///< Get Bit 55
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(55, g_buff, &mBufLen) == SUCCESS) {
        EMV_UnpackField55(g_buff, mBufLen, g_tempBuff, sizeof(g_tempBuff));
    }

END:
    ISO8583_Free();
    return iRet;
}

/**
 * @brief  reversal data pack
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_ReversalPack(void)
{
    int iRet = SUCCESS;
    int iLen = 0;
    unsigned char temp[32] = {0};

    if ((iRet = ISO8583_ClearBackup()) != SUCCESS) {
        return iRet;
    }

    ///< Set MSG ID
    ISO8583_SetBackupBit(0, "0400", 4);

    ///< Set Bit 03
    ISO8583_CopyBitToBackup(3);

    ///< Set Bit 02
    ISO8583_CopyBitToBackup(2);

    ///< Set Bit 04
    ISO8583_CopyBitToBackup(4);

    ///< Set Bit 11
    ISO8583_CopyBitToBackup(11);

    ///< Set Bit 14
    ISO8583_CopyBitToBackup(14);

    ///< Set Bit 22
    ISO8583_CopyBitToBackup(22);

    ///< Set Bit 23
    ISO8583_CopyBitToBackup(23);

    ///< Set Bit 25
    ISO8583_CopyBitToBackup(25);

    /* Set Bit 38 授权标识应答码*/
    //原始交易有授权码时, 放在冲正发送时打包
    ISO8583_CopyBitToBackup(38);

    /* Set Bit 39 冲正原因*/
    //放在冲正发送时打包

    /// Set Bit 41
    ISO8583_CopyBitToBackup(41);

    ///< Set Bit 42
    ISO8583_CopyBitToBackup(42);

    ///< Set Bit 49
    ISO8583_CopyBitToBackup(49);

    ///< Set Bit 55
    if (((TRANS_SALE == ExtraData.transType))
        && ((InputMode_ICC == DataTrans.cardInputType)
            || (InputMode_QICC == DataTrans.cardInputType)))
    {
        iLen = sizeof(g_buff);
        memset(g_buff, 0, sizeof(g_buff));
        EMV_GetReversalField55(g_buff, sizeof(g_buff), (unsigned int *)&iLen);
        ISO8583_SetBackupBit(55, g_buff, iLen);
    }

    ///< Set Bit 59
    if ((TRANS_SALE == ExtraData.transType)
        && (InputMode_Scan == DataTrans.cardInputType)) {
        iLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        transOnline_Bit59TlvAppend("A3", DataTrans.ScanCodeC2B,
            strlen((const char *)DataTrans.ScanCodeC2B),
            &g_buff[iLen], &iLen);
        if (iLen > 0) {
            iRet = ISO8583_SetBackupBit(59, g_buff, iLen);
        }
    }

    ///< Set Bit 60
    ISO8583_CopyBitToBackup(60);

    ///< Set Bit 61
    if ((TRANS_VOID_SALE == ExtraData.transType)) {
        iLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        ISO8583_GetSendBit(61, g_buff, &iLen);
    #if DEBUG_TRANS_ONLINE
        LOGD("auth 61 field = %s, %d\r\n", g_buff, iLen);
    #endif
        ///< 上送原预授权完成请求或预授权撤销交易批次号和流水号
        iLen = 0;
        memset(temp, 0, sizeof(temp));
        iRet = ISO8583_GetSendBit(60, temp, &iLen);
        if ((SUCCESS == iRet) && (iLen > 0)) {
            memcpy(&g_buff[0], &temp[2], 6);
        } else {
            memcpy(&g_buff[0], DataChange.batchNumber, 6);
        }
        iLen = 0;
        memset(temp, 0, sizeof(temp));
        iRet = ISO8583_GetSendBit(11, temp, &iLen);
        if ((SUCCESS == iRet) && (iLen > 0)) {
            memcpy(&g_buff[6], temp, 6);
        } else {
            memcpy(&g_buff[6], DataTrans.traceNumber, 6);
        }
        ISO8583_SetBackupBit(61, g_buff, strlen((const char *)g_buff));
    }

    ///< save reverse data
    ISO8583_SaveBackup(DataReverse.data, &DataReverse.dataLen);
    iRet = transUtil_SaveReversal("98");

    return iRet;
}

/**
 * @brief  purchase on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_Sale(void)
{
    ///< add scan
    int iRet = SUCCESS;
    unsigned short mBufLen;
    tsTransData *pTransData = &DataTrans;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_NormalCommon_pack(pTransData);
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0200");
    }

    ///< Set Bit 03
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "000000", 6);
        iRet = ISO8583_SetBit(3, g_buff, 6);
    }

    ///< Set Bit 02
    if ((SUCCESS == iRet)
      && (InputMode_Mag != DataTrans.cardInputType)
      && (InputMode_Scan != DataTrans.cardInputType)
      && DataTrans.sourceAccLen) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_bcd_asc(g_buff, DataTrans.sourceAcc,
                      DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
        iRet = ISO8583_SetBit(2, g_buff, DataTrans.sourceAccLen);
    }

    ///< Set Bit 25
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(25, "00", 2);
    }

    ///< Set Bit 47
    if (SUCCESS == iRet) {
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(&g_buff[mBufLen], "\xF1", 1);
        mBufLen += 1;
        memcpy(&g_buff[mBufLen], "\x02", 1);
        mBufLen += 1;
        memcpy(&g_buff[mBufLen], "\x60\x00", 2);
        mBufLen += 2;
        ISO8583_SetBit(47, g_buff, mBufLen);
    }

    ///< Set Bit 55
    if ((SUCCESS == iRet)
        && ((InputMode_ICC == DataTrans.cardInputType)
            || (InputMode_QICC == DataTrans.cardInputType))) {
        mBufLen = sizeof(g_buff);
        EMV_GetField55(0, g_buff, sizeof(g_buff), &mBufLen);
        iRet = ISO8583_SetBit(55, g_buff, mBufLen);
    }

    ///< Set Bit 59
    if (SUCCESS == iRet) {
        iRet = transOnline_Bit59_pack();
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        iRet = transOnline_Bit60_pack("22", "000", ExtraData.transType);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_ReversalPack();
    }

    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
        ///< 未实际发送成功的交易，需清除冲正，降低冲正率
        if ((ERR_PARAM == iRet)
            || (ERR_DATA_PACK == iRet)
            || (ERR_COMMU_PARAM == iRet)
            || (ERR_COMMU_CONNECT == iRet)
            || (ERR_COMMU_SEND == iRet)) {
            ///< clear reversal
            transUtil_ClearReversal();
        }
    }
    if (SUCCESS != iRet) {
        ///< mac校验错更新冲正原因
        if (ERR_MAC == iRet) {
            transUtil_SaveReversal("A0");
        }
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(false))) {
//        goto END;
    }

    ///< Get Bit 55
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(55, g_buff, &mBufLen) == SUCCESS) {
        EMV_UnpackField55(g_buff, mBufLen, g_tempBuff, sizeof(g_tempBuff));
    }

    ///< Get Bit 59
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(59, g_buff, &mBufLen) == SUCCESS) {
        transOnline_Bit59_Unpack(g_buff, mBufLen, DataTrans.ascScanVoucherNo);
#if DEBUG_TRANS_ONLINE
        LOGD((char *)">>>scan voucher no.:%s\r\n", DataTrans.ascScanVoucherNo);
#endif
    }

END:
    ISO8583_Free();
    return iRet;
}

/**
 * @brief  cancel purchase on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_VoidSale(void)
{
    int iRet = SUCCESS;
    unsigned short mBufLen;
    tsTransData *pTransData = &DataTrans;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_NormalCommon_pack(pTransData);
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0200");
    }

    ///< Set Bit 03
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "200000", 6);
        //g_buff[2] = DataTrans.sourceAccType;
        iRet = ISO8583_SetBit(3, g_buff, 6);
    }

    ///< Set Bit 02
    if ((SUCCESS == iRet)
        && (InputMode_Scan != DataTrans.cardInputType)
        && DataTrans.sourceAccLen) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_bcd_asc(g_buff, DataTrans.sourceAcc,
                      DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
        iRet = ISO8583_SetBit(2, g_buff, DataTrans.sourceAccLen);
    }

    ///< Set Bit 25
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(25, "00", 2);
    }

    ///< Set Bit 37
    if (SUCCESS == iRet && strlen((char *)DataTrans.oldRefNumber)) {
        iRet = ISO8583_SetBit(37, DataTrans.oldRefNumber, 12);
    }

    ///< Set Bit 38
    if (SUCCESS == iRet && strlen((char *)DataTrans.authCode)) {
        iRet = ISO8583_SetBit(38, DataTrans.authCode, 6);
    }

    ///< Set Bit 59
    if ((SUCCESS == iRet)
        && (InputMode_Scan == DataTrans.cardInputType)) {
        ///< 付款凭证号
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        transOnline_Bit59TlvAppend("A4", DataTrans.ascScanVoucherNo,
            strlen((const char *)DataTrans.ascScanVoucherNo),
            &g_buff[mBufLen], &mBufLen);
        if (mBufLen > 0) {
            iRet = ISO8583_SetBit(59, g_buff, mBufLen);
        }
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        iRet = transOnline_Bit60_pack("23", "000", ExtraData.transType);
    }

    ///< Set Bit 61
    if (SUCCESS == iRet) {
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        //--61.1[N6] 原批号
        memcpy(&g_buff[mBufLen], DataTrans.batchNumber, 6);
        mBufLen += 6;
        //--61.2[6] 原POS流水号
        memcpy(&g_buff[mBufLen], DataTrans.oldtraceNumber, 6);
        mBufLen += 6;
        iRet = ISO8583_SetBit(61, g_buff, mBufLen);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_ReversalPack();
    }

    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
        ///< 未实际发送成功的交易，需清除冲正，降低冲正率
        if ((ERR_PARAM == iRet)
            || (ERR_DATA_PACK == iRet)
            || (ERR_COMMU_PARAM == iRet)
            || (ERR_COMMU_CONNECT == iRet)
            || (ERR_COMMU_SEND == iRet)) {
            ///< clear reversal
            transUtil_ClearReversal();
        }
    }
    if (SUCCESS != iRet) {
        ///< mac校验错更新冲正原因
        if (ERR_MAC == iRet) {
            transUtil_SaveReversal("A0");
        }
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(false))) {
//        goto END;
    }

    ///< Get Bit 55
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(55, g_buff, &mBufLen) == SUCCESS)
    {
        EMV_UnpackField55(g_buff, mBufLen, g_tempBuff, sizeof(g_tempBuff));
    }

END:
    ISO8583_Free();
    return iRet;
}

/**
 * @brief  refund on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
    退货
 */
static int transOnline_Refund(void)
{
    int iRet = SUCCESS;
    unsigned short mBufLen;
    tsTransData *pTransData = &DataTrans;

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_NormalCommon_pack(pTransData);
    if (SUCCESS == iRet)
    {
        ISO8583_SetMsgID("0220");
    }

    ///< Set Bit 03
    if (SUCCESS == iRet)
    {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "200000", 6);
        iRet = ISO8583_SetBit(3, g_buff, 6);
    }

    ///< Set Bit 02
    if ((SUCCESS == iRet)
        && (InputMode_Mag != DataTrans.cardInputType)
        && (InputMode_Scan != DataTrans.cardInputType)
        && DataTrans.sourceAccLen)
    {
        memset(g_buff, 0, sizeof(g_buff));
        tools_bcd_asc(g_buff, DataTrans.sourceAcc,
                      DataTrans.sourceAccLen + (DataTrans.sourceAccLen % 2 ? 1 : 0));
        iRet = ISO8583_SetBit(2, g_buff, DataTrans.sourceAccLen);
    }

    ///< Set Bit 25
    if (SUCCESS == iRet)
    {
        iRet = ISO8583_SetBit(25, "00", 2);
    }

    ///< Set Bit 37
    if (SUCCESS == iRet) {
        if (InputMode_Scan == DataTrans.cardInputType) {
            memset(g_buff, 0, sizeof(g_buff));
            memset(g_buff, '0', 12);
            iRet = ISO8583_SetBit(37, g_buff, 12);
        } else if (strlen((char *)DataTrans.oldRefNumber)) {
            iRet = ISO8583_SetBit(37, DataTrans.oldRefNumber, 12);
        }
    }

    ///< Set Bit 38
    if (SUCCESS == iRet && strlen((char *)DataTrans.oldAuthCode))
    {
        iRet = ISO8583_SetBit(38, DataTrans.oldAuthCode, 6);
    }

    ///< Set Bit 59
    if ((SUCCESS == iRet)
        && (InputMode_Scan == DataTrans.cardInputType)) {
        ///< 付款凭证号
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        transOnline_Bit59TlvAppend("A4", DataTrans.ascScanVoucherNo,
            strlen((const char *)DataTrans.ascScanVoucherNo),
            &g_buff[mBufLen], &mBufLen);
        if (mBufLen > 0) {
            iRet = ISO8583_SetBit(59, g_buff, mBufLen);
        }
    }

    ///< Set Bit 60
    if (SUCCESS == iRet)
    {
        iRet = transOnline_Bit60_pack("25", "000", ExtraData.transType);
    }

    ///< Set Bit 61
    if (SUCCESS == iRet)
    {
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));
        //--61.1[N6] 原批号
        memcpy(&g_buff[mBufLen], "000000", 6);
        mBufLen += 6;
        //--61.2[6] 原POS流水号
        memcpy(&g_buff[mBufLen], "000000", 6);
        mBufLen += 6;
        //--61.2[4] 原交易日期
        memcpy(&g_buff[mBufLen], DataTrans.oldDate, 4);
        mBufLen += 4;
        iRet = ISO8583_SetBit(61, g_buff, mBufLen);
    }

    ///< Set Bit 63
    if (SUCCESS == iRet)
    {
        ISO8583_SetBit(63, "000", 3);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet)
    {
        iRet = transOnline_SendRev();
        ///< 未实际发送成功的交易，需清除冲正，降低冲正率
        if ((ERR_PARAM == iRet)
            || (ERR_DATA_PACK == iRet)
            || (ERR_COMMU_PARAM == iRet)
            || (ERR_COMMU_CONNECT == iRet)
            || (ERR_COMMU_SEND == iRet))
        {
            ///< clear reversal
            transUtil_ClearReversal();
        }
    }

    if (SUCCESS != iRet)
    {
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(false)))
    {
        // goto END;
    }

    ///< Get Bit 55
    mBufLen = 0;
    memset(g_buff, 0, sizeof(g_buff));
    if (ISO8583_GetBit(55, g_buff, &mBufLen) == SUCCESS)
    {
        EMV_UnpackField55(g_buff, mBufLen, g_tempBuff, sizeof(g_tempBuff));
    }

END:
    ISO8583_Free();
    return iRet;
}

static int transOnline_Reverse(unsigned char transType)
{
    int iRet = SUCCESS;
    int i = 0;
    tsTransData tmpTransData;

    switch (transType)
    {
        case TRANS_SALE:
        case TRANS_VOID_SALE:
        case TRANS_QUERY_BAL:
        case TRANS_SETTLEMENT:
        case TRANS_REFUND:
            break;
        default:
            return SUCCESS;
    }

    ///< bakup trans data
    memset(&tmpTransData, 0, sizeof(tsTransData));
    memcpy(&tmpTransData, &DataTrans, sizeof(tsTransData));

    iRet = UFile_ReadFileIndexOf(DB_Reverse);
    if (iRet != SUCCESS)
        return iRet;

    if (!DataReverse.reversalFlag)
        return SUCCESS;

    ExtraData.transType = TRANS_REVERSAL;
    for (i = 0; i < DataConstant.transRetry; i++) {
        /*!< -------------------------------- pack data ----------------------------------------*/
    #if DEBUG_TRANS_ONLINE
        logger_serial_dump_buff("DataReverse.data", DataReverse.data, DataReverse.dataLen);
    #endif

        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_ReverseNumSend, i+1);
        Sleep(300);

        iso8583_SetISODef(&sIsoDef, SecretKey_MacECB);
        iRet = ISO8583_LoadData(DataReverse.data);

        ///< Set Bit 38
        if (SUCCESS == iRet && strlen((char *)DataReverse.authCode))
        {
            iRet = ISO8583_SetBit(38, DataReverse.authCode, 6);
        }

        ///< Set Bit 39
        if (SUCCESS == iRet) {
            if (!strlen((const char *)DataReverse.reversalEvent)) {
                strcpy((char *)DataReverse.reversalEvent, "06");
            }
            iRet = ISO8583_SetBit(39, DataReverse.reversalEvent, 2);
        }

        ///< Set Bit 64
        if (SUCCESS == iRet) {
            iRet = ISO8583_SetBit(64, "00000000", 8);
        }

        if (SUCCESS != iRet) {
            goto END;
        }

        /*!< -------------------------------- send and recv data --------------------------------*/
        if (SUCCESS == iRet) {
            if (SUCCESS != (iRet = transOnline_SendRev())) {
                if ((ERR_COMMU_PARAM == iRet)
                    || (ERR_COMMU_CONNECT == iRet)
                    || (ERR_MAC == iRet)) {
                    goto END;
                } else if (ERR_COMMU_RECV == iRet) {
                    if ((i+1) >= DataConstant.transRetry) {
                        mmi_clearLine(DISP_ClearALL);
                        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_ReverseFailed);
                        transUtil_ClearReversal();
                        iRet = SUCCESS;
                        mmi_inputWaitKeypress(3);
                        goto END;
                    }
                }
                continue;
            }
        }

        /*!< -------------------------------- upack data ---------------------------------------*/
        iRet = transOnline_CommonUPack(false);
        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_ReverseSuccess);
            transUtil_ClearReversal();
            mmi_inputWaitKeypress(3);
            goto END;
        } else if (ERR_MAC == iRet) {
            goto END;
        } else if (ERR_HOSTCODE == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_ReverseFailed);
            transUtil_ClearReversal();
            iRet = SUCCESS;
            mmi_inputWaitKeypress(3);
            goto END;
        }
    }

END:
    ///< recovery trans data
    memset(&DataTrans, 0, sizeof(tsTransData));
    memcpy(&DataTrans, &tmpTransData, sizeof(tsTransData));
    ExtraData.transType = transType;
    ISO8583_Free();

    return iRet;
}

/**
 * @brief  script pack on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_ScriptResultSave(void)
{
    int iRet = SUCCESS;
    unsigned short mBufLen;
    tsScriptData scriptData;

    iRet = transOnline_CommonPack();
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0620");
    }

    ///< Set Bit 03
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "000000", 6);
        switch(DataTrans.transType)
        {
        case TRANS_QUERY_BAL:
            memcpy(g_buff, "31", 2); break;
        case TRANS_SALE:
            memcpy(g_buff, "00", 2); break;
        case TRANS_VOID_SALE:
        case TRANS_REFUND:
            memcpy(g_buff, "20", 2); break;
        default:
            break;
        }
        iRet = ISO8583_SetBit(3, g_buff, 6);
    }

    ///< Set Bit 02
    if (SUCCESS == iRet && DataTrans.sourceAccLen) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_bcd_asc(g_buff, DataTrans.sourceAcc, DataTrans.sourceAccLen + (DataTrans.sourceAccLen%2 ? 1 : 0));
        iRet = ISO8583_SetBit(2, g_buff, DataTrans.sourceAccLen);
    }

    ///< Set Bit 04
    if (SUCCESS == iRet && DataTrans.ulAmount > 0) {
        memset(g_buff, 0, sizeof(g_buff));
        tools_long_asc(g_buff, 12, &DataTrans.ulAmount);
        iRet = ISO8583_SetBit(4, g_buff, 12);
    }

    ///< Set Bit 22
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, "0000", 4);
        switch(DataTrans.cardInputType)
        {
        case InputMode_Mag:
            g_buff[1] = '2';
            break;
        case InputMode_ICC:
            g_buff[1] = '5';
            break;
        case InputMode_QICC:
            g_buff[1] = '7';
            break;
        case InputMode_Scan:
            g_buff[1] = '3';
            break;
        default:
            g_buff[1] = '1';
            break;
        }
        g_buff[2] = (ExtraData.inputPINLen > 0) ? '1' : '2';
        iRet = ISO8583_SetBit(22, g_buff, 3);
    }

    ///< Set Bit 23
    if (SUCCESS == iRet && strlen((char *)DataTrans.panSeq)) {
        memset(g_buff, 0, sizeof(g_buff));
        memset(g_buff, 0x30, 4);
        memcpy(&g_buff[2], DataTrans.panSeq, 2);
        iRet = ISO8583_SetBit(23, g_buff, 4);
    }

    ///< Set Bit 25
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(25, "00", 2);
    }

    ///< Set Bit 32
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, DataTrans.bankID, sizeof(DataTrans.bankID));
        iRet = ISO8583_SetBit(32, g_buff, strlen((char *)g_buff));
    }

    ///< Set Bit 37
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, DataTrans.refNumber, sizeof(DataTrans.refNumber));
        iRet = ISO8583_SetBit(37, g_buff, strlen((char *)g_buff));
    }

    ///< Set Bit 38
    if (SUCCESS == iRet && strlen((char *)DataTrans.authCode)) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(g_buff, DataTrans.authCode, sizeof(DataTrans.authCode));
        iRet = ISO8583_SetBit(38, g_buff, strlen((char *)g_buff));
    }

    ///< Set Bit 49
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(49, DataConstant.currencyCode, 3);
    }

    ///< Set Bit 55
    if (SUCCESS == iRet) {
        mBufLen = sizeof(g_buff);
        EMV_GetScriptField55(g_buff, sizeof(g_buff), &mBufLen);
        iRet = ISO8583_SetBit(55, g_buff, mBufLen);
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        iRet = transOnline_Bit60_pack("00", "951", DataTrans.transType);
    }

    ///< Set Bit 61
    if (SUCCESS == iRet) {
        memset(DataTrans.oldtraceNumber, 0, sizeof(DataTrans.oldtraceNumber));
        memcpy(DataTrans.oldtraceNumber, DataTrans.traceNumber, sizeof(DataTrans.oldtraceNumber));

        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));

        //--61.1[N6] 原批号
        if (strlen((const char *)DataTrans.batchNumber) > 0) {
            memcpy(&g_buff[mBufLen], DataTrans.batchNumber, 6);
        } else {
            memcpy(&g_buff[mBufLen], "000000", 6);
        }
        mBufLen += 6;

        //--61.2[6] 原POS流水号
        if (strlen((const char *)DataTrans.oldtraceNumber) > 0) {
            memcpy(&g_buff[mBufLen], DataTrans.oldtraceNumber, 6);
        } else {
            memcpy(&g_buff[mBufLen], "000000", 6);
        }
        mBufLen += 6;

        //--61.3[4] 原交易日期
        memcpy(&g_buff[mBufLen], &DataTrans.date[4], 4);
        mBufLen += 4;

        iRet = ISO8583_SetBit(61, g_buff, mBufLen);
    }

    if (SUCCESS == iRet) {
        memset(&scriptData, 0, sizeof(scriptData));
        memset(g_tempBuff, 0, sizeof(g_tempBuff));
        mBufLen = 0;
        iRet = ISO8583_Pack(g_tempBuff, &mBufLen);
        memcpy(scriptData.data, g_tempBuff, sizeof(scriptData.data));
        scriptData.dataLen = mBufLen;
    }

    if (SUCCESS == iRet) {
        scriptData.flag = 1;
        iRet = UFile_WriteFile(FILE_ICScript, &scriptData, sizeof(scriptData));
    }

    ISO8583_Free();
    return iRet;
}

/**
 * @brief  script result send
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_ScriptResultSend(unsigned char transType)
{
    int iRet = SUCCESS;
    int i;
    tsScriptData scriptData;
    tsTransData tmpTransData;

    ///<
    if ((TRANS_LOGON == transType)
        || (TRANS_LOADAID == transType)
        || (TRANS_LOADCAPK == transType)
        || (TRANS_LOADRF == transType)) {
        return SUCCESS;
    }

    ///< bakup trans data
    memset(&tmpTransData, 0, sizeof(tsTransData));
    memcpy(&tmpTransData, &DataTrans, sizeof(tsTransData));

    memset(&scriptData, 0, sizeof(scriptData));
    iRet = UFile_ReadFile(FILE_ICScript, &scriptData, sizeof(scriptData));
    if (iRet != SUCCESS) {
        return iRet;
    }

    if (!scriptData.flag) {
        return SUCCESS;
    }

    ExtraData.transType = TRANS_SCRIPT_SEND;
    for (i = 0; i < DataConstant.transRetry; i++)
    {
        /*!< -------------------------------- pack data ----------------------------------------*/
    #if DEBUG_TRANS_ONLINE
        logger_serial_dump_buff("Script data", scriptData.data, scriptData.dataLen);
    #endif

        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_ScriptSend, i+1);
        Sleep(300);

        iso8583_SetISODef(&sIsoDef, SecretKey_MacECB);
        iRet = ISO8583_LoadData(scriptData.data);
        if (SUCCESS == iRet) {
            ISO8583_DelBit(11);
            iRet = ISO8583_SetBit(11, DataChange.traceNumber, 6);
        }

        ///< Set Bit 64
        if (SUCCESS == iRet) {
            iRet = ISO8583_SetBit(64, "00000000", 8);
        }

        if (SUCCESS != iRet) {
            goto END;
        }

        /*!< -------------------------------- send and recv data --------------------------------*/
        if (SUCCESS == iRet) {
            if (SUCCESS != (iRet = transOnline_SendRev())) {
                if ((ERR_COMMU_PARAM == iRet)
                    || (ERR_COMMU_CONNECT == iRet)
                    || (ERR_MAC == iRet)) {
                    goto END;
                } else if (ERR_COMMU_RECV == iRet) {
                    if ((i+1) >= DataConstant.transRetry) {
                        mmi_clearLine(DISP_ClearALL);
                        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_UploadFailed);
                        UFile_ClearFile(FILE_ICScript);
                        iRet = SUCCESS;
                        mmi_inputWaitKeypress(3);
                        goto END;
                    }
                }
            }
        }

        /*!< -------------------------------- upack data ---------------------------------------*/
        iRet = transOnline_CommonUPack(false);
        if (iRet == SUCCESS) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_UploadSuccess);
            UFile_ClearFile(FILE_ICScript);
            mmi_inputWaitKeypress(3);
            goto END;
        } else if (ERR_MAC == iRet) {
            goto END;
        } else if (ERR_HOSTCODE == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_UploadFailed);
            UFile_ClearFile(FILE_ICScript);
            iRet = SUCCESS;
            mmi_inputWaitKeypress(3);
            goto END;
        }
    }

END:
    ///< recovery trans data
    memset(&DataTrans, 0, sizeof(tsTransData));
    memcpy(&DataTrans, &tmpTransData, sizeof(tsTransData));
    ExtraData.transType = transType;
    ISO8583_Free();

    return iRet;
}

/**
 * @brief settle on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int transOnline_Settle(void)
{
    int iRet = SUCCESS;
     unsigned short mBufLen;
     tsTradeTotalAll *pstForAll = &DataTransDetail.transDetailData.totalAll;

     if (!pstForAll) {
         return ERR_PARAM;
     }

    /*!< -------------------------------- pack data ----------------------------------------*/
    iRet = transOnline_CommonPack();
    if (SUCCESS == iRet) {
        ISO8583_SetMsgID("0500");
    }

    ///< Set Bit 11 trace number
    if (SUCCESS == iRet) {
        ISO8583_DelBit(11);
        iRet = ISO8583_SetBit(11, DataChange.traceNumber, 6);
    }

    ///< Set Bit 48 Settle amount
    if (SUCCESS == iRet) {
        mBufLen = 0;
        memset(g_buff, 0, sizeof(g_buff));

        ///< debit
        tools_long_asc(&g_buff[mBufLen], 12, &pstForAll->stTotalIn.totalDebitAmount);
        mBufLen += 12;
        tools_short_asc(&g_buff[mBufLen], 3, &pstForAll->stTotalIn.totalDebitNum);
        mBufLen += 3;

        ///< credit
        tools_long_asc(&g_buff[mBufLen], 12, &pstForAll->stTotalIn.totalCreditAmount);
        mBufLen += 12;
        tools_short_asc(&g_buff[mBufLen], 3, &pstForAll->stTotalIn.totalCreditNum);
        mBufLen += 3;
        g_buff[mBufLen] = 0x30;
        mBufLen += 1;

        ///< debit
        tools_long_asc(&g_buff[mBufLen], 12, &pstForAll->stTotalOut.totalDebitAmount);
        mBufLen += 12;
        tools_short_asc(&g_buff[mBufLen], 3, &pstForAll->stTotalOut.totalDebitNum);
        mBufLen += 3;

        ///< credit
        tools_long_asc(&g_buff[mBufLen], 12, &pstForAll->stTotalOut.totalCreditAmount);
        mBufLen += 12;
        tools_short_asc(&g_buff[mBufLen], 3, &pstForAll->stTotalOut.totalCreditNum);
        mBufLen += 3;
        g_buff[mBufLen] = 0x30;
        mBufLen += 1;

        iRet = ISO8583_SetBit(48, g_buff, mBufLen);
    }

    ///< Set Bit 49 Currency code
    if (SUCCESS == iRet) {
        iRet = ISO8583_SetBit(49, DataConstant.currencyCode, 3);
    }

    ///< Set Bit 60
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memcpy(&g_buff[0], "00", 2);
        memcpy(&g_buff[2], DataChange.batchNumber, 6);
        memcpy(&g_buff[8], "201", 3);
        iRet = ISO8583_SetBit(60, g_buff, 11);
    }

    ///< Set Bit 63
    if (SUCCESS == iRet) {
        memset(g_buff, 0, sizeof(g_buff));
        memset(g_buff, 0x20, 3);
        memcpy(g_buff, DataChange.cashierNo, sizeof(DataChange.cashierNo));
        iRet = ISO8583_SetBit(63, g_buff, 3);
    }

    /*!< -------------------------------- send and recv data --------------------------------*/
    if (SUCCESS == iRet) {
        iRet = transOnline_SendRev();
    }
    if (SUCCESS != iRet) {
        goto END;
    }

    /*!< -------------------------------- upack data ---------------------------------------*/
    if (SUCCESS != (iRet = transOnline_CommonUPack(true))) {
        goto END;
    }

    ///< Get Bit 44

    ///< Get Bit 48
    mBufLen = 0;
    memset(g_buff,0,sizeof(g_buff));
    iRet = ISO8583_GetBit(48, g_buff, &mBufLen);
    if (SUCCESS == iRet) {
        ///< 内卡
        switch(g_buff[30])
        {
        case '1':
            DataTransDetail.transDetailData.InternalSettleFlag = SETTLE_OK;
            break;
        case '2':
            DataTransDetail.transDetailData.InternalSettleFlag = SETTLE_UNEVEN;
            break;
        case '3':
        default:
            DataTransDetail.transDetailData.InternalSettleFlag = SETTLE_ERROR;
            break;
        }

        ///< 外卡
        switch(g_buff[61])
        {
        case '1':
            DataTransDetail.transDetailData.ForeignSettleFlag = SETTLE_OK;
            break;
        case '2':
            DataTransDetail.transDetailData.ForeignSettleFlag = SETTLE_UNEVEN;
            break;
        case '3':
        default:
            DataTransDetail.transDetailData.ForeignSettleFlag = SETTLE_ERROR;
            break;
        }
    }

END:
    ISO8583_Free();
    return iRet;
}

/**
 * @brief batch settle on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_BatchSettle(void)
{
    int iRet = SUCCESS;
    unsigned char settleFlag;

    ///< 先置结算中断标志
    if (DataChange.ucSettleStep == 0) {
        DataChange.ucSettleStep = 1;
        iRet = UFile_WriteFileIndexOf(DB_Change);
    }

    ///< 批结算
    if (SUCCESS == iRet) {
        iRet = transOnline_Settle();
        transUtil_IncreaseTraceNumber(1);
    }
    if (iRet != SUCCESS) {
        goto END;
    }

    settleFlag = (DataTransDetail.transDetailData.ForeignSettleFlag == SETTLE_OK)&(DataTransDetail.transDetailData.InternalSettleFlag == SETTLE_OK);
    ///< 对账平
    if (settleFlag) {
        mmi_clearLine(255);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SettlementOK);
        Sleep(500);
    }
    else {
        mmi_clearLine(255);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SettlementUneven);
        Sleep(500);
    }

END:
    return iRet;
}

extern void trans_GetInfo(void);
/**
 * @brief  on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_process(void)
{
    extern void mdm_mq_set_idle_state(int idle);
    int iRet = SUCCESS;

    if (1 == DataConstant.posState) {
        trans_GetInfo();
        transUtil_IncreaseTraceNumber(1);
        return SUCCESS;
    }

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
    mmi_display(DISP_Line3, 0, AMSG_Processing);
    mmi_display(DISP_Line4, 0, AMSG_PleaseWait);

    ///< hang up mdm
    mdm_mq_set_idle_state(0);

    ///< 如果在联机交易的应答中包含了发卡行脚本，POS终端应在下次联机交易（签到除外）时或联机冲正时或在批结算前上送脚本处理结果
    if (SUCCESS == iRet) {
        iRet = transOnline_ScriptResultSend(ExtraData.transType);
    }

    ///< 如果有冲正,则联机冲正
    if (SUCCESS == iRet) {
        iRet = transOnline_Reverse(ExtraData.transType);
    }

    ///< 获取流水号，批次号
    if (SUCCESS == iRet) {
        trans_GetInfo();
        transUtil_IncreaseTraceNumber(1);
    }

    ///< Online request
    if (SUCCESS == iRet) {
        switch(ExtraData.transType)
        {
        case TRANS_LOGON:
            iRet = transOnline_Logon();
            if (SUCCESS == iRet) {
                iRet = transOnline_DownParam(DataChange.packgeHeadEve);
            }
            break;
        case TRANS_LOGOFF:
            iRet = transOnline_Logoff();
            break;
        case TRANS_LOADAID:
            iRet = transOnline_DownAID();
            break;
        case TRANS_LOADCAPK:
            iRet = transOnline_DownCAPK(DataConstant.bSM);
            break;
        case TRANS_LOADRF:
            iRet = transOnline_DownUntouchParam();
            break;
        case TRANS_SETTLEMENT:
            iRet = transOnline_BatchSettle();
            break;
        case TRANS_QUERY_BAL:
            iRet = transOnline_QueryBal();
            break;
        case TRANS_SALE:
            iRet = transOnline_Sale();
            break;
        case TRANS_VOID_SALE:
            iRet = transOnline_VoidSale();
            break;
        case TRANS_REFUND:
            iRet = transOnline_Refund();
            break;
        default:
            iRet = ERR_PARAM;
            break;
        }
    }

    ///< recover mdm
    mdm_mq_set_idle_state(1);
    return iRet;
}

