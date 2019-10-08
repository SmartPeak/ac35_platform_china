#include "bwsdk_api.h"
#include "applib_tools.h"
#include "applib_err.h"
#include "Kernel_Param.h"

#include "Emv_DownParam.h"
#include "Emv_ct_storage.h"
#include "Emv_Utile.h"
#include "pos_data.h"

#define DEBUG_EMV_DOWN_PARAM        0

#if DEBUG_EMV_DOWN_PARAM
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "EMV_DownParam.c"
#endif

/*!< -------------------------EMV Get Down Param List ----------------------*/
union DOWN_EMV_PARAM_LIST
{
    AID_DOWN_INFO   apiList[MAX_AID_LIST];      ///< AID down list
    CAPK_DOWN_INFO  capkList[MAX_CAPK_LIST];    ///< CAPK down list
};

static union DOWN_EMV_PARAM_LIST g_downEmvParamList;

/*!< --------------------------EMV Down Param UnPack Data -----------------*/
int EMV_DownParam_ClearGlobalData(void)
{
    memset(&g_downEmvParamList, 0, sizeof(g_downEmvParamList));
    return SUCCESS;
}

CAPK_DOWN_INFO *EMV_CAPK_GetDownInfo(int index)
{
    if (index < 0 || index > MAX_CAPK_LIST) {
        return NULL;
    }
    return &g_downEmvParamList.capkList[index];
}

typedef struct _EMV_TAG_ATTR
{
    unsigned char   aucTag[4];
}EMV_TAG_ATTR;

typedef struct _EMV_TAG_INFO
{
    unsigned char           aucTag[4];
    unsigned short          uiLen;
    unsigned char           *pTagValue;
    struct _EMV_TAG_INFO    *pTemplate;
}EMV_TAG_INFO;

#define EMV_MAX_TAG_NUM         50
#define EMV_MAX_TAG_BUFF        1024
typedef struct
{
    const struct _EMV_TAG_ATTR     *pEMVTagAttr;
    unsigned char                   ucTagNum;
    EMV_TAG_INFO                    EMVTagInfo[EMV_MAX_TAG_NUM];
    unsigned short                  uiTagBuffLen;
    unsigned char                   aucEMVTagVaule[EMV_MAX_TAG_BUFF];
    unsigned short                  uiTransInfoLen;
    unsigned char                   *aucTransInfo;
}IC_TRANS_INFO;

const struct _EMV_TAG_ATTR EMVParamCAPKInfo[] =
{
    {"\x9F\x06"},   ///< RID
    {"\x9F\x22"},   ///< 公钥索引   ///< ic card public key index
    {"\xDF\x02"},   ///< 公钥膜     ///< ic card public key module 
    {"\xDF\x03"},   ///< 公钥校验值 ///< ic card public key check value
    {"\xDF\x04"},   ///< 公钥指数   ///< ic card public key exponent
    {"\xDF\x05"},   ///< 有效期     ///< ic card public key period of validity
    {"\xDF\x06"},   ///< hash算法标识///< Hash algorithm identification
    {"\xDF\x07"}    ///< 签名算法标识///< Signature algorithm identification
};

const struct _EMV_TAG_ATTR EMVParamAIDInfo[] =
{
    {"\x9F\x06"},   ///< AID
    {"\xDF\x01"},   ///< Selection indicator 选择指示符:0 不支持部分匹配;1 支持部分匹配
                    ///< 0:unsupport part of the match,1:support
    {"\x9F\x08"},   ///< Application Version Number(Terminal) 终端应用版本号
    {"\x9F\x09"},   ///< Application Version Number(Terminal) 终端应用版本号
    {"\xDF\x11"},   ///< TAC default 缺省
    {"\xDF\x12"},   ///< TAC online 联机
    {"\xDF\x13"},   ///< TAC refuse 拒绝
    {"\x9F\x1B"},   ///< Terminal Floor Limit 最低限额
    {"\xDF\x15"},   ///< Bias randomly selected thresholds 偏置随机选择的阈值
    {"\xDF\x16"},   ///< Bias the maximum target percentage 
                    ///< selected at random 偏置随机选择的最大目标百分数
    {"\xDF\x17"},   ///< Random target percentage 随机选择的目标百分数
    {"\xDF\x14"},   ///< DEFAULT DDOL
    {"\xDF\x18"},   ///< Terminal on-line capability 终端联机能力
    {"\x9F\x7B"},   ///< Terminal electronic cash transaction limits 终端电子现金交易限额
    {"\xDF\x19"},   ///< Contactless reader offline minimum 非接触读写器脱机最低限额
    {"\xDF\x20"},   ///< Contactless reader transaction limits 非接触读写器交易限额
    {"\xDF\x21"},   ///< 读写器持卡人验证方法（CVM） 所需限制（CVM 交易限额）
};

