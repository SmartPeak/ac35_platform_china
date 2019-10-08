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
    ERR_SAVE_KEY_KCV,               ///< 密钥校验错
    ERR_CALC_KEY_KCV,               ///< 密钥校验错,请重新签到
    ERR_MAC,                        ///< mac wrong

    ///<
    ERR_DATA_OVERFLOW       = 0x25, ///< 缓存超限
    ERR_DATA_INVALID,               ///< 无效数据
    ERR_DATA_PACK,                  ///< Data package wrong
    ERR_DATA_UPACK,                 ///< Data unpackage wrong
    ERR_SM2_SIGN,                   ///< SM2 sign error

    ERR_CASHIER,                    ///< 柜员

    ERR_NOT_LOGON,                  ///< 未签到,请先签到
    ERR_PLZ_SETTLE,                 ///< 请先结算
    ERR_ADMIN_LOGON,                ///< 主管不能交易,请先签到
    ERR_BATCH,                      ///< 批次不符,请签到
    ERR_STORE_KEY,                  ///< 密钥错误,请签到
    ERR_TRANS_FULL,                 ///< 交易已满,请结算
    ERR_TRANS_EMPTY,                ///< 无交易流水
    ERR_TRANS_NOFIND,               ///< 原交易不存在
    ERR_TRANS_NOVOID,               ///< 已撤销或不支持
    ERR_NEED_REPRINT,               ///< 需要重打印上一笔交易
    ERR_AMOUNT_OVERFLOW,            ///< 退货金额超限

    ERR_VOID_CARD_DIFFER,           ///< 退款卡号不一致
    ERR_PWD_CASH_PASS,              ///< 密码错误
    ERR_PWD_NO_PASSWORD,            ///< no password
    ERR_PWD_PIN_ERR,
    ERR_PWD_PIN_BLOCK,
    ERR_PWD_OTHER_ERR,
    ERR_FUNC_CLOSE,                 ///< 该功能暂不支持
    ERR_EMV_CT,
    ERR_EMV_CL,
    ERR_FIELD_CMP,
    ///<------add esign-------->///
    ERR_INPUT_FORMAT,               ///< 输入格式错误,请重新输入
    ///<----------------------->///
    ERR_MSG_CHECK,                  ///< 消息类型不匹配
    ERR_AMT_CHECK,                  ///< 交易金额不匹配
    ERR_VHN_CHECK,                  ///< 流水号不匹配
    ERR_TID_CHECK,                  ///< 终端号不匹配
    ERR_MID_CHECK,                  ///< 商户号不匹配
    ///<------add esign-------->///
    ERR_NEED_RESIGN,                ///< 签名数据过大,请重新签名
    ///<----------------------->///
    ERR_POOR_STORAGE,               ///< 存储空间不足,请先结算
    
    ERR_NO_SETTLE,                  ///< 终端未结算过
    ERR_MAX_INDEX
};

void transErr_ErrBeep(void);
int transErr_SetSubErrCode(int errCode, int subErrCode);
void transErr_DispErrMsg(int transType, int errCode);

#endif  //_TRANS_ERR_H
