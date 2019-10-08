#include "bwsdk_api.h"
#include "applib_def.h"
#include "applib_tools.h"

#include "mmi_display.h"
#include "mmi_input.h"
#include "uFile.h"

#include "trans.h"
#include "cashier.h"

enum
{
    PARAM_OkNo,
    PARAM_YesNo,
    PARAM_Clear
};

int posParam_Tool_1Or0(const char *title,
                       const char *caption,
                       unsigned char type,
                       bool isAscii,
                       tsDBIndex fileIndex,
                       unsigned char *pValue)
{
    int iKey;
    unsigned char mSelect;

    if (!pValue) {
        return SUCCESS;
    }

    mSelect = (*pValue) + (false == isAscii ? '0' : 0);
BEGIN:
    mmi_clearLine(DISP_ClearALL);
    if (title) {
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, title);
    }
    mmi_display(DISP_Line2, DISP_Left, caption);
    switch(type)
    {
    case PARAM_OkNo:
        mmi_display(DISP_Line4, DISP_Left,
                    AMSG_Param_Msg10,
                    (mSelect == '1' ? " <=" : ""),
                    (mSelect == '0' ? " <=" : ""));
        break;
    case PARAM_YesNo:
        mmi_display(DISP_Line4, DISP_Left,
                    AMSG_Param_Msg11,
                    (mSelect == '1' ? " <=" : ""),
                    (mSelect == '0' ? " <=" : ""));
        break;
    case PARAM_Clear:
        mmi_display(DISP_Line4, DISP_Left,
                    AMSG_Param_Msg12,
                    (mSelect == '1' ? " <=" : ""),
                    (mSelect == '0' ? " <=" : ""));
        break;
    default:
        return ERR_PARAM;
    }

    while(1)
    {
        iKey = mmi_inputWaitKeypress(60);
        if (KEY_ASCII0 == iKey || KEY_ASCII1 == iKey) {
            mSelect = iKey;
            goto BEGIN;
        }
        else if (KEY_NONE == iKey) {
            return ERR_TIMEOUT;
        }
        else if (KEY_CANCEL == iKey) {
            return ERR_CANCEL;
        }
        else if (KEY_ENTER == iKey) {
            if ((mSelect - (false == isAscii ? '0' : 0)) != *pValue) {
                *pValue = mSelect - (false == isAscii ? '0' : 0);
                if (fileIndex < DB_MaxIndex) {
                    return UFile_WriteFileIndexOf(fileIndex);
                }
            }
            return SUCCESS;
        }
    }
}

#define posParam_OkNO_bcd(title, caption, value, index)     posParam_Tool_1Or0(title, caption, PARAM_OkNo, false, index, value)
#define posParam_OkNO_bcd_noSave(title, caption, value)     posParam_Tool_1Or0(title, caption, PARAM_OkNo, false, DB_MaxIndex, value)
#define posParam_OkNO_ascii(title, caption, value, index)   posParam_Tool_1Or0(title, caption, PARAM_OkNo, true, index, value)
#define posParam_OkNO_ascii_noSave(title, caption, value)   posParam_Tool_1Or0(title, caption, PARAM_OkNo, true, DB_MaxIndex, value)
#define posParam_YesNo_bcd(title, caption, value, index)    posParam_Tool_1Or0(title, caption, PARAM_YesNo, false, index, value)
#define posParam_YesNo_bcd_noSave(title, caption, value)    posParam_Tool_1Or0(title, caption, PARAM_YesNo, false, DB_MaxIndex, value)
#define posParam_YesNo_ascii(title, caption, value, index)  posParam_Tool_1Or0(title, caption, PARAM_YesNo, true, index, value)
#define posParam_YesNo_ascii_noSave(title, caption, value)  posParam_Tool_1Or0(title, caption, PARAM_YesNo, true, DB_MaxIndex, value)
#define posParam_Clear_bcd(title, caption, value)           posParam_Tool_1Or0(title, caption, PARAM_Clear, false, DB_MaxIndex, value)