const struct _EMV_TAG_ATTR EMVParamUntouchInfo[] =
{
    {"\xFF\x80\x5D"},   ///< 非接优先选择(0.联机,1.脱机)
    {"\xFF\x80\x3A"},   ///< 闪卡当笔重刷处理时间
    {"\xFF\x80\x3C"},   ///< 闪卡记录可处理时间T
    {"\xFF\x80\x58"},   ///< 非接快速业务(QPS)免密限额
    {"\xFF\x80\x54"},   ///< 非接快速业务标识
    {"\xFF\x80\x55"},   ///< BIN A
    {"\xFF\x80\x56"},   ///< BIN B
    {"\xFF\x80\x57"},   ///< CD-CVM
    {"\xFF\x80\x59"},   ///< 免签限额
    {"\xFF\x80\x5A"},   ///< 免签标识
    {"\xFF\x81\x0C"},   ///< 优先挥卡处理
};


#if DEBUG_EMV_DOWN_PARAM
static void EMV_TAG_DataDump(IC_TRANS_INFO * pDataInfo)
{
    unsigned char i = 0;
    EMV_TAG_INFO *pEMVTagInfo;

    LOGD("--------- EMVTAG_DataDump ---------");
    for(i = 0; i < pDataInfo->ucTagNum; i++)
    {
        pEMVTagInfo = &pDataInfo->EMVTagInfo[i];
        logger_serial_dump_buff("Tag:", pEMVTagInfo->aucTag, strlen((char *)pEMVTagInfo->aucTag));
        if(pEMVTagInfo->aucTag[0]&0x20) {
            LOGD("Template");
        }
        else {
            logger_serial_dump_buff("Value:", pEMVTagInfo->pTagValue, pEMVTagInfo->uiLen);
        }
    }
}
#endif

static EMV_TAG_INFO *EMV_SearchTag(IC_TRANS_INFO *pICInfo, const char *pTag)
{
    unsigned char ucI, ucScrLen, ucTagLen;
    EMV_TAG_INFO *pEMVTagInfo;
    EMV_TAG_ATTR *pEMVTagAttr;

    ucScrLen = strlen(pTag);
    pEMVTagInfo = pICInfo->EMVTagInfo;
    pEMVTagAttr = pICInfo->pEMVTagAttr;

    for(ucI = 0; ucI < pICInfo->ucTagNum; ucI++, pEMVTagAttr++, pEMVTagInfo++)
    {
        ucTagLen = strlen((char *)pEMVTagAttr->aucTag);
        if(ucScrLen == ucTagLen && !memcmp(pEMVTagAttr->aucTag, (unsigned char *)pTag, ucTagLen))
        {
            return pEMVTagInfo;
        }
    }
    return NULL;
}

static unsigned char EMV_GetTagLenAttr(unsigned char *pTagData, unsigned short* pTagLen)
{
    unsigned char i = 0;
    unsigned char tagLen = 0;
    unsigned short len = 0;

    if(*pTagData <= 127) {
        len = *pTagData;
        tagLen++;
    }
    else {
        len = 0;
        tagLen = *pTagData&0x7F;
        for(i = 1; i <= tagLen; i++) {
            len = len*256 + *(pTagData+i);
        }
        tagLen += 1;
    }

    *pTagLen = len;
    return tagLen;
}

