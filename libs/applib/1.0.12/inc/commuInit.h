#ifndef _COMMUINIT_H
#define _COMMUINIT_H

#include "bwsdk_api.h"
#include "applib_def.h"


void set_default_apn(void);
int connectOpenGprs(void);
int openGPRS(void);


int openWIFI(char *ssid, char *pwd, char *mac);

int pppDialV(void);
int isPPPInited(void);
void connect_init(void);

int sysGetWifiList(WIFI_INFO_T* info, unsigned int* info_len);
void getLock(void);
void releaseLock(void);
int switchNet(int mode);
void restoreNet(void);

int SetNetDeviceModel(void);

net_dev_t GetNetDeviceModel(void);

int GetSimExist(void);

#endif  // _COMMUINIT_H
