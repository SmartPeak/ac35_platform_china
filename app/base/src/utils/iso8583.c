#include "bwsdk_api.h"
#include "logger.h"
#include "utils.h"
#include "iso8583.h"
#include "trans_err.h"

#ifdef TAG
#undef TAG
#endif
#define TAG "iso8583.c"

#define OPEN_DEBUG_ISO8583      0

/*!< ------------------------- err code -----------------------*/
#define ISO8583_SUCCESS                 SUCCESS
#define ISO8583_ERR_DATA_PACK           ERR_DATA_PACK
#define ISO8583_ERR_DATA_UNPACK         ERR_DATA_UPACK
#define ISO8583_ERR_DATA_COMPARE        ERR_FIELD_CMP
#define ISO8583_ERR_DATA_MAC            ERR_MAC
/*!< ----------------------------------------------------------*/


#define MY_BITGET(p, n) ((p)[(n - 1) / 8] & (0x80 >> ((n - 1) % 8)))     //取bit位
#define MY_BITSET(p, n) ((p)[(n - 1) / 8] |= (0x80 >> ((n - 1) % 8)))    //设bit位
#define MY_BITCLR(p, n) ((p)[(n - 1) / 8] &= (~(0x80 >> ((n - 1) % 8)))) //清bit位

/*
 * ISO数据域结构定义
 */
typedef struct
{
    struct tagISO_FLD
    {
        int len;
        uchar *buf;
    } field[ISO_MAX_FIELD + 1];
} tsIsoMsg;

//8583指向的配置表
static tsField *pG_ISODef = NULL;
static tsIsoMsg sendIso;
static tsIsoMsg recvIso;
int (*pG_MacFun)(unsigned char *pDataIn, unsigned int inLen, unsigned char *pDataOut) = NULL;

int iso8583_SetISODef(tsField *pISODef, int (*pMacFun)(unsigned char *pDataIn, unsigned int inLen, unsigned char *pDataOut))
{
    if (!pISODef) {
        return ERR_PARAM;
    }

    pG_ISODef = NULL;
    pG_ISODef = pISODef;

    pG_MacFun = NULL;
    pG_MacFun = pMacFun;

    return ISO8583_SUCCESS;
}

/**
 * @deprecated 全局变量isoMsg初始化
 * @param isoMsg
 */
int iso8583Init(tsIsoMsg *isoMsg)
{
    int i;

    if (!isoMsg) {
        return -1;
    }

    for (i = 0; i <= ISO_MAX_FIELD; i++)
    {
        //这里要判断i域是否有未释放空间；如果有，则需要释放
        if (isoMsg->field[i].buf)
        {
            free(isoMsg->field[i].buf);
        }
        isoMsg->field[i].buf = NULL;
        isoMsg->field[i].len = 0;
    }

    isoMsg->field[1].len = ISO_MAX_FIELD / 8;
    isoMsg->field[1].buf = (uchar *)malloc(isoMsg->field[1].len * sizeof(char) + 1);
    if (!isoMsg->field[1].buf)
    {
        return -1;
    }

    memset(isoMsg->field[1].buf, 0x00, isoMsg->field[1].len + 1);
    if(128 == ISO_MAX_FIELD)
    {
        isoMsg->field[1].buf[0] = 0x80;
    }
    return 0;
}

/**
 * @deprecated 设置报文数据域
 * @param isoMsg,全局变量
 * @param index,域索引
 * @param data,数据源
 * @param len,数据源长度
 */
