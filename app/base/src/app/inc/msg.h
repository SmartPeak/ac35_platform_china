#ifndef _MSG_H
#define _MSG_H

#define MSG_FILE(type)          MSG_FILE_##type

#define MSG_FILE_CN             "msg_cn.h"
#define MSG_FILE_EN             "msg_en.h"


#include MSG_FILE(CN)

#endif  //_MSG_H
