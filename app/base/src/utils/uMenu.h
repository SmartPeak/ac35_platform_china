#ifndef API_MENU_H
#define API_MENU_H

#define API_MENU_MAX_ITEM           25
#if !defined(QR100)
#define API_MENU_MAX_LINE           5
#else
#define API_MENU_MAX_LINE           9
#endif

typedef enum _MENU_STYLE
{
    MENU_STYLE_101      = 0,        ///< 1.XX
                                    ///< 2.XX
                                    ///< 3.XX
                                    ///< 4.XX

                                    ///< 5.XX
                                    ///< 6.XX
                                    ///< 7.XX
                                    ///< 8.XX

    MENU_STYLE_102,                 ///< 1.XX
                                    ///< 2.XX
                                    ///< 3.XX
                                    ///< 4.XX

                                    ///< 1.XX
                                    ///< 2.XX
                                    ///< 3.XX
                                    ///< 4.XX

    MENU_STYLE_201,                 ///< 1.XX    2.XX
                                    ///< 3.XX    4.XX

                                    ///< 5.XX    6.XX
                                    ///< 7.XX    8.XX

    MENU_STYLE_202,                 ///< 1.XX    2.XX
                                    ///< 3.XX    4.XX

                                    ///< 1.XX    2.XX
                                    ///< 3.XX    4.XX

    MENU_STYLE_203                  ///< 1.XX    3.XX
                                    ///< 2.XX    4.XX
}teMenuStyle;


typedef struct
{
    unsigned char   *hidden;
    unsigned char   *text;
    int  (*pfnProc)(void);       //菜单运行函数
    unsigned int    value;
}tsMenuItem;

typedef struct
{
    int             key;
    int  (*pfnProc)(void);      //菜单运行函数
    unsigned char   bGoBack;    //是否返回上层
}tsMenuQKey;

typedef struct
{
    unsigned char   isAntiColor;
    unsigned char   *text;
}tsMenuCaption;

typedef struct
{
    unsigned char   isExit;
    unsigned int    itemCount;
    unsigned int    qKeyCount;
    unsigned char   *getValue;
    int             (*checkFunc)(void);
    tsMenuCaption   title;
    tsMenuCaption   caption;
    tsMenuItem      item[API_MENU_MAX_ITEM];        //菜单结构
    tsMenuQKey      QKey[8];                        //快捷键
}tsMenu;

int UMenu_CheckPgUp(int key);
int UMenu_CheckPgDn(int key);

int UMenu_Init(unsigned char *getValue, tsMenu *pMenu);

int UMenu_SetTitle(const char *pText, unsigned char isAntiColor, tsMenu *pMenu);

int UMenu_AddCaption(const char *pText, tsMenu *pMenu);

int UMenu_AddQKey(unsigned char ucKey, int (*callback)(void), tsMenu *pMenu);

int UMenu_AddMenu(const char *pText, int (*callback)(void), unsigned int value, unsigned char *enableFlag, tsMenu *pMenu);

int UMenu_DispMenu(teMenuStyle menuMode, unsigned int timeout, tsMenu *pMenu);

#endif
