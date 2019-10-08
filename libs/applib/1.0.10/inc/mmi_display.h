/*****************************************************************************
*  QR and P90 Basic tool library                                             *
*  Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mmi_display                                                     *
*  @brief    Display Module API                                              *
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

#ifndef MMI_DISPLAY_H
#define MMI_DISPLAY_H

/**
 * @defgroup display display
 * @brief display related interface
 * @{
 */
 
//=============================================================
//#include "mmi_display.h"
//=============================================================

 /**
 * @defgroup struct struct
 * @brief display related struct
 * @{
 */
 
//---------------------------------------------------------------------------
// enum definition
//---------------------------------------------------------------------------

/**
 * @brief enum definition of display vertical alignment
 */
typedef enum
{
    DISP_Line1      = 1,    /*!< line 1 */
    DISP_Line2      = 2,    /*!< line 2 */
    DISP_Line3      = 3,    /*!< line 3 */
    DISP_Line4      = 4,    /*!< line 4 */
    DISP_Line5      = 5,    /*!< line 5 */
    DISP_Line6      = 6,    /*!< line 6 */
#if defined(QR100)
    DISP_Line7      = 7,    /*!< line 7 */
    DISP_Line8      = 8,    /*!< line 8 */
    DISP_Line9      = 9,    /*!< line 9 */
#endif
    DISP_Top        = 0xE0, /*!< to top */
    DISP_Bottom     = 0xE1, /*!< to buttom */
    DISP_Bottom2    = 0xE2, /*!< to buttom 2 */
    DISP_VCenter    = 0xE3  /*!< to vertical center */
} DISP_VAlign;

/**
 * @brief enum definition of display horizontal alignment
 */
typedef enum
{
    DISP_Left       = 0xE0, /*!< to left */
    DISP_Right      = 0xE1, /*!< to right */
    DISP_HCenter    = 0xE2  /*!< to horizontal center */
} DISP_HAlign;

/** @} */

/**
 * @defgroup struct struct
 * @brief display related struct
 * @{
 */

//---------------------------------------------------------------------------
// struct definition
//---------------------------------------------------------------------------

/**
 * @brief struct definition of display param
 */
typedef struct
{
    unsigned int    alignL;             /*!< horizontal center */

    int             backgroundColor;        /*!< background color */
    int             color;                  /*!< font color */
    int             fontBackgroundColor;    /*!< font background color */
} tsDispParam;

/** @} */

/**
 * @defgroup interface interface
 * @brief display related interface
 * @{
 */
 
//---------------------------------------------------------------------------
// API Interface
//---------------------------------------------------------------------------
/**
 * @brief screen data backup
 */
void mmi_backupScreen(void);

/**
 * @brief restore the screen data
 */
void mmi_freshScreen(void);

/**
 * @brief remove a line
 * @param line [in] DISP_ClearALL and vertical alignment
 */
void mmi_clearLine(unsigned int line);

/**
 * @brief display string
 * @param pDispParam [in] display param
 * @param line [in] vertical alignment
 * @param text [in] display string
 * @retval next line number
 */
int mmi_displayEx(tsDispParam *pDispParam, DISP_VAlign line, const char *text);

/**
 * @brief display string
 * @param [in] line         vertical alignment
 * @param [in] column       horizontal alignment
 * @param [in] pszFmt       display string
 * @retval return next line
 */
int mmi_displayOfBlackBg(DISP_VAlign line, unsigned int column, char *pszFmt, ...);

/**
 * @brief display string
 * @param line [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param pszFmt [in] display string
 * @retval next line number
 */
int mmi_display(DISP_VAlign line, unsigned int column, char *pszFmt, ...);

/**
 * @brief display pixs
 * @param line [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param pPixsBuff [in] pixs buff
 * @param width [in] pixs width
 * @param height [in] pixs height
 * @param color [in] pixs color
 * @retval next line number
 */
int mmi_displayPixs(DISP_VAlign line, unsigned int column,
                    unsigned char *pPixsBuff, unsigned short width, unsigned short height, int color);

/**
 * @brief display qrcode
 * @param line [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param qrcode [in] qrcode string
 * @param width [in] qrcode width
 * @param height [in] qrcode height
 * @retval next line number
 */
int mmi_displayQrCode(DISP_VAlign line, unsigned int column,
                      unsigned char *qrcode, unsigned short width, unsigned short height);

/**
 * @brief display bmp picture
 * @param [in] line         vertical alignment
 * @param [in] column       horizontal alignment
 * @param [in] qrcode       qrcode string
 * @param [in] width        qrcode width
 * @param [in] height       qrcode height
 * @retval return next line
 */
int mmi_displayBMP(DISP_VAlign line, unsigned int column,
                   unsigned char *bmpData, unsigned short width, unsigned short height);

/**
 * @brief display progress bar
 * @param line [in] vertical alignment
 * @param borderColor [in] border color
 * @param backgroundColor [in] background color
 * @param percent [in] percent
 */
void mmi_displayProgressbar(DISP_VAlign line, int borderColor, int backgroundColor, unsigned int percent);

/**
 * @brief timer display start
 * @param line [in] vertical alignment
 * @param column [in] horizontal alignment
 * @param flipEnable [in] enable the countdown (0-disabled, 1-enable)
 * @param timeout [in] timeout
 */
void mmi_displayTimerStart(DISP_VAlign line, unsigned int column, unsigned char flipEnable, int timeout);

/**
 * @brief timer display stop
 */
void mmi_displayTimerStop(void);

/** @} */

/**
 * @defgroup macros macros
 * @brief display related macros
 * @{
 */

//---------------------------------------------------------------------------
// macros definition
//---------------------------------------------------------------------------

/**
 * @brief screen display biggest character
 */
#if defined(QR100)
#define SCREEN_WIDTH (20)
#else
#define SCREEN_WIDTH (26)
#endif

/**
 * @brief clear the screen
 */
#define DISP_ClearALL   255

/** @} */

/** @} */

#endif

