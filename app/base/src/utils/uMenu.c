#include "bwsdk_api.h"
#include "uMenu.h"
#include "applib_def.h"
#include "applib_err.h"
#include "mmi_display.h"
#include "mmi_input.h"

#define DEBUG_API_MENU              0
#if DEBUG_API_MENU
#include "logger.h"
#ifdef TAG
#undef TAG
#endif
#define TAG __func__
#endif

#define LINEPIX     32
#define FONTPIX     24

/*==============================================================*/
static int __UMenu_GetMaxStrAndMaxLine(unsigned int *pMaxStingLen, unsigned int *pMaxLine)
{
    tsScrInfo mScrInfo;

    if (!pMaxStingLen || !pMaxLine) {
        return ERR_PARAM;
    }

    memset(&mScrInfo, 0, sizeof(tsScrInfo));
    ScrGetStatus(&mScrInfo);

    *pMaxLine = (unsigned int)((mScrInfo.Height / LINEPIX) - 1);
    *pMaxStingLen = (unsigned int)(mScrInfo.Width / (FONTPIX / 2));
    return SUCCESS;
}

int UMenu_CheckPgUp(int key)
{
#if defined(QR300)
    if (KEY_FUNC == key)
#elif defined(QR100)
    if (KEY_ALPHA == key)
#elif defined(P90)
    if (KEY_UP == key)
#else
    if (KEY_FUNC == key || KEY_F1 == key)
#endif
    {
        return true;
    }
    return false;
}

int UMenu_CheckPgDn(int key)
{
#if defined(QR300)
    if (KEY_ALPHA == key)
#elif defined(QR100)
    if (KEY_FUNC == key)
#elif defined(P90)
    if (KEY_DOWN == key)
#else
    if (KEY_ENTER == key || KEY_F2 == key)
#endif
    {
        return true;
    }
    return false;
}

static int __UMenu_DisplayTitle(const char *pText, unsigned char isAntiColor)
{
    if (isAntiColor) {
        return mmi_displayOfBlackBg(DISP_Line1, DISP_HCenter, pText);
    }
    return mmi_display(DISP_Line1, DISP_HCenter, pText);
}

static int __UMENU_DisplayMenuGroup(teMenuStyle menuStyle,
                                    unsigned int pageIndex,
                                    unsigned int *pageCount,
                                    unsigned int maxLine,
                                    unsigned int maxLen,
                                    tsMenu *pMenu)
{
    unsigned int line = DISP_Line1;
    unsigned int i, m_index, m_number;
    unsigned int count;
    unsigned int column;


    if (!pMenu) {
        return ERR_PARAM;
    }

    mmi_clearLine(DISP_ClearALL);
    if (pMenu->title.text) {
        line = __UMenu_DisplayTitle((const char *)pMenu->title.text, pMenu->title.isAntiColor);
    }

    count = pMenu->itemCount;
    switch(menuStyle)
    {
    case MENU_STYLE_201:
    case MENU_STYLE_202:
        *pageCount = pMenu->itemCount / (maxLine*2) + ((pMenu->itemCount % (maxLine*2)) ? 1 : 0);
        for (i = 0; i < (maxLine*2); i++)
        {
            m_index = (pageIndex * maxLine) + i;
            m_number = (MENU_STYLE_202 != menuStyle) ? m_index : i;
            if (m_index >= count) {
                break;
            }

            if (i%2) {
                column = (maxLen/2)+1;
                if (strlen((char *)pMenu->item[m_index].text)+2 > (maxLen/2)) {
                    column = maxLen-strlen((char *)pMenu->item[m_index].text)-2;
                }

//                LOGD("[%s-%d]>>>>[%d/%d/%d]%s", __func__, __LINE__, maxLen, strlen(pMenu->item[m_index].text), column, pMenu->item[m_index].text);
                line = mmi_display((DISP_VAlign)line, column, "%d.%s", m_number+1, pMenu->item[m_index].text);
            }
            else {
                mmi_display((DISP_VAlign)line, 0, "%d.%s", m_number+1, pMenu->item[m_index].text);
            }
        }
        break;
    case MENU_STYLE_101:
    case MENU_STYLE_102:
    default:
        *pageCount = pMenu->itemCount / maxLine + ((pMenu->itemCount % maxLine) ? 1 : 0);
        for (i = 0; i < maxLine; i++)
        {
            m_index = (pageIndex * maxLine) + i;
            m_number = (MENU_STYLE_102 != menuStyle) ? m_index : i;
            if (m_index >= count) {
                break;
            }
            line = mmi_display((DISP_VAlign)line, 0, "%d.%s", m_number+1, pMenu->item[m_index].text);
        }
        break;
    }
    return SUCCESS;
}