int EMV_GetTagValue(IC_TRANS_INFO *pICTransInfo, const char *paucTag, unsigned char* paucTagValue, unsigned short* uiTagValueLen)
{
    EMV_TAG_INFO *pEMVTagInfo;
    unsigned short uiBufLen;

    pEMVTagInfo = EMV_SearchTag(pICTransInfo, paucTag);
    if(!pEMVTagInfo) {
        return -1;
    }

    uiBufLen = pEMVTagInfo->uiLen;
    if(pEMVTagInfo->uiLen > *uiTagValueLen) {
        uiBufLen= *uiTagValueLen;
        return -1;
    }

    memcpy(paucTagValue, pEMVTagInfo->pTagValue, uiBufLen);
    *uiTagValueLen = uiBufLen;

    return 0;
}

static int EMV_ParamDown_Init(IC_TRANS_INFO *pICTransInfo, const EMV_TAG_ATTR EMVTagAttrInfo[], unsigned char arrayNum)
{
    memset(pICTransInfo, 0, sizeof(IC_TRANS_INFO));
    if(arrayNum > EMV_MAX_TAG_NUM) {
        return -1;
    }

    pICTransInfo->pEMVTagAttr = EMVTagAttrInfo;
    pICTransInfo->ucTagNum = arrayNum;
    pICTransInfo->uiTransInfoLen = EMV_MAX_TAG_BUFF;
    return 0;
}

static int EMV_ParamDown_Unpack(IC_TRANS_INFO *pICTransInfo)
{
    unsigned char i, ucLenAttr;
    unsigned char *pBuff = NULL;
    EMV_TAG_INFO *pEMVTagInfo = NULL;
    EMV_TAG_ATTR *pEMVTagAttr = NULL;
    unsigned char tagSize = 0, tag[3] = {0};
    unsigned short offset = 0;

    if (pICTransInfo->uiTransInfoLen < 2) {
        goto ERR;
    }

#if DEBUG_EMV_DOWN_PARAM
    logger_serial_dump_buff("Unpack Data:", pICTransInfo->aucTransInfo, pICTransInfo->uiTransInfoLen);
#endif

    pBuff = pICTransInfo->aucTransInfo;
    while (pBuff < pICTransInfo->aucTransInfo + pICTransInfo->uiTransInfoLen) {
        for (i = 0; i < pICTransInfo->ucTagNum; i++) {
            pEMVTagAttr = &pICTransInfo->pEMVTagAttr[i];
            tagSize = ((pEMVTagAttr->aucTag[0] & 0xFF) == 0xFF ? 3 : ((pEMVTagAttr->aucTag[0] & 0x1F) == 0x1F ? 2 : 1));

            memset(tag, 0, sizeof(tag));
            if (tagSize == 3) {
                tools_asc_hex(tag, 3, pBuff, 6);
                if (!memcmp(tag, pEMVTagAttr->aucTag, tagSize)) {
                    tagSize = tagSize * 2;
                    break;
                }
            }
            else if (!memcmp(pBuff, pEMVTagAttr->aucTag, tagSize)) {

                break;
            }
        }

        if (i < pICTransInfo->ucTagNum) {
            pEMVTagInfo = &pICTransInfo->EMVTagInfo[i];
            if (pEMVTagInfo->uiLen) {
                goto ERR;
            }

            memcpy(pEMVTagInfo->aucTag, pEMVTagAttr->aucTag, tagSize);
            pBuff += tagSize;

            pEMVTagInfo->pTagValue = pICTransInfo->aucEMVTagVaule + offset;
            if (tagSize == 6) {
                ucLenAttr = 3;
                pEMVTagInfo->uiLen = tools_asc_long(pBuff, 3);
            }
            else {
                ucLenAttr = EMV_GetTagLenAttr(pBuff, &pEMVTagInfo->uiLen);
            }

            pBuff += ucLenAttr;
            if (offset + pEMVTagInfo->uiLen > EMV_MAX_TAG_BUFF) {
                goto ERR;
            }

            memcpy(pEMVTagInfo->pTagValue, pBuff, pEMVTagInfo->uiLen);
            pBuff += pEMVTagInfo->uiLen;
            offset += pEMVTagInfo->uiLen;

            continue;
        }
        pBuff++;
    }

#if DEBUG_EMV_DOWN_PARAM
    EMV_TAG_DataDump(pICTransInfo);
#endif
    return 0;
ERR:
    return -1;
}

