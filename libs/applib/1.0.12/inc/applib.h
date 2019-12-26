/*****************************************************************************
*  QR and P90 Basic applib configuration definition header                   *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     applib.h                                                        *
*  @brief    applib configuration definition                                 *
*  Details.                                                                  *
*                                                                            *
*  @author   XuZhou.Chen                                                     *
*  @version  1.0.0                                                           *
*  @date     25/10/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  25/10/2018 | 1.0.0     | XuZhou.Chen    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef APPLIB_INDEX_H
#define APPLIB_INDEX_H


/**
 * @defgroup applib applib
 * @brief applib config related interface
 * @{
 */

//=============================================================
//#include "applib.h"
//=============================================================

/**
 * @defgroup enum enum
 * @brief applib config related enum
 * @{
 */

/**
* @brief enum definition of battery state
*/
typedef enum
{
    Normal = 0,             ///< normal
    Warning,                ///< notice
    Error,                  ///< charge
    Forbidden               ///< low power

} EN_BATTERY_STATE;

/** @} */

/**
 * @defgroup struct struct
 * @brief applib config related struct
 * @{
 */
 
/**
* @brief struct definition of application attribute
*/
typedef struct
{
    tsDeviceHwInfo deviceHwInfo;
    char *appVersion;                       ///< application version
    int fontColor;                          ///< font color
    int fontbackgroundColor;                ///< background color of font
    int backgroundColor;                    ///< theme background color
    int barbroundColor;                     ///< status bar background color
    char *backgroundImg;                    ///< pointer of background picture

    void (*callback_powerKey)(void *p);     ///< power keypress event
    void (*networkInit)(void);              ///< Custom network initialization
    char notUseSmartpeakMq;                 ///< use smartpeak mq 0:not use 1:use

} tsAppLibParm;

/** @} */

/**
 * @defgroup interface interface
 * @brief applib config related interface
 * @{
 */
 
//--------------------------------
// applib config api
//--------------------------------
/**
 * @brief get applib version
 * @retval char *(applib version string)
 */
char *AppLib_GetVersion(void);

/**
 * @brief check applib version
 * @param ver [in] applib version string pointer
 * @retval int(-1:no, 0:yes)
 */
int AppLib_CheckVersion(const char * ver);

/**
 * @brief initialization applib config parameter
 * @param pParam [in] tsAppLibParm
 * @retval void
 */
void AppLib_InitParam(tsAppLibParm *pParam);

/**
 * @brief set applib config parameter
 * @param setParamFunc [in] set param callback function
 * @retval void
 */
void AppLib_SetParam(void (*setParamFunc)(tsAppLibParm *param));

/**
 * @brief get applib config parameter
 * @retval tsAppLibParm
 */
tsAppLibParm AppLib_GetParam(void);

/**
 * @brief get battery voltage state
 * @retval EN_BATTERY_STATE
 */
EN_BATTERY_STATE AppLib_GetBatteryState(void);

/** @} */

/** @} */

#endif

