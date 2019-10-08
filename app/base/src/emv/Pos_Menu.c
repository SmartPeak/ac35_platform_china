#include "bwsdk_api.h"
#include "applib_def.h"
#include "mmi_display.h"
#include "mmi_input.h"
#include "Pos_Menu.h"

#define SLEEP_TIME          150

#if !defined(EMV_TRUE)
#define EMV_TRUE  1
#endif

#if !defined(EMV_FALSE)
#define EMV_FALSE  0
#endif

int Menu_Select(char *pszTitle, int uiMenuCount, char **ppMenus, int iDefaultSelect, char bAllowCancel, Fn_Menu_Process pProcess, void * pvProcessParam)
{
    int iRetval = iDefaultSelect;
    char *C_MARK_SELECT = "=>";
    char *C_MARK_UNSELECT = "  ";
    int  key;
    char bLoop;
    int i;
    int uiStart;

    if (iDefaultSelect < 0) {
        iDefaultSelect = 0;
    }

    if (uiMenuCount <= 0) {
        return -1;
    }

    bLoop = EMV_TRUE;
    while (EMV_TRUE == bLoop)
    {
        mmi_clearLine(DISP_ClearALL);
        mmi_display(DISP_Line1, DISP_HCenter, pszTitle);
        uiStart = (iDefaultSelect / 6) * 6;
        ///<  display menus
        for (i = 0; i < 6; i++)
        {
            if (uiStart + i < uiMenuCount)
            {
                if (uiStart + i == (int)iDefaultSelect)
                {
                    mmi_display((DISP_VAlign)(i + 2), 0, "%s%s", C_MARK_SELECT, ppMenus[uiStart + i]);
                }
                else
                {
                    mmi_display((DISP_VAlign)(i + 2), 0, "%s%s", C_MARK_UNSELECT, ppMenus[uiStart + i]);
                }
            }
            else
            {
                break;
            }
        }


    LOOP:
        if (NULL != pProcess)
        {
            pProcess(pvProcessParam);
        }

        if (!KbHit())
        {
            key = mmi_inputGetKeypress();
            switch (key)
            {
            case KEY_NONE:
                Sleep(SLEEP_TIME);
                goto LOOP;
#if defined(QR200) || defined(QR80ST)
            case KEY_ASCII8:
                    iDefaultSelect--;
                    if (iDefaultSelect < 0)
                    {
                        iDefaultSelect = uiMenuCount - 1;
                    }
                    break;
            case KEY_ASCII2:
                    iDefaultSelect++;
                    if ((unsigned int)iDefaultSelect >= uiMenuCount)
                    {
                        iDefaultSelect = 0;
                    }
                    break;
#elif defined(QR100) || defined(QR300) || defined(QR150) || defined(P90)
            case KEY_ASCII2:
            case KEY_UP:
                    iDefaultSelect--;
                    if (iDefaultSelect < 0)
                    {
                        iDefaultSelect = uiMenuCount - 1;
                    }
                    break;
            case KEY_ASCII8:
            case KEY_DOWN:
                    iDefaultSelect++;
                    if ((unsigned int)iDefaultSelect >= uiMenuCount)
                    {
                        iDefaultSelect = 0;
                    }
                    break;
#endif
            case KEY_CANCEL:
                if (EMV_TRUE == bAllowCancel)
                {
                    iDefaultSelect = -1;
                    bLoop = EMV_FALSE;
                }
                break;
            case KEY_ENTER:
                bLoop = EMV_FALSE;
                break;
            default:
                Sleep(SLEEP_TIME);
                goto LOOP;
            }
        }
        else
        {
            Sleep(SLEEP_TIME);
            goto LOOP;
        }
    }
    Sleep(SLEEP_TIME+20);
    iRetval = iDefaultSelect;
    return iRetval;
}

