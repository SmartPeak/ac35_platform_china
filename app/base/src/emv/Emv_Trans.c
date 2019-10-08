#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "AppCallBack.h"
#include "EmvCtKernelMain.h"
#include "Kernel_Param.h"
#include "Kernel_Main.h"

#include "EmvKernel.h"
#include "EmvCtKernelL2.h"
#include "Emv_Callback.h"
#include "Emv_CT_Callback.h"
#include "Emv_CL_Callback.h"
#include "Emv_Utile.h"
#include "Emv_Param.h"
#include "emv_ct_storage.h"
#include "Emv_Trans.h"

#include "trans.h"

#define DEBUG_EMV_TRANS         0
#if DEBUG_EMV_TRANS
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_Trans.c"
#endif

struct KERNEL_CALLBACK_FUNCS _CALLBACK_KERNEL;

union _DRV_DATA
{
    MagTrack_T          magTrack;
    MAG_TRACK_DATA      emvMagTrack;
};
union _DRV_DATA drvData;

/*接触内核检卡*/
CT_DETECT_MODE Kernel_Contact_DetectCard(char bFallBackFlag, char bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData);

static int getMagTrack(MagTrack_T *pInData, MAG_TRACK_DATA *pOutData)
{
    if (!pInData || !pOutData) {
        return EMVErr_SetCTErrCode(EMV_ICC_DATA_ERR);
    }

    if (strlen((char*)pInData->aucTrack1) > 0){
        strcpy((char*)pOutData->m_Track1, (char*)pInData->aucTrack1);
#if 0
        logger_serial_dump_buff("Track1:", pInData->aucTrack1, strlen((char*)pInData->aucTrack1));
        logger_serial_dump_buff("Track1:", pOutData->m_Track1, strlen((char*)pOutData->m_Track1));
#endif
    }
    if (strlen((char*)pInData->aucTrack2) > 0){
        strcpy((char*)pOutData->m_Track2, (char*)pInData->aucTrack2);
#if 0
        logger_serial_dump_buff("Track2:", pInData->aucTrack2, strlen((char*)pInData->aucTrack2));
        logger_serial_dump_buff("Track2:", pOutData->m_Track2, strlen((char*)pOutData->m_Track2));
#endif
    } else {
        return EMVErr_SetCTErrCode(EMV_ICC_DATA_ERR);
    }

    if (strlen((char*)pInData->aucTrack3) > 0){
        strcpy((char*)pOutData->m_Track3, (char*)pInData->aucTrack3);
#if 0
        logger_serial_dump_buff("Track3:", pInData->aucTrack3, strlen((char*)pInData->aucTrack3));
        logger_serial_dump_buff("Track3:", pOutData->m_Track3, strlen((char*)pOutData->m_Track3));
#endif
    }
    pOutData->m_TrackExistFlag = EMV_TRUE;
    return SUCCESS;
}

int Kernel_GetResult(void)
{
    int iRet = _TRANS_HANDLE.ret;

#if DEBUG_EMV_TRANS
    LOGD("[%5d]%s>>>_TRANS_HANDLE.ret:%d", __LINE__, __func__, _TRANS_HANDLE.ret);
#endif
    if (iRet == TRANS_HANDLE_FF) {
        iRet = SUCCESS;
    }
#if DEBUG_EMV_TRANS
    LOGD("[%5d]%s>>>iRet:%d", __LINE__, __func__, iRet);
#endif
    return iRet;
}

