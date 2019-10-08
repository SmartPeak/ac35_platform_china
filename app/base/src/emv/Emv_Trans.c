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

/*�Ӵ��ں˼쿨*/
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

/*��ʼ���ں˻ص�*/
char EMV_Trans_InitEntryKernel(void){

    memset((LP_EMV_BYTE)&_CALLBACK_KERNEL, 0, sizeof(_CALLBACK_KERNEL));

    ///< �ں���־��ӡ
    _CALLBACK_KERNEL.m_Log_Print = Kernel_Log_Printf;
    ///< ��ȡ�ն�ʱ��
    _CALLBACK_KERNEL.m_GetCurrentTime = Kernel_GetCurrentTime;
    ///< ��ȡ�����
    _CALLBACK_KERNEL.m_GenerateRandomData = Kernel_GetRandomData;
    ///< APDU ͨѶ
    _CALLBACK_KERNEL.m_ExchangeApdu = Kernel_ExchangeApdu;
    ///< SM2����
    _CALLBACK_KERNEL.m_ContactSM2VerifySign = Kernel_SM2VerifySign;
    ///< SM3��ϣ����
    _CALLBACK_KERNEL.m_ContactSM3Hash = Kernel_SM3Hash;

    ///< ��������(�Ӵ�,�ǽ�VISA,QPBOC,AMEX,D-PAS)
    _CALLBACK_KERNEL.m_FinacialTransactionRequest = Kernel_FinacialTransactionRequest;

    ///< ���׽�� Mastrt,MIR ����,�ѻ����� ���շ���ֵ����
    _CALLBACK_KERNEL.m_Display_Trans_Report = Kernel_Display_Trans_Report;

    //�ǽ�
    _CALLBACK_KERNEL.m_DetectBreak = Kernel_CL_DetectBreak_Callback;
    ///< ����PIN
    _CALLBACK_KERNEL.m_GetOnlinePin = Kernel_CL_GetOnlinePin;
    ///< �ƿ�
    _CALLBACK_KERNEL.m_AskRemoveCard = Kernel_CL_AskRemoveCard;
    ///< �����Ŀ�
    _CALLBACK_KERNEL.m_SecondTapCard = Kernel_CL_SecondTapCard;
    ///< ָʾ��ǰ��ic��picc�����
    _CALLBACK_KERNEL.m_KernelMode = Kernel_CL_KernelMode;

    //�Ӵ�
    ///< �������
    _CALLBACK_KERNEL.m_EnterAmount = Kernel_EnterAmount;
    ///< Ӧ��ѡ��
    _CALLBACK_KERNEL.m_SelectApplication = Kernel_CT_SelectApplication;
    ///< �ֿ���֤����֤
    _CALLBACK_KERNEL.m_ContactGetHolderCert = Kernel_Contact_GetHolderCert;
    ///< �ѻ�����pin
    _CALLBACK_KERNEL.m_ContactGetPlainTextPin = Kernel_Contact_GetPlainTextPin;
    ///< ��������pin
    _CALLBACK_KERNEL.m_ContactGetOnlinePin = Kernel_Contact_GetOnlinePin;
    ///< �ѻ�����pin
    _CALLBACK_KERNEL.m_ContactGetOffCipherPin = Kernel_Contact_GetOfflineCipherPin;
    ///< �����ο�(����)
    _CALLBACK_KERNEL.m_ContactPanConfirm = Kernel_Contact_PanConfirm;
    ///< ��Ӧ��ѡ��,ѡ�����,������ʾ
    _CALLBACK_KERNEL.m_ContactSelAppErr = Kernel_Contact_SelAppErr;
    ///< ��������������
    _CALLBACK_KERNEL.m_MagStripeOnlineRequeset = Kernel_MagStripe_OnlineRequeset;
    ///< �Ӵ��ں˼쿨
    _CALLBACK_KERNEL.m_ContactDetectCard = Kernel_Contact_DetectCard;
    ///< �Ӵ���ʾ����
    _CALLBACK_KERNEL.m_ContactShowPanNo = Kernel_CT_Display_PanNo;

    //��֤(ƽ���ò���)
    ///< ������
    _CALLBACK_KERNEL.m_BatchDataCapture = NULL;
    ///< ����
    _CALLBACK_KERNEL.m_Reversal = NULL;
    ///< ֪ͨ
    _CALLBACK_KERNEL.m_OnlineAdvice = NULL;
    ///< ȷ��
    _CALLBACK_KERNEL.m_FinancialTransConfirm = NULL;
    ///< �ѻ���׼
    _CALLBACK_KERNEL.m_AuthorisationRequest = NULL;

    //��ʱδ����.
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

/*�Ӵ��ں˼쿨*/
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

    ///< �����¼�
    switch(_TRANS_HANDLE.drvMode)
    {
    case DEVMAG:
        uiEvent = EVENT_MAG_DRV;
        ///< �Ǵ�IC��оƬ�Ĵ�����
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
                strcat(dispMsg, "�ӿ�");
            }
            if ((uiEvent&EVENT_ICC_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "��");
                }
                strcat(dispMsg, "�忨");
            }
            if ((uiEvent&EVENT_MAG_DRV)) {
                if (strlen(dispMsg)) {
                    strcat(dispMsg, "��");
                }
                strcat(dispMsg, "ˢ��");
            }

            mmi_clearLine(DISP_ClearALL);
            mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
            if (ulAmount > 0)
            {
                mmi_display(DISP_Line3, DISP_HCenter, "%d.%02d", ulAmount / 100, ulAmount % 100);
            }
            mmi_display(DISP_Line4, DISP_HCenter, "��%s", dispMsg);
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
    case EVENT_ICC_DRV:     //�忨
        mmi_clearLine(DISP_ClearALL);
        mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, trans_GetTransName(ExtraData.transType));
        mmi_display(DISP_Line2, DISP_HCenter, "����ο�");
        mmi_display(DISP_Line3, 0, "������");
        mmi_display(DISP_Line4, 0, "���Ե�...");

        _TRANS_HANDLE.drvMode = DEVICC;
        DataTrans.cardInputType = InputMode_ICC;
        KernelRen = Contact_Start_Kernel(traceNumber, EMV_Get_TransType(), uiAmount, 0, bEMVSimpleFlag, (MAG_TRACK_DATA *)drvData);
        break;
    case EVENT_MFR_DRV:     //�ǽ�
        _TRANS_HANDLE.drvMode = DEVPICC;
        DataTrans.cardInputType = InputMode_QICC;
        Contactless_Set_Kernel_Version(CL_Get_Kernel_Version());
        Contactless_Set_KernelApplyAid(EMV_TRUE);   ///< ��AID��
        KernelRen = Contactless_Start_Kernel(traceNumber, EMV_Get_TransType(), uiAmount, 0);
        break;
    case EVENT_MAG_DRV:     //����
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
    EMV_Trans_InitEntryKernel();    //��ʼ���ص�
    CT_Start_Trans_InitParam();
    switch (ExtraData.eventType)
    {
    case EVENT_ICC_DRV:     ///< �Ӵ�
        iRet = EMV_Kernel_Process(EVENT_ICC_DRV, EMV_GetSimpleFlag(), (char *)&pMagTrack, &KernelRen);
        break;
    case EVENT_MFR_DRV:     ///< �ǽ�
        transUtil_LED_ReadCardData();
        iRet = EMV_Kernel_Process(EVENT_MFR_DRV, EMV_GetSimpleFlag(), NULL, &KernelRen);
        break;
    case EVENT_MAG_DRV:     ///< ˢ��
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