int iso8583SetBit(tsIsoMsg *isoMsg, int index, const uchar *data, int len)
{
    if (!isoMsg || !pG_ISODef) {
        return ERR_PARAM;
    }

    if (len > pG_ISODef[index].len)
    {
        return ERR_PARAM;
    }
    if (index < 0 || index > ISO_MAX_FIELD)
    {
        return ERR_PARAM;
    }

    if (!data)
    {
        return ERR_PARAM;
    }

    if (isoMsg->field[index].buf != NULL)
    {
        free(isoMsg->field[index].buf);
        isoMsg->field[index].buf = NULL;
        isoMsg->field[index].len = 0;
    }

    isoMsg->field[index].len = len;
    isoMsg->field[index].buf = (uchar *)malloc(isoMsg->field[index].len * sizeof(char) + 1);
    if (isoMsg->field[index].buf == NULL)
    {
        return ERR_PARAM;
    }

    memcpy(isoMsg->field[index].buf, data, isoMsg->field[index].len);
    isoMsg->field[index].buf[len] = 0x00;

    //设置标志位
    if (index > 1)
    {
        MY_BITSET(isoMsg->field[1].buf, index);
    }

    return ISO8583_SUCCESS;
}

/**
 * @deprecated 复制报文数据域
 */
int iso8583CopyBit(int index, tsIsoMsg *isoDtsMsg, tsIsoMsg *isoSrcMsg)
{
    if (!isoDtsMsg || !isoSrcMsg || !pG_ISODef) {
        return ERR_PARAM;
    }

    if (isoSrcMsg->field[index].len > pG_ISODef[index].len)
    {
        return ERR_PARAM;
    }
    if (index < 0 || index > ISO_MAX_FIELD)
    {
        return ERR_PARAM;
    }

    if (!isoSrcMsg->field[index].len)
    {
        return ERR_PARAM;
    }

    if (isoDtsMsg->field[index].buf != NULL)
    {
        free(isoDtsMsg->field[index].buf);
        isoDtsMsg->field[index].buf = NULL;
        isoDtsMsg->field[index].len = 0;
    }

    isoDtsMsg->field[index].len = isoSrcMsg->field[index].len;
    isoDtsMsg->field[index].buf = (uchar *)malloc(isoSrcMsg->field[index].len * sizeof(char) + 1);
    if (isoSrcMsg->field[index].buf == NULL)
    {
        return ERR_PARAM;
    }

    memcpy(isoDtsMsg->field[index].buf, isoSrcMsg->field[index].buf, isoSrcMsg->field[index].len);
    isoDtsMsg->field[index].buf[isoSrcMsg->field[index].len] = 0x00;

    //设置标志位
    if (index > 1)
    {
        MY_BITSET(isoDtsMsg->field[1].buf, index);
    }
    return ISO8583_SUCCESS;
}

/**
 * @deprecated 获取报文数据域
 * @param isoMsg,数据源全局变量
 * @param index,域索引
 * @param data,目标缓冲区
 * @param len,获取数据长度
 */
int iso8583GetBit(const tsIsoMsg *isoMsg, int index, uchar *data, int *len)
{
    if (!isoMsg || !data || !len) {
        return -1;
    }

    if (isoMsg == NULL || isoMsg->field[index].buf == NULL)
    {
        return -1;
    }

    memcpy(data, isoMsg->field[index].buf, isoMsg->field[index].len);
    data[isoMsg->field[index].len] = 0x00;
    *len = isoMsg->field[index].len;

    return isoMsg->field[index].len;
}

/**
 * @deprecated 删除某个域
 * @param isoMsg,保存数据域的全局变量
 * @param index,待删除的位置索引
 */

int iso8583DeleteBit(tsIsoMsg *isoMsg, int index)
{
    if (!isoMsg) {
        return ERR_PARAM;
    }

    if (index < 2 || index > ISO_MAX_FIELD)
    {
        return ERR_PARAM;
    }
    if (!isoMsg)
    {
        return ERR_PARAM;
    }
    if (MY_BITGET(isoMsg->field[1].buf, index))
    {
        free(isoMsg->field[index].buf);
        isoMsg->field[index].buf = NULL;
        isoMsg->field[index].len = 0;
        MY_BITCLR(isoMsg->field[1].buf, index);
    }
    return ISO8583_SUCCESS;
}

