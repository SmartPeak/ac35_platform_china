/*************************************************
* explain : secret key
* creator : XuZhou.Chen
* date created : 06/14/2018
*************************************************/
#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "utils.h"
#include "uFile.h"

#include "secretKey.h"
#include "trans.h"

#define SECRETKEY_DEBUG             0
#if SECRETKEY_DEBUG
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "secretKey.c"
#endif

#define TLK_USE_TMK                 1    ///< use TMK make TLK
//===========================================
//secretkey index
//===========================================
#if TLK_USE_TMK
#define KEY_INDEX_TLK               30   ///< TLK index
#else
#define KEY_INDEX_TLK               0x01 ///< TLK index
#endif
#define KEY_INDEX_TMK               0x01 ///< TMK index
#define KEY_INDEX_TPK               0x06 ///< TPK index
#define KEY_INDEX_TAK               0x08 ///< TAK index
#define KEY_INDEX_TDK               0x10 ///< TDK index
#define KEY_INDEX_SMK               64   ///< SMK index

///< check KCV len
#define KEY_CHECK_LEN               4

//===========================================
//error code
//===========================================
///< current use TMK index
#define CURRY_TMK_USER_INDEX        DataConstant.ucUseKeyIndex
#if SECRETKEY_SOFTDES
#define s_softSp                    DataSave.softSpData
#endif

/**
 * @brief get SP write key error code
 */
static int SecretKey_GetSpErrCode(int code, int errCode)
{
    if (code < 0) {
        code = (65536 + code);
        switch(code)
        {
        case 0xFEBB:
            return ERR_SAVE_KEY_KCV;
        case 0xFE94:
            return ERR_CALC_KEY_KCV;
        default:
            return errCode;
        }
    }
    return SUCCESS;
}

///< save new SMK(test smk)
int SecretKey_LoadTestSNKey(unsigned char *pKeyValue, unsigned char len)
{
    int iRet = 0;
    ST_KEY_INFO keyInfo;
    ST_KCV_INFO kcvInfo;

    memset(&keyInfo, 0, sizeof(keyInfo));
    memset(&kcvInfo, 0, sizeof(kcvInfo));

    keyInfo.ucSrcKeyType    = 0x00;
    keyInfo.ucSrcKeyIdx     = 0x00;
    keyInfo.ucDstKeyType    = PED_TEK;
    keyInfo.ucDstKeyIdx     = KEY_INDEX_SMK;
//    keyInfo.Algorithm       = PED_SM4;
    keyInfo.ucDstKeyLen     = len;
    memcpy(keyInfo.ucDstKeyValue, pKeyValue, len);

#if SECRETKEY_SOFTDES
    memset(s_softSp.SMKey, 0, sizeof(s_softSp.SMKey));
    memcpy(s_softSp.SMKey, pKeyValue, len);
#else
    iRet = PedWriteKeyRev(&keyInfo, &kcvInfo);
#endif
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_SAVE);
}

///< save new TLK
int SecretKey_LoadTLK(unsigned char *pKeyValue, unsigned char len)
{
    int iRet = 0;
    ST_KEY_INFO keyInfo;
    ST_KCV_INFO kcvInfo;

    memset(&keyInfo, 0, sizeof(keyInfo));
    memset(&kcvInfo, 0, sizeof(kcvInfo));

    keyInfo.ucSrcKeyType    = 0x00;
    keyInfo.ucSrcKeyIdx     = 0x00;
#if TLK_USE_TMK
    keyInfo.ucDstKeyType    = PED_TMK;
#else
    keyInfo.ucDstKeyType    = PED_TLK;
#endif
    keyInfo.ucDstKeyIdx     = KEY_INDEX_TLK;
    keyInfo.Algorithm       = PED_TDES;
    keyInfo.ucDstKeyLen     = len;
    memcpy(keyInfo.ucDstKeyValue, pKeyValue, len);

#if SECRETKEY_SOFTDES
    memset(s_softSp.tlKey, 0, sizeof(s_softSp.tlKey));
    memcpy(s_softSp.tlKey, pKeyValue, len);
    s_softSp.tlKeyLen = len;
#else
    iRet = PedWriteKeyRev(&keyInfo, &kcvInfo);
#endif
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_SAVE);
}

///< save TMK
int SecretKey_LoadTMK(unsigned char bTLKdecrypt, unsigned char index, unsigned char *pKeyValue, unsigned char len)
{
    int iRet = 0;
    ST_KEY_INFO keyInfo;
    ST_KCV_INFO kcvInfo;

    memset(&keyInfo, 0, sizeof(keyInfo));
    memset(&kcvInfo, 0, sizeof(kcvInfo));

    keyInfo.ucSrcKeyType    = 0x00;
    keyInfo.ucSrcKeyIdx     = 0x00;
    if (bTLKdecrypt)
    {
#if TLK_USE_TMK
        keyInfo.ucSrcKeyType    = PED_TMK;
#else
        keyInfo.ucSrcKeyType    = PED_TLK;
#endif
        keyInfo.ucSrcKeyIdx     = KEY_INDEX_TLK;
    }
    keyInfo.ucDstKeyType    = PED_TMK;
    keyInfo.ucDstKeyIdx     = index;
    keyInfo.Algorithm       = PED_TDES;
    keyInfo.ucDstKeyLen     = len;
    memcpy(keyInfo.ucDstKeyValue, pKeyValue, len);

#if SECRETKEY_SOFTDES
    memset(s_softSp.MainKey, 0, sizeof(s_softSp.MainKey));
    s_softSp.MainKeyLen = len;
    if (bTLKdecrypt)
    {
        iRet = PedCalcDesDPARev(&s_softSp.tlKey[0], s_softSp.tlKeyLen, &pKeyValue[0], 8, &s_softSp.MainKey[0], 8, 0, 0);
        if (iRet >= 0 && len > 8)
            iRet = PedCalcDesDPARev(&s_softSp.tlKey[0], s_softSp.tlKeyLen, &pKeyValue[8], 8, &s_softSp.MainKey[8], 8, 0, 0);
        s_softSp.MainKeyLen = len;
    }
    else
    {
        memcpy(s_softSp.MainKey, pKeyValue, len);
    }
#else
    iRet = PedWriteKeyRev(&keyInfo, &kcvInfo);
#endif
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_SAVE);
}