/*初始化内核回调*/
char EMV_Trans_InitEntryKernel(void){

    memset((LP_EMV_BYTE)&_CALLBACK_KERNEL, 0, sizeof(_CALLBACK_KERNEL));

    ///< 内核日志打印
    _CALLBACK_KERNEL.m_Log_Print = Kernel_Log_Printf;
    ///< 获取终端时间
    _CALLBACK_KERNEL.m_GetCurrentTime = Kernel_GetCurrentTime;
    ///< 获取随机数
    _CALLBACK_KERNEL.m_GenerateRandomData = Kernel_GetRandomData;
    ///< APDU 通讯
    _CALLBACK_KERNEL.m_ExchangeApdu = Kernel_ExchangeApdu;
    ///< SM2加密
    _CALLBACK_KERNEL.m_ContactSM2VerifySign = Kernel_SM2VerifySign;
    ///< SM3哈希加密
    _CALLBACK_KERNEL.m_ContactSM3Hash = Kernel_SM3Hash;

    ///< 联机处理(接触,非接VISA,QPBOC,AMEX,D-PAS)
    _CALLBACK_KERNEL.m_FinacialTransactionRequest = Kernel_FinacialTransactionRequest;

    ///< 交易结果 Mastrt,MIR 联机,脱机处理 按照返回值处理
    _CALLBACK_KERNEL.m_Display_Trans_Report = Kernel_Display_Trans_Report;

    //非接
    _CALLBACK_KERNEL.m_DetectBreak = Kernel_CL_DetectBreak_Callback;
    ///< 联机PIN
    _CALLBACK_KERNEL.m_GetOnlinePin = Kernel_CL_GetOnlinePin;
    ///< 移卡
    _CALLBACK_KERNEL.m_AskRemoveCard = Kernel_CL_AskRemoveCard;
    ///< 二次拍卡
    _CALLBACK_KERNEL.m_SecondTapCard = Kernel_CL_SecondTapCard;
    ///< 指示当前是ic、picc或磁条
    _CALLBACK_KERNEL.m_KernelMode = Kernel_CL_KernelMode;

    //接触
    ///< 金额输入
    _CALLBACK_KERNEL.m_EnterAmount = Kernel_EnterAmount;
    ///< 应用选择
    _CALLBACK_KERNEL.m_SelectApplication = Kernel_CT_SelectApplication;
    ///< 持卡人证件验证
    _CALLBACK_KERNEL.m_ContactGetHolderCert = Kernel_Contact_GetHolderCert;
    ///< 脱机明文pin
    _CALLBACK_KERNEL.m_ContactGetPlainTextPin = Kernel_Contact_GetPlainTextPin;
    ///< 联机加密pin
    _CALLBACK_KERNEL.m_ContactGetOnlinePin = Kernel_Contact_GetOnlinePin;
    ///< 脱机密文pin
    _CALLBACK_KERNEL.m_ContactGetOffCipherPin = Kernel_Contact_GetOfflineCipherPin;
    ///< 联机参考(卡号)
    _CALLBACK_KERNEL.m_ContactPanConfirm = Kernel_Contact_PanConfirm;
    ///< 多应用选择,选择错误,界面提示
    _CALLBACK_KERNEL.m_ContactSelAppErr = Kernel_Contact_SelAppErr;
    ///< 磁条卡联机请求
    _CALLBACK_KERNEL.m_MagStripeOnlineRequeset = Kernel_MagStripe_OnlineRequeset;
    ///< 接触内核检卡
    _CALLBACK_KERNEL.m_ContactDetectCard = Kernel_Contact_DetectCard;
    ///< 接触显示卡号
    _CALLBACK_KERNEL.m_ContactShowPanNo = Kernel_CT_Display_PanNo;

    //认证(平常用不到)
    ///< 批捕获
    _CALLBACK_KERNEL.m_BatchDataCapture = NULL;
    ///< 冲正
    _CALLBACK_KERNEL.m_Reversal = NULL;
    ///< 通知
    _CALLBACK_KERNEL.m_OnlineAdvice = NULL;
    ///< 确认
    _CALLBACK_KERNEL.m_FinancialTransConfirm = NULL;
    ///< 脱机批准
    _CALLBACK_KERNEL.m_AuthorisationRequest = NULL;

    //暂时未采用.
    _CALLBACK_KERNEL.m_CardHolderConfirm = NULL;
    _CALLBACK_KERNEL.m_TryOtherApplication = NULL;
    _CALLBACK_KERNEL.m_GetPlainTextPin = NULL;
    _CALLBACK_KERNEL.m_Display_Pin_Verify_Status = NULL;
    _CALLBACK_KERNEL.m_AfterAppSelected = NULL;
    _CALLBACK_KERNEL.m_LanguageSelect = NULL;
    _CALLBACK_KERNEL.m_GetTransLogAmount = NULL;
    _CALLBACK_KERNEL.m_Issuer_Referral = NULL;
    _CALLBACK_KERNEL.m_SaveTransLog = NULL;
    _CALLBACK_KERNEL.m_GetTransLogAmt = NULL;

    return (char) Contactless_init_EntryKernel(&_CALLBACK_KERNEL);
}

