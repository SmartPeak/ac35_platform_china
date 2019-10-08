///////////////////////////////////////////////////////////////////////////////
/// @file     multilingual.h
/// @brief    multilingual interface
/// @author   xuzhou.chen
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @date     11/12/2018
//////////////////////////////////////////////////////////////////////////////

#ifndef _MULTILINGUAL_H
#define _MULTILINGUAL_H

/**
 * @brief the enum definition of language type
 */
typedef enum
{
    LANG_CN = 0,/*!< chinese*/
    LANG_EN     /*!< english*/
    
} eLangIndex;

/**
 * @brief get the current language
 * @param
 * @retval eLangIndex
 */
int multilingual_getLanguage(void);

/**
 * @brief set the current language
 * @param [in] index
 * @retval success or error
 */
int multilingual_setLanguage(eLangIndex index);

/**
 * @brief read a string from the language file
 * @param [in] msgIndex
 * @retval string
 */
char *multilingual_getSysMsg(unsigned int msgIndex);

/**
 * @brief read a string from the language file
 * @param [in] msgIndex
 * @retval string
 */
char *multilingual_getMsg(unsigned int msgIndex);


#endif //_MULTILINGUAL_H

