/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     elecsign.c                                                      *
*  @brief    electronic signature function                                   *
*  Details.                                                                  *
*                                                                            *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "bwsdk_api.h"
#include "applib_tools.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "mmi_printer.h"
#include "mmi_esignature.h"
#include "uFile.h"

#include "elecsign.h"
#include "iso8583_config.h"
#include "trans.h"

#define DEBUG_ELECSIGN  0
#if DEBUG_ELECSIGN
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "elecsign.c"
#endif

///< ----------------------------------
int transOnline_SendRev(void);
int transOnline_CommonPack(void);
int transOnline_CommonUPack(bool bManage);
int transOnline_Bit60_pack(const char *pTransType, const char *pNetInforCode, unsigned char ucTransType);
///< ----------------------------------

extern void mdm_mq_set_idle_state(int idle);
extern void msg_displayErr(int _ret);
extern int transUtil_UpdateTrans(unsigned int index);
extern unsigned char GetNoPinNoSignData(char *plSignData, tsTransData *pTransData);
extern int TlvAppend(unsigned long Tag, unsigned char *srcData, int srcOffset, unsigned char *dstData, int dstOffset, int srcLen);

/**
 * @brief get compressed esign data into file
 */
int esign_GetCompressedFile(int index)
{
    int iRet = ERR_END;
    unsigned char esignData[1024] = {0};
    unsigned int uiEsignDataLen = 0;
    unsigned int uiEsignOffset = 0;

    ///< clear esign file
    UFile_ClearFile(ESIGN_JPG);

    if (index >= MAX_TRANS_NUM) {
        return ERR_PARAM;
    }

    ///< esign data offset in the file
    uiEsignOffset = DataTransDetail.uiEsDataOffsetTab[index];
    ///< esign data length
    uiEsignDataLen = DataTransDetail.uiEsDataLenTab[index];
#if DEBUG_ELECSIGN
    LOGD("[%s,%d]offset=%d,len=%d\r\n", __FUNCTION__, __LINE__, uiEsignOffset, uiEsignDataLen);
#endif
    ///< check the file
    if ((uiEsignDataLen > 0) && (uiEsignDataLen <= 900)) {
        ///< read esign data
        iRet = UFile_ReadFileEx(FILE_Esign, uiEsignOffset, esignData, uiEsignDataLen);
        if (SUCCESS == iRet) {
            ///< create esign data file for printing
            iRet = UFile_WriteFile(ESIGN_JPG, esignData, uiEsignDataLen);
        }
    }
    return iRet;
}

/**
 * @brief add elecsign print bmp data
 */
int esign_AddPrintBmp(void)
{
    int iRet = ERR_PARAM;
    char *pEsignData = NULL;
    int esignDataLen = 0;
    ts_printer_para stPrinterPara;

    ///< ---------------------------
    memset(&stPrinterPara, 0, sizeof(ts_printer_para));
    iRet = printer_get_para(&stPrinterPara);
    if (PRINTER_RET_OK != iRet) {
        return ERR_PARAM;
    }

    stPrinterPara.fontSize = PRINT_FONT_LARGE;
    stPrinterPara.printAlign = ALIGN_CENTER;
    stPrinterPara.lineSpace = 8;
    ///< ---------------------------

    pEsignData = malloc(ESIGN_BUFF_LEN);
    if (NULL != pEsignData) {
        iRet = SUCCESS;
        memset(pEsignData, 0, ESIGN_BUFF_LEN);
    }

    ///< uncompress esign data get image file
    if (SUCCESS == iRet) {
        iRet = mmi_eSign_UnCompressImage(ESIGN_JPG, (unsigned char *)pEsignData, (unsigned int *)&esignDataLen);
#if DEBUG_ELECSIGN
        LOGD("[%s,%d]uncompress image = %d\r\n", __FUNCTION__, __LINE__, iRet);
#endif
    }
#if DEBUG_ELECSIGN
    LOGD("[%s,%d]UnCompress esign data = %d\r\n", __FUNCTION__, __LINE__, iRet);
#endif

    if (SUCCESS == iRet) {
        iRet = ERR_END;
        if (esignDataLen > 0) {
            iRet = printer_add_bmp_with_param(&stPrinterPara, pEsignData, esignDataLen, 0);
#if DEBUG_ELECSIGN
            LOGD("add elecsign print bmp data = %d\r\n", iRet);
#endif
        }
    }

    if (NULL != pEsignData) {
        free(pEsignData);
        pEsignData = NULL;
    }
    return iRet;
}

/**
 * @brief calc esign trans code
 */
int esign_CalcTransCode(unsigned char *plIn, unsigned char *plOut)
{
    int index = 0;
    unsigned char bcdBuf1[5] = {0};
    unsigned char bcdBuf2[5] = {0};
    unsigned char bcdBuf[5] = {0};

    ///< check param in
    if ((NULL == plIn) ||  (NULL == plOut)) {
        return ERR_PARAM;
    }

    vTwoOne(&plIn[0], 8, bcdBuf1);
    vTwoOne(&plIn[8], 8, bcdBuf2);
    for (; index < 4; index++) {
        bcdBuf[index] = bcdBuf1[index] ^ bcdBuf2[index];
    }

    vOneTwo(bcdBuf, 4, plOut);
#if DEBUG_ELECSIGN
    LOGD("[%s,%d]trans Code = %s\r\n", __FUNCTION__, __LINE__, plOut);
#endif

    return SUCCESS;
}

