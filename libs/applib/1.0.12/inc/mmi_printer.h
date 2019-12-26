/*****************************************************************************
*  QR and P90 Basic printer api library header                               *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mmi_printer.h                                                   *
*  @brief    Printer Module API                                              *
*  Details.                                                                  *
*                                                                            *
*  @author   ChengYang.Geng                                                  *
*  @version  1.0.0                                                           *
*  @date     27/11/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  27/11/2018 | 1.0.0     | ChengYang.Geng | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef _MMI_PRINTER_H
#define _MMI_PRINTER_H


#ifdef __cplusplus
extern   "C"
{
#endif

#ifdef ENABLE_PRINTER_LOG
#undef ENABLE_PRINTER_LOG
#endif
#define ENABLE_PRINTER_LOG

/**
 * @defgroup printer printer
 * @brief printer related interface 
 * @{
 */


/**
 * @defgroup enum enum
 * @brief printer related enum 
 * @{
 */

/**
 * @brief enum definition of print font size
 */
typedef enum
{
    PRINT_FONT_SMALL     = 16,
    PRINT_FONT_NORMAL    = 24,
    PRINT_FONT_LARGE     = 32
    
} te_printer_fontsize;

/**
 * @brief enum definition of print effect
 */
typedef enum
{
    EFFECT_NONE,
    EFFECT_BOLD
    
} te_printer_effect;

/**
 * @brief enum definition of print align mode
 */
typedef enum 
{
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
    
} te_printer_align;

/**
 * @brief enum definition of print heat point
 * @note larger value, print faster
 */
typedef enum 
{
    HEAT_POINT_MIN = 32,
    HEAT_POINT_48  = 48,
    HEAT_POINT_64  = 64,
    HEAT_POINT_MAX = 96     ///<recommended
    
} te_printer_heat_point;

/** @} */

/**
 * @defgroup struct struct
 * @brief printer related struct 
 * @{
 */

/**
 * @brief struct definition of printer parameter
 */
typedef struct
{
    te_printer_fontsize fontSize;           ///<print font size
    te_printer_effect fontEffect; 	        ///<print effect
    int lineSpace; 		                    ///<print line spacing (>= 0)
    te_printer_align printAlign; 	        ///<print align mode
    int printGray; 		                    ///<print gray level(heat time.Value range:1800-5000)
    te_printer_heat_point printHeatpoint;   ///<print heat point
    int printStep; 		                    ///<print step delay time(Value range:600-1200)
    
} ts_printer_para;

/**
 * brief enum definition of barcode type
 */
typedef enum 
{
	BARCODE_TYPE_ANY,       ///< self-adaption
	BARCODE_TYPE_CODE128,   ///< recommended
	BARCODE_TYPE_CODE39,
	BARCODE_TYPE_CODE93,
	BARCODE_TYPE_CODE11,
	BARCODE_TYPE_MSI,
	BARCODE_TYPE_I25,
	BARCODE_TYPE_EAN8,
	BARCODE_TYPE_EAN13,
	BARCODE_TYPE_UPCA,
	BARCODE_TYPE_UPCE,
	BARCODE_TYPE_CODABAR,
	
} ts_barcode_type;

/** @} */

/**
 * @defgroup interface interface
 * @brief printer related interface 
 * @{
 */
 
//----------------------------------------------
// printer interface
//----------------------------------------------

/**
 * @brief  check printer state
 * @retval =0 : success
 * @retval !0 : fail
 */
int printer_check(void);

/**
 * @brief  open and init printer
 * @retval =0 : success
 * @retval !0 : fail
 */
int printer_open(void);

/**
 * @brief set printer parameter
 * @param p_printer_para [in] pointer of ts_printer_para struct for setting value
 * @retval =0 : success
 * @retval !0 : fail
 * @pre none
 */
int printer_set_para(ts_printer_para *p_printer_para);

/**
 * @brief get printer parameter
 * @param p_printer_para [out] pointer of ts_printer_para struct for getting value
 * @retval =0 : success
 * @retval !0 : fail
 * @pre none
 */
