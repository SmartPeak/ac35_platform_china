#ifndef _POS_DATA_H
#define _POS_DATA_H
/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     pos_data.h                                                      *
*  @brief    data definition, initialization                                 *
*  Details.                                                                  *
*                                                                            *
*****************************************************************************/
#include "secretKey.h"
#include "cashier.h"

#define BCTCVER                 "3200003"   //不得擅自改动
#define CUP_CERTIFICATE_NO      "3863"      //证书编号
/*!< -------------------------------------------*/

#define MAX_TRANS_NUM           500 ///< 最大流水数量

/*!< -------------------------------------------*/

#define TID_LEN                 8   ///< terminal id len
#define MID_LEN                 15  ///< merchant id len
#define MERCHANTNAME_LEN        40  ///< merchant name len
#define TRACE_NO_LEN            6   ///< trace number len
#define BATCH_NO_LEN            6   ///< batch number len
#define TPDU_LEN                5   ///< tpdu len

/*!< -------------------------------------------*/
enum TRANS_TYPE
{
    TRANS_NULL,
    TRANS_LOGON             = 1,    ///< logon
    TRANS_LOGOFF,                   ///< logoff
    TRANS_SETTLEMENT,               ///< settlement
    TRANS_QUERY_BAL         = 20,   ///< query balance
    TRANS_SALE,
    TRANS_VOID_SALE,
    TRANS_REFUND,
    ///< -----------------------------
    TRANS_SCRIPT_SEND,              ///< script inform send
    TRANS_REVERSAL,
    ///< -----------------------------
    TRANS_LOADAID,
    TRANS_LOADCAPK,
    TRANS_LOADRF
};

enum TRANS_STATE
{
    TRANS_NIINORMAL         = 0x01, ///< 普通交易
    TRANS_NIIVOID           = 0x02, ///< 撤销交易
    TRANS_BATCHSEND         = 0x04, ///< 批上送交易
    
    TRANS_VOIDSTATE         = 0x10, ///< 撤销状态位
    TRANS_PRINTSTATE        = 0x20, ///< 打印状态位
    TRANS_ARPC_ERR          = 0x40
};

enum SETTLE_STATE
{
    SETTLE_OK               = 0x00, ///< 对账平
    SETTLE_UNEVEN           = 0x01, ///< 对账不平
    SETTLE_ERROR            = 0x02  ///< 对账失败
};

enum CARD_TYPE
{
    CARD_INTERNAL = 0,  ///< 内卡
    CARD_FOREIGN        ///< 外卡
};

enum CARD_INPUT_TYPE
{
    InputMode_Manual = 0,
    InputMode_Mag = 1,
    InputMode_ICC,
    InputMode_QICC,
    InputMode_Scan      ///< add scan
};

enum DOWN_PARAM_TYPE
{
    DOWN_PARAM_AID      = 1,
    DOWN_PARAM_CAPK     = 2,
    DOWN_PARAM_UNTOUCH  = 4
};

enum ENCRYPT_TYPE
{
    EncryptSingle,
    EncryptDouble,
    EncryptDoubleTDK,
    EncryptSM2
};

typedef struct
{
    unsigned char setFlag;      /*设置标志*/
    char type;                  /*通讯类型,0 TCP  1 UDP*/
    char host[50];              /*服务器ip地址*/
    unsigned short port;        /*服务器端口号*/

    char apntype;               /*apn类型 0 CMNET 1 CMWAP*/
    char username[30];          /*认证用户名*/
    char passwd[20];            /*认证密码*/
    char flag;                  /*IP地址的访问方式 0 IPADDRESS 1 DOMAINADDRESS*/
    unsigned char timeout;      /*超时时间*/
    unsigned char httpPath[100];/*路径*/
    unsigned char httpURL[200]; /**/

    unsigned char sslEnable;    /**/
}tsCommuPar;