int posParam_inputAmount(const char *title, const char *caption, unsigned long *amount)
{
    int iRet = SUCCESS;

    if (!amount) {
        return iRet;
    }

    mmi_clearLine(DISP_ClearALL);
    if (title) {
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, title);
    }
    mmi_display(DISP_Line2, DISP_Left, caption);
    mmi_display(DISP_Line5, DISP_Left, AMSG_InputErrClearKey);
    iRet = mmi_InputAmount(DISP_Line3, DISP_HCenter, 0, amount, 0, 999999999, 60);
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileIndexOf(DB_Constant);
    }
    return iRet;
}

/**
 * @brief 商户参数设置
 * @brief set merchant info
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetMerchantInfo(void)
{
    int iRet = SUCCESS;
    unsigned int inputType;
    const char *pTitle = AMSG_Param_Msg1;
    unsigned char ucBuffer[64] = {0};

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(pTitle, AMSG_Param_Msg8, &DataConstant.posState, DB_Constant);
    }

    ///< TID
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg13);
        inputType = mmi_setInputType(InputMethod_digital, InputMethod_digital|InputMethod_caps_abc|InputMethod_lower_abc);
        memset(ucBuffer, 0, sizeof(ucBuffer));
        memcpy(ucBuffer, DataConstant.TID, TID_LEN);
        iRet = mmi_inputString(DISP_Line3, inputType, ucBuffer, TID_LEN, TID_LEN, NULL, 60);
        if (SUCCESS == iRet) {
            ///< 检查终端号是否变化
            if (memcmp(ucBuffer, DataConstant.TID, TID_LEN)) {
                ///< 检查终端是否存在未结算交易
                if (DataTransDetail.transCount > 0) {
                    iRet = ERR_PLZ_SETTLE;
                } else {
                    ///< 首次设置终端号不验证安全密码
                    if (strlen((const char *)DataConstant.TID) > 0) {
                        ///< 验证安全密码
                        iRet = CASH_CheckSafePwd(pTitle);
                    }
                    ///< 保存终端号
                    if (SUCCESS == iRet) {
                        memset(DataConstant.TID, 0, sizeof(DataConstant.TID));
                        memcpy(DataConstant.TID, ucBuffer, TID_LEN);
                        iRet = UFile_WriteFileIndexOf(DB_Constant);
                        ///< 清除签到相关状态
                        if (SUCCESS == iRet) {
                            DataChange.isLogon = 0;
                            DataChange.isStoreKeyDownRight = 0;
                            DataChange.isUpdateBatch = 0;
                            memset(DataChange.logonDate, 0, sizeof(DataChange.logonDate));
                            DataChange.isCashierLogon = 0;
                            memset(DataChange.cashierNo, 0, 2);
                            UFile_WriteFileIndexOf(DB_Change);
                        }
                    }
                }
            }
        }
    }

    ///< Merchant ID
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg14);
        inputType = mmi_setInputType(InputMethod_digital, InputMethod_digital|InputMethod_caps_abc|InputMethod_lower_abc);
        memset(ucBuffer, 0, sizeof(ucBuffer));
        memcpy(ucBuffer, DataConstant.MID, MID_LEN);
        iRet = mmi_inputString(DISP_Line3, inputType, ucBuffer, MID_LEN, MID_LEN, NULL, 60);
        if (SUCCESS == iRet) {
            ///< 检查商户号是否变化
            if (memcmp(ucBuffer, DataConstant.MID, MID_LEN)) {
                ///< 检查终端是否存在未结算交易
                if (DataTransDetail.transCount > 0) {
                    iRet = ERR_PLZ_SETTLE;
                } else {
                    ///< 首次设置商户号不验证安全密码
                    if (strlen((const char *)DataConstant.MID) > 0) {
                        ///< 验证安全密码
                        iRet = CASH_CheckSafePwd(pTitle);
                    }
                    ///< 保存商户号
                    if (SUCCESS == iRet) {
                        memset(DataConstant.MID, 0, sizeof(DataConstant.MID));
                        memcpy(DataConstant.MID, ucBuffer, MID_LEN);
                        iRet = UFile_WriteFileIndexOf(DB_Constant);
                        ///< 清除签到相关状态
                        if (SUCCESS == iRet) {
                            DataChange.isLogon = 0;
                            DataChange.isStoreKeyDownRight = 0;
                            DataChange.isUpdateBatch = 0;
                            memset(DataChange.logonDate, 0, sizeof(DataChange.logonDate));
                            DataChange.isCashierLogon = 0;
                            memset(DataChange.cashierNo, 0, 2);
                            UFile_WriteFileIndexOf(DB_Change);
                        }
                    }
                }
            }
        }
    }

    ///< Merchant Name
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg15);
        inputType = mmi_setInputType(InputMethod_digital, InputMethod_digital|InputMethod_caps_abc|InputMethod_lower_abc);
        memset(ucBuffer, 0, sizeof(ucBuffer));
        strcpy((char *)ucBuffer, (const char *)DataConstant.merchantName);
        iRet = mmi_inputString(DISP_Line3, inputType, ucBuffer, 0, MERCHANTNAME_LEN, NULL, 60);
        if (SUCCESS == iRet) {
            if (strcmp((const char *)ucBuffer, (const char *)DataConstant.merchantName)) {
                memset(DataConstant.merchantName, 0, sizeof(DataConstant.merchantName));
                strcpy((char *)DataConstant.merchantName, (const char *)ucBuffer);
                iRet = UFile_WriteFileIndexOf(DB_Constant);
            }
        }
    }

    ///< 流水号
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg16);
        memset(ucBuffer, 0, sizeof(ucBuffer));
        memcpy(ucBuffer, DataChange.traceNumber, 6);
        iRet = mmi_inputString(DISP_Line3, InputMethod_digital<<8|InputMethod_digital,
                                ucBuffer, 1, 6, NULL, 60);
        if (SUCCESS == iRet) {
            if (strcmp((const char *)ucBuffer, (const char *)DataChange.traceNumber)) {
                memset(DataChange.traceNumber, 0, sizeof(DataChange.traceNumber));
                strcpy((char *)DataChange.traceNumber, (const char *)ucBuffer);
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(AMSG_Param_Msg1, AMSG_Param_Msg20, NULL, DB_MaxIndex);
    }

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(pTitle, AMSG_Param_Msg23, &DataConstant.isVoidSwipe, DB_Constant);
    }

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(pTitle, AMSG_Param_Msg25, &DataConstant.isVoidInputPIN, DB_Constant);
    }

    return iRet;
}

//
/**
 * @brief 通讯参数设置
 * @brief set socket param
 * @retval SUCCESS  success
 * @retval other    failure
 */
