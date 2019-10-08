/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_KEYPAD_H_
#define _MERCURY_KEYPAD_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// keypad uid
typedef enum  _KEYPAD_UID_E
{
    UID_1 = 0,        
    UID_2, 
    UID_3,  
    UID_4,  
    UID_5,  
    UID_6,  
    UID_7,
    UID_8, 
    UID_9,
    UID_10,   
    UID_MAX,
    MERCURY_ENUM_KPDUID_MAX = 0x7fffffff
}KEYPAD_UID_E;

// Definition for Keypad message
typedef enum
{
    // Keypad message.
    MC_KPD_KEYDOWN,
    MC_KPD_KEYUP,
    MC_KPD_KEYPRESS,
    MC_KPD_RESERVED1,          // User cann't use it
    MC_KPD_MSG_MAX,
    MERCURY_ENUM_KPDMSG_MAX = 0x7fffffff
} MC_KPD_MSG_E;


INT KP_Init(void);
INT KP_Deinit(void);
INT KP_RegisterApp(KEYPAD_UID_E uid, VOID(*kpCallback)(UINT,UINT,UINT));
INT KP_DeregisterApp(KEYPAD_UID_E uid);
INT KP_SetFocus(KEYPAD_UID_E uid);
INT KP_SetKeyPressSound(BOOL bEnabled);
INT KP_SetBlackLight(UINT brightness);
VOID  KeypadCallBackFunc(KEYPAD_UID_E uid,UINT singleCode,UINT keyCode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MERCURY_KEYPAD_H_

