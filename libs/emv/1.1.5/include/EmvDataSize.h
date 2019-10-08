#ifndef EMV_DATA_SIZE_H_
#define EMV_DATA_SIZE_H_

#ifdef __cplusplus
extern   "C"
{
#endif
#define MAX_SCRIPT_LENGTH 300 // 脚本数据
#define MAX_SCRIPT_RESULT_LENGTH 256 // 脚本结果长度

#define MAX_SDA_DATA				1024*3// sda数据 1k->3k 防止返回静态数据过长,死机
#define MAX_CDA_DATA				1024// cda数据 

#define MAX_RSA_EXPONENTS  3
#define MAX_RSA_MODULES    256
#define MAX_DATA_SIZE 255
#define MAX_PAN 19
#define MAX_APPS 100
#define MAX_RSA_KEY_SIZE 256
#define MAX_RSA_EXPONENTS_SIZE 3
#define MAX_AID 16
#define MAX_APP_LABEL 16
#define MAX_AID_NAME 32
#define MAX_DRL 16
#define MAX_DOOL 256
#define MAX_RISK_MAN_DATA 10  // 风险管理数据长
#define MAX_IC_AUTH_DATA 16 // ic卡返回的认证的数据

#define MAX_MAG_TRACK1 80 // 磁条卡1磁道的长度
#define MAX_MAG_TRACK2 48 // 磁条卡二磁道的长度
#define MAX_MAG_TRACK3 112 // 二磁道的长度
#define MAX_CARD_RANDOM 8 //卡片随机数
// 定义常用buff的大小
#define MAX_TEMP_BUFF_SIZE_8 8 // 定义临时变量的buff
#define MAX_TEMP_BUFF_SIZE_16 16 // 定义临时变量的buff
#define MAX_TEMP_BUFF_SIZE_32 32 // 定义临时变量的buff
#define MAX_TEMP_BUFF_SIZE_64 64 
#define MAX_TEMP_BUFF_SIZE_256 256
#define MAX_APDU_RESPONSE 256 // 设置最大的apdu返回数据
#define MAX_SUPPROT_SCRIPT_LEN 128 // 终端支持的最大脚本长度

#define SIZE_CVM_RESULT 3
#define SIZE_CVM_AMOUNT_X 4
#define SIZE_CVM_AMOUNT_Y 4
#define SIZE_RESPONSE_CODE 2
#define SIZE_APP_CRYPTOGRAM 8
#define SIZE_AC 2
#define SIZE_ISSUER_AUTH_DATA 50
#define SIZE_APP_VERSION 2
#define SIZE_APP_PRIORITY 1
#define SIZE_TVR 5
#define SIZE_TSI 2
#define SIZE_AMOUNT 6
#define SIZE_AMOUNT_BINARY 4
#define SIZE_PAN_SEQUENCE_NUM 1
#define SIZE_RID 5
#define SIZE_HASH 20 // sha3¤?è
#define SIZE_EXP_DATE 3 // ê§D§è??ú
#define SIZE_CERT 3 // ??ê?1????¤êé3¤?è
#define SIZE_CAPK_INDEX 1
#define SIZE_PIN_BLOCK 8
#define SIZE_TERMINAL_ID 8
#define SIZE_TERMINAA_ACQUIRE_ID 6
#define SIZE_MERCHANT_ID 15
#define SIZE_MERCHANT_CATEGORY_CODE 2
#define SIZE_MERCHANT_LOCATION 255
#define SIZE_TRANS_CURRENCY_CODE 2
#define SIZE_IFD_SERIAL_NUMBER 8
#define SIZE_COUNTRY_CODE 2
#define SIZE_TERMINAL_TYPE 1
#define SIZE_TERMINAL_CAPABILITIES 3
#define SIZE_ADDTIONAL_TERMINAL_CAPABILITIES 5
#define SIZE_TERMINAL_ENTRY_MODE 1
#define SIZE_ACTION_CODE SIZE_TVR
#define SIZE_APP_PROGRAM_ID 16
#define SIZE_TTQ 4
#define SIZE_CTQ 2
#define SIZE_CARD 16
#define SIZE_LOG_ENTRY 2
#define SIZE_AIP 2
#define SIZE_RSP_CODE 2 // ?ìó|??
#define SIZE_AUTH_CODE 6 // êúè¨êy?Y
#define SIZE_SHA1 20 // sha1μ??μ
#define SIZE_SM3 32 
#define SIZE_MAG_SERVER_CODE 3  // ′?ì??¨
#define SIZE_MAG_EXP_DATE 4 // 磁条卡有效期
#define SIZE_DSDOL                  250
#define SIZE_KERNEL_IDENTIFIER      8
#define SIZE_DUAL_CURRENCY_CODE		2
#define SIZE_CONTACTLESS_READER_CAPABILITIES		1
#define SIZE_ENHANCED_CONTACTLESS_READER_CAPABILITIES		4
#define SIZE_MOBILE_CVM_RESULTS		3
#define SIZE_CARD_INTERFACE_AND_PAYMENT_CAPABILITIES		2


//PAYPASS
#define SIZE_ADF_NAME               16
#define SIZE_APP_LABEL              16
#define SIZE_TRK1_DATA              76
#define SIZE_TRK2_EQU_DATA          19
#define SIZE_PAN                    10
#define SIZE_APP_TEMPLATE           252
#define SIZE_FCI_TEMPLATE           250
#define SIZE_RR_TEMPLATE            253
#define SIZE_TEMPLATE_FORMAT_2      253
#define SIZE_TEMPLATE_FORMAT_1      253
#define SIZE_AIP                    2
#define SIZE_DF_NAME                16
#define SIZE_API                    1
#define SIZE_CDOL1                  250
#define SIZE_CVM_LIST               250
#define SIZE_CAPK_INDEX_C           1
#define SIZE_ISSPK_CERT             248
#define SIZE_ISSPK_REMAINDER        248
#define SIZE_AFL                    248
#define SIZE_TVR                    5
#define SIZE_TRAN_DATE              3
#define SIZE_TRAN_TYPE              1
#define SIZE_APP_EXP_DATE           3
#define SIZE_APP_EFF_DATE           3
#define SIZE_ISS_COUNTRY_CODE       2
#define SIZE_TRAN_CUR_CODE          2
#define SIZE_LANGUAGE_PREF          8
#define SIZE_SERVICE_CODE           2
#define SIZE_PSN                    1
#define SIZE_TRAN_CUR_EXP           1
#define SIZE_ACCOUNT_TYPE           1
#define SIZE_ACQ_IDENTIFIER         6
#define SIZE_AMOUNT_NUM             6
#define SIZE_AMOUNT_OTHER_NUM       6
#define SIZE_AUC                    2
#define SIZE_AVN_C                  2
#define SIZE_AVN_T                  2
//#define SIZE_ASRPD                  80
#define SIZE_IAC_DEFAULT            5
#define SIZE_IAC_DENIAL             5
#define SIZE_IAC_ONLINE             5
#define SIZE_ISS_APP_DATA           32
#define SIZE_ISS_CODE_TAB_INDEX     1
#define SIZE_APP_PREF_NAME          16
#define SIZE_MCC                    2
#define SIZE_MID                    15
#define SIZE_TCC                    2
#define SIZE_TID                    8
#define SIZE_TRMD                   8
#define SIZE_IDSN                   8
#define SIZE_TRK1_DIS_DATA          54
#define SIZE_TRK2_DIS_DATA          16
#define SIZE_TRAN_TIME              3
#define SIZE_PAR                    29
#define SIZE_CID                    1
#define SIZE_KERNEL_IDENTIFIER      8
#define SIZE_ISSPK_EXP              3
#define SIZE_TER_CAP                3
#define SIZE_CVR                    3
#define SIZE_TER_TYPE               1
#define SIZE_ATC                    2
#define SIZE_UNPRE_NUM              4
#define SIZE_PDOL                   240
#define SIZE_ADD_TER_CAP            5
#define SIZE_APP_CUR_CODE           2
#define SIZE_APP_CUR_EXP            1
#define SIZE_ICCPK_CERT             248
#define SIZE_ICCPK_EXP              3
#define SIZE_ICCPK_REMAINDER        128
#define SIZE_SDA_TAG_LIST           250
#define SIZE_SIGN_DYN_APP_DATA      248
#define SIZE_ICC_DYN_NUM            8
#define SIZE_LOG_ENTRY              2
#define SIZE_MER_NAME_AND_LOC       128
#define SIZE_OFF_ACC_BALANCE        6
#define SIZE_DRDOL                  250
#define SIZE_TRAN_CAT_CODE          1
#define SIZE_DS_ODS_CARD            160
#define SIZE_DSDOL                  250
#define SIZE_DS_REQ_OPE_ID          8
#define SIZE_APP_CAP_INFO           3
#define SIZE_DS_ID                  11
#define SIZE_DS_SLOT_AVAIL          1
#define SIZE_CVC3_TRK1              2
#define SIZE_CVC3_TRK2              2
#define SIZE_PCVC3TRK1              6
#define SIZE_PUNATCTRK1             6
#define SIZE_NATCTRK1               1
#define SIZE_PCVC3TRK2              2
#define SIZE_PUNATCTRK2             2
#define SIZE_NATCTRK2               1
#define SIZE_UDOL                   250
#define SIZE_UN_NUM_N               4
#define SIZE_TRK2_DATA              19
#define SIZE_MS_AVN_READER          2
#define SIZE_THIRD_PARTY_DATA       32
#define SIZE_DS_SLOT_MANAG_CTL      1
#define SIZE_PDE_1                  192
#define SIZE_PDE_2                  192
#define SIZE_PDE_3                  192
#define SIZE_PDE_4                  192
#define SIZE_PDE_5                  192
#define SIZE_UNPDE_1                192
#define SIZE_UNPDE_2                192
#define SIZE_UNPDE_3                192
#define SIZE_UNPDE_4                192
#define SIZE_UNPDE_5                192
#define SIZE_MER_CUSTOM_DATA        20
#define SIZE_DS_SUMMARY_1           16
#define SIZE_MSI                    1
#define SIZE_DS_UN_NUM              4
#define SIZE_FCI_PRO_TEMPLATE       240
#define SIZE_FCI_ISS_DIS_DATA       220
#define SIZE_PCI_INFO               3
#define SIZE_DS_INPUT_CARD          8
#define SIZE_DS_DIGEST_H            8
#define SIZE_DS_ODS_INFO            1
#define SIZE_DS_ODS_TERM            160
#define SIZE_DS_SUMMARY_2           16
#define SIZE_DS_SUMMARY_3           16
#define SIZE_BALANCE_BEF_GAC        6
#define SIZE_BALANCE_AFT_GAC        6
#define SIZE_DATA_NEEDED            512
#define SIZE_CDOL1_REL_DATA         512
#define SIZE_DS_AC_TYPE             1
#define SIZE_DS_INPUT_TERM          8
#define SIZE_DS_ODS_INFO_FOR_READER 1
#define SIZE_DS_SUMMARY_STATUS      1
#define SIZE_KERNEL_ID              1
#define SIZE_DSVN_TERM              512
#define SIZE_POST_GAC_PUT_DATA_STATUS       1
#define SIZE_PRE_GAC_PUT_DATA_STATUS        1
#define SIZE_PROCEED_TO_FIRST_WRITE_FLAG    1
#define SIZE_PDOL_REL_DATA          512
#define SIZE_TAGS_TO_READ           512
#define SIZE_DRDOL_RELATED_DATA     512
#define SIZE_REF_CTL_PARAM          1
#define SIZE_ERR_ID                 6
#define SIZE_UI_REQ_DATA            22
#define SIZE_CARD_DATA_INPUT_CAP    1
#define SIZE_CVM_CAP_CVM_REQ        1
#define SIZE_CVM_CAP_NO_CVM_REQ     1
#define SIZE_DEFAULT_UDOL           3
#define SIZE_KERNEL_CONFIG          1
#define SIZE_MAX_TORN_LIFETIME      2
#define SIZE_MAX_TORN_NUM           1
#define SIZE_MS_CVM_CAP_CVM_REQ     1
#define SIZE_SECURITY_CAP           1
#define SIZE_TAC_DEFAULT            5
#define SIZE_TAC_DENIAL             5
#define SIZE_TAC_ONLINE             5
#define SIZE_RCFL                   6
#define SIZE_RCTL_NO_ODCVM          6
#define SIZE_RCTL_ODCVM             6
#define SIZE_CVM_REQ_LIMIT          6
#define SIZE_TIME_OUT_VALUE         2
#define SIZE_IDS_STATUS             1
#define SIZE_OUTCOME_PARAM_SET      8
#define SIZE_DD_CARD_TRK1           56
#define SIZE_DD_CARD_TRK2           11
#define SIZE_MS_CVM_CAP_NO_CVM_REQ  1
#define SIZE_MSG_HOLD_TIME          3
#define SIZE_SELECTED_COMBINATION   17
#define SIZE_STATUS_BYTES           2
#define SIZE_HOLD_TIME_VALUE        1
#define SIZE_PHONE_MSG_TABLE        512
#define SIZE_MIN_RRGP               2
#define SIZE_MAX_RRGP               2
#define SIZE_TER_EXP_TRANSM_TIME_CA 2
#define SIZE_TER_EXP_TRANSM_TIME_RA 2
#define SIZE_ACCURACY_THRESHOLD     2
#define SIZE_TRANSM_TIME_MISMATCH_THRESHOLD 1
#define SIZE_TER_RR_ENTROPY         4
#define SIZE_DEV_RR_ENTROPY         4
#define SIZE_MIN_TIME_FOR_RRP       2
#define SIZE_MAX_TIME_FOR_RRP       2
#define SIZE_DEV_ESTIMATED_TRANSM_TIME      2
#define SIZE_MEASURED_RRP_TIME      2
#define SIZE_RRP_COUNTER            1
#define SIZE_ACTIVE_AFL             248
#define SIZE_ACTIVE_TAG             2
#define SIZE_AC_TYPE                1
#define SIZE_FAILED_MS_CNTR         1
#define SIZE_NEXT_CMD               1
#define SIZE_NUN                    1
#define SIZE_ODA_STATUS             1
#define SIZE_RCTL                   6
#define SIZE_STATIC_DATA_AUTH       2048
#define SIZE_TAGS_TO_READ_YET       512
#define SIZE_TAGS_TO_WRITE_YET_AFTER_GEN_AC     512
#define SIZE_TAGS_TO_WRITE_YET_BEFORE_GEN_AC    512
#define SIZE_TORN_ENTRY             1024
#define SIZE_TORN_TEMP_RECORD       1024
#define SIZE_TMP_UIREQUEST_DATA     22
#define SIZE_TORN_RECORD            1024
#define SIZE_TAGS_TO_WRITE_BEFORE_GEN_AC        512
#define SIZE_TAGS_TO_WRITE_AFTER_GEN_AC         512
#define SIZE_DATA_TO_SEND           512
#define SIZE_DATA_RECORD            512
#define SIZE_DIS_DATA               512

#ifdef __cplusplus
}
#endif

#endif