//查询获取CAPK下载列表
int EMV_CAPK_DownListUnpack(unsigned char *paucParam, int uiLen, int *pCAPKNum)
{
    int iCAPKNum = 0;
    unsigned char ucTagLen = 0;
    unsigned char *pParamEnd = NULL;
    unsigned char aucRID[5] = {0}, ucPKIndex = 0, aucExpireDate[8] = {0};

    iCAPKNum = *pCAPKNum;
    pParamEnd = paucParam + uiLen;
    while (paucParam < pParamEnd && iCAPKNum < MAX_CAPK_LIST)
    {
        if (memcmp(paucParam, "\x9F\x06", 2)) {
            goto ERR;
        }
        paucParam += 2;

        ucTagLen = *paucParam;
        if (ucTagLen != 5) {
            goto ERR;
        }
        paucParam++;

        memcpy(aucRID, paucParam, ucTagLen);
        paucParam += ucTagLen;
        if (memcmp(paucParam, "\x9F\x22", 2)) {
            goto ERR;
        }
        paucParam += 2;

        ucTagLen = *paucParam;
        if (ucTagLen != 1) {
            goto ERR;
        }
        paucParam++;

        ucPKIndex = *paucParam;
        paucParam += ucTagLen;
        if (memcmp(paucParam, "\xDF\x05", 2)) {
            goto ERR;
        }
        paucParam += 2;

        ucTagLen = *paucParam;
        if (ucTagLen != 8) {
            goto ERR;
        }
        paucParam++;

        memcpy(aucExpireDate, paucParam, ucTagLen);
        paucParam += ucTagLen;

        memcpy(g_downEmvParamList.capkList[iCAPKNum].RID, aucRID, sizeof(aucRID));
        g_downEmvParamList.capkList[iCAPKNum].CAPKI = ucPKIndex;
        memcpy(g_downEmvParamList.capkList[iCAPKNum].ExpireDate, aucExpireDate, sizeof(aucExpireDate));
        iCAPKNum++;
        if (iCAPKNum >= MAX_CAPK_LIST) {
            goto ERR;
        }
    }
    *pCAPKNum = iCAPKNum;
    return 0;
ERR:
    return -1;
}

/*下载capk参数*/
int EMV_CAPK_DownUnpack(unsigned char *revData, int revDataLen)
{
    int iRet;
    unsigned char buff[20] = {0};
    unsigned short uiLen;
    EMV_CAPK_ITEM capkItem = {0};
    IC_TRANS_INFO m_EMVTagInfo = {0};

    iRet = EMV_ParamDown_Init(&m_EMVTagInfo, EMVParamCAPKInfo, sizeof(EMVParamCAPKInfo)/sizeof(EMV_TAG_ATTR));
    if (!iRet) {
        m_EMVTagInfo.aucTransInfo = revData;
        m_EMVTagInfo.uiTransInfoLen = revDataLen;
        iRet = EMV_ParamDown_Unpack(&m_EMVTagInfo);
    }

    memset(&capkItem, 0, sizeof(capkItem));

    ///< RID
    if (!iRet) {
        uiLen = sizeof(capkItem.m_RID);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x06", capkItem.m_RID, &uiLen);
        if (!iRet && uiLen != sizeof(capkItem.m_RID)) {
            iRet = -1;
        }
    }

    ///< 公钥索引
    if (!iRet) {
        uiLen = sizeof(capkItem.m_CapkIndex);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x22", &capkItem.m_CapkIndex, &uiLen);
        if (!iRet && uiLen != sizeof(capkItem.m_CapkIndex)) {
            iRet = -1;
        }
    }

    ///< 公钥膜
    if (!iRet) {
        uiLen = sizeof(capkItem.m_Modules);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x02", capkItem.m_Modules, &uiLen);
        capkItem.m_uiModules = uiLen;
    }

    ///< 公钥校验值
    if (!iRet) {
        uiLen = sizeof(capkItem.m_Checksum);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x03", capkItem.m_Checksum, &uiLen);
        if (!iRet && uiLen != sizeof(capkItem.m_Checksum)) {
            iRet = -1;
        }
    }

    ///< 公钥指数
    if (!iRet) {
        uiLen = sizeof(capkItem.m_Exponents);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x04", capkItem.m_Exponents, &uiLen);
        capkItem.m_uiExponents = uiLen;
    }

    ///< 有效期
    if (!iRet) {
        uiLen = 8;
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x05", buff, &uiLen);
        if (!iRet) {
            tools_asc_bcd(capkItem.m_ExpDate, 3, &buff[2], 6);
            if (uiLen != 8) {
                iRet = -1;
            }
        }
    }

    ///< hash算法标识,SHA1 为01,SM3 为 04
    if (!iRet) {
        uiLen = sizeof(capkItem.m_HashInd);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x06", &capkItem.m_HashInd, &uiLen);
    }

    ///< 签名算法标识 00>国际,04-sm
    if (!iRet) {
        uiLen = 1;
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x07", buff, &uiLen);
        if (!iRet) {
            capkItem.m_ArithInd = AIRTH_IND_RSA;
            if (buff[0] == 0x04){
                capkItem.m_ArithInd = AIRTH_IND_SM;
            }
        }
    }

    if (!iRet) {
        iRet = EMV_CapkList_Add_NoCheck_App(&capkItem);
#if DEBUG_EMV_DOWN_PARAM
        LOGD("[%s:%5d]iRet:%d", __func__, __LINE__, iRet);
#endif
    }
    return iRet;
}

