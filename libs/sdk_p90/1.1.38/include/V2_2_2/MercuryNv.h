/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_NV_H__
#define __MERCURY_NV_H__
#include "MercuryDef.h"

//nv item id form 0 to 499
#define NV_ITEM_NUM_MAX   500
#define NV_APPINFO_LEN          640

extern int NV_Init(void);
extern int NV_Deinit(void);
extern int NV_Read(WORD ItemID,WORD cchSize, BYTE *pBuf);
extern int NV_Write(WORD ItemID, WORD cchSize, BYTE *pBuf);
extern int NV_Delete(WORD ItemID);
extern int NV_AppInfoRead(void* pAppInfo, DWORD len);
extern int NV_AppInfoWrite(void* pAppInfo, DWORD len);


#endif //__MERCURY_NV_H__