/** 校验8585数据
 *  tag 1:校验消息类型
 *      0:比较数据相同与否
 *  返回:成功返回0
 *       失败返回-1
*/
int iso8583CompareSentBit(tsIsoMsg *recv, tsIsoMsg *send, int index)
{
    int len = 0;
    unsigned char recv_temp[30];
    unsigned char send_temp[30];

    if (!recv || !send) {
        return -1;
    }

    memset(recv_temp, 0x00, sizeof(recv_temp));
    memset(send_temp, 0x00, sizeof(send_temp));
    iso8583GetBit(recv, index, recv_temp, &len);
    iso8583GetBit(send, index, send_temp, &len);
#if OPEN_DEBUG_ISO8583
    LOGD("recv_temp = [%s] send_temp = [%s]\n", recv_temp, send_temp);
#endif
    if(len > 0)
    {
        if(index != 0)
        {
            if(strcmp((char *)recv_temp, (char *)send_temp) == 0)
            {
                return 0;
            }
        }
        else
        {
            if(atol((char *)recv_temp) - atol((char *)send_temp) == 10)
            {
                return 0;
            }
        }
    }
    return -1;
}

//打印
void iso8583Dump(int iBitNo, unsigned char *pData, short sDataLen)
{
    short i;

    if (!pData) {
        return;
    }

    PrintLogToCom_App((char *)"Bit[%02d: %3d]: ", iBitNo, sDataLen);
    for(i = 0; i < sDataLen; i++)
    {
        PrintLogToCom_App((char *)"%02X ", pData[i]);
        if((i+1) % 20 == 0)
        {
            PrintLogToCom_App((char*)"\r\n%14s", "");
        }
    }
    PrintLogToCom_App((char *)"\r\n");
    Sleep(100);
}

/**
 * @deprecated 8583报文打包
 * @param isoMsg,已设置数据域的全局变量
 * @param buffer,打包后存放数据的缓冲区
 */
int iso8583Pack(const tsIsoMsg *isoMsg, uchar *buffer, unsigned int *pLen)
{
    unsigned char *start = buffer;
    int i;
    char format[8] = {0};
    char temp[20];
    int len = 0;

    if (!isoMsg || !buffer || !pLen) {
        return ERR_PARAM;
    }

    //报文类型(0域)是强制的，且长度固定
    if (isoMsg->field[0].len != pG_ISODef[0].len || pG_ISODef[0].format != LEN_FIXED)
    {
#if OPEN_DEBUG_ISO8583
        LOGD("pack error,field = %d", 0);
#endif
        return ISO8583_ERR_DATA_PACK;
    }

    len = utilsAsc2Bcd(isoMsg->field[0].buf, isoMsg->field[0].len, buffer);
    buffer += len;

    //bitmap(1域)表明后面存在哪些域
    if (isoMsg->field[1].buf == NULL || pG_ISODef[1].len != 8)
    {
#if OPEN_DEBUG_ISO8583
        LOGD("pack error,pG_ISODef = %d", pG_ISODef[1].len);
        LOGD("pack error,field = %s", isoMsg->field[1].buf);
        LOGD("pack error,field = %d", 1);
#endif
        return ISO8583_ERR_DATA_PACK;
    }

    //bitmap位置不能手动设置，只能自动计算
    if ((isoMsg->field[1].len != 8) || (isoMsg->field[1].buf[0] & 0x80))
    {
#if OPEN_DEBUG_ISO8583
        LOGD("pack error,field2 = %d", 1);
#endif
        return ISO8583_ERR_DATA_PACK;
    }

    //待完善
    memcpy(buffer, isoMsg->field[1].buf, isoMsg->field[1].len);
#if OPEN_DEBUG_ISO8583
    iso8583Dump(1, buffer, isoMsg->field[1].len);
#endif
    buffer += isoMsg->field[1].len;

    for (i = 2; i < ISO_MAX_FIELD; i++)
    {
        //第i域不为空
        if (MY_BITGET(isoMsg->field[1].buf, i))
        {
            if (isoMsg->field[i].buf == NULL || isoMsg->field[i].len <= 0 || isoMsg->field[i].len > pG_ISODef[i].len)
            {
                LOGD("pack error,field3 = %d", i);
                return ISO8583_ERR_DATA_PACK;
            }

            //变长域的长度值
            if (pG_ISODef[i].format)
            { /* Variable length */
                //先拼出格式字符串，比如"%02d"、"%03d"
                snprintf(format, sizeof(format), "%%0%dd", pG_ISODef[i].format);
                //再将实际长度拼成buffer
                if (pG_ISODef[i].format % 2)
                {
                    memset(temp, 0, sizeof(temp));
                    *temp = '0';
                    snprintf(temp + 1, sizeof(temp) - 1, format, isoMsg->field[i].len);
                }
                else
                {
                    snprintf(temp, sizeof(temp), format, isoMsg->field[i].len);
                }
                len = utilsAsc2Bcd((uchar *)temp, pG_ISODef[i].format + pG_ISODef[i].format % 2, buffer);
                buffer += pG_ISODef[i].format / 2 + pG_ISODef[i].format % 2;
            }

            switch (pG_ISODef[i].type)
            {
            case TYP_BCD:
                if (27 == i)
                {
                    len = utilsAsc2BcdPrefix(isoMsg->field[i].buf, isoMsg->field[i].len, buffer);
                }
                else
                {
                    len = utilsAsc2Bcd(isoMsg->field[i].buf, isoMsg->field[i].len, buffer);
                }

#if OPEN_DEBUG_ISO8583
                iso8583Dump(i, buffer, len);
#endif
                buffer += len;
                break;
            case TYP_ASC:
            case TYP_BIN:
                memcpy(buffer, isoMsg->field[i].buf, isoMsg->field[i].len);

#if OPEN_DEBUG_ISO8583
                iso8583Dump(i, buffer, isoMsg->field[i].len);
#endif
                buffer += isoMsg->field[i].len;
                break;
            default:
#if OPEN_DEBUG_ISO8583
                LOGD("pack error,field4 = %d", i);
#endif
                return ISO8583_ERR_DATA_PACK;
            }
        }
    }

    if (MY_BITGET(isoMsg->field[1].buf, 64))
    {
        memset(temp, 0, sizeof(temp));
        if (pG_MacFun != NULL)
        {
            pG_MacFun(start, buffer - start, (uchar *)temp);
        }

        memcpy(buffer, temp, pG_ISODef[64].len);
        buffer += pG_ISODef[64].len;
    }

    *pLen = buffer - start;
    if (*pLen <= 0) {
        return ISO8583_ERR_DATA_PACK;
    }

    return ISO8583_SUCCESS;
}

