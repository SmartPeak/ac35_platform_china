/*
 * Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd
 */
 
#ifndef __MDM_MQ_H__
#define __MDM_MQ_H__

#include "MQTTAsync.h"

typedef void (*mq_msg_callback)(const char* topic, const char* payload, int payloadLen);

int mdm_mq_init(void);
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
