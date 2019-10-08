/*
 * ʢ�����ܿƼ����޹�˾ ��Ȩ����(c) 
 *
 * 
 * ���籣������ͷ�ļ�  --- sysFile.h
 * ��    �ߣ�    ������ 
 * ��    �ڣ�    2017.12.28
 * ����޸��ˣ�   
 * ����޸����ڣ�
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
    char dhcpFlag;              ///< 0 �ر�  1:��  Ĭ��1��
    char ipaddr[15 + 1];        ///< ����IP
    char mask[15 + 1];          ///< ��������
    char gateway[15 + 1];       ///< ����IP��ַ
    char dns[15 + 1];           ///< ����������
    char dns_standby[15 + 1];   ///< ����������
} connected_wifiDhcp;

typedef struct
{
    int speaknum;
    int keysepaknum;
} speakandkeystudio_status;


///< -----------------------------------------------------------------
// �µ籣�����������ڴ˽ṹ��
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
    char wifiOk;            //wifi�Ƿ��
    char gprsOk;            //GPRS�Ƿ��
    char usr_apn_set;       //�Ƿ�����apn�û�����

    ///<
    int     dormancytime;
    int     sysSleepType;   ///<0,1,2
};

SYSFILE_GLOBAL struct SystemVar SystemSave;


int sysFile_ReadParam(void *data, unsigned int dataSize);
int sysFile_WriteParam(void *saveData, unsigned int dataSize);


#endif

