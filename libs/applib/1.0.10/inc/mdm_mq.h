/*
 * Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd
 */
 
#ifndef __MDM_MQ_H__
#define __MDM_MQ_H__

#include "MQTTAsync.h"

/**
 * Define mq status.
 */
enum
{
    MQ_STATUS_IDLE,
    MQ_STATUS_REPORT_INFO,
    MQ_STATUS_CONNECTING,
    MQ_STATUS_CONNECT_FAILED,
    MQ_STATUS_CONNECTED,
    MQ_STATUS_DISCONNECTED_FROM_REMOTE,
    MQ_STATUS_RECONNECTING,
    MQ_STATUS_MAX
};

typedef void (*mq_msg_callback)(const char* topic, const char* payload, int payloadLen);

char* mq_get_server_url(void);
int   mq_get_server_port(void);
char* mq_get_group_id(void);
char* mq_get_access_key(void);
char* mq_get_access_secret(void);
char* mq_get_user_name(void);
char* mq_get_user_password(void);
char* mq_get_client_id(void);
int mq_get_clean_session(void);
int mq_get_keep_alive_interval(void);
void mq_messge_arrived(void *context, char *topicName, int topicLen, MQTTAsync_message *m);
void mq_onconnect(void *context, MQTTAsync_successData *response);

void mdm_mq_init(void);
void mdm_mq_set_callback(mq_msg_callback cb);
mq_msg_callback mdm_mq_get_callback(void);
void mdm_mq_set_idle_state(int idle); // 1 -- idle, 0 -- transaction.
int  mdm_get_idle_state(void);
int mdm_report_info_by_http(void);
int mdm_report_status_by_http(const char * msgId, int status, const char *result);
int mdm_mq_check_network_available(void);
void mdm_set_init_allowed(int allowed); // 1 -- allowed, 0 -- not allowed.
int mdm_get_init_allowed(void);
void mdm_set_need_reinited(int allowed); // 1 -- need, 0 -- no need.
int mdm_get_need_reinited(void);
int mdm_mq_get_status(void);

#endif //__MDM_MQ_H__