AID_DOWN_INFO *EMV_AID_GetDownInfo(int index)
{
    if (index < 0 || index > MAX_AID_LIST) {
        return NULL;
    }
    return &g_downEmvParamList.apiList[index];
}

//查询获取AID下载列表
int EMV_AID_DownListUnpack(unsigned char *paucParam, int uiLen, int *pAIDNum)
{
    int iAIDNum = 0;
    unsigned char ucAIDLen = 0;
    unsigned char* pucParamEnd = NULL;

    iAIDNum = *pAIDNum;
    pucParamEnd = paucParam + uiLen;
    while (paucParam < pucParamEnd && iAIDNum < MAX_AID_LIST)
    {
        if (memcmp(paucParam, "\x9F\x06", 2)) {
            goto ERR;
        }
        paucParam += 2;

        ucAIDLen = *paucParam;
        if (ucAIDLen > 17) {
            goto ERR;
        }
        paucParam++;
        memcpy(&g_downEmvParamList.apiList[iAIDNum].aucAID, paucParam, ucAIDLen);
        g_downEmvParamList.apiList[iAIDNum].ucLen = ucAIDLen;
        paucParam += ucAIDLen;
        iAIDNum++;
    }
    *pAIDNum = iAIDNum;
    return 0;
ERR:
    return -1;
}

