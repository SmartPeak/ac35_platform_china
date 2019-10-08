#include "bwsdk_api.h"
#include "mmi_input.h"
#include "mmi_display.h"
#include "applib_tools.h"
#include "uFile.h"
#include "sysFile.h"

#include "cashier.h"
#include "trans.h"

#define CASH_TYPE_CASHIER       1   ///< cashier type
#define CASH_TYPE_SUPER         2   ///< manage type
#define CASH_TYPE_SYS           3   ///< admin type

/**
 * @brief cashier init
 */
int CASH_CashierInit(void)
{
    unsigned char index = 0;
    char aucCashierNo[4] = {0};

    memset(&DataCashier, 0, sizeof(SYSCASHIER));

    ///< default cashier no. & pwd (5)
    for (index = 1; index <= 5; index++)
    {
        memset(aucCashierNo, 0, sizeof(aucCashierNo));
        snprintf(aucCashierNo, sizeof(aucCashierNo), "%02d", index);
        memcpy(DataCashier.aucCashierNo[index-1], aucCashierNo, CASH_CASHIERNOLEN);
        memcpy(DataCashier.aucCashierPass[index-1], "0000", CASH_CASHIERPASSLEN);
    }

    ///< default admin no. & pwd
    memcpy(DataCashier.aucSYSCashierNo, "00", CASH_SYSCASHIERNOLEN);
    memcpy(DataCashier.aucSYSCashierPass, CASH_DEF_SYS_CASHIER_PWD, CASH_SYSCASHIERPASSLEN);

    ///< default system safe pwd
    memcpy(DataCashier.aucSafePSW, "12345678", CASH_SAFEPASSWDLEN);

    ///< default system manage no. & pwd
    memcpy(DataCashier.aucSuperNo, "99", CASH_MAXSUPERNOLEN);
    memcpy(DataCashier.aucSuperPSW, "12345678", CASH_SUPERPASSWDLEN);

    return SUCCESS;
}

static void CASH_DisplayMsg(const char *msg)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_VCenter, DISP_HCenter, msg);
    mmi_inputWaitKeypress(5);
}

static int CASH_InputCashierNo(const char *title, unsigned char *pNo)
{
    mmi_clearLine(DISP_ClearALL);
    if (NULL != title) {
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, title);
    }
    mmi_display(DISP_Line2, DISP_Left, AMSG_InputCashierNo);
    return mmi_inputString(DISP_Line3, InputMethod_digital, pNo, CASH_CASHIERNOLEN, CASH_CASHIERNOLEN, NULL, 60);
}

static int CASH_InputPassword(const char *title, const char *caption, unsigned char *pPWD, unsigned int minLen, unsigned int maxLen, unsigned char *pCheckVlaue)
{
    int iRet = SUCCESS;
    unsigned int inputType = mmi_setInputType(InputMethod_digital, InputMethod_digital);
    unsigned char mBuf[20] = {0};

    if (minLen > maxLen || maxLen <= 0) {
        return ERR_PARAM;
    }

    mmi_clearLine(DISP_ClearALL);
    ///< title
    if (NULL != title) {
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, title);
    }

    ///< input message
    if (NULL != caption) {
        mmi_display(DISP_Line2, DISP_Left, caption);
    }

    ///< input pwd
    iRet = mmi_InputPasswd(DISP_Line3, 0, inputType, mBuf, minLen, maxLen, 60);
    if (SUCCESS == iRet) {
        if (pCheckVlaue != NULL) {
            if (memcmp(mBuf, pCheckVlaue, maxLen) || !strlen((char *)mBuf)) {
                iRet = ERR_PWD_CASH_PASS;
            }
        }
        else if (pPWD){
            memcpy(pPWD, mBuf, maxLen);
        }
        else {
            iRet = ERR_PARAM;
        }
    }
    return iRet;
}

/**
 * @brief check admin pwd
 */