///< pCheckValue说明:第1个字节为校验标志,第2个字节为校验长度,第3个字节起为校验数据
static int SecretKey_LoadKey(unsigned char bNoDecrypt, unsigned char ucSaveKeyType, unsigned char *pKeyValue, unsigned char len, unsigned char ucKeyIndex, unsigned char ucSaveKeyIndex, unsigned char *pCheckValue)
{
    int iRet = 0;
    char bCheckFlag, iCheckLen;
    unsigned char *p, pKey[17], kcv[10];
    ST_KEY_INFO keyInfo;
    ST_KCV_INFO kcvInfo;

    p = pCheckValue;
    bCheckFlag = pCheckValue[0];
    p++;

    iCheckLen = pCheckValue[1];
    p++;

#if SECRETKEY_DEBUG
    LOGD("key len1 = %d\r\n", len);
    logger_serial_dump_buff("key value1:", pKeyValue, len);
#endif

    if (len == 16) {
        if (!memcmp(&pKeyValue[8], "\x00\x00\x00\x00\x00\x00\x00\x00", 8)) {
            len -= 8;
        }
    }

#if SECRETKEY_DEBUG
    LOGD("key len2 = %d\r\n", len);
    logger_serial_dump_buff("key value2:", pKeyValue, len);
#endif

    /*!< -------------------------- Write Key -------------------------- >!*/
    memset(pKey, 0, sizeof(pKey));
    memset(kcv, 0x00, sizeof(kcv));
    memset(&keyInfo, 0, sizeof(keyInfo));
    memset(&kcvInfo, 0, sizeof(kcvInfo));

    if (!bNoDecrypt) {
        keyInfo.ucSrcKeyType    = PED_TMK;
        keyInfo.ucSrcKeyIdx     = ucKeyIndex;
    }

    keyInfo.ucDstKeyType    = ucSaveKeyType;
    keyInfo.ucDstKeyIdx     = ucSaveKeyIndex;
    keyInfo.Algorithm       = PED_TDES;
    keyInfo.ucDstKeyLen     = len;
    memcpy(keyInfo.ucDstKeyValue, pKeyValue, len);
    if (bCheckFlag == 1) {
        kcvInfo.iCheckMode = 0x01;
        kcvInfo.iDataLen = iCheckLen;
        memcpy(kcvInfo.szCheckBuf, p, iCheckLen);
    }

#if SECRETKEY_SOFTDES
    if (!bNoDecrypt) {
        iRet = PedCalcDesDPARev(&s_softSp.MainKey[0], s_softSp.MainKeyLen, &pKeyValue[0], 8, &pKey[0], 8, 0, 0);
        if (iRet >= 0 && len > 8) {
            iRet = PedCalcDesDPARev(&s_softSp.MainKey[0], s_softSp.MainKeyLen, &pKeyValue[8], 8, &pKey[8], 8, 0, 0);
        }
    }
    else {
        memcpy(pKey, pKeyValue, len);
    }

    ///< check kcv
    if (iRet >= 0 && bCheckFlag == 1) {
        ///< use 0x00 encrypt
        memset(kcv, 0, sizeof(kcv));
        iRet = PedCalcDesDPARev(pKey, len, (unsigned char *)"\x00\x00\x00\x00\x00\x00\x00\x00", 8, kcv, 8, 0, 1);
        logger_serial_dump_buff("check data 1:", kcv, iCheckLen);
        logger_serial_dump_buff("check data 1:", p, iCheckLen);
        if (memcmp(kcv, p, iCheckLen)) {
            iRet = -1;
        }

#if SECRETKEY_DEBUG
        LOGD("[%5d]key check:%d\n", __LINE__, iRet);
#endif
    }

    if (iRet >= 0) {
        ///< decode and save
        if (ucSaveKeyType == PED_TPK) {
            memset(s_softSp.pinKey, 0x00, sizeof(s_softSp.pinKey));
            memcpy(s_softSp.pinKey, pKey, len);
            s_softSp.pinKeyLen = len;
        }
        else if (ucSaveKeyType == PED_TAK)
        {
            memset(s_softSp.macKey, 0x00, sizeof(s_softSp.macKey));
            memcpy(s_softSp.macKey, pKey, len);
            s_softSp.macKeyLen = len;
        }
        else if (ucSaveKeyType == PED_TDK)
        {
            memset(s_softSp.tdkKey, 0x00, sizeof(s_softSp.tdkKey));
            memcpy(s_softSp.tdkKey, pKey, len);
            s_softSp.tdkKeyLen = len;
        }
        else
        {
            iRet = -1;
        }
    }
#else
    iRet = PedWriteKeyRev(&keyInfo, &kcvInfo);
#endif
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_SAVE);
}

