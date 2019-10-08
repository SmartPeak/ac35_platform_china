/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     trans_online                                                    *
*  @brief    on-line transaction processing                                  *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "logger.h"
#include "applib_def.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "uFile.h"

#include "trans.h"
#include "ota_update.h"

#define DEBUG_TRANS_UTIL        0
#if DEBUG_TRANS_UTIL
#ifdef TAG
#undef TAG
#endif
#define TAG "trans_util.c"
#endif

#define LED_RED             RF_LED_RED
#define LED_YELLOW          RF_LED_YELLOW
#define LED_GREEN           RF_LED_GREEN
#define LED_BLUE            RF_LED_BLUE

static unsigned char bLedOpen = false;

/**
 * @brief  error red lights
 */
void transUtil_LED_Error(void)
{
    if (bLedOpen) {
        SpSysLedOn(LED_RED);
        SpSysLedOff(LED_BLUE|LED_YELLOW|LED_GREEN);
    }
}

/**
 * @brief  wait read card blue lights
 */
void transUtil_LED_WaitReadCard(void)
{
    bLedOpen = true;
    SpSysLedOn(LED_BLUE);
}

/**
 * @brief  read card finish yellow lights
 */
void transUtil_LED_ReadCardData(void)
{
    if (bLedOpen) {
        SpSysLedOn(LED_YELLOW);
    }
}

/**
 * @brief  trans online green flash
 * @param  ledEnable [in] 1-flash, 0-close
 */
void transUtil_LED_TransOnline(unsigned char ledEnable)
{
    if (bLedOpen) {
        if (ledEnable) {
            SpSysLedFlash(LED_GREEN, 750, 250);
        }
        else {
            SpSysLedOff(LED_GREEN);
        }
    }
}

/**
 * @brief  trans finish opened green lights
 */
void transUtil_LED_TransFinish(void)
{
    if (bLedOpen) {
        SpSysLedOn(LED_GREEN);
    }
}

/**
 * @brief  close led
 */
void transUtil_LED_Close(void)
{
    SpSysLedOff(LED_BLUE|LED_YELLOW|LED_GREEN|LED_RED);
    bLedOpen = false;
}

/**
 * @brief  get TUSN
 */
int transUtil_GetSN(unsigned char *pSN, unsigned short snSize)
{
    unsigned int i;
    unsigned char m_sn[64] = {0};

    if (pSN == NULL || snSize < 64) {
        return ERR_PARAM;
    }

    for (i = 0; i < 3; i++)
    {
        memset(m_sn, 0, sizeof(m_sn));
        if (!GetDSN(m_sn, sizeof(m_sn))){
            if (strlen((char *)m_sn)) {
                break;
            }
        }
    }

    if (!strlen((char *)m_sn)) {
        return ERR_DRV;
    }
    memcpy(pSN, m_sn, snSize);
    return SUCCESS;
}

/**
 * @brief  check keypress of page up
 */
unsigned char transUtil_CheckPgUp(int key)
{
#if defined(QR300)
    if (KEY_FUNC == key)
#elif defined(QR100)
    if (KEY_ALPHA == key)
#elif defined(P90)
    if (KEY_UP == key)
#else
    if (KEY_ASCII0 == key)
#endif
    {
        return true;
    }
    return false;
}

/**
 * @brief  check keypress of page down
 */
unsigned char transUtil_CheckPgDn(int key)
{
#if defined(QR300)
    if (KEY_ALPHA == key || KEY_ENTER == key)
#elif defined(QR100)
    if (KEY_FUNC == key || KEY_ENTER == key)
#elif defined(P90)
    if (KEY_DOWN == key || KEY_ENTER == key)
#else
    if (KEY_DOT == key || KEY_ENTER == key)
#endif
    {
        return true;
    }
    return false;
}

/**
 * @brief  clear global data
 */
int transUtil_ClearGlobalData(void)
{
    memset(&tempData, 0, sizeof(tempData));
    memset(&DataTrans, 0, sizeof(DataTrans));

    return SUCCESS;
}

