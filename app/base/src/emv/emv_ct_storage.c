#include "bwsdk_api.h"
#include "emv_ct_storage.h"

#include "Emv_Param.h"
#include "Kernel_Param.h"
#include "AppCallBack.h"
#include "EmvCtKernelL2.h"
#include "pos_data.h"

#define DEBUG_EMV_STORAGE       0
#if DEBUG_EMV_STORAGE
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG "Emv_Storage.c"
#endif

EMV_TERMINAL_INFO   TERMINAL_INFO;  // 终端参数
EMV_KERNEL_CONFIG   KERNEL_CONFIG;  // 内核配置

QPBOC_PARAM         _QPBOC_PARAMETER;
EXPRESS_PARAM       _AMEX_PARAMETER;
QVSDC_PARAM         _QVSDC_PARAMETER;
DISCOVER_PARAM      _DISCOVER_PARAMETER;
MIR_PARAMETER       _MIR_PARAMETER;
MASTRT_PARAM        _MASTRT_PARAM;

EMV_KERNEL_CONFIG_ICC KERNEL_CONFIG_ICC;// 接触配置

#define PARAM_FILE_NAME     "PARAM.dat"
#define AID_FILE_NAME       "AID.dat"
#define CAPK_FILE_NAME      "CAPK.dat"
#define IPK_FILE_NAME       "IPK.dat"
#define EXT_FILE_NAME       "EXT.dat"

