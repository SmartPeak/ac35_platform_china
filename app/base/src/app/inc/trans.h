#ifndef _TRANS_H
#define _TRANS_H

#include "pos_data.h"
#include "trans_err.h"
#include "msg.h"
#ifdef ENABLE_ESIGN
#include "elecsign.h"
#endif

#define min(a, b)           (((a) < (b)) ? (a) : (b))
#define max(a, b)           (((a) > (b)) ? (a) : (b))


void trans_GetErrCodeToEmvKernel(int errCode, char *pResCode);
//=============================================================
//trans_menu.c: transaction menu
//=============================================================
/**
 * @brief Main Menu
 * @param
 * @retval
 */
int trans_mainMenu(void);

//=============================================================
//trans_ui.c: transaction ui
//=============================================================
enum FIND_CARD_EVENT_TYPE
{
    EventNull   = 0x00,
    EventMag    = 0x01,
    EventICC    = 0x02,
    EventPICC   = 0x04,
    EventInput  = 0x08
};

///< 提示移卡、拔卡
int transUI_RemoveCard(void);

int transUI_Input(const char *pCaption, unsigned int inputType, unsigned char *pBuff, int minLen, int maxLen);

/**
 * @brief  swipe card
 */
int transUI_SwipeCard(unsigned long ulAmount);

/**
 * @brief  input card pin
 */
int transUI_InputCardPIN(void);

/**
 * @brief  input amount
 */
int transUI_inputAmount(const char* caption, unsigned long mixAmount, unsigned long maxAmount, unsigned long *amount);

/**
 * @brief  input date
 */
int transUI_inputDate(const char* caption, unsigned char *date);

/**
 * @brief  input expiredDate
 */
int transUI_inputExpiredDate(const char* caption, unsigned char *expiredDate);

/**
 * @brief  input Reference Number
 */
int transUI_inputRefNo(const char* caption, unsigned char *refNo);

/**
 * @brief  confirm amount
 */
int transUI_confirmAmount(const char* caption, unsigned long ulAmount);

/**
 * @brief  display trade info
 */
int transUI_DisplayTradeInfo(unsigned char keySwitch, tsTransData *ptsTransData);

/**
 * @brief  search trace info
 * @param pTitle [in] title txt
 * @param on_off [in] on-off
                      on_off[0]: 0x01 - re enter
                      on_off[1]: 0x01 - enter keypress last trace
 */
int transUI_SearchTransEx(const char *pTitle, const char on_off[2], unsigned int *pTransIndex, tsTransData *pTransData);

/**
 * @brief  search trans
 */
int transUI_SearchTrans(const char *pTitle, unsigned int *pTransIndex);

/**
 * @brief  display balance
 */
void transUI_DisplayBalance(void);

/**
 * @brief scan code
 */
int transUI_ScanCode(const char *caption1, const char *caption2, const unsigned char *speakValue, unsigned char *plOut, int flag);

/**
 * @brief  Check Battery
 */
int transUI_CheckBattery(void);

//=============================================================
//trans_util.c:
//=============================================================
/**
 * @brief  error red lights
 */
void transUtil_LED_Error(void);

/**
 * @brief  wait read card blue lights
 */
void transUtil_LED_WaitReadCard(void);

/**
 * @brief  read card finish yellow lights
 */
void transUtil_LED_ReadCardData(void);

/**
 * @brief  trans online green flash
 * @param  ledEnable [in] 1-flash, 0-close
 */
void transUtil_LED_TransOnline(unsigned char ledEnable);

/**
 * @brief  trans finish opened green lights
 */
void transUtil_LED_TransFinish(void);

/**
 * @brief  close led
 */
void transUtil_LED_Close(void);

/**
 * @brief  get TUSN
 */
int transUtil_GetSN(unsigned char *pSN, unsigned short snSize);

/**
 * @brief  check keypress of page up
 */
unsigned char transUtil_CheckPgUp(int key);

/**
 * @brief  check keypress of page down
 */
unsigned char transUtil_CheckPgDn(int key);

/**
 * @brief  clear global data
 */
int transUtil_ClearGlobalData(void);

/**
 * @brief  clear reversal
 */
int transUtil_ClearReversal(void);

/**
 * @brief  清除脚本数据
 * @brief  clear script
 */
int transUtil_ClearScript(void);

/**
 * @brief  save reversal data
 */
int transUtil_SaveReversal(unsigned char *pReversalEvent);

/**
 * @brief  updata batch no.
 */
int transUtil_UpdataBatchNumber(const char *batchNumber);