typedef struct
{
    unsigned char           ucUseKeyIndex;                      ///< 密钥索引
    enum ENCRYPT_TYPE       encryptType;                        ///< 加密算法 encrypt type
    unsigned char           tpdu[TPDU_LEN];                     ///< tpdu

    unsigned char           dialRetry;                          ///< 重试次数 dial retry
    unsigned short          recvTimeout;                        ///< 接收超时时间 recv timeout

    unsigned char           TID[TID_LEN+1];                     ///< 终端号 terminal id
    unsigned char           MID[MID_LEN+1];                     ///< 商户号 merchant id
    unsigned char           merchantName[MERCHANTNAME_LEN+1];   ///< 商户名称 merchant name

    unsigned char           currencyCode[4];                    ///< 货币代码
    unsigned char           bSM;                                ///< 是否支持国密
    unsigned char           bDownEMVFlag;                       ///< 是否支持EMV参数下载

    unsigned char           ucPrintTimes;                       ///< 票单打印联数 print paper times

    unsigned char           transRetry;                         ///< 消息重发次数

    unsigned char           isVoidSwipe;                        ///< 撤销是否读卡
    unsigned char           isVoidInputPIN;                     ///< 撤销是否输密

    unsigned char           posState;                           ///< 0-Normal, 1-Test
    unsigned char           transEnable[4];                     ///< 交易开关
    unsigned char           emvDebug;
    unsigned short          maxTransNum;                        ///< 最大交易笔数

    unsigned char           bisCheckAdminPwd;                   ///< 是否输入主管密码

}tsConstantPar;

typedef struct
{
    unsigned char       isLogon;                                ///< is logon (1 is logon, 0 is logoff)
    unsigned char       logonDate[9];                           ///< logon date
    unsigned char       isStoreKeyDownRight;                    ///< store key down is right?
    unsigned char       isUpdateBatch;                          ///< 需签到修改批次
    unsigned char       traceNumber[TRACE_NO_LEN+1];            ///< trace number
    unsigned char       batchNumber[BATCH_NO_LEN+1];            ///< batch number
    unsigned char       isCashierLogon;                         ///< cashier logon state   
    unsigned char       cashierNo[2];                           ///< 柜员号

    ///
    unsigned char       packgeHeadEve;                          ///<
    unsigned char       downFlag;                               ///< 参数下载标志

    unsigned char       ucSettleFlag;                           ///< 结算标志
    unsigned char       ucSettleStep;                           ///< 结算中断位置
    unsigned short      usBatchSendNum;                         ///< batch send number
    unsigned int        uiBatchSendTotalNum;                    ///< batch send total number

    ///< 非接参数
    unsigned long QPS_PINAmtLimit;          ///< 非接免密限额

    unsigned char QPS_NoPIN_Flag;           ///< 非接快速业务标识(免密)
    unsigned char QPS_BINA_Flag;            ///< BIN表A标识
    unsigned char QPS_BINB_Flag;            ///< BIN表B标识
    unsigned char QPS_CDCVM_Flag;           ///< CDCVM标识
    unsigned char QPS_Signature_Flag;       ///< 免签标识
    unsigned long QPS_SignatureAmtLimit;    ///< 免签限额
    /*! <----------------------------------------> !*/
}tsChangePar;

