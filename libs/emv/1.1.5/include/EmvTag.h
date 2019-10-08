#ifndef EMV_TAG_DEFINE_H
#define EMV_TAG_DEFINE_H
#include "MercurySystem.h"

#include "EmvDataType.h"
//#include <string.h>
/************************************************************************/
/* EMV                                                                  */
/************************************************************************/
#define TAG_IIN                                               0x42
#define TAG_AID                                               0x4F 
#define TAG_APP_LABEL                                         0x50
#define TAG_TRACK1_EQUIVALENT_DATA                            0x56
#define TAG_TRACK2_EQUIVALENT_DATA                            0x57
#define TAG_PAN                                               0x5A 
#define TAG_APP_TEMPLATE                                      0x61
#define TAG_FCI_TEMPLATE                                      0x6F 
#define TAG_RECORD_TEMPLATE                                   0x70
#define TAG_ISSUER_SCRIPT_TEMPLATE1                           0x71
#define TAG_ISSUER_SCRIPT_TEMPLATE2                           0x72
#define TAG_DIRECTORY_DISCRETIONARY_TEMPLATE                  0x73
#define TAG_RESPONSE_MSG_FORMAT2                              0x77
#define TAG_RESPONSE_MSG_FORMAT1                              0x80
#define TAG_AMOUNT_AUTHORISED_B                               0x81
#define TAG_AIP                                               0x82
#define TAG_COMMAND_TEMPLATE                                  0x83
#define TAG_DF_NAME                                           0x84
#define TAG_ISSUER_SCRIPT_COMMAND                             0x86
#define TAG_APP_PRIORITY_IDENTIFIER                           0x87
#define TAG_SFI                                               0x88
#define TAG_AUTHORISATION_CODE                                0x89
#define TAG_ARC                                               0x8A 
#define TAG_CDOL1                                             0x8C 
#define TAG_CDOL2                                             0x8D 
#define TAG_CVM_LIST                                          0x8E 
#define TAG_CAPK_INDEX                                        0x8F 
#define TAG_IPKC                                              0x90
#define TAG_IAD                                               0x91
#define TAG_IPK_REMAINDER                                     0x92
#define TAG_SSAD                                              0x93
#define TAG_AFL                                               0x94
#define TAG_TVR                                               0x95
#define TAG_TDOL                                              0x97
#define TAG_TC_HASH                                           0x98
#define TAG_TRANS_PIN_DATA                                    0x99
#define TAG_TRANSACTION_DATE                                  0x9A 
#define TAG_TSI                                               0x9B 
#define TAG_TRANSACTION_TYPE                                  0x9C 
#define TAG_DDF_NAME                                          0x9D 
#define TAG_FCI_PROPRIETARY_TEMPLATE                          0xA5 
// emv 新增
#define TAG_VISA_C2											  0xC2
#define TAG_VISA_C3											  0xC3
#define TAG_CARDHOLDER_NAME                                   0x5F20 
#define TAG_APP_EXPIRATION_DATE                               0x5F24 
#define TAG_APP_EFFECTIVE_DATE                                0x5F25 
#define TAG_ISSUER_COUNTRY_CODE                               0x5F28 
#define TAG_TRANSACTION_CURRENCY_CODE                         0x5F2A 
#define TAG_LANGUAGE_PREFERENCE                               0x5F2D 
#define TAG_SERVICE_CODE                                      0x5F30 
#define TAG_PAN_SEQ                                           0x5F34 
#define TAG_TRANSACTION_CURRENCY_EXPONENT                     0x5F36 
#define TAG_ISSUER_URL                                        0x5F50 
#define TAG_IBAN                                              0x5F53 
#define TAG_BIC                                               0x5F54 
#define TAG_ISSUER_COUNTRY_CODE_ALPHA2                        0x5F55 
#define TAG_ISSUER_COUNTRY_CODE_ALPHA3                        0x5F56 
#define TAG_ACCOUNT_TYPE                                      0x5F57
#define TAG_ACQUIRER_IDENTIFIER                               0x9F01 
#define TAG_AMOUNT_AUTHORISED_N                               0x9F02 
#define TAG_AMOUNT_OTHER_N                                    0x9F03 
#define TAG_AMOUNT_OTHER_B                                    0x9F04 
#define TAG_APP_DISCRETIONARY_DATA                            0x9F05 
#define TAG_AID_TERMINAL                                      0x9F06 
#define TAG_AUC                                               0x9F07 
#define TAG_APP_VERSION_NUMBER                                0x9F08 
#define TAG_APP_VERSION_NUMBER_TERMINAL                       0x9F09 
#define TAG_CARDHOLDER_NAME_EXTENDED                          0x9F0B 
#define TAG_IAC_DEFAULT                                       0x9F0D 
#define TAG_IAC_DENIAL                                        0x9F0E 
#define TAG_IAC_ONLINE                                        0x9F0F 
#define TAG_ISSUER_APPLICATION_DATA                           0x9F10 
#define TAG_ISSUER_CODE_TABLE_INDEX                           0x9F11 
#define TAG_APP_PREFERRED_NAME                                0x9F12 
#define TAG_LAST_ATC                                          0x9F13 
#define TAG_LOWER_CONSECUTIVE_OFFLINE_LIMIT                   0x9F14 
#define TAG_MERCHANT_CATEGORY_CODE                            0x9F15 
#define TAG_MERCHANT_IDENTIFIER                               0x9F16 
#define TAG_PIN_TRY_COUNTER                                   0x9F17 
#define TAG_ISSUER_SCRIPT_IDENTIFIER                          0x9F18 
#define TAG_TOKEN_USE_ID									  0x9F19 // emv新增
#define TAG_TERMINAL_COUNTRY_CODE                             0x9F1A 
#define TAG_TERMINAL_FLOOR_LIMIT                              0x9F1B 
#define TAG_TERMINAL_ID                                       0x9F1C 
#define TAG_TERMINAL_RISK_MANAGEMENT_DATA                     0x9F1D 
#define TAG_IFD_SERIAL_NUMBER                                 0x9F1E 
#define TAG_TRACK1_DESCRETIONARY_DATA                         0x9F1F 
#define TAG_TRACK2_DESCRETIONARY_DATA                         0x9F20 
#define TAG_TRANSACTION_TIME                                  0x9F21 
#define TAG_CAPK_INDEX_TERMINAL                               0x9F22 
#define TAG_UPPER_CONSECUTIVE_OFFLINE_LIMIT                   0x9F23
#define TAG_PAYMENT_ACCOUNT_REFERENCE                         0x9F24
#define TAG_APP_CRYPTOGRAM                                    0x9F26 
#define TAG_CID                                               0x9F27 
#define TAG_EXTENDED_SELECTION								  0x9F29 //Discover 
#define TAG_PEKC                                              0x9F2D 
#define TAG_PEK_EXPONENT                                      0x9F2E 
#define TAG_PEK_REMAINDER                                     0x9F2F 
#define TAG_IPK_EXPONENT                                      0x9F32 
#define TAG_TERMINAL_CAPABILITIES                             0x9F33 
#define TAG_CVM_RESULT                                        0x9F34 
#define TAG_TERMINAL_TYPE                                     0x9F35 
#define TAG_ATC                                               0x9F36 
#define TAG_UNPREDICTABLE_NUMBER                              0x9F37 
#define TAG_PDOL                                              0x9F38 
#define TAG_POS_ENTRY_MODE                                    0x9F39 
#define TAG_AMOUNT_REFERENCE_CURRENCY                         0x9F3A 
#define TAG_APPL_REFERENCE_CURRENCY                           0x9F3B 
#define TAG_TRANSACTION_REFERENCE_CURRENCY_CODE               0x9F3C 
#define TAG_TRANSACTION_REFERENCE_CURRENTY_EXPONENT           0x9F3D 
#define TAG_ADDITIONAL_TERMINAL_CAPABILITIES                  0x9F40 
#define TAG_TRANSACTION_SEQUENCE_COUNTER                      0x9F41 
#define TAG_APP_CURRENCY_CODE                                 0x9F42 
#define TAG_APP_REFERENCE_CURRENCY_EXPONENT                   0x9F43 
#define TAG_APP_CURRENCY_EXPONENT                             0x9F44 
#define TAG_DAC                                               0x9F45 
#define TAG_ICCPKC                                            0x9F46 
#define TAG_ICCPK_EXPONENT                                    0x9F47 
#define TAG_ICCPK_REMAINDER                                   0x9F48 
#define TAG_DDOL                                              0x9F49 
#define TAG_SDA_TAG_LIST                                      0x9F4A 
#define TAG_SDAD                                              0x9F4B 
#define TAG_ICC_DYNAMIC_NUMBER                                0x9F4C 
#define TAG_LOG_ENTRY                                         0x9F4D 
#define TAG_MERCHANT_NAME_AND_LOCATION                        0x9F4E 
#define TAG_LOG_FORMAT                                        0x9F4F 
#define TAG_APP_PROGRAME_ID									  0x9F5A// 非emv
#define TAG_AOSA				              				  0x9F5D// 非emv
#define TAG_HOLDER_CERTIFICATION							  0x9F61 //Holder certificate(PBOC)	
#define TAG_CERTIFICATION_TYPE							  	  0x9F62 //Certificate type(PBOC)
#define TAG_PBOC_PRODUCT_INFO               				  0x9F63 // 非emv
#define TAG_TERMINAL_TRANSACTION_QUALIFIERS               	  0x9F66 // 非emv
#define TAG_CARD_ADDITIONAL_PROCESS	               	  		  0x9F68 //Card Additional Processes
#define TAG_CARD_AUTH_RELATED_DATA 							  0x9F69 // 非emv
#define TAG_CARD_CVM_LIMIT 				  	                  0x9F6B //Card CVM Limit	// 非emv 
#define TAG_CARD_TRANSACTION_QUALIFIERS 				  	  0x9F6C // 非emv
#define TAG_EC_RESET_THRESHOLD				  	              0x9F6D //EC Reset Threshold  电子现金重置阈值
#define TAG_FORM_FACTOR_INDICATOR                             0x9F6E // 非emv
#define TAG_CURRENCY_CONVER_FACTOR                            0x9F73 // emv 新增 visa
#define TAG_EC_ISSUER_AUTH_CODE                               0x9F74 //EC Issuer Authorization Code 电子现金发卡行授权码																			
#define TAG_EC_BALANCE_LIMIT                                  0x9F77 //  Electronic Cash Balance Limit 电子现金余额上限
#define TAG_EC_SIGNLE_TRANS_LIMIT                             0x9F78 // EC Single Transaction Limit 电子现金单笔交易限额
#define TAG_EC_BALANCE                           			  0x9F79 //  Electronic Cash Balance 电子现金余额
#define TAG_EC_TERMINAL_SUPPROT_INDICATOR                     0x9F7A //EC Terminal Support Indicator 电子现金终端支持指示器
#define TAG_EC_TERMINAL_TRANS_LIMIT                           0x9F7B //EC Terminal Transaction Limit 电子现金终端交易限额
#define TAG_CUSTOMER_EXCLUSIVE_DATA                           0x9F7C
#define TAG_FCI_ISSUER_DISCRETIONARY_DATA                     0xBF0C 