/**
 * @brief  increase trace no.
 */
int transUtil_IncreaseTraceNumber(unsigned long increaseNumber);

/**
 * @brief  update logon state
 * @param state [in] 1 logon, 0 logoff
 */
int transUtil_UpdateLogonState(unsigned char state);

/**
 * @brief  clear trans
 */
int transUtil_ClearTrans(void);

/**
 * @brief  清除终端参数
 * @brief  clear terminal param
 */
int transUtil_ClearParam(void);

/**
 * @brief  save trans
 */
int transUtil_SaveTrans(void);

/**
 * @brief  search trans
 */
int transUtil_SearchTrans(tsTransData *pTransData, unsigned char *transNumber, unsigned int *pIndex);

/**
 * @brief  update void state
 * @param state [in] 1 print, 0 no print
 */
int transUtil_UpdatePrintState(unsigned char state, unsigned int index);

/**
 * @brief judge trade type and mask card no.
 */
int transUtil_JudgeMaskCardNo(unsigned char ucTradeId, unsigned char *lpCardNo);

/**
 * @brief timer
 * @param listTime [in/out] list time
 * @param timeout [in] timeout (ms)
 * @retval true/false
 */
unsigned char transUtil_CheckTimeout(unsigned int *listTime, unsigned int timeout);

void transUtil_CheckMdmPush(void);

//=============================================================
//trans.c: transaction func
//=============================================================
/**
 * @brief logon processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Logon(void);

/**
 * @brief logoff processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Logoff(void);

/**
 * @brief ic card aid download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadAID(void);

/**
 * @brief ic card capk download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadCAPK(void);

/**
 * @brief rf parameter download processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_LoadRF(void);

/**
 * @brief  standby
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_standby(unsigned char *imgData, unsigned short imgW, unsigned short imgH);

/**
 * @brief query balance processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_QueryBal(void);

/**
 * @brief  purchase processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Sale(void);

/**
 * @brief  cancel purchase processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_VoidSale(void);

/**
 * @brief  scan void sale processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_ScanVoidSale(void);

/**
 * @brief  refund process
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_Refund(void);

/**
 * @brief  scan refund process
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_ScanRefund(void);

/**
 * @brief  batch settle processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_BatchSettle(void);

//=============================================================
//trans_online.c: on-line transaction processing
//=============================================================
/**
 * @brief settle batch on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_BatchSettle(void);

int transOnline_ScriptResultSave(void);

/**
 * @brief  on-line transaction processing
 * @retval SUCCESS  success
 * @retval other    failure
 */
int transOnline_process(void);

//=============================================================
//trans_print.c: print transaction processing
//=============================================================
/**
 * @brief print settle sheet
 */
int transPrint_PrintSettleSheet(void);

/**
 * @brief reprint the last trade sheet
 */
int transPrint_LastTrade(void);

/**
 * @brief reprint any trade sheet
 */
int transPrint_AnyTrade(void);

/**
 * @brief print trade detail
 */
int transPrint_DetailTrade(void);

/**
 * @brief print trade total
 */
int transPrint_TotalSheet(void);

/**
 * @brief reprint settle sheet
 */
int transPrint_RePrintSettleSheet(void);

//=============================================================
//trans_search.c: search transaction processing
//=============================================================

/**
 * @brief trade record search menu
 */
int search_TradeDetail(void);

/**
 * @brief view trade total
 */
int search_TradeTotal(void);

/**
 * @brief search trade detail by trace no.
 */
int search_TradeInfo(int bisReInput);

/**
 * @brief trade record search menu
 */
int trans_SearchTradeMenu(void);

/**
 * @brief get trade Chinese name or English name
 */
int GetTradeName(unsigned char *lpChOut, unsigned char ucTradeId);

char *trans_GetTransName(int transType);

/**
 * @brief pos logon
 * @retval SUCCESS  success
 * @retval other    failure
 */
int trans_PosLogon(void);

/**
 * @brief  通过付款凭证号查询交易流水
 * @brief  search scan trans
 */
int transUtil_SearchScanTrans(tsTransData *pTransData, unsigned char *transVoucher, unsigned int *pIndex);

/**
 * @brief  根据付款凭证号查询流水
 * @brief  search trans by scan voucher no.
 */
int transUI_SearchScanTrans(unsigned int *pTransIndex);


/**
 * @brief print voucher sheets
 */
int PrintVoucherSheet(tsTransData *pstTransData, int isErrPrint, int isRePrint);


#endif  //_TRANS_H

