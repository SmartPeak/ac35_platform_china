#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "uFile.h"

#include "trans_err.h"
#define _GDATA_
#include "pos_data.h"
#undef _GDATA_

int POS_LoadDefParam(unsigned int fileIndex);
int CASH_CashierInit(void);

/*
  1.Ver: versions changes update file
  2.fileSize: structure size changes update file
*/
///< user data file list
const DATA_FILE_INFO fileList[] =
{
    {0x0002, DFA_DataDB,      "db_commu", &DataCommu, sizeof(DataCommu), POS_LoadDefParam},
    {0x0002, DFA_DataDB,      "db_constant", &DataConstant, sizeof(DataConstant), POS_LoadDefParam},
    {0x0002, DFA_DataDB,      "db_change", &DataChange, sizeof(DataChange), POS_LoadDefParam},
    {0x0002, DFA_DataDB,      "db_reverse", &DataReverse, sizeof(DataReverse), NULL},
    {0x0002, DFA_DataDB,      "db_transDetail", &DataTransDetail, sizeof(DataTransDetail), NULL},
    {0x0002, DFA_RecordDB,    FILE_TransTab, &DataTrans, sizeof(DataTrans), NULL},
    {0x0002, DFA_DataDB,      "db_Cashier", &DataCashier, sizeof(DataCashier), POS_LoadDefParam},
    {0x0002, DFA_DataDB,      FILE_ICScript, NULL, sizeof(tsScriptData), NULL},
    ///<---------add esign--------->///
    {0x0002, DFA_DataDB,      FILE_EsignParam, &DataEsign, sizeof(tsEsignParam), POS_LoadDefParam},
    {0x0002, DFA_DataDB,      FILE_Esign, NULL, 0, NULL},
    ///<--------------------------->///
};

///< default param
static int POS_LoadDefParam(unsigned int fileIndex)
{
    memset(fileList[fileIndex].fileData, 0, fileList[fileIndex].fileSize);
    switch(fileIndex)
    {
    case DB_Commu:
        break;
    case DB_Constant:
        memcpy(DataConstant.tpdu, "\x60\x04\x01\x00\x00", 5);

        DataConstant.dialRetry      = 3;
        DataConstant.recvTimeout    = 60;

        DataConstant.ucUseKeyIndex  = 1;
        DataConstant.encryptType    = EncryptDoubleTDK;

        ///<
        memcpy(DataConstant.transEnable, "\xFF\x30\x00\x00", 4);
        strcpy((char *)DataConstant.currencyCode, "156");
        DataConstant.posState       = 0;
        DataConstant.transRetry     = 3;
        DataConstant.ucPrintTimes   = 2;
        DataConstant.isVoidSwipe    = 1;
        DataConstant.isVoidInputPIN = 1;
        DataConstant.maxTransNum    = MAX_TRANS_NUM;
        DataConstant.bisCheckAdminPwd = 1;

#if !defined(P90)
        DataConstant.isVoidInputPIN = 0;
#endif
        break;
    case DB_Change:
        strcpy((char *)DataChange.traceNumber, "000001");
        strcpy((char *)DataChange.batchNumber, "000001");

        DataChange.QPS_NoPIN_Flag = 1;
        DataChange.QPS_PINAmtLimit  = 30000;
        DataChange.QPS_Signature_Flag = 1;
        DataChange.QPS_SignatureAmtLimit = 30000;

#if !defined(P90)
        DataChange.QPS_PINAmtLimit  = 1000000;
#endif
        break;
    case DB_Cashier:
        CASH_CashierInit();
        break;
    ///< -----------add esign------------>///
    case DB_EsignParam:
        DataEsign.bisSupportEs = 0;
        DataEsign.bisEsConfirmTipFlag = 0;
        DataEsign.usEsShakeHandTimeOut = 3;
        DataEsign.usEsSignTimeOut = 150;
        DataEsign.ucEsUploadTimes = 1;
        DataEsign.bisSupportEsPartPackage = 0;
        DataEsign.usEsPartPackageUnit = 900;
        DataEsign.ucEsReSignMaxTimes = 3;
        DataEsign.usEsMaxTradeNum = MAX_TRANS_NUM;
        DataEsign.bisEsNeedInputPhoneNo = 1;
        DataEsign.bisEsPrintVoucher = 1;
        DataEsign.ucEsUploadMode = 0;
        break;
    ///< -------------------------------->///
    default:
        break;
    }
    return SUCCESS;
}

///< user data files init and load data
int POS_DataInit(void)
{
    int iRet;

    ///< clear global variable
    memset(&DataSave, 0, sizeof(DataSave));
    memset(&tempData, 0, sizeof(tempData));

    ///< check user data files exist
    iRet = UFile_CheckAllValidFiles(fileList, DB_MaxIndex);

    return iRet;
}

