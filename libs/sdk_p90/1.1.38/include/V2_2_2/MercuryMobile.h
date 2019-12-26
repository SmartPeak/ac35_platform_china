/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef __MERCURY_MOBILE_H__
#define __MERCURY_MOBILE_H__

#include "MercuryDef.h"

typedef enum
{
    CHSET_IRA = 0,    /*0: International reference alphabet*/
    CHSET_GSM,        /*1: GSM 7 bit default alphabet */
    CHSET_HEX,        /*2: Character strings consist only of hexadecimal numbers from 00 to FF*/
    CHSET_UCS2,       /*3: 16-bit universal multiple-octet coded character set*/
    CHSET_MAX_NUM,
    MERCURY_ENUM_SMSCHARACTER_MAX = 0x7fffffff
} SMS_CHARACTER_SET_TYPE_E;

typedef enum
{
    SMS_SIM_NOT_READY = 1,
    SMS_IS_SENDING,
    SMS_NUM_ERR,
    SMS_MSG_LEN_ERR,
    SMS_MSG_ERR,
    ENCODE_USER_DATA_ERR,
    SMS_SEND_ERR,
    SMS_SC_NUM_ERR,
    SMS_MSG,
    MERCURY_ENUM_SMSERROR_MAX = 0x7fffffff
}SMS_ERROR_E;

typedef struct
{
    short index;
    short phoneNumLen;
    char   phoneNum[28];
    short msgLen;
    char   msg[500];
}SMS_REC_TEXT_S;

typedef struct
{
    short index;
    short msgLen;
    char   msg[500];
}SMS_REC_PDU_S;

extern int SmsReadText(BYTE index,SMS_CHARACTER_SET_TYPE_E type);
extern int SmsReadPdu(BYTE index);
extern int SmsSendText(BYTE*  pNum, BYTE numLen,SMS_CHARACTER_SET_TYPE_E type,BYTE* pMsg,BYTE msgLen);
extern int SmsSendPdu(BYTE* pPduStr, DWORD len);
extern int SmsDelete(BYTE index);

extern int TelephonyDial(BYTE* NUM);
extern int TelephonyAnswer(void);
extern int TelephonyHangup(void);

#endif //__MERCURY_MOBILE_H__

