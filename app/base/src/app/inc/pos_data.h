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

#define BCTCVER                 "3200003"   //�������ԸĶ�
#define CUP_CERTIFICATE_NO      "3863"      //֤����
/*!< -------------------------------------------*/

#define MAX_TRANS_NUM           500 ///< �����ˮ����

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
    TRANS_NIINORMAL         = 0x01, ///< ��ͨ����
    TRANS_NIIVOID           = 0x02, ///< ��������
    TRANS_BATCHSEND         = 0x04, ///< �����ͽ���
    
    TRANS_VOIDSTATE         = 0x10, ///< ����״̬λ
    TRANS_PRINTSTATE        = 0x20, ///< ��ӡ״̬λ
    TRANS_ARPC_ERR          = 0x40
};

enum SETTLE_STATE
{
    SETTLE_OK               = 0x00, ///< ����ƽ
    SETTLE_UNEVEN           = 0x01, ///< ���˲�ƽ
    SETTLE_ERROR            = 0x02  ///< ����ʧ��
};

enum CARD_TYPE
{
    CARD_INTERNAL = 0,  ///< �ڿ�
    CARD_FOREIGN        ///< �⿨
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
    unsigned char setFlag;      /*���ñ�־*/
    char type;                  /*ͨѶ����,0 TCP  1 UDP*/
    char host[50];              /*������ip��ַ*/
    unsigned short port;        /*�������˿ں�*/

    char apntype;               /*apn���� 0 CMNET 1 CMWAP*/
    char username[30];          /*��֤�û���*/
    char passwd[20];            /*��֤����*/
    char flag;                  /*IP��ַ�ķ��ʷ�ʽ 0 IPADDRESS 1 DOMAINADDRESS*/
    unsigned char timeout;      /*��ʱʱ��*/
    unsigned char httpPath[100];/*·��*/
    unsigned char httpURL[200]; /**/

    unsigned char sslEnable;    /**/
}tsCommuPar;

typedef struct
{
    unsigned char           ucUseKeyIndex;                      ///< ��Կ����
    enum ENCRYPT_TYPE       encryptType;                        ///< �����㷨 encrypt type
    unsigned char           tpdu[TPDU_LEN];                     ///< tpdu

    unsigned char           dialRetry;                          ///< ���Դ��� dial retry
    unsigned short          recvTimeout;                        ///< ���ճ�ʱʱ�� recv timeout

    unsigned char           TID[TID_LEN+1];                     ///< �ն˺� terminal id
    unsigned char           MID[MID_LEN+1];                     ///< �̻��� merchant id
    unsigned char           merchantName[MERCHANTNAME_LEN+1];   ///< �̻����� merchant name

    unsigned char           currencyCode[4];                    ///< ���Ҵ���
    unsigned char           bSM;                                ///< �Ƿ�֧�ֹ���
    unsigned char           bDownEMVFlag;                       ///< �Ƿ�֧��EMV��������

    unsigned char           ucPrintTimes;                       ///< Ʊ����ӡ���� print paper times

    unsigned char           transRetry;                         ///< ��Ϣ�ط�����

    unsigned char           isVoidSwipe;                        ///< �����Ƿ����
    unsigned char           isVoidInputPIN;                     ///< �����Ƿ�����

    unsigned char           posState;                           ///< 0-Normal, 1-Test
    unsigned char           transEnable[4];                     ///< ���׿���
    unsigned char           emvDebug;
    unsigned short          maxTransNum;                        ///< ����ױ���

    unsigned char           bisCheckAdminPwd;                   ///< �Ƿ�������������

}tsConstantPar;