/**
 * @deprecated 8583报文解包
 * @param isoMsg,解包后存放数据域的全局变量
 * @param buffer,存放待解包数据的缓冲区
 */
int iso8583Unpack(tsIsoMsg *isoMsg, const uchar *buffer)
{
    const uchar *start = buffer;
    int i;
    char format[8] = {0};
    uchar temp[20];
    int len;

    if (!isoMsg || !buffer) {
        return -1;
    }

    memset(format, 0, sizeof(format));

    //报文类型(0域)是强制的，且长度固定
    if (isoMsg->field[0].buf != NULL || pG_ISODef[0].format != LEN_FIXED)
    {
#if OPEN_DEBUG_ISO8583
        LOGD("unpack error,field = %d", 0);
#endif
        return -1;
    }

    isoMsg->field[0].len = pG_ISODef[0].len;
    isoMsg->field[0].buf = (uchar *)malloc((isoMsg->field[0].len) * sizeof(char) + 1);
    if (!isoMsg->field[0].buf)
    {
        return -2;
    }

    if (TYP_BCD == pG_ISODef[0].type)
    {
        len = utilsBcd2Asc(buffer, isoMsg->field[0].len / 2, isoMsg->field[0].buf);
        buffer += len / 2;
    }
    else
    {
        memcpy(isoMsg->field[0].buf, buffer, isoMsg->field[0].len);
        buffer += isoMsg->field[0].len;
    }
    isoMsg->field[0].buf[isoMsg->field[0].len] = 0x00;

    //8583报文只有64位情况，bitmap(1域)第1字节的第1位不能为1
    if (buffer[0] & 0x80)
    {
#if OPEN_DEBUG_ISO8583
        LOGD("unpack error,field = %d", 1);
#endif
        return -1;
    }

    if (!isoMsg->field[1].buf)
    {
        return -2;
    }
    memcpy(isoMsg->field[1].buf, buffer, isoMsg->field[1].len);
    isoMsg->field[1].buf[isoMsg->field[1].len] = 0x00;
    buffer += isoMsg->field[1].len;

    for (i = 2; i <= ISO_MAX_FIELD; i++)
    {
        //第i域不为空
        if (MY_BITGET(isoMsg->field[1].buf, i))
        {
            //变长域
            if (pG_ISODef[i].format)
            {
                //先拼出格式字符串，比如"%02d"、"%03d"
                snprintf(format, sizeof(format), "%%0%dd", pG_ISODef[i].format);
                //长度值占的位数
                len = pG_ISODef[i].format / 2 + pG_ISODef[i].format % 2;
                //取长度值
                memset(temp, 0x00, sizeof(temp));
                utilsBcd2Asc(buffer, len, temp);
                isoMsg->field[i].len = atoi((char *)temp);
                buffer += len;

                if (isoMsg->field[i].len > pG_ISODef[i].len)
                {
#if OPEN_DEBUG_ISO8583
                    LOGD("unpack error,field = %d", i);
#endif
                    return -1;
                }
            }
            else
            {
                isoMsg->field[i].len = pG_ISODef[i].len;
            }

            isoMsg->field[i].buf = (uchar *)malloc((isoMsg->field[i].len) * sizeof(char) + 1);
            if (!isoMsg->field[i].buf)
            {
                return -2;
            }

            switch (pG_ISODef[i].type)
            {
            case TYP_BCD:
                len = isoMsg->field[i].len / 2 + isoMsg->field[i].len % 2;
#if OPEN_DEBUG_ISO8583
                iso8583Dump(i, buffer, len);
#endif
                utilsBcd2Asc(buffer, len, isoMsg->field[i].buf);
                buffer += len;
                break;
            case TYP_ASC:
            case TYP_BIN:
                memcpy(isoMsg->field[i].buf, buffer, isoMsg->field[i].len);
#if OPEN_DEBUG_ISO8583
                if (i == 56)
                {
                    LOGD("\nBit[%02d:%3d]: %-20.20s\n", i, isoMsg->field[i].len, isoMsg->field[i].buf);
                }
                else
                {
                    iso8583Dump(i, buffer, isoMsg->field[i].len);
                }
#endif
                buffer += isoMsg->field[i].len;
                break;
            default:
#if OPEN_DEBUG_ISO8583
                LOGD("unpack error,field = %d", i);
#endif
                return -1;
            }
            isoMsg->field[i].buf[isoMsg->field[i].len] = 0x00;
        }
    }

    if (MY_BITGET(isoMsg->field[1].buf, 64))
    {
        memset(temp, 0, sizeof(temp));
        if (pG_MacFun != NULL)
        {
            pG_MacFun(start, buffer - start - pG_ISODef[64].len, (uchar *)temp);
        }

        if (memcmp(temp, isoMsg->field[64].buf, pG_ISODef[64].len))
            return -10;
    }
    
    return (buffer - start);
}

