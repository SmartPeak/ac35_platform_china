#ifndef POS_MENU_H_
#define POS_MENU_H_

typedef void(*Fn_Menu_Process)(void * pCallbackParam);
int Menu_Select(char *pszTitle, int uiMenuCount, char **ppMenus, int iDefaultSelect, char bAllowCancel, Fn_Menu_Process pProcess, void *pvProcessParam);

#endif
