/*
 * 盛本智能科技有限公司 版权所有(c) 
 *
 * 
 * 掉电保护定义头文件  --- sysFile.h
 * 作    者：    刘德宇 
 * 日    期：    2017.12.28
 * 最后修改人：   
 * 最后修改日期：
*/

#ifndef SYSFILE_H
#define SYSFILE_H

#ifndef SYSFILE_GLOBAL
#define SYSFILE_GLOBAL extern
#endif

#define SYS_FILE_COMMU      "sysParam"

#define ON      1
#define OFF     0

#define CONNECTED_WIFI_LIST_MAX_LEN         10
#define MERCURYPLATFORMVER_211              0x20101

typedef struct
{
    char ssid[32 + 1];
    char mac[17 + 1];
    char pwd[32 + 1];
    char ifOpen;
} connected_wifi;

typedef struct
{
    char apn[32 + 1];
    char user[32 + 1];
    char pwd[32 + 1];
} connected_gprs;

typedef struct
{
    char dhcpFlag;              ///< 0 关闭  1:打开  默认1打开
    char ipaddr[15 + 1];        ///< 本地IP
    char mask[15 + 1];          ///< 子网掩码
    char gateway[15 + 1];       ///< 网关IP地址
    char dns[15 + 1];           ///< 域名服务器
    char dns_standby[15 + 1];   ///< 域名服务器
} connected_wifiDhcp;

typedef struct
{
    int speaknum;
    int keysepaknum;
} speakandkeystudio_status;


///< -----------------------------------------------------------------
// 下电保护变量定义在此结构中
struct SystemVar
{
    char commuType;
    connected_gprs gprs;
    char connected_wifi_num;
    connected_wifi wifi[CONNECTED_WIFI_LIST_MAX_LEN];
    speakandkeystudio_status studio_status;
    char connectError;
    char searchWifi;
    connected_wifiDhcp wifiDhcp;
    char wifiOk;            //wifi是否打开
    char gprsOk;            //GPRS是否打开
    char usr_apn_set;       //是否启用apn用户设置

    ///<
    int     dormancytime;
    int     sysSleepType;   ///<0,1,2
};

SYSFILE_GLOBAL struct SystemVar SystemSave;


int sysFile_ReadParam(void *data, unsigned int dataSize);
int sysFile_WriteParam(void *saveData, unsigned int dataSize);


#endif

