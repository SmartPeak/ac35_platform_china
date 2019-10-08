#include "bwsdk_api.h"
#include "logger.h"
#include "applib_def.h"
#include "applib.h"
#include "mmi_input.h"
#include "mmi_display.h"
#include "multilingual.h"
#include "sysFile.h"

#include "device.h"
#include "builtinfo.h"
#include "trans.h"

#ifdef TAG
#undef TAG
#endif
#define TAG "main_code"

///< power keypress event
void main_powerKey(void *p)
{
    ///< stop man gui thread
    mmi_backupScreen();

    ///< stop TTS Abort
    TTS_Abort();

    mmi_clearLine(DISP_ClearALL);
    mmi_display(DISP_Line2, 1, AMSG_EnterPowerOff);
    mmi_display(DISP_Line3, 1, AMSG_ClearReboot);
    mmi_display(DISP_Line4, 1, AMSG_CancelBack);
    while (1)
    {
        switch(mmi_inputWaitKeypress(60))
        {
        case KEY_NONE:
        case KEY_CANCEL:
            break;
        case KEY_ASCII1:
            ScanBarStop();
            ScanBarLightSet(SCANBAR_RLED|SCANBAR_WLED, 0);
            Sleep(100);

            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_PowerOff);
            Sleep(500);
            BWSP_Power(0);
            PowerOff();
            break;
        case KEY_ASCII2:
            ScanBarStop();
            ScanBarLightSet(SCANBAR_RLED|SCANBAR_WLED, 0);
            Sleep(100);

            mmi_clearLine(DISP_ClearALL);
            mmi_display(DISP_VCenter, DISP_HCenter, AMSG_Rebooting);
            Sleep(500);
            BWSP_Power(0);
            PowerReboot();
            break;
        default:
            continue;
        }
        Sleep(10);
        break;
    }
    mmi_freshScreen();
}

///< applib param init
void AppLib_InitParam(tsAppLibParm *pParam)
{
    sdm_start(PORT_USB_AT);

    ///< app version
    pParam->appVersion = _APP_VERSION;

    /*!< ------------------- color ----------------------- */
    ///< font color
    pParam->fontColor           = MERCURY_BLACK;
    ///< font forecolor
    pParam->fontbackgroundColor = MERCURY_WHITE;
    ///< bgcolor
    pParam->backgroundColor     = MERCURY_WHITE;
    ///< top bar bgcolor
    pParam->barbroundColor      = MERCURY_IRON_GRAY;
    ///< background-image
//    pParam->backgroundImg       = "bgcommonlog";

//    pParam->callback_powerKey   = main_powerKey;

    ///< set language
    multilingual_setLanguage(LANG_CN);
}

void main_CheckFileExist(const char *pFileList)
{
    char *p = (char *)pFileList;
    int iLen = 0;
    char mFile[40];

    memset(mFile, 0, sizeof(mFile));
    while (*pFileList != '\0')
    {
        if (*pFileList == ',')
        {
            iLen = (pFileList - p);

            memset(mFile, 0, sizeof(mFile));
            memcpy(mFile, p, iLen);
            if (FsSize(mFile) <= 0) {
                do
                {
                    mmi_clearLine(DISP_ClearALL);
                    mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, "Warning");

                    mmi_display(DISP_Line3, DISP_HCenter, "\"%s\"", mFile);
                    mmi_display(DISP_Line4, DISP_HCenter, "file not exist");
                    mmi_display(DISP_Line5, DISP_HCenter, "Please download!!!");
                    SpSysBeepOn(1000, 200);
                } while(KEY_ENTER != mmi_inputWaitKeypress(2));
            }
            p = (char *)pFileList;
            p++;
        }
        pFileList++;
    }
    mmi_clearLine(DISP_ClearALL);
}

///< check files exist
static int Check_ResourceFile(void)
{
    main_CheckFileExist("hzk24s,gbk16x16,gbkunicodemap,resource,");
    main_CheckFileExist("asc_16x8,asc_16x8_B,asc_24x12,asc_24x12_B,");
    main_CheckFileExist("hz_16x16,hz_16x16_B,hz_24x24_B,");

    return SUCCESS;
}

///< power on event
void Main_PownOn(void)
{
    extern int POS_DataInit(void);
    extern void EMV_LoadCount(void);

    ///< close dormancy
    SetSysSleepLevel(SLEEP_LEVEL_NOSLEEP);

    ///< Register Power Key LongPress Callback
    RegisterPowerKeyLongPressCallback(main_powerKey, NULL);

    ///< set scanbar param
    scanbar_param_t barcfg = {1, BARSCAN_MODE_ONCE, 0};
    ScanBarSetParam(&barcfg);

    ///< data file init
    POS_DataInit();

    ///< load emv param
    EMV_LoadCount();

    Sleep(2*1000);

    ///< check files exist
    Check_ResourceFile();

    ///< restore dormancy
    SetSysSleepLevel((sleep_level_t)SystemSave.sysSleepType);
}

///< main entry
void main_code(ULONG argc, LPVOID lpThreadParameter)
{
    extern char *UFile_GetResource(char* sourceName, int* width, int* height);
    unsigned char *imgData = NULL;
    unsigned short imgW = 0;
    unsigned short imgH = 0;

    Main_PownOn();          ///< pown on event

    ///< get standby logo
    imgData = (unsigned char *)UFile_GetResource("yinglian", (int *)&imgW, (int *)&imgH);
    while (1)
    {
        trans_standby(imgData, imgW, imgH);
    }
}

