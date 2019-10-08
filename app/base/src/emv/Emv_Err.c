#include "bwsdk_api.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "QVSDC.h"
#include "EmvKernel.h"
#include "EmvCtKernelL2.h"
#include "trans_err.h"

struct _ErrMsg
{
    int         errIndex;
    char*       errCode;
    char*       errMsg;
};

#define MAX_INDEX       0xFFFF
static const struct _ErrMsg EMV_CT_ERR_MsgTab[] =
{
    {6,                                 "6",    "ǿ�ƽ���"},
    {EMV_ICC_BLOCK,                     "-3",   "IC������,������ֹ"},
    {EMV_ICC_APP_BLOCK,                 "-5",   "Ӧ����"},
    {EMV_ICC_NO_APP,                    "-6",   "��Ч��Ƭ"},
    {EMV_ICC_TIME_OUT,                  "-8",   "������ʱ"},
    {EMV_ICC_NOT_ACCEPT,                "-10",  "���ײ�����"},
    {EMV_ICC_DENIAL,                    "-11",  "���׾ܾ�"},
    {EMV_ICC_RECORD_NOTEXIST,           "-20",  "��¼������"},
    {EMV_ICC_RSP_ERR,                   "-4",   "��������"},
    {EMV_ICC_DATA_ERR,                  "-9",   "��������"},
    {EMV_ICC_RSP_6985,                  "-29",  "��������"},
    {MAX_INDEX,                         "FF",   "������ֹ"},
};

static const struct _ErrMsg EMV_CL_ERR_MsgTab[] =
{
    {EMV_DECLINED_OFFLINE,              "03",   "�ѻ��ܾ�"},
    {EMV_DECLINED_ONLINE,               "04",   "�����ܾ�"},
    {EMV_NO_ACCEPTED,                   "06",   "������"},
    {EMV_TERMINATED,                    "07",   "�ն˴���"},
    {EMV_CARD_BLOCKED,                  "08",   "��Ƭ����"},
    {EMV_APP_BLOCKED,                   "09",   "Ӧ����"},
    {EMV_NO_APP,                        "10",   "��Ӧ��"},
    {EMV_APP_NOT_ALLOW,                 "28",   "������ֹ"},
    {QVSDC_AMOUNT_BIG_THAN_CL_LIMIT,    "99",   "����"},
    {QPBOC_RETURN_TO_TAP_CARD_GPO_NULL, "118",  "IC�����׾ܾ�,������"},
    {MAX_INDEX,                         "FF",   "������ֹ"},
};

int G_EMV_ErrCode = 0;
int EMVErr_SetCLErrCode(int ret)
{
    G_EMV_ErrCode = ret;
    return ERR_EMV_CL;
}

int EMVErr_SetCTErrCode(int ret)
{
    G_EMV_ErrCode = ret;
    return ERR_EMV_CT;
}

char *EMVErr_GetCLErrMsg(void)
{
    short i;

    for (i = 0; ; i++) {
        if (EMV_CL_ERR_MsgTab[i].errIndex == MAX_INDEX) {
            break;
        }

        if (EMV_CL_ERR_MsgTab[i].errIndex == G_EMV_ErrCode) {
            break;
        }
    }
    return EMV_CL_ERR_MsgTab[i].errMsg;
}

char *EMVErr_GetCTErrMsg(void)
{
    short i;

    for (i = 0; ; i++) {
        if (EMV_CT_ERR_MsgTab[i].errIndex == MAX_INDEX) {
            break;
        }

        if (EMV_CT_ERR_MsgTab[i].errIndex == G_EMV_ErrCode) {
            break;
        }
    }
    return EMV_CT_ERR_MsgTab[i].errMsg;
}

