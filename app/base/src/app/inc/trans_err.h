#ifndef _TRANS_ERR_H
#define _TRANS_ERR_H

#include "applib_err.h"

enum ERR_INDEX
{
    ERR_PRINTER             = 0x09, ///< Printer error

    ///< COMMU ERR
    ERR_SOCKET              = 0x10,
    ERR_HOSTCODE            = 0xA0,
    ERR_COMMU_PARAM         = 0x11,
    ERR_COMMU_CONNECT       = 0x12,
    ERR_COMMU_SEND          = 0x13,
    ERR_COMMU_RECV          = 0x14,

    ///< secret key err
    ERR_SECREKEY_SAVE       = 0x17,
    ERR_SECREKEY_DATA_ERR,
    ERR_SECREKEY_ENCRYPTION,
    ERR_SAVE_KEY_KCV,               ///< ��ԿУ���
    ERR_CALC_KEY_KCV,               ///< ��ԿУ���,������ǩ��
    ERR_MAC,                        ///< mac wrong

    ///<
    ERR_DATA_OVERFLOW       = 0x25, ///< ���泬��
    ERR_DATA_INVALID,               ///< ��Ч����
    ERR_DATA_PACK,                  ///< Data package wrong
    ERR_DATA_UPACK,                 ///< Data unpackage wrong
    ERR_SM2_SIGN,                   ///< SM2 sign error

    ERR_CASHIER,                    ///< ��Ա

    ERR_NOT_LOGON,                  ///< δǩ��,����ǩ��
    ERR_PLZ_SETTLE,                 ///< ���Ƚ���
    ERR_ADMIN_LOGON,                ///< ���ܲ��ܽ���,����ǩ��
    ERR_BATCH,                      ///< ���β���,��ǩ��
    ERR_STORE_KEY,                  ///< ��Կ����,��ǩ��
    ERR_TRANS_FULL,                 ///< ��������,�����
    ERR_TRANS_EMPTY,                ///< �޽�����ˮ
    ERR_TRANS_NOFIND,               ///< ԭ���ײ�����
    ERR_TRANS_NOVOID,               ///< �ѳ�����֧��
    ERR_NEED_REPRINT,               ///< ��Ҫ�ش�ӡ��һ�ʽ���
    ERR_AMOUNT_OVERFLOW,            ///< �˻�����

    ERR_VOID_CARD_DIFFER,           ///< �˿�Ų�һ��
    ERR_PWD_CASH_PASS,              ///< �������
    ERR_PWD_NO_PASSWORD,            ///< no password
    ERR_PWD_PIN_ERR,
    ERR_PWD_PIN_BLOCK,
    ERR_PWD_OTHER_ERR,
    ERR_FUNC_CLOSE,                 ///< �ù����ݲ�֧��
    ERR_EMV_CT,
    ERR_EMV_CL,
    ERR_FIELD_CMP,
    ///<------add esign-------->///
    ERR_INPUT_FORMAT,               ///< �����ʽ����,����������
    ///<----------------------->///
    ERR_MSG_CHECK,                  ///< ��Ϣ���Ͳ�ƥ��
    ERR_AMT_CHECK,                  ///< ���׽�ƥ��
    ERR_VHN_CHECK,                  ///< ��ˮ�Ų�ƥ��
    ERR_TID_CHECK,                  ///< �ն˺Ų�ƥ��
    ERR_MID_CHECK,                  ///< �̻��Ų�ƥ��
    ///<------add esign-------->///
    ERR_NEED_RESIGN,                ///< ǩ�����ݹ���,������ǩ��
    ///<----------------------->///
    ERR_POOR_STORAGE,               ///< �洢�ռ䲻��,���Ƚ���
    
    ERR_NO_SETTLE,                  ///< �ն�δ�����
    ERR_MAX_INDEX
};

void transErr_ErrBeep(void);
int transErr_SetSubErrCode(int errCode, int subErrCode);
void transErr_DispErrMsg(int transType, int errCode);

#endif  //_TRANS_ERR_H
