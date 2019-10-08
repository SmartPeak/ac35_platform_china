#ifndef _EMV_DOWN_PARAM_H_
#define _EMV_DOWN_PARAM_H_

///< AID down info
typedef struct
{
    unsigned char ucLen;
    unsigned char aucAID[16];
}AID_DOWN_INFO;

///< CAPK down info
typedef struct
{
    unsigned char RID[5];
    unsigned char CAPKI;
    unsigned char ExpireDate[8];
}CAPK_DOWN_INFO;

#ifdef __cplusplus
extern "C"
{
#endif

int EMV_DownParam_ClearGlobalData(void);
/*======================================
  API DOWN
*======================================*/
extern int EMV_AidList_Clear_App(void);
AID_DOWN_INFO *EMV_AID_GetDownInfo(int index);
//��ȡAID�����б�
int EMV_AID_DownListUnpack(unsigned char *paucParam, int uiLen, int *pAIDNum);
/*����AID����*/
int EMV_AID_DownUnpack(unsigned char *revData, int revDataLen);
/*���طǽӲ���*/
int EMV_Untouch_DownUnpack(unsigned char *revData, int revDataLen);
/*======================================
  CAPK DOWN
*======================================*/
extern int EMV_CapkList_Clear_App(void);
CAPK_DOWN_INFO *EMV_CAPK_GetDownInfo(int index);
//��ȡCAPK�����б�
int EMV_CAPK_DownListUnpack(unsigned char *paucParam, int uiLen, int *pCAPKNum);
/*����capk����*/
int EMV_CAPK_DownUnpack(unsigned char *revData, int revDataLen);

#ifdef __cplusplus
}
#endif

#endif