typedef struct
{
    unsigned char       transType;                              ///< 交易类型
    ///< --------------------------------------
    unsigned char       cardInputType;                          ///< card input type
    enum CARD_TYPE      cardType;                               ///< 卡类型 Internal or foreign card flag
    unsigned char       sourceAccType;                          ///< 主账户类型
    unsigned char       sourceAccLen;                           ///< 主账户长度
    unsigned char       sourceAcc[10];                          ///< 主账户

    unsigned char       expiredDate[4];                         ///< 卡有效期
    ///
    unsigned char       panSeq[2];                              ///< 卡序列号 card sequence
    unsigned char       cardPan[6];
    ///< --------------------------------------
    unsigned char       settleDate[4];                          ///< 清算日期
    unsigned char       time[6];                                ///< 交易时间
    unsigned char       date[8];                                ///< 交易日期
    ///< --------------------------------------
    unsigned long       ulAmount;                               ///< 金额
    unsigned char       batchNumber[BATCH_NO_LEN];              ///< 批次号
    unsigned char       traceNumber[TRACE_NO_LEN];              ///< 流水号
    unsigned char       oldtraceNumber[TRACE_NO_LEN];           ///< 原流水号
    unsigned char       authCode[6];                            ///< 授权码
    unsigned char       refNumber[12];                          ///< 系统参考号
    unsigned char       oldRefNumber[12];                       ///< 原系统参考号
    ///< --------------------------------------

    unsigned char       isVoid;                                 ///< the trade is be void or not
    unsigned char       isInputPIN;                             ///< is be input PIN
    ///< --------------------------------------
    unsigned char       bcdTVR[5];                              ///< emv tvr(BCD)
    unsigned char       BatchSendNum;                           ///< batch send number

    unsigned char       bankID[11];                             ///< 受理方标识码
    unsigned char       issuerID[11];                           ///< 接收机构标识码
    unsigned char       acquereID[11];                          ///< 收单机构标识码

    unsigned int        field55Len;                             ///< filed 55 lenth
    unsigned char       field55Data[256];                       ///< filed 55 data

    unsigned char       aucARQC[17];                            ///< emv arqc(ASCII)
    unsigned char       aucAID[17];                             ///< emv aid(ASCII)
    unsigned char       bcdTSI[2];                              ///< emv tsi(BCD)
    unsigned char       bcdATC[2];                              ///< emv atc(BCD)
    unsigned char       aucAPPLAB[17];                          ///< emv applab(ASCII)
    unsigned char       aucAPPNAME[17];                         ///< emv appname(ASCII)
    unsigned char       isHavePrint;                            ///< trans sheet have be printed 1-yes,0-no

    unsigned char       ucCDCVM;                                ///< CDCVM flag

    unsigned char       oldDate[4];                             ///< old trans date
    unsigned char       oldAuthCode[6];                         ///< old auth code

    unsigned char       ScanCodeC2B[351];                       ///< scan code data
    unsigned char       ascScanVoucherNo[20+1];                 ///< scan voucher no.

} tsTransData;

typedef struct
{
    unsigned char   reversalFlag;
    unsigned char   reversalEvent[3];       ///< reversal reason
    unsigned char   authCode[6];            ///< Authorization code
    unsigned short  dataLen;
    unsigned char   data[1024];

}tsReverseData;

typedef struct
{
    unsigned char   flag;
    unsigned short  dataLen;
    unsigned char   data[1024];
}tsScriptData;

enum _ENTRY_TYPE
{
    ENTRY_STANDBY   = 1,
    ENTRY_INSERT_CARD,
    ENTRY_PUT_CARD
};

typedef struct
{
    unsigned char   transType;
    unsigned char   serialNo[64];

    unsigned int    eventType;
    unsigned int    oldTransIndex;
    //----
    unsigned char   iso2Status;
    unsigned short  iso2Len;
    unsigned char   iso2[37+1];
    unsigned char   iso3Status;
    unsigned short  iso3Len;
    unsigned char   iso3[104];
    unsigned char   iso1Status;
    unsigned short  iso1Len;
    unsigned char   iso1[79];

    //----
    unsigned char   qInputPinFlag;              //PIN已输入
    unsigned char   inputPINLen;                //密码长度
    unsigned char   PINData[8];                 //密码
    //----
    unsigned char   uc9F36Flag;                 ///< EMV中心39域返回错置1
    unsigned char   uc9F26Flag;                 ///< 密文类型为2时,填ARPC
    unsigned char   balanceInfo[21];            ///< balance info
    //----
    unsigned char   issuerID[11];               ///< 接收机构标识码
    unsigned char   acquereID[11];              ///< 收单机构标识码
    //----
    //fild 55 tag 89
    unsigned char   authCode[6];                ///<

    //fild 55 tag 91
    unsigned char   arpc[8];                    ///< 后台返回的临时ARPC
    unsigned short  arpcLen;                    ///< 后台返回的临时ARPC长度

    ///<
    unsigned char   entryType;                  ///< 入口类型
    MagTrack_T      magTrack;
    
}tsExtraTransData;

