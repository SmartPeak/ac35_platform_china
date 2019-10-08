/*****************************************************************************
*  QR and P90 Basic error code definition header                             *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     applib_err.h                                                    *
*  @brief    error code definition                                           *
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

#ifndef APPLIB_ERR_H
#define APPLIB_ERR_H

/**
 * @brief system and applib error index
 */
#define SUCCESS         (0)         /*!< succeed*/

typedef enum SYS_ERR_INDEX_
{
    ERR_END             = -1,       /*!< end */
    ERR_CANCEL          = -2,       /*!< cancel */
    ERR_TIMEOUT         = -3,       /*!< timeout */
    ERR_PARAM           = -4,       /*!< param error */
    ERR_DRV             = -5,       /*!< driver error*/
    ERR_MIF_DRV         = -6,       /*!< open picc device fail */
    ERR_ICC_DRV         = -7,       /*!< open icc device fail */
    ERR_SCAN_DRV        = -8,       /*!< open scan device fail */
    ERR_MAG_DRV         = -9,       /*!< open mag device fail */
    ERR_FILE            = -10       /*!< file operation fail */
} SysErrIndex;

/** @} */

#endif