/**
 * @brief  clear reversal
 */
int transUtil_ClearReversal(void)
{
    memset(&DataReverse, 0, sizeof(DataReverse));
    return UFile_WriteFileIndexOf(DB_Reverse);
}

/**
 * @brief  clear script
 */
int transUtil_ClearScript(void)
{
    return UFile_ClearFileIndexOf(DB_Script);
}

/**
 * @brief  save reversal data
 */
int transUtil_SaveReversal(unsigned char *pReversalEvent)
{
    DataReverse.reversalFlag = 1;
    memset(DataReverse.reversalEvent, 0, sizeof(DataReverse.reversalEvent));
    memcpy(DataReverse.reversalEvent, pReversalEvent, 2);

    return UFile_WriteFileIndexOf(DB_Reverse);
}

/**
 * @brief  updata batch no.
 */
int transUtil_UpdataBatchNumber(const char *batchNumber)
{
    DataChange.isUpdateBatch = 0;
    memset(DataChange.batchNumber, 0, sizeof(DataChange.batchNumber));
    memcpy(DataChange.batchNumber, batchNumber, BATCH_NO_LEN);
    return UFile_WriteFileIndexOf(DB_Change);
}

/**
 * @brief  increase batch no.
 */
int transUtil_IncreaseBatchNumber(unsigned long increaseNumber)
{
    unsigned long ulBatchNumber;

    ulBatchNumber = tools_asc_long(DataChange.batchNumber, BATCH_NO_LEN);
    ulBatchNumber += increaseNumber ? increaseNumber : 1;
    if (ulBatchNumber > 999999) {
        ulBatchNumber = 1;
    }

    memset(DataChange.batchNumber, 0, sizeof(DataChange.batchNumber));
    tools_long_asc(DataChange.batchNumber, BATCH_NO_LEN, &ulBatchNumber);
    return UFile_WriteFileIndexOf(DB_Change);
}

/**
 * @brief  increase trace no.
 */
int transUtil_IncreaseTraceNumber(unsigned long increaseNumber)
{
    unsigned long ulTraceNumber;

    ulTraceNumber = tools_asc_long(DataChange.traceNumber, TRACE_NO_LEN);
    ulTraceNumber += increaseNumber ? increaseNumber : 1;
    if (ulTraceNumber > 999999) {
        ulTraceNumber = 1;
    }

    memset(DataChange.traceNumber, 0, sizeof(DataChange.traceNumber));
    tools_long_asc(DataChange.traceNumber, TRACE_NO_LEN, &ulTraceNumber);
    return UFile_WriteFileIndexOf(DB_Change);
}

/**
 * @brief  update logon state
 * @param state [in] 1 logon, 0 logoff
 */
int transUtil_UpdateLogonState(unsigned char state)
{
    tsSysTime datime;
    
    DataChange.isLogon = state;
    ///< clear cashier logon state
    if (!state) {
        DataChange.isCashierLogon = state;
        memset(DataChange.cashierNo, 0, sizeof(DataChange.cashierNo));
    } else {
        ///< get system date and time
        GetSysLocalTime(&datime);
        ///< save logon date
        memset(DataChange.logonDate, 0, sizeof(DataChange.logonDate));
        snprintf((char *)DataChange.logonDate, sizeof(DataChange.logonDate), "%04d%02d%02d",
            datime.year, datime.mon, datime.day);
    }
    
    return UFile_WriteFileIndexOf(DB_Change);
}

/**
 * @brief  update trans type
 * @param state [in] type bit[enum TRANS_STATE]
 */
int transUtil_SetTransType(enum TRANS_STATE type, unsigned int index)
{
    if (index >= MAX_TRANS_NUM) {
        return ERR_PARAM;
    }
    
    ///< set trans type bit
    DataTransDetail.transIndex[index] = DataTransDetail.transIndex[index] | type;

    return UFile_WriteFileIndexOf(DB_TransDetail);
}

