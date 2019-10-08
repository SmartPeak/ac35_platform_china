#ifndef EMV_UTIL_H
#define EMV_UTIL_H


#ifdef __cplusplus
extern "C" {
#endif

int TlvAppendAscii(unsigned int Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen);

/*
//idx=TlvAppend(0x9f21, buf1, 0,buff,idx,3);
Tag:要封装的tag
srcData:原数据
srcOffset:原数据起始位置
dstData:目的数据
dstOffset:目的数据起始位置
srcLen:原数据长度
以tlv的格式封装数据到buff中,返回值为buff的当前索引
*/
int TlvAppend(unsigned long Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen);

///< input off-online pin
int EMV_UTIL_InputOffPlainPinPwd(unsigned int dispLine, unsigned int column, char bPinByPass, int *bVerifyPinTryCnt, int timeout);

///< input off-online pin
int EMV_UTIL_InputOffCipherPinPwd(unsigned int dispLine,
                                  unsigned int column,
                                  char bPinByPass,
                                  int *bVerifyPinTryCnt,
                                  unsigned char *pinCipherItem,
                                  int timeout);

///< input online pin
int EMV_UTIL_InputOnlinePIN(unsigned int dispLine, unsigned int column, const char* panData, unsigned char *pinBlock, unsigned int *pinBlockSize, unsigned short timeout);

int EMV_GetTagValueFromStr(unsigned char* aucTagStr,
                           unsigned int uiTagStrLen,
                           unsigned char* aucTag,
                           unsigned char* aucTagValue,
                           unsigned short* uiTagValueLen);

#ifdef __cplusplus
}
#endif

#endif