///< analysis and save work key
static int SecretKey_Single_SaveNewKey(unsigned char *pInData, unsigned short iInLen)
{
    int iRet = -1;
    unsigned char mBuf[25];
    unsigned char mPinKey[9], mMacKey[9];
    unsigned char mPinCheck[6], mMacCheck[6];
    unsigned char usOffset;
    unsigned char ucTMKIndex;

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("key in data:", pInData, iInLen);
#endif

    if (iInLen != 24) {
        return ERR_SECREKEY_DATA_ERR;
    }

    /*!< ------------------------------------- >!*/
    memset(mBuf, 0, sizeof(mBuf));
    memcpy(mBuf, pInData, 24);
    usOffset = 0;

    ///< pin
    memset(mPinKey, 0, sizeof(mPinKey));
    memcpy(mPinKey, &mBuf[usOffset], 8);
    usOffset += 8;
    ///< pin check
    memset(mPinCheck, 0, sizeof(mPinCheck));
    memcpy(&mPinCheck[2], &mBuf[usOffset], 4);
    mPinCheck[0] = 1;
    mPinCheck[1] = 4;
    usOffset += 4;

    ///< mac
    memset(mMacKey, 0, sizeof(mMacKey));
    memcpy(mMacKey, &mBuf[usOffset], 8);
    usOffset += 8;
    ///< mac check
    memset(mMacCheck, 0, sizeof(mMacCheck));
    memcpy(&mMacCheck[2], &mBuf[usOffset], 4);
    mMacCheck[0] = 1;
    mMacCheck[1] = 4;
    usOffset += 4;

    /*!< ------------------------------------- >!*/
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("PinKey:", mPinKey, 8);
    logger_serial_dump_buff("MacKey:", mMacKey, 8);
#endif

    ucTMKIndex = CURRY_TMK_USER_INDEX;
    /*!< ___________________ PIN Key ______________________*/
    iRet = SecretKey_LoadKey(0, PED_TPK, mPinKey, 8, ucTMKIndex, KEY_INDEX_TPK, mPinCheck);
    /*!< ___________________ MAC Key ______________________*/
    if (!iRet)
    {
        iRet = SecretKey_LoadKey(0, PED_TAK, mMacKey, 8, ucTMKIndex, KEY_INDEX_TAK, mMacCheck);
    }
    return iRet;
}

///< analysis and save double work key
static int SecretKey_Double_SaveNewKey(unsigned char *pInData, unsigned short iInLen)
{
    int iRet = -1;
    int iMaxLen;
    unsigned char mBuf[41];
    unsigned char mPinKey[17], mMacKey[17];
    unsigned char mPinCheck[6], mMacCheck[6];
    unsigned char usOffset;
    unsigned char ucTMKIndex;

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("key in data:", pInData, iInLen);
#endif

    iMaxLen = (16+KEY_CHECK_LEN)*2;
    if (iInLen != iMaxLen) {
        return ERR_SECREKEY_DATA_ERR;
    }

    /*!< ------------------------------------- >!*/
    memset(mBuf, 0, sizeof(mBuf));
    memcpy(mBuf, pInData, iMaxLen);
    usOffset = 0;

    ///< pin
    memset(mPinKey, 0, sizeof(mPinKey));
    memcpy(mPinKey, &mBuf[usOffset], 16);
    usOffset += 16;
    ///< pin check
    memset(mPinCheck, 0, sizeof(mPinCheck));
    memcpy(&mPinCheck[2], &mBuf[usOffset], KEY_CHECK_LEN);
    mPinCheck[0] = 1;
    mPinCheck[1] = KEY_CHECK_LEN;
    usOffset += KEY_CHECK_LEN;

    ///< mac
    memset(mMacKey, 0, sizeof(mMacKey));
    memcpy(mMacKey, &mBuf[usOffset], 16);
    usOffset += 16;
    ///< mac check
    memset(mMacCheck, 0, sizeof(mMacCheck));
    memcpy(&mMacCheck[2], &mBuf[usOffset], KEY_CHECK_LEN);
    mMacCheck[0] = 1;
    mMacCheck[1] = KEY_CHECK_LEN;
    usOffset += KEY_CHECK_LEN;

#if SECRETKEY_DEBUG
    /*!< ------------------------------------- >!*/
    logger_serial_dump_buff("PinKey:", mPinKey, 16);
    logger_serial_dump_buff("MacKey:", mMacKey, 16);
#endif
    ucTMKIndex = CURRY_TMK_USER_INDEX;
    /*!< ___________________ PIN Key ______________________*/
    iRet = SecretKey_LoadKey(0, PED_TPK, mPinKey, 16, ucTMKIndex, KEY_INDEX_TPK, mPinCheck);
    /*!< ___________________ MAC Key ______________________*/
    if (!iRet)
    {
        iRet = SecretKey_LoadKey(0, PED_TAK, mMacKey, 16, ucTMKIndex, KEY_INDEX_TAK, mMacCheck);
    }
    return iRet;
}