///< trade type total struct define
typedef struct
{
    unsigned short totalSaleNum;            ///< sale trade total number(not include void trade)
    unsigned long  totalSaleAmount;         ///< sale trade total amount(not include void trade)

    unsigned short totalSaleNumAll;         ///< sale trade total number(include void trade)
    unsigned long  totalSaleAmountAll;      ///< sale trade total amount(include void trade)

    unsigned short totalVoidNum;            ///< void trade total number
    unsigned long  totalVoidAmount;         ///< void trade total amount

    unsigned short totalRefundNum;          ///< refund trade total number
    unsigned long  totalRefundAmount;       ///< refund trade total amount

    unsigned short totalFinishNum;          ///< total finish number(without void)
    unsigned long totalFinishAmount;        ///< total finish amount(without void)

    unsigned short totalFinishNumAll;       ///< total finish number(with void)
    unsigned long totalFinishAmountAll;     ///< total finish amount(with void)

    unsigned short totalAuthSettleNum;      ///< total auth settle number
    unsigned long totalAuthSettleAmount;    ///< total auth settle amount

    unsigned short totalFinishVoidNum;      ///< total unfinish number 
    unsigned long totalFinishVoidAmount;    ///< total unfinish amount
    
} tsTradeTotalForTrade;

///< trade total struct define
typedef struct
{
    unsigned short TotalNum;            ///< total number
    unsigned short totalDebitNum;       ///< total debit number
    unsigned long totalDebitAmount;     ///< total debit amount
    unsigned short totalCreditNum;      ///< total credit number
    unsigned long totalCreditAmount;    ///< total credit amount

} tsTradeTotalForAll;

///< trade total all struct define(include in & out)
typedef struct
{
    tsTradeTotalForAll stTotalIn;
    tsTradeTotalForAll stTotalOut;

} tsTradeTotalAll;

///< trade type total struct define (include in & out)
typedef struct
{       
    tsTradeTotalForTrade stTradeIn;
    tsTradeTotalForTrade stTradeOut;

} tsTradeTotalTrade;

typedef struct
{
    unsigned char       SettlePrintFlag;            ///< settle sheet print flag
    unsigned char       InternalSettleFlag;         ///< internal settle flag
    unsigned char       ForeignSettleFlag;          ///< foreign settle flag
    unsigned char       SettleDate[8];              ///< settle date
    unsigned char       SettleTime[6];              ///< settle time
    unsigned char       SettleBatchNo[BATCH_NO_LEN];///< settle batch no.
    tsTradeTotalAll     totalAll;
    tsTradeTotalTrade   totalTrade;

} tsTradeDetail;

typedef struct 
{
    unsigned int        transCount;                 ///< 当前交易笔数
    unsigned int        lastTransIndex;             ///< 上一笔索引
    unsigned short      transIndex[MAX_TRANS_NUM];
    tsTradeDetail       transDetailData;            ///< current batch trade info
    tsTradeDetail       lastTransDetailData;        ///< last batch trade info
    ///<----------add esign----------->///
    unsigned int        esignCount;                 ///< 电子签名笔数
    unsigned int        lastOffsetEnd;              ///< 上一笔交易电签数据偏移终点
    unsigned int        uiEsDataOffsetTab[MAX_TRANS_NUM];   ///< 电子签名数据地址
    unsigned int        uiEsDataLenTab[MAX_TRANS_NUM];      ///< 电子签名数据长度
    ///<------------------------------>///
}tsTradeInfo;

///< bank name
struct BankName
{
    unsigned char BankCode[5];      ///< bank code
    unsigned char BankName[20];	    ///< bank name
};