/*接触内核检卡*/
CT_DETECT_MODE Kernel_Contact_DetectCard(char bFallBackFlag, char bInsertCardFlag, LP_MAG_TRACK_DATA pMagTrackData)
{
    int iRet = ERR_CANCEL;
    CT_DETECT_MODE pDetectMode = CT_DETECT_MODE_NONE;
    unsigned int uiEvent = EVENT_NULL, uiCurEvent = EVENT_NULL;
    unsigned int drvDataLen;
    unsigned char drvData[1024];
    unsigned char bRef;
    char dispMsg[20];
    unsigned long ulAmount = DataTrans.ulAmount;

#if DEBUG_EMV_TRANS
    LOGD("bFallBackFlag:%d", bFallBackFlag);
    LOGD("bInsertCardFlag:%d", bInsertCardFlag);
#endif
    mmi_EventClose(EVENT_ICC_DRV|EVENT_MAG_DRV);

    ///< 开启事件
    switch(_TRANS_HANDLE.drvMode)
    {
    case DEVMAG:
        uiEvent = EVENT_MAG_DRV;
        ///< 是带IC卡芯片的磁条卡
        if (bInsertCardFlag == EMV_TRUE) {
            uiEvent = EVENT_ICC_DRV;
        }
        break;
    case DEVICC:
        uiEvent = EVENT_ICC_DRV;
        break;
    default:
        break;
    }

    if ((iRet = mmi_EventOpen(uiEvent)) != SUCCESS) {
        goto ERR;
    }

    if ((EVENT_MFR_DRV&uiEvent)) {
        transUtil_LED_WaitReadCard();
    }

    bRef = 1;
    while(1)
    {
        if (bRef) {
            bRef = 0;

            memset(dispMsg, 0, sizeof(dispMsg));
            if ((uiEvent&EVENT_MFR_DRV)) {
                strcat(dispMsg, "挥卡");
            }
            if ((uiEvent&EVENT_ICC_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "或");
                }
                strcat(dispMsg, "插卡");
            }
            if ((uiEvent&EVENT_MAG_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "或");
                }
                strcat(dispMsg, "刷卡");
            }

            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
            if (ulAmount > 0)
            {
                mmi_display(DISP_Line3, DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
            }
            mmi_display(DISP_Line4, DISP_HCenter, "请%s", dispMsg);
        }

        drvDataLen = sizeof(drvData);
        memset(drvData, 0, sizeof(drvData));
        uiCurEvent = uiEvent;
        if ((iRet = mmi_EventWait(&uiCurEvent, drvData, &drvDataLen, 60)) != SUCCESS) {
            break;
        }

        if (EVENT_KEY_DRV == uiCurEvent) {
            if (KEY_CANCEL == drvData[0]) {
                iRet = ERR_CANCEL;
                break;
            }
        }
        else if (EVENT_ICC_DRV == uiCurEvent) {
            if (IccResetRev(NULL) >= 0) {
                if (0 == IccGetResponseEnableRev(1)) {
                    pDetectMode             = CT_DETECT_MODE_IC;
                    _TRANS_HANDLE.drvMode   = DEVICC;
                    DataTrans.cardInputType = InputMode_ICC;
                    break;
                }
            }
        }
        else if (EVENT_MAG_DRV == uiCurEvent) {
            memcpy(&ExtraData.magTrack, drvData, sizeof(ExtraData.magTrack));
            if (pMagTrackData) {
                memset(pMagTrackData, 0, sizeof(MAG_TRACK_DATA));
                iRet = getMagTrack(&ExtraData.magTrack, pMagTrackData);
            }
            pDetectMode             = CT_DETECT_MODE_MAG;
            _TRANS_HANDLE.drvMode   = DEVMAG;
            DataTrans.cardInputType = InputMode_Mag;
            break;
        }
    }

ERR:
    if (!(uiCurEvent&EVENT_MFR_DRV)) {
        transUtil_LED_Close();
    }

    if (SUCCESS == iRet) {
        ExtraData.eventType = uiCurEvent;
        uiEvent &= ~uiCurEvent;
    }
    mmi_EventClose(uiEvent);
    _TRANS_HANDLE.ret = iRet;
    return pDetectMode;
}

