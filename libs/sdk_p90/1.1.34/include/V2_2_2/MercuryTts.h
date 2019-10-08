/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_TTS_H_
#define _MERCURY_TTS_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* the range of voice speed value is from -32768 to +32767 */
#define MC_TTS_SPEED_MIN                 -32768      /* slowest voice speed */
#define MC_TTS_SPEED_NORMAL              0           /* normal voice speed (default) */
#define MC_TTS_SPEED_MAX                 +32767      /* fastest voice speed */

/* the range of voice tone value is from -32768 to +32767 */
#define MC_TTS_PITCH_MIN                 -32768      /* lowest voice tone */
#define MC_TTS_PITCH_NORMAL              0           /* normal voice tone (default) */
#define MC_TTS_PITCH_MAX                 +32767      /* highest voice tone */


typedef struct
{
    int SpeakSpeed;
    int Pitch;
}TTS_PARAM_S;



int TTS_Init(void);
int TTS_Deinit(void);
int TTS_SetParams(TTS_PARAM_S* mode);
int TTS_GetParams(TTS_PARAM_S* mode);
int TTS_PlayText(const uint8 * text, int len);
int TTS_Abort(void);

int PCM_StartPlay(void);
int PCM_FillData(uint8 * chBuf,uint32 nSize);
int PCM_StopPlay(void);

/*
成对使用，amr play之后，需要调用stop play，再进行其它播放
*/
int AMR_StartPlay(uint8* pucData, uint32 uiDataLength);
int AMR_StopPlay(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
