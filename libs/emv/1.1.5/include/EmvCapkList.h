#ifndef EMV_CAPK_LIST_H_
#define EMV_CAPK_LIST_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvTransHandle.h"

#define MAX_CAPK_LIST   44

#define AIRTH_IND_RSA 0x01  // rsaǩ���㷨��ʶ
#define AIRTH_IND_SM  0x04 // �����㷨��ʶ

typedef struct  {
	// 294
	EMV_BYTE m_RID[SIZE_RID];
	EMV_BYTE m_CapkIndex;
	EMV_BYTE m_HashInd;           //HASH�㷨��־ 01->sha1,03->sha256,05->sha512,07->sm3
	EMV_BYTE m_ArithInd;          //ǩ���㷨��־ 01->RSA,04->SM2
	EMV_UINT16 m_uiModules;
	EMV_BYTE m_Modules[MAX_RSA_KEY_SIZE];
	EMV_UINT16 m_uiExponents;
	EMV_BYTE m_Exponents[MAX_RSA_EXPONENTS_SIZE];
	EMV_BYTE m_ExpDate[SIZE_EXP_DATE];    //��Ч��(YYMMDD)
	EMV_BYTE m_Checksum[20];
}EMV_CAPK_ITEM;

typedef  EMV_CAPK_ITEM * LP_EMV_CAPK_ITEM;
typedef const  EMV_CAPK_ITEM * LPC_EMV_CAPK_ITEM;


// ��ȡ��Կ����
EMV_UINT32 EMV_CapkList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);
// ��ȡ��Կ����
EMV_UINT32 EMV_CapkList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_CAPK_ITEM pItem);
// ��ȡ��Կ����		
EMV_UINT32 EMV_CapkList_GetItemEx(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pRID, EMV_BYTE Index, LP_EMV_CAPK_ITEM pItem);
// ���ӹ�Կ		
EMV_UINT32 EMV_CapkList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_CAPK_ITEM pItem);

EMV_UINT32 EMV_CapkList_Add_NO_Check(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_CAPK_ITEM pItem);

// ɾ����Կ		
EMV_UINT32 EMV_CapkList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);
// �����Կ�б�
EMV_UINT32 EMV_CapkList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);
// ��ȡ��Կ����
EMV_UINT32 EMV_CapkList_DeleteEx(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pRID, EMV_BYTE bIndex);
// ���
EMV_BOOL EMV_Capk_CheckChecksum(LPC_EMV_CAPK_ITEM pCapk);

#ifdef __cplusplus
}
#endif

#endif
