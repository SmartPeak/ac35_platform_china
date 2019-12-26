/*****************************************************************************
*  QR and P90 Basic input tool library                                       *
*  Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mmi_input                                                       *
*  @brief    input Module API                                                *
*  Details.                                                                  *
*                                                                            *
*  @author   XuZhou.Chen                                                     *
*  @version  1.0.0                                                           *
*  @date     24/10/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  24/10/2018 | 1.0.0     | XuZhou.Chen    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef MMI_INPUT_H
#define MMI_INPUT_H



/**
 * @defgroup input input
 * @brief input related interface
 * @{
 */

//=============================================================
//#include "mmi_input.h"
//=============================================================

/**
 * @defgroup enum enum
 * @brief input related enum
 * @{
 */
 
/**
 * @brief input method
 */
typedef enum MMI_INPUT_METHOD_
{
    InputMethod_digital     = 1,    /*!< digital input*/
    InputMethod_lower_abc   = 2,    /*!< lowercase input*/
    InputMethod_caps_abc    = 4,    /*!< capital input*/
    InputMethod_hex         = 8     /*!< hex input*/
} InputMethod;

typedef struct
{
    unsigned char   eventType;          /*!< drv event type */
    unsigned int    displayLine;        /*!< display lines */
    unsigned char   displayColumn;      /*!< horizontal alignment*/

    unsigned char   defInputMethod;     /*!< default input method */
    unsigned char   inputMethodGroup;   /*!< input method group */
    unsigned int    waitTimeout;        /*!< wait timeout */

    //format string
    unsigned char   formatChar;

    unsigned char   openScan;           /*!< open scan */
    unsigned char   isShowScanData;     /*!< is show scan data (true/false) */
    int (*checkScanData)(unsigned int displayLine, unsigned char *pScanData, unsigned int dataLen, unsigned int scanDataSize);
    unsigned int    scanDataLen;        /*!< out scan data len */
    unsigned char   funKeyType;         /*!< 1.funckey call 2.scan */
    int (*funcKey)(void);               /*!< funcKey callback */
    int (*menuKey)(void);               /*!< menukey callback */

}tsInputMethodParam;

typedef struct
{
    unsigned char integerUnit;           /*!< 0 dots, 1 not dots */               
    unsigned char *currencySymbol;       /*!<  currency symbol */   
    unsigned long *amount;               /*!< amount */   
    int fontColor;                       /*!< amount font color */     
    int (*enterKey)(void);               /*!< enterKey callback */
    int (*funcKey)(void);                /*!< funcKey callback */   
    int (*menuKey)(void);                /*!< menuKey callback */
}tsInputAmtParam;

/** @} */

/**
 * @defgroup interface interface
 * @brief input related interface
 * @{
 */
 
//-------------------------------------------------
// input api
//-------------------------------------------------

/**
* @brief get keypress value
* @retval  keypress value
*/
int mmi_inputGetKeypress(void);

/**
* @brief wait keypress, blocking mode
* @retval  > 0 : keypress value
* @retval  <=0 : timeout
*/
int mmi_inputWaitKeypress(unsigned int timeout);

/**
 * @brief input digital
 * @param dispLine [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param pBuff [out] buff address
 * @param buffSize [in] buff sizeof
 * @param minValue [in] minimum value
 * @param maxValue [in] maximum value
 * @param timeout [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_inputDigital(unsigned int dispLine, unsigned int column, unsigned char *pBuff, int buffSize, unsigned long minValue, unsigned long maxValue, unsigned int timeout);

/**
 * @brief input string
 * @param pBuff [in] buff address
 * @param minLen [in] minimum len
 * @param maxLen [in] maximum len
 * @param pucMask [in] Mask
 * @param pParam [in/out] param
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_inputStringEx(unsigned char *pBuff, int minLen, int maxLen, char *pucMask, tsInputMethodParam *pParam);

#define mmi_setInputType(defType, inputType)        (defType<<8|inputType)

/**
 * @brief input string
 * @param dispLine [in] vertical alignment
 * @param inputType [in] input methoed
 * @param pBuff [in] buff address
 * @param minLen [in] minimum len
 * @param maxLen [in] maximum len
 * @param pucMask [in] Mask
 * @param timeout [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_inputString(unsigned int dispLine, unsigned int inputType, unsigned char *pBuff, int minLen, int maxLen, char *pucMask, unsigned int timeout);

/**
 * @brief input password
 * @param dispLine [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param inputType [in] input methoed
 * @param pwdData [in] buff address
 * @param minLen [in] minimum len
 * @param maxLen [in] maximum len
 * @param timeout [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
*/
int mmi_InputPasswd(unsigned int dispLine, unsigned int column, unsigned int inputType, unsigned char *pwdData, unsigned int minLen, unsigned int maxLen, unsigned int timeout);

/**
 * @brief input amount
 * @param dispLine [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param minAmount [in] minimum amount
 * @param maxAmount [in] maximum amount
 * @param timeout [in] timeout
 * @param pInputAmtParam [in/out] param
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_InputAmountEx(unsigned int dispLine, int column, int minAmount, int maxAmount, int timeout, tsInputAmtParam *pInputAmtParam);

/**
 * @brief input amount
 * @param dispLine [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param inputType [in] 0 dots, 1 not dots
 * @param pAmount [in] buff amount
 * @param minAmount [in] minimum amount
 * @param maxAmount [in] maximum amount
 * @param timeout [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_InputAmount(unsigned int dispLine, int column, unsigned char inputType, unsigned long *pAmount, int minAmount, int maxAmount, unsigned int timeout);

/**
 * @brief input IP
 * @param line [in] vertical alignment
 * @param pucBuf [in] buff address
 * @param timeOut [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_InputIPV4Addr(unsigned int DispLine, unsigned char *pucBuf, int timeOut);

/**
 * @brief  input event type
 */
//(1<<0)
#define EVENT_NULL          0
#define EVENT_KEY_DRV       1
#define EVENT_MAG_DRV       2
#define EVENT_ICC_DRV       4
#define EVENT_MFR_DRV       8
#define EVENT_SCAN_DRV      16
#define EVENT_MANUAL_DRV    32

/**
 * @brief event open
 * @param event [in]
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_EventOpen(unsigned int event);

/**
 * @brief event close
 * @param event [in]
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_EventClose(unsigned int event);

/**
 * @brief event wait
 * @param pEvent [in/out]
 * @param pDrvData [out]
 * @param pDrvDataLen [out]
 * @param timeout [in] timeout
 * @retval  SUCCESS  success
 * @retval  other    failure
 */
int mmi_EventWait(unsigned int *pEvent, unsigned char *pDrvData, unsigned int *pDrvDataLen, unsigned int timeout);

/** @} */

/** @} */

#endif