int posParam_SetSocketParam(void)
{
    int iRet = SUCCESS;
    const char *pTitle = AMSG_Param_Msg2;
    unsigned int inputType;
    unsigned char mBuf[20];

    ///< TPDU:
    if (SUCCESS == iRet) {
        memset(mBuf, 0, sizeof(mBuf));
        tools_bcd_asc(mBuf, DataConstant.tpdu, 10);

        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, "TPDU:");
        inputType = mmi_setInputType(InputMethod_digital,InputMethod_digital);
        iRet = mmi_inputString(DISP_Line3, inputType, mBuf, 0, 10, NULL, 60);
        if (SUCCESS == iRet) {
            tools_asc_bcd(DataConstant.tpdu, 5, mBuf, 10);
        }
        
        if (SUCCESS == iRet) {
            iRet = UFile_WriteFileIndexOf(DB_Constant);
        }
    }

    ///< 主机1 IP:
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg29);
        iRet = mmi_InputIPV4Addr(DISP_Line3, (unsigned char *)DataCommu.host, 60);
        if (SUCCESS == iRet) {
            iRet = UFile_WriteFileIndexOf(DB_Commu);
        }
    }

    ///< 主机1 端口:
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg30);
        iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataCommu.port,
                                sizeof(DataCommu.port), 0, 999999, 60);
        if (SUCCESS == iRet) {
            iRet = UFile_WriteFileIndexOf(DB_Commu);
        }
    }

    ///< 主机1 SSL:
    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(pTitle, AMSG_Param_Msg31, &DataCommu.sslEnable, DB_Commu);
    }

    ///< 重试次数:
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg32);
        iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataConstant.dialRetry,
                                sizeof(DataConstant.dialRetry), 1, 6, 60);
        if (SUCCESS == iRet) {
            iRet = UFile_WriteFileIndexOf(DB_Constant);
        }
    }

    ///< 接收超时:
    if (SUCCESS == iRet) {
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
        mmi_display(DISP_Line2, 0, AMSG_Param_Msg33);
        iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataConstant.recvTimeout,
                                sizeof(DataConstant.recvTimeout), 10, 120, 60);
        if (SUCCESS == iRet) {
            iRet = UFile_WriteFileIndexOf(DB_Constant);
        }
    }

    return iRet;
}