/*下载AID参数*/
int EMV_AID_DownUnpack(unsigned char *revData, int revDataLen)
{
    int iRet;
    unsigned char buff[64] = { 0 };
    unsigned short uiLen = 0;
    EMV_AID_ITEM aidItem = { 0 };
    IC_TRANS_INFO m_EMVTagInfo = {0};

    iRet = EMV_ParamDown_Init(&m_EMVTagInfo, EMVParamAIDInfo, sizeof(EMVParamAIDInfo)/sizeof(EMV_TAG_ATTR));
    if (!iRet) {
        m_EMVTagInfo.aucTransInfo = revData;
        m_EMVTagInfo.uiTransInfoLen = revDataLen;
        iRet = EMV_ParamDown_Unpack(&m_EMVTagInfo);
    }

    memset(&aidItem, 0, sizeof(aidItem));

    ///< AID
    if (!iRet) {
        uiLen = sizeof(aidItem.m_AID);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x06", aidItem.m_AID, &uiLen);
        if (!iRet) {
            aidItem.m_uiAID = uiLen;
        }
    }

    ///< 选择指示符:1-全匹配, 0-部分匹配
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x01", buff, &uiLen);
        if (!iRet) {
            if (buff[0])
            {
                aidItem.m_PartMach = 1;
            }
            else
            {
                aidItem.m_PartMach = 0;
            }
        }
    }

    ///< Application Version Number(Terminal) 终端应用版本号
    if (!iRet) {
        uiLen = sizeof(aidItem.m_AppVersion);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x08", aidItem.m_AppVersion, &uiLen);
        if (!iRet && uiLen != sizeof(aidItem.m_AppVersion)) {
            iRet = -1;
        }

        ///< 如果9F08找不到, 那么继续找9F09
        if (iRet) {
            uiLen = sizeof(aidItem.m_AppVersion);
            iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x09", aidItem.m_AppVersion, &uiLen);
            if (!iRet && uiLen != sizeof(aidItem.m_AppVersion)) {
                iRet = -1;
            }
        }
    }

    ///< TAC 缺省
    if (!iRet) {
        uiLen = sizeof(aidItem.m_TAC_Default);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x11", aidItem.m_TAC_Default, &uiLen);
        if (!iRet && uiLen != sizeof(aidItem.m_TAC_Default)) {
            iRet = -1;
        }
    }

    ///< TAC 联机
    if (!iRet) {
        uiLen = sizeof(aidItem.m_TAC_Online);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x12", aidItem.m_TAC_Online, &uiLen);
        if (!iRet && uiLen != sizeof(aidItem.m_TAC_Online)) {
            iRet = -1;
        }
    }

    ///< TAC 拒绝
    if (!iRet) {
        uiLen = sizeof(aidItem.m_TAC_Denial);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x13", aidItem.m_TAC_Denial, &uiLen);
        if (!iRet && uiLen != sizeof(aidItem.m_TAC_Denial)) {
            iRet = -1;
        }
    }

    ///< Terminal Floor Limit 最低限额
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x1B", buff, &uiLen);
        if (!iRet) {
            if (uiLen == sizeof(aidItem.m_TerminalFloorLimit)) {
                aidItem.m_TerminalFloorLimit = tools_hex_long(buff, uiLen);
            }
            else {
                iRet = -1;
            }
        }
    }

    ///< 偏置随机选择的阈值
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x15", buff, &uiLen);
        if (!iRet) {
            if (uiLen == sizeof(aidItem.m_TresholdValue)) {
                aidItem.m_TresholdValue = tools_hex_long(buff, uiLen);
            }
            else {
                iRet = -1;
            }
        }
    }

    ///< 偏置随机选择的最大目标百分数
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x16", buff, &uiLen);
        if (!iRet) {
            if (uiLen == sizeof(unsigned char)) {
                aidItem.m_MaxTargetPercentage = tools_bcd_long(buff, 2);
            }
            else {
                iRet = -1;
            }
        }
    }

    ///< 随机选择的目标百分数
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x17", buff, &uiLen);
        if (!iRet) {
            if (uiLen == sizeof(unsigned char)) {
                aidItem.m_TargetPercentage = tools_bcd_long(buff, 2);
            }
            else {
                iRet = -1;
            }
        }
    }

    ///< DEFAULT DDOL
    if (!iRet) {
        uiLen = sizeof(aidItem.m_Default_DDOL);
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x14", aidItem.m_Default_DDOL, &uiLen);
        if (!iRet) {
            aidItem.m_Default_DDOL_Len = uiLen;
        }
    }

    ///< 终端联机能力
#if 0
    if (!iRet) {
        uiLen = sizeof(buff);
        memset(buff, 0, sizeof(buff));
        iRet = EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x18", buff, &uiLen);
        if (!iRet) {
            if (uiLen == sizeof(unsigned char)) {
                aidItem.m_OnlinePinSpt = 1;
                if (!buff[0]) {
                    aidItem.m_OnlinePinSpt = 0;
                }
            }
            else {
                iRet = -1;
            }
        }
    }
#else
    aidItem.m_OnlinePinSpt = 1; // 默认为1
