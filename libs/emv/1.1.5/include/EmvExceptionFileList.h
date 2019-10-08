#ifndef EMV_EXCEPTION_FILE_LIST_H_
#define EMV_EXCEPTION_FILE_LIST_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvTransHandle.h"

#define MAX_EXCEPTION_FILE 20  // 100

struct EMV_EXCEPT_ITEM {
// 22
	EMV_UINT16 m_uiPAN;
	EMV_BYTE m_PAN[MAX_PAN];
	EMV_BYTE m_Seq;
};

typedef struct EMV_EXCEPT_ITEM * LP_EMV_EXCEPT_ITEM;
typedef const struct EMV_EXCEPT_ITEM * LPC_EMV_EXCEPT_ITEM;

// ��ȡ����������
EMV_UINT32 EMV_ExceptList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);
// ��ȡ����������
EMV_UINT32 EMV_ExceptList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_EXCEPT_ITEM pItem);
// ���Ӻ�����	
EMV_UINT32 EMV_ExceptList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_EXCEPT_ITEM pItem);
// ɾ��������		
EMV_UINT32 EMV_ExceptList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);
// ɾ��������
EMV_UINT32 EMV_ExceptList_DeleteEx(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN, EMV_BYTE bSeq);
// ��պ�����		
EMV_UINT32 EMV_ExceptList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);
// ��������
EMV_BOOL EMV_ExceptList_Check(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN, EMV_BYTE bSeq);
	
EMV_BOOL EMV_ExceptList_NoSeq_Check(LP_EMV_TRANS_HANDLE pTransHandle,
	LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN);
		
#ifdef __cplusplus
}
#endif
		
#endif