/**
 * @deprecated 释放保存各子域的全局变量
 * @param isoMsg,保存各子域的全局变量
 */
void iso8583Free(tsIsoMsg *isoMsg)
{
    int i;

    if (!isoMsg) {
        return;
    }

    for (i = 0; i <= ISO_MAX_FIELD; i++)
    {
        if (isoMsg->field[i].buf)
        {
            free(isoMsg->field[i].buf);
        }
        isoMsg->field[i].buf = NULL;
        isoMsg->field[i].len = 0;
    }
}

/*_______________________________ 自定义封装 _____________________________________*/
int ISO8583_Clear(void)
{
    if (iso8583Init(&sendIso) < 0)
        return ISO8583_ERR_DATA_PACK;
    if (iso8583Init(&recvIso) < 0)
        return ISO8583_ERR_DATA_PACK;
    return ISO8583_SUCCESS;
}

void ISO8583_Free(void)
{
    iso8583Free(&sendIso);
    iso8583Free(&recvIso);
}

int ISO8583_LoadData(unsigned char *pDataIn)
{
    if (iso8583Init(&recvIso) < 0)
        return ISO8583_ERR_DATA_PACK;

    if (iso8583Init(&sendIso) < 0)
        return ISO8583_ERR_DATA_PACK;

    if (iso8583Unpack(&sendIso, (const uchar *)pDataIn) < 0)
        return ISO8583_ERR_DATA_PACK;
    return ISO8583_SUCCESS;
}

