/*****************************************************************************
*  QR and P90 Basic esignature api library header                         *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mmi_esignature.h                                                     *
*  @brief    electronic signature Module API                                *
*  Details.                                                                  *
*                                                                            *
*  @author   BoBo.Li                                                   *
*  @version  1.0.0                                                           *
*  @date     24/05/2019                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  24/05/2019 | 1.0.0     | BoBo.Li | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef _MMI_COMMU_H
#define _MMI_COMMU_H
#include "applib_def.h"

#ifdef __cplusplus
extern   "C"
{
#endif

/*电子签名返回*/
typedef enum
{
	ESIGN_OK		=  0,		/*签名正常*/
	ESIGN_FAIL		= -1,		/*签名故障*/
	ESIGN_FILEFAIL  = -2,		/*文件操作失败*/
	ESIGN_CANCEL	= -3,		/*签名取消*/
	ESIGN_TIMEOUT	= -4,		/*签名超时*/
	ESIGN_NOMEMORY	= -5
}enumEsignRet;

/**
 * @brief Inner condition code
 * @param code [in] condition code
 * @param iCodeLen [in] condition code len
 * @param timeout [in] timeout
 * @retval  ESIGN_OK  success
 * @retval  other    failure
 */
int mmi_eSign_InnerSign(unsigned char *pCode, unsigned int iCodeLen, int timeout);

/**
 * @brief Compress Image
 * @param pDstFileName [in] file name
 * @param pOutData [out] Compress data
 * @param pOutLen [in] Compress data len
 * @retval  ESIGN_OK  success
 * @retval  other    failure
 */
int mmi_eSign_CompressImage(const char *pDstFileName,unsigned char* pOutData,unsigned int* pOutLen);

/**
 * @brief Compress data
 * @param pOutData [out] Compress data
 * @param pOutLen [in] Compress data len
 * @retval  ESIGN_OK  success
 * @retval  other    failure
 */
int mmi_eSign_CompressData(unsigned char* pOutData,unsigned int* pOutLen);


/**
 * @brief unCompress Image
 * @param pSrcFileName [in] file name
 * @param pOutBuff [out] unCompress data
 * @param pOutLen [out] unCompress data len
 * @retval  ESIGN_OK  success
 * @retval  other    failure
 */
int mmi_eSign_UnCompressImage(const char *pSrcFileName,unsigned char*pOutBuff,unsigned int* pOutLen);


/**
 * @brief unCompress data 
 * @param pInData [in] unCompress data
 * @param uiInLen [in] unCompress data len
 * @param pOutBuff [out] unCompress out data 
 * @param pOutLen [out] unCompress out len
 * @retval  ESIGN_OK  success
 * @retval  other    failure
 */
int mmi_eSign_UnCompressData(unsigned char *pInData,unsigned int uiInLen,unsigned char*pOutBuff,unsigned int* pOutLen);

#ifdef __cplusplus
}
#endif

#endif