int CASH_CheckAdminPwd(const char *title)
{
    unsigned char aucAdminPwd[9] = {0};

    memcpy(aucAdminPwd, DataCashier.aucSYSCashierPass, CASH_SYSCASHIERPASSLEN);
    return CASH_InputPassword(title, AMSG_InputAdminPwd, NULL, CASH_SYSCASHIERPASSLEN, CASH_SYSCASHIERPASSLEN, aucAdminPwd);
}

/**
 * @brief check manage pwd
 */
int CASH_CheckManagePwd(const char *title)
{
    unsigned char aucManagePwd[9] = {0};

    memcpy(aucManagePwd, DataCashier.aucSuperPSW, CASH_SUPERPASSWDLEN);
    return CASH_InputPassword(title, AMSG_InputManagePwd, NULL, CASH_SUPERPASSWDLEN, CASH_SUPERPASSWDLEN, aucManagePwd);
}

/**
 * @brief check safe pwd
 */
int CASH_CheckSafePwd(const char *title)
{
    return CASH_InputPassword(title, AMSG_InputSafePwd, NULL, CASH_SAFEPASSWDLEN, CASH_SAFEPASSWDLEN, DataCashier.aucSafePSW);
}

/**
 * @brief change pwd
 */
static int CASH_ChangePwdEx(const char *pTitle, unsigned int minLen, unsigned int maxLen, unsigned char *pPassword, unsigned int passwordSize)
{
    int iRet = SUCCESS;
    unsigned char bEdit = 0;
    unsigned char aucManagePwd[9] = {0};
    unsigned char aucManagePwdNew[9] = {0};

    memcpy(aucManagePwd, pPassword, passwordSize);
    if (strlen((char *)aucManagePwd) > 0) {
        bEdit = 1;
        iRet = CASH_InputPassword(pTitle, AMSG_InputOldPwd, NULL, minLen, maxLen, aucManagePwd);
    }
    ///< first input new pwd
    if (SUCCESS == iRet) {
        memset(aucManagePwd, 0, sizeof(aucManagePwd));
        iRet = CASH_InputPassword(pTitle, AMSG_InputNewPwd, aucManagePwd, minLen, maxLen, NULL);
    }
    ///< second input new pwd
    if (SUCCESS == iRet) {
        iRet = CASH_InputPassword(pTitle, AMSG_InputAgain, aucManagePwdNew, minLen, maxLen, NULL);
    }

    ///< check input pwd
    if (SUCCESS == iRet && memcmp(aucManagePwd, aucManagePwdNew, maxLen)) {
        iRet = transErr_SetSubErrCode(ERR_CASHIER, CASHIER_PWD_DIFFER);
    }

    ///< save the new pwd when it is diffrent with the old one.
    if (SUCCESS == iRet && memcmp(aucManagePwd, pPassword, maxLen)) {
        memset(pPassword, 0, passwordSize);
        memcpy(pPassword, aucManagePwd, maxLen);
        if (SUCCESS != UFile_WriteFileIndexOf(DB_Cashier)) {
            iRet = transErr_SetSubErrCode(ERR_CASHIER, CASHIER_PWD_CHANGE_FAIL);
        }
    }

    if (SUCCESS == iRet && bEdit) {
        CASH_DisplayMsg(AMSG_ChangeSuccess);
    }
    return iRet;
}

static int CASH_FindCashierNoEx(const unsigned char *pCashierNo, unsigned int *pIndex)
{
    unsigned int i;

    ///< check input cashier no.
    ///< system manage
    if (!memcmp(pCashierNo, DataCashier.aucSuperNo, CASH_MAXSUPERNOLEN)) {
        return CASH_TYPE_SUPER;
    }

    ///< admin
    if (!memcmp(pCashierNo, DataCashier.aucSYSCashierNo, CASH_SYSCASHIERNOLEN)) {
        return CASH_TYPE_SYS;
    }

    ///< find the cashier
    for (i = 0; i < CASH_MAXCASHIER; i++) {
        if (!memcmp(pCashierNo, DataCashier.aucCashierNo[i], CASH_CASHIERNOLEN)) {
            if (pIndex) {
                *pIndex = i;
            }
            return CASH_TYPE_CASHIER;
        }
    }

    if (pIndex) {
        *pIndex = i;
    }
    return 0;
}