///< analysis and save tdk
static int SecretKey_Double_SaveNewKeyTDK(unsigned char *pInData, unsigned short iInLen)
{
    int iRet = -1;
    int iMaxLen;
    unsigned char mBuf[61];
    unsigned char mPinKey[17], mMacKey[17], mTDKey[17];
    unsigned char mPinCheck[6], mMacCheck[6], mTDCheck[6];
    unsigned char usOffset;
    unsigned char ucTMKIndex;

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("key in data:", pInData, iInLen);
#endif

    iMaxLen = (16+KEY_CHECK_LEN)*3;
    if (iInLen != iMaxLen) {
        return ERR_SECREKEY_DATA_ERR;
    }

    /*!< ------------------------------------- >!*/
    memset(mBuf, 0, sizeof(mBuf));
    memcpy(mBuf, pInData, iMaxLen);
    usOffset = 0;

    ///< pin
    memset(mPinKey, 0, sizeof(mPinKey));
    memcpy(mPinKey, &mBuf[usOffset], 16);
    usOffset += 16;
    ///< pin check
    memset(mPinCheck, 0, sizeof(mPinCheck));
    memcpy(&mPinCheck[2], &mBuf[usOffset], KEY_CHECK_LEN);
    mPinCheck[0] = 1;
    mPinCheck[1] = KEY_CHECK_LEN;
    usOffset += KEY_CHECK_LEN;

    ///< mac
    memset(mMacKey, 0, sizeof(mMacKey));
    memcpy(mMacKey, &mBuf[usOffset], 16);
    usOffset += 16;
    ///< mac check
    memset(mMacCheck, 0, sizeof(mMacCheck));
    memcpy(&mMacCheck[2], &mBuf[usOffset], KEY_CHECK_LEN);
    mMacCheck[0] = 1;
    mMacCheck[1] = KEY_CHECK_LEN;
    usOffset += KEY_CHECK_LEN;

    ///< TDK
    memset(mTDKey, 0, sizeof(mTDKey));
    memcpy(mTDKey, &mBuf[usOffset], 16);
    usOffset += 16;
    ///< TDK check
    memset(mTDCheck, 0, sizeof(mTDCheck));
    memcpy(&mTDCheck[2], &mBuf[usOffset], KEY_CHECK_LEN);
    mTDCheck[0] = 1;
    mTDCheck[1] = KEY_CHECK_LEN;
    usOffset += KEY_CHECK_LEN;

#if SECRETKEY_DEBUG
    /*-------------------------------------*/
    logger_serial_dump_buff("PinKey:", mPinKey, 16);
    logger_serial_dump_buff("MacKey:", mMacKey, 16);
    logger_serial_dump_buff("TDKey:", mTDKey, 16);
#endif

    ucTMKIndex = CURRY_TMK_USER_INDEX;
    /*!< ___________________ PIN Key ______________________*/
    iRet = SecretKey_LoadKey(0, PED_TPK, mPinKey, 16, ucTMKIndex, KEY_INDEX_TPK, mPinCheck);
    /*!< ___________________ MAC Key ______________________*/
    if (!iRet)
        iRet = SecretKey_LoadKey(0, PED_TAK, mMacKey, 16, ucTMKIndex, KEY_INDEX_TAK, mMacCheck);
    /*!< ___________________ TD Key ______________________*/
    if (!iRet) {
        iMaxLen = 16;
        if (!memcmp(&mTDKey[8], "\x00\x00\x00\x00\x00\x00\x00\x00", 8)) {
            iMaxLen -= 8;
        }
        iRet = SecretKey_LoadKey(0, PED_TDK, mTDKey, iMaxLen, ucTMKIndex, KEY_INDEX_TDK, mTDCheck);
    }
    return iRet;
}

///< analysis and save new work key
int SecretKey_SaveNewKey(unsigned char encryptType, unsigned char *pInData, unsigned short iInLen)
{
    switch(encryptType)
    {
    case EncryptSingle:
        return SecretKey_Single_SaveNewKey(pInData, iInLen);
    case EncryptDouble:
        return SecretKey_Double_SaveNewKey(pInData, iInLen);
    case EncryptDoubleTDK:
    default:
        return SecretKey_Double_SaveNewKeyTDK(pInData, iInLen);
    }
}

///< SN encryption
int SecretKey_Bit59_CalcMAC(unsigned char *pInData, unsigned short uiInLen, unsigned char *pKey, unsigned char *pOutMAC)
{
    int iRet = SUCCESS;
    unsigned char aucHexData[16+1];
    unsigned char aucAscData[32+1];
    unsigned char aucTmpData[16+1];
    unsigned char *pucPtr;
    unsigned short uiI, uiJ;
    unsigned short uiLen;

#if SECRETKEY_DEBUG
    LOGD((char *)"(%4d)========%s(B)========", __LINE__, __func__);
#endif

    //1.准备初始数据[硬件序列号+加密随机因子]
    pucPtr = pInData;
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("初始数据:", pucPtr, uiInLen);
#endif
    //2.按每16个字节做异或, 如果最后不满16个字节，则添加“0x00”
    memset(aucHexData, 0x00, sizeof(aucHexData));
    for (uiI = 0; uiI < uiInLen; uiI += 16)
    {
        uiLen = (16 < pInData + uiInLen - pucPtr) ? 16 : (pInData + uiInLen - pucPtr);
        for (uiJ = 0; uiJ < uiLen; uiJ++)
        {
            aucHexData[uiJ] ^= *(pucPtr + uiJ);
        }
        pucPtr += 16;
    }
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("每16位异或后数据:", aucHexData, 32);
#endif
    //3.将异或运算后的最后16个字节（RESULT BLOCK）转换成32个 HEXDECIMAL
    utilsBcd2Asc(aucHexData, 16, aucAscData);
    aucAscData[32] = 0;
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("转换32位后数据:", aucAscData, 32);
#endif
    //4.取前16 个字节用SM4加密
    memset(aucHexData, 0, sizeof(aucHexData));
#if SECRETKEY_SOFTDES
    iRet = PedCalcDesDPARev(s_softSp.SMKey, 16, aucAscData, 32, aucHexData, 16, 0, 1);
    if (iRet < 0)
        goto GOTO_ERR;
#else
    iRet = PedCalcDESRev(KEY_INDEX_SMK, PED_ECB_ENC, aucAscData, 32, aucHexData);
    if (iRet < 0)
        goto GOTO_ERR;
#endif

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("SM4加密后数据", aucHexData, 16);
#endif
    //5.将加密后的结果与后16 个字节异或
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("后16位数据:", &aucAscData[16], 16);
#endif
    for (uiI = 0; uiI < 16; uiI++) {
        aucHexData[uiI] ^= aucAscData[16 + uiI];
    }
#if SECRETKEY_DEBUG
    logger_serial_dump_buff("再次异或后数据", aucHexData, 16);
#endif
    //6.用异或的结果TEMP BLOCK 再进行一次SM4密钥算法运算
    memset(aucTmpData, 0x00, sizeof(aucTmpData));
#if SECRETKEY_SOFTDES
    iRet = PedCalcDesDPARev(s_softSp.SMKey, 16, aucHexData, 32, aucTmpData, 16, 0, 1);
    if (iRet < 0)
        goto GOTO_ERR;
#else
    iRet = PedCalcDESRev(KEY_INDEX_SMK, PED_ECB_ENC, aucHexData, 32, aucTmpData);
    if (iRet < 0)
        goto GOTO_ERR;
#endif

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("再次SM4加密后数据:", aucTmpData, 16);
#endif
    //7.将运算后的结果（ENC BLOCK2）转换成32个 HEXDECIMAL
    utilsBcd2Asc(aucTmpData, 16, aucAscData);
    memcpy(pOutMAC, aucAscData, 8);

#if SECRETKEY_DEBUG
    logger_serial_dump_buff("最后转换16位后数据:", aucAscData, 8);
#endif

GOTO_ERR:
#if SECRETKEY_DEBUG
    LOGD((char *)"(%4d)========%s(E)%d========", __LINE__, __func__, iRet);
#endif
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_ENCRYPTION);
}

