#ifndef EMV_AID_LIST_H_
#define EMV_AID_LIST_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvTransHandle.h"

#define MAX_AID_LIST 32


// ��ȡaid����
EMV_UINT32 EMV_AidList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);

// ��ȡaid����
EMV_UINT32 EMV_AidList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_AID_ITEM pItem);

// ����aid
EMV_UINT32 EMV_AidList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_AID_ITEM pItem);

// ɾ��aid
EMV_UINT32 EMV_AidList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);

// ɾ��aid����ͨ��aid
EMV_UINT32 EMV_AidList_DeleteByAID(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pAID, EMV_UINT16 uiAID);

// ���aid�����б�
EMV_UINT32 EMV_AidList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);

// ��ȡƥ���aid����
EMV_BOOL EMV_AidList_GetMatchItem(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pAid, EMV_UINT32 uiAid, LP_EMV_AID_ITEM pItem);
		
#ifdef __cplusplus
}
#endif
		
#endif