/**
 * @brief 其他交易控制
 * @brief settle trans off-on
 * @retval SUCCESS  success
 * @retval other    failure
 */
int posParam_SetTransOtherParam(void)
{
    int iRet = SUCCESS;
    const char *title = AMSG_Param_Msg44;

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(title, AMSG_Param_Msg45, &DataConstant.bisCheckAdminPwd, DB_Constant);
    }

    if (SUCCESS == iRet) {
        iRet = posParam_YesNo_bcd(title, AMSG_Param_Msg48, &DataConstant.emvDebug, DB_Constant);
    }
    
    return iRet;
}

/**
 * @brief 打印张数设置
 * @brief set print times
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetPrintTimes(void)
{
    int iRet = SUCCESS;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg49);
    mmi_display(DISP_Line2, 0, AMSG_Param_Msg50);
    iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataConstant.ucPrintTimes, sizeof(DataConstant.ucPrintTimes), 0, 3, 60);
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileIndexOf(DB_Constant);
    }
    
    return iRet;
}

/**
 * @brief 设置最大交易笔数
 * @brief set max trans number
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetMaxTransNum(void)
{
    int iRet = SUCCESS;

    mmi_clearLine(DISP_ClearALL);
    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg51);
    mmi_display(DISP_Line2, 0, AMSG_Param_Msg52);
    iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataConstant.maxTransNum, sizeof(DataConstant.maxTransNum), 1, MAX_TRANS_NUM, 60);
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileIndexOf(DB_Constant);
    }
    return iRet;
}

static int posParam_SetSubTransParamMenu(void)
{
    int iRet = SUCCESS;
    int iKey;
    bool bRefresh = true;

    while(1)
    {
        if (true == bRefresh) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg3);
            mmi_display(DISP_Line2, 0, "1.%s", AMSG_Param_Msg56);
            mmi_display(DISP_Line3, 0, "2.%s", AMSG_Param_Msg49);
            mmi_display(DISP_Line4, 0, "3.%s", AMSG_Param_Msg58);
            mmi_display(DISP_Line5, 0, "4.%s", AMSG_Param_Msg59);
        }

        bRefresh = true;
        iKey = mmi_inputWaitKeypress(60);
        switch(iKey)
        {
        case KEY_ASCII1:
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg62);
            mmi_display(DISP_Line2, 0, AMSG_Param_Msg63);
            iRet = mmi_inputDigital(DISP_Line3, 0, (unsigned char*)&DataConstant.transRetry, sizeof(DataConstant.transRetry), 1, 6, 60);
            if (SUCCESS == iRet) {
                iRet = UFile_WriteFileIndexOf(DB_Constant);
            }
            break;
        case KEY_ASCII2:
            iRet = posParam_SetPrintTimes();
            break;
        case KEY_ASCII3:
            iRet = posParam_SetMaxTransNum();
            break;
        case KEY_ASCII4:
            iRet = posParam_SetTransOtherParam();
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            bRefresh = false;
            continue;
        }

        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SetSuccess);
            mmi_inputWaitKeypress(5);
        }
        else if (iRet != ERR_CANCEL
              && iRet != ERR_END) {
            transErr_DispErrMsg(0, iRet);
        }
    }
}

/**
 * @brief 清除交易流水
 * @brief clear trans data
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_ClearTransData(void)
{
    int iRet = SUCCESS;
    unsigned char mFlag;

    if (SUCCESS == iRet) {
        mFlag = 0;
        iRet = posParam_Clear_bcd(NULL, AMSG_Param_Msg64, &mFlag);
        if (1 == mFlag) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg64);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg65);
            Sleep(150);
            if (SUCCESS == (iRet = transUtil_ClearReversal())) {
                mmi_clearLine(DISP_VCenter);
                mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg66);
                mmi_inputWaitKeypress(5);
            }
        }
    }

    if (SUCCESS == iRet) {
        mFlag = 0;
        iRet = posParam_Clear_bcd(NULL, AMSG_Param_Msg67, &mFlag);
        if (1 == mFlag) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg67);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg65);
            Sleep(150);
            if (SUCCESS == (iRet = transUtil_ClearScript())) {
                mmi_clearLine(DISP_VCenter);
                mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg66);
                mmi_inputWaitKeypress(5);
            }
        }
    }

    if (SUCCESS == iRet) {
        mFlag = 0;
        iRet = posParam_Clear_bcd(NULL, AMSG_Param_Msg68, &mFlag);
        if (1 == mFlag) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg68);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg65);
            Sleep(150);
            if (SUCCESS == (iRet = transUtil_ClearTrans())) {
                mmi_clearLine(DISP_VCenter);
                mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg66);
                mmi_inputWaitKeypress(5);
            }
        }
    }

    if (iRet != ERR_CANCEL
     && iRet != ERR_END
     && iRet != SUCCESS) {
        transErr_DispErrMsg(0, iRet);
    }
    
    return iRet;
}

/**
 * @brief 清除终端参数
 * @brief clear terminal param
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_ClearParam(void)
{
    int iRet = SUCCESS;
    unsigned char mFlag;

    if (SUCCESS == iRet) {
        mFlag = 0;
        iRet = posParam_Clear_bcd(NULL, AMSG_Param_Msg69, &mFlag);
        if (1 == mFlag) {
            if (DataTransDetail.transCount > 0) {
                iRet = ERR_PLZ_SETTLE;
            } else {
                mmi_clearLine(DISP_ClearALL);
                mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg69);
                mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg65);
                Sleep(150);
                if (SUCCESS == (iRet = transUtil_ClearParam())) {
                    mmi_clearLine(DISP_VCenter);
                    mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Param_Msg66);
                    mmi_inputWaitKeypress(5);
                }
            }
        }
    }

    if (iRet != ERR_CANCEL
     && iRet != ERR_END
     && iRet != SUCCESS) {
        transErr_DispErrMsg(0, iRet);
    }
    
    return iRet;
}

/**
 * @brief 密码管理
 * @brief pwd manage
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_PwdManageMenu(void)
{
    int iKey = KEY_NONE;
    bool bRefresh = true;
    int iRet = 0;

    while(1)
    {
        if (true == bRefresh) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg6);
            mmi_display(DISP_Line2, 0, "1.%s", AMSG_ChangeManagePwd);
            mmi_display(DISP_Line3, 0, "2.%s", AMSG_ChangeSafePwd);
            mmi_display(DISP_Line4, 0, "3.%s", AMSG_ResetAdminPwd);
        }

        bRefresh = true;
        iKey = mmi_inputWaitKeypress(60);
        switch(iKey)
        {
            case KEY_ASCII1:
                iRet = CASH_ChangeManagePwd();
                break;
            case KEY_ASCII2:
                iRet = CASH_ChangeSafePwd();
                break;
            case KEY_ASCII3:
                iRet = CASH_InitAdminPwd();
                break;
            case KEY_CANCEL:
            case KEY_NONE:
                return ERR_CANCEL;
            default:
                bRefresh = false;
                continue;
        }

        if (iRet != SUCCESS
         && iRet != ERR_CANCEL
         && iRet != ERR_END) {
            transErr_DispErrMsg(0, iRet);
        }
    }
}

/**
 * @brief download menu
 */