int printer_get_para(ts_printer_para *p_printer_para);

/**
 * @brief printer feed paper
 * @param point_lines [in] >0:forward <0:rollback
 * @retval =0 : success
 * @retval !0 : fail
 * @pre none
 */
int printer_feed(int point_lines);

/**
 * @brief add text data to printer cache
 * @param text [in] text to be printed
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_text(const char *text);

/**
 * @brief add bmp data to printer cache
 * @param bmp_data [in] bmp data to be printed
 * @param bmp_data_len [in] bmp data length
 * @param need_reverse [in] int need_reverse
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_bmp(const char *bmp_data, int bmp_data_len, int need_reverse);

/**
 * @brief add text data to printer cache
 * @param bmp_path [in] bmp file path to be printed
 * @param need_reverse [in] int need_reverse
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_bmp_path(const char *bmp_path, int need_reverse);

/**
 * @brief  add barcode data to printer cache \n
 * the text will be transfered to barcode
 * @param [in] ts_barcode_type barcode_type
 * @param [in] int code_width
 * @param [in] int code_height
 * @param [in] const char* barcode_text
 * @retval 0 : success
 * @retval !0: fail
 */
int printer_add_barcode(ts_barcode_type barcode_type, int code_width, int code_height, const char *barcode_text);

/**
 * @brief  add qrcode data to printer cache \n
 * the text will be transfered to qrcode
 * @param [in] int code_size
 * @param [in] const char* qrcode_text
 * @retval 0 : success
 * @retval !0: fail
 */
int printer_add_qrcode(int code_size, const char *qrcode_text);


/**
 * @brief add text data to printer cache with param
 * @param p_printer_para [in] pointer of ts_printer_para struct for setting value
 * @param text [in] text to be printed
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_text_with_param(const ts_printer_para *p_printer_para, const char *text);

/**
 * @brief add bmp data to printer cache with param
 * @param p_printer_para [in] pointer of ts_printer_para struct for setting value
 * @param bmp_data [in] bmp data to be printed
 * @param bmp_data_len [in] bmp data length
 * @param need_reverse [in] int need_reverse
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_bmp_with_param(const ts_printer_para *p_printer_para, const char *bmp_data, int bmp_data_len, int need_reverse);

/**
 * @brief  add bmp file to printer cache with param
 * @param p_printer_para [in] pointer of ts_printer_para struct for setting value
 * @param bmp_path [in] bmp file path to be printed
 * @param need_reverse [in] int need_reverse
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_add_bmp_path_with_param(const ts_printer_para *p_printer_para, const char *bmp_path, int need_reverse);

/**
 * @brief  add barcode data to printer cache with param \n
 * the text will be transfered to barcode
 * @param [in] const ts_printer_para *p_printer_para
 * @param [in] ts_barcode_type barcode_type
 * @param [in] int code_width
 * @param [in] int code_height
 * @param [in] const char* barcode_text
 * @retval 0 : success
 * @retval !0: fail
 */
int printer_add_barcode_with_param(const ts_printer_para *p_printer_para, ts_barcode_type barcode_type, int code_width, int code_height, const char *barcode_text);

/**
 * @brief  add qrcode data to printer cache with param \n
 * the text will be transfered to qrcode
 * @param [in] const ts_printer_para *p_printer_para
 * @param [in] int code_size
 * @param [in] const char* qrcode_text
 * @retval 0 : success
 * @retval !0: fail
 */
int printer_add_qrcode_with_param(const ts_printer_para *p_printer_para, int code_size, const char *qrcode_text);

/**
 * @brief  start printing the data in the cache
 * @retval =0 : success
 * @retval !0 : fail
 * @pre printer_open or printer_set_para
 */
int printer_print(void);

/**
 * @brief  clean printer cache
 * @retval =0 : success
 * @retval !0 : fail
 */
int printer_clear(void);


