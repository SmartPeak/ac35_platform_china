#ifndef _EMV_PARAM_H_
#define _EMV_PARAM_H_

typedef enum
{
    VERSION_QUICS = 0,
    VERSION_QPBOC

} Kernel_Version;

#ifdef __cplusplus
extern   "C"
{
#endif
    /*删除终端设置参数*/
    void EMV_DeleteFunParam(void);

    /*获取交易类型*/
    int EMV_Get_TransType(void);

    /*使用是否打印log标志位*/
    void EMV_Set_AbleLog(char bAbleLogFalg);

    /*获取打印log标志位*/
    char EMV_Get_AbleLog(void);

    int CL_Get_Kernel_Version(void);

    /**
    * @brief 获取系统版本信息
    */
    int EMV_Get_SysVersion(void);

#ifdef __cplusplus
}
#endif

#endif
