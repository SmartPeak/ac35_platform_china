#ifndef EMV_TRANS_H_
#define EMV_TRANS_H_

#ifdef __cplusplus
extern   "C"
{
#endif

int EMVErr_SetCLErrCode(int ret);
int EMVErr_SetCTErrCode(int ret);


///< Get field 55
int EMV_UnpackField55(unsigned char *buff, unsigned int buffSize, unsigned char *pTempBuff, unsigned int tempBuffSize);

///< Set field 55 (type: 1-query, 2-reversal)
int EMV_GetField55(unsigned char type, unsigned char *buff, unsigned int buffSize, unsigned int *outLen);
///< Set field 55
int EMV_GetReversalField55(unsigned char *buff, unsigned int buffSize, unsigned int *outLen);
///< Set field 55
int EMV_GetScriptField55(unsigned char *buff, unsigned int buffSize, unsigned int *outLen);

///< Get IC Inof
void EMV_GetICCardInfo(void);

char EMV_Trans_InitEntryKernel(void);

int EMV_LoadConfig(void);
int EMV_Trans(void);

int Kernel_GetResult(void);

///< ��ʾ������
void EMV_DisplayProcessing(void);

///< ����
int EMV_InputAmount(unsigned int *amount);

///< ��ʾ���˺�
int EMV_DisplayPanNo(const char* pPanNo);

///< ����PIN����
int EMV_InputOnlinePIN(const char *panData, unsigned char *pinBlock, unsigned short *pPinBlockBuffSize);

///< �ѻ�����PIN����
int EMV_InputOffPlainPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt);

///< �ѻ�����PIN����
int EMV_InputOffCipherPinPwd(char bPinByPass, char bPinTryCnt, int *bVerifyPinTryCnt, unsigned char* pVerifyResult);

///< ��������
int EMV_TransOnline(void);

#ifdef __cplusplus
}
#endif

#endif