/************************************************************************/
/*   QPBOC - VISA                                                       */
/************************************************************************/
#define TAG_PAYMENT_ACCOUNT_REFERENCE                         0x9F24
#define TAG_AOSA				              				  0x9F5D
#define TAG_TERMINAL_TRANSACTION_QUALIFIERS               	  0x9F66
#define TAG_CARD_AUTH_RELATED_DATA 							  0x9F69
#define TAG_CARD_TRANSACTION_QUALIFIERS 				  	  0x9F6C
#define TAG_CUSTOMER_EXCLUSIVE_DATA                           0x9F7C
#define TAG_FCI_ISSUER_DISCRETIONARY_DATA                     0xBF0C 
#define TAG_APP_CURRENCY_CODE_ICC							  0x9F51
#define TAG_PBOC_CREDENTIALS_NUMBER							  0x9F61
#define TAG_PBOC_CREDENTIALS_TYPE							  0x9F62
#define TAG_PBOC_PRODUCT_INFO               				  0x9F63
#define TAG_SM_IDENTIFY										  0xDF69
#define TAG_FORM_FACTOR_INDICATOR                             0x9F6E //QUICS 认证中用到. 跟AMEX 重复.
#define TAG_APP_PROGRAME_ID									  0x9F5A //VISA 使用到TAG.
#define TAG_PBOC_CARD_ADD_FUNCTION							  0xDF61 //QUICS 卡片增值功能.
#define TAG_EC_SECONDARY_APP_CURRENCY_CODE					  0xDF71 //QUICS 免密免签.