static int EMV_Kernel_Process(unsigned int inputMethod, unsigned char bEMVSimpleFlag, void *drvData, int *pKernelRen)
{
    int KernelRen = 0;
    unsigned int traceNumber;
    unsigned int uiAmount;

#if DEBUG_EMV_TRANS
    LOGD("[%5d]%s", __LINE__, __func__);
#endif

    traceNumber = tools_asc_long(DataChange.traceNumber, TRACE_NO_LEN);
    uiAmount = DataTrans.ulAmount;

    memset(&_TRANS_HANDLE, 0, sizeof(_TRANS_HANDLE));
    EMV_LoadConfig();
    _TRANS_HANDLE.ret = TRANS_HANDLE_FF;

    switch(inputMethod)
    {
    case EVENT_ICC_DRV:     //插卡
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
        mmi_display(DISP_Line2, DISP_HCenter, "请勿拔卡");
        mmi_display(DISP_Line3, 0, "处理中");
        mmi_display(DISP_Line4, 0, "请稍等...");

        _TRANS_HANDLE.drvMode = DEVICC;
        DataTrans.cardInputType = InputMode_ICC;
        KernelRen = Contact_Start_Kernel(traceNumber, EMV_Get_TransType(), uiAmount, 0, bEMVSimpleFlag, (MAG_TRACK_DATA *)drvData);
        break;
    case EVENT_MFR_DRV:     //非接
        _TRANS_HANDLE.drvMode = DEVPICC;
        DataTrans.cardInputType = InputMode_QICC;
        Contactless_Set_Kernel_Version(CL_Get_Kernel_Version());
        Contactless_Set_KernelApplyAid(EMV_TRUE);   ///< 按AID来
        KernelRen = Contactless_Start_Kernel(traceNumber, EMV_Get_TransType(), uiAmount, 0);
        break;
    case EVENT_MAG_DRV:     //磁条
        _TRANS_HANDLE.drvMode = DEVMAG;
        DataTrans.cardInputType = InputMode_Mag;
        ((MAG_TRACK_DATA *)drvData)->m_TrackExistFlag = EMV_TRUE;
        KernelRen = Contact_Start_Kernel(traceNumber, EMV_Get_TransType(), uiAmount, 0, bEMVSimpleFlag, (MAG_TRACK_DATA *)drvData);
        break;
    default:
        break;
    }

#if DEBUG_EMV_TRANS
    LOGD("KernelRen:%d", KernelRen);
    LOGD("[%5d]%s>>>_TRANS_HANDLE.ret:%d", __LINE__, __func__, _TRANS_HANDLE.ret);
#endif

    *pKernelRen = KernelRen;
    if (TRANS_HANDLE_FF == _TRANS_HANDLE.ret) {
        if (KernelRen) {
            _TRANS_HANDLE.ret = EMVErr_SetCLErrCode(KernelRen);
        }
    }
    return _TRANS_HANDLE.ret;
}

unsigned char EMV_GetSimpleFlag(void)
{
    if ((TRANS_VOID_SALE == ExtraData.transType)
        || (TRANS_REFUND == ExtraData.transType)) {
        return EMV_TRUE;
    }
    return EMV_FALSE;
}

int EMV_Trans(void)
{
    int iRet = ERR_CANCEL;
    int KernelRen = 0;
    MAG_TRACK_DATA  pMagTrack;

    memset(&pMagTrack, 0, sizeof(MAG_TRACK_DATA));
    EMV_Trans_InitEntryKernel();    //初始化回调
    CT_Start_Trans_InitParam();
    switch (ExtraData.eventType)
    {
    case EVENT_ICC_DRV:     ///< 接触
        iRet = EMV_Kernel_Process(EVENT_ICC_DRV, EMV_GetSimpleFlag(), (char *)&pMagTrack, &KernelRen);
        break;
    case EVENT_MFR_DRV:     ///< 非接
        transUtil_LED_ReadCardData();
        iRet = EMV_Kernel_Process(EVENT_MFR_DRV, EMV_GetSimpleFlag(), NULL, &KernelRen);
        break;
    case EVENT_MAG_DRV:     ///< 刷卡
        iRet = getMagTrack(&ExtraData.magTrack, &pMagTrack);
        if (SUCCESS == iRet) {
            iRet = EMV_Kernel_Process(EVENT_MAG_DRV, EMV_GetSimpleFlag(), (char *)&pMagTrack, &KernelRen);
        }
        break;
    default:
        break;
    }

    mmi_EventClose(ExtraData.eventType);
    return iRet;
}

