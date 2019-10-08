/*
 * Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd
 */

#ifndef __DATETIME_SETTINGS_H
#define __DATETIME_SETTINGS_H

void datetime_settings_init(void);
int datetime_settings_network_sync(void (*freshViewData)(int,char*));
int datetime_settings_manual_set(void (*freshViewData)(int,char*));
int datetime_is_network_sync_done(void);

#endif
