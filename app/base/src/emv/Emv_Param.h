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
    /*ɾ���ն����ò���*/
    void EMV_DeleteFunParam(void);

    /*��ȡ��������*/
    int EMV_Get_TransType(void);

    /*ʹ���Ƿ��ӡlog��־λ*/
    void EMV_Set_AbleLog(char bAbleLogFalg);

    /*��ȡ��ӡlog��־λ*/
    char EMV_Get_AbleLog(void);

    int CL_Get_Kernel_Version(void);

    /**
    * @brief ��ȡϵͳ�汾��Ϣ
    */
    int EMV_Get_SysVersion(void);

#ifdef __cplusplus
}
#endif

#endif
