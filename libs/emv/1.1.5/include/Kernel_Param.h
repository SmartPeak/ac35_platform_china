#ifndef KERNEL_PARAM_H_
#define KERNEL_PARAM_H_

#ifdef __cplusplus
extern   "C"
{
#endif


#include "EmvKernel.h"
#include "EmvDataType.h"
#include "EmvDataSize.h"
#include "QVSDC.h"

#include "EmvRevocationIPKList.h"
#include "EmvExceptionFileList.h"
#include "EmvTransHandle.h"
#include "EmvCapkList.h"
#include "EmvAidList.h"
#include "AppCallBack.h"

//#if !defined(CLOSE_LOG)
//#define LOG(...)   PrintLogToCom(__VA_ARGS__)
//#else
//#define LOG(...)
//#endif

typedef struct  {// 启动交易
	unsigned int pAmount;
	unsigned int pAmountOther;
	unsigned int pTarnsCounter;
	unsigned char pRandom[16];
}START_KERNEL;

extern struct EMV_TERMINAL_INFO __TERMINAL_INFO;
extern struct EMV_KERNEL_CONFIG __KERNEL_CONFIG;

extern KERNEL_START_TYPE __KERNEL_START_TYPE;
extern KERNEL_VERSION_TYPE __KERNEL_VERSION_TYPE;

extern EMV_UINT32 __TRANSACTION_COUNTER;

extern EMV_BOOL __EC_STATUS;
extern EMV_BOOL __IS_LOG;
extern EMV_BYTE __TRANS_TYPE;
extern LPC_EMV_CHAR __TERMINAL_ACQUIRE_ID;
extern START_KERNEL __KERNEL_START;


//VISA - QUICS 使用
#define		TRANSACTION_TYPE_VISA_SALE					0x00
#define		TRANSACTION_TYPE_VISA_REFUND				0x01
#define		TRANSACTION_TYPE_VISA_CASH					0x02
#define		TRANSACTION_TYPE_VISA_CASHBACK				0x03
#define		TRANSACTION_TYPE_VISA_CASH_DISBURSEMENT		0x04

#define		TRANSACTION_TYPE_EMV_GOODS					0x05
#define		TRANSACTION_TYPE_EMV_CASH					0x06
#define		TRANSACTION_TYPE_EMV_CASHBACK				0x07
#define		TRANSACTION_TYPE_EMV_SERVICE				0x08
#define		TRANSACTION_TYPE_EMV_INQUIRY				0x09
#define		TRANSACTION_TYPE_EMV_TRANSFER				0x10
#define		TRANSACTION_TYPE_EMV_PAYMENT				0x11
#define		TRANSACTION_TYPE_EMV_ADMIN					0x12
#define		TRANSACTION_TYPE_EMV_DEPOSIT				0x13

#define		TRANSACTION_VERSION_DEFAULT					0x14
#define		TRANSACTION_VERSION_CERTIFIED				0x15
#define		TRANSACTION_START_CODE_A					0x16
#define		TRANSACTION_START_CODE_B					0x17
#define		TRANSACTION_START_CODE_C					0x18
#define		TRANSACTION_START_CODE_D					0x19

// add by wl 
#define		TRANSACTION_TYPE_EMV_LOAD					0x20 // 圈存
#define		TRANSACTION_TYPE_EMV_PREAUTH				0x21 // 预授权
#define		TRANSACTION_TYPE_EMV_LOAD_UNSPEC			0x22 // 非指定圈存
#define		TRANSACTION_TYPE_EMV_RETURN					0x23 // 退货
//---------------------------  交易开始
#define TAG_TRANS_TYPE                0x9C
#define TAG_TRANS_AMT                 0x9F02
#define TAG_TRANS_CASH                0x9F03
#define TAG_TRANS_DATE                0x9A
#define TAG_TRANS_TIME                0x9F21
#define TAG_TRANS_LOG                 0x9F70
#define TAG_TRANS_RANDOM              0x9F71
#define TAG_TRANS_TARNS_COUNTER       0x9F72

//---------------------------

//--------------------------- 终端参数
#define TAG_PARAM_TERMINAL_ID                 0x9F01
#define TAG_PARAM_TERMINAL_COUNTRY_CODE       0x9F02
#define TAG_PARAM_TERMINAL_ENTRY_MODE         0x9F03
#define TAG_PARAM_MERCHANT_MERCHANT_ID        0x9F04
#define TAG_PARAM_MERCHANT_CATEGORY_CODE      0x9F05
#define TAG_PARAM_MERCHANT_LOCATION           0x9F06
#define TAG_PARAM_TRANS_CURRENCY_CODE         0x9F07
#define TAG_PARAM_TRANS_CURRENCY_EXP          0x9F08
#define TAG_PARAM_TRANS_REF_CURRENCY_CODE     0x9F09
#define TAG_PARAM_TRANS_REF_CURRENCY_EXP      0x9F10
//---------------------------

//--------------------------- 内核参数
#define TAG_CONFIG                      				0x9F01
#define TAG_CONFIG_CODE_METHOD       					0x9F02
#define TAG_CONFIG_CDA_METHOD         					0x9F03
#define TAG_CONFIG_TERMINAL_TYPE      					0x9F04
#define TAG_CONFIG_TERMINAL_CAPABILITIES      			0x9F05
#define TAG_CONFIG_ADDTIONAL_TERMINAL_CAPABILITIES      0x9F06
//---------------------------

//--------------------------- QVSDC
#define TAG_QVSDC                 0x9F01
#define TAG_QVSDC_RISK_DEFAULT    0x9F02
#define TAG_QVSDC_RISK_CASH       0x9F03
#define TAG_QVSDC_RISK_CASHBACK   0x9F04
#define TAG_QVSDC_RISK_PURCHASE   0x9F05
#define TAG_QVSDC_DRL			  0x9F06

//--------------------------- QVSDC_RISK
#define TAG_QVSDC_RISK                       0x9F01
#define TAG_QVSDC_RISK_CONTACTLESSTRANSLIMIT 0x9F02
#define TAG_QVSDC_RISK_CONTACTLESSCVMLIMIT   0x9F03
#define TAG_QVSDC_RISK_CONTACTLESSFLOORLIMIT 0x9F04
#define TAG_QVSDC_RISK_FLOORLIMIT            0x9F05
//---------------------------

//--------------------------- QVSDC_DRL
#define TAG_QVSDC_DRL_ACTIVE				0x9F01
#define TAG_QVSDC_DRL_PROGRAME_ID			0x9F02
#define TAG_QVSDC_DRL_CONTACTLESSTRANSLIMIT 0x9F03
#define TAG_QVSDC_DRL_CONTACTLESSCVMLIMIT   0x9F04
#define TAG_QVSDC_DRL_CONTACTLESSFLOORLIMIT 0x9F05
#define TAG_QVSDC_DRL_ACTIVE_STATUS_CHECK	0x9F06
#define TAG_QVSDC_DRL_ACTIVE_STATUS_PATH	0x9F07
#define TAG_QVSDC_DRL_ZERO_AMT_CHECK		0x9F08
#define TAG_QVSDC_DRL_ZERO_AMT_PATH			0x9F09

//---------------------------
//--------------------------- QVSDC_RISK
#define TAG_MIR_CONTACTLESSTRANSLIMIT_CVM 0x9F06
#define TAG_MIR_TRANSACTIONRECOVERYLIMIT  0x9F07
#define TAG_MIR_DATA_EXCHANGE			  0x9F08
//---------------------------



//--------------------------- AID参数

#define TAG_AID_AID                       0x9F01
#define TAG_AID_APP_VER                   0x9F02
#define TAG_AID_PART_MACH                 0x9F03
#define TAG_AID_DEFAULT_DDOL              0x9F04
#define TAG_AID_DEFAULT_TDOL              0x9F16
#define TAG_AID_TAC_DENIAL                0x9F05
#define TAG_AID_TAC_ONLINE                0x9F06
#define TAG_AID_TAC_DEFAULT               0x9F07
#define TAG_AID_TERMINALFLOORLIMIT        0x9F08
#define TAG_AID_TRESHOLDVALUE             0x9F09
#define TAG_AID_TARGETPERCENTAGE          0x9F10
#define TAG_AID_MAXTARGETPERCENTAGE       0x9F11
#define TAG_AID_EC_TRANS_LIMIT            0x9F12
#define TAG_AID_CONTACTLESSMAXTRANSAMOUNT 0x9F13
#define TAG_AID_CONTACTLESSFLOORLIMIT     0x9F14
#define TAG_AID_CONTACTLESSCVMAMOUNT      0x9F15

//---------------------------

//--------------------------- Capk参数
#define TAG_CAPK_RID                      0x9F01
#define TAG_CAPK_CAPK_INDEX               0x9F02
#define TAG_CAPK_MODULES                  0x9F03
#define TAG_CAPK_EXPONENTS                0x9F04
#define TAG_CAPK_CHECKSUM                 0x9F05
#define TAG_CAPK_TYPE					  0x9F06

//---------------------------

//--------------------------- RevocationIPK参数
#define TAG_REVOCATIONIPK_RID             0x9F01
#define TAG_REVOCATIONIPK_CAPK_INDEX      0x9F02
#define TAG_REVOCATIONIPK_SERIAL_NO       0x9F03
//---------------------------

//--------------------------- ExceptionFile参数
#define TAG_EXCEPTIONFILE_PAN             0x9F01
#define TAG_EXCEPTIONFILE_SERIAL_NO       0x9F02
//---------------------------

//--------------------------- 当前交易卡片
#define TAG_INSERTED_ICCARD     0x80
#define TAG_SWIPED_MAGCARD      0x81
#define TAG_INSERTED_PICC       0x82

#define TAG_KERNEL_NOT			0x00
#define TAG_KERNEL_QUICS		0x01
#define TAG_KERNEL_VISA			0x02
#define TAG_KERNEL_MASTERCARD	0x03
#define TAG_KERNEL_DISCOVER		0x04
#define TAG_KERNEL_EXPRESS		0x05
#define TAG_KERNEL_JCB			0x06
#define TAG_KERNEL_MIR			0x07

//---------------------------

int PrintLogToCom(const char *fmt, ...);

/**
* 设置内核 预处理参数 是否使用 AID 中定义的参数
*/
unsigned int Contactless_Set_KernelApplyAid(int parameter);

void Kernel_Set_Trans_Param(EMV_INT32 uiTarnsCounter,
	EMV_UINT8 TransType, EMV_UINT32 Amount, EMV_UINT32 AmountOther);


// 设置终端参数
int EMV_SetTerminalInfo_App(LPC_EMV_TERMINAL_INFO pTerminalInfo);

// 设置配置参数相关交易参数
int EMV_SetKernelConfig_App(LPC_EMV_KERNEL_CONFIG pKernelConfig);



int EMV_SetQPBOCParam_App(LP_QPBOC_PARAM qpbocParam);

int EMV_SetQVSDCParam_App(LP_QVSDC_PARAM qvsdcParam);

int EMV_SetAMEXParam_App(LP_EXPRESS_PARAMETER amexParam);

int EMV_SetDISCOVERParam_App(LP_DISCOVER_PARAM amexParam);

int EMV_SetMIRParam_App(LP_MIR_PARAM amexParam);

int EMV_SetMASTRTParam_App(LP_MASTRT_PARAM amexParam);

// 增加aid
int EMV_AidList_Add_App(LPC_EMV_AID_ITEM pItem);

/*从aid列表中,获取aid*/
int EMV_AidList_Get_App(LP_EMV_AID_ITEM pItem, unsigned int uiIndex);

//  获取aid列表个数
int EMV_AidList_GetCount_App(void);

// 清空aid列表
int EMV_AidList_Clear_App(void);



// 增加公钥
int EMV_CapkList_Add_App(LPC_EMV_CAPK_ITEM pItem);

// 增加公钥 不需要校验checksum
int EMV_CapkList_Add_NoCheck_App(LPC_EMV_CAPK_ITEM pItem);

/*从capk列表中获取capk*/
int EMV_CapkList_Get_App(LP_EMV_CAPK_ITEM pItem, unsigned int uiIndex);

/*获取集合中capk的个数*/
int EMV_CapkList_GetCount_App(void);

// 删除公钥
int EMV_CapkList_DeleteEx_App(LPC_EMV_BYTE pRID, EMV_BYTE bIndex);

// 清空公钥列表
int EMV_CapkList_Clear_App(void);




// 增加回收公钥
int EMV_RevoIPKList_Add_App(LPC_EMV_REVO_IPK_ITEM pItem);

/*从过期公钥列表中获取过期公钥*/
int EMV_RevoIPKList_Get_App(LP_EMV_REVO_IPK_ITEM pItem, unsigned int uiIndex);

/*获取回收公钥的个数*/
int EMV_RevoIPKList_GetCount_App(void);

// 清空回收公钥
int EMV_RevoIPKList_Clear_App(void);

// 删除回收公钥对象
int EMV_RevoIPKList_DeleteEx_App(LPC_EMV_REVO_IPK_ITEM pItem);




// 增加黑名单
int EMV_ExceptList_Add_App(LPC_EMV_EXCEPT_ITEM pItem);

int EMV_ExceptList_Get_App(LP_EMV_EXCEPT_ITEM pItem,unsigned int uiIndex);

/*获取黑名单的个数*/
int EMV_ExceptList_GetCount_App(void);

// 清除删除黑名单
int EMV_ExceptList_DeleteEx_App(LPC_EMV_BYTE pPAN, EMV_UINT16 uiPAN, EMV_BYTE bSeq);

// 清空列表
int EMV_ExceptList_Clear_App(void);


#ifdef __cplusplus
}
#endif

#endif
