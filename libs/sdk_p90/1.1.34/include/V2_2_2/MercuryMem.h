/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_MEM_H__
#define __MERCURY_MEM_H__

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define    LMEM_FIXED           0
#define    LMEM_ZEROINIT     0x0040

extern HLOCAL LocalAlloc(UINT uFlags,UINT uBytes);
extern HLOCAL LocalReAlloc(void * memblock,UINT size);
extern HLOCAL LocalFree(HLOCAL hMem);
extern PVOID SecureZeroMemory(PVOID ptr,SIZE_T cnt);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif //__MERCURY_MEM_H__