static int __UMenu_SelectKey(teMenuStyle menuStyle,
                             int key,
                             unsigned int pageIndex,
                             unsigned int maxLine,
                             unsigned int count,
                             unsigned int *pSelectIndex)
{
    int iRet = false;
    unsigned int iKey = 0;
    unsigned int iIndex = 0;

    if (!pSelectIndex) {
        return false;
    }

    if (key < KEY_ASCII1 || key > KEY_ASCII9) {
        return false;
    }

    iKey = (unsigned int)(key - '0');
    switch(menuStyle)
    {
    case MENU_STYLE_101:
        if (iKey > 0 && (iKey - 1) < count) {
            iIndex = iKey - 1;
            iRet = true;
        }
        break;
    case MENU_STYLE_102:
        if (iKey > 0 && (iKey - 1) < maxLine) {
            iIndex = (iKey - 1) + (pageIndex*maxLine);
            if (iIndex < count) {
                iRet = true;
            }
        }
        break;
    case MENU_STYLE_201:
    case MENU_STYLE_202:
        if (iKey > 0 && (iKey - 1) < (maxLine*2)) {
            iIndex = (iKey - 1) + (pageIndex*(maxLine*2));
            if (iIndex < count) {
                iRet = true;
            }
        }
        break;
    }

    if (true == iRet) {
        *pSelectIndex = iIndex;
    }
    return iRet;
}

int UMenu_DispMenu(teMenuStyle menuStyle, unsigned int timeout, tsMenu *pMenu)
{
    int iRet = SUCCESS;
    int iKey;
    unsigned char bRedraw;
    unsigned int maxLen, maxLine;
    unsigned int pageIndex, pageCount, selectIndex;

    ///< check menu count
    if(!pMenu->itemCount) {
        return ERR_PARAM;
    }

    ///< get max string len and max line
    if (SUCCESS == iRet) {
        iRet = __UMenu_GetMaxStrAndMaxLine(&maxLen, &maxLine);
    }

    if (pMenu->title.text) {
        maxLine -= 1;
    }

    pageIndex = 0;
    pageCount = 0;
    bRedraw = true;
    while(1)
    {
        if (pMenu->checkFunc) {
            iRet = pMenu->checkFunc();
            if (iRet != SUCCESS) {
                return iRet;
            }
        }

        ///< display menu
        if (bRedraw) {
            iRet = __UMENU_DisplayMenuGroup(menuStyle, pageIndex, &pageCount, maxLine, maxLen, pMenu);
            bRedraw = false;
        }

        ///< wait key
        iKey = mmi_inputWaitKeypress(timeout);
        if (iKey == KEY_CANCEL) {                   ///< cancel
            pMenu->isExit = true;
            return ERR_CANCEL;
        }
        else if (iKey == KEY_NONE) {                ///< timeout
            pMenu->isExit = true;
            return ERR_TIMEOUT;
        }
        else if (true == UMenu_CheckPgUp(iKey)) {   ///< pgUp
            if (pageIndex > 0)
            {
                pageIndex--;
                bRedraw = true;
            }
        }
        else if (true == UMenu_CheckPgDn(iKey)) {   ///< pgDn
            if (pageIndex < pageCount - 1) {
                pageIndex++;
                bRedraw = true;
            }
        }
        else if (true == __UMenu_SelectKey(menuStyle, iKey, pageIndex, maxLine, pMenu->itemCount, &selectIndex))
        {
            if (pMenu->item[selectIndex].pfnProc) {
                if (pMenu->getValue) {
                    *pMenu->getValue = pMenu->item[selectIndex].value;
                }
                return pMenu->item[selectIndex].pfnProc();
            }
        }
    }
}

int UMenu_Init(unsigned char *getValue, tsMenu *pMenu)
{
    memset(pMenu, 0, sizeof(tsMenu));
    if (getValue) {
        pMenu->getValue = getValue;
    }
    return SUCCESS;
}

int UMenu_SetTitle(const char *pText, unsigned char isAntiColor, tsMenu *pMenu)
{
    if (!pMenu || !pText) {
        return ERR_PARAM;
    }

    pMenu->title.isAntiColor = isAntiColor;
    pMenu->title.text = (unsigned char *)pText;
    return SUCCESS;
}

int UMenu_AddCaption(const char *pText, tsMenu *pMenu)
{
    if (!pMenu || !pText) {
        return ERR_PARAM;
    }

    pMenu->caption.text  = (unsigned char *)pText;
    return SUCCESS;
}

int UMenu_AddQKey(unsigned char ucKey, int (*callback)(void), tsMenu *pMenu)
{
    if (!pMenu) {
        return ERR_PARAM;
    }
    else if(pMenu->qKeyCount > 8) {
        return ERR_PARAM;
    }

    pMenu->QKey[pMenu->qKeyCount].key = ucKey;
    pMenu->QKey[pMenu->qKeyCount].pfnProc = callback;
    pMenu->qKeyCount++;
    return SUCCESS;
}

int UMenu_AddMenu(const char *pText, int (*callback)(void), unsigned int value, unsigned char *enableFlag, tsMenu *pMenu)
{
    if (!pMenu) {
        return ERR_PARAM;
    }
    else if(pMenu->itemCount > sizeof(pMenu->item)/sizeof(pMenu->item[0])) {
        return ERR_PARAM;
    }
    else if (enableFlag && *enableFlag == 0) {
        return SUCCESS;
    }

    pMenu->item[pMenu->itemCount].text = (unsigned char *)pText;
    pMenu->item[pMenu->itemCount].pfnProc = callback;
    pMenu->item[pMenu->itemCount].value = value;
    pMenu->itemCount++;
    return SUCCESS;
}

