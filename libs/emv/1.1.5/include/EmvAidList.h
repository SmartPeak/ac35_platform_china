#ifndef EMV_AID_LIST_H_
#define EMV_AID_LIST_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvTransHandle.h"

#define MAX_AID_LIST 32


// 获取aid个数
EMV_UINT32 EMV_AidList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);

// 获取aid对象
EMV_UINT32 EMV_AidList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_AID_ITEM pItem);

// 增加aid
EMV_UINT32 EMV_AidList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_AID_ITEM pItem);

// 删除aid
EMV_UINT32 EMV_AidList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);

// 删除aid对象通过aid
EMV_UINT32 EMV_AidList_DeleteByAID(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pAID, EMV_UINT16 uiAID);

// 情况aid对象列表
EMV_UINT32 EMV_AidList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);

// 获取匹配的aid对象
EMV_BOOL EMV_AidList_GetMatchItem(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pAid, EMV_UINT32 uiAid, LP_EMV_AID_ITEM pItem);
		
#ifdef __cplusplus
}
#endif
		
#endif