/**
 * @brief get elecsign
 */
int esign_GetEsign(unsigned char *pTransCode, unsigned int codeLen)
{
    int iRet = 0;
    unsigned char *pEsignData = NULL;
    unsigned int esignDataLen = 0;
    unsigned char resignCount = 0;

    for (; resignCount < DataEsign.ucEsReSignMaxTimes; resignCount++) {
        ///< show signature notice
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line1, DISP_Left, AMSG_EsignInputSign);

        DataTransDetail.uiEsDataOffsetTab[DataTransDetail.lastTransIndex] = 0;
        DataTransDetail.uiEsDataLenTab[DataTransDetail.lastTransIndex] = 0;
        ///< remove compressed esign file before resign
        UFile_ClearFile(ESIGN_JPG);

#if DEBUG_ELECSIGN
        LOGD("esign code, len, timeout = %s,%d,%d\r\n", pTransCode, codeLen, DataEsign.usEsSignTimeOut);
#endif
        iRet = mmi_eSign_InnerSign(pTransCode, codeLen, DataEsign.usEsSignTimeOut);
        ///< esign success or continue the normal step
        if (SUCCESS == iRet) {

            ///< check & get memory
            if (NULL == pEsignData) {
                pEsignData = malloc(ESIGN_JPG_BUFF_LEN);
            }

            if (NULL != pEsignData) {
                /*!< --- Data overflow after compression --- >!*/
                memset(pEsignData, 0, ESIGN_JPG_BUFF_LEN);
                iRet = mmi_eSign_CompressImage(ESIGN_JPG, pEsignData, &esignDataLen);
            }
            else {
                iRet = ERR_END;
            }
        }
#if DEBUG_ELECSIGN
        LOGD("[%s,%d]ret = %d, len = %d\r\n", __FUNCTION__, __LINE__, iRet, esignDataLen);
#endif
        ///< check length
        if ((SUCCESS == iRet) && ((esignDataLen < MIN_ESIGN_LEN) || (esignDataLen > 900))) {
            iRet = ERR_NEED_RESIGN;
            msg_displayErr(iRet);
        }

        if (ERR_NEED_RESIGN != iRet) {
            break;
        }

        iRet = ERR_END;
    }

    ///< fail -> clear jpg
    if (SUCCESS != iRet) {
        UFile_ClearFile(ESIGN_JPG);
    }

    ///< save esign data into file
    if (SUCCESS == iRet) {
        iRet = UFile_WriteFileEx(FILE_Esign, DataTransDetail.lastOffsetEnd, pEsignData, esignDataLen);
    }

    ///< update the detail file
    if (SUCCESS == iRet) {
        DataTransDetail.uiEsDataOffsetTab[DataTransDetail.lastTransIndex] = DataTransDetail.lastOffsetEnd;
        DataTransDetail.uiEsDataLenTab[DataTransDetail.lastTransIndex] += esignDataLen;
        DataTransDetail.lastOffsetEnd += esignDataLen;
        DataTransDetail.esignCount++;
        ///< save the esign info
        iRet = UFile_WriteFileIndexOf(DB_TransDetail);
    }

    if (NULL != pEsignData) {
        free(pEsignData);
        pEsignData = NULL;
    }

    return iRet;
}

/**
 * @brief signature processing
 */
int esign_Processing(void)
{
    int iRet;
    unsigned char tmpTransCode[17] = {0};
    unsigned char transCode[9] = {0};

    if (!DataEsign.bisSupportEs) {
        return ERR_END;
    }
    else if (DataTransDetail.esignCount >= DataEsign.usEsMaxTradeNum) {
        return ERR_END;
    }
    else if (1 != GetNoPinNoSignData(NULL, &DataTrans)) {
        return ERR_END;
    }

    ///< calc trans code
    memset(tmpTransCode, '0', 16);
    memcpy(&tmpTransCode[0], DataTrans.settleDate, 4);
    memcpy(&tmpTransCode[4], DataTrans.refNumber, 12);
    iRet = esign_CalcTransCode(tmpTransCode, transCode);

    ///< sign
    if (SUCCESS == iRet) {
        iRet = esign_GetEsign(transCode, 8);
    }

    if (SUCCESS == iRet && DataEsign.bisEsPrintVoucher && DataConstant.ucPrintTimes > 0) {
        iRet = PrintVoucherSheet(&DataTrans, 0, 0);

        ///< update print flag while print success
        if (SUCCESS == iRet) {
            transUtil_UpdatePrintState(1, DataTransDetail.lastTransIndex);
        }
    }
    else if (SUCCESS != iRet) {
        UFile_ClearFile(ESIGN_JPG);
        return ERR_END;
    }
    return SUCCESS;
}

