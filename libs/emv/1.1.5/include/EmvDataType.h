#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#ifdef __cplusplus
extern   "C"
{
#endif

#include "EmvDataSize.h"

#define EMV_TRUE  1
#define EMV_FALSE 0

#if !defined(NULL)
#define NULL (void*)0
#endif

//typedef void			EMV_VOID;
#define EMV_VOID		void
typedef unsigned char EMV_BOOL; // 无符号
typedef char EMV_CHAR;// 有符号
typedef unsigned char EMV_BYTE;// 无符号
typedef signed char EMV_INT8; // 有符号
typedef short EMV_INT16;
typedef int EMV_INT32;
typedef unsigned char EMV_UINT8;
typedef unsigned short EMV_UINT16;
typedef unsigned int EMV_UINT32;
//typedef double EMV_AMOUNT;
typedef unsigned long EMV_AMOUNT;
//No change bellow data type define
typedef EMV_UINT32 EMV_TAG;
typedef EMV_VOID * LP_EMV_VOID;
typedef const EMV_VOID * LPC_EMV_VOID;
typedef EMV_BOOL * LP_EMV_BOOL; 	// *uchar
typedef const EMV_BOOL * LPC_EMV_BOOL;
typedef EMV_CHAR * LP_EMV_CHAR;		// *char  请求参数
typedef const EMV_CHAR * LPC_EMV_CHAR;//  响应参数
typedef EMV_BYTE * LP_EMV_BYTE;		// *uchar
typedef const EMV_BYTE * LPC_EMV_BYTE;
typedef EMV_INT8 * LP_EMV_INT8;
typedef const EMV_INT8 * LPC_EMV_INT8;
typedef EMV_INT16 * LP_EMV_INT16;
typedef const EMV_INT16 * LPC_EMV_INT16;
typedef EMV_INT32 * LP_EMV_INT32;
typedef const EMV_INT32 * LPC_EMV_INT32;
typedef EMV_UINT8 * LP_EMV_UINT8;
typedef const EMV_UINT8 * LPC_EMV_UINT8;
typedef EMV_UINT16 * LP_EMV_UINT16;
typedef const EMV_UINT16 * LPC_EMV_UINT16;
typedef EMV_UINT32 * LP_EMV_UINT32;
typedef const EMV_UINT32 * LPC_EMV_UINT32;
typedef EMV_TAG * LP_EMV_TAG;
typedef const EMV_TAG * LPC_EMV_TAG;
typedef unsigned long EMV_UINT64;
typedef EMV_AMOUNT * LP_EMV_AMOUNT;// *ulong

typedef struct {
	EMV_TAG m_Tag;
	EMV_UINT16 m_ValueLen;
	EMV_BYTE m_Value[MAX_DATA_SIZE];
}EMV_DATA;

typedef EMV_DATA * LP_EMV_DATA;
typedef const EMV_DATA * LPC_EMV_DATA;

#ifdef __cplusplus
}
#endif

#endif
