#ifndef EMV_CT_KERNEL_L2_H_
#define EMV_CT_KERNEL_L2_H_


#include "EmvTransHandle.h"
#ifdef __cplusplus
extern   "C"
{
#endif

/*����Ӵ��ں˵�����*/
typedef enum
{
	EMV_KERNEL_CONTACT_MODE_ALL = 0,// ȫ����
	EMV_KERNEL_CONTACT_MODE_CONFIG_2C_PBOC,// pboc�ں�,
	EMV_KERNEL_CONTACT_MODE_CONFIG_3C,//��֧��no cvm
	EMV_KERNEL_CONTACT_MODE_CONFIG_4C,//��֧���ѻ�pin
	EMV_KERNEL_CONTACT_MODE_CONFIG_5C,//ֻ֧��no cvm
	EMV_KERNEL_CONTACT_MODE_CONFIG_6C,//���ѻ�,��֧�ִ���,����pin,��֧��ǿ������
	// ������ʱ����
	EMV_KERNEL_CONTACT_MODE_CONFIG_7C,
	EMV_KERNEL_CONTACT_MODE_CONFIG_8C,
	EMV_KERNEL_CONTACT_MODE_CONFIG_9C,
}EMV_KERNEL_CONTACT_CONFIG_MODE;

typedef EMV_KERNEL_CONTACT_CONFIG_MODE *LP_EMV_KERNEL_CONTACT_CONFIG_MODE;
//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     EMVCtKernelL2
/// @brief    ���ڽӴ����̵� ����
/// @author   wl
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     05/25/2018
//////////////////////////////////////////////////////////////////////////////

#define	EMV_KERNEL_USE_AUTH_TEST  // ���ڲ��ֲ���ʹ��aid������ʹ���ն˲���

#define EMV_BASE 0

#define EMV_ICC_RESET_ERR     					EMV_BASE-1 //IC����λʧ��
#define EMV_ICC_CMD_ERR       					EMV_BASE-2 //IC����ʧ��
#define EMV_ICC_BLOCK         					EMV_BASE-3 //IC������    
#define EMV_ICC_RSP_ERR       					EMV_BASE-4 //IC���������
#define EMV_ICC_APP_BLOCK     					EMV_BASE-5 //Ӧ������
#define EMV_ICC_NO_APP              			EMV_BASE-6	// ��Ƭ��û��EMVӦ��
#define EMV_ICC_USER_CANCEL   					EMV_BASE-7 //�û�ȡ����ǰ��������
#define EMV_ICC_TIME_OUT      					EMV_BASE-8 //�û�������ʱ
#define EMV_ICC_DATA_ERR      					EMV_BASE-9 //��Ƭ���ݴ���
#define EMV_ICC_NOT_ACCEPT   					EMV_BASE-10 //���ײ�����
#define EMV_ICC_DENIAL        					EMV_BASE-11 //���ױ��ܾ�
#define EMV_ICC_INVALID_TLV         			EMV_BASE-12 // ��Чtlv
#define EMV_ICC_PIN_BLOCK     					EMV_BASE-13 // pin����
#define EMV_ICC_NEEDUSERSEL	  					EMV_BASE-14	//��Ҫ�û�ѡ��  
#define EMV_ICC_CARD_READ_ERROR   				EMV_BASE-15	//��Ƭ��ȡ����
#define EMV_ICC_USE_MAG_STRIPE 					EMV_BASE-16	//����
#define EMV_ICC_DATA_EXIST    					EMV_BASE-17 // ���ݲ�����
#define EMV_ICC_CVM_DATA_ERR					EMV_BASE-18	//cvm(8e)���ݴ���
#define EMV_ICC_NO_TRANS_LOG					EMV_BASE-19	//û�н���log
#define EMV_ICC_RECORD_NOTEXIST					EMV_BASE-20	//��¼������
#define EMV_ICC_MULT_SEL_REE					EMV_BASE-21	//��Ӧ��ѡ�����
#define EMV_ICC_AUTH_RECOVER_CERT_ERR			EMV_BASE-22	//�ָ�֤��ʧ��
#define EMV_ICC_AUTH_SDA_AUTH_ERR				EMV_BASE-23	//sda��֤ʧ��
#define EMV_ICC_AUTH_DDA_AUTH_ERR				EMV_BASE-24	//dda��֤ʧ��
#define EMV_ICC_AUTH_CDA_AUTH_ERR				EMV_BASE-25	//cda��֤ʧ��
#define EMV_ICC_AUTH_VERIFY_HASH_ERR			EMV_BASE-26	//��֤hash����
#define EMV_ICC_DEAL_CVM_ERR					EMV_BASE-27	//����cvm�б�ʧ��
#define EMV_ICC_MAG_FAIL						EMV_BASE-28	//������ʧ��
#define EMV_ICC_RSP_6985  						EMV_BASE-29 // ����6985
#define EMV_ICC_NO_RECORD 						EMV_BASE-30 // û��¼
#define EMV_ICC_CID_ERR       					EMV_BASE-31 // CDA��֤ʱ,�ָ���CID�뿨Ƭ���͵�CID��Ϣ��һ��
#define EMV_ICC_EC_BALANCE_LIMIT    			EMV_BASE-32 // �������ֽ�����



#define POS_ENTRY_MODE_MAG_STRIPE  "02" // ����
#define POS_ENTRY_MODE_CONTACT  "05" // �Ӵ�
#define POS_ENTRY_MODE_QPBOC  "07" // qpboc
#define POS_ENTRY_MODE_CONTACTLESS_PBOC  "08" // �ǽӽ����

#define POS_ENTRY_MODE_MAG_FAIL_TO_IC   "80" // ������pos���뷽ʽ ��0x92->0x80

/**
* ��ȡ�Ӵ��ں˰汾
*/
EMV_INT32 Contact_Get_Version_Kernel(char * pBuffer, int uiBufferSize);


/*
�����ں˽���
bEMVSimpleFlag:�Ƿ�Ϊ������
pMagTrack:����������
pContactDetect:����������
*/
EMV_INT32 Contact_Start_EMV_Kernel(EMV_CHAR bEMVSimpleFlag, LP_MAG_TRACK_DATA pMagTrack,
	Fn_EMV_Contact_DetectCard pContactDetect);

/*�������ò���*/
EMV_VOID EMV_Cantact_Kernel_Set_Config(LP_EMV_KERNEL_CONFIG_ICC pContactConfigIcc);


/*��ȡ�Ӵ����ò���*/
EMV_VOID EMV_Cantact_Kernel_Get_Config(LP_EMV_KERNEL_CONFIG_ICC pContactConfigIcc);


/**
����Ӧ���б�,���ڶ�ȡ��Ƭ��־,
return:EMV_OK->suc(����EMV_Contact_ReadCardLog)
*/
EMV_INT32 EMV_Contact_AppListNoGPO(void);

/**
��ȡ��Ƭ��־
bRecordNO:���
pLogFormatList:��ȡ��Ƭ��־��ʽ9f4f
uiLogFormatList:
pReadCardLog:���ض���¼
uiReadCardLog:���ؼ�¼��
return:EMV_OK->suc,EMV_ICC_RECORD_NOTEXIST:�޼�¼,EMV_ICC_NO_TRANS_LOG->��¼������,
EMV_ICC_DATA_ERR->���ݴ���
*/
EMV_INT32 EMV_Contact_ReadCardLog(EMV_INT32 bRecordNO, EMV_BYTE *pLogFormatList, LP_EMV_INT32 uiLogFormatList,
	EMV_BYTE *pReadCardLog, LP_EMV_INT32 uiReadCardLog);


/*��ȡ�����ֽ����*/
EMV_INT32 EMV_Contact_ReadEcBanlance(EMV_INT32 *pECBanlance);


/*��ȡ�ں˵�����checksum*/
EMV_VOID EMV_Contact_CfgCheckSum(LP_EMV_CHAR pCheckSum, EMV_INT32 uiCheckSumSize);

/*
��ȡ�ں˵�checksum
tips:��EMV_Contact_CfgCheckSum
	������ȡ��ͬ�ں����õ�checksum,���ò�ͬsumֵ,�ɶ��sumֵ
	EMV_Contact_KernelCheckSum ��ȡ�ں˵�sum,һ��һ���ں�ֻ��һ��sumֵ
*/
EMV_VOID EMV_Contact_KernelCheckSum(LP_EMV_CHAR pKernelCheckSum, EMV_INT32 uiKernelCheckSumSize);


/*��ȡ�����ֽ����*/
EMV_VOID EMV_Contact_GetECBanlance(EMV_INT32 *pECBanlance);

/*��ȡ�Ƿ��ӡ�վݵı�־λ*/
EMV_BOOL EMV_Contact_GetPrintReceipt(EMV_VOID);


/*
��ȡ�ű����(str)
*/
EMV_UINT32 EMV_Contact_GetScriptResult(LP_EMV_CHAR pScript, EMV_INT32 uiScriptSize);


/*
������֤�ѻ�pinlock�Ƿ�����
pClipherPinFlag:�Ƿ�Ϊ����pin��֤
pPinBlock:Ҫ��֤��pinblock
uiPinBlock:
*/
EMV_INT32 EMV_Contact_Verify(EMV_BOOL pCipherPinFlag, LPC_EMV_BYTE pPinBlock, EMV_INT32 uiPinBlock, EMV_BYTE pVerifySW[2]);

/*�����ں�����*/
EMV_VOID EMV_Contact_SetKernelCfg(EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);


/*���õ�ǰ�ں�����*/
EMV_VOID EMV_Contact_GetKernelCfg(LP_EMV_KERNEL_CONTACT_CONFIG_MODE pKernelContactConfigMode);

/*
��ȡ��������ָ֤ʾλ
pResp:��Ӧ����
uiResp:��Ӧ��ָ��
*/
EMV_INT32 EMV_Cantact_Kernel_GetIssuerAuthFlag(LP_EMV_BYTE pResp, LP_EMV_INT32 uiResp);

#ifdef __cplusplus
}
#endif

#endif

