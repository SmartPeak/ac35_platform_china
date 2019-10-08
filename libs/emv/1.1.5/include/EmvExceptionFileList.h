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

// 获取黑名单个数
EMV_UINT32 EMV_ExceptList_GetCount(LP_EMV_TRANS_HANDLE pTransHandle);
// 获取黑名单对象
EMV_UINT32 EMV_ExceptList_GetItem(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex, LP_EMV_EXCEPT_ITEM pItem);
// 增加黑名单	
EMV_UINT32 EMV_ExceptList_Add(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_EXCEPT_ITEM pItem);
// 删除黑名单		
EMV_UINT32 EMV_ExceptList_Delete(LP_EMV_TRANS_HANDLE pTransHandle,
		EMV_UINT32 uiIndex);
// 删除黑名单
EMV_UINT32 EMV_ExceptList_DeleteEx(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN, EMV_BYTE bSeq);
// 清空黑名单		
EMV_UINT32 EMV_ExceptList_Clear(LP_EMV_TRANS_HANDLE pTransHandle);
// 检查黑名单
EMV_BOOL EMV_ExceptList_Check(LP_EMV_TRANS_HANDLE pTransHandle,
		LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN, EMV_BYTE bSeq);
	
EMV_BOOL EMV_ExceptList_NoSeq_Check(LP_EMV_TRANS_HANDLE pTransHandle,
	LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN);
		
#ifdef __cplusplus
}
#endif
		
#endif