/************************************************************************/
/*   Expresspay                                                         */
/************************************************************************/
#define TAG_MEMBERSHIP_PRODUCT_IDENTIFIER					  0x9F5A // 注意 重复 .
#define TAG_PRODUCT_MEMBERSHIP_NUMBER						  0x9F5B
#define TAG_KERNEL_IDENTIFIER								  0x9F2A
#define TAG_DUAL_CURRENCY_CODE								  0x9F50
#define TAG_CONTACTLESS_READER_CAPABILITIES					  0x9F6D
#define TAG_ENHANCED_CONTACTLESS_READER_CAPABILITIES		  0x9F6E
#define TAG_MOBILE_CVM_RESULTS								  0x9F71
#define TAG_CARD_INTERFACE_AND_PAYMENT_CAPABILITIES			  0x9F70
#define TAG_SPECIFIC_REGISTERED_PROPRIETARY_DATA			  0x9F0A

/************************************************************************/
/*   Discover                                                           */
/************************************************************************/
#define TAG_PAYMENT_APPLICATION_VERSION_NUMBER				  0x9F7D //Discover
#define TAG_CARD_PROCESSING_REQUIREMENTS					  0x9F71			
#define TAG_OFFLINE_BALANCE									  0xD1	
#define TAG_DCVV_2											  0x9F7E
#define TAG_DCVV_1											  0x9F80
#define TAG_CARD_VERIFICATION_RESULTS						  0x9F53





