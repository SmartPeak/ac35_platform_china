/*****************************************************************************
*  QR and P90 Basic applib configuration definition header                   *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*                                                                            *
*  @file     menuList.c                                                      *
*  @brief    menu list                                                       *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "applib_def.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "trans.h"
#include "uMenu.h"

#define TRANS_MENU_TIMEOUT      30

/**
 * @brief logon menu
 */
static int trans_LogonMenu(void)
{
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(NULL, &mMenu);
        UMenu_SetTitle(AMSG_Title_Logon, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_PosLogon, trans_PosLogon, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashierLogon, trans_CashierLogon, NULL, NULL, &mMenu);

        return UMenu_DispMenu(MENU_STYLE_101, TRANS_MENU_TIMEOUT, &mMenu);
    }while(!mMenu.isExit);
}

/**
 * @brief cashier manage menu
 */
static int trans_CashierManage(void)
{
    int iRet = SUCCESS;
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(NULL, &mMenu);
        UMenu_SetTitle(AMSG_Title_CashiersManage, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_ChangeAdminPwd, CASH_ChangeAdminPwd, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashierAdd, CASH_AddCashier, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashierQuery, CASH_QueryCashier, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashierDel, CASH_DelCashier, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashierChangePwd, CASH_ModiCashierPwd, NULL, NULL, &mMenu);

        iRet = UMenu_DispMenu(MENU_STYLE_201, TRANS_MENU_TIMEOUT, &mMenu);
        if (iRet != SUCCESS
         && iRet != ERR_CANCEL
         && iRet != ERR_END) {
            transErr_DispErrMsg(0, iRet);
        }
    }while(!mMenu.isExit);

    return iRet;
}

/**
 * @brief system manage menu
 */
static int trans_ManageMenu(void)
{
    int iRet = SUCCESS;
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(NULL, &mMenu);
        UMenu_SetTitle(AMSG_Title_Manage, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_Logon, trans_LogonMenu, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_Logoff, trans_Logoff, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_TradeInquiries, trans_SearchTradeMenu, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_CashiersManage, trans_CashierManage, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_Settlement, trans_BatchSettle, NULL, NULL, &mMenu);

        iRet = UMenu_DispMenu(MENU_STYLE_201, TRANS_MENU_TIMEOUT, &mMenu);
    }while(!mMenu.isExit);

    return iRet;
}

/**
 * @brief void menu
 */
static int trans_VoidMenu(void)
{
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(&ExtraData.transType, &mMenu);
        UMenu_SetTitle(AMSG_Title_SaleVoid, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_CardSaleVoid, trans_VoidSale, TRANS_VOID_SALE, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_ScanSaleVoid, trans_ScanVoidSale, TRANS_VOID_SALE, NULL, &mMenu);
        return UMenu_DispMenu(MENU_STYLE_101, TRANS_MENU_TIMEOUT, &mMenu);
    }while(!mMenu.isExit);
}

/**
 * @brief refund menu
 */
static int trans_RefundMenu(void)
{
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(&ExtraData.transType, &mMenu);
        UMenu_SetTitle(AMSG_Title_Refund, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_CardRefund, trans_Refund, TRANS_REFUND, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_ScanRefund, trans_ScanRefund, TRANS_REFUND, NULL, &mMenu);

        return UMenu_DispMenu(MENU_STYLE_101, TRANS_MENU_TIMEOUT, &mMenu);
    }while(!mMenu.isExit);
}

/**
 * @brief print select menu
 */
static int trans_PrintMenu(void)
{
    int iRet = SUCCESS;
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        UMenu_Init(NULL, &mMenu);
        UMenu_SetTitle(AMSG_Title_Print, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_ReprintLastTrade, transPrint_LastTrade, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_ReprintAnyTrade, transPrint_AnyTrade, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_PrintTradeDetail, transPrint_DetailTrade, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_PrintTradeTotal, transPrint_TotalSheet, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_ReprintSettleSheet, transPrint_RePrintSettleSheet, NULL, NULL, &mMenu);

        iRet = UMenu_DispMenu(MENU_STYLE_101, TRANS_MENU_TIMEOUT, &mMenu);

        if (SUCCESS != iRet
         && ERR_CANCEL != iRet
         && ERR_TIMEOUT != iRet
         && ERR_END != iRet) {
            transErr_DispErrMsg(0, iRet);
        }
    }while(!mMenu.isExit);

    return iRet;
}

/**
 * @brief main menu
 */
int trans_mainMenu(void)
{
    int iRet;
    tsMenu mMenu;

    do
    {
        transUtil_ClearGlobalData();

        transUI_CheckBattery();

        UMenu_Init(&ExtraData.transType, &mMenu);
        UMenu_SetTitle(AMSG_Title_Headline, true, &mMenu);

        UMenu_AddMenu(AMSG_Title_Sale, trans_Sale, TRANS_SALE, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_SaleVoid, trans_VoidMenu, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_Refund, trans_RefundMenu, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_Print, trans_PrintMenu, NULL, NULL, &mMenu);
        UMenu_AddMenu(AMSG_Title_Manage, trans_ManageMenu, NULL, NULL, &mMenu);

        iRet = UMenu_DispMenu(MENU_STYLE_201, TRANS_MENU_TIMEOUT, &mMenu);
    }while(!mMenu.isExit);
    return iRet;
}

