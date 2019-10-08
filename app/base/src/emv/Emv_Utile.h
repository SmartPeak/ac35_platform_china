#ifndef EMV_UTIL_H
#define EMV_UTIL_H


#ifdef __cplusplus
extern "C" {
#endif

int TlvAppendAscii(unsigned int Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen);

/*
//idx=TlvAppend(0x9f21, buf1, 0,buff,idx,3);
Tag:Ҫ��װ��tag
srcData:ԭ����
srcOffset:ԭ������ʼλ��
dstData:Ŀ������
dstOffset:Ŀ��������ʼλ��
srcLen:ԭ���ݳ���
��tlv�ĸ�ʽ��װ���ݵ�buff��,����ֵΪbuff�ĵ�ǰ����
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