///< 计算MAC ECB模式
int SecretKey_MacECB(unsigned char *pDataIn, unsigned int inLen, unsigned char *pDataOut)
{
    int iRet;
    int nLen, nP, nI, nJ;
    unsigned char szTmpBuf[20] = {0};
    unsigned char szMacBuf1[10] = {0};
    unsigned char szMacBuf2[10] = {0};
    unsigned char szGetBuffer[40] = {0};

    nLen = inLen;
    if (nLen % 8)
        nP = 1;
    else
        nP = 0;

    for (nI = 0; nI < (nLen / 8) + nP; nI++)
    {
        for (nJ = 0; nJ < 8; nJ++)
        {
            if((nI * 8 + nJ) < nLen)
            {
                szTmpBuf[nJ] ^= pDataIn[nI * 8 + nJ];
            }
            else
            {
                szTmpBuf[nJ] ^= 0x00;
            }
        }
    }

    memset(szMacBuf1, 0, sizeof(szMacBuf1));
    memset(szMacBuf2, 0, sizeof(szMacBuf2));
    memset(szGetBuffer, 0, sizeof(szGetBuffer));

    utilsBcd2Asc(szTmpBuf, 8, szGetBuffer);
    memcpy(szMacBuf1, szGetBuffer, 8);
    memcpy(szMacBuf2, szGetBuffer + 8, 8);

    memset(szTmpBuf, 0, sizeof(szTmpBuf));
    memset(szGetBuffer, 0, sizeof(szGetBuffer));

#if SECRETKEY_SOFTDES
    iRet = PedCalcDesDPARev(s_softSp.macKey, s_softSp.macKeyLen, szMacBuf1, 8, szTmpBuf, 8, 0, 1);
    if (iRet < 0)
        goto ERR;
#else
    iRet = PedCalcDESRev(KEY_INDEX_TAK, PED_ECB_ENC, szMacBuf1, 8, szTmpBuf);
    if (iRet < 0)
        goto ERR;
#endif
    for(nI = 0; nI < 8; nI++) {
        szGetBuffer[nI] = szTmpBuf[nI] ^ szMacBuf2[nI];
    }

    memset(szTmpBuf, 0, sizeof(szTmpBuf));

#if SECRETKEY_SOFTDES
    iRet = PedCalcDesDPARev(s_softSp.macKey, s_softSp.macKeyLen, szGetBuffer, 8, szTmpBuf, 8, 0, 1);
    if (iRet < 0)
        goto ERR;
#else
    iRet = PedCalcDESRev(KEY_INDEX_TAK, PED_ECB_ENC, szGetBuffer, 8, szTmpBuf);
    if (iRet < 0)
        goto ERR;
#endif

    memset(szGetBuffer, 0, sizeof(szGetBuffer));
    utilsBcd2Asc(szTmpBuf, 8, szGetBuffer);
    memcpy(pDataOut, szGetBuffer, 8);
    return SUCCESS;
ERR:
    return SecretKey_GetSpErrCode(iRet, ERR_MAC);
}

///< PIN加密
int SecretKey_EncryptPINData(unsigned char *pPINData, unsigned char *pDataOut)
{
    int iRet = -1;

#if SECRETKEY_SOFTDES
    iRet = PedCalcDesDPARev(s_softSp.pinKey, s_softSp.pinKeyLen, pPINData, 8, pDataOut, 8, 0, 1);
    if (iRet < 0)
        goto DO_ERR;
#else
    iRet = PedCalcDESRev(KEY_INDEX_TPK, PED_ECB_ENC, pPINData, 8, pDataOut);
    if (iRet < 0)
        goto DO_ERR;
#endif

    return SUCCESS;

DO_ERR:
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_ENCRYPTION);
}