/**
 * @brief add cashier
 */
int CASH_AddCashier(void)
{
    int iRet = SUCCESS;
    unsigned char aucCashierNo[4] = {0};
    const char *pTitle = AMSG_AddCashierNo;
    unsigned int index = 0;

    ///< check admin pwd first
    iRet = CASH_CheckAdminPwd(pTitle);

    ///< input cashier no.
    if (SUCCESS == iRet) {
SIG_BEGIN:
        memset(aucCashierNo, 0, sizeof(aucCashierNo));
        iRet = CASH_InputCashierNo(pTitle, aucCashierNo);
        if (SUCCESS == iRet) {
            if (CASH_FindCashierNoEx(aucCashierNo, NULL)) {
                transErr_DispErrMsg(0, transErr_SetSubErrCode(ERR_CASHIER, CASHIER_EXIST));
                goto SIG_BEGIN;
            }
        }
    }

    if (SUCCESS == iRet) {
        index = atoi((const char *)aucCashierNo)-1;
        if (index >= CASH_MAXCASHIER) {
            return transErr_SetSubErrCode(ERR_CASHIER, CASHIER_ILLEGAL);
        }
        memset(DataCashier.aucCashierNo[index], 0, sizeof(DataCashier.aucCashierNo[index]));
        memset(DataCashier.aucCashierPass[index], 0, sizeof(DataCashier.aucCashierPass[index]));
        memcpy(DataCashier.aucCashierNo[index], aucCashierNo, CASH_CASHIERNOLEN);
        iRet = CASH_ChangePwdEx(pTitle, CASH_CASHIERPASSLEN, CASH_CASHIERPASSLEN, DataCashier.aucCashierPass[index], sizeof(DataCashier.aucCashierPass[index]));
        if (SUCCESS != iRet) {
            memset(DataCashier.aucCashierNo[index], 0, sizeof(DataCashier.aucCashierNo[index]));
            memset(DataCashier.aucCashierPass[index], 0, sizeof(DataCashier.aucCashierPass[index]));
        }
    }

    if (SUCCESS == iRet) {
        CASH_DisplayMsg(AMSG_AddSuccess);
    }
    return iRet;
}

/**
 * @brief delete cashier
 */
int CASH_DelCashier(void)
{
    int iRet = SUCCESS;
    unsigned int index = 0;
    unsigned char mCashierNoType = 0;
    unsigned char aucCashierNo[4] = {0};
    const char *pTitle = AMSG_DelCashierNo;

    ///< check admin pwd first
    iRet = CASH_CheckAdminPwd(pTitle);

    ///< input cashier no.
    if (SUCCESS == iRet) {
SIG_BEGIN:
        memset(aucCashierNo, 0, sizeof(aucCashierNo));
        iRet = CASH_InputCashierNo(pTitle, aucCashierNo);
        if (SUCCESS == iRet) {
            mCashierNoType = CASH_FindCashierNoEx(aucCashierNo, &index);
            if (!mCashierNoType) {
                iRet = CASHIER_NO_EXIST;
            }
            else if (CASH_TYPE_SUPER == mCashierNoType
                  || CASH_TYPE_SYS == mCashierNoType
                  || !memcmp(aucCashierNo, DataChange.cashierNo, CASH_CASHIERNOLEN)) {
                iRet = CASHIER_DEL_NOT_ALLOW;
            }

            if (SUCCESS != iRet) {
                transErr_DispErrMsg(0, transErr_SetSubErrCode(ERR_CASHIER, iRet));
                goto SIG_BEGIN;
            }
        }
    }

    if (SUCCESS == iRet) {
        memset(DataCashier.aucCashierNo[index], 0, sizeof(DataCashier.aucCashierNo[index]));
        memset(DataCashier.aucCashierPass[index], 0, sizeof(DataCashier.aucCashierPass[index]));
        iRet = UFile_WriteFileIndexOf(DB_Cashier);
    }

    if (SUCCESS == iRet) {
        CASH_DisplayMsg(AMSG_DelSuccess);
    }
    return iRet;
}

