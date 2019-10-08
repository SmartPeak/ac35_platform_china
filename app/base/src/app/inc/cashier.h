#ifndef _CASHIER_
#define _CASHIER_

#define CASH_MAXSUPERNOLEN          2
#define CASH_SUPERPASSWDLEN         8
#define CASH_MAXCASHIER             25
#define CASH_CASHIERNOLEN           2
#define CASH_CASHIERPASSLEN         4
#define CASH_SYSCASHIERNOLEN        2
#define CASH_SYSCASHIERPASSLEN      6
#define CASH_SAFEPASSWDLEN          8

#define CASH_DEF_SYS_CASHIER_PWD    "123456"

typedef struct
{
    unsigned char   aucSuperNo[CASH_MAXSUPERNOLEN];
    unsigned char   aucSuperPSW[CASH_SUPERPASSWDLEN];
    unsigned char   aucSYSCashierNo[CASH_SYSCASHIERNOLEN];
    unsigned char   aucSYSCashierPass[CASH_SYSCASHIERPASSLEN];
    unsigned char   aucCashierNo[CASH_MAXCASHIER][CASH_CASHIERNOLEN];
    unsigned char   aucCashierPass[CASH_MAXCASHIER][CASH_CASHIERPASSLEN];
    unsigned char   aucSafePSW[CASH_SAFEPASSWDLEN];

}SYSCASHIER;

/*!< cashier error code */
typedef enum
{
    CASHIER_DEL_NOT_ALLOW               = -8,
    CASHIER_PWD_DIFFER                  = -7,   ///< 两次输入不一致
    CASHIER_PWD_CHANGE_NOT_ALLOW        = -6,   ///< 不允许修改
    CASHIER_PWD_CHANGE_FAIL             = -5,   ///< 修改失败
    CASHIER_ILLEGAL                     = -4,
    CASHIER_FULL                        = -3,   ///< 操作员已满
    CASHIER_NO_EXIST                    = -2,   ///< 操作员不存在
    CASHIER_EXIST                       = -1    ///< 操作员已存在
}CashierErrCode;

/**
 * @brief check admin pwd
 */
int CASH_CheckAdminPwd(const char *title);

/**
 * @brief check manage pwd
 */
int CASH_CheckManagePwd(const char *title);

/**
 * @brief check safe pwd
 */
int CASH_CheckSafePwd(const char *title);

/**
 * @brief init admin pwd
 */
int CASH_InitAdminPwd(void);

/**
 * @brief cashier init
 */
int CASH_CashierInit(void);

/**
 * @brief add cashier
 */
int CASH_AddCashier(void);

/**
 * @brief delete cashier
 */
int CASH_DelCashier(void);

/**
 * @brief modify cashier
 */
int CASH_ModiCashierPwd(void);

/**
 * @brief query cashier
 */
int CASH_QueryCashier(void);

/**
 * @brief change admin pwd
 */
int CASH_ChangeAdminPwd(void);

/**
 * @brief change manage pwd
 */
int CASH_ChangeManagePwd(void);

/**
 * @brief change safe pwd
 */
int CASH_ChangeSafePwd(void);

/**
 * @brief cashier logon
 */
int trans_CashierLogon(void);

#endif