int SecretKey_EcryptTrack(unsigned char *pTrackData, unsigned short usLen, int *pOutLen)
{
    int iRet = SUCCESS;
    unsigned char *pucISO2;
    unsigned char aucEncTrackBuf[9],aucTempData[9];
    unsigned char aucTemp[16];
    unsigned short ucI,ucJ,ucK;

    memset(aucEncTrackBuf, 0, sizeof(aucEncTrackBuf));
    memset(aucTempData, 0, sizeof(aucTempData));
    memset(aucTemp, 0, sizeof(aucTemp));
    pucISO2 = pTrackData;

    if(usLen != 0)
    {
        if (usLen%2)
        {
            ucI = usLen-2;
        }
        else
        {
            ucI = usLen-3;
        }

        for (ucJ = 0; ucI > 0; ucI--)
        {
            ucJ++;
            if (ucJ >= 16)
                break;
        }

        if (!ucI)
            ucI = 0;

        memset(aucTemp, 'F', 16);
        for (ucJ = ucI, ucK = 0; ucJ < usLen; ucJ++)
        {
            aucTemp[ucK] = pucISO2[ucJ];
            ucK++;

            if (ucK >= 16)
                break;
        }

        utilsAsc2Bcd(aucTemp, 16, aucTempData);
#if SECRETKEY_SOFTDES
        iRet = PedCalcDesDPARev(s_softSp.tdkKey, s_softSp.tdkKeyLen, aucTempData, 8, aucTempData, 8, 0, 1);
        if (iRet < 0)
            goto DO_ERR;
#else
        iRet = PedCalcDESRev(KEY_INDEX_TDK, PED_ECB_ENC, aucTempData, 8, aucTempData);
        if (iRet < 0)
            goto DO_ERR;
#endif
        utilsBcd2Asc(aucTempData, 8, &pucISO2[ucI]);
    }

    *pOutLen = usLen;
    return SUCCESS;

DO_ERR:
    return SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_ENCRYPTION);
}

/**
 * @brief key pos download master key
 */
int Key_Download(void)
{
    unsigned char szTmpKey[17] = {0}, szMKey[17] = {0}, szCKey[17] = {0}, szMKeyBuf[17] = {0};
    char szRecvBuf[256] = {0}, szBuf[17] = {0};
    int nFailTime = 0;
    int iLen = 0;
    int iRet = SUCCESS;
    unsigned char ucKeyId = 0;
    unsigned char ucKeyLen = 0;

    ///< serial port init
    USBAT_Init();

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_DownloadTMK);
    mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SerialPortRecv);

    memset(szTmpKey, 0, sizeof(szTmpKey));
    memcpy(szTmpKey, "STARTSSD", 8);    ///< for decrypting the master key
    memset(szRecvBuf, 0, sizeof(szRecvBuf));
    nFailTime = 0;

    do
    {
        ///< timeout quit(30s)
        if (++nFailTime > 60) {
            iRet = ERR_TIMEOUT;
            break;
        }

        ///< serial port recv data
        iLen = USBATGet((BYTE *)szRecvBuf, 1, 500);
#if SECRETKEY_DEBUG
        LOGD("Recv Head = %d, %02X\r\n", iLen, szRecvBuf[0]);
#endif
        ///< check cancel key
        if (!KbHit()) {
            if (KEY_CANCEL == mmi_inputGetKeypress()) {
                iRet = ERR_CANCEL;
                break;
            }
        }
    } while (0x02 != szRecvBuf[0]);

    ///< recv the rest of data
    if (SUCCESS == iRet) {
        iLen = 0;
        iLen = USBATGet((BYTE *)&szRecvBuf[1], 50, 500);
#if SECRETKEY_DEBUG
        LOGD("Recv Data = %d\r\n", iLen);
        logger_serial_dump_buff("szRecvBuf:", &szRecvBuf[1], iLen);
#endif
        ///< check recv data length
        if ((19 != iLen) && (27 != iLen)) {
            iRet = ERR_SECREKEY_DATA_ERR;
        }
    }

    ///< parse the recv master key data
    if (SUCCESS == iRet) {
        ucKeyId = (unsigned char)szRecvBuf[1]; ///< master key index
        ucKeyLen = 8;
        ///< calc master key length
        if (27 == iLen) {
            ucKeyLen = 16;
        }

        memset(szMKey, 0, sizeof(szMKey));
        memset(szCKey, 0, sizeof(szCKey));
        memset(szBuf, 0, sizeof(szBuf));

        memcpy(szMKey, &szRecvBuf[2], ucKeyLen);    ///< get master key value
        memcpy(szCKey, &szRecvBuf[ucKeyLen+2], 8);  ///< get master key check value
        ///< des decrypt the key check value with master key
        iRet = PedCalcDesDPARev(szMKey, ucKeyLen, szCKey, 8, (unsigned char *)szBuf, sizeof(szBuf), 0, 0);
        iRet = SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_ENCRYPTION);
#if SECRETKEY_DEBUG
        logger_serial_dump_buff("check value:", szBuf, 8);
#endif
    }
    ///< check key value fail
    if (SUCCESS == iRet) {
        if (memcmp(szBuf, "00000000", 8)) {
            iRet = ERR_SECREKEY_DATA_ERR;
        }
    }

    ///< des decrypt the plain master key
    if (SUCCESS == iRet) {
        memset(szMKeyBuf, 0, sizeof(szMKeyBuf));
        iRet = PedCalcDesDPARev(szTmpKey, 8, szMKey, ucKeyLen, szMKeyBuf, sizeof(szMKeyBuf), 0, 0);
        iRet = SecretKey_GetSpErrCode(iRet, ERR_SECREKEY_ENCRYPTION);
#if SECRETKEY_DEBUG
        logger_serial_dump_buff("master key value:", szMKeyBuf, ucKeyLen);
#endif
    }

    ///< send response data
    if (SUCCESS == iRet) {
        USBATSend("\x02\x00\x00\x03\x01", 5);
    }

    ///< serial port close
    USBAT_Deinit();

    ///< Write plain key value into the SP
    if (SUCCESS == iRet) {
        iRet = SecretKey_LoadTMK(0, ucKeyId, szMKeyBuf, ucKeyLen);
    }

    if (iRet != ERR_CANCEL && iRet != ERR_TIMEOUT) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, SUCCESS == iRet ? AMSG_DownloadTMKSuccess : AMSG_DownloadTMKFail);
        mmi_inputWaitKeypress(5);
    }
    return iRet;
}