/**
 * @brief query cashier
 */
int CASH_QueryCashier(void)
{
    int index = 0;
    int isFresh = 1, flag = 1;
    int iKey = 0;
    char aucCashierNo[4] = {0};

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_CashierSearch);
    mmi_display(DISP_Line2, DISP_Left, AMSG_CashierNo);
    mmi_display(DISP_Line6, DISP_Left, AMSG_PageTurn);
    mmi_display(DISP_Line6, DISP_Right, AMSG_CancelExit);
    ///< show cashier no. form 0
    while (1)
    {
        for ( ; (isFresh) && (index < CASH_MAXCASHIER) && (index >= 0); ) {
            memset(aucCashierNo, 0, sizeof(aucCashierNo));
            memcpy(aucCashierNo, DataCashier.aucCashierNo[index], CASH_CASHIERNOLEN);
            if (strlen(aucCashierNo) > 0) {
                mmi_clearLine(DISP_Line3);
                mmi_display(DISP_Line3, DISP_HCenter, aucCashierNo);
                break;
            }
            index += flag;
        }

        isFresh = 1;
        iKey = mmi_inputWaitKeypress(60);
        if (KEY_NONE == iKey || KEY_CANCEL == iKey) {
            return ERR_CANCEL;
        }
        else if (transUtil_CheckPgDn(iKey)) {
            if (index < (CASH_MAXCASHIER - 1)) {
                index++;
                flag = 1;
                continue;
            }
        }
        else if (transUtil_CheckPgUp(iKey)) {
            if (index > 0) {
                index--;
                flag = -1;
                continue;
            }
        }
        isFresh = 0;
    }
}

/**
 * @brief modify cashier
 */
int CASH_ModiCashierPwd(void)
{
    int iRet = SUCCESS;
    const char *pTitle = AMSG_ChangeCashierNoPwd;
    unsigned char mCashierNoType = 0;
    unsigned char aucCashierNo[4] = {0};
    unsigned int index = 0;

SIG_BEGIN:
    ///< input cashier no.
    memset(aucCashierNo, 0, sizeof(aucCashierNo));
    iRet = CASH_InputCashierNo(pTitle, aucCashierNo);
    if (SUCCESS == iRet) {
        mCashierNoType = CASH_FindCashierNoEx(aucCashierNo, &index);
        if (CASH_TYPE_SUPER == mCashierNoType || CASH_TYPE_SYS == mCashierNoType) {
            iRet = CASHIER_PWD_CHANGE_NOT_ALLOW;
        }
        else if (!mCashierNoType) {
            iRet = CASHIER_NO_EXIST;
        }
        if (SUCCESS != iRet) {
            transErr_DispErrMsg(0, transErr_SetSubErrCode(ERR_CASHIER, iRet));
            goto SIG_BEGIN;
        }
    }

    if (SUCCESS == iRet) {
        iRet = CASH_ChangePwdEx(pTitle, CASH_CASHIERPASSLEN, CASH_CASHIERPASSLEN,
                                DataCashier.aucCashierPass[index], sizeof(DataCashier.aucCashierPass[index]));
    }
    return iRet;
}

/**
 * @brief change admin pwd
 */
int CASH_ChangeAdminPwd(void)
{
    return CASH_ChangePwdEx(AMSG_ChangeAdminPwd, CASH_SYSCASHIERPASSLEN, CASH_SYSCASHIERPASSLEN,
                            DataCashier.aucSYSCashierPass, sizeof(DataCashier.aucSYSCashierPass));
}

/**
 * @brief change manage pwd
 */
int CASH_ChangeManagePwd(void)
{
    return CASH_ChangePwdEx(AMSG_ChangeManagePwd, CASH_SUPERPASSWDLEN, CASH_SUPERPASSWDLEN,
                            DataCashier.aucSuperPSW, sizeof(DataCashier.aucSuperPSW));
}

/**
 * @brief change safe pwd
 */
int CASH_ChangeSafePwd(void)
{
    return CASH_ChangePwdEx(AMSG_ChangeSafePwd, CASH_SAFEPASSWDLEN, CASH_SAFEPASSWDLEN,
                            DataCashier.aucSafePSW, sizeof(DataCashier.aucSafePSW));
}

