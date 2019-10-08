/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_AUDIO_H__
#define __MERCURY_AUDIO_H__
#include "MercuryDef.h"

typedef enum
{
	AUDIO_MODE_HANDHOLD,
	AUDIO_MODE_HANDFREE,
	AUDIO_MODE_EARPHONE,
	AUDIO_MODE_EARFREE,
	AUDIO_MODE_MAX,
	MERCURY_ENUM_MODE_MAX = 0x7fffffff
}MERCURY_AUDIO_MODE_TYPE_E;

typedef enum
{
    AUDIO_VOLUME_LEVEL1 = 1,
    AUDIO_VOLUME_LEVEL2 = 2,
    AUDIO_VOLUME_LEVEL3 = 3,
    AUDIO_VOLUME_LEVEL4 = 4,
    AUDIO_VOLUME_LEVEL5 = 5,
    AUDIO_VOLUME_LEVEL6 = 6,
    AUDIO_VOLUME_LEVEL7 = 7,
    AUDIO_VOLUME_LEVEL8 = 8,
    AUDIO_VOLUME_LEVEL9 = 9,
    MERCURY_ENUM_VOLUME_MAX = 0x7fffffff
}AUDIO_VOLUME_LEVEL_E;

typedef enum
{
    DTMF_One,           // 1
    DTMF_Two,           // 2
    DTMF_Three,         // 3
    DTMF_letterA,       // A
    DTMF_Four,          // 4
    DTMF_Five,          // 5
    DTMF_Six,           // 6
    DTMF_letterB,       // B
    DTMF_Seven,         // 7
    DTMF_Eight,         // 8
    DTMF_Nine,          // 9
    DTMF_letterC,       // C
    DTMF_Star,          // *
    DTMF_Zero,          // 0
    DTMF_Pond,          // #
    DTMF_letterD,       // D
    DTMF_MAX_ID,         // Reserved, user can't use it.
    MERCURY_ENUM_DTMF_MAX = 0x7fffffff
} MERCURY_DTMF_TONE_ID_E;
extern int AudioSetChannel(MERCURY_AUDIO_MODE_TYPE_E channel);
extern MERCURY_AUDIO_MODE_TYPE_E AudioGetChannel(void);
extern int AudioSetVolume(DWORD volume);
extern int AudioGetVolume(void);
extern int AudioDtmfPlay(MERCURY_DTMF_TONE_ID_E tone,BYTE time);
extern void AudioDtmfAbort(void);
extern void AudioDtmfVolume(uint32 volume);
extern int AudioSingleTonePlay(uint32 freq,BYTE time);
extern void AudioSingleToneAbort(void);
extern void AudioSingleToneVolume(uint32 volume);
#endif //__MERCURY_AUDIO_H__

