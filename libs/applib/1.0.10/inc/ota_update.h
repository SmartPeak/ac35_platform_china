/*
 * Copyright (C) 2018 Shanghai Basewin Technology Co.,Ltd
 */

#ifndef OTA_UPDATE_H__
#define OTA_UPDATE_H__

//状态
enum
{
    OTA_STATUS_UNKNOW,
    OTA_STATUS_IDLE,
    OTA_STATUS_CHECKING,
    OTA_STATUS_CHECK_FAIL,
    OTA_STATUS_DOWNLOADING,
    OTA_STATUS_DOWNLOAD_FAIL,
    OTA_STATUS_VALIDATING,
    OTA_STATUS_VALIDATE_FAIL,
    OTA_STATUS_LOW_BATTERY,
    OTA_STATUS_INSTALLING,
    OTA_STATUS_INSTALL_FAIL,
    OTA_STATUS_INSTALL_DONE,
    OTA_STATUS_BUSY, /*Conflict status.*/
    OTA_STATUS_MAX
};

//失败原因
enum
{
    OTA_UPDATE_REASON_NONE,
    OTA_UPDATE_REASON_NO_NETWORK,
    OTA_UPDATE_REASON_NO_VALID_PKG,
    OTA_UPDATE_REASON_HASH_NO_MATCH,
    OTA_UPDATE_REASON_MEMORY_NOT_ENOUGH,
    OTA_UPDATE_REASON_MAX
};

/**
 * Need to remove file name.
 */
#define REMOVE_INFO_FILE_NAME "ota_update_remove.txt"

/**
 * Firmware type define.
 */
#define FIRMWARE_TYPE_AP "ap"
#define FIRMWARE_TYPE_SP "sp"
#define FIRMWARE_TYPE_MP "mp"

/**
 * Config file name.
 */
#define CONFIG_FILE_NAME "updates.txt"

/**
 * Config file TAG define.
 */
#define FIRMWARE_RES_TAG            "firmware-resources"
#define FIRMWARE_PROTOCAL_VERSION   "version"
#define FIRMWARE_TAG                "firmware"
#define FIRMWARE_TYPE_TAG           "type"
#define FIRMWARE_VERSION_TAG        "version"
#define FIRMWARE_NAME_TAG           "name"
#define FIRMWARE_HASH_TAG           "hash"
#define FIRMWARE_DESCRIPTION_TAG    "description"
#define FIRMWARE_DELTA_TAG          "delta"

typedef struct {
    char* from; //基础版本
    char* to; //目标版本
} delta_t;

typedef struct _firmware_t firmware_t;

typedef void (*install_result_cb)(firmware_t* firmware, int result);

//静默安装状态回调
typedef void (*hideinstall_status_cb)(int status, int percent);

struct _firmware_t {   
    int force_update;//0 -- 不强制更新，1 -- 强制更新
    char* type;//固件类型
    char* version; //固件版本
    char* name; //固件名字
    char* hash; //固件HASH
    char* description; //固件描述
    char* url;
    int port;
    char* msgId; //推送消息ID
    delta_t delta; //差分信息
    install_result_cb cb;
    firmware_t *next; 
};

typedef struct {
    char* version; //协议版本
    firmware_t *firmware; //firmware列表
} firmware_list_t;

void ota_update_init(void);
int ota_update_ap_entry(void);
int ota_update_sp_entry(void);
int ota_update_mq_entry(firmware_t* firmware);
void ota_update_handle_message(void);
int ota_update_is_in_idle(void);

void set_update_status(const char* type, int status, int percent, int reason);
int is_valid_version(const char* type, const char *version, const char* base_version);
int install_firmware(const char* type, const char* file_path, 
	void (*progress_cb)(int percent), char* remove_file_name);
void free_firmware(firmware_t *firmware, int free_self);
void free_firmware_list(firmware_list_t *list_info, int free_self);
int save_remove_file_info(const char* filename);
void clear_remove_file_info(void);
int ota_update_download_and_install_firmware(const char* firmware_type, 
	const char* name, const char* url, int port, const char* hash, int ui_hint);

//Interfaces need to implement by project files.
int ota_update_firmware(const char* firmware_type);

void ota_update_set_hideinstall_callback(hideinstall_status_cb status_cb);

#endif //OTA_UPDATE_H__