/*初始化aid*/
static void initAid(void)
{
    EMV_AID_ITEM  aid1, aid2, aid3, aid4, aid5, aid6, aid7, aid8, aid9, aid10,
        aid11, aid12, aid13, aid14, aid15, aid16, aid17, aid18, aid19, aid20;

    memset(&aid2, 0, sizeof(EMV_AID_ITEM));
    memset(&aid3, 0, sizeof(EMV_AID_ITEM));
    memset(&aid4, 0, sizeof(EMV_AID_ITEM));
    memset(&aid5, 0, sizeof(EMV_AID_ITEM));
    memset(&aid6, 0, sizeof(EMV_AID_ITEM));
    memset(&aid7, 0, sizeof(EMV_AID_ITEM));
    memset(&aid8, 0, sizeof(EMV_AID_ITEM));
    memset(&aid9, 0, sizeof(EMV_AID_ITEM));
    memset(&aid10, 0, sizeof(EMV_AID_ITEM));
    memset(&aid11, 0, sizeof(EMV_AID_ITEM));
    memset(&aid12, 0, sizeof(EMV_AID_ITEM));
    memset(&aid13, 0, sizeof(EMV_AID_ITEM));
    memset(&aid14, 0, sizeof(EMV_AID_ITEM));
    memset(&aid15, 0, sizeof(EMV_AID_ITEM));
    memset(&aid16, 0, sizeof(EMV_AID_ITEM));
    memset(&aid17, 0, sizeof(EMV_AID_ITEM));
    memset(&aid18, 0, sizeof(EMV_AID_ITEM));
    memset(&aid19, 0, sizeof(EMV_AID_ITEM));
    memset(&aid20, 0, sizeof(EMV_AID_ITEM));
    // 12-->1
    aid1.m_uiAID = 7;
    memcpy(aid1.m_AID, "\xA0\x00\x00\x03\x33\x01\x01", 7);
    memcpy(aid1.m_AppVersion, "\x00\x30", 2);
    aid1.m_PartMach = 0x01;
    aid1.m_Default_DDOL_Len = 3;
    memcpy(aid1.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid1.m_Default_DDOL_Len = 3;
    memcpy(aid1.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid1.m_TerminalFloorLimit = 15000;
    aid1.m_TresholdValue = 10000;
    aid1.m_TargetPercentage = 0;
    aid1.m_MaxTargetPercentage = 0;
    memcpy(aid1.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid1.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid1.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid1.m_EC_Trans_Limite = 10000;
    aid1.m_ContactlessTransLimit = 20000;
    aid1.m_ContactlessFloorLimit = 10000;
    aid1.m_ContactlessCVMAmount = 5000;
    aid1.m_OnlinePinSpt = 1;  // 默认支持联机
    aid1.m_ucECTSIFlag = 1;   //

    // 2
    aid2.m_uiAID = 8;
    memcpy(aid2.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x03", 8);
    memcpy(aid2.m_AppVersion, "\x00\x96", 2);
    aid2.m_PartMach = 0x01;
    aid2.m_Default_DDOL_Len = 3;
    memcpy(aid2.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid2.m_Default_DDOL_Len = 3;
    memcpy(aid2.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid2.m_TerminalFloorLimit = 15000;
    aid2.m_TresholdValue = 10000;
    aid2.m_TargetPercentage = 0;
    aid2.m_MaxTargetPercentage = 0;
    memcpy(aid2.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid2.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid2.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid2.m_EC_Trans_Limite = 7000;
    aid2.m_ContactlessTransLimit = 20000;
    aid2.m_ContactlessFloorLimit = 10000;
    aid2.m_ContactlessCVMAmount = 5000;
    aid2.m_OnlinePinSpt = 1;  // 默认支持联机
    aid2.m_ucECTSIFlag = 1;   //

    // 3
    aid3.m_uiAID = 8;
    memcpy(aid3.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x04", 8);
    memcpy(aid3.m_AppVersion, "\x00\x96", 2);
    aid3.m_PartMach = 0x01;
    aid3.m_Default_DDOL_Len = 3;
    memcpy(aid3.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid3.m_Default_DDOL_Len = 3;
    memcpy(aid3.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid3.m_TerminalFloorLimit = 15000;
    aid3.m_TresholdValue = 10000;
    aid3.m_TargetPercentage = 0;
    aid3.m_MaxTargetPercentage = 0;
    memcpy(aid3.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid3.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid3.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid3.m_EC_Trans_Limite = 8000;
    aid3.m_ContactlessTransLimit = 20000;
    aid3.m_ContactlessFloorLimit = 10000;
    aid3.m_ContactlessCVMAmount = 5000;
    aid3.m_OnlinePinSpt = 1;  // 默认支持联机
    aid3.m_ucECTSIFlag = 1;   //

    // 4
    aid4.m_uiAID = 8;
    memcpy(aid4.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x05", 8);
    memcpy(aid4.m_AppVersion, "\x00\x96", 2);
    aid4.m_PartMach = 0x01;
    aid4.m_Default_DDOL_Len = 3;
    memcpy(aid4.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid4.m_Default_DDOL_Len = 3;
    memcpy(aid4.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid4.m_TerminalFloorLimit = 15000;
    aid4.m_TresholdValue = 10000;
    aid4.m_TargetPercentage = 0;
    aid4.m_MaxTargetPercentage = 0;
    memcpy(aid4.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid4.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid4.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid4.m_EC_Trans_Limite = 6000;
    aid4.m_ContactlessTransLimit = 20000;
    aid4.m_ContactlessFloorLimit = 10000;
    aid4.m_ContactlessCVMAmount = 5000;
    aid4.m_OnlinePinSpt = 1;  // 默认支持联机
    aid4.m_ucECTSIFlag = 1;   //
    // 5
    aid5.m_uiAID = 8;
    memcpy(aid5.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x06", 8);
    memcpy(aid5.m_AppVersion, "\x00\x96", 2);
    aid5.m_PartMach = 0x01;
    aid5.m_Default_DDOL_Len = 3;
    memcpy(aid5.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid5.m_Default_DDOL_Len = 3;
    memcpy(aid5.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid5.m_TerminalFloorLimit = 15000;
    aid5.m_TresholdValue = 10000;
    aid5.m_TargetPercentage = 0;
    aid5.m_MaxTargetPercentage = 0;
    memcpy(aid5.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid5.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid5.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid5.m_EC_Trans_Limite = 6000;
    aid5.m_ContactlessTransLimit = 20000;
    aid5.m_ContactlessFloorLimit = 10000;
    aid5.m_ContactlessCVMAmount = 5000;
    aid5.m_OnlinePinSpt = 1;  // 默认支持联机
    aid5.m_ucECTSIFlag = 1;   //
    // 6
    aid6.m_uiAID = 8;
    memcpy(aid6.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x07", 8);
    memcpy(aid6.m_AppVersion, "\x00\x96", 2);
    aid6.m_PartMach = 0x01;// 全匹配
    aid6.m_Default_DDOL_Len = 3;
    memcpy(aid6.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid6.m_Default_DDOL_Len = 3;
    memcpy(aid6.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid6.m_TerminalFloorLimit = 15000;
    aid6.m_TresholdValue = 10000;
    aid6.m_TargetPercentage = 0;
    aid6.m_MaxTargetPercentage = 0;
    memcpy(aid6.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid6.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid6.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid6.m_EC_Trans_Limite = 6000;
    aid6.m_ContactlessTransLimit = 20000;
    aid6.m_ContactlessFloorLimit = 10000;
    aid6.m_ContactlessCVMAmount = 5000;
    aid6.m_OnlinePinSpt = 1;  // 默认支持联机
    aid6.m_ucECTSIFlag = 1;   //

    // 7
    aid7.m_uiAID = 8;
    memcpy(aid7.m_AID, "\xA0\x00\x00\x03\x33\x01\x01\x01", 8);
    memcpy(aid7.m_AppVersion, "\x00\x30", 2);
    aid7.m_PartMach = 0x01;
    aid7.m_Default_DDOL_Len = 3;
    memcpy(aid7.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid7.m_Default_DDOL_Len = 3;
    memcpy(aid7.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid7.m_TerminalFloorLimit = 15000;
    aid7.m_TresholdValue = 10000;
    aid7.m_TargetPercentage = 0;
    aid7.m_MaxTargetPercentage = 0;
    memcpy(aid7.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid7.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid7.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid7.m_EC_Trans_Limite = 6000;
    aid7.m_ContactlessTransLimit = 20000;
    aid7.m_ContactlessFloorLimit = 10000;
    aid7.m_ContactlessCVMAmount = 5000;
    aid7.m_OnlinePinSpt = 1;  // 默认支持联机
    aid7.m_ucECTSIFlag = 1;   //

    // 8
    aid8.m_uiAID = 7;
    memcpy(aid8.m_AID, "\xA0\x00\x00\x00\x99\x90\x90", 7);
    memcpy(aid8.m_AppVersion, "\x00\x09", 2);
    aid8.m_PartMach = 0x01;
    aid8.m_Default_DDOL_Len = 3;
    memcpy(aid8.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid8.m_Default_DDOL_Len = 3;
    memcpy(aid8.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid8.m_TerminalFloorLimit = 15000;
    aid8.m_TresholdValue = 10000;
    aid8.m_TargetPercentage = 0;
    aid8.m_MaxTargetPercentage = 0;
    memcpy(aid8.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid8.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid8.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid8.m_EC_Trans_Limite = 6000;
    aid8.m_ContactlessTransLimit = 20000;
    aid8.m_ContactlessFloorLimit = 10000;
    aid8.m_ContactlessCVMAmount = 5000;
    aid8.m_OnlinePinSpt = 1;  // 默认支持联机
    aid8.m_ucECTSIFlag = 1;   //
    // 9
    aid9.m_uiAID = 6;
    memcpy(aid9.m_AID, "\xA0\x00\x00\x99\x99\x01", 6);
    memcpy(aid9.m_AppVersion, "\x99\x99", 2);
    aid9.m_PartMach = 0x01;
    aid9.m_Default_DDOL_Len = 3;
    memcpy(aid9.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid9.m_Default_DDOL_Len = 3;
    memcpy(aid9.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid9.m_TerminalFloorLimit = 15000;
    aid9.m_TresholdValue = 10000;
    aid9.m_TargetPercentage = 0;
    aid9.m_MaxTargetPercentage = 0;
    memcpy(aid9.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid9.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid9.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid9.m_EC_Trans_Limite = 6000;
    aid9.m_ContactlessTransLimit = 20000;
    aid9.m_ContactlessFloorLimit = 10000;
    aid9.m_ContactlessCVMAmount = 5000;
    aid9.m_OnlinePinSpt = 1;  // 默认支持联机
    aid9.m_ucECTSIFlag = 1;   //
    // 10
    aid10.m_uiAID = 7;
    memcpy(aid10.m_AID, "\xA0\x00\x00\x00\x04\x10\x10", 7);
    memcpy(aid10.m_AppVersion, "\x00\x02", 2);
    aid10.m_PartMach = 0x01;
    aid10.m_Default_DDOL_Len = 3;
    memcpy(aid10.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid10.m_Default_DDOL_Len = 3;
    memcpy(aid10.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid10.m_TerminalFloorLimit = 0;
    aid10.m_TresholdValue = 10000;
    aid10.m_TargetPercentage = 0;
    aid10.m_MaxTargetPercentage = 0;
    memcpy(aid10.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid10.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid10.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid10.m_EC_Trans_Limite = 6000;
    aid10.m_ContactlessTransLimit = 20000;
    aid10.m_ContactlessFloorLimit = 10000;
    aid10.m_ContactlessCVMAmount = 5000;
    aid10.m_OnlinePinSpt = 1;  // 默认支持联机
    aid10.m_ucECTSIFlag = 1;   //

    // 11
    aid11.m_uiAID = 7;
    memcpy(aid11.m_AID, "\xA0\x00\x00\x00\x65\x10\x10", 7);
    memcpy(aid11.m_AppVersion, "\x02\x00", 2);
    aid11.m_PartMach = 0x01;
    aid11.m_Default_DDOL_Len = 3;
    memcpy(aid11.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid11.m_Default_DDOL_Len = 3;
    memcpy(aid11.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid11.m_TerminalFloorLimit = 15000;
    aid11.m_TresholdValue = 10000;
    aid11.m_TargetPercentage = 0;
    aid11.m_MaxTargetPercentage = 0;
    memcpy(aid11.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid11.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid11.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid11.m_EC_Trans_Limite = 6000;
    aid11.m_ContactlessTransLimit = 20000;
    aid11.m_ContactlessFloorLimit = 10000;
    aid11.m_ContactlessCVMAmount = 5000;
    aid11.m_OnlinePinSpt = 1;  // 默认支持联机
    aid11.m_ucECTSIFlag = 1;   //

    // aid1--->12
    aid12.m_uiAID = 7;
    memcpy(aid12.m_AID, "\xA0\x00\x00\x00\x03\x10\x10", 7);
    memcpy(aid12.m_AppVersion, "\x00\x96", 2);
    aid12.m_PartMach = 0x01;
    aid12.m_Default_DDOL_Len = 3;
    memcpy(aid12.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid12.m_Default_DDOL_Len = 3;
    memcpy(aid12.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid12.m_TerminalFloorLimit = 15000;
    aid12.m_TresholdValue = 10000;
    aid12.m_TargetPercentage = 0;
    aid12.m_MaxTargetPercentage = 0;
    memcpy(aid12.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid12.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid12.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid12.m_EC_Trans_Limite = 6000;
    aid12.m_ContactlessTransLimit = 20000;
    aid12.m_ContactlessFloorLimit = 10000;
    aid12.m_ContactlessCVMAmount = 5000;
    aid12.m_OnlinePinSpt = 1;  // 默认支持联机
    aid12.m_ucECTSIFlag = 1;   //
    // 13
    aid13.m_uiAID = 8;
    memcpy(aid13.m_AID, "\xA0\x00\x00\x00\x25\x01\x05\x01", 8);
    memcpy(aid13.m_AppVersion, "\x00\x01", 2);
    aid13.m_PartMach = 0x01;
    aid13.m_Default_DDOL_Len = 3;
    memcpy(aid13.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid13.m_Default_DDOL_Len = 3;
    memcpy(aid13.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid13.m_TerminalFloorLimit = 15000;
    aid13.m_TresholdValue = 10000;
    aid13.m_TargetPercentage = 0;
    aid13.m_MaxTargetPercentage = 0;
    memcpy(aid13.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid13.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid13.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid13.m_EC_Trans_Limite = 6000;
    aid13.m_ContactlessTransLimit = 20000;
    aid13.m_ContactlessFloorLimit = 10000;
    aid13.m_ContactlessCVMAmount = 5000;
    aid13.m_OnlinePinSpt = 1;  // 默认支持联机
    aid13.m_ucECTSIFlag = 1;   //
    // 14
    aid14.m_uiAID = 5;
    memcpy(aid14.m_AID, "\xA1\x22\x33\x44\x55", 5);
    memcpy(aid14.m_AppVersion, "\x12\x34", 2);
    aid14.m_PartMach = 0x01;
    aid14.m_Default_DDOL_Len = 3;
    memcpy(aid14.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid14.m_Default_DDOL_Len = 3;
    memcpy(aid14.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid14.m_TerminalFloorLimit = 15000;
    aid14.m_TresholdValue = 10000;
    aid14.m_TargetPercentage = 0;
    aid14.m_MaxTargetPercentage = 0;
    memcpy(aid14.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid14.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid14.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid14.m_EC_Trans_Limite = 6000;
    aid14.m_ContactlessTransLimit = 20000;
    aid14.m_ContactlessFloorLimit = 10000;
    aid14.m_ContactlessCVMAmount = 5000;
    aid14.m_OnlinePinSpt = 1;  // 默认支持联机
    aid14.m_ucECTSIFlag = 1;   //

    // 15
    aid15.m_uiAID = 16;
    memcpy(aid15.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x01\x02\x03\x04\x05\x06\x07\x08\x09", 16);
    memcpy(aid15.m_AppVersion, "\x00\x96", 2);
    aid15.m_PartMach = 0x01;
    aid15.m_Default_DDOL_Len = 3;
    memcpy(aid15.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid15.m_Default_DDOL_Len = 3;
    memcpy(aid15.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid15.m_TerminalFloorLimit = 15000;
    aid15.m_TresholdValue = 10000;
    aid15.m_TargetPercentage = 0;
    aid15.m_MaxTargetPercentage = 0;
    memcpy(aid15.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid15.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid15.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid15.m_EC_Trans_Limite = 6000;
    aid15.m_ContactlessTransLimit = 20000;
    aid15.m_ContactlessFloorLimit = 10000;
    aid15.m_ContactlessCVMAmount = 5000;
    aid15.m_OnlinePinSpt = 1;  // 默认支持联机
    aid15.m_ucECTSIFlag = 1;   //

    // 16
    aid16.m_uiAID = 7;
    memcpy(aid16.m_AID, "\xA0\x00\x00\x01\x52\x30\x10", 7);
    memcpy(aid16.m_AppVersion, "\x00\x01", 2);
    aid16.m_PartMach = 0x01;
    aid16.m_Default_DDOL_Len = 3;
    memcpy(aid16.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid16.m_Default_DDOL_Len = 3;
    memcpy(aid16.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid16.m_TerminalFloorLimit = 15000;
    aid16.m_TresholdValue = 10000;
    aid16.m_TargetPercentage = 0;
    aid16.m_MaxTargetPercentage = 0;
    memcpy(aid16.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid16.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid16.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid16.m_EC_Trans_Limite = 6000;
    aid16.m_ContactlessTransLimit = 20000;
    aid16.m_ContactlessFloorLimit = 10000;
    aid16.m_ContactlessCVMAmount = 5000;
    aid16.m_OnlinePinSpt = 1;  // 默认支持联机
    aid16.m_ucECTSIFlag = 1;   //

    // visa aid
    // 17
    aid17.m_uiAID = 5;
    memcpy(aid17.m_AID, "\xA0\x00\x00\x00\x03", 5);
    memcpy(aid17.m_AppVersion, "\x00\x96", 2);
    aid17.m_PartMach = 0x01;
    aid17.m_Default_DDOL_Len = 3;
    memcpy(aid17.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid17.m_Default_DDOL_Len = 3;
    memcpy(aid17.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid17.m_TerminalFloorLimit = 15000;
    aid17.m_TresholdValue = 10000;
    aid17.m_TargetPercentage = 0;
    aid17.m_MaxTargetPercentage = 0;
    memcpy(aid17.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid17.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid17.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid17.m_EC_Trans_Limite = 6000;
    aid17.m_ContactlessTransLimit = 20000;
    aid17.m_ContactlessFloorLimit = 10000;
    aid17.m_ContactlessCVMAmount = 5000;
    aid17.m_OnlinePinSpt = 1;  // 默认支持联机
    aid17.m_ucECTSIFlag = 1;   //


    // 18
    aid18.m_uiAID = 6;
    memcpy(aid18.m_AID, "\xA0\x00\x00\x00\x03\x10", 6);
    memcpy(aid18.m_AppVersion, "\x00\x96", 2);
    aid18.m_PartMach = 0x01;
    aid18.m_Default_DDOL_Len = 3;
    memcpy(aid18.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid18.m_Default_DDOL_Len = 3;
    memcpy(aid18.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid18.m_TerminalFloorLimit = 15000;
    aid18.m_TresholdValue = 10000;
    aid18.m_TargetPercentage = 0;
    aid18.m_MaxTargetPercentage = 0;
    memcpy(aid18.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid18.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid18.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid18.m_EC_Trans_Limite = 6000;
    aid18.m_ContactlessTransLimit = 20000;
    aid18.m_ContactlessFloorLimit = 10000;
    aid18.m_ContactlessCVMAmount = 5000;
    aid18.m_OnlinePinSpt = 1;  // 默认支持联机
    aid18.m_ucECTSIFlag = 1;   //
    // 19
    aid19.m_uiAID = 10;
    memcpy(aid19.m_AID, "\xA0\x00\x00\x00\x09\x08\x07\x06\x05\x04", 10);
    memcpy(aid19.m_AppVersion, "\x00\x96", 2);
    aid19.m_PartMach = 0x01;
    aid19.m_Default_DDOL_Len = 3;
    memcpy(aid19.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid19.m_Default_DDOL_Len = 3;
    memcpy(aid19.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid19.m_TerminalFloorLimit = 15000;
    aid19.m_TresholdValue = 10000;
    aid19.m_TargetPercentage = 0;
    aid19.m_MaxTargetPercentage = 0;
    memcpy(aid19.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid19.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid19.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid19.m_EC_Trans_Limite = 6100;
    aid19.m_ContactlessTransLimit = 20000;
    aid19.m_ContactlessFloorLimit = 10000;
    aid19.m_ContactlessCVMAmount = 5000;
    aid19.m_OnlinePinSpt = 1;  // 默认支持联机
    aid19.m_ucECTSIFlag = 1;   //

    // 20
    aid20.m_uiAID = 8;
    memcpy(aid20.m_AID, "\xA0\x00\x00\x00\x03\x10\x10\x02", 8);
    memcpy(aid20.m_AppVersion, "\x00\x96", 2);
    aid20.m_PartMach = 0x01;
    aid20.m_Default_DDOL_Len = 3;
    memcpy(aid20.m_Default_DDOL, "\x9F\x37\x04", 3);
    aid20.m_Default_DDOL_Len = 3;
    memcpy(aid20.m_Default_TDOL, "\x9F\x37\x04", 3);
    aid20.m_TerminalFloorLimit = 15000;
    aid20.m_TresholdValue = 10000;
    aid20.m_TargetPercentage = 0;
    aid20.m_MaxTargetPercentage = 0;
    memcpy(aid20.m_TAC_Denial, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid20.m_TAC_Online, "\x00\x00\x00\x00\x00", 5);
    memcpy(aid20.m_TAC_Default, "\x00\x00\x00\x00\x00", 5);
    aid20.m_EC_Trans_Limite = 6000;
    aid20.m_ContactlessTransLimit = 20000;
    aid20.m_ContactlessFloorLimit = 10000;
    aid20.m_ContactlessCVMAmount = 5000;
    aid20.m_OnlinePinSpt = 1;  // 默认支持联机
    aid20.m_ucECTSIFlag = 1;   //


    EMV_AidList_Add_App(&aid1);
    EMV_AidList_Add_App(&aid2);
    EMV_AidList_Add_App(&aid3);
    EMV_AidList_Add_App(&aid4);
    EMV_AidList_Add_App(&aid5);
    EMV_AidList_Add_App(&aid6);
    EMV_AidList_Add_App(&aid7);
    EMV_AidList_Add_App(&aid8);
    EMV_AidList_Add_App(&aid9);
    EMV_AidList_Add_App(&aid10);
    EMV_AidList_Add_App(&aid11);
    EMV_AidList_Add_App(&aid12);
    EMV_AidList_Add_App(&aid13);
    EMV_AidList_Add_App(&aid14);
    EMV_AidList_Add_App(&aid15);
    EMV_AidList_Add_App(&aid16);
    EMV_AidList_Add_App(&aid17);
    EMV_AidList_Add_App(&aid18);
    EMV_AidList_Add_App(&aid19);
    EMV_AidList_Add_App(&aid20);
}

/*初始化capk*/
static void initCapk(void)
{
    EMV_CAPK_ITEM capk1, capk2, capk3, capk4, capk5, capk6, capk7, capk8,
        capk9, capk10, capk11, capk12, capk13, capk14, capk15, capk16,
        capk17, capk18, capk19, capk20, capk21, capk22, capk23, capk24, capk25, capk26, capk27, capk28;

    EMV_CAPK_ITEM smCapk1, smCapk2, smCapk3, smCapk4;
    EMV_CAPK_ITEM pRealCapk05, pRealCapk08;// 生产公钥

    memset(&capk1, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk2, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk3, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk4, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk5, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk6, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk7, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk8, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk9, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk10, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk11, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk12, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk13, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk14, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk15, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk16, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk17, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk18, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk19, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk20, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk21, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk22, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk23, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk24, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk25, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk26, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk27, 0, sizeof(EMV_CAPK_ITEM));
    memset(&capk28, 0, sizeof(EMV_CAPK_ITEM));

    memset(&smCapk1, 0, sizeof(EMV_CAPK_ITEM));
    memset(&smCapk2, 0, sizeof(EMV_CAPK_ITEM));
    memset(&smCapk3, 0, sizeof(EMV_CAPK_ITEM));
    memset(&smCapk4, 0, sizeof(EMV_CAPK_ITEM));

    memset(&pRealCapk05, 0, sizeof(EMV_CAPK_ITEM));
    memset(&pRealCapk08, 0, sizeof(EMV_CAPK_ITEM));
    // 1
    memcpy(capk1.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk1.m_CapkIndex = 0x50;
    capk1.m_ArithInd = AIRTH_IND_RSA;
    capk1.m_uiModules = 128;
    memcpy(capk1.m_Modules, "\xD1\x11\x97\x59\x00\x57\xB8\x41\x96\xC2\xF4\xD1\x1A\x8F\x3C\x05\x40\x8F\x42\x2A\x35\xD7\x02\xF9\x01\x06\xEA\x5B\x01\x9B\xB2\x8A\xE6\x07\xAA\x9C\xDE\xBC\xD0\xD8\x1A\x38\xD4\x8C\x7E\xBB\x00\x62\xD2\x87\x36\x9E\xC0\xC4\x21\x24\x24\x6A\xC3\x0D\x80\xCD\x60\x2A\xB7\x23\x8D\x51\x08\x4D\xED\x46\x98\x16\x2C\x59\xD2\x5E\xAC\x1E\x66\x25\x5B\x4D\xB2\x35\x25\x26\xEF\x09\x82\xC3\xB8\xAD\x3D\x1C\xCE\x85\xB0\x1D\xB5\x78\x8E\x75\xE0\x9F\x44\xBE\x73\x61\x36\x6D\xEF\x9D\x1E\x13\x17\xB0\x5E\x5D\x0F\xF5\x29\x0F\x88\xA0\xDB\x47", 128);
    capk1.m_uiExponents = 3;
    memcpy(capk1.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk1.m_Checksum, "\xB7\x69\x77\x56\x68\xCA\xCB\x5D\x22\xA6\x47\xD1\xD9\x93\x14\x1E\xDA\xB7\x23\x7B", 20);

    // 2
    memcpy(capk2.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk2.m_ArithInd = AIRTH_IND_RSA;
    capk2.m_CapkIndex = 0x51;
    capk2.m_uiModules = 144;
    memcpy(capk2.m_Modules, "\xDB\x5F\xA2\x9D\x1F\xDA\x8C\x16\x34\xB0\x4D\xCC\xFF\x14\x8A\xBE\xE6\x3C\x77\x20\x35\xC7\x98\x51\xD3\x51\x21\x07\x58\x6E\x02\xA9\x17\xF7\xC7\xE8\x85\xE7\xC4\xA7\xD5\x29\x71\x0A\x14\x53\x34\xCE\x67\xDC\x41\x2C\xB1\x59\x7B\x77\xAA\x25\x43\xB9\x8D\x19\xCF\x2C\xB8\x0C\x52\x2B\xDB\xEA\x0F\x1B\x11\x3F\xA2\xC8\x62\x16\xC8\xC6\x10\xA2\xD5\x8F\x29\xCF\x33\x55\xCE\xB1\xBD\x3E\xF4\x10\xD1\xED\xD1\xF7\xAE\x0F\x16\x89\x79\x79\xDE\x28\xC6\xEF\x29\x3E\x0A\x19\x28\x2B\xD1\xD7\x93\xF1\x33\x15\x23\xFC\x71\xA2\x28\x80\x04\x68\xC0\x1A\x36\x53\xD1\x4C\x6B\x48\x51\xA5\xC0\x29\x47\x8E\x75\x7F", 144);
    capk2.m_uiExponents = 1;
    memcpy(capk2.m_Exponents, "\x03", 1);
    memcpy(capk2.m_Checksum, "\xB9\xD2\x48\x07\x5A\x3F\x23\xB5\x22\xFE\x45\x57\x3E\x04\x37\x4D\xC4\x99\x5D\x71", 20);


    // 3
    memcpy(capk3.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk3.m_ArithInd = AIRTH_IND_RSA;
    capk3.m_CapkIndex = 0x52;
    capk3.m_uiModules = 176;
    memcpy(capk3.m_Modules, "\xAF\xF7\x40\xF8\xDB\xE7\x63\xF3\x33\xA1\x01\x3A\x43\x72\x20\x55\xC8\xE2\x2F\x41\x77\x9E\x21\x9B\x0E\x1C\x40\x9D\x60\xAF\xD4\x5C\x87\x89\xC5\x7E\xEC\xD7\x1E\xA4\xA2\x69\xA6\x75\x91\x6C\xC1\xC5\xE1\xA0\x5A\x35\xBD\x74\x5A\x79\xF9\x45\x55\xCE\x29\x61\x2A\xC9\x33\x87\x69\x66\x5B\x87\xC3\xCA\x8E\x1A\xC4\x95\x7F\x9F\x61\xFA\x7B\xFF\xE4\xE1\x76\x31\xE9\x37\x83\x7C\xAB\xF4\x3D\xD6\x18\x3D\x63\x60\xA2\x28\xA3\xEB\xC7\x3A\x1D\x1C\xDC\x72\xBF\x09\x95\x3C\x81\x20\x3A\xB7\xE4\x92\x14\x8E\x4C\xB7\x74\xCD\xDF\xAA\xC3\x54\x4D\x0D\xD4\xF8\xC8\xA0\xE9\xC7\x0B\x87\x7E\xA7\x9F\x2C\x22\xE4\xCE\x52\xC6\x9F\x3E\xF3\x76\xF6\x1B\x0F\x43\xA5\x40\xFE\x96\xC6\x3F\x58\x63\x10\xC3\xB6\xE3\x9C\x78\xC4\xD6\x47\xCA\xDB\x59\x33", 176);
    capk3.m_uiExponents = 1;
    memcpy(capk3.m_Exponents, "\x03", 1);
    memcpy(capk3.m_Checksum, "\x42\xD9\x6E\x6E\x12\x17\xE5\xB5\x9C\xC2\x07\x9C\xE5\x0C\x3D\x9F\x55\xB6\xFC\x1D", 20);


    // 4
    memcpy(capk4.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk4.m_ArithInd = AIRTH_IND_RSA;
    capk4.m_CapkIndex = 0x53;
    capk4.m_uiModules = 248;
    memcpy(capk4.m_Modules, "\xBC\xD8\x37\x21\xBE\x52\xCC\xCC\x4B\x64\x57\x32\x1F\x22\xA7\xDC\x76\x9F\x54\xEB\x80\x25\x91\x3B\xE8\x04\xD9\xEA\xBB\xFA\x19\xB3\xD7\xC5\xD3\xCA\x65\x8D\x76\x8C\xAF\x57\x06\x7E\xEC\x83\xC7\xE6\xE9\xF8\x1D\x05\x86\x70\x3E\xD9\xDD\xDA\xDD\x20\x67\x5D\x63\x42\x49\x80\xB1\x0E\xB3\x64\xE8\x1E\xB3\x7D\xB4\x0E\xD1\x00\x34\x4C\x92\x88\x86\xFF\x4C\xCC\x37\x20\x3E\xE6\x10\x6D\x5B\x59\xD1\xAC\x10\x2E\x2C\xD2\xD7\xAC\x17\xF4\xD9\x6C\x39\x8E\x5F\xD9\x93\xEC\xB4\xFF\xDF\x79\xB1\x75\x47\xFF\x9F\xA2\xAA\x8E\xEF\xD6\xCB\xDA\x12\x4C\xBB\x17\xA0\xF8\x52\x81\x46\x38\x71\x35\xE2\x26\xB0\x05\xA4\x74\xB9\x06\x2F\xF2\x64\xD2\xFF\x8E\xFA\x36\x81\x4A\xA2\x95\x00\x65\xB1\xB0\x4C\x0A\x1A\xE9\xB2\xF6\x9D\x4A\x4A\xA9\x79\xD6\xCE\x95\xFE\xE9\x48\x5E\xD0\xA0\x3A\xEE\x9B\xD9\x53\xE8\x1C\xFD\x1E\xF6\xE8\x14\xDF\xD3\xC2\xCE\x37\xAE\xFA\x38\xC1\xF9\x87\x73\x71\xE9\x1D\x6A\x5E\xB5\x9F\xDE\xDF\x75\xD3\x32\x5F\xA3\xCA\x66\xCD\xFB\xA0\xE5\x71\x46\xCC\x78\x98\x18\xFF\x06\xBE\x5F\xCC\x50\xAB\xD3\x62\xAE\x4B\x80\x99\x6D", 248);
    capk4.m_uiExponents = 1;
    memcpy(capk4.m_Exponents, "\x03", 1);
    memcpy(capk4.m_Checksum, "\xAC\x21\x3A\x2E\x0D\x2C\x0C\xA3\x5A\xD0\x20\x13\x23\x53\x6D\x58\x09\x7E\x4E\x57", 20);

    // 5
    memcpy(capk5.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk5.m_ArithInd = AIRTH_IND_RSA;
    capk5.m_CapkIndex = 0x54;
    capk5.m_uiModules = 248;
    memcpy(capk5.m_Modules, "\xC6\xDD\xC0\xB7\x64\x5F\x7F\x16\x28\x6A\xB7\xE4\x11\x66\x55\xF5\x6D\xD0\xC9\x44\x76\x60\x40\xDC\x68\x66\x4D\xD9\x73\xBD\x3B\xFD\x4C\x52\x5B\xCB\xB9\x52\x72\xB6\xB3\xAD\x9B\xA8\x86\x03\x03\xAD\x08\xD9\xE8\xCC\x34\x4A\x40\x70\xF4\xCF\xB9\xEE\xAF\x29\xC8\xA3\x46\x08\x50\xC2\x64\xCD\xA3\x9B\xBE\x3A\x7E\x7D\x08\xA6\x9C\x31\xB5\xC8\xDD\x9F\x94\xDD\xBC\x92\x65\x75\x8C\x0E\x73\x99\xAD\xCF\x43\x62\xCA\xEE\x45\x8D\x41\x4C\x52\xB4\x98\x27\x48\x81\xB1\x96\xDA\xCC\xA7\x27\x3F\x68\x7F\x2A\x65\xFA\xEB\x80\x9D\x4B\x2A\xC1\xD3\xD1\xEF\xB4\xF6\x49\x03\x22\x31\x8B\xD2\x96\xD1\x53\xB3\x07\xA3\x28\x3A\xB4\xE5\xBE\x6E\xBD\x91\x03\x59\xA8\x56\x5E\xB9\xC4\x36\x0D\x24\xBA\xAC\xA3\xDB\xFE\x39\x3F\x3D\x6C\x83\x0D\x60\x3C\x6F\xC1\xE8\x34\x09\xDF\xCD\x80\xD3\xA3\x3B\xA2\x43\x81\x3B\xBB\x4C\xEA\xF9\xCB\xAB\x6B\x74\xB0\x01\x16\xF7\x2A\xB2\x78\xA8\x8A\x01\x1D\x70\x07\x1E\x06\xCA\xB1\x40\x64\x64\x38\xD9\x86\xD4\x82\x81\x62\x4B\x85\xB3\xB2\xEB\xB9\xA6\xAB\x3B\xF2\x17\x8F\xCC\x30\x11\xE7\xCA\xF2\x48\x97\xAE\x7D", 248);
    capk5.m_uiExponents = 3;
    memcpy(capk5.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk5.m_Checksum, "\x06\x96\x06\x18\x79\x1A\x86\xD3\x87\x30\x1E\xDD\x4A\x3B\xAF\x2D\x34\xFE\xF1\xB4", 20);

    // 6
    memcpy(capk6.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk6.m_ArithInd = AIRTH_IND_RSA;
    capk6.m_CapkIndex = 0x57;
    capk6.m_uiModules = 96;
    memcpy(capk6.m_Modules, "\x94\x2B\x7F\x2B\xA5\xEA\x30\x73\x12\xB6\x3D\xF7\x7C\x52\x43\x61\x8A\xCC\x20\x02\xBD\x7E\xCB\x74\xD8\x21\xFE\x7B\xDC\x78\xBF\x28\xF4\x9F\x74\x19\x0A\xD9\xB2\x3B\x97\x13\xB1\x40\xFF\xEC\x1F\xB4\x29\xD9\x3F\x56\xBD\xC7\xAD\xE4\xAC\x07\x5D\x75\x53\x2C\x1E\x59\x0B\x21\x87\x4C\x79\x52\xF2\x9B\x8C\x0F\x0C\x1C\xE3\xAE\xED\xC8\xDA\x25\x34\x31\x23\xE7\x1D\xCF\x86\xC6\x99\x8E\x15\xF7\x56\xE3", 96);
    capk6.m_uiExponents = 3;
    memcpy(capk6.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk6.m_Checksum, "\x25\x1A\x5F\x5D\xE6\x1C\xF2\x8B\x5C\x6E\x2B\x58\x07\xC0\x64\x4A\x01\xD4\x6F\xF5", 20);

    // 7
    memcpy(capk7.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk7.m_ArithInd = AIRTH_IND_RSA;
    capk7.m_CapkIndex = 0x58;
    capk7.m_uiModules = 200;
    memcpy(capk7.m_Modules, "\x99\x55\x2C\x4A\x1E\xCD\x68\xA0\x26\x01\x57\xFC\x41\x51\xB5\x99\x28\x37\x44\x5D\x3F\xC5\x73\x65\xCA\x56\x92\xC8\x7B\xE3\x58\xCD\xCD\xF2\xC9\x2F\xB6\x83\x75\x22\x84\x2A\x48\xEB\x11\xCD\xFF\xE2\xFD\x91\x77\x0C\x72\x21\xE4\xAF\x62\x07\xC2\xDE\x40\x04\xC7\xDE\xE1\xB6\x27\x6D\xC6\x2D\x52\xA8\x7D\x2C\xD0\x1F\xBF\x2D\xC4\x06\x5D\xB5\x28\x24\xD2\xA2\x16\x7A\x06\xD1\x9E\x6A\x0F\x78\x10\x71\xCD\xB2\xDD\x31\x4C\xB9\x44\x41\xD8\xDC\x0E\x93\x63\x17\xB7\x7B\xF0\x6F\x51\x77\xF6\xC5\xAB\xA3\xA3\xBC\x6A\xA3\x02\x09\xC9\x72\x60\xB7\xA1\xAD\x3A\x19\x2C\x9B\x8C\xD1\xD1\x53\x57\x0A\xFC\xC8\x7C\x3C\xD6\x81\xD1\x3E\x99\x7F\xE3\x3B\x39\x63\xA0\xA1\xC7\x97\x72\xAC\xF9\x91\x03\x3E\x1B\x83\x97\xAD\x03\x41\x50\x0E\x48\xA2\x47\x70\xBC\x4C\xBE\x19\xD2\xCC\xF4\x19\x50\x4F\xDB\xF0\x38\x9B\xC2\xF2\xFD\xCD\x4D\x44\xE6\x1F", 200);
    capk7.m_uiExponents = 3;
    memcpy(capk7.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk7.m_Checksum, "\x75\x3E\xD0\xAA\x23\xE4\xCD\x5A\xBD\x69\xEA\xE7\x90\x4B\x68\x4A\x34\xA5\x7C\x22", 20);


    // 8
    memcpy(capk8.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk8.m_ArithInd = AIRTH_IND_RSA;
    capk8.m_CapkIndex = 0x96;
    capk8.m_uiModules = 128;
    memcpy(capk8.m_Modules, "\xB7\x45\x86\xD1\x9A\x20\x7B\xE6\x62\x7C\x5B\x0A\xAF\xBC\x44\xA2\xEC\xF5\xA2\x94\x2D\x3A\x26\xCE\x19\xC4\xFF\xAE\xEE\x92\x05\x21\x86\x89\x22\xE8\x93\xE7\x83\x82\x25\xA3\x94\x7A\x26\x14\x79\x6F\xB2\xC0\x62\x8C\xE8\xC1\x1E\x38\x25\xA5\x6D\x3B\x1B\xBA\xEF\x78\x3A\x5C\x6A\x81\xF3\x6F\x86\x25\x39\x51\x26\xFA\x98\x3C\x52\x16\xD3\x16\x6D\x48\xAC\xDE\x8A\x43\x12\x12\xFF\x76\x3A\x7F\x79\xD9\xED\xB7\xFE\xD7\x6B\x48\x5D\xE4\x5B\xEB\x82\x9A\x3D\x47\x30\x84\x8A\x36\x6D\x33\x24\xC3\x02\x70\x32\xFF\x8D\x16\xA1\xE4\x4D\x8D", 128);
    capk8.m_uiExponents = 1;
    memcpy(capk8.m_Exponents, "\x03", 1);
    memcpy(capk8.m_Checksum, "\x76\x16\xE9\xAC\x8B\xE0\x14\xAF\x88\xCA\x11\xA8\xFB\x17\x96\x7B\x73\x94\x03\x0E", 20);

    // 9
    memcpy(capk9.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk9.m_ArithInd = AIRTH_IND_RSA;
    capk9.m_CapkIndex = 0xE1;
    capk9.m_uiModules = 112;
    memcpy(capk9.m_Modules, "\x99\xC5\xB7\x0A\xA6\x1B\x4F\x4C\x51\xB6\xF9\x0B\x0E\x3B\xFB\x7A\x3E\xE0\xE7\xDB\x41\xBC\x46\x68\x88\xB3\xEC\x8E\x99\x77\xC7\x62\x40\x7E\xF1\xD7\x9E\x0A\xFB\x28\x23\x10\x0A\x02\x0C\x3E\x80\x20\x59\x3D\xB5\x0E\x90\xDB\xEA\xC1\x8B\x78\xD1\x3F\x96\xBB\x2F\x57\xEE\xDD\xC3\x0F\x25\x65\x92\x41\x7C\xDF\x73\x9C\xA6\x80\x4A\x10\xA2\x9D\x28\x06\xE7\x74\xBF\xA7\x51\xF2\x2C\xF3\xB6\x5B\x38\xF3\x7F\x91\xB4\xDA\xF8\xAE\xC9\xB8\x03\xF7\x61\x0E\x06\xAC\x9E\x6B", 112);
    capk9.m_uiExponents = 1;
    memcpy(capk9.m_Exponents, "\x03", 1);
    memcpy(capk9.m_Checksum, "\xF8\x70\x7B\x9B\xED\xF0\x31\xE5\x8A\x9F\x84\x36\x31\xB9\x0C\x90\xD8\x0E\xD6\x95", 20);

    // 10
    memcpy(capk10.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk10.m_ArithInd = AIRTH_IND_RSA;
    capk10.m_CapkIndex = 0xE2;
    capk10.m_uiModules = 112;
    memcpy(capk10.m_Modules, "\xBD\x23\x2E\x34\x8B\x11\x8E\xB3\xF6\x44\x6E\xF4\xDA\x6C\x3B\xAC\x9B\x2A\xE5\x10\xC5\xAD\x10\x7D\x38\x34\x32\x55\xD2\x1C\x4B\xDF\x49\x52\xA4\x2E\x92\xC6\x33\xB1\xCE\x4B\xFE\xC3\x9A\xFB\x6D\xFE\x14\x7E\xCB\xB9\x1D\x68\x1D\xAC\x15\xFB\x0E\x19\x8E\x9A\x7E\x46\x36\xBD\xCA\x10\x7B\xCD\xA3\x38\x4F\xCB\x28\xB0\x6A\xFE\xF9\x0F\x09\x9E\x70\x84\x51\x1F\x3C\xC0\x10\xD4\x34\x35\x03\xE1\xE5\xA6\x72\x64\xB4\x36\x7D\xAA\x9A\x39\x49\x49\x92\x72\xE9\xB5\x02\x2F", 112);
    capk10.m_uiExponents = 1;
    memcpy(capk10.m_Exponents, "\x03", 1);
    memcpy(capk10.m_Checksum, "\xC1\x05\x6A\xDC\xE9\xE6\xF7\x6E\xA7\x7C\x89\xCB\x83\x2F\x5A\x48\x17\x90\x7A\x1A", 20);

    // 11
    memcpy(capk11.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk11.m_ArithInd = AIRTH_IND_RSA;
    capk11.m_CapkIndex = 0xE3;
    capk11.m_uiModules = 112;
    memcpy(capk11.m_Modules, "\xBC\x01\xE1\x22\x23\xE1\xA4\x1E\x88\xBF\xFA\x80\x10\x93\xC5\xF8\xCE\xC5\xCD\x05\xDB\xBD\xBB\x78\x7C\xE8\x72\x49\xE8\x80\x83\x27\xC2\xD2\x18\x99\x1F\x97\xA1\x13\x1E\x8A\x25\xB0\x12\x2E\xD1\x1E\x70\x9C\x53\x3E\x88\x86\xA1\x25\x9A\xDD\xFD\xCB\xB3\x96\x60\x4D\x24\xE5\x05\xA2\xD0\xB5\xDD\x03\x84\xFB\x00\x02\xA7\xA1\xEB\x39\xBC\x8A\x11\x33\x9C\x7A\x94\x33\xA9\x48\x33\x77\x61\xBE\x73\xBC\x49\x7B\x8E\x58\x73\x6D\xA4\x63\x65\x38\xAD\x28\x2D\x3C\xD3\xDB", 112);
    capk11.m_uiExponents = 3;
    memcpy(capk11.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk11.m_Checksum, "\x1B\x79\x5C\xBB\x08\x30\xE2\xC5\x23\x17\x04\xFA\x57\x42\x4D\x1C\x4E\x50\xF3\xE4", 20);

    // 12
    memcpy(capk12.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk12.m_ArithInd = AIRTH_IND_RSA;
    capk12.m_CapkIndex = 0xE4;
    capk12.m_uiModules = 128;
    memcpy(capk12.m_Modules, "\xCB\xF2\xE4\x0F\x08\x36\xC9\xA5\xE3\x90\xA3\x7B\xE3\xB8\x09\xBD\xF5\xD7\x40\xCB\x1D\xA3\x8C\xFC\x05\xD5\xF8\xD6\xB7\x74\x5B\x5E\x9A\x3F\xA6\x96\x1E\x55\xFF\x20\x41\x21\x08\x52\x5E\x66\xB9\x70\xF9\x02\xF7\xFF\x43\x05\xDD\x83\x2C\xD0\x76\x3E\x3A\xA8\xB8\x17\x3F\x84\x77\x71\x00\xB1\x04\x7B\xD1\xD7\x44\x50\x93\x12\xA0\x93\x2E\xD2\x5F\xED\x52\xA9\x59\x43\x07\x68\xCC\xD9\x02\xFD\x8C\x8A\xD9\x12\x3E\x6A\xDD\xB3\xF3\x4B\x92\xE7\x92\x4D\x72\x9C\xB6\x47\x35\x33\xAE\x2B\x2B\x55\xBF\x0E\x44\x96\x4F\xDE\xA8\x44\x01\x17", 128);
    capk12.m_uiExponents = 1;
    memcpy(capk12.m_Exponents, "\x03", 1);
    memcpy(capk12.m_Checksum, "\xAC\x8D\xA3\xE1\x23\x24\xD7\x19\xC1\xD5\xC9\xE6\xE8\x58\x01\x57\x19\x6E\xFE\xB9", 20);

    // 13
    memcpy(capk13.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk13.m_ArithInd = AIRTH_IND_RSA;
    capk13.m_CapkIndex = 0xE5;
    capk13.m_uiModules = 128;
    memcpy(capk13.m_Modules, "\xD4\xFD\xAE\x94\xDE\xDB\xEC\xC6\xD2\x0D\x38\xB0\x1E\x91\x82\x6D\xC6\x95\x43\x38\x37\x99\x17\xB2\xBB\x8A\x6B\x36\xB5\xD3\xB0\xC5\xED\xA6\x0B\x33\x74\x48\xBA\xFF\xEB\xCC\x3A\xBD\xBA\x86\x9E\x8D\xAD\xEC\x6C\x87\x01\x10\xC4\x2F\x5A\xAB\x90\xA1\x8F\x4F\x86\x7F\x72\xE3\x38\x6F\xFC\x7E\x67\xE7\xFF\x94\xEB\xA0\x79\xE5\x31\xB3\xCF\x32\x95\x17\xE8\x1C\x5D\xD9\xB3\xDC\x65\xDB\x5F\x90\x43\x19\x0B\xE0\xBE\x89\x7E\x5F\xE4\x8A\xDF\x5D\x3B\xFA\x05\x85\xE0\x76\xE5\x54\xF2\x6E\xC6\x98\x14\x79\x7F\x15\x66\x9F\x4A\x25\x5C\x13", 128);
    capk13.m_uiExponents = 1;
    memcpy(capk13.m_Exponents, "\x03", 1);
    memcpy(capk13.m_Checksum, "\xAD\xA2\x34\x9A\xFD\x11\x8D\x55\xAF\x78\x2D\x37\xB6\x46\x51\xAF\x1C\xA6\x1E\xE5", 20);

    // 14
    memcpy(capk14.m_RID, "\xA0\x00\x00\x99\x99", 5);
    capk14.m_ArithInd = AIRTH_IND_RSA;
    capk14.m_CapkIndex = 0xE6;
    capk14.m_uiModules = 128;
    memcpy(capk14.m_Modules, "\xEB\xF9\xFA\xEC\xC3\xE5\xC3\x15\x70\x96\x94\x66\x47\x75\xD3\xFB\xDA\x5A\x50\x4D\x89\x34\x4D\xD9\x20\xC5\x56\x96\xE8\x91\xD9\xAB\x62\x25\x98\xA9\xD6\xAB\x8F\xBF\x35\xE4\x59\x9C\xAB\x7E\xB2\x2F\x95\x69\x92\xF8\xAB\x2E\x65\x35\xDE\xCB\x6B\x57\x6F\xA0\x67\x5F\x97\xC2\x3D\xD4\xC3\x74\xA6\x6E\x6A\xF4\x19\xC9\xD2\x04\xD0\xB9\xF9\x3C\x08\xD7\x89\xD6\x38\x05\x66\x0F\xBB\x62\x9D\xF1\xB4\x88\xCF\xA1\xD7\xA1\x3E\x9B\x72\x94\x37\xEE\xAF\xE7\x18\xEF\xA8\x59\x34\x8B\xA0\xD7\x68\x12\xA9\x9F\x31\xCD\x36\x4F\x2A\x4F\xD4\x2F", 128);
    capk14.m_uiExponents = 3;
    memcpy(capk14.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk14.m_Checksum, "\x8A\xA4\xF4\x64\x8F\x0D\xC6\x2A\xB6\xAE\xD9\x25\x54\xAD\x1A\x83\x1B\xAF\xC9\xE4", 20);

    // 15
    memcpy(capk15.m_RID, "\xA0\x00\x00\x00\x25", 5);
    capk15.m_ArithInd = AIRTH_IND_RSA;
    capk15.m_CapkIndex = 0x60;
    capk15.m_uiModules = 144;
    memcpy(capk15.m_Modules, "\xA8\xEE\x74\xED\xEF\x3C\x0D\xCA\x51\x02\xFF\x9B\x57\x07\x97\x5F\xF6\x7B\x60\xD6\x4B\x5E\x73\x22\xD4\x8D\xE9\xD3\xBB\x61\x53\xF6\x35\x12\xA0\x91\xB6\x06\xDD\x8F\xD5\xF6\xA1\x45\x88\x32\x4E\xF8\x82\x78\x44\xC7\xFF\xC0\xBA\xB2\x33\x4A\xE5\x20\x77\x70\x07\x8B\x69\xCD\xC3\xF2\xC6\x66\xCF\x69\xE2\x8E\x16\xE1\x81\x67\x14\xC4\xDF\x31\x3B\xEF\x53\x9C\xC0\x1D\xA9\xDD\x2D\x6F\x47\xDE\x4F\x24\x7C\x50\x0B\x56\x1C\x09\x91\x66\xAD\x4F\xC1\x6D\xF1\x2D\xFB\x68\x4A\xC4\x8D\x35\xCD\xD2\xC4\x7A\x13\xA8\x6A\x5A\x16\x23\x06\xF6\x4E\x33\xB0\x92\xAB\x74\xED\xA7\x1A\x40\x91\xD9\x6E\x3D\xAA\x47", 144);
    capk15.m_uiExponents = 3;
    memcpy(capk15.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk15.m_Checksum, "\x89\x4B\x8D\xF1\x9B\xDC\x69\x11\x03\xC3\xB9\x39\x79\xF5\xEE\x28\xC0\x58\x88\xA7", 20);


    // 16
    memcpy(capk16.m_RID, "\xA0\x00\x00\x00\x03", 5);
    capk16.m_ArithInd = AIRTH_IND_RSA;
    capk16.m_CapkIndex = 0x61;
    capk16.m_uiModules = 248;
    memcpy(capk16.m_Modules, "\x86\xC7\x25\x46\x65\xE1\x7C\xE6\x93\x4D\xF7\xD0\x82\x56\x9F\x20\x8D\x1C\xC1\xAD\x8E\x9F\xB2\xFE\x23\xE3\xD7\x46\x7B\xE5\x0B\x4F\x87\x4F\x90\x6A\xDF\x22\x80\xEC\x9D\x20\x4F\x6D\x10\xC0\x37\xA2\x3C\xE5\xFD\x82\x83\xC9\xED\x47\xD1\xC6\x69\xAB\xDD\x7C\x1C\xB3\x56\xC7\x0B\xCD\xC4\x4E\x5C\x8A\xE2\x31\x55\x5F\x7B\x78\x6A\xC9\xC3\x15\x5B\xCD\x51\xF2\x8E\xFB\xC1\xB3\x3C\xC8\x72\x77\x04\x92\x19\xB2\xC8\x90\x95\x27\x36\xC4\x71\x34\x87\x11\x16\x78\x91\x1D\x9F\x42\xE0\x80\x74\xCF\x52\x4E\x65\xD7\x21\xD7\x27\xF0\x54\xE6\xB5\xE8\x5E\xC9\x2B\x3E\xB5\x9F\xFE\xE9\x26\xDD\x6C\x31\x4D\xF5\x55\xC9\x4A\xD4\x87\xA9\x9B\x67\xCB\x7C\x7B\xA5\xE4\x6A\x5B\x81\x3D\xDB\x91\x8B\x8E\x3E\x04\x23\xF4\x30\x2A\x58\x68\x6D\x12\x63\xC0\xBA\xCA\x9E\x82\x06\x8C\x49\x32\x89\xE3\xE6\x93\x6E\xCA\x5F\x9F\x77\xE0\x6B\x0D\x6F\xBD\xA7\x18\x81\x8B\x83\x50\x20\x09\x8C\x67\x1C\x5D\xD7\xE9\xB8\xE8\xE8\x41\xD2\xDF\x32\xEE\x94\xA7\xF4\x74\x84\x84\xCA\x44\x10\x8A\xB2\x41\xA5\x26\x3B\xA1\xFF\x00\xD5\x13\x60\xDD\xDC\x74\x9D\x30\xA1", 248);
    capk16.m_uiExponents = 3;
    memcpy(capk16.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk16.m_Checksum, "\xCC\xCF\x27\xC4\x9C\x15\xB2\xA9\x41\x0E\xC6\x08\x92\x23\xA3\xA0\x1E\xA8\x43\x3E", 20);


    // 17
    memcpy(capk17.m_RID, "\xA0\x00\x00\x01\x52", 5);
    capk17.m_ArithInd = AIRTH_IND_RSA;
    capk17.m_CapkIndex = 0xD0;
    capk17.m_uiModules = 144;
    memcpy(capk17.m_Modules, "\xD0\x5C\x2A\x09\xD0\x9C\x90\x31\x36\x6E\xC0\x92\xBC\xAC\x67\xD4\xB1\xB4\xF8\x8B\x10\x00\x5E\x1F\xC4\x5C\x1B\x48\x3A\xE7\xEB\x86\xFF\x0E\x88\x4A\x19\xC0\x59\x5A\x6C\x34\xF0\x63\x86\xD7\x76\xA2\x1D\x62\x0F\xC9\xF9\xC4\x98\xAD\xCA\x00\xE6\x6D\x12\x9B\xCD\xD4\x78\x98\x37\xB9\x6D\xCC\x7F\x09\xDA\x94\xCC\xAC\x5A\xC7\xCF\xC0\x7F\x46\x00\xDF\x78\xE4\x93\xDC\x19\x57\xDE\xBA\x3F\x48\x38\xA4\xB8\xBD\x4C\xEF\xE4\xE4\xC6\x11\x90\x85\xE5\xBB\x21\x07\x73\x41\xC5\x68\xA2\x1D\x65\xD0\x49\xD6\x66\x80\x7C\x39\xC4\x01\xCD\xFE\xE7\xF7\xF9\x9B\x8F\x9C\xB3\x4A\x88\x41\xEA\x62\xE8\x3E\x8D\x63", 144);
    capk17.m_uiExponents = 3;
    memcpy(capk17.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk17.m_Checksum, "\xDE\x1B\xB8\xA3\x7C\xDD\xBC\xEA\xAB\x04\x3A\xAE\xF8\x16\x34\x12\x03\x49\x72\x6D", 20);

    // 18
    memcpy(capk18.m_RID, "\xA0\x00\x00\x01\x52", 5);
    capk18.m_ArithInd = AIRTH_IND_RSA;
    capk18.m_CapkIndex = 0xD1;
    capk18.m_uiModules = 248;
    memcpy(capk18.m_Modules, "\xA7\x1A\xF9\x77\xC1\x07\x93\x04\xD6\xDF\xF3\xF6\x65\xAB\x6D\xB3\xFB\xDF\xA1\xB1\x70\x28\x7A\xC6\xD7\xBC\x0A\xFC\xB7\xA2\x02\xA4\xC8\x15\xE1\xFC\x2E\x34\xF7\x5A\x05\x25\x64\xEE\x21\x48\xA3\x9C\xD6\xB0\xF3\x9C\xFA\xEF\x95\xF0\x29\x4A\x86\xC3\x19\x8E\x34\x9F\xF8\x2E\xEC\xE6\x33\xD5\x0E\x58\x60\xA1\x50\x82\xB4\xB3\x42\xA9\x09\x28\x02\x40\x57\xDD\x51\xA2\x40\x1D\x78\x1B\x67\xAE\x75\x98\xD5\xD1\xFF\x26\xA4\x41\x97\x0A\x19\xA3\xA5\x80\x11\xCA\x19\x28\x42\x79\xA8\x55\x67\xD3\x11\x92\x64\x80\x6C\xAF\x76\x11\x22\xA7\x1F\xC0\x49\x2A\xC8\xD8\xD4\x2B\x03\x6C\x39\x4F\xC4\x94\xE0\x3B\x43\x60\x0D\x7E\x02\xCB\x52\x67\x75\x5A\xCE\x64\x43\x7C\xFA\x7B\x47\x5A\xD4\x0D\xDC\x93\xB8\xC9\xBC\xAD\x63\x80\x1F\xC4\x92\xFD\x25\x16\x40\xE4\x1F\xD1\x3F\x6E\x23\x1F\x56\xF9\x72\x83\x44\x7A\xB4\x4C\xBE\x11\x91\x0D\xB3\xC7\x52\x43\x78\x4A\xA9\xBD\xF5\x75\x39\xC3\x1B\x51\xC9\xF3\x5B\xF8\xBC\x24\x95\x76\x28\x81\x25\x54\x78\x26\x4B\x79\x2B\xBD\xCA\x64\x98\x77\x7A\xE9\x12\x0E\xD9\x35\xBB\x3E\x8B\xEA\x3E\xAB\x13\xD9", 248);
    capk18.m_uiExponents = 3;
    memcpy(capk18.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk18.m_Checksum, "\xFF\xDA\x85\x8C\xB2\xAF\x08\xB7\x9D\x75\x0C\xC9\x7F\xA6\xEF\xE2\xEF\x22\x8D\xDA", 20);


    // 19
    memcpy(capk19.m_RID, "\xA0\x00\x00\x00\x65", 5);
    capk19.m_ArithInd = AIRTH_IND_RSA;
    capk19.m_CapkIndex = 0x02;
    capk19.m_uiModules = 128;
    memcpy(capk19.m_Modules, "\xBB\x7F\x51\x98\x3F\xD8\x70\x7F\xD6\x22\x7C\x23\xDE\xF5\xD5\x37\x7A\x5A\x73\x7C\xEF\x3C\x52\x52\xE5\x78\xEF\xE1\x36\xDF\x87\xB5\x04\x73\xF9\x34\x1F\x16\x40\xC8\xD2\x58\x03\x4E\x14\xC1\x69\x93\xFC\xE6\xC6\xB8\xC3\xCE\xEB\x65\xFC\x8F\xBC\xD8\xEB\x77\xB3\xB0\x5A\xC7\xC4\xD0\x9E\x0F\xA1\xBA\x2E\xFE\x87\xD3\x18\x4D\xB6\x71\x8A\xE4\x1A\x7C\xAD\x89\xB8\xDC\xE0\xFE\x80\xCE\xB5\x23\xD5\xD6\x47\xF9\xDB\x58\xA3\x1D\x2E\x71\xAC\x67\x7E\x67\xFA\x6E\x75\x82\x07\x36\xC9\x89\x37\x61\xEE\x4A\xCD\x11\xF3\x1D\xBD\xC3\x49\xEF", 128);
    capk19.m_uiExponents = 3;
    memcpy(capk19.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk19.m_Checksum, "\xB9\x73\xE9\xF3\x77\xB4\x19\xC3\x6A\xC9\x69\x6E\xD9\x5F\xFB\x25\xC8\x02\x06\x87", 20);


    // 20
    memcpy(capk20.m_RID, "\xA0\x00\x00\x00\x65", 5);
    capk20.m_ArithInd = AIRTH_IND_RSA;
    capk20.m_CapkIndex = 0x03;
    capk20.m_uiModules = 248;
    memcpy(capk20.m_Modules, "\xC9\xE6\xC1\xF3\xC6\x94\x9A\x8A\x42\xA9\x1F\x8D\x02\x24\x13\x2B\x28\x65\xE6\xD9\x53\xA5\xB5\xA5\x4C\xFF\xB0\x41\x24\x39\xD5\x4A\xEB\xA7\x9E\x9B\x39\x9A\x6C\x10\x46\x84\xDF\x3F\xB7\x27\xC7\xF5\x59\x84\xDB\x7A\x45\x0E\x6A\xA9\x17\xE1\x10\xA7\xF2\x34\x3A\x00\x24\xD2\x78\x5D\x9E\xBE\x09\xF6\x01\xD5\x92\x36\x2F\xDB\x23\x77\x00\xB5\x67\xBA\x14\xBB\xE2\xA6\xD3\xD2\x3C\xF1\x27\x0B\x3D\xD8\x22\xB5\x49\x65\x49\xBF\x88\x49\x48\xF5\x5A\x0D\x30\x83\x48\xC4\xB7\x23\xBA\xFB\x6A\x7F\x39\x75\xAC\x39\x7C\xAD\x3C\x5D\x0F\xC2\xD1\x78\x71\x6F\x5E\x8E\x79\xE7\x5B\xEB\x1C\x84\xFA\x20\x2F\x80\xE6\x80\x69\xA9\x84\xE0\x08\x70\x6B\x30\xC2\x12\x30\x54\x56\x20\x15\x40\x78\x79\x25\xE8\x6A\x8B\x28\xB1\x29\xA1\x1A\xF2\x04\xB3\x87\xCB\x6E\xE4\x3D\xB5\x3D\x15\xA4\x6E\x13\x90\x1B\xEB\xD5\xCE\xCF\x48\x54\x25\x1D\x9E\x98\x75\xB1\x6E\x82\xAD\x1C\x59\x38\xA9\x72\x84\x2C\x8F\x1A\x42\xEB\xB5\xAE\x53\x36\xB0\x4F\xF3\xDA\x8B\x8D\xFB\xE6\x06\xFC\xA8\xB9\x08\x4E\xE0\x5B\xF6\x79\x50\xBA\x89\x89\x7C\xD0\x89\xF9\x24\xDB\xCD", 248);
    capk20.m_uiExponents = 1;
    memcpy(capk20.m_Exponents, "\x03", 1);
    memcpy(capk20.m_Checksum, "\x7D\xC4\x35\xDB\xDE\x09\x3D\x1F\x0A\xD0\xBA\xE0\xFE\xA4\xDC\x12\x05\x64\x13\xDC", 20);


    // 21
    memcpy(capk21.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk21.m_ArithInd = AIRTH_IND_RSA;
    capk21.m_CapkIndex = 0x80;
    capk21.m_uiModules = 128;
    memcpy(capk21.m_Modules, "\xCC\xDB\xA6\x86\xE2\xEF\xB8\x4C\xE2\xEA\x01\x20\x9E\xEB\x53\xBE\xF2\x1A\xB6\xD3\x53\x27\x4F\xF8\x39\x1D\x70\x35\xD7\x6E\x21\x56\xCA\xED\xD0\x75\x10\xE0\x7D\xAF\xCA\xCA\xBB\x7C\xCB\x09\x50\xBA\x2F\x0A\x3C\xEC\x31\x3C\x52\xEE\x6C\xD0\x9E\xF0\x04\x01\xA3\xD6\xCC\x5F\x68\xCA\x5F\xCD\x0A\xC6\x13\x21\x41\xFA\xFD\x1C\xFA\x36\xA2\x69\x2D\x02\xDD\xC2\x7E\xDA\x4C\xD5\xBE\xA6\xFF\x21\x91\x3B\x51\x3C\xE7\x8B\xF3\x3E\x68\x77\xAA\x5B\x60\x5B\xC6\x9A\x53\x4F\x37\x77\xCB\xED\x63\x76\xBA\x64\x9C\x72\x51\x6A\x7E\x16\xAF\x85", 128);
    capk21.m_uiExponents = 3;
    memcpy(capk21.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk21.m_Checksum, "\xA5\xE4\x4B\xB0\xE1\xFA\x4F\x96\xA1\x17\x09\x18\x66\x70\xD0\x83\x50\x57\xD3\x5E", 20);


    // 22
    memcpy(capk22.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk22.m_ArithInd = AIRTH_IND_RSA;
    capk22.m_CapkIndex = 0x61;
    capk22.m_uiModules = 128;
    memcpy(capk22.m_Modules, "\x83\x4D\x2A\x38\x7C\x5A\x5F\x17\x6E\xF3\xE6\x6C\xAA\xF8\x3F\x19\x4B\x15\xAA\xD2\x47\x0C\x78\xC7\x7D\x6E\xB3\x8E\xDA\xE3\xA2\xF9\xBA\x16\x23\xF6\xA5\x8C\x89\x2C\xC9\x25\x63\x2D\xFF\x48\xCE\x95\x4B\x21\xA5\x3E\x1F\x1E\x43\x66\xBE\x40\x3C\x27\x9B\x90\x02\x7C\xBC\x72\x60\x5D\xB6\xC7\x90\x49\xB8\x99\x2C\xB4\x91\x2E\xFA\x27\x0B\xEC\xAB\x3A\x7C\xEF\xE0\x5B\xFA\x46\xE4\xC7\xBB\xCF\x7C\x7A\x17\x3B\xD9\x88\xD9\x89\xB3\x2C\xB7\x9F\xAC\x8E\x35\xFB\xE1\x86\x0E\x7E\xA9\xF2\x38\xA9\x2A\x35\x93\x55\x2D\x03\xD1\xE3\x86\x01", 128);
    capk22.m_uiExponents = 1;
    memcpy(capk22.m_Exponents, "\x03", 1);
    memcpy(capk22.m_Checksum, "\x5C\xBB\x74\xA5\x92\x61\x38\xA5\xE2\xCA\x0C\xDA\x5C\x45\x64\x35\x81\x95\x3F\xFF", 20);


    // 23
    memcpy(capk23.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk23.m_ArithInd = AIRTH_IND_RSA;
    capk23.m_CapkIndex = 0x62;
    capk23.m_uiModules = 128;
    memcpy(capk23.m_Modules, "\xB5\xCD\xD1\xE5\x36\x88\x19\xFC\x3E\xA6\x5B\x80\xC6\x81\x17\xBB\xC2\x9F\x90\x96\xEB\xD2\x17\x26\x9B\x58\x3B\x07\x45\xE0\xC1\x64\x33\xD5\x4B\x8E\xF3\x87\xB1\xE6\xCD\xDA\xED\x49\x23\xC3\x9E\x37\x0E\x5C\xAD\xFE\x04\x17\x73\x02\x3A\x6B\xC0\xA0\x33\xB0\x03\x1B\x00\x48\xF1\x8A\xC1\x59\x77\x3C\xB6\x69\x5E\xE9\x9F\x55\x1F\x41\x48\x83\xFB\x05\xE5\x26\x40\xE8\x93\xF4\x81\x60\x82\x24\x1D\x7B\xFA\x36\x40\x96\x00\x03\xAD\x75\x17\x89\x5C\x50\xE1\x84\xAA\x95\x63\x67\xB7\xBF\xFC\x6D\x86\x16\xA7\xB5\x7E\x2D\x44\x7A\xB3\xE1", 128);
    capk23.m_uiExponents = 3;
    memcpy(capk23.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk23.m_Checksum, "\xAE\x65\xCF\x80\xC8\x6D\xF6\x1D\x06\x94\xE6\xB5\x15\x75\x56\x6F\x03\x48\xFE\x12", 20);


    // 24
    memcpy(capk24.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk24.m_ArithInd = AIRTH_IND_RSA;
    capk24.m_CapkIndex = 0x64;
    capk24.m_uiModules = 160;
    memcpy(capk24.m_Modules, "\x91\x12\x3E\xCF\x02\x30\xE3\xCB\x24\x5C\x88\xDD\xFA\x3E\xE5\x7B\xC5\x8E\xD0\x0B\x36\x7B\x38\x75\xFC\xB7\x95\x48\x87\x26\x80\xF6\x01\xE8\xC8\x39\xAC\x07\x21\xBA\xB3\xB8\x9E\xD2\x16\x07\x28\x1C\x89\x19\xBF\x72\x62\x66\xEA\xB8\x48\x50\x2A\xD8\x74\xB5\x10\x7A\x4E\x65\x4E\xF6\xD3\x77\x73\x34\x3F\x46\x14\x35\xC8\x6E\x4A\x8F\x86\x6F\xB1\x8C\x7C\xBA\x49\x7B\x42\x62\x90\xC3\x8D\x19\x6E\x2A\xFF\x33\xC0\x90\x6F\x92\x96\xF2\x97\xE1\x56\xDC\x60\x2A\x5E\x65\x3C\xA1\x16\x8F\x11\x09\x26\x11\x14\xBF\x7B\xE8\x12\x7A\x3E\x80\x07\x19\x18\x30\x13\x42\x99\x39\x5C\xE2\xB3\x22\x22\x86\x67\xB7\x6E\x07\x2E\xB7\xFD\x5D\x0F\xB3\xA8\x3E\x8A\xD1\xD7\xF6\xFD\x81", 160);
    capk24.m_uiExponents = 1;
    memcpy(capk24.m_Exponents, "\x03", 1);
    memcpy(capk24.m_Checksum, "\xFF\x9C\xA5\x4E\x62\xBD\xF1\xA3\xA1\x27\xAD\x8B\x02\xFD\x79\x64\xA5\x8F\x02\xBA", 20);


    // 25
    memcpy(capk25.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk25.m_ArithInd = AIRTH_IND_RSA;
    capk25.m_CapkIndex = 0xc0;
    capk25.m_uiModules = 144;
    memcpy(capk25.m_Modules, "\xC7\xCD\xB6\xF2\xA3\xFE\x80\xA8\x83\x4C\xDD\xDD\x32\x6E\x10\x82\xAA\x22\x88\xF4\x7C\x46\x4D\x57\xB3\x47\x18\x19\x34\x31\x71\x1A\x44\x11\x91\x48\x05\x50\x44\xCF\xE3\x31\x37\x08\xBE\xD0\xC9\x8E\x1C\x58\x9B\x0F\x53\xCF\x6D\x7E\x82\x9F\xCD\x90\x6D\x21\xA9\x0F\xD4\xCB\x6B\xAF\x13\x11\x0C\x46\x85\x10\x7C\x27\xE0\x09\x81\xDB\x29\xDC\x0A\xC1\x86\xE6\xD7\x01\x57\x7F\x23\x86\x56\x26\x24\x4E\x1F\x9B\x2C\xD1\xDD\xFC\xB9\xE8\x99\xB4\x1F\x50\x84\xD8\xCC\xC1\x78\xA7\xC3\xF4\x54\x6C\xF9\x31\x87\x10\x6F\xAB\x05\x5A\x7A\xC6\x7D\xF6\x2E\x77\x8C\xB8\x88\x23\xBA\x58\xCF\x75\x46\xC2\xB0\x9F", 144);
    capk25.m_uiExponents = 3;
    memcpy(capk25.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk25.m_Checksum, "\x8B\x09\x4D\x26\x0B\xDF\x8B\xFC\x8B\x9A\x88\xB0\xC1\x77\xA4\x3F\xE2\xFA\xE7\x65", 20);


    // 26
    memcpy(capk26.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk26.m_ArithInd = AIRTH_IND_RSA;
    capk26.m_CapkIndex = 0xc1;
    capk26.m_uiModules = 248;
    memcpy(capk26.m_Modules, "\x92\xF0\x83\xCB\xE4\x6F\x8D\xCC\x0C\x04\xE4\x98\xBA\x99\x52\xBA\x9D\x4C\x09\xC8\x0D\xD2\x77\xE5\x79\xF0\x7E\x45\x77\x28\x46\xFA\x43\xDD\x3A\xB3\x1C\xC6\xB0\x8D\xD1\x86\x95\x71\x59\x49\xFB\x10\x8E\x53\xA0\x71\xD3\x93\xA7\xFD\xDB\xF9\xC5\xFB\x0B\x05\x07\x13\x87\x97\x31\x74\x80\xFC\x48\xD6\x33\xED\x38\xB4\x01\xA4\x51\x44\x3A\xD7\xF1\x5F\xAC\xDA\x45\xA6\x2A\xBE\x24\xFF\x63\x43\xAD\xD0\x90\x9E\xA8\x38\x93\x48\xE5\x4E\x26\xF8\x42\x88\x0D\x1A\x69\xF9\x21\x43\x68\xBA\x30\xC1\x8D\xE5\xC5\xE0\xCB\x92\x53\xB5\xAB\xC5\x5F\xB6\xEF\x0A\x73\x8D\x92\x74\x94\xA3\x0B\xBF\x82\xE3\x40\x28\x53\x63\xB6\xFA\xA1\x56\x73\x82\x9D\xBB\x21\x0E\x71\x0D\xA5\x8E\xE9\xE5\x78\xE7\xCE\x55\xDC\x81\x2A\xB7\xD6\xDC\xCE\x0E\x3B\x1A\xE1\x79\xD6\x64\xF3\x35\x6E\xB9\x51\xE3\xC9\x1A\x1C\xBB\xF6\xA7\xCA\x8D\x0C\x7E\xC9\xC6\xAF\x7A\x49\x41\xC5\x05\x10\x99\xB9\x78\x4E\x56\xC9\x16\x20\x67\xB8\xC3\xB1\x5C\x5F\xA4\x48\x0A\x64\x5C\xD2\x52\x6A\x69\xC8\x0B\xA8\xEF\x36\x1B\xE2\xAA\x94\x17\xDE\xFC\xE3\x5B\x62\xB0\xC9\xCF\x09\x7D", 248);
    capk26.m_uiExponents = 3;
    memcpy(capk26.m_Exponents, "\x01\x00\x01", 3);
    memcpy(capk26.m_Checksum, "\xB6\x37\x2D\xB9\x91\x9F\x8C\x6C\x9C\x88\xE8\x3D\x3C\x60\x0A\x4A\xD8\xAD\xC7\xA9", 20);


    // 27
    memcpy(capk27.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk27.m_ArithInd = AIRTH_IND_RSA;
    capk27.m_CapkIndex = 0x05;
    capk27.m_uiModules = 248;
    memcpy(capk27.m_Modules, "\x97\xCF\x8B\xAD\x30\xCA\xE0\xF9\xA8\x92\x85\x45\x4D\xDD\xE9\x67\xAA\xFB\xCD\x4B\xC0\xB7\x8F\x29\xEC\xB1\x00\x52\x86\xF1\x5F\x6D\x75\x32\xA9\xC4\x76\x60\x7C\x73\xFF\x74\x24\x31\x6D\xFC\x74\x18\x94\xAA\x52\xED\xBA\xF9\x09\x71\x9C\x7B\x53\x44\x83\x43\xB4\x5C\xF2\xF0\x0A\x8A\xBF\xB7\x8C\xEE\xBE\x84\x89\x33\xAA\xED\x97\xDB\xE8\x4F\x07\x30\xF3\x4F\xB1\xAA\x15\x28\xD3\xD6\xEC\x75\xB7\x32\x52\xA3\x0D\x0C\x71\x75\x18\xBE\x36\x45\x8A\xDD\x0F\xBF\x85\x4C\x65\x49\x7F\x3F\x54\x08\x41\x54\xB6\x0F\x51\x56\x13\x61\xEE\x8E\x85\xF7\x42\xA5\x40\x05\x52\x4C\xB0\x0F\xEB\xC3\x34\x27\x6E\x0E\x63\xDA\xD8\x6C\x07\x9A\x9A\x3D\xF5\xDD\x32\xBE\xCA\xDE\x1A\xB2\xB7\x1F\x5F\x0A\x0E\x95\xA4\x00\x0D\x01\xF1\x04\x4A\x57\x8A\xAD\x92\xE9\xFD\xE9\x2E\x3C\x6A\xA3\xDC\xD4\x91\x3D\xFA\x55\x52\x53\x7E\x7D\xE7\x5E\x24\x1F\xAE\xD4\x55\xD7\x6C\xB8\xFC\xAF\xEE\xD3\xFD\x6D\xAB\x24\xD7\xA9\xC3\x28\x52\xF8\x66\xC7\x51\xD7\x71\x0F\x49\x4A\x0D\xF1\x1B\x67\xFA\xEC\xDD\x87\xA9\xA4\xE2\xCC\x44\xF6\xF2\x7E\x46\xE3\xC0\xCC\xCD\x0F", 248);
    capk27.m_uiExponents = 1;
    memcpy(capk27.m_Exponents, "\x03", 1);
    memcpy(capk27.m_Checksum, "\xCC\xDA\xCB\x02\x6C\x93\x5D\xA3\x8F\xA9\x7E\x83\x96\xF1\xD3\x76\x99\xD9\x08\x71", 20);


    // 28
    memcpy(capk28.m_RID, "\xA0\x00\x00\x03\x33", 5);
    capk28.m_ArithInd = AIRTH_IND_RSA;
    capk28.m_CapkIndex = 0x08;
    capk28.m_uiModules = 144;
    memcpy(capk28.m_Modules, "\xB6\x16\x45\xED\xFD\x54\x98\xFB\x24\x64\x44\x03\x7A\x0F\xA1\x8C\x0F\x10\x1E\xBD\x8E\xFA\x54\x57\x3C\xE6\xE6\xA7\xFB\xF6\x3E\xD2\x1D\x66\x34\x08\x52\xB0\x21\x1C\xF5\xEE\xF6\xA1\xCD\x98\x9F\x66\xAF\x21\xA8\xEB\x19\xDB\xD8\xDB\xC3\x70\x6D\x13\x53\x63\xA0\xD6\x83\xD0\x46\x30\x4F\x5A\x83\x6B\xC1\xBC\x63\x28\x21\xAF\xE7\xA2\xF7\x5D\xA3\xC5\x0A\xC7\x4C\x54\x5A\x75\x45\x62\x20\x41\x37\x16\x96\x63\xCF\xCC\x0B\x06\xE6\x7E\x21\x09\xEB\xA4\x1B\xC6\x7F\xF2\x0C\xC8\xAC\x80\xD7\xB6\xEE\x1A\x95\x46\x5B\x3B\x26\x57\x53\x3E\xA5\x6D\x92\xD5\x39\xE5\x06\x43\x60\xEA\x48\x50\xFE\xD2\xD1\xBF", 144);
    capk28.m_uiExponents = 1;
    memcpy(capk28.m_Exponents, "\x03", 1);
    memcpy(capk28.m_Checksum, "\xEE\x23\xB6\x16\xC9\x5C\x02\x65\x2A\xD1\x88\x60\xE4\x87\x87\xC0\x79\xE8\xE8\x5A", 20);

    // sm1
    memcpy(smCapk1.m_RID, "\xA0\x00\x00\x03\x33", 5);
    smCapk1.m_ArithInd = AIRTH_IND_SM;
    smCapk1.m_CapkIndex = 0x14;
    smCapk1.m_uiModules = 64;
    memcpy(smCapk1.m_Modules, "\x16\x34\x93\x66\x88\x52\x31\x09\xC9\xB0\xFC\xE9\xF3\xD9\x4C\x8B\xDD\x7E\x55\x40\x4C\xD0\x60\x97\x10\x84\xAE\x9B\x07\x04\x80\x4D\x43\x82\x06\xE0\x03\x39\x1B\x6C\x92\xD1\x6F\xE5\xD8\x7B\x02\xFA\xC3\x00\x65\x82\x21\xC8\x86\x5C\x37\x07\xA0\x25\xC8\xBA\xCA\x13", 64);
    smCapk1.m_uiExponents = 0;

    // sm2
    memcpy(smCapk2.m_RID, "\xA0\x00\x00\x03\x33", 5);
    smCapk2.m_ArithInd = AIRTH_IND_SM;
    smCapk2.m_CapkIndex = 0x18;
    smCapk2.m_uiModules = 64;
    memcpy(smCapk2.m_Modules, "\x37\x71\x0F\xEB\x7C\xC3\x61\x77\x67\x87\x4E\x85\x50\x9C\x26\x8E\x8F\x93\x1D\x68\x77\x3E\x93\xA8\x9F\x39\xA4\x24\x7D\xFE\x2D\x28\x0F\xC5\xBC\x83\x83\x53\x88\x5B\x6D\xAD\x44\x7C\x8F\x90\x11\x6B\xD9\xD3\x14\x04\x75\x91\x98\x9F\x67\xF3\x19\x54\x4D\x42\xA4\x8B", 64);
    smCapk2.m_uiExponents = 0;

    //sm3
    memcpy(smCapk3.m_RID, "\xA0\x00\x00\x03\x33", 5);
    smCapk3.m_ArithInd = AIRTH_IND_SM;
    smCapk3.m_CapkIndex = 0x57;
    smCapk3.m_uiModules = 64;
    memcpy(smCapk3.m_Modules, "\xE8\x10\x5E\x77\x86\x1F\xD2\xEB\x72\x7C\x84\xE3\x6D\x3D\x4A\x56\x66\xBD\x0A\xDC\xE8\x78\x1F\x01\x45\xD3\xD8\x2D\x72\xB9\x27\x48\xE2\x2D\x54\x04\xC6\xC4\x1F\x3E\xC8\xB7\x90\xDE\x2F\x61\xCF\x29\xFA\xEC\xB1\x68\xC7\x9F\x5C\x86\x66\x76\x2D\x53\xCC\x26\xA4\x60", 64);
    smCapk3.m_uiExponents = 0;

    // sm4
    memcpy(smCapk4.m_RID, "\xA0\x00\x00\x03\x33", 5);
    smCapk4.m_ArithInd = AIRTH_IND_SM;
    smCapk4.m_CapkIndex = 0x58;
    smCapk4.m_uiModules = 64;
    memcpy(smCapk4.m_Modules, "\xFF\xC2\xB1\x51\x33\x20\xC2\x75\x41\x1D\xBA\xDD\x21\x88\x20\x3F\x7B\x62\x51\x9F\x8C\x7B\xA9\x8E\xF8\xAA\x9F\xD6\xD2\xE4\x75\x98\x4E\x38\x3C\x3E\x12\x78\x4B\x42\xB0\x66\x96\x0E\xEA\x0C\x8F\xC8\x09\x9E\x14\x12\x80\x55\xD6\x7A\x66\x6C\xCA\x5A\x05\x8C\x26\xA4", 64);
    smCapk4.m_uiExponents = 0;

    // 生产公钥
    memcpy(pRealCapk05.m_RID, "\xA0\x00\x00\x00\x04", 5);
    pRealCapk05.m_ArithInd = AIRTH_IND_RSA;
    pRealCapk05.m_CapkIndex = 0x05;
    pRealCapk05.m_uiModules = 176;
    memcpy(pRealCapk05.m_Modules, "\xB8\x04\x8A\xBC\x30\xC9\x0D\x97\x63\x36\x54\x3E\x3F\xD7\x09\x1C\x8F\xE4\x80\x0D\xF8\x20\xED\x55\xE7\xE9\x48\x13\xED\x00\x55\x5B\x57\x3F\xEC\xA3\xD8\x4A\xF6\x13\x1A\x65\x1D\x66\xCF\xF4\x28\x4F\xB1\x3B\x63\x5E\xDD\x0E\xE4\x01\x76\xD8\xBF\x04\xB7\xFD\x1C\x7B\xAC\xF9\xAC\x73\x27\xDF\xAA\x8A\xA7\x2D\x10\xDB\x3B\x8E\x70\xB2\xDD\xD8\x11\xCB\x41\x96\x52\x5E\xA3\x86\xAC\xC3\x3C\x0D\x9D\x45\x75\x91\x64\x69\xC4\xE4\xF5\x3E\x8E\x1C\x91\x2C\xC6\x18\xCB\x22\xDD\xE7\xC3\x56\x8E\x90\x02\x2E\x6B\xBA\x77\x02\x02\xE4\x52\x2A\x2D\xD6\x23\xD1\x80\xE2\x15\xBD\x1D\x15\x07\xFE\x3D\xC9\x0C\xA3\x10\xD2\x7B\x3E\xFC\xCD\x8F\x83\xDE\x30\x52\xCA\xD1\xE4\x89\x38\xC6\x8D\x09\x5A\xAC\x91\xB5\xF3\x7E\x28\xBB\x49\xEC\x7E\xD5\x97", 176);
    pRealCapk05.m_uiExponents = 1;
    memcpy(pRealCapk05.m_Exponents, "\x03", 1);
    memcpy(pRealCapk05.m_ExpDate, "\x20\x24\x12", 3);
    memcpy(pRealCapk05.m_Checksum, "\xEB\xFA\x0D\x5D\x06\xD8\xCE\x70\x2D\xA3\xEA\xE8\x90\x70\x1D\x45\xE2\x74\xC8\x45", 20);


    memcpy(pRealCapk08.m_RID, "\xA0\x00\x00\x00\x03", 5);
    pRealCapk08.m_ArithInd = AIRTH_IND_RSA;
    pRealCapk08.m_CapkIndex = 0x08;
    pRealCapk08.m_uiModules = 176;
    memcpy(pRealCapk08.m_Modules, "\xD9\xFD\x6E\xD7\x5D\x51\xD0\xE3\x06\x64\xBD\x15\x70\x23\xEA\xA1\xFF\xA8\x71\xE4\xDA\x65\x67\x2B\x86\x3D\x25\x5E\x81\xE1\x37\xA5\x1D\xE4\xF7\x2B\xCC\x9E\x44\xAC\xE1\x21\x27\xF8\x7E\x26\x3D\x3A\xF9\xDD\x9C\xF3\x5C\xA4\xA7\xB0\x1E\x90\x70\x00\xBA\x85\xD2\x49\x54\xC2\xFC\xA3\x07\x48\x25\xDD\xD4\xC0\xC8\xF1\x86\xCB\x02\x0F\x68\x3E\x02\xF2\xDE\xAD\x39\x69\x13\x3F\x06\xF7\x84\x51\x66\xAC\xEB\x57\xCA\x0F\xC2\x60\x34\x45\x46\x98\x11\xD2\x93\xBF\xEF\xBA\xFA\xB5\x76\x31\xB3\xDD\x91\xE7\x96\xBF\x85\x0A\x25\x01\x2F\x1A\xE3\x8F\x05\xAA\x5C\x4D\x6D\x03\xB1\xDC\x2E\x56\x86\x12\x78\x59\x38\xBB\xC9\xB3\xCD\x3A\x91\x0C\x1D\xA5\x5A\x5A\x92\x18\xAC\xE0\xF7\xA2\x12\x87\x75\x26\x82\xF1\x58\x32\xA6\x78\xD6\xE1\xED\x0B", 176);
    pRealCapk08.m_uiExponents = 1;
    memcpy(pRealCapk08.m_Exponents, "\x03", 1);
    memcpy(pRealCapk08.m_ExpDate, "\x20\x24\x12", 3);
    memcpy(pRealCapk08.m_Checksum, "\x20\xD2\x13\x12\x69\x55\xDE\x20\x5A\xDC\x2F\xD2\x82\x2B\xD2\x2D\xE2\x1C\xF9\xA8", 20);


    EMV_CapkList_Add_NoCheck_App(&capk1);
    EMV_CapkList_Add_NoCheck_App(&capk2);
    EMV_CapkList_Add_NoCheck_App(&capk3);
    EMV_CapkList_Add_NoCheck_App(&capk4);
    EMV_CapkList_Add_NoCheck_App(&capk5);
    EMV_CapkList_Add_NoCheck_App(&capk6);
    EMV_CapkList_Add_NoCheck_App(&capk7);
    EMV_CapkList_Add_NoCheck_App(&capk8);
    EMV_CapkList_Add_NoCheck_App(&capk9);
    EMV_CapkList_Add_NoCheck_App(&capk10);
    EMV_CapkList_Add_NoCheck_App(&capk11);
    EMV_CapkList_Add_NoCheck_App(&capk12);
    EMV_CapkList_Add_NoCheck_App(&capk13);
    EMV_CapkList_Add_NoCheck_App(&capk14);
    EMV_CapkList_Add_NoCheck_App(&capk15);
    EMV_CapkList_Add_NoCheck_App(&capk16);
    EMV_CapkList_Add_NoCheck_App(&capk17);
    EMV_CapkList_Add_NoCheck_App(&capk18);
    EMV_CapkList_Add_NoCheck_App(&capk19);
    EMV_CapkList_Add_NoCheck_App(&capk20);
    EMV_CapkList_Add_NoCheck_App(&capk21);
    EMV_CapkList_Add_NoCheck_App(&capk22);
    EMV_CapkList_Add_NoCheck_App(&capk23);
    EMV_CapkList_Add_NoCheck_App(&capk24);
    EMV_CapkList_Add_NoCheck_App(&capk25);
    EMV_CapkList_Add_NoCheck_App(&capk26);
    EMV_CapkList_Add_NoCheck_App(&capk27);
    EMV_CapkList_Add_NoCheck_App(&capk28);

    EMV_CapkList_Add_NoCheck_App(&smCapk1);
    //EMV_AppCapkList_Add(&smCapk2);
    EMV_CapkList_Add_NoCheck_App(&smCapk3);
    EMV_CapkList_Add_NoCheck_App(&smCapk4);

    EMV_CapkList_Add_NoCheck_App(&pRealCapk08);
    EMV_CapkList_Add_NoCheck_App(&pRealCapk05);
}

/***************************************内核参数***************************************************/
/*初始化内核配置*/
#include "pos_data.h"

void Kernel_InitPBOC(void)
{
    memset(&KERNEL_CONFIG_ICC, 0, sizeof(EMV_KERNEL_CONFIG_ICC));

    strcpy((char*)KERNEL_CONFIG_ICC.m_MagFailtoIC, POS_ENTRY_MODE_MAG_FAIL_TO_IC);///< 降级

    KERNEL_CONFIG_ICC.m_SupportSM = EMV_FALSE;      ///< 是否支持国密算法
    KERNEL_CONFIG_ICC.m_CardRefer = EMV_TRUE;       ///< 是否支持卡片参考
    KERNEL_CONFIG_ICC.m_EquippedPINPAD = EMV_TRUE;  ///< 是否外接密码键盘
    KERNEL_CONFIG_ICC.m_EnterAmtSamePAD = EMV_TRUE; ///< 金额和pin是否同一键盘
    KERNEL_CONFIG_ICC.m_ActionRequired = EMV_TRUE;  ///< 公钥更新失败,是否提醒
    KERNEL_CONFIG_ICC.m_AppNotAllow_Flag = EMV_TRUE;///< 应用不允许
    KERNEL_CONFIG_ICC.m_BlockAddFlag = EMV_TRUE;    ///< 锁定的应用是否加入候选列表(1不加入,0加入)
    KERNEL_CONFIG_ICC.m_ForcePrint = EMV_FALSE;     ///< 强制打印
    KERNEL_CONFIG_ICC.m_SupprrtShowPan = EMV_TRUE;  ///< 是否支持显示卡号
}

void Kernel_InitQPBOC(void)
{
    memset(&_QPBOC_PARAMETER, 0, sizeof(QPBOC_PARAM));

    _QPBOC_PARAMETER.m_Support_Get_Data_9F51_DF71 = EMV_TRUE;   ///< 可取9f51,df71值
    _QPBOC_PARAMETER.m_Support_Contactless  = EMV_TRUE;
    _QPBOC_PARAMETER.m_Support_QPBOC        = EMV_TRUE;     ///< qpboc
    _QPBOC_PARAMETER.m_Support_PBOC         = EMV_FALSE;    ///< 借贷记
    _QPBOC_PARAMETER.m_Offline_Only         = EMV_FALSE;    ///< 仅脱机
    _QPBOC_PARAMETER.m_Support_Online_PIN   = EMV_TRUE;     ///< 支持联机PIN
    _QPBOC_PARAMETER.m_Support_Signature    = EMV_TRUE;     ///< 支持签名
    _QPBOC_PARAMETER.m_Support_Status_Check = EMV_TRUE;     ///< 支持状态检查
    _QPBOC_PARAMETER.m_Support_CDCVM        = !DataChange.QPS_CDCVM_Flag ? EMV_FALSE : EMV_TRUE; ///< 支持CDCVM


    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCTLCheck               = 0x01;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessTransLimit        = 999999999;

    ///< CVM限额, 金额超限 会走CVM 流程. 例如 签名,输PIN.
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCVMCheck               = !DataChange.QPS_NoPIN_Flag ? 0 : 0x01;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessCVMLimit          = DataChange.QPS_PINAmtLimit;
    // 3
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCFLCheck               = 0x01;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimitExist   = 0x01;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorlimitCheck              = 0x01;
    ///< 脱机限额, 金额未超限, 会走脱机交易. 超限 会执行联机
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimit        = 0;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorLimit                   = 0;
    // 4
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveStatusCheck            = 0x01;
    // 5
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveZeroAmtCheck           = 0x01;
    _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ZeroAmtPath                  = 0x01;

    ///< 闪付凭密
    if (ENTRY_PUT_CARD == ExtraData.entryType) {
        _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCVMCheck = 0;
        _QPBOC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessCVMLimit = 0;
    }
}

void Kernel_InitAmex(void)
{
    int i;

    memset(&_AMEX_PARAMETER, 0, sizeof(EXPRESS_PARAM));

    _AMEX_PARAMETER.m_Support_Express = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_Contactless = EMV_TRUE;
    _AMEX_PARAMETER.m_Offline_Only = EMV_FALSE;
    _AMEX_PARAMETER.m_Online_Only = EMV_FALSE;
    _AMEX_PARAMETER.m_Support_Magstripe_Mode = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_Emv_Mode = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_Status_Check = EMV_TRUE;

    _AMEX_PARAMETER.m_Support_Online_PIN = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_Signature = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_Mobile_Cvm = EMV_TRUE;

    _AMEX_PARAMETER.m_Support_Alternative_Interface = EMV_FALSE;
    _AMEX_PARAMETER.m_Support_Delayed_Authorisations = EMV_FALSE;
    _AMEX_PARAMETER.m_Support_ExceptionFile = EMV_TRUE;
    _AMEX_PARAMETER.m_Support_DRL = EMV_FALSE;

    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCTLCheck = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessTransLimit = 100000;
    // 2
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCVMCheck = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessCVMLimit = 90000;
    // 3
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCFLCheck = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimitExist = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorlimitCheck = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimit = 0;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorLimit = 0;
    // 4
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveStatusCheck = 0x01;
    // 5
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveZeroAmtCheck = 0x01;
    _AMEX_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ZeroAmtPath = 0x01;

    for (i = 0; i < 16; i++){
        memset((void *)&_AMEX_PARAMETER.m_DRL[i], 0, sizeof(QVSDC_DRL));
        _AMEX_PARAMETER.m_DRL[i].m_Active = EMV_TRUE;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ActiveCTLCheck = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ContactlessTransLimit = 100000;
        // 2
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ActiveCVMCheck = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ContactlessCVMLimit = 40000;
        // 3
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ActiveCFLCheck = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ContactlessFloorLimitExist = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_FloorlimitCheck = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ContactlessFloorLimit = 0;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_FloorLimit = 0;
        // 4
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ActiveStatusCheck = 0x01;
        // 5
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ActiveZeroAmtCheck = 0x01;
        _AMEX_PARAMETER.m_DRL[i].m_RiskParam.m_ZeroAmtPath = 0x01;
    }
}

void Kernel_InitQVSDC(void)
{
    memset(&_QVSDC_PARAMETER, 0, sizeof(QVSDC_PARAM));

    _QVSDC_PARAMETER.m_Support_QVSDC = EMV_TRUE;
    _QVSDC_PARAMETER.m_Support_Contact = EMV_TRUE;
    _QVSDC_PARAMETER.m_Offline_Only = EMV_FALSE;
    _QVSDC_PARAMETER.m_Online_Only = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_Online_PIN = EMV_TRUE;
    _QVSDC_PARAMETER.m_Support_Signature = EMV_TRUE;
    _QVSDC_PARAMETER.m_Support_Online_ODA = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_IssuerScriptUpdate = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_MSD = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_CDCVM = EMV_TRUE;
    _QVSDC_PARAMETER.m_Support_ExceptionFile = EMV_TRUE;

    _QVSDC_PARAMETER.m_Support_CASH = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_CASHBACK = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_REFUND = EMV_FALSE;
    _QVSDC_PARAMETER.m_Support_DRL = EMV_FALSE;

    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCTLCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessTransLimit = 100000;
    // 2
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCVMCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessCVMLimit = 90000;
    // 3
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCFLCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimitExist = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorlimitCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimit = 0;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorLimit = 0;
    // 4
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveStatusCheck = 0x01;
    // 5
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveZeroAmtCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ZeroAmtPath = 0x01;

    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ActiveCTLCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ContactlessTransLimit = 100000;
    // 2
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ActiveCVMCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ContactlessCVMLimit = 90000;
    // 3
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ActiveCFLCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ContactlessFloorLimitExist = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_FloorlimitCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ContactlessFloorLimit = 0;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_FloorLimit = 0;
    // 4
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ActiveStatusCheck = 0x01;
    // 5
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ActiveZeroAmtCheck = 0x01;
    _QVSDC_PARAMETER.m_RiskParam_Purchase.m_RiskParam.m_ZeroAmtPath = 0x01;
}

void Kernel_InitDiscover(void)
{
    memset(&_DISCOVER_PARAMETER, 0, sizeof(DISCOVER_PARAM));

    _DISCOVER_PARAMETER.m_Offline_Only = EMV_FALSE;
    _DISCOVER_PARAMETER.m_Supported_DCVV = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Alternative_Interface = EMV_FALSE;
    _DISCOVER_PARAMETER.m_Support_CDCVM = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Contact = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Emv_Mode = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_ExceptionFile = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_IssuerScriptUpdate = EMV_FALSE;
    _DISCOVER_PARAMETER.m_Support_Magstripe_Mode = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Online_PIN = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Signature = EMV_TRUE;
    _DISCOVER_PARAMETER.m_Support_Status_Check = EMV_TRUE;

    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCTLCheck = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessTransLimit = 100000;
    // 2
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCVMCheck = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessCVMLimit = 90000;
    // 3
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveCFLCheck = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimitExist = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorlimitCheck = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ContactlessFloorLimit = 0;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_FloorLimit = 0;
    // 4
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveStatusCheck = 0x01;
    // 5
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ActiveZeroAmtCheck = 0x01;
    _DISCOVER_PARAMETER.m_RiskParam_Default.m_RiskParam.m_ZeroAmtPath = 0x01;
}

void Kernel_InitMIR(void)
{
    memset(&_MIR_PARAMETER, 0, sizeof(MIR_PARAMETER));

    _MIR_PARAMETER.m_Support_Contactless = EMV_TRUE;
    _MIR_PARAMETER.m_Offline_Only = EMV_FALSE;
    _MIR_PARAMETER.m_Support_Online_PIN = EMV_TRUE;
    _MIR_PARAMETER.m_Support_Signature = EMV_TRUE;
    _MIR_PARAMETER.m_Support_CDCVM = EMV_TRUE;
    _MIR_PARAMETER.m_Delayed_Authorization = EMV_FALSE;
    _MIR_PARAMETER.m_Support_ExceptionFile = EMV_TRUE;
    _MIR_PARAMETER.m_Unable_Online = EMV_FALSE;

    _MIR_PARAMETER.m_ActiveCTLCheck = EMV_TRUE;
    _MIR_PARAMETER.m_ContactlessTransLimit_Cvm = 100000;
    _MIR_PARAMETER.m_ContactlessTransLimit_NoCvm = 120000;
    _MIR_PARAMETER.m_ActiveCVMCheck = EMV_TRUE;
    _MIR_PARAMETER.m_ContactlessCVMLimit = 300000;
    _MIR_PARAMETER.m_ActiveCFLCheck = EMV_TRUE;
    _MIR_PARAMETER.m_ContactlessFloorLimit = 0;
    _MIR_PARAMETER.m_FloorLimit = 0;
}

void Kernel_InitMastrt(void)
{
    memset(&_MASTRT_PARAM, 0, sizeof(MASTRT_PARAM));

    _MASTRT_PARAM.m_Support_Signature = EMV_TRUE;
    _MASTRT_PARAM.m_Support_Online_PIN = EMV_TRUE;
    _MASTRT_PARAM.m_Support_NO_CVM = EMV_TRUE;
    _MASTRT_PARAM.m_ContactlessTransLimitOdCvm = 100000;
    _MASTRT_PARAM.m_ContactlessTransLimitNoODCvm = 100000;
    _MASTRT_PARAM.m_ContactlessFloorLimit = 0;
    _MASTRT_PARAM.m_ContactlessCVMLimit = 90000;
}

void initKernelParam(void)
{
    memset(&TERMINAL_INFO, 0, sizeof(EMV_TERMINAL_INFO));
    memset(&KERNEL_CONFIG, 0, sizeof(EMV_KERNEL_CONFIG));

    strcpy(TERMINAL_INFO.m_TerminalID, (char *)DataConstant.TID);
    strcpy(TERMINAL_INFO.m_TerminalCountryCode, "0156");
    strcpy(TERMINAL_INFO.m_TerminalEntryMode, "02");

    strcpy(TERMINAL_INFO.m_Merchant_ID, (char *)DataConstant.MID);
    strcpy(TERMINAL_INFO.m_Merchant_Category_Code, "0001");
    strcpy(TERMINAL_INFO.m_Merchant_Location, "Shenzhen China");
    strcpy(TERMINAL_INFO.m_Trans_Currency_Code, "0156");
    memcpy(TERMINAL_INFO.m_IFDSerialNumber, "90000001", 8); // ifd
    TERMINAL_INFO.m_Trans_Currency_Exp = 0x00;  //0x02
    strcpy(TERMINAL_INFO.m_Trans_Ref_Currency_Code, "0156");
    TERMINAL_INFO.m_Trans_Ref_Currency_Exp = 0x02;
    TERMINAL_INFO.m_ReferCurrCon = 1000;

    KERNEL_CONFIG.m_PSE = EMV_TRUE;
    KERNEL_CONFIG.m_CardHolderConfirm = EMV_TRUE;
    KERNEL_CONFIG.m_PreferredDisplayOrder = EMV_FALSE; //NO implemented
    KERNEL_CONFIG.m_LanguateSelect = EMV_TRUE;
    KERNEL_CONFIG.m_RevocationOfIssuerPublicKey = EMV_TRUE;
    KERNEL_CONFIG.m_Default_DDOL = EMV_TRUE;
    KERNEL_CONFIG.m_Bypass_PIN_Entry = EMV_TRUE;
    KERNEL_CONFIG.m_Subsequent_Bypass_PIN_Entry = EMV_TRUE;
    KERNEL_CONFIG.m_Getdata_For_PIN_Try_Counter = EMV_TRUE;
    KERNEL_CONFIG.m_Floor_Limit_Checking = EMV_TRUE;
    KERNEL_CONFIG.m_Random_Transaction_Selection = EMV_TRUE; //unvaliable for the offline only terminal
    KERNEL_CONFIG.m_Velocity_Checking = EMV_TRUE;
    KERNEL_CONFIG.m_TransactionLog = EMV_TRUE;
    KERNEL_CONFIG.m_Exception_File = EMV_TRUE;
    KERNEL_CONFIG.m_TerminalActionCode = EMV_TRUE;

    KERNEL_CONFIG.m_DefaultActionCodeMethod = EMV_DEFAULT_ACTION_CODE_AFTER_GAC1;

    KERNEL_CONFIG.m_TAC_IAC_Default_SkipedWhenUnableToGoOnline = EMV_FALSE;
    KERNEL_CONFIG.m_CDA_FailureDetectedPriorTerminalActionAnalysis = EMV_TRUE;;

    KERNEL_CONFIG.m_CDA_Method = EMV_CDA_MODE1;

    KERNEL_CONFIG.m_ForcedOnline = EMV_TRUE;    ///< 强制联机
    KERNEL_CONFIG.m_ForcedAcceptance = EMV_FALSE;
    KERNEL_CONFIG.m_Advices = EMV_TRUE;
    KERNEL_CONFIG.m_Issuer_Referral = EMV_TRUE;
    KERNEL_CONFIG.m_BatchDataCapture = EMV_FALSE;
    KERNEL_CONFIG.m_OnlineDataCapture = EMV_TRUE;
    KERNEL_CONFIG.m_Default_TDOL = EMV_TRUE;
    KERNEL_CONFIG.m_Terminal_SupportAccountTypeSelection = EMV_FALSE;//No Implemented;


    strcpy(KERNEL_CONFIG.m_TerminalType, "22");
    //E0F8C8
    strcpy(KERNEL_CONFIG.m_TerminalCapabilities, "E0E9C8");// 只支持sda,E0E980 E0E9C8
    strcpy(KERNEL_CONFIG.m_AddtionalTerminalCapabilities, "FF00A0E001");    //FF00F0F001


    Kernel_InitPBOC();      ///< IC参数
    Kernel_InitQPBOC();     ///< 非接参数
    Kernel_InitAmex();      ///<
    Kernel_InitQVSDC();     ///<
    Kernel_InitDiscover();  ///<
    Kernel_InitMIR();       ///<
    Kernel_InitMastrt();    ///<
}

/*加载终端内核参数*/
void EMV_LoadParameters(void)
{
    initKernelParam();
    //设置终端参数
    EMV_SetKernelConfig_App(&KERNEL_CONFIG);
    EMV_SetTerminalInfo_App(&TERMINAL_INFO);
    EMV_Cantact_Kernel_Set_Config(&KERNEL_CONFIG_ICC);

    EMV_SetQPBOCParam_App(&_QPBOC_PARAMETER);
    EMV_SetQVSDCParam_App(&_QVSDC_PARAMETER);
    EMV_SetAMEXParam_App(&_AMEX_PARAMETER);
    EMV_SetDISCOVERParam_App(&_DISCOVER_PARAMETER);
    EMV_SetMIRParam_App(&_MIR_PARAMETER);
    EMV_SetMASTRTParam_App(&_MASTRT_PARAM);
}

/*保存内核参数*/
void EMV_SaveParameters(void)
{

}

/*删除aid文件*/
void EMV_DeleteAidParam(void)
{
    FsRemove(AID_FILE_NAME);
}

/*从文件中加载aid参数 896字节*/
void EMV_LoadAidParam(void)
{
    int uiFileSize = -1;
    int iFd = -1;
    unsigned int i, count;
    EMV_AID_ITEM item;
    const char *pFileName = AID_FILE_NAME;

    if (EMV_AidList_GetCount_App() > 0) {
        return;
    }

    EMV_AidList_Clear_App();
    uiFileSize = FsSize(pFileName);
    if (uiFileSize%(sizeof(EMV_AID_ITEM))) {
        FsRemove(pFileName);
    }
    else {
        iFd = FsOpen(pFileName, O_RO);
    }

    if (iFd >= 0) {
        count = uiFileSize/sizeof(EMV_AID_ITEM) > MAX_AID_LIST ? MAX_AID_LIST : uiFileSize/sizeof(EMV_AID_ITEM);
        for (i = 0; i < count; i++) {
            memset(&item, 0, sizeof(item));
            if (FsRead(iFd, &item, sizeof(EMV_AID_ITEM)) < 0) {
                EMV_AidList_Clear_App();
                break;
            }
            EMV_AidList_Add_App(&item);
        }
    }
    else {
        initAid();
    }

    if (iFd >= 0) {
        FsClose(iFd);
    }
}

/*保存aid到文件中(先add)*/
void EMV_SaveAidParam(void)
{
    int iFd = -1;
    unsigned int i, count;
    EMV_AID_ITEM item;
    const char *pFileName = AID_FILE_NAME;

    count = EMV_AidList_GetCount_App();
    if (count > 0) {
        FsRemove(pFileName);
        if ((iFd = FsOpen(pFileName, O_CREATE)) >= 0) {
            for (i = 0; i < count; i++) {
                memset(&item, 0, sizeof(item));
                EMV_AidList_Get_App(&item, i);
                if (FsWrite(iFd, &item, sizeof(EMV_AID_ITEM)) < 0) {
                    break;
                }
            }
        }

        if (iFd >= 0) {
            FsClose(iFd);
        }
    }
}


/*删除回收公钥文件*/
void EMV_DeleteIpkParam(void)
{
    FsRemove(IPK_FILE_NAME);
}

/**加载回收列表*/
void EMV_LoadIpkParam(void)
{
    EMV_RevoIPKList_Clear_App();
}

/*保存回收公钥到文件中*/
void EMV_SaveIpkParam(void)
{

    return;
}

/*删除黑名单文件*/
void EMV_DeleteExtParam(void)
{
    FsRemove(EXT_FILE_NAME);
}

/*从文件中加载黑名单*/
void EMV_LoadExtParam(void)
{
    EMV_ExceptList_Clear_App();
}

/*保存黑名单参数到文件*/
void EMV_SaveExtParam(void)
{

    return;
}

/*删除capk文件*/
void EMV_DeleteCapkParam(void)
{
    FsRemove(CAPK_FILE_NAME);
}

/***************************************capk***************************************************/
/*从文件中加载capk*/
void EMV_LoadCapkParam(void)
{
    int iRet = -1;
    int uiFileSize = -1;
    int iFd = -1;
    unsigned int i, count;
    EMV_CAPK_ITEM item;
    const char *pFileName = CAPK_FILE_NAME;

#if DEBUG_EMV_STORAGE
    LOGD("[%s:%5d]>>>", __func__, __LINE__);
#endif
    if (EMV_CapkList_GetCount_App() > 0) {
        return;
    }

    EMV_CapkList_Clear_App();
    uiFileSize = FsSize(pFileName);
    if (uiFileSize%(sizeof(EMV_CAPK_ITEM))) {
        FsRemove(pFileName);
    }
    else {
        iFd = FsOpen(pFileName, O_RO);
    }

    if (iFd >= 0) {
        count = uiFileSize/sizeof(EMV_CAPK_ITEM) > MAX_CAPK_LIST ? MAX_CAPK_LIST : uiFileSize/sizeof(EMV_CAPK_ITEM);
        for (i = 0; i < count; i++) {
            memset(&item, 0, sizeof(item));
            if (FsRead(iFd, &item, sizeof(EMV_CAPK_ITEM)) < 0) {
                EMV_CapkList_Clear_App();
                break;
            }

            iRet = EMV_CapkList_Add_App(&item);
#if DEBUG_EMV_STORAGE
            LOGD("[%5d]add capk:%d", __LINE__, iRet);
            logger_serial_dump_buff("add capk", (unsigned char *)&item, sizeof(item));
#endif
            if (iRet) {
                break;
            }
        }
    }

    if (iFd >= 0) {
        FsClose(iFd);
    }

    if (iRet) {
        EMV_CapkList_Clear_App();
        initCapk();
    }
}

/*保存capk到文件中 294*/
void EMV_SaveCapkParam(void)
{
    int iFd = -1;
    unsigned int i, count;
    EMV_CAPK_ITEM item;
    const char *pFileName = CAPK_FILE_NAME;

#if DEBUG_EMV_STORAGE
    LOGD("[%s:%5d]>>>", __func__, __LINE__);
#endif
    count = EMV_CapkList_GetCount_App();
#if DEBUG_EMV_STORAGE
    LOGD("[%s:%5d]>>>count:%d", __func__, __LINE__, count);
#endif
    if (count > 0) {
        FsRemove(pFileName);
        if ((iFd = FsOpen(pFileName, O_CREATE)) >= 0) {
            for (i = 0; i < count; i++) {
                memset(&item, 0, sizeof(item));
                EMV_CapkList_Get_App(&item, i);
#if DEBUG_EMV_STORAGE
                logger_serial_dump_buff("add capk", (unsigned char *)&item, sizeof(item));
#endif
                if (FsWrite(iFd, &item, sizeof(EMV_CAPK_ITEM)) < 0) {
                    break;
                }
            }
        }

        if (iFd >= 0) {
            FsClose(iFd);
        }
    }
}

/*加载aid,capk,ipk,expfile 个数*/
void EMV_LoadCount(void)
{
    EMV_LoadAidParam();
    EMV_LoadIpkParam();
    EMV_LoadExtParam();
    EMV_LoadCapkParam();
}

/*交易时,初始化参数*/
void CT_Start_Trans_InitParam(void){

    //Contact_Start_Clear_Param(不调用该方法,不EMV_LoadCount)
    ///< AID参数加载放到开机加载一次避免反复加载
    //EMV_LoadCount();                // 加载aid等参数
    EMV_LoadParameters();           // 加载内核配置

    //EMV_TRUE
    EMV_Set_AbleLog(DataConstant.emvDebug);     // 默认输入日志
}