static int posParam_DownloadMenu(void)
{
    int iKey = KEY_NONE;
    bool bRefresh = true;

    while(1) {
        if (true == bRefresh) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, "%s ↓↑", AMSG_Param_Msg70);
            mmi_display(DISP_Line4, 0, "1.%s", AMSG_Param_Msg73);
            mmi_display(DISP_Line5, 0, "2.%s", AMSG_Param_Msg74);
            mmi_display(DISP_Line6, 0, "3.%s", AMSG_Param_Msg75);
        }

        bRefresh = true;
        iKey = mmi_inputWaitKeypress(60);
        switch (iKey)
        {
        case KEY_ASCII1:
            trans_LoadCAPK();
            break;
        case KEY_ASCII2:
            trans_LoadAID();
            break;
        case KEY_ASCII3:
            trans_LoadRF();
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            bRefresh = false;
            continue;
        }
    }
}

/**
 * @brief 其他功能设置
 * @brief set other func
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetOtherParamMenu(void)
{
    int iKey;
    bool bRefresh = true;

    while(1)
    {
        if (true == bRefresh) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, AMSG_Param_Msg7);
            mmi_display(DISP_Line2, 0, "1.%s", AMSG_Param_Msg68);
            mmi_display(DISP_Line3, 0, "2.%s", AMSG_Param_Msg70);
            mmi_display(DISP_Line4, 0, "3.%s", AMSG_Param_Msg69);
        }

        bRefresh = true;
        iKey = mmi_inputWaitKeypress(60);
        switch(iKey)
        {
        case KEY_ASCII1:
            posParam_ClearTransData();
            break;
        case KEY_ASCII2:
            posParam_DownloadMenu();
            break;
        case KEY_ASCII3:
            posParam_ClearParam();
            break;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            bRefresh = false;
            continue;
        }
    }
}

/**
 * @brief 非接参数设置
 * @brief set rf param
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetRFParam(void)
{
    int iRet = SUCCESS;
    const char *pTitle = AMSG_Param_Msg75;

    ///< 免密开关
    if (SUCCESS == iRet) {
        iRet = posParam_OkNO_bcd(pTitle, AMSG_Param_Msg79, &DataChange.QPS_NoPIN_Flag, DB_Change);
    }

    ///< 免密限额
    if (DataChange.QPS_NoPIN_Flag) {
        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
            mmi_display(DISP_Line2, 0, AMSG_Param_Msg80);
            iRet = mmi_InputAmount(DISP_Line3, DISP_Left, 0, &DataChange.QPS_PINAmtLimit, 0, 1000000, 60);
            if (SUCCESS == iRet) {
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }

    ///< 免签开关
    if (SUCCESS == iRet) {
        iRet = posParam_OkNO_bcd(pTitle, AMSG_Param_Msg83, &DataChange.QPS_Signature_Flag, DB_Change);
    }

    ///< 免签限额
    if (DataChange.QPS_Signature_Flag) {
        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
            mmi_display(DISP_Line2, 0, AMSG_Param_Msg84);
            iRet = mmi_InputAmount(DISP_Line3, DISP_Left, 0, &DataChange.QPS_SignatureAmtLimit, 0, 1000000, 60);
            if (SUCCESS == iRet) {
                iRet = UFile_WriteFileIndexOf(DB_Change);
            }
        }
    }

    ///< CDCVM开关
    if (SUCCESS == iRet) {
        iRet = posParam_OkNO_bcd(pTitle, AMSG_Param_Msg85, &DataChange.QPS_CDCVM_Flag, DB_Change);
    }
    return iRet;
}

///<-------------add esign----------->///
/**
 * @brief 电子签名设置
 * @brief set elecsign param
 * @retval SUCCESS  success
 * @retval other    failure
 */