int ISO8583_LoadBitData(int index, unsigned char *data, int *len)
{
   if (iso8583GetBit(&sendIso, index, data, len) < 0)
       return ISO8583_ERR_DATA_UNPACK;
   return ISO8583_SUCCESS;
}

void ISO8583_SetMsgID(char *data)
{
    iso8583SetBit(&sendIso, 0, (const uchar *)data, 4);
}

int ISO8583_SetBit(int index, unsigned char *data, int len)
{
#if OPEN_DEBUG_ISO8583
    LOGD("set bit>>>%02d\n", index);
#endif
    return iso8583SetBit(&sendIso, index, (const uchar *)data, len);
}

int ISO8583_GetBit(int index, unsigned char *data, int *len)
{
   if (iso8583GetBit(&recvIso, index, data, len) < 0)
       return ISO8583_ERR_DATA_UNPACK;
   return ISO8583_SUCCESS;
}

int ISO8583_CompareBit(int bitNo)
{
    if (iso8583CompareSentBit(&recvIso, &sendIso, bitNo) < 0) {
        if (0 == bitNo) {
            return ERR_MSG_CHECK;
        } else if (4 == bitNo) {
            return ERR_AMT_CHECK;
        } else if (11 == bitNo) {
            return ERR_VHN_CHECK;
        } else if (41 == bitNo) {
            return ERR_TID_CHECK;
        } else if (42 == bitNo) {
            return ERR_MID_CHECK;
        } else {
            return ISO8583_ERR_DATA_COMPARE;
        }
    }
    
    return ISO8583_SUCCESS;
}

int ISO8583_DelBit(int index)
{
    return iso8583DeleteBit(&sendIso, index);
}

int ISO8583_Pack(unsigned char *buffer, unsigned int *pLen)
{
    return iso8583Pack(&sendIso, buffer, pLen);
}

int ISO8583_Unpack(unsigned char *buffer)
{
    int iRet;

    iRet = iso8583Unpack(&recvIso, buffer);
    if (iRet < 0) {
        if (iRet == -10) {
            return ISO8583_ERR_DATA_MAC;
        }
        return ISO8583_ERR_DATA_UNPACK;
    }
    return ISO8583_SUCCESS;
}
/*__________________________ 备份封装函数 ________________________________*/
int ISO8583_ClearBackup(void)
{
    if (iso8583Init(&recvIso) < 0)
        return ISO8583_ERR_DATA_PACK;
    return ISO8583_SUCCESS;
}

int ISO8583_SetBackupBit(int index, unsigned char *data, int len)
{
    return iso8583SetBit(&recvIso, index, (const uchar *)data, len);
}

int ISO8583_CopyBitToBackup(int index)
{
    return iso8583CopyBit(index, &recvIso, &sendIso);
}

int ISO8583_GetSendBit(int index, unsigned char *data, int *len)
{
    if (iso8583GetBit(&sendIso, index, data, len) < 0)
        return ISO8583_ERR_DATA_UNPACK;
    return ISO8583_SUCCESS;
}

int ISO8583_SaveBackup(unsigned char *pDataOut, unsigned short *pDataOutLen)
{
    int iRet = ISO8583_SUCCESS;
    unsigned int iLen = 0;

    iRet = iso8583Pack(&recvIso, pDataOut, &iLen);
    *pDataOutLen = iLen;
    if (iso8583Init(&recvIso) < 0)
        return ISO8583_ERR_DATA_PACK;
    return iRet;
}