/**
 * @brief  clear trans
 */
int transUtil_ClearTrans(void)
{   
    int iRet = SUCCESS;
    tsTradeDetail *pLastTradeDetail = &DataTransDetail.lastTransDetailData;
    tsTradeDetail *pCurryTradeDetail = &DataTransDetail.transDetailData;

    ///< 备份数据
    memset(pLastTradeDetail, 0, sizeof(tsTradeDetail));
    memcpy(pLastTradeDetail, pCurryTradeDetail, sizeof(tsTradeDetail));
    ///< 清除数据
    DataTransDetail.transCount = 0;
    DataTransDetail.lastTransIndex = 0;
    memset(DataTransDetail.transIndex, 0, sizeof(DataTransDetail.transIndex));
    ///<----------add esign--------->///
    DataTransDetail.esignCount = 0;
    DataTransDetail.lastOffsetEnd = 0;
    memset(DataTransDetail.uiEsDataOffsetTab, 0, sizeof(DataTransDetail.uiEsDataOffsetTab));
    memset(DataTransDetail.uiEsDataLenTab, 0, sizeof(DataTransDetail.uiEsDataLenTab));
    ///<---------------------------->///
    memset(pCurryTradeDetail, 0, sizeof(tsTradeDetail));

    iRet = UFile_ClearFileIndexOf(DB_TransTable);
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileIndexOf(DB_TransDetail);
    }
    
    ///<--------add esign----------->///
    if (SUCCESS == iRet) {
        iRet = UFile_ClearFileIndexOf(DB_Esign);
    }
    ///<---------------------------->///
    
    return iRet;
}

/**
 * @brief  clear terminal param
 */
int transUtil_ClearParam(void)
{   
    extern int POS_DataInit(void);
    int iRet = SUCCESS;

    memset(&DataConstant, 0, sizeof(tsConstantPar));
    iRet = UFile_ClearFileIndexOf(DB_Constant);

    if (SUCCESS == iRet) {
        memset(&DataChange, 0, sizeof(tsChangePar));
        iRet = UFile_ClearFileIndexOf(DB_Change);
    }
    if (SUCCESS == iRet) {
        memset(&DataCommu, 0, sizeof(tsCommuPar));
        iRet = UFile_ClearFileIndexOf(DB_Commu);
    }
    if (SUCCESS == iRet) {
        memset(&DataCashier, 0, sizeof(SYSCASHIER));
        iRet = UFile_ClearFileIndexOf(DB_Cashier);
    }
    ///<--------add esign------>///
    if (SUCCESS == iRet) {
        memset(&DataEsign, 0, sizeof(tsEsignParam));
        iRet = UFile_ClearFileIndexOf(DB_EsignParam);
    }
    ///<----------------------->///

    return iRet;
}

/**
 * @brief  update void state
 * @param state [in] 1 void, 0 unvoid
 */
int transUtil_UpdateVoidState(unsigned char state, unsigned int index)
{
    if (index >= MAX_TRANS_NUM) {
        return ERR_PARAM;
    }
    
    ///< set void state bit
    if (state) {
        DataTransDetail.transIndex[index] =
            DataTransDetail.transIndex[index] | TRANS_VOIDSTATE;
    ///< clear void state bit
    } else {
        DataTransDetail.transIndex[index] =
            DataTransDetail.transIndex[index] & (!TRANS_VOIDSTATE);
    }
    
    return SUCCESS;
}

/**
 * @brief  update void state
 * @param state [in] 1 print, 0 no print
 */
int transUtil_UpdatePrintState(unsigned char state, unsigned int index)
{
    if (index >= MAX_TRANS_NUM) {
        return ERR_PARAM;
    }
    
    ///< set print state bit
    if (state) {
        DataTransDetail.transIndex[index] =
            DataTransDetail.transIndex[index] | TRANS_PRINTSTATE;
    ///< clear print state bit
    } else {
        DataTransDetail.transIndex[index] =
            DataTransDetail.transIndex[index] & (!TRANS_PRINTSTATE);
    }

    return UFile_WriteFileIndexOf(DB_TransDetail);
}