/**
 * @brief set master key index
 */
static int Key_SetIndex(void)
{
    int iRet = SUCCESS;
    unsigned char index = CURRY_TMK_USER_INDEX;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_SetTMKIndex);
    mmi_display(DISP_Line2, DISP_Left, AMSG_USE_TMK_INDEX);
    iRet = mmi_inputDigital(DISP_Line4, DISP_Right, &index, sizeof(index), 1, 9, 60);
    if (SUCCESS == iRet) {
        if (index != CURRY_TMK_USER_INDEX) {
            CURRY_TMK_USER_INDEX = index;
            iRet = UFile_WriteFileIndexOf(DB_Constant);
        }
    }

    if (iRet != ERR_CANCEL && iRet != ERR_TIMEOUT) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, SUCCESS == iRet ? AMSG_SetSuccess : AMSG_SetFailed);
        mmi_inputWaitKeypress(5);
    }
    return iRet;
}

/**
 * @brief set DES algorithm mode
 */
int Key_SetAlgorithm(void)
{
    int iRet = ERR_CANCEL;
    enum ENCRYPT_TYPE ecrypt_type = DataConstant.encryptType;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_SetSecretKeyType);
    mmi_display(DISP_Line2, DISP_Left, "0-%s", AMSG_SecretKeySingle);
    mmi_display(DISP_Line3, DISP_Left, "1-%s", AMSG_SecretKeyDouble);
    mmi_display(DISP_Line4, DISP_Left, "2-%s", AMSG_SecretKeyDoubleTDK);

    iRet = mmi_inputDigital(DISP_Line5, DISP_Right, &ecrypt_type, sizeof(enum ENCRYPT_TYPE), 0, 2, 60);
    if (SUCCESS == iRet && ecrypt_type != DataConstant.encryptType) {
        DataConstant.encryptType = ecrypt_type;
        iRet = UFile_WriteFileIndexOf(DB_Constant);
    }

    if (iRet != ERR_CANCEL && iRet != ERR_TIMEOUT) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, SUCCESS == iRet ? AMSG_SetSuccess : AMSG_SetFailed);
        mmi_inputWaitKeypress(5);
    }
    return iRet;
}

/**
 * @brief set master key value
 */
int Key_SetValue(void)
{
    int iRet = 0;
    unsigned int length = 0;
    unsigned char key_index = 1;
    unsigned char asc_key[33] = {0};
    unsigned char hex_key[17] = {0};

DO_LOOP:
    key_index = 1;
    memset(asc_key, 0, sizeof(asc_key));

    ///< input master key index
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_ManualSecretKey);
    mmi_display(DISP_Line2, DISP_Left, AMSG_InputTMKIndex);
    iRet = mmi_inputDigital(DISP_Line4, DISP_Right, &key_index, sizeof(key_index), 1, 9, 60);

    ///< input plain master key value
    if (SUCCESS == iRet) {
        length = EncryptSingle == DataConstant.encryptType ? 16 : 32;

        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_ManualSecretKey);
        mmi_display(DISP_Line2, DISP_Left, AMSG_InputTMK, length);
        iRet = mmi_inputString(DISP_Line3, mmi_setInputType(InputMethod_hex, InputMethod_hex),
                               asc_key, (int)length, (int)length, NULL, 60);
    }

    ///< save tmk
    if (SUCCESS == iRet) {
        memset(hex_key, 0, sizeof(hex_key));
        tools_asc_hex(hex_key, length/2, asc_key, length);
        iRet = SecretKey_LoadTMK(0, key_index, hex_key, length/2);
    }

    ///< ----
    if (iRet != ERR_CANCEL && iRet != ERR_TIMEOUT) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line2, DISP_HCenter, SUCCESS == iRet ? AMSG_DownloadTMKSuccess : AMSG_DownloadTMKFail);
        mmi_display(DISP_Line3, DISP_HCenter, AMSG_EnterToSet);
        mmi_display(DISP_Line4, DISP_HCenter, AMSG_CancelToExit);
        while(1)
        {
            switch(mmi_inputWaitKeypress(60))
            {
            case KEY_ENTER:
                goto DO_LOOP;
            case KEY_CANCEL:
            case KEY_NONE:
                return ERR_CANCEL;
            }
        }
    }
    return iRet;
}