/************************************************************************/
/*   MIR	                                                            */
/************************************************************************/
#define TAG_MIR_APPLICATION_INFO							  0xDF70
#define TAG_MIR_ODOL										  0xDF6F
#define TAG_MIR_SIGNED_APPLICATION							  0xBF61
#define TAG_MIR_UNSIGNED_APPLICATION						  0xBF62
#define TAG_MIR_CARD_PROCESSING_REQUIREMENTS				  0x9F71
#define TAG_MIR_CARD_VERIFICATION_RESULTS					  0x9F52
#define TAG_MIR_EXTENDED_SELECTION							  0x9F2A

#define TAG_MIR_CDA_RESULT									  0x9F70
#define TAG_MIR_TPM_CAPABILITIES							  0xDF55
#define TAG_MIR_TPM											  0xDF71
#define TAG_MIR_KVR											  0xDF74



//Data Exchange Tag List 
#define TAG_MIR_DATA_EXCHANGE_TAG_LIST						  0xFF04

/************************************************************************/
/* MasterCard                                                           */
/************************************************************************/
#define TAG_MASTER_DS_REQ_OPE_ID                   0x9F5C
#define TAG_MASTER_APP_CAP_INFO					   0x9F5D
#define TAG_MASTER_DS_ID                           0x9F5E
//PBOC 返回



#define TAG_MASTER_CVC3_TRACK1								  0x9F60
#define TAG_MASTER_CVC3_TRACK2                  			  0x9F61
#define TAG_MASTER_PCVC3_TRACK1								  0x9F62
#define TAG_MASTER_PUNATC_TRACK1                			  0x9F63
#define TAG_MASTER_NATC_TRACK1                  			  0x9F64
#define TAG_MASTER_PCVC3_TRACK2                 			  0x9F65
#define TAG_MASTER_PUNATC_TRACK2                			  0x9F66
#define TAG_MASTER_NATC_TRACK2                  			  0x9F67
#define TAG_MASTER_UDOL                         			  0x9F69
#define TAG_MASTER_TRACK2                       			  0x9F6B
#define TAG_MASTER_TERMINAL_APP_VERSION         			  0x9F6D
#define TAG_MASTER_TRACK1                       			  0x56
//未用到.
#define TAG_MASTER_PAR							   0x9F24
#define TAG_MASTER_KERNEL_IDENTIFIER               0x9F2A
#define TAG_MASTER_OFF_ACC_BALANCE                 0x9F50
#define TAG_MASTER_DRDOL                           0x9F51
#define TAG_MASTER_TRAN_CAT_CODE                   0x9F53
#define TAG_MASTER_DS_ODS_CARD                     0x9F54
#define TAG_MASTER_DSDOL                           0x9F5B