/**
 * @brief  save trans
 */
int transUtil_SaveTrans(void)
{
    int iRet = SUCCESS;
    tsTransData *pTransData = &DataTrans;
    tsTradeInfo *pTransInfo = &DataTransDetail;
    tsTradeTotalForAll *pstForAll = NULL;
    tsTradeTotalForTrade *pstForTrade = NULL;

    if (!pTransData || !pTransInfo) {
        return ERR_PARAM;
    }

    /*!< --------------- card type -------------*/
    pstForAll   = &pTransInfo->transDetailData.totalAll.stTotalIn;
    pstForTrade = &pTransInfo->transDetailData.totalTrade.stTradeIn;
    if (pTransData->cardType) {
        pstForAll   = &pTransInfo->transDetailData.totalAll.stTotalOut;
        pstForTrade = &pTransInfo->transDetailData.totalTrade.stTradeOut;
    }

    /*!< --------------- save trans ------------*/
    if (SUCCESS == iRet) {
        ///< save trans record
        iRet = UFile_WriteRecordIndexOf(DB_TransTable, pTransInfo->transCount);
        ///< void sale & auth finish void update old trans state
        if ((TRANS_VOID_SALE == pTransData->transType)) {
            transUtil_UpdateVoidState(1, ExtraData.oldTransIndex);
        }
        ///< ---
        if (1 == ExtraData.uc9F26Flag) {
            DataTransDetail.transIndex[pTransInfo->transCount] |= TRANS_ARPC_ERR;
        }
    }

    ///< trans total
    if (SUCCESS == iRet) {
        pstForAll->TotalNum ++;
        switch (pTransData->transType)
        {
        case TRANS_SALE:
            pstForAll->totalDebitNum++;
            pstForAll->totalDebitAmount += pTransData->ulAmount;

            ///<
            pstForTrade->totalSaleNum++;
            pstForTrade->totalSaleAmount += pTransData->ulAmount;

            pstForTrade->totalSaleNumAll++;
            pstForTrade->totalSaleAmountAll += pTransData->ulAmount;
            break;
        case TRANS_VOID_SALE:
            pstForAll->totalCreditNum++;
            pstForAll->totalCreditAmount += pTransData->ulAmount;

            ///<
            pstForTrade->totalSaleNum--;
            pstForTrade->totalSaleAmount -= pTransData->ulAmount;

            pstForTrade->totalVoidNum++;
            pstForTrade->totalVoidAmount += pTransData->ulAmount;
            break;
        case TRANS_REFUND:
            pstForAll->totalCreditNum++;
            pstForAll->totalCreditAmount += pTransData->ulAmount;

            pstForTrade->totalRefundNum++;
            pstForTrade->totalRefundAmount += pTransData->ulAmount;
            break;
        default:
            break;
        }
    }

    ///< save total info
    if (SUCCESS == iRet) {
        pTransInfo->lastTransIndex = pTransInfo->transCount;
        pTransInfo->transCount++;
        iRet = UFile_WriteFileIndexOf(DB_TransDetail);
    }

    ///< clear reversal data
    if (SUCCESS == iRet) {
        transUtil_ClearReversal();
    }
    return iRet;
}

static int transUtil_SearchTransCallback(tsDBExec *pExec)
{
    unsigned long ulTraceNumber = 0;
    unsigned char aucTraceNumber[TRACE_NO_LEN+1] = {0};
    tsTransData *pTransData = pExec->recordData;

    ulTraceNumber = tools_asc_long(pExec->inData, strlen((char *)pExec->inData));
    tools_long_asc(aucTraceNumber, TRACE_NO_LEN, &ulTraceNumber);

    if (!memcmp(pTransData->traceNumber, aucTraceNumber, TRACE_NO_LEN)) {
        pExec->exitLoop = 1;
        return SUCCESS;
    }
    return ERR_TRANS_NOFIND;
}