typedef struct
{
    unsigned char       isLogon;                                ///< is logon (1 is logon, 0 is logoff)
    unsigned char       logonDate[9];                           ///< logon date
    unsigned char       isStoreKeyDownRight;                    ///< store key down is right?
    unsigned char       isUpdateBatch;                          ///< ��ǩ���޸�����
    unsigned char       traceNumber[TRACE_NO_LEN+1];            ///< trace number
    unsigned char       batchNumber[BATCH_NO_LEN+1];            ///< batch number
    unsigned char       isCashierLogon;                         ///< cashier logon state   
    unsigned char       cashierNo[2];                           ///< ��Ա��

    ///
    unsigned char       packgeHeadEve;                          ///<
    unsigned char       downFlag;                               ///< �������ر�־

    unsigned char       ucSettleFlag;                           ///< �����־
    unsigned char       ucSettleStep;                           ///< �����ж�λ��
    unsigned short      usBatchSendNum;                         ///< batch send number
    unsigned int        uiBatchSendTotalNum;                    ///< batch send total number

    ///< �ǽӲ���
    unsigned long QPS_PINAmtLimit;          ///< �ǽ������޶�

    unsigned char QPS_NoPIN_Flag;           ///< �ǽӿ���ҵ���ʶ(����)
    unsigned char QPS_BINA_Flag;            ///< BIN��A��ʶ
    unsigned char QPS_BINB_Flag;            ///< BIN��B��ʶ
    unsigned char QPS_CDCVM_Flag;           ///< CDCVM��ʶ
    unsigned char QPS_Signature_Flag;       ///< ��ǩ��ʶ
    unsigned long QPS_SignatureAmtLimit;    ///< ��ǩ�޶�
    /*! <----------------------------------------> !*/
}tsChangePar;

