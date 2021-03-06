/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/

#ifndef __MERCURY_FOTA_H__
#define __MERCURY_FOTA_H__

#include "MercuryDef.h"

typedef enum
{
    STORE_INSIDE_FLASH = 0,
    STORE_FILE_SYSTEM,
    STORE_INSIDE_FLASH_EXT,    //仅在release 且不支持audio版本可使用
    IMG_STORE_MAX,
    MERCURY_ENUM_STORE_MAX = 0x7fffffff
}IMG_STORE_E;

typedef enum
{
    IMG_UPDATA_NOW = 0,
    IMG_UPDATA_NEXT_BOOT,
    IMG_UPDATA_NEVER,
    IMG_UPDATA_MAX,
    MERCURY_ENUM_UPDATE_MAX = 0x7fffffff
}IMG_UPDATE_E;

extern void FOTA_Init(void);
extern int FOTA_ImgInfoSet(IMG_STORE_E storeType, const uint8* name, IMG_UPDATE_E updataType);
extern uint32 FOTA_WroteLenGet(void);
extern int FOTA_FlashWrite(uint32 addr, const uint8 * buf,uint32 write_len);
extern int FOTA_FlashRead(uint32 addr, uint8* buf, uint32 read_len);

/*************************************************************************************
主应用刷次应用时需要flash操作
addr 范围0~1024kbyte
addr+readlen 不能大于1024kbyte

执行erase时，addr必须是32kbyte的整数倍，按32kbyte擦除
*************************************************************************************/
extern BOOLEAN APP_FlashWrite(uint32 addr, const uint8 * buf,uint32 read_len);
extern BOOLEAN APP_FlashErase(uint32 addr);
extern BOOLEAN APP_FlashRead(uint32 addr, uint8* buf, uint32 read_len);


extern int FOTA_RawDataInfoSet(uint32 cs_id, uint32 imgAddr, uint32 imgLen, uint32 enable);
extern int FOTA_RawDataClear(void);

extern BOOLEAN LOGO_FlashWrite(uint32 addr, const uint8 * buf,uint32 read_len);
extern BOOLEAN LOGO_FlashErase(uint32 addr);
extern BOOLEAN LOGO_FlashRead(uint32 addr, uint8* buf, uint32 read_len);

/*************************************************************************************
以下仅在release版本且不支持音频的版本中可用

fota img存储类型新增 IMG_STORE_E -- STORE_INSIDE_FLASH_EXT
使用方式，应用使用下面三个api将fota img写入，然后配置FOTA_ImgInfoSet(STORE_INSIDE_FLASH_EXT,NULL,IMG_UPDATA_NEXT_BOOT)即可

该区域大小32*1024*31kbyte = 992kbyte
客户次应用等亦可使用此区间，执行规划
*************************************************************************************/
extern BOOLEAN APP_FlashWriteExt(uint32 addr, const uint8 * buf,uint32 read_len);
extern BOOLEAN APP_FlashEraseExt(uint32 addr);
extern BOOLEAN APP_FlashReadExt(uint32 addr, uint8* buf, uint32 read_len);

#endif //__MERCURY_FOTA_H__
