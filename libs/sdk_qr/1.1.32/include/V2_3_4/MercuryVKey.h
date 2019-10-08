/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_VKEY_H_
#define _MERCURY_VKEY_H_

#include "MercuryDef.h"


#ifdef __cplusplus
    extern   "C"
    {
#endif
// customize
#define  VK_OK            0x01
#define VK_SCAN           0x29
#define VK_ENTER          0x2b
#define VK_ESC            0x2c

// system
#define  VK_POWER         0x02    // If a key is used as both  VK_POWER and  VK_CANCEL, only use  VK_POWER
#define  VK_CANCEL        0x03    // If a key is used as both  VK_POWER and  VK_CANCEL, only use  VK_POWER
#define VK_BACK           0x08
#define VK_CLEAR          0x0C
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28



// Define virtual key code.
/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */

#define  VK_0                ('0')   // 0x30 ~ 0x39
#define  VK_1                ('1')
#define  VK_2                ('2')
#define  VK_3                ('3')
#define  VK_4                ('4')
#define  VK_5                ('5')
#define  VK_6                ('6')
#define  VK_7                ('7')
#define  VK_8                ('8')
#define  VK_9                ('9')
#define  VK_STAR             ('*')   // 0x2a
#define  VK_POUND            ('#')   // 0x23
#define  VK_AT               ('@')   // 0x40  

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#define VK_VOLUME_DOWN    0xAE
#define VK_VOLUME_UP      0xAF
       
/*for qwery keypad*/            
#define  VK_Q             ('Q')
#define  VK_W             ('W')
#define  VK_E             ('E')
#define  VK_R             ('R')
#define  VK_T             ('T')
#define  VK_Y             ('Y')
#define  VK_U             ('U')
#define  VK_I             ('I')
#define  VK_O              ('O')
#define  VK_P              ('P')
#define  VK_A             ('A')
#define  VK_S             ('S')
#define  VK_D             ('D')
#define  VK_F              ('F')
#define  VK_G              ('G')
#define  VK_H              ('H')
#define  VK_J              ('J')
#define  VK_K              ('K')
#define  VK_L              ('L')
#define  VK_Z              ('Z')
#define  VK_X               ('X')
#define  VK_C               ('C')
#define  VK_V               ('V')
#define  VK_B               ('B')
#define  VK_N               ('N')
#define  VK_M               ('M')


#ifdef __cplusplus
    }
#endif

#endif  // _MERCURY_VKEY_H_

