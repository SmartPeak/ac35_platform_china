/*****************************************************************************
*  QR and P90 Basic communication api library header                         *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mmi_commu.h                                                     *
*  @brief    Network Communication Module API                                *
*  Details.                                                                  *
*                                                                            *
*  @author   ChengYang.Geng                                                  *
*  @version  1.0.0                                                           *
*  @date     12/11/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  12/11/2018 | 1.0.0     | ChengYang.Geng | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef _MMI_COMMU_H
#define _MMI_COMMU_H


#ifdef __cplusplus
extern   "C"
{
#endif


#ifdef ENABLE_COMMU_LOG
#undef ENABLE_COMMU_LOG
#endif
#define ENABLE_COMMU_LOG    1

/**
 * @defgroup commu commu
 * @brief net communication related interface
 * @{
 */
 
//=============================================================
//#include "mmi_commu.h"
//=============================================================


/**
 * @defgroup enum enum
 * @brief net communication related enum definition
 * @{
 */

//----------------------------------------------
// enum definition
//----------------------------------------------
/**
 * @brief Communication mode type definition[socket, http or https]
 */
typedef enum COMMU_MODE_ENUM
{
    COMMU_SOCKET = 0,       ///<socket
    COMMU_HTTP,             ///<http
    COMMU_HTTPS,            ///<https
    COMMU_SSL_SOCKET,       ///<ssl socket
    
} COMMU_MODE;

/**
 * @brief socket type definition[TCP or UDP]
 */
typedef enum SOCKET_TYPE_ENUM
{
    TCP_SOCKET = 0,         ///<tcp
    UDP_SOCKET,             ///<udp
    MAX_SOCKET
    
} SOCKET_TYPE;

/**
 * @brief host addr type definition[IP or DOMAIN]
 */
typedef enum ADDR_TYPE_ENUM
{
    IP_ADDR = 0,            ///<ip
    DOMAIN_ADDR             ///<domain
    
} ADDR_TYPE;

/**
 * @brief http method type definition[GET,POST,PUT,DELETE,HEAD and so on]
 */
typedef enum HTTP_METHOD_ENUM
{
    HTTP_GET = 0,           ///<get
    HTTP_POST,              ///<post
    HTTP_PUT,               ///<put
    HTTP_DELETE,            ///<delete
    HTTP_HEAD               ///<head
    
} HTTP_METHOD;

/** @} */

/**
 * @defgroup struct struct
 * @brief net communication related struct definition
 * @{
 */
 
//----------------------------------------------
// struct definition
//----------------------------------------------
/**
 * @brief sever parameter structure definition
 */
typedef struct SERVER_PARA_STRU
{
    char host[128];             /**<server address: IP or DOMAIN*/
    unsigned short port;        /**<server port*/
    
} SERVER_PARA;

/**
 * @brief socket parameter structure definition
 */
typedef struct SOCKET_PARA_STRU
{
    SOCKET_TYPE socket_type;    /**<socket type, UDP or TCP*/
    ADDR_TYPE addr_type;        /**<server address type, IP or DOMAIN*/
    
} SOCKET_PARA;

/**
 * @brief https parameter structure definition
 */
typedef struct CACRT_PARA_STRU
{
    char *p_cacrt;  /**<ca crt*/
    int cacrt_len;  /**<ca crt length*/
    
} CACRT_PARA;

/**
 * @brief callback function for display receiving countdown time
 * @code
    void display_timeout(const int rest_time) {
        mmi_display(DISP_LINE3, DISP_Right, "%d", rest_time);
    }
 * @endcode
 */
typedef void (*commu_display)(const int rest_time);

/**
 * @brief Communication parameter structure definition
 */