/**
 * @brief init admin pwd
 */
int CASH_InitAdminPwd(void)
{
    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_ResetAdminPwd);
    mmi_display(DISP_Line3, DISP_HCenter, AMSG_IsResetAdminPwd);
    mmi_display(DISP_Line6, DISP_HCenter, AMSG_EnterOrCancel);
    while (1)
    {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_CANCEL:
            return ERR_CANCEL;
        case KEY_NONE:
            return ERR_TIMEOUT;
        case KEY_ENTER:
            memset(DataCashier.aucSYSCashierPass, 0, sizeof(DataCashier.aucSYSCashierPass));
            memcpy(DataCashier.aucSYSCashierPass, CASH_DEF_SYS_CASHIER_PWD, CASH_SYSCASHIERPASSLEN);
            if (SUCCESS == UFile_WriteFileIndexOf(DB_Cashier)) {
                CASH_DisplayMsg(AMSG_ResetSuccess);
                return SUCCESS;
            }
            break;
        default:
            break;
        }
    }
}

/**
 * @brief cashier logon
 */
int trans_CashierLogon(void)
{
    extern int posParam_SystemManagement(void);
    unsigned char mCashierNoType = 0;
    unsigned char aucCashierNo[4] = {0};
    unsigned char aucCashierPwd[9] = {0};
    const char *title = AMSG_Title_Logon;
    unsigned int index = 0;
    int iRet = SUCCESS;

    while (1)
    {
        memset(aucCashierNo, 0, sizeof(aucCashierNo));
        memset(aucCashierPwd, 0, sizeof(aucCashierPwd));

        ///< get cashier no. input
        iRet = CASH_InputCashierNo(title, aucCashierNo);
        if (SUCCESS != iRet && ERR_TIMEOUT != iRet) {
            iRet = ERR_CANCEL;
        }

        ///< check the cashier & get the pwd
        if (SUCCESS == iRet) {
            mCashierNoType = CASH_FindCashierNoEx(aucCashierNo, &index);
            if (CASH_TYPE_SYS == mCashierNoType) {
                iRet = CASH_CheckAdminPwd(title);
            }
            else if (CASH_TYPE_SUPER == mCashierNoType) {
                iRet = CASH_CheckManagePwd(title);
            }
            else if (CASH_TYPE_CASHIER == mCashierNoType) {
                iRet = CASH_InputPassword(title, AMSG_InputCashierNoPwd, NULL, CASH_CASHIERPASSLEN, CASH_CASHIERPASSLEN, DataCashier.aucCashierPass[index]);
            }
            else {
                transErr_DispErrMsg(0, transErr_SetSubErrCode(ERR_CASHIER, CASHIER_NO_EXIST));
                continue;
            }
        }

        if (SUCCESS == iRet) {
            ///< admin cashier logon
            memset(DataChange.cashierNo, 0, 2);
            memcpy(DataChange.cashierNo, aucCashierNo, 2);
            DataChange.isCashierLogon = 0;
            if (CASH_TYPE_CASHIER == mCashierNoType) {
                DataChange.isCashierLogon = 1;
                return SUCCESS;
            }
            else if (CASH_TYPE_SUPER == mCashierNoType) {
                ///< stop  dormancy
                if (SLEEP_LEVEL_NOSLEEP != GetSysSleepLevel()) {
                    SetSysSleepLevel(SLEEP_LEVEL_NOSLEEP);
                }

                ///< enter the param setting menu
                posParam_SystemManagement();

                ///< restore dormancy
                if (GetSysSleepLevel() != (sleep_level_t)SystemSave.sysSleepType) {
                    SetSysSleepLevel((sleep_level_t)SystemSave.sysSleepType);
                }
                return ERR_CANCEL;
            }
            return ERR_END;
        }
        else if (ERR_PWD_CASH_PASS == iRet) {
            transErr_DispErrMsg(0, iRet);
            continue;
        }
        break;
    }
    return iRet;
}