///<---------add esign--------->///
typedef struct _esignParam
{
    unsigned char           bisSupportEs;                       ///< 是否支持电子签名
    unsigned char           bisEsConfirmTipFlag;                ///< 是否提示确认签名
    unsigned short          usEsShakeHandTimeOut;               ///< 电子签名握手超时时间
    unsigned short          usEsSignTimeOut;                    ///< 电子签名超时时间
    unsigned char           ucEsUploadTimes;                    ///< 签名重复上送次数
    unsigned char           bisSupportEsPartPackage;            ///< 签名是否支持分包上送
    unsigned short          usEsPartPackageUnit;                ///< 电子签名分包传输单位
    unsigned char           ucEsReSignMaxTimes;                 ///< 电子签名最大重签次数
    unsigned short          usEsMaxTradeNum;                    ///< 电子签名最大交易笔数
    unsigned char           bisEsNeedInputPhoneNo;              ///< 是否要求输入手机号
    unsigned char           bisEsPrintVoucher;                  ///< 电签是否打印签购单
    unsigned char           ucEsUploadMode;                     ///< 电子签名上送方式0-当笔完成后送，1-下笔联机前送
} tsEsignParam;
///<-------------------------->///

/*!< -------------------------------------------*/
#ifndef _GDATA_
#define _GDATA_ extern
#endif

typedef struct
{
#if SECRETKEY_SOFTDES
    tsSoftSp        softSpData;
#endif

    tsCommuPar      commuData;
    tsConstantPar   constantData;
    tsChangePar     changeData;
    SYSCASHIER      cashierData;
    tsTradeInfo     tradeinfoData;
    tsTransData     transData;
    tsReverseData   reverseData;
    ///<----add esign---->///
    tsEsignParam    esignData;
    ///<----------------->///

}tsDataSave;

typedef struct
{
    tsExtraTransData    extraTransData;
}tsTempData;

_GDATA_ tsDataSave DataSave;
_GDATA_ tsTempData tempData;

typedef enum
{
    DB_Commu = 0,       ///< 通讯参数文件
    DB_Constant,        ///< 固参
    DB_Change,          ///< 变参
    DB_Reverse,         ///< 冲正文件
    DB_TransDetail,     ///< 交易汇总文件
    DB_TransTable,      ///< 交易流水文件
    DB_Cashier,
    DB_Script,          ///< 脚本文件(只用于文件检查,不作索引读写)
    ///<-----------add esign---------->///
    DB_EsignParam,      ///< 电子签名参数文件
    DB_Esign,           ///< 电子签名数据文件
    ///<------------------------------>///
    DB_MaxIndex
}tsDBIndex;

///< file name
#define FILE_TransTab       "db_transTable"
#define FILE_ICScript       "db_Script"
///<---------add esign----------->///
#define FILE_EsignParam     "db_EsignParam"
#define FILE_Esign          "db_Esign"
///<----------------------------->///

#define DataCommu           DataSave.commuData          ///< 通讯参数
#define DataConstant        DataSave.constantData       ///< 固参
#define DataChange          DataSave.changeData         ///< 变参
#define DataCashier         DataSave.cashierData
#define DataReverse         DataSave.reverseData        ///< 冲正数据
#define DataScript          DataSave.scriptData         ///< 脚本数据
#define DataTransDetail     DataSave.tradeinfoData      ///< 交易汇总数据
#define DataTrans           DataSave.transData          ///< 交易流水数据
///<---------add esign---------->///
#define DataEsign           DataSave.esignData          ///< 电子签名参数数据
///<---------------------------->///
#define ExtraData           tempData.extraTransData     ///< 交易中临时缓存数据(不需要保存)


/*!< --------------------------- 交易开关 --------------------------->! */
#define BitGet(X,pos)               ((X) >> (pos-1)&1)          //得到某字节的某位
#define SetBit(X,pos)               ((X)|= 1<<(pos-1))          //把某位置1
#define Clrbit(X,pos)               ((X) &= ~(1<<(pos-1)))      //把某位置0
#define SetBitValue(X,pos,value)    (!value ? Clrbit(X,pos) : SetBit(X,pos))

#define ENABLE_BIT(a,b)             (DataConstant.transEnable[a]&b)

#define isEnable_inquiry            ENABLE_BIT(0,0x80)  ///< 查询8
#define isEnable_sale               ENABLE_BIT(0,0x04)  ///< 消费3
#define isEnable_voidSale           ENABLE_BIT(0,0x02)  ///< 消费撤销2
#define isEnable_refund             ENABLE_BIT(0,0x01)  ///< 退货1

#endif  //_POS_DATA_H