/**
 * @brief  close printer
 * @retval =0 : success
 * @retval !0 : fail
 */
int printer_close(void);

/**
 * @brief printer_formblank
 * @param align_mode [in] align mode
 * @param dest [out] in & out buff
 * @param src [in] in buff
 * @param nfont [in] font type
 * @param available_dot [in] default value 384
 * @retval >=0 : success
 * @retval  <0 : fail
 */
int printer_formblank(const te_printer_align align_mode, char *dest,
                      char * const src, const te_printer_fontsize nfont,
                      const unsigned int available_dot);

/** @} */

/**
 * @defgroup retval retval
 * @brief printer related retval 
 * @{
 */

/**
 * @brief definition of printer retval code
 */
#define PRINTER_RET_OK                  (0)                     ///<success

/**
 * @brief definition of printer fail error code
 */
#define PRINTER_ERR_MIN                 (-1000)
#define PRINTER_ERR_NULL_ARG            (PRINTER_ERR_MIN - 1)   ///<null parameter
#define PRINTER_ERR_GET_INFO            (PRINTER_ERR_MIN - 2)   ///<get printer information failure
#define PRINTER_ERR_SET_DEFAULT_PARA    (PRINTER_ERR_MIN - 3)   ///<set default printer parameter failure
#define PRINTER_ERR_IN_PARA             (PRINTER_ERR_MIN - 4)   ///<input parameter error
#define PRINTER_ERR_SET_PARA            (PRINTER_ERR_MIN - 5)   ///<set printerparameter failure
#define PRINTER_ERR_CLEAR               (PRINTER_ERR_MIN - 6)   ///<clean printer cache failure
#define PRINTER_ERR_CLOSE               (PRINTER_ERR_MIN - 7)   ///<close printer failure
#define PRINTER_ERR_FEED                (PRINTER_ERR_MIN - 8)   ///<printer feed paper error
#define PRINTER_ERR_GET_PRINT_FONT      (PRINTER_ERR_MIN - 9)   ///<get print font failure
#define PRINTER_ERR_GET_BITMAP_DATA     (PRINTER_ERR_MIN - 10)  ///<get bitmap data failure
#define PRINTER_ERR_ARG_OVER_RANGE      (PRINTER_ERR_MIN - 11)  ///<over range parameter
#define PRINTER_ERR_GET_LAYOUT          (PRINTER_ERR_MIN - 12)  ///<get print bar\qrcode layout failure

/**
 * @brief print error code
 */
#define PRINTER_ERR_CACHE               (PRINTER_ERR_MIN - 21)  ///<print cache data exception
#define PRINTER_ERR_NO_PAPER            (PRINTER_ERR_MIN - 22)  ///<printer no paper
#define PRINTER_ERR_OVERHEAT            (PRINTER_ERR_MIN - 23)  ///<printer over heat
#define PRINTER_ERR_BMARK               (PRINTER_ERR_MIN - 24)  ///<printer bmark
#define PRINTER_ERR_COMM                (PRINTER_ERR_MIN - 25)  ///<printer communication error
#define PRINTER_ERR_NO_PRINTER          (PRINTER_ERR_MIN - 26)  ///<have no printer
#define PRINTER_ERR_LOW_BATTERY         (PRINTER_ERR_MIN - 27)  ///<low battery
#define PRINTER_ERR_NO_FONT             (PRINTER_ERR_MIN - 28)  ///<no print font lib
#define PRINTER_ERR_NO_CACHE_MEMORY     (PRINTER_ERR_MIN - 29)  ///<no cache memory
#define PRINTER_ERR_CACHING             (PRINTER_ERR_MIN - 30)  ///<printer is caching
#define PRINTER_ERR_PRINTING            (PRINTER_ERR_MIN - 31)  ///<printer is printing
#define PRINTER_ERR_NO_BATTERY          (PRINTER_ERR_MIN - 32)  ///<no battery

/** @} */

/** @} */


#ifdef __cplusplus
}
#endif

#endif