#endif

    ///< 终端电子现金交易限额
    if (!iRet) {
        uiLen = 6;
        memset(buff, 0, sizeof(buff));
        if (!EMV_GetTagValue(&m_EMVTagInfo, "\x9F\x7B", buff, &uiLen)) {
            if (uiLen > 0 && uiLen <= 6) {
                aidItem.m_ucECTSIFlag = 0;    ///< 不支持电子现金
                aidItem.m_EC_Trans_Limite = tools_bcd_long(buff, uiLen*2);
            }
        }
    }

    ///< 非接触读写器脱机最低限额
    if (!iRet) {
        uiLen = 6;
        memset(buff, 0, sizeof(buff));
        if (!EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x19", buff, &uiLen)) {
            if (uiLen > 0 && uiLen <= 6) {
                aidItem.m_ContactlessFloorLimit = tools_bcd_long(buff, uiLen*2);
            }
        }
    }

    ///< 非接触读写器交易限额
    if (!iRet) {
        uiLen = 6;
        memset(buff, 0, sizeof(buff));
        if (!EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x20", buff, &uiLen)) {
            if (uiLen > 0 && uiLen <= 6) {
                aidItem.m_ContactlessTransLimit = tools_bcd_long(buff, uiLen*2);
            }
        }
     }

    ///< 读写器持卡人验证方法（CVM） 所需限制（CVM 交易限额）
    if (!iRet) {
        uiLen = 6;
        memset(buff, 0, sizeof(buff));
        if (!EMV_GetTagValue(&m_EMVTagInfo, "\xDF\x21", buff, &uiLen)) {
            if (uiLen > 0 && uiLen <= 6) {
                aidItem.m_ContactlessCVMAmount = tools_bcd_long(buff, uiLen*2);
            }
        }
    }

    if (!iRet) {
        iRet = EMV_AidList_Add_App(&aidItem);
#if DEBUG_EMV_DOWN_PARAM
        LOGD("[%s:%5d]add aid:%d", __func__, __LINE__, iRet);
#endif
    }
    return iRet;
}

/*下载非接参数*/
int EMV_Untouch_DownUnpack(unsigned char *revData, int revDataLen)
{
    int iRet;
    unsigned char buff[64] = { 0 };
    unsigned short uiLen = 0;
    IC_TRANS_INFO m_EMVTagInfo = {0};

    iRet = EMV_ParamDown_Init(&m_EMVTagInfo, EMVParamUntouchInfo, sizeof(EMVParamUntouchInfo)/sizeof(EMV_TAG_ATTR));
    if (!iRet) {
        m_EMVTagInfo.aucTransInfo = revData;
        m_EMVTagInfo.uiTransInfoLen = revDataLen;
        iRet = EMV_ParamDown_Unpack(&m_EMVTagInfo);
    }
    if (iRet) {
        goto ERR;
    }

    ///< FF 805D 非接优先选择(0.联机,1.脱机)
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x5D", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("805D", buff, uiLen);
#endif
    }

    ///< FF 8058 非接快速业务(QPS)免密限额
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x58", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8058", buff, uiLen);
#endif
        DataChange.QPS_PINAmtLimit = tools_asc_long(buff, uiLen);
    }

    ///< FF 8054 非接快速业务标识
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x54", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8054", buff, uiLen);
#endif
        DataChange.QPS_NoPIN_Flag = buff[0] - '0';
    }

    ///< FF 8055 BIN A
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x55", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8055", buff, uiLen);
#endif
        DataChange.QPS_BINA_Flag = buff[0] - '0';
    }

    ///< FF 8056 BIN B
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x56", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8056", buff, uiLen);
#endif
        DataChange.QPS_BINB_Flag = buff[0] - '0';
    }

    ///< FF 8057 CD-CVM
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x57", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8057", buff, uiLen);
#endif
        DataChange.QPS_CDCVM_Flag = buff[0] - '0';
    }

    ///< FF 8059 免签限额
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x59", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("8059", buff, uiLen);
#endif
        DataChange.QPS_SignatureAmtLimit = tools_asc_long(buff, uiLen);
    }

    ///< FF 805A 免签标识
    uiLen = sizeof(buff);
    memset(buff, 0, sizeof(buff));
    if (!EMV_GetTagValue(&m_EMVTagInfo, "\xFF\x80\x5A", buff, &uiLen)) {
#if DEBUG_EMV_DOWN_PARAM
        logger_serial_dump_buff("805A", buff, uiLen);
#endif
        DataChange.QPS_Signature_Flag = buff[0] - '0';
    }

ERR:
    return iRet;
}

