/*****************************************************************************
*  QR and P90 Basic applib configuration definition header                   *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*                                                                            *
*  @file     trans_search                                                    *
*  @brief    search transaction processing                                   *
*  Details.                                                                  *
*  @author   chengyang geng                                                  *
*  @date     2019-01-25                                                      *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "uFile.h"
#include "trans.h"

#define DEBUG_SEARCH    0
#if DEBUG_SEARCH
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "trans_search.c"
#endif

/**
 * @brief view trade detail
 */
int search_TradeDetail(void)
{
    unsigned char isReFresh = 1;
    int index = 0;
    int iRet = 0;
    int iKey = 0;


    ///< check record number
    if (DataTransDetail.transCount <= 0) {
        return ERR_TRANS_EMPTY;
    }

    ///< search...
    index = DataTransDetail.transCount - 1;
    while (1)
    {
        if (isReFresh)
        {
            memset(&DataTrans, 0, sizeof(tsTransData));
            ///< get record data by index
            iRet = UFile_ReadRecordIndexOf(DB_TransTable, index);
            if (UFILE_SUCCESS != iRet) {
                return iRet;
            }

            ///< get void state
            DataTrans.isVoid = DataTransDetail.transIndex[index] & TRANS_VOIDSTATE;
            transUI_DisplayTradeInfo(0, &DataTrans);
        }

        isReFresh = 1;
        iKey = mmi_inputWaitKeypress(60);
        if ((KEY_CANCEL == iKey)
         || (KEY_NONE == iKey)
         || (KEY_ENTER == iKey)) {
            break;
        }
        else if (transUtil_CheckPgUp(iKey)) {
            if (index < (DataTransDetail.transCount - 1)) {
                index++;
                continue;
            }
        }
        else if (transUtil_CheckPgDn(iKey)) {
            if (index > 0) {
                index--;
                continue;
            }
        }
        isReFresh = 0;
    }
    return SUCCESS;
}

/**
 * @brief view trade total
 */
int search_TradeTotal(void)
{
    tsTradeTotalForAll *pstTotalForAll = NULL;
    char show_buff[30] = {0};
    unsigned char ucCardType = CARD_INTERNAL;
    int iKey = KEY_NONE;
    int isReFresh = 1;

    while (1)
    {
        if (isReFresh)
        {
            isReFresh = 0;

            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_Line1, DISP_HCenter, AMSG_TotalTransactions);

            memset(show_buff, 0, sizeof(show_buff));
            if (CARD_INTERNAL == ucCardType)
            {
                strcpy(show_buff, AMSG_DebitInternalCard);
                pstTotalForAll = &DataTransDetail.transDetailData.totalAll.stTotalIn;
            }
            else
            {
                strcpy(show_buff, AMSG_DebitForeignCard);
                pstTotalForAll = &DataTransDetail.transDetailData.totalAll.stTotalOut;
            }

            mmi_display(DISP_Line2, DISP_Left, show_buff);
            mmi_display(DISP_Line2, DISP_Right, AMSG_TickCount, pstTotalForAll->totalDebitNum);
            mmi_display(DISP_Line3, DISP_Right, AMSG_Amount,
                        pstTotalForAll->totalDebitAmount / 100,
                        pstTotalForAll->totalDebitAmount % 100);

            memset(show_buff, 0, sizeof(show_buff));
            if (CARD_INTERNAL == ucCardType)
            {
                strcpy(show_buff, AMSG_CreditInternalCard);
            }
            else
            {
                strcpy(show_buff, AMSG_CreditForeignCard);
            }
            mmi_display(DISP_Line4, DISP_Left, show_buff);
            mmi_display(DISP_Line4, DISP_Right, AMSG_TickCount, pstTotalForAll->totalCreditNum);
            mmi_display(DISP_Line5, DISP_Right, AMSG_Amount,
                        pstTotalForAll->totalCreditAmount / 100,
                        pstTotalForAll->totalCreditAmount % 100);
        }

        iKey = mmi_inputWaitKeypress(60);
        if (KEY_NONE == iKey || KEY_CANCEL == iKey) {
            return ERR_CANCEL;
        }
        else if (transUtil_CheckPgDn(iKey) || transUtil_CheckPgUp(iKey)) {
            if ((KEY_ENTER == iKey) && (CARD_FOREIGN == ucCardType)) {
                break;
            }

            if (CARD_INTERNAL == ucCardType) {
                ucCardType = CARD_FOREIGN;
            }
            else {
                ucCardType = CARD_INTERNAL;
            }
            isReFresh = 1;
        }
    }
    return SUCCESS;
}

/**
 * @brief search trade detail by trace no.
 */
int search_TradeInfo(int bisReInput)
{
    int iRet = SUCCESS;
    char mOnOff[2] = {0};

    mOnOff[0] = bisReInput;
    iRet = transUI_SearchTransEx(AMSG_Title_VoucherNoSearch, mOnOff, NULL, &DataTrans);
    if (SUCCESS == iRet) {
        iRet = transUI_DisplayTradeInfo(1, &DataTrans);
    }
    return iRet;
}

/**
 * @brief trade record search menu
 */
int trans_SearchTradeMenu(void)
{
    int iRet;
    while (1)
    {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Title_TradeInquiries);
        mmi_display(DISP_Line2, DISP_Left, "1.%s", AMSG_Title_ViewTradeDetail);
        mmi_display(DISP_Line3, DISP_Left, "2.%s", AMSG_Title_ViewTradeTotal);
        mmi_display(DISP_Line4, DISP_Left, "3.%s", AMSG_Title_VoucherNoSearch);
        switch (mmi_inputWaitKeypress(60))
        {
        case KEY_ASCII1:
            iRet = search_TradeDetail();
            break;
        case KEY_ASCII2:
            iRet = search_TradeTotal();
            break;
        case KEY_ASCII3:
            iRet = search_TradeInfo(1);
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            continue;
        }

        if (iRet != SUCCESS
         && iRet != ERR_END
         && iRet != ERR_CANCEL
         && iRet != ERR_TIMEOUT) {
            transErr_DispErrMsg(0, iRet);
        }
    }
}