#define TAG_MASTER_DS_SLOT_AVAIL                   0x9F5F
#define TAG_MASTER_UN_NUM_N                        0x9F6A
#define TAG_MASTER_THIRD_PARTY_DATA                0x9F6E
#define TAG_MASTER_DS_SLOT_MANAG_MASTER_CTL        0x9F6F
#define TAG_MASTER_PDE_1                           0x9F70
#define TAG_MASTER_PDE_2                           0x9F71
#define TAG_MASTER_PDE_3                           0x9F72
#define TAG_MASTER_PDE_4                           0x9F73
#define TAG_MASTER_PDE_5                           0x9F74
#define TAG_MASTER_UNPDE_1                         0x9F75
#define TAG_MASTER_UNPDE_2                         0x9F76
#define TAG_MASTER_UNPDE_3                         0x9F77
#define TAG_MASTER_UNPDE_4                         0x9F78
#define TAG_MASTER_UNPDE_5                         0x9F79
#define TAG_MASTER_MER_CUSTOM_DATA                 0x9F7C
#define TAG_MASTER_DS_SUMMARY_1                    0x9F7D
#define TAG_MASTER_MSI                             0x9F7E
#define TAG_MASTER_DS_UN_NUM                       0x9F7F
#define TAG_MASTER_FCI_ISS_DIS_DATA                0xBF0C
#define TAG_MASTER_PCI_INFO                        0xDF4B
#define TAG_MASTER_DS_INPUT_CARD                   0xDF60
#define TAG_MASTER_DS_DIGEST_H                     0xDF61
#define TAG_MASTER_DS_ODS_INFO                     0xDF62
#define TAG_MASTER_DS_ODS_TERM                     0xDF63
#define TAG_MASTER_DS_SUMMARY_2                    0xDF8101
#define TAG_MASTER_DS_SUMMARY_3                    0xDF8102
#define TAG_MASTER_BALANCE_BEF_GAC                 0xDF8104
#define TAG_MASTER_BALANCE_AFT_GAC                 0xDF8105
#define TAG_MASTER_DATA_NEEDED                     0xDF8106
#define TAG_MASTER_CDOL1_REL_DATA                  0xDF8107
#define TAG_MASTER_DS_AC_TYPE                      0xDF8108
#define TAG_MASTER_DS_INPUT_TERM                   0xDF8109
#define TAG_MASTER_DS_ODS_INFO_FOR_READER          0xDF810A
#define TAG_MASTER_DS_SUMMARY_STATUS               0xDF810B
#define TAG_MASTER_KERNEL_ID                       0xDF810C
#define TAG_MASTER_DSVN_TERM                       0xDF810D
#define TAG_MASTER_POST_GAC_PUT_DATA_STATUS        0xDF810E
#define TAG_MASTER_PRE_GAC_PUT_DATA_STATUS         0xDF810F
#define TAG_MASTER_PROCEED_TO_FIRST_WRITE_FLAG     0xDF8110
#define TAG_MASTER_PDOL_REL_DATA                   0xDF8111
#define TAG_MASTER_TAGS_TO_READ                    0xDF8112
#define TAG_MASTER_DRDOL_RELATED_DATA              0xDF8113
#define TAG_MASTER_REF_CTL_PARAM                   0xDF8114
#define TAG_MASTER_ERR_ID                          0xDF8115
#define TAG_MASTER_UI_REQ_DATA                     0xDF8116
#define TAG_MASTER_CARD_DATA_INPUT_CAP							0xDF8117
#define TAG_MASTER_CVM_CAP_CVM_REQ                 0xDF8118
#define TAG_MASTER_CVM_CAP_NO_CVM_REQ              0xDF8119
#define TAG_MASTER_DEFAULT_UDOL                    0xDF811A
#define TAG_MASTER_KERNEL_CONFIG                   0xDF811B
#define TAG_MASTER_MAX_TORN_LIFETIME               0xDF811C
#define TAG_MASTER_MAX_TORN_NUM                    0xDF811D
#define TAG_MASTER_MS_CVM_CAP_CVM_REQ              0xDF811E
#define TAG_MASTER_SECURITY_CAP                    0xDF811F
#define TAG_MASTER_TAC_DEFAULT                     0xDF8120
#define TAG_MASTER_TAC_DENIAL                      0xDF8121
#define TAG_MASTER_TAC_ONLINE                      0xDF8122
#define TAG_MASTER_RCFL                            0xDF8123
#define TAG_MASTER_RCTL_NO_ODCVM                   0xDF8124
#define TAG_MASTER_RCTL_ODCVM                      0xDF8125
#define TAG_MASTER_CVM_REQ_LIMIT                   0xDF8126
#define TAG_MASTER_TIME_OUT_VALUE                  0xDF8127
#define TAG_MASTER_IDS_STATUS                      0xDF8128
#define TAG_MASTER_OUTCOME_PARAM_SET               0xDF8129
#define TAG_MASTER_DD_CARD_TRK1                    0xDF812A
#define TAG_MASTER_DD_CARD_TRK2                    0xDF812B
#define TAG_MASTER_MS_CVM_CAP_NO_CVM_REQ           0xDF812C
#define TAG_MASTER_MSG_MASTER_HOLD_TIME            0xDF812D
#define TAG_MASTER_SELECTED_COMBINATION            0xDF812E
#define TAG_MASTER_STATUS_BYTES                    0xDF812F
#define TAG_MASTER_HOLD_TIME_VALUE                 0xDF8130
#define TAG_MASTER_PHONE_MSG_MASTER_TABLE          0xDF8131
#define TAG_MASTER_MIN_RRGP                        0xDF8132
#define TAG_MASTER_MAX_RRGP                        0xDF8133
#define TAG_MASTER_TER_EXP_TRANSM_TIME_CA          0xDF8134
#define TAG_MASTER_TER_EXP_TRANSM_TIME_RA          0xDF8135
#define TAG_MASTER_ACCURACY_THRESHOLD              0xDF8136
#define TAG_MASTER_TRANSM_TIME_MISMATCH_THRESHOLD  0xDF8137
#define TAG_MASTER_TER_RR_ENTROPY                  0xDF8301
#define TAG_MASTER_DEV_RR_ENTROPY                  0xDF8302
#define TAG_MASTER_MIN_TIME_FOR_RRP                0xDF8303
#define TAG_MASTER_MAX_TIME_FOR_RRP                0xDF8304
#define TAG_MASTER_DEV_ESTIMATED_TRANSM_TIME       0xDF8305
#define TAG_MASTER_MEASURED_RRP_TIME               0xDF8306
#define TAG_MASTER_RRP_COUNTER                     0xDF8307
#define TAG_MASTER_ACTIVE_AFL                      0xDF8801
#define TAG_MASTER_ACTIVE_TAG                      0xDF8802
#define TAG_MASTER_AC_TYPE						   0xDF8803
#define TAG_MASTER_FAILED_MS_CNTR                  0xDF8804
#define TAG_MASTER_NEXT_CMD                        0xDF8805
#define TAG_MASTER_NUN                             0xDF8806
#define TAG_MASTER_ODA_STATUS                      0xDF8807
#define TAG_MASTER_RCTL                            0xDF8808
#define TAG_MASTER_STATIC_DATA_AUTH                0xDF8809
#define TAG_MASTER_TAGS_TO_READ_YET                0xDF8810
#define TAG_MASTER_TAGS_TO_WRITE_YET_AFTER_GEN_AC  0xDF8811
#define TAG_MASTER_TAGS_TO_WRITE_YET_BEFORE_GEN_AC 0xDF8812
#define TAG_MASTER_TORN_ENTRY                      0xDF8813
#define TAG_MASTER_TORN_TEMP_RECORD                0xDF8814
#define TAG_MASTER_TMP_UIREQUEST_DATA              0xDF8815
#define TAG_MASTER_TORN_RECORD                     0xFF8101
#define TAG_MASTER_TAGS_TO_WRITE_BEFORE_GEN_AC     0xFF8102
#define TAG_MASTER_TAGS_TO_WRITE_AFTER_GEN_AC      0xFF8103
#define TAG_MASTER_DATA_TO_SEND                    0xFF8104
#define TAG_MASTER_DATA_RECORD                     0xFF8105
#define TAG_MASTER_DIS_DATA                        0xFF8106

/************************************************************************/
/* PC端后台自定义TAG, 只为认证                                          */
/************************************************************************/
#define TAG_TRACK2_DATA                                       0xDF03
#define TAG_TRACK1_DATA                                       0xDF04

#define TAG_DISCOVER_TRACK1_DATA                              0xDF05
#define TAG_DISCOVER_TRACK2_DATA                              0xDF06

#define TAG_FINAL_OUTCOME									  0xDF07
#define TAG_OUTCOME_CVM										  0xDF08
#define TAG_OUTCOME_MESSAGE									  0xDF09
#define TAG_OUTCOME_STATUS									  0xDF0A

#define TAG_SIGNED_APPLICATION								  0xDF0B
#define TAG_UNSIGNED_APPLICATION							  0xDF0C
#define TAG_TRACK2_DATA                                       0xDF03
#define TAG_SCRIPT_RESULT									  0xDF31 // 脚本结果

#define TAG_SM_NA                                       	  0xDF60  // add by wl 20171214 增加国密
#define TAG_SM_FLAG                                       	  0xDF69  // add by wl 20171214 增加国密


#define TAG_PBOC_PRODUCT_INFO               				  0x9F63

#endif

