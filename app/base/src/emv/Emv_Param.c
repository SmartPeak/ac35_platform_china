#include "bwsdk_api.h"
#include "mmi_display.h"
#include "mmi_input.h"

#include "EmvCtKernelL2.h"
#include "Kernel_Param.h"
#include "Kernel_Main.h"

#include "Emv_Param.h"
#include "pos_data.h"

#if 0
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_Param.c"
#endif

/*获取交易类型*/
int EMV_Get_TransType(void)
{
    if (ExtraData.transType == TRANS_QUERY_BAL) {
        return TRANSACTION_TYPE_EMV_INQUIRY;
    }
    return TRANSACTION_TYPE_EMV_GOODS;
}

int  CL_Get_Kernel_Version(void)
{
    return VERSION_QUICS;   //VERSION_QPBOC
}

static char m_AbleLog = 0;
/*使用是否打印log标志位*/
void  EMV_Set_AbleLog(char bAbleLogFalg){

    m_AbleLog = bAbleLogFalg;
}

/*获取打印log标志位*/
char  EMV_Get_AbleLog(void){
    return m_AbleLog;
}

/**
* @brief 获取系统版本信息
*/
int EMV_Get_SysVersion(void)
{
    char bCLKernelVersion[16] = { 0 };
    char bCTKernelVersion[16] = { 0 };
    int uiKernelVersion = sizeof(bCLKernelVersion);

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Top, DISP_HCenter, "EMV内核信息");

    Contactless_Get_VersionKernel(bCLKernelVersion, uiKernelVersion);
    Contact_Get_Version_Kernel(bCTKernelVersion, uiKernelVersion);
    mmi_display(DISP_Line1, 0, "QPBOC Ver:%s", bCLKernelVersion);
    mmi_display(DISP_Line1, 0, "PBOC Ver:%s", bCTKernelVersion);
    mmi_inputWaitKeypress(60);
    return 0x00;
}