static int posParam_SetEsParam(void)
{
    int iRet = SUCCESS;
    const char *pTitle = AMSG_Param_Msg9;

    ///< 是否支持电子签名
    iRet = posParam_OkNO_bcd(pTitle, AMSG_Param_Msg86, &DataEsign.bisSupportEs, DB_EsignParam);
    
    if (DataEsign.bisSupportEs) {
        ///< 电子签名超时时间
        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
            mmi_display(DISP_Line2, 0, AMSG_Param_Msg87);
            iRet = mmi_inputDigital(DISP_Line3, 0,
                    (unsigned char *)&DataEsign.usEsSignTimeOut,
                    sizeof(DataEsign.usEsSignTimeOut), 15, 900, 60);
            if (SUCCESS == iRet) {
                iRet = UFile_WriteFileIndexOf(DB_EsignParam);
            }
        }

        ///< 电子签名最大重签次数
        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pTitle);
            mmi_display(DISP_Line2, 0, AMSG_Param_Msg91);
            iRet = mmi_inputDigital(DISP_Line3, 0,
                    &DataEsign.ucEsReSignMaxTimes,
                    sizeof(DataEsign.ucEsReSignMaxTimes), 1, 9, 60);
            if (SUCCESS == iRet) {
                iRet = UFile_WriteFileIndexOf(DB_EsignParam);
            }
        }

        ///< 电签是否打印签购单
        if (SUCCESS == iRet) {
            iRet = posParam_YesNo_bcd(pTitle, AMSG_Param_Msg94, &DataEsign.bisEsPrintVoucher, DB_EsignParam);
        }
    }
    
    return iRet;
}
///<-------------------------->///