typedef struct COMMU_PARA_STRU
{
    COMMU_MODE commu_mode;          /**<communication mode*/
    int is_auto_switch_net;         /**<auto switch net GPRS or WIFI, 0-NO 1-YES*/
    int commu_timeout;              /**<the time of recv data timeout(>= 5)*/
    SERVER_PARA server_para;        /**<remote server para*/
    SOCKET_PARA socket_para;        /**<socket communication para*/
    CACRT_PARA cacrt_para;          /**<ca crt para*/
    commu_display display_timeout;  /**<display receiving countdown time,http/s unsupported*/
} COMMU_PARA;

/**
 * @brief callback function for setting headers of\n
          http or https parameters\n
          implemented by caller.
 * @param hmc [in] http handle for httpHeadPar(hmc, ...) of sdk api
 * @retval =0 : success
 * @retval !0 : fail
 */
typedef void (*commu_set_http_header)(const HTTP_MODE_CTX * hmc);

/**
 * @brief send parameter structure definition
 */
typedef struct HTTP_SEND_PARA_STRU
{
    HTTP_METHOD http_method;                /**<http request type*/
    char *http_url;	                        /**<http url*/
    int http_url_len;                       /**<http url length*/
    int is_keep_alive;                      /**<http keep alive flag(1-yes,0-no)*/
    commu_set_http_header set_http_header;  /**<set http header call back function pointer*/
    
} HTTP_SEND_PARA;

/** @} */

/**
 * @defgroup interface interface
 * @brief net communication related interface 
 * @{
 */
 
//----------------------------------------------
// net communication interface
//----------------------------------------------
/**
 * @brief set communication common parameter
 * @param pCommuPara [in] pointer of COMMU_PARA struct for setting value
 * @retval =0 : success
 * @retval !0 : fail
 */
int commu_set_para(COMMU_PARA *pCommuPara);

/**
 * @brief  connect host before online trade
 * @retval =0 : success
 * @retval !0 : fail
 * @pre commu_set_para
 */
int commu_preconnect(void);

/**
 * @brief  connect host 
 * @retval =0 : success
 * @retval !0 : fail
 * @pre commu_set_para
 */
int commu_connect(void);

/**
 * @brief send data without format
 * @param p_http_send_para [in] HTTP_SEND_PARA struct pointer
 * @param send_buff [in] send data buff
 * @param send_len [in] send data length
 * @retval =0 : success
 * @retval !0 : fail
 * @pre commu_set_para
 */
int commu_send(const HTTP_SEND_PARA *p_http_send_para,
               const char *send_buff,
               const int send_len);

/**
 * @brief receive data
 * @param recv_buff [out] recv buff
 * @param p_recv_len [out] recv data length
 * @param max_recv_len [in] max size of recv buff
 * @retval =0 : success
 * @retval !0 : fail
 */
int commu_recv(char *recv_buff, int *p_recv_len, const int max_recv_len);

/**
 * @brief get http response header value
 * @param const char *header [in] header key name
 * @param int size [in] header key name size
 * @retval !NULL : success
 * @retval =NULL : fail
 * @code
 *  For example: char *authToken = commu_get_head("Cookie", sizeof("Cookie"));
 * @endcode
 */
const char *commu_get_header(const char *header, int size);

/**
 * @brief  disconnect link
 * @retval =0 : success
 * @retval !0 : fail
 */
int commu_disconnect(void);

/**
 * @brief  get preconnect error code
 * @retval preconnect error code
 */
int commu_get_preconnect_errcode(void);

/** @} */

/**
 * @defgroup retval retval
 * @brief net communication related retval definition
 * @{
 */
 
//----------------------------------------------
// retval definition
//----------------------------------------------
/**
 * @brief communication retval code definition
 */
#define COMMU_RET_OK                        (0)                             ///<success

/**
 * @brief Communication fail error code definition
 */