///< download tmk 4442 card
int SecretKey_DownLoadTMK_Sel4442(void)
{
    int iRet = SUCCESS;
    int iOffset = 0;
    unsigned char mReadBuf[128], mBuf[20], mTemp[20], mCheckValue[20];
    MemicOptType mMemicOpt;
    T_SOFTTIMER tm;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_DownloadTMK);
    if (SUCCESS == iRet) {
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_PlzPushSecretKeyCard);
        memset(&tm, 0, sizeof(tm));
        memset(&mMemicOpt, 0, sizeof(mMemicOpt));
        mMemicOpt.ucType    = MEMIC_TYPE_SLE4442;
        mMemicOpt.ucCmd     = MEMIC_CMD_STA;
        s_TimerSet(&tm, 120*1000);
        while(1)
        {
            if (!s_TimerCheck(&tm)) {
                return ERR_TIMEOUT;
            }
            else if (!MemoryCardOperate(&mMemicOpt)) {
                break;
            }
            else if (KbHit()) {
                Sleep(10);
                continue;
            }
            else if (KEY_CANCEL == mmi_inputGetKeypress()) {
                return ERR_CANCEL;
            }
        }
    }

    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_VCenter);
        mmi_display(DISP_VCenter, DISP_HCenter, AMSG_DontMoveSecretKeyCard);
        memset(&mMemicOpt, 0, sizeof(mMemicOpt));
        mMemicOpt.ucType    = MEMIC_TYPE_SLE4442;
        mMemicOpt.ucCmd     = MEMIC_CMD_OPEN;
        if (MemoryCardOperate(&mMemicOpt)) {
            goto READ_CARD_ERR;
        }
    }

    if (SUCCESS == iRet) {
        memset(mReadBuf, 0, sizeof(mReadBuf));
        memset(&mMemicOpt, 0, sizeof(mMemicOpt));
        mMemicOpt.ucType    = MEMIC_TYPE_SLE4442;
        mMemicOpt.ucCmd     = MEMIC_CMD_READ;
        mMemicOpt.ucZone    = SLE4442_MM;
        mMemicOpt.usAddr    = 0x20;
        mMemicOpt.usLength  = sizeof(mReadBuf);
        if (MemoryCardOperate(&mMemicOpt)) {
            goto READ_CARD_ERR;
        }
        memcpy(mReadBuf, mMemicOpt.aucBuf, mMemicOpt.usLength);
    }

    memset(&mMemicOpt, 0, sizeof(mMemicOpt));
    mMemicOpt.ucType    = MEMIC_TYPE_SLE4442;
    mMemicOpt.ucCmd     = MEMIC_CMD_CLOSE;
    MemoryCardOperate(&mMemicOpt);

    ///< 15 MID + 8 TID + 1 TMK index + 16 TMK + 4 CV = 44
    if (SUCCESS == iRet) {
        iOffset =0;

        ///< ----
        if(memcmp(&mReadBuf[iOffset], DataConstant.MID, 15)) {
            return ERR_MID_CHECK;
        }
        iOffset +=15;

        ///< ----
        if(memcmp(&mReadBuf[iOffset], DataConstant.TID, 8)) {
            return ERR_TID_CHECK;
        }
        iOffset +=8;

        ///< ----
        DataConstant.ucUseKeyIndex = mReadBuf[iOffset] + 1;
        iOffset +=1;

        ///< ----
        memset(mBuf, 0, sizeof(mBuf));
        if (PedCalcDesDPARev("\x56\x65\x72\x69\x46\x6F\x6E\x65", 8, &mReadBuf[iOffset], 16, mBuf, 16, PED_SYMM_MODE_ECB, PED_FUNC_DECRYPT) < 0) {
            iRet = ERR_SAVE_KEY_KCV;
        }
        iOffset += 16;

        ///< ----
        if (SUCCESS == iRet) {
            memset(mTemp, 0, sizeof(mTemp));
            memset(mCheckValue, 0, sizeof(mCheckValue));
            if (PedCalcDesDPARev(mBuf, 16, mTemp, 16, mCheckValue, 16, PED_SYMM_MODE_ECB, PED_FUNC_ENCRYPT) < 0) {
                iRet = ERR_SAVE_KEY_KCV;
            }
        }

        if (SUCCESS == iRet) {
            if(memcmp(mCheckValue, &mReadBuf[iOffset], 4)){
                iRet = ERR_SAVE_KEY_KCV;
            }
        }
    }

    if (SUCCESS == iRet) {
        iRet = SecretKey_LoadTMK(0, DataConstant.ucUseKeyIndex, &mReadBuf[iOffset-16], 16);
    }
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileIndexOf(DB_Constant);
    }

    if (iRet != ERR_CANCEL && iRet != ERR_TIMEOUT) {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_VCenter, DISP_HCenter, SUCCESS == iRet ? AMSG_DownloadTMKSuccess : AMSG_DownloadTMKFail);
        mmi_inputWaitKeypress(5);
    }

    return SUCCESS;

READ_CARD_ERR:
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SecretKeyCardReadFailed);
    mmi_inputWaitKeypress(20);
    return ERR_END;
}

int POS_DownTMKMenu(void)
{
    while(1)
    {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_DownloadTMK);
        mmi_display(DISP_Line2, 0, "1.%s", AMSG_DownloadTMK_IC);
        mmi_display(DISP_Line3, 0, "2.%s", AMSG_DownloadTMK_POS);
        mmi_display(DISP_Line4, 0, "3.%s", AMSG_DownloadTMK_Manual);

        switch (mmi_inputWaitKeypress(60))
        {
        case KEY_ASCII1:
            SecretKey_DownLoadTMK_Sel4442();
            break;
        case KEY_ASCII2:
            Key_Download();
            break;
        case KEY_ASCII3:
            Key_SetValue();
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            break;
        }
    }
}

/**
 * @brief master key manage menu
 */
int POS_KeyManageMenu(void)
{
    while(1)
    {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_SecretKeyManage);
        mmi_display(DISP_Line2, 0, "1.%s", AMSG_DownloadTMK);
        mmi_display(DISP_Line3, 0, "2.%s", AMSG_SetTMKIndex);
        mmi_display(DISP_Line4, 0, "3.%s", AMSG_SetSecretKeyType);
        switch (mmi_inputWaitKeypress(60))
        {
        case KEY_ASCII1:
            POS_DownTMKMenu();
            break;
        case KEY_ASCII2:
            Key_SetIndex();
            break;
        case KEY_ASCII3:
            Key_SetAlgorithm();
            break;
        case KEY_ASCII4:
            Key_SetValue();
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            break;
        }
    }
}