/**
 * @brief  search trans
 */
int transUtil_SearchTrans(tsTransData *pTransData, unsigned char *transNumber, unsigned int *pIndex)
{
    int iRet = ERR_TRANS_NOFIND;
    tsDBExec mExec;

    memset(&mExec, 0, sizeof(mExec));
    memset(pTransData, 0, sizeof(tsTransData));
    mExec.count = DataTransDetail.transCount;
    mExec.recordData = pTransData;
    mExec.recordDataSize = sizeof(tsTransData);
    mExec.inData = transNumber;
    mExec.execFunc = transUtil_SearchTransCallback;

    iRet = UFile_SearchRecordIndexOf(DB_TransTable, &mExec);
    if (SUCCESS == iRet && pIndex) {
        *pIndex = mExec.currIndex;
    }
    return iRet;
}

static int trans_SearchScanTransEx(tsDBExec *pExec)
{
    tsTransData *pTransData = pExec->recordData;

    if (!strcmp((const char *)pTransData->ascScanVoucherNo,
            (const char *)pExec->inData)) {
        pExec->exitLoop = 1;
        return SUCCESS;
    }
    
    return ERR_TRANS_NOFIND;
}

/**
 * @brief  search scan trans
 */
int transUtil_SearchScanTrans(tsTransData *pTransData, unsigned char *transVoucher, unsigned int *pIndex)
{
    int iRet = ERR_TRANS_NOFIND;
    tsDBExec mExec;

    memset(&mExec, 0, sizeof(mExec));
    memset(pTransData, 0, sizeof(tsTransData));
    mExec.count = DataTransDetail.transCount;
    mExec.recordData = pTransData;
    mExec.recordDataSize = sizeof(tsTransData);
    mExec.inData = transVoucher;
    mExec.execFunc = trans_SearchScanTransEx;

    iRet = UFile_SearchRecordIndexOf(DB_TransTable, &mExec);
    if (SUCCESS == iRet && pIndex) {
        *pIndex = mExec.currIndex;
    }
    return iRet;
}

/**
 * @brief judge trade type and mask card no.
 */
int transUtil_JudgeMaskCardNo(unsigned char ucTradeId, unsigned char *lpCardNo)
{
    unsigned char ucLen = 0;
    int i = 0, j = 0;
    unsigned char tmp[64] = {0};

    ucLen = strlen((char *)lpCardNo);
    switch(ucTradeId)
    {
    case TRANS_SALE:
    case TRANS_VOID_SALE:
    case TRANS_REFUND:
        if (ucLen > 10 && ucLen < 20) {
            memset(&lpCardNo[6], '*', ucLen - 10);
        }
        break;
    default:
        for (i=0, j=0; i < ucLen;) {
            tmp[j++] = lpCardNo[i++];
            if (i%4 == 0) {
                tmp[j] = ' ';
                j++;
            }
        }
        strcpy((char *)lpCardNo, (char *)tmp);
        break;
    }
    return SUCCESS;
}

/**
 * @brief  update trans
 */
int transUtil_UpdateTrans(unsigned int index)
{
    if (index >= MAX_TRANS_NUM) {
        return ERR_PARAM;
    }

    return UFile_WriteRecordIndexOf(DB_TransTable, index);
}

/**
 * @brief timer
 * @param listTime [in/out] list time
 * @param timeout [in] timeout (ms)
 * @retval true/false
 */
unsigned char transUtil_CheckTimeout(unsigned int *listTime, unsigned int timeout)
{
    bool bTrue = false;
    unsigned int time = GetSysTickCount();

    if (0 == *listTime || (time - *listTime) > timeout) {
        if (0 != *listTime) {
            bTrue = true;
        }
        *listTime = GetSysTickCount();
    }
    return bTrue;
}

void transUtil_CheckMdmPush(void)
{
    ota_update_handle_message();
}