int posParam_SystemManagement(void)
{
    extern int sysSettingsMenu(void);
    int iRet = SUCCESS;
    int iKey;
    bool bRefresh = true;
    unsigned char page = 0;

    while(1)
    {
        if (true == bRefresh) {
            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, "%s ↓↑", AMSG_Title_SysManage);
            if (!page) {
                mmi_display(DISP_Line2, 0, "1.%s", AMSG_Param_Msg1);
                mmi_display(DISP_Line3, 0, "2.%s", AMSG_Param_Msg2);
                mmi_display(DISP_Line4, 0, "3.%s", AMSG_Param_Msg3);
                mmi_display(DISP_Line5, 0, "4.%s", AMSG_Param_Msg4);
                mmi_display(DISP_Line6, 0, "5.%s", AMSG_Param_Msg5);
            }
            else {
                mmi_display(DISP_Line2, 0, "6.%s", AMSG_Param_Msg6);
                mmi_display(DISP_Line3, 0, "7.%s", AMSG_Param_Msg7);
                mmi_display(DISP_Line4, 0, "8.%s", AMSG_Param_Msg75);
                ///<-------add esign------->///
                mmi_display(DISP_Line5, 0, "9.%s", AMSG_Param_Msg9);
                ///<----------------------->///
            }
        }

        bRefresh = true;
        iKey = mmi_inputWaitKeypress(60);
        switch(iKey)
        {
        case KEY_ASCII1:
            iRet = posParam_SetMerchantInfo();
            break;
        case KEY_ASCII2:
            iRet = posParam_SetSocketParam();
            break;
        case KEY_ASCII3:
            iRet = posParam_SetSubTransParamMenu();
            break;
        case KEY_ASCII4:
            iRet = POS_KeyManageMenu();
            break;
        case KEY_ASCII5:
            iRet = sysSettingsMenu();
            break;
        case KEY_ASCII6:
            iRet = posParam_PwdManageMenu();
            break;
        case KEY_ASCII7:
            iRet = posParam_SetOtherParamMenu();
            break;
        case KEY_ASCII8:
            iRet = posParam_SetRFParam();
            break;
        ///<----------add esign----------->///
        case KEY_ASCII9:
            iRet = posParam_SetEsParam();
            break;
        ///<------------------------------>///
        case KEY_UP:
            if (page > 0) {
                page--;
            }
            continue;
        case KEY_DOWN:
            if (page < 1) {
                page ++;
            }
            continue;
        case KEY_CANCEL:
        case KEY_NONE:
            return ERR_CANCEL;
        default:
            bRefresh = false;
            continue;
        }

        if (SUCCESS == iRet) {
            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_SetSuccess);
            mmi_inputWaitKeypress(5);
        }
        else if (iRet != ERR_CANCEL
              && iRet != ERR_END) {
            transErr_DispErrMsg(0, iRet);
        }
    }
}

