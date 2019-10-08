/**
 * @deprecated ISO8583打包解包功能函数、常量声明
 * @author 韩雷
 * @date 2018/01/05
 */

#ifndef _ISO8583_H
#define _ISO8583_H

/*
 * 数据域个数，正常标准为64，如有需要可以为128
 */
#define ISO_MAX_FIELD 64

#define TYP_BIT 0
#define TYP_BCD 1
#define TYP_ASC 2
#define TYP_BIN 3

#define LEN_FIXED 0
#define LEN_LLVAR 2
#define LEN_LLLVAR 3

/*
 * ISO定义域结构定义
 */
typedef struct
{
    short type;
    short format;
    int len;
} tsField;

//设置iso8583交易属性表
int iso8583_SetISODef(tsField *pISODef, int (*pMacFun)(unsigned char *pDataIn, unsigned int inLen, unsigned char *pDataOut));

/*_______________________________ 自定义封装 _____________________________________*/
int ISO8583_Clear(void);
void ISO8583_Free(void);
void ISO8583_SetMsgID(char *data);
int ISO8583_LoadData(unsigned char *pDataIn);
int ISO8583_LoadBitData(int index, unsigned char *data, int *len);
int ISO8583_SetBit(int index, unsigned char *data, int len);
int ISO8583_GetBit(int index, unsigned char *data, int *len);
int ISO8583_CompareBit(int bitNo);
int ISO8583_DelBit(int index);
int ISO8583_Pack(unsigned char *buffer, unsigned int *pLen);
int ISO8583_Unpack(unsigned char *buffer);
/*__________________________ 备份封装函数 ________________________________*/
int ISO8583_ClearBackup(void);
int ISO8583_SetBackupBit(int index, unsigned char *data, int len);
int ISO8583_CopyBitToBackup(int index);
int ISO8583_SaveBackup(unsigned char *pDataOut, unsigned short *pDataOutLen);
int ISO8583_GetSendBit(int index, unsigned char *data, int *len);///< 获取发送包指定域数据

#endif
