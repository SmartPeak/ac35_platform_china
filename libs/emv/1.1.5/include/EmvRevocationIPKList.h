#ifndef EMV_REVOCATION_IPK_LIST_H_
#define EMV_REVOCATION_IPK_LIST_H_

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvTransHandle.h"
#define MAX_REVO_IPK    20   // 100

struct EMV_REVO_IPK_ITEM {
	// 9
	EMV_BYTE m_RID[SIZE_RID];
	EMV_BYTE m_CapkIndex;
	EMV_BYTE m_SerialNo[3];
};

typedef struct EMV_REVO_IPK_ITEM * LP_EMV_REVO_IPK_ITEM;
typedef const struct EMV_REVO_IPK_ITEM * LPC_EMV_REVO_IPK_ITEM;

// 获取回收公钥个数
EMV_UINT32 EMV_RevoIPKList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);
// 获取回收公钥对象
EMV_UINT32 EMV_RevoIPKList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_REVO_IPK_ITEM pItem);
// 检查回收公钥		
EMV_BOOL EMV_RevoIPKList_Check(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_REVO_IPK_ITEM pItem);
// 增加回收公钥		
EMV_UINT32 EMV_RevoIPKList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_REVO_IPK_ITEM pItem);
// 删除回收公钥		
EMV_UINT32 EMV_RevoIPKList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);
// 清空回收公钥
EMV_UINT32 EMV_RevoIPKList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);
// 删除回收公钥
EMV_UINT32 EMV_RevoIPKList_DeleteEx(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_REVO_IPK_ITEM pItem);
		
#ifdef __cplusplus
}
#endif
		
#endif
