/*****************************************************************************
*  QR and P90 Basic tool library                                             *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     mq.h                                                            *
*  @brief    mq Module API                                                   *
*  Details.                                                                  *
*                                                                            *
*  @author   BoBo.Li                                                         *
*  @version  1.0.0                                                           *
*  @date     03/09/2019                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  03/09/2019 | 1.0.0     | BoBo.Li        | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "MQTTAsync.h"

enum
{
    MQ_ERR_URL_PARAM                   = -11,      /*!< url set error  */
    MQ_ERR_CLIENT_ID_PARAM             = -12,      /*!< client id set error*/
    MQ_ERR_GROUP_ID_PARAM              = -13,      /*!< group id set error */
    MQ_ERR_USER_NAME_PARAM             = -14,      /*!< user name set error*/
    MQ_ERR_USER_PASSWD_PARAM           = -15,      /*!< user passwd set error*/
    MQ_ERR_SUBSCRIBED_PARAM            = -16,      /*!< subscribed topic set error */
    MQ_ERR_PUBLISHED_PARAM             = -17,      /*!< published topic set  error */
    MQ_ERR_OFFLINE_PARAM               = -18,      /*!< offline param set error */
    MQ_ERR_ONCONNECT_PARAM             = -19,      /*!< onconnect callback set error */
    MQ_ERR_MAX_CONNECT                 = -20,      /*!< max connect error*/
    MQ_ERR_HAVE_RELEASED               = -21,      /*!< mq have release error*/
  
};

enum
{
    MQ_STATUS_IDLE,                                 /*!< mq in idle status  */
    MQ_STATUS_INIT,                                 /*!< mq init status */
    MQ_STATUS_CONNECTING,                           /*!< mq connecting status  */
    MQ_STATUS_CONNECT_FAILED,                       /*!< mq connected failed  */
    MQ_STATUS_CONNECTED,                            /*!< mq connected status  */
    MQ_STATUS_DISCONNECTED_FROM_REMOTE,             /*!< mq disconnected from remote */
    MQ_STATUS_RECONNECTING,                         /*!< mq reconnecting */
    MQ_STATUS_MAX           
};


//< server success callback
typedef void (*pSuccess)(void);
//< receiving the server message callback
typedef void (*pMessgeArrived)(char *topicName, int topicLen, char*payload,int payloadLen);
//< idle status callback
typedef int (*pIdle)(void);

typedef struct
{
    unsigned char   is_spt_offline_msg;     /*!< support offline msg 1:support 0:not support */
    char            *offline_topic;         /*!< offline topic */
    char            *offline_payload;       /*!< offline payload */
} mq_offline_param_t;

typedef struct
{
    MQTTAsync           client;                 /*!< connect client */
    char                *url;                   /*!< url */
    unsigned int        port;                   /*!< port */
    char                *client_id;             /*!< client id */
    char                *group_id;              /*!< group id */
    char                *user_name;             /*!< user name */
    char                *user_passwd;           /*!< user passwd */
    unsigned int        keep_interval;          /*!< keep interval */
    char                *subscribed_topic;      /*!< subscribed topic */
    char                *published_topic;       /*!< published topic */
    mq_offline_param_t  offline_param;          /*!< offline param */
    pSuccess            onconnect;              /*!< onconnect callback */
    pMessgeArrived      memsge_arrived;         /*!< memsge_arrived callback*/
    pSuccess            onpublish;              /*!< on publish callback */
    pSuccess            onsubcribe;             /*!< on subcribe callback*/
    pIdle               onidle;                 /*!< on idle callback 0:success !0:failture*/
    pIdle               onidlestatus;           /*!< on idle status callback,return 1:idle 0:stop*/

} mq_param_t;



/**
 * @brief mq get connect status
 * @retval mq connect status
 */
int mq_get_connect_status(void);

/**
 * @brief mq init
 * @param [in] param for mq init.
 * @retval = 0 Sucess,retval < 0 fail
 */
int mq_init(const mq_param_t* param);

/**
 * @brief mq send message
 * @param [in] qos          Quality of Service 0,1,2
 * @param [in] payload       send message data.
 * @param [in] payload_len   send message len.
 * @retval = 0 Sucess,retval < 0 fail
 */
int mq_send_message(int qos, const unsigned char *payload, unsigned int payload_len);









