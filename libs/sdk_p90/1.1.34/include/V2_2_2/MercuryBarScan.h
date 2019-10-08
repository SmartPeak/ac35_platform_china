/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_BAR_SCAN_H_
#define _MERCURY_BAR_SCAN_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NONE        =      0,  /**< no symbol */
    PARTIAL     =      1,  /**< intermediate status */
    EAN8        =      8,  /**< EAN-8 */
    UPCE        =      9,  /**< UPC-E */
    ISBN10      =     10,  /**< ISBN-10 (from EAN-13)*/
    UPCA        =     12,  /**< UPC-A */
    EAN13       =     13,  /**< EAN-13 */
    ISBN13      =     14,  /**< ISBN-13 (from EAN-13).  */
    I25         =     25,  /**< Interleaved 2 of 5*/
    CODE39      =     39,  /**< Code 39.  */
    PDF417      =     57,  /**< PDF417.  */
    QRCODE      =     64,  /**< QR Code.  */
    CODE128     =    128,  /**< Code 128 */
    SYMBOL      =    0x00ff,  /**< mask for base symbol type */
    MERCURY_ENUM_SYMBOL_MAX = 0x7fffffff
} SYMBOL_TYPE_T;




typedef enum
{
  DCAMERA_OP_SUCCESS = 0,
  DCAMERA_OP_ERROR,
  DCAMERA_OP_PARAM_ERR,
  DCAMERA_OP_NO_SENSOR_ERR,
  DCAMERA_OP_SENSOR_NOT_WORK_ERR,
  DCAMERA_OP_PREVIEW_ERR,
  DCAMERA_OP_IOCTL_ERR,
  DCAMERA_OP_SCAN_ERR,
  DCAMERA_OP_GET_SCAN_DATA_ERR,
  DCAMERA_OP_NO_ENOUGH_MEMORY,
  DCAMERA_OP_REVIEW_ERR,
  DCAMERA_OP_ISP_ERR,
  
  DCAMERA_OP_MAX = 0xFF,
  MERCURY_ENUM_DCAMERA_MAX = 0x7fffffff
}DCAMERA_RETURN_VALUE_E;

typedef struct{
    SYMBOL_TYPE_T   symbol_type;   
    int            dataLen;
    unsigned char   data[1];
} SYMBOL_RESULT_T;

typedef struct {
    int width;
    int height;
    int rowSize;
    unsigned char* bits;
} QR_ENC_CODE_T;

typedef enum
{
    BARSCAN_MODE_CONTINUE = 0,
    BARSCAN_MODE_ONCE = 1,
    BARSCAN_MODE_MOTIONDETECT = 2,
    BARSCAN_MODE_ONED_ONLY = 3,
    BARSCAN_MODE_MOTIONDETECT_MINI = 4,
    BARSCAN_MODE_MAX,
    MERCURY_ENUM_BARSCAN_MODE_MAX = 0x7fffffff
}BARSCAN_MODE_VALUE_E;

typedef enum
{
    BARSCAN_FEATURE_ALL = 0,
    BARSCAN_FEATURE_PAY,
    BARSCAN_FEATURE_BOX_PAY,
    BARSCAN_FEATURE_MAX,
    MERCURY_ENUM_FEATURE_MAX = 0x7fffffff
}BARSCAN_FEATURE_CONFIGURE_E;

typedef struct sensor_reg_tag
{
    unsigned short reg_addr;                        // address of sensor register
    unsigned short reg_value;                       // value of sensor register
}SENSOR_REG_T, *SENSOR_REG_T_PTR;

/**
 * Level of error correction.
 */
typedef enum {
    QR_ECLEVEL_L = 0, ///< lowest
    QR_ECLEVEL_M,
    QR_ECLEVEL_Q,
    QR_ECLEVEL_H,      ///< highest
    QR_ECLEVEL_MAX = 0x7fffffff
} QRecLevel;


DCAMERA_RETURN_VALUE_E Cam_Init(void);  
DCAMERA_RETURN_VALUE_E Cam_DeInit(void);
DCAMERA_RETURN_VALUE_E Cam_StartScan(BARSCAN_MODE_VALUE_E mode) ;
DCAMERA_RETURN_VALUE_E Cam_AbortScan(void);
DCAMERA_RETURN_VALUE_E Cam_Suspend(void);
DCAMERA_RETURN_VALUE_E Cam_Resume(void);
DCAMERA_RETURN_VALUE_E Cam_Suspend_LP(void);
DCAMERA_RETURN_VALUE_E Cam_Resume_LP(void);
DCAMERA_RETURN_VALUE_E Cam_FeatureConfig(BARSCAN_FEATURE_CONFIGURE_E feature2Config);
DCAMERA_RETURN_VALUE_E Cam_InitWithPara(SENSOR_REG_T_PTR pPara, int numCount, unsigned short sensorID );

QR_ENC_CODE_T* Cam_QR_Enc(int lenth, const unsigned char* data);
int Cam_QR_SetEncLEVEL(QRecLevel level);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