typedef struct
{
    unsigned char       transType;                              ///< ��������
    ///< --------------------------------------
    unsigned char       cardInputType;                          ///< card input type
    enum CARD_TYPE      cardType;                               ///< ������ Internal or foreign card flag
    unsigned char       sourceAccType;                          ///< ���˻�����
    unsigned char       sourceAccLen;                           ///< ���˻�����
    unsigned char       sourceAcc[10];                          ///< ���˻�

    unsigned char       expiredDate[4];                         ///< ����Ч��
    ///
    unsigned char       panSeq[2];                              ///< �����к� card sequence
    unsigned char       cardPan[6];
    ///< --------------------------------------
    unsigned char       settleDate[4];                          ///< ��������
    unsigned char       time[6];                                ///< ����ʱ��
    unsigned char       date[8];                                ///< ��������
    ///< --------------------------------------
    unsigned long       ulAmount;                               ///< ���
    unsigned char       batchNumber[BATCH_NO_LEN];              ///< ���κ�
    unsigned char       traceNumber[TRACE_NO_LEN];              ///< ��ˮ��
    unsigned char       oldtraceNumber[TRACE_NO_LEN];           ///< ԭ��ˮ��
    unsigned char       authCode[6];                            ///< ��Ȩ��
    unsigned char       refNumber[12];                          ///< ϵͳ�ο���
    unsigned char       oldRefNumber[12];                       ///< ԭϵͳ�ο���
    ///< --------------------------------------

    unsigned char       isVoid;                                 ///< the trade is be void or not
    unsigned char       isInputPIN;                             ///< is be input PIN
    ///< --------------------------------------
    unsigned char       bcdTVR[5];                              ///< emv tvr(BCD)
    unsigned char       BatchSendNum;                           ///< batch send number

    unsigned char       bankID[11];                             ///< ������ʶ��
    unsigned char       issuerID[11];                           ///< ���ջ�����ʶ��
    unsigned char       acquereID[11];                          ///< �յ�������ʶ��

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
    unsigned char   qInputPinFlag;              //PIN������
    unsigned char   inputPINLen;                //���볤��
    unsigned char   PINData[8];                 //����
    //----
    unsigned char   uc9F36Flag;                 ///< EMV����39�򷵻ش���1
    unsigned char   uc9F26Flag;                 ///< ��������Ϊ2ʱ,��ARPC
    unsigned char   balanceInfo[21];            ///< balance info
    //----
    unsigned char   issuerID[11];               ///< ���ջ�����ʶ��
    unsigned char   acquereID[11];              ///< �յ�������ʶ��
    //----
    //fild 55 tag 89
    unsigned char   authCode[6];                ///<

    //fild 55 tag 91
    unsigned char   arpc[8];                    ///< ��̨���ص���ʱARPC
    unsigned short  arpcLen;                    ///< ��̨���ص���ʱARPC����

    ///<
    unsigned char   entryType;                  ///< �������
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
    unsigned int        transCount;                 ///< ��ǰ���ױ���
    unsigned int        lastTransIndex;             ///< ��һ������
    unsigned short      transIndex[MAX_TRANS_NUM];
    tsTradeDetail       transDetailData;            ///< current batch trade info
    tsTradeDetail       lastTransDetailData;        ///< last batch trade info
    ///<----------add esign----------->///
    unsigned int        esignCount;                 ///< ����ǩ������
    unsigned int        lastOffsetEnd;              ///< ��һ�ʽ��׵�ǩ����ƫ���յ�
    unsigned int        uiEsDataOffsetTab[MAX_TRANS_NUM];   ///< ����ǩ�����ݵ�ַ
    unsigned int        uiEsDataLenTab[MAX_TRANS_NUM];      ///< ����ǩ�����ݳ���
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
    unsigned char           bisSupportEs;                       ///< �Ƿ�֧�ֵ���ǩ��
    unsigned char           bisEsConfirmTipFlag;                ///< �Ƿ���ʾȷ��ǩ��
    unsigned short          usEsShakeHandTimeOut;               ///< ����ǩ�����ֳ�ʱʱ��
    unsigned short          usEsSignTimeOut;                    ///< ����ǩ����ʱʱ��
    unsigned char           ucEsUploadTimes;                    ///< ǩ���ظ����ʹ���
    unsigned char           bisSupportEsPartPackage;            ///< ǩ���Ƿ�֧�ְַ�����
    unsigned short          usEsPartPackageUnit;                ///< ����ǩ���ְ����䵥λ
    unsigned char           ucEsReSignMaxTimes;                 ///< ����ǩ�������ǩ����
    unsigned short          usEsMaxTradeNum;                    ///< ����ǩ������ױ���
    unsigned char           bisEsNeedInputPhoneNo;              ///< �Ƿ�Ҫ�������ֻ���
    unsigned char           bisEsPrintVoucher;                  ///< ��ǩ�Ƿ��ӡǩ����
    unsigned char           ucEsUploadMode;                     ///< ����ǩ�����ͷ�ʽ0-������ɺ��ͣ�1-�±�����ǰ��
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
    DB_Commu = 0,       ///< ͨѶ�����ļ�
    DB_Constant,        ///< �̲�
    DB_Change,          ///< ���
    DB_Reverse,         ///< �����ļ�
    DB_TransDetail,     ///< ���׻����ļ�
    DB_TransTable,      ///< ������ˮ�ļ�
    DB_Cashier,
    DB_Script,          ///< �ű��ļ�(ֻ�����ļ����,����������д)
    ///<-----------add esign---------->///
    DB_EsignParam,      ///< ����ǩ�������ļ�
    DB_Esign,           ///< ����ǩ�������ļ�
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

#define DataCommu           DataSave.commuData          ///< ͨѶ����
#define DataConstant        DataSave.constantData       ///< �̲�
#define DataChange          DataSave.changeData         ///< ���
#define DataCashier         DataSave.cashierData
#define DataReverse         DataSave.reverseData        ///< ��������
#define DataScript          DataSave.scriptData         ///< �ű�����
#define DataTransDetail     DataSave.tradeinfoData      ///< ���׻�������
#define DataTrans           DataSave.transData          ///< ������ˮ����
///<---------add esign---------->///
#define DataEsign           DataSave.esignData          ///< ����ǩ����������
///<---------------------------->///
#define ExtraData           tempData.extraTransData     ///< ��������ʱ��������(����Ҫ����)


/*!< --------------------------- ���׿��� --------------------------->! */
#define BitGet(X,pos)               ((X) >> (pos-1)&1)          //�õ�ĳ�ֽڵ�ĳλ
#define SetBit(X,pos)               ((X)|= 1<<(pos-1))          //��ĳλ��1
#define Clrbit(X,pos)               ((X) &= ~(1<<(pos-1)))      //��ĳλ��0
#define SetBitValue(X,pos,value)    (!value ? Clrbit(X,pos) : SetBit(X,pos))

#define ENABLE_BIT(a,b)             (DataConstant.transEnable[a]&b)

#define isEnable_inquiry            ENABLE_BIT(0,0x80)  ///< ��ѯ8
#define isEnable_sale               ENABLE_BIT(0,0x04)  ///< ����3
#define isEnable_voidSale           ENABLE_BIT(0,0x02)  ///< ���ѳ���2
#define isEnable_refund             ENABLE_BIT(0,0x01)  ///< �˻�1

#endif  //_POS_DATA_H