#define COMMU_ERR_COMMU_MIN                 (-100)
#define COMMU_ERR_NULL_ARG                  (COMMU_ERR_COMMU_MIN - 1)       ///<null parameter
#define COMMU_ERR_COMMU_UNSET               (COMMU_ERR_COMMU_MIN - 2)       ///<communication parameters unseted
#define COMMU_ERR_UNCONNECTED               (COMMU_ERR_COMMU_MIN - 3)       ///<unconnected
#define COMMU_ERR_MODE                      (COMMU_ERR_COMMU_MIN - 4)       ///<communication type error
#define COMMU_ERR_NET_UNAVAILABLE           (COMMU_ERR_COMMU_MIN - 5)       ///<Network unavailable
#define COMMU_ERR_CREATE_THREAD             (COMMU_ERR_COMMU_MIN - 6)       ///<create thread error
#define COMMU_ERR_SOCKET_BREAK              (COMMU_ERR_COMMU_MIN - 7)       ///<Socket disconnected
#define COMMU_ERR_HTTP_URL                  (COMMU_ERR_COMMU_MIN - 8)       ///<url is null
#define COMMU_ERR_NEED_DISCONNECT           (COMMU_ERR_COMMU_MIN - 9)       ///<need to call disconnect first

/**
 * @brief error code of set communication parameters failed
 */
#define COMMU_SET_ERR_MIN                   (-200)   
#define COMMU_SET_ERR_SOCKET_TYPE           (COMMU_SET_ERR_MIN - 2)         ///<Socket type error
#define COMMU_SET_ERR_ADDR_TYPE             (COMMU_SET_ERR_MIN - 3)         ///<host addr error
#define COMMU_SET_ERR_CACRT                 (COMMU_SET_ERR_MIN - 4)         ///<cacrt error
#define COMMU_SET_ERR_HTTP_METHOD           (COMMU_SET_ERR_MIN - 5)         ///<HTTP METHOD error
#define COMMU_SET_ERR_SERVER_ARG            (COMMU_SET_ERR_MIN - 6)         ///<host ip or port error
#define COMMU_SET_ERR_SWITCH_FLAG           (COMMU_SET_ERR_MIN - 7)         ///<error of switch network parameter
#define COMMU_SET_ERR_TIMEOUT               (COMMU_SET_ERR_MIN - 8)         ///<error of receive timeout parameter
#define COMMU_SET_ERR_MALLOC                (COMMU_SET_ERR_MIN - 9)         ///<malloc failed

/**
 * @brief error code of connection failed
 */
#define COMMU_CONNECT_ERR_MIN               (-300)
#define COMMU_CONNECT_ERR_HTTPSHAKE         (COMMU_CONNECT_ERR_MIN - 1)     ///<httpsInit failed
#define COMMU_CONNECT_ERR_CREATE_SOCKET     (COMMU_CONNECT_ERR_MIN - 2)     ///<create socket failed
#define COMMU_CONNECT_ERR_CONNECT           (COMMU_CONNECT_ERR_MIN - 3)     ///<connect host failed
#define COMMU_CONNECT_ERR_HTTP_HEADER       (COMMU_CONNECT_ERR_MIN - 4)     ///<set HTTP Header failed
#define COMMU_CONNECT_ERR_HTTP_INIT         (COMMU_CONNECT_ERR_MIN - 5)     ///<http init failed
#define COMMU_CONNECT_ERR_ESTABLISH_SSL     (COMMU_CONNECT_ERR_MIN - 6)     ///<ssl establish failed

/**
 * @brief error code of sending failed
 */
#define COMMU_SEND_ERR_MIN                  (-400)
#define COMMU_SEND_ERR                      (COMMU_SEND_ERR_MIN - 1)        ///<send failed

/**
 * @brief error code of receiving failed
 */
#define COMMU_RECV_ERR_MIN                  (-500)
#define COMMU_RECV_ERR                      (COMMU_RECV_ERR_MIN - 1)        ///<receive failed
#define COMMU_RECV_TIMEOUT                  (COMMU_RECV_ERR_MIN - 2)        ///<receive timeout
#define COMMU_RECV_ERR_SSL_CONNECT          (COMMU_RECV_ERR_MIN - 3)        ///<ssl connect error
#define COMMU_RECV_ERR_REMOTE_CLOSED        (COMMU_RECV_ERR_MIN - 4)        ///<remote server close connection

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif

