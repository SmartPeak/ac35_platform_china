#ifndef _ELECSIGN_H
#define _ELECSIGN_H

/*****************************************************************************
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  @file     elecsign.h                                                      *
*  @brief    electronic signature header                                     *
*  Details.                                                                  *
*                                                                            *
*****************************************************************************/

#define ESIGN_JPG               "esign.jpg"
#define MIN_ESIGN_LEN           150
#define ESIGN_BUFF_LEN          (1024*5)
#define ESIGN_JPG_BUFF_LEN      (2500)


/**
 * @brief get compressed esign data into file
 */
int esign_GetCompressedFile(int index);

/**
 * @brief add elecsign print bmp data
 */
int esign_AddPrintBmp(void);

/**
 * @brief calc esign trans code
 */
int esign_CalcTransCode(unsigned char *plIn, unsigned char *plOut);

/**
 * @brief get elecsign
 */
int esign_GetEsign(unsigned char *pTransCode, unsigned int codeLen);

/**
 * @brief signature processing
 */
int esign_Processing(void);

#endif

