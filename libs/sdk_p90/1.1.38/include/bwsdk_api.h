//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2018 �Ϻ�ʢ�����ܿƼ��ɷ����޹�˾
/// All rights reserved.
/// 
/// @file     bwsdk_api.h
/// @brief    ʢ��SDKͷ�ļ�����
/// @brief    BaseWin SDK header
/// @copyright Shanghai Basewin Technology Co.,Ltd.
/// @version  1.0
/// @date     01/28/2018
//////////////////////////////////////////////////////////////////////////////

#ifndef _BWSDK_API_H_
#define _BWSDK_API_H_

#include "MercurySystem.h"

#ifdef __cplusplus
extern   "C"
{
#endif

//#define SP_DEPRECATED_API

/**
 * @defgroup BWSDK BWSDK
 * @brief Basewin SDK APIs
 * @{
 */

/**
 * @defgroup utils utils
 * @brief Utils API
 * @{
 */

#ifdef uchar
#undef uchar
#endif

#define uchar unsigned char     ///< uchar 

#ifdef ulong
#undef ulong
#endif
#define ulong unsigned long     ///< ulong

#ifdef ushort
#undef ushort
#endif
#define ushort unsigned short   ///< ushort

/**
 * @brief there is no such interface within system
 * @brief ϵͳû���ṩsnprintf
 */
int BW_snprintf(char *str, unsigned int size, const char *format, ...);

/**
 * @brief there is no such interface within system
 * @brief ϵͳû���ṩstrcasecmp
 */
int BW_strcasecmp(const char *s1, const char *s2);

/**
 * @brief there is no such interface within system
 * @brief ϵͳû���ṩstrncasecmp
 */
int BW_strncasecmp(const char *s1, const char *s2, int n);

//=============================================================
//#include "hexutile.h"
//=============================================================

/**
 * @brief Host to Network short (Big-endian)
 * @brief �������ֽ���ת��Ϊ������(���)
 */
unsigned short int htons(unsigned short int h);

/**
 * @brief Network (Big-endian) to Host short
 * @brief ������(���)ת��Ϊ�������ֽ���
 */
unsigned short int ntohs(unsigned short int n);

/**
 * @brief Host to Network long (Big-endian)
 * @brief �������ֽ���ת��Ϊ������(���)
 */
unsigned long htonl(unsigned long h);

/**
 * @brief Network (Big-endian) to Host long
 * @brief ������(���)ת��Ϊ�������ֽ���
 */
unsigned long ntohl(unsigned long n);

/**
 * @brief Judge whether a string is a pure HEX string (a-f allows case)
 * @brief �ж�һ���ַ����Ƿ��Ǵ�HEX�ַ���(A-F�����Сд)
 * @param hexstr [in] �ַ���(hex string) 
 * @param hexstrlen [in] �ַ�������(length of the hex string)
 * @retval 0 ����HEX�ִ�(return value 0: not hex string)
 * @retval 1 ��HEX�ִ�(return value 1: is hex string)
 */
int IsHexString(const char *hexstr, unsigned int hexstrlen);


/**
 * @brief Transfer Hex string to Byte array
 * @brief ��HEX�ִ�ת��Ϊ�ֽ�����
 *  "12345678" -> {0x12, 0x34, 0x56, 0x78}
 * @param hexstr [in] �����HEX�ִ� (Input Hex string)
 * @param hexstrlen [in] HEX�ִ��ĳ��� (Input Hex string length)
 * @param buff [out] ������ֽ����ݻ����� (Output buffer)
 * @param buffsize [in] ����������ֽ��� (Buffer size), [out] ת���������ֽ��� (Output Byte array size)
 * @retval 0 ת���ɹ� (return value 0: Transfer success)
 * @retval <0 ת��ʧ�� (return valie <0: Transfer fail)
 */
int HexStringToBytes(const char *hexstr, unsigned int hexstrlen, void *buff, unsigned int *buffsize);

/**
 * @brief Transfer Byte array to Hex string
 * @brief ���ֽ�����ת��ΪHEX�ִ�
 *  {0x12, 0x34, 0x56, 0x78} -> "12345678"
 * @param buff [in] ������ֽ����� (Input Byte array)
 * @param bufflen [in] ������ֽ����ݳ��� (Input Byte array length)
 * @param hexstr [out] �����HEX�ִ������� (Output Hex string buffer)
 * @param hexstrlen [in] HEX�ִ�����������ֽ��� (Hex string buffer size), [out] ת��������HEX�ִ����� (Output Hex string buffer size)
 * @retval 0 ת���ɹ� (return value 0: Transfer success)
 * @retval <0 ת��ʧ�� (return value <0: Transfer fail)
 */
int BytesToHexString(const char *buff, unsigned int bufflen, char *hexstr, unsigned int *hexstrlen);

/**
 * @brief Transfer Byte Array sequence
 * @brief ת���ֽ���
 * BitEndian -> LittleEndian
 * LittleEndian -> BitEndian
 * from��to����һ�� (Input and Output buffer can be same)
 * {0x12, 0x34, 0x56} -> {0x56, 0x34, 0x12}
 * 0x123456 -> 0x563412
 * @param from [in] ��Դ������ (Input buffer)
 * @param to [in] Ŀ�Ļ����� (Output buffer)
 * @param len [in] Ҫת���ĳ���(��λ: Byte) (Transfer length)
 * @retval None
 */
void SwapBytesOrder(void *from, void *to, unsigned int len);

/**
 * @brief Transfer Byte array to Hex string
 * @brief ���ֽ�����ת��ΪHEX�ַ���
 * ������BytesToHexStringһ�� (Same with Function "BytesToHexString")
 * {0x12, 0x34} -> "1234"
 * @param One [in] Ҫת�����ֽ����� (Input Byte array)
 * @param len [in] �ֽ����鳤�� (Input Byte array length)
 * @param Two [out] �����HEX�ַ��� (Output Hex String)
 * @retval None
 */
void vOneTwo(unsigned char *One, unsigned short len, unsigned char *Two);

/**
 * @brief Transfer Hex string to Byte array
 * @brief ��HEX�ַ���ת��Ϊ�ֽ�����
 * ������HexStringToBytesһ�� (Same with Function "HexStringToBytes")
 * "1234" -> {0x12, 0x34}
 * @param in [in] Ҫת����HEX�ַ��� (Input Hex string)
 * @param in_len [in] HEX�ַ������� (Input Hex string length)
 * @param out [out] ������ֽ����� (Outout Byte array)
 * @retval ת����out�е��ֽڳ��� (return value: Output Byte array length)
 */
int vTwoOne(unsigned char *in, unsigned short in_len, unsigned char *out);


/**
 * @brief Large Number Converter
 * @brief ������ת����ֵ
 * "010001" -> "65537"(16-10����)
 * @param oldData [in] Ҫת����ԭ���� (Input Number)
 * @param oldDataConv [in] ԭ���ݵ���ֵ(2,8,10,16����) (Input Number System, for example: binary, octal, decimal or hex)
 * @param conv [in] Ҫת������ֵ(2,8,10,16����) (Output Number System, for example: binary, octal, decimal or hex)
 * @param convData [out] ת��������� (Output)
 * @param sizeConvData [int] ������ݵĴ�С(sizeof(convData))
 * @retval >0 ת�������ݳ��� (return value > 0: length of data converted)
 * @retval <=0 ת��ʧ�� (return value <= 0: convert fail)
 */
int bigNumberConv(char *oldData,int oldDataConv,int conv,char *convData,int sizeConvData);

// #include "gbk2utf8.h"
/**
 * @brief Convert GBK code to Unicode
 * @brief ��һ��GBK�����ַ�ת��Ϊunicode����
 */
unsigned short conv_char_gbk2unicode(unsigned short int gbkcode);

/**
 * @brief Convert Unicode to GBK code
 * @brief ��һ��unicode�����ַ�ת��ΪGBK����
 */
unsigned short conv_char_unicode2gbk(unsigned short int unicode);

/**
 * @brief Convert specified length of GBK string to Unicode string
 * @brief ��ָ�����ȵ�GBK�ִ�ת��Ϊunicode�ִ�
 */
int conv_string_gbk2unicode(unsigned short int *unicode, char *gbk, int len);

/**
 * @brief Convert specified length of Unicode string to GBK string
 * @brief ��ָ�����ȵ�unicode�ִ�ת��ΪGBK�ִ�
 */
int conv_string_unicode2gbk(char *gbk, unsigned short int *unicode, int len);

/**
 * @brief Convert Unicode string to utf8 string
 * @brief ��ָ��unicode�ִ�ת��Ϊutf8�ִ�
 */
int conv_string_UnicodeToUtf8(char *pInput, char *pOutput);

/**
 * @brief Convert utf8 string to Unicode string
 * @brief ��ָ��utf8�ִ�ת��Ϊunicode�ִ�
 */
int conv_string_Utf8ToUnicode(char *pInput, char *pOutput);

/**
 * @brief Convert GBK string to utf8 string
 * @brief ��ָ��gbk�ִ�ת��Ϊutf8�ִ�
 */
int gbk2utf8(uchar *gbk, uchar *utf8);

/**
 * @brief Convert utf8 string to GBK string
 * @brief ��ָ��utf8�ִ�ת��Ϊgbk�ִ�
 */
int utf82gbk(uchar *utf8, uchar *gbk);
/** @} utils */


/**
 * @defgroup SP SP
 * @brief Security processor module APIs
 * @{
 */

/**
 * @defgroup Iccard Iccard
 * @brief ICC and PSAM module APIs
 * @{
 */
//=============================================================
//#include "bw_icc.h"
//=============================================================


#define ICC_APDU_LEN_MIN        4   ///< Minimum bytes of C-APDU
#define ICC_APDU_LEN_MAX        260 ///< Maximum bytes of C-APDU
#define ICC_SW_SIZE             2   ///< Bytes of Status-Word

/**
 * @brief ICC/PSAM slot number
 */
typedef enum {
    ICC_SLOT = 0, ///< ICC usercard slot
    PSAM1_SLOT,   ///< PSAM1 slot
    PSAM2_SLOT,   ///< PSAM2 slot
} IccSlot_t;


#define ICC_ISO7816_SLOT_MASK   (0<<7) ///< Bitmask of spec ISO7816
#define ICC_EMV_SLOT_MASK       (1<<7) ///< Bitmask of spec EMV
#define ICC_CITYCARD_SLOT_MASK  (1<<6) ///< Bitmask of spec China City Card
#define ICC_PPS_SUPP_MASK       (1<<5) ///< Bitmask of PPS enable/disable

#define ICC_BDR_9600_TLV        "\x41\x01\x11" ///< ICC/PSAM baudrate 9600
#define ICC_BDR_19200_TLV       "\x41\x01\x12" ///< ICC/PSAM baudrate 19200
#define ICC_BDR_38400_TLV       "\x41\x01\x13" ///< ICC/PSAM baudrate 38400


/**
 * @brief  Card check
 * @details  Check whether ICC/PSAM is exist or not.
 * @retval  0: SUCCESS(card exist)
 * @retval  <0: FAIL
 * @pre None
 */
int IccStatusRev(void);


/**
 * @brief Card Reset
 * @details ICC/PSAM reset and get ATR.
 * @param [out] pucATR: point of ATR buffer. if NULL, no ATR will be output.
 * @retval >=0: Success, Length of ATR
 * @retval <0: Fail
 * @pre None
 */
int IccResetRev(unsigned char *pucATR);

/**
 * @brief Card powerOff
 * @details ICC/PSAM power off.
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int IccCloseRev(void);


/**
 * @brief Select card slot
 * @details Select card slot, card specification and PPS feature.
 * @param [in] ucSlot:
 * -#                [7:6] spec mask
 * -#                [5]   pps mask
 * -#                [0:3] slot number
 * @see:: ICC_ISO7816_SLOT_MASK
 * @see:: ICC_EMV_SLOT_MASK
 * @see:: ICC_CITYCARD_SLOT_MASK
 * @see:: ICC_PPS_SUPP_MASK
 * @see:: IccSlot_t
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int IccSelectSlotRev(unsigned char ucSlot);

/**
 * @brief Select card slot
 * @details Select card slot, card specification and PPS feature and set parameters
 * @param [in] ucSlot:
 * -#                [7:6] spec mask
 * -#                [5]   pps mask
 * -#                [0:3] slot number
 * @see:: ICC_ISO7816_SLOT_MASK
 * @see:: ICC_EMV_SLOT_MASK
 * @see:: ICC_CITYCARD_SLOT_MASK
 * @see:: ICC_PPS_SUPP_MASK
 * @see:: IccSlot_t
 * @param [in] pucTLVs: baudrate and voltage TLV
 * @see:: ICC_BDR_9600_TLV
 * @see:: ICC_BDR_19200_TLV
 * @see:: ICC_BDR_38400_TLV
 * @param [in] uiTLVsLen: length of TLVs
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int IccSelectSlotByParamterRev(unsigned char ucSlot, unsigned char *pucTLVs, unsigned int uiTLVsLen);

/**
 * @brief Set reponse mode
 * @details Set the mode that the get response command send by SP or by APP.
 * @param [in] ucAutoFlag:
 * -# 0: disable
 * -# 1: enable(Default, get response by SP)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int IccGetResponseEnableRev(unsigned char ucAutoFlag);

/**
 * @brief APDU exchange
 * @param [in] pucCmd:   C-APDU
 * @param [in] uiCmdLen: Length of C-APDU
 * @param [in] pucRsp:   R-APDU
 * @param [in] pucSW:    Status-Word(2 bytes)
 * @retval  >=0: Success, Length of R-APDU
 * @retval  <0: Fail
 * @pre None
 */
int IccApduTransmit(unsigned char *pucCmd, unsigned int uiCmdLen, unsigned char *pucRsp, unsigned char *pucSW);

/**
 * @brief APDU exchange
 * @param [in] pucCmd:   C-APDU
 * @param [in] uiCmdLen: Length of C-APDU
 * @param [in] pucRsp:   R-APDU
 * @param [in] pucSW:    Status-Word(2 bytes)
 * @param [in] uiTimeoutMs: Command timeout for response.
 * @retval  >=0: Success, Length of R-APDU
 * @retval  <0: Fail
 * @pre None
 */
int IccApduTransmitExt(unsigned char *pucCmd, unsigned int uiCmdLen, unsigned char *pucRsp, unsigned char *pucSW, unsigned int uiTimeoutMs);

/** @} Iccard */


/**
 * @defgroup MemoryCard MemoryCard
 * @brief MemoryCard Module APIs
 * @{
 */
//=============================================================
//#include "bw_memic.h"
//=============================================================

#define MEMIC_ZONE_NONE     0xFF    ///< No zone indicated(Absolute address used) or card with no mutil zone

/*
 * @brief Zone length define of AT88SC101
 */
#define AT88SC101_FZ_LEN        2 ///<
#define AT88SC101_IZ_LEN        8 ///<
#define AT88SC101_SC_LEN        2 ///<
#define AT88SC101_SCAC_LEN      2 ///<
#define AT88SC101_CPZ_LEN       8 ///<
#define AT88SC101_AZ1_LEN       128 ///<
#define AT88SC101_EZ1_LEN       4 ///<
#define AT88SC101_EC_LEN        16 ///<
#define AT88SC101_MTZ_LEN       2 ///<

/*
 * @brief Zone length define of AT88SC102
 */
#define AT88SC102_FZ_LEN        2 ///<
#define AT88SC102_IZ_LEN        8 ///<
#define AT88SC102_SC_LEN        2 ///<
#define AT88SC102_SCAC_LEN      2 ///<
#define AT88SC102_CPZ_LEN       8 ///<
#define AT88SC102_AZ1_LEN       64 ///<
#define AT88SC102_EZ1_LEN       6 ///<
#define AT88SC102_AZ2_LEN       64 ///<
#define AT88SC102_EZ2_LEN       4 ///<
#define AT88SC102_EC_LEN        16 ///<
#define AT88SC102_MTZ_LEN       2 ///<

/*
 * @brief Zone length define of AT88SC1604
 */
#define AT88SC1604_FZ_LEN       2 ///<
#define AT88SC1604_IZ_LEN       8 ///<
#define AT88SC1604_SC_LEN       2 ///<
#define AT88SC1604_SCAC_LEN     1 ///<
#define AT88SC1604_CPZ_LEN      8 ///<
#define AT88SC1604_SC1_LEN      2 ///<
#define AT88SC1604_S1AC_LEN     1 ///<
#define AT88SC1604_EZ1_LEN      2 ///<
#define AT88SC1604_E1AC_LEN     1 ///<
#define AT88SC1604_AZ1_LEN      1195 ///<
#define AT88SC1604_SC2_LEN      2 ///<
#define AT88SC1604_EZ2_LEN      2 ///<
#define AT88SC1604_E2AC_LEN     1 ///<
#define AT88SC1604_AZ2_LEN      256 ///<
#define AT88SC1604_SC3_LEN      2 ///<
#define AT88SC1604_SC3_LEN      2 ///<
#define AT88SC1604_EZ3_LEN      2 ///<
#define AT88SC1604_E3AC_LEN     1 ///<
#define AT88SC1604_AZ3_LEN      256 ///<
#define AT88SC1604_SC4_LEN      2 ///<
#define AT88SC1604_EZ4_LEN      2 ///<
#define AT88SC1604_E4AC_LEN     1 ///<
#define AT88SC1604_AZ4_LEN      256 ///<
#define AT88SC1604_MTZ_LEN      2 ///<

#define AT88SC1604_SCEZ_LEN     2 ///<

/**
 * @brief Zone of AT88SC101. Not support yet.
 * @note Refer to AT88SC1014 datasheet
 */
typedef enum {
    AT88SC101_FZ = 0,       ///< �����̴�����, 2Byte
    AT88SC101_IZ,           ///< �����̴�����, 8Byte
    AT88SC101_SC,           ///< ��������, 2Byte
    AT88SC101_SCAC,         ///< ��������������, 2Byte
    AT88SC101_CPZ,          ///< ���뱣����, 8Byte
    AT88SC101_AZ1,          ///< Ӧ��1��, 128Byte
    AT88SC101_EZ1,          ///< Ӧ��1����������������, 4Byte
    AT88SC101_EC,           ///< ɾ��������, 16Byte
    AT88SC101_MTZ,          ///< ������, 2Byte
} at88sc101_zone_t;

/**
 * @brief Zone of AT88SC102
 * @note Refer to AT88SC102 datasheet
 */
typedef enum {
    AT88SC102_FZ = 0,       ///< �����̴�����, 2Byte
    AT88SC102_IZ,           ///< �����̴�����, 8Byte
    AT88SC102_SC,           ///< ��������, 2Byte
    AT88SC102_SCAC,         ///< ��������������, 2Byte
    AT88SC102_CPZ,          ///< ��Ƭ���뱣����, 8Byte
    AT88SC102_AZ1,          ///< Ӧ��1��, 64Byte
    AT88SC102_EZ1,          ///< Ӧ��1����������������, 6Byte
    AT88SC102_AZ2,          ///< Ӧ��2��, 64Byte
    AT88SC102_EZ2,          ///< Ӧ��2����������������, 4Byte
    AT88SC102_EC,           ///< Ӧ��2������������, 16Byte
    AT88SC102_MTZ,          ///< ������, 2Byte
} at88sc102_zone_t;

/**
 * @brief Zone of AT88SC1604
 * @note Refer to AT88SC1604 datasheet
 */
typedef enum {
    AT88SC1604_FZ = 0,      ///< �����̴�����, 2B
    AT88SC1604_IZ,          ///< �����̴�����, 8B
    AT88SC1604_SC,          ///< ��������, 2B
    AT88SC1604_SCAC,        ///< ��������������, 1B
    AT88SC1604_CPZ,         ///< ���뱣����, 8B
    AT88SC1604_SC1,         ///< Ӧ��1������, 2B
    AT88SC1604_S1AC,        ///< Ӧ��1��������������, 1B
    AT88SC1604_EZ1,         ///< Ӧ��1����������������, 2B
    AT88SC1604_E1AC,        ///< Ӧ��1����������������������, 1B
    AT88SC1604_AZ1,         ///< Ӧ��1��
    AT88SC1604_SC2,         ///< Ӧ��2������, 2B
    AT88SC1604_EZ2,         ///< Ӧ��2����������������, 2B
    AT88SC1604_E2AC,        ///< Ӧ��2����������������������, 1B
    AT88SC1604_AZ2,         ///< Ӧ��2��
    AT88SC1604_SC3,         ///< Ӧ��3������, 2B
    AT88SC1604_EZ3,         ///< Ӧ��3����������������, 2B
    AT88SC1604_E3AC,        ///< Ӧ��3����������������������, 1B
    AT88SC1604_AZ3,         ///< Ӧ��3��
    AT88SC1604_SC4,         ///< Ӧ��4������, 2B
    AT88SC1604_EZ4,         ///< Ӧ��4����������������, 2B
    AT88SC1604_E4AC,        ///< Ӧ��4����������������������, 1B
    AT88SC1604_AZ4,         ///< Ӧ����4
    AT88SC1604_MTZ,         ///< ������
} at88sc1604_zone_t;

/**
 * @brief Security level of AT88SC101, AT88SC102, AT88SC1604
 */
typedef enum {
    SEC_LEVEL_1 = 0,
    SEC_LEVEL_2,
} sec_level_t;

#define SLE4428_ATR_LEN     4 ///< 
#define SLE4428_SM_LEN      3 ///< 
#define SLE4428_EC_LEN      1 ///< 
#define SLE4428_INIT_EC     8 ///< 
#define SLE4428_EC_MASK     0xFF ///< 
#define SLE4428_EC_REC      0xFF ///< 
#define SLE4428_SC_LEN      2 ///< 
#define SLE4428_MM_LEN      1021 ///< EC, PSC1 and PSC2 at 0x03FD~03FF, so not 1024 here


#define SLE4442_ATR_LEN     4 ///< 
#define SLE4442_SM_LEN      4 ///< 
#define SLE4442_EC_LEN      1 ///< 
#define SLE4442_INIT_EC     3 ///< 
#define SLE4442_EC_MASK     0x07 ///< 
#define SLE4442_EC_REC      0xFF ///< 
#define SLE4442_SC_LEN      3 ///< 
#define SLE4442_MM_LEN      256 ///< 
#define SLE4442_PM_LEN      4 ///< 

#define AT88_ATR_LEN        4 ///< 
#define AT88_PWD_LEN        3 ///< 
#define AT88_PAC_LEN        1 ///< 
#define AT88SC1608_CZ_SIZE  128 ///< 
#define AT88SC1608_UZ_SIZE  256 ///< 
#define AT88SC153_CUZ_SIZE  64 ///< 



/**
 * @brief Bitmask of operation with or without protect bit 
 * @warning When read SLE4428 with protect bit, length should be MEMIC_BUF_SIZE/2 maximum.
 */
typedef enum {
    SLE4428_FLAG_WITHOUT_PB = (1<<0), ///< operation without protect bit 
    SLE4428_FLAG_WITH_PB = (1<<1), ///< operation with protect bit 
} sle4428_flag_t;


/**
 * @brief Zone of SLE4442
 *
 * Main Memory: 32 bytes Protectable Data Memory(0-31, 32 Bytes), 224 bytes Unprotected Data Memory (32-255, 224Bytes)
 * 
 * Protection Memory: (0-31 bit, totally 4 Bytes)
 *
 * Security Memory: Error counter(EC, 1 Byte), Protect security code(PSC, 3Bytes)
 *     EC: Only the least 3 bits use for counter, most 5 bits is always 0.
 *     PSC: Generally, PSC is FFFFFF default.
 * 
 */
typedef enum {
    SLE4442_MM = 0, ///< Main Memory
    SLE4442_PM,     ///< Protection Memory
    SLE4442_SM,     ///< Security Memory
} sle4442_zone_t;

/**
 * @brief Zone of AT88SC153. Not support yet.
 *
 */
typedef enum {
    AT88SC153UZONE0 = 0, ///< 
    AT88SC153UZONE1,     ///< 
    AT88SC153UZONE2,     ///< 
    AT88SC153CZONE,      ///< 
    AT88SC153AZONE,      ///< AAC
    AT88SC153FZONE,      ///< Fuse
} at88sc153_zone_t;

/**
 * @brief Zone of AT88SC608
 *
 */
typedef enum {
    AT88SC1608UZONE0 = 0, ///< 
    AT88SC1608UZONE1,     ///< 
    AT88SC1608UZONE2,     ///< 
    AT88SC1608UZONE3,     ///< 
    AT88SC1608UZONE4,     ///< 
    AT88SC1608UZONE5,     ///< 
    AT88SC1608UZONE6,     ///< 
    AT88SC1608UZONE7,     ///< 
    AT88SC1608CZONE,      ///< 
    AT88SC1608AZONE,      ///< AAC
    AT88SC1608FZONE,      ///< Fuse
} at88sc1608_zone_t;

/**
 * @brief Password for read or write
 *
 */
typedef enum {
    TYPE_WRITE = 0, ///< Password for write
    TYPE_READ,      ///< Password for read
} pwd_rw_t;

/**
 * @brief Three part authenticate step. Not support yet.
 *
 */
typedef enum {
    AUTH_STEP_INITIALIZE = 0, ///< 
    AUTH_STEP_VERIFY,         ///< 
} auth_step_t;


/**
 * @brief Memory card type
 *
 */
typedef enum {
    MEMIC_TYPE_UNKNOW = 0, ///< 
    MEMIC_TYPE_AT88SC101,  ///< 
    MEMIC_TYPE_AT88SC102,  ///< 
    MEMIC_TYPE_AT88SC1604, ///< 
    MEMIC_TYPE_AT88SC153,  ///< 
    MEMIC_TYPE_AT88SC1608, ///< 
    MEMIC_TYPE_SLE4428,    ///< 
    MEMIC_TYPE_SLE4442,    ///< 

    MEMIC_TYPE_AT24C01 = 0x10, ///< 
    MEMIC_TYPE_AT24C02,        ///< 
    MEMIC_TYPE_AT24C04,        ///< 
    MEMIC_TYPE_AT24C08,        ///< 
    MEMIC_TYPE_AT24C16,        ///< 
    MEMIC_TYPE_AT24C32,        ///< 
    MEMIC_TYPE_AT24C64,        ///< 
    MEMIC_TYPE_AT24C128,       ///< 
    MEMIC_TYPE_AT24C256,       ///< 
    MEMIC_TYPE_AT24C512,       ///< 
} memic_type_t;


/**
 * @brief Memory card command
 *
 */
typedef enum {
    MEMIC_CMD_CLOSE = 0, ///< Close/Poweroff
    MEMIC_CMD_OPEN,      ///< Open/Poweron
    MEMIC_CMD_READ,      ///< Read
    MEMIC_CMD_WRITE,     ///< Write
    MEMIC_CMD_VERIFY,    ///< PWD/SC/PSC Verify
    MEMIC_CMD_UPDATE,    ///< PWD/SC/PSC Update
    MEMIC_CMD_PAC,       ///< Get password attempts counter
    MEMIC_CMD_AUTH,      ///< Authenticate
    MEMIC_CMD_CONFIG,    ///< Config
    MEMIC_CMD_STA,       ///< State. For checking card exist or not.
} memic_cmd_t;

#define AT88SC102_FZ_DEF    "\x0F\x0F"          ///<(MSB: 0F0F; LSB: F0F0)
#define AT88SC1604_FZ_DEF   "\x31\x3A"          ///<(MSB: 313A; LSB: 8C5C)
#define SLE4428_ATR_DEF     "\x92\x23\x10\x91"  ///<
#define SLE4442_ATR_DEF     "\xA2\x13\x10\x91"  ///<
#define AT88SC1608_ATR_DEF  "\x2C\xAA\x55\xA0"  ///<

#define	MEMIC_BUF_SIZE      256 ///< Memory card operation buffer size
/**
 * @brief structure for memory card operation
 * @note 
 * DETSTA
 * PWRON     CTYPE   RFU
 * PWROFF    CTYPE   RFU
 * RESET     CTYPE   RFU     FLAG
 * READ      CTYPE   RFU     FLAG    ZONE    ADDR    LEN
 * WRITE     CTYPE   RFU     FLAG    ZONE    ADDR    LEN     DATA
 * PAC       CTYPE   RFU     FLAG    ZONE    ADDR    LEN
 * CHECK     CTYPE   RFU     FLAG    ZONE    ADDR    LEN     DATA
 * VERIFY    CTYPE   RFU     FLAG    ZONE    ADDR    LEN     DATA
 * AUTHEN    CTYPE   RFU     FLAG    ZONE    ADDR    LEN     DATA
 * CONFIG    CTYPE   RFU     FLAG    ZONE    ADDR    LEN     DATA
 *
 * @warning All RFU shold be 00
 */
typedef struct MEMIC_OPT_ST {
    unsigned char ucType;                   ///< Card type
    unsigned char ucCmd;                    ///< Card command
    unsigned char ucZone;                   ///< Operation zone
    unsigned char ucFlag;                   ///< Operation flag
    unsigned char ucSpec;                   ///< Operation spec
    unsigned short usAddr;                  ///< Operation address
    unsigned short usLength;                ///< Operation or response data length
    unsigned char aucBuf[MEMIC_BUF_SIZE];   ///< Operation or response data buffer
} MemicOptType;


/**
 * @brief Memory card operate interface
 * @param [inout] pstMemicOpt:
 * -#                       [in]  Command for card operation
 * -#                       [out] Response data of card operation
 * @retval  0: Success
 * @retval  <0: Fail
 */
int MemoryCardOperate(MemicOptType *pstMemicOpt);

/** @} MemoryCard */


/**
 * @defgroup Magcard Magcard
 * @brief Magcard Module APIs
 * @{
 */
//=============================================================
//#include "bw_magcard.h"
//=============================================================

/**
 * @brief  Track TAG of magcard
 */
typedef enum {
    TAG_MAGCARD_TRKVIEW = 0x00,
    TAG_MAGCARD_TRKERR,
    TAG_MAGCARD_TRACK1,
    TAG_MAGCARD_TRACK2,
    TAG_MAGCARD_TRACK3,
} TagTrack_t;

///< The maximum allowed is: track1 = 79; track2 = 40; track3 = 107.
#define MAG_TRACK1_SIZE     80
#define MAG_TRACK2_SIZE     48
#define MAG_TRACK3_SIZE     112


#define MAG_TRACK1_MASK     (1<<0) ///< bitmask of TRACK1
#define MAG_TRACK2_MASK     (1<<1) ///< bitmask of TRACK2
#define MAG_TRACK3_MASK     (1<<2) ///< bitmask of TRACK3
#define MAG_TRACKV_MASK     (1<<3) ///< bitmask of TRACKView

/**
 * @brief  Track infomation of magcard
 */
typedef struct {
    unsigned char ucNr; ///< count of tracks with data
    unsigned char ucTrackMask; ///< bismasks of tracks with data. Refer to MAG_TRACKx_MASK
    unsigned char aucTrack1[MAG_TRACK1_SIZE];  ///< Track 1 string
    unsigned char aucTrack2[MAG_TRACK2_SIZE];  ///< Track 2 string
    unsigned char aucTrack3[MAG_TRACK3_SIZE];  ///< Track 3 string
    unsigned char aucTrkView[MAG_TRACK2_SIZE]; ///< Track view string
} MagTrack_T;

/**
 * @brief  Encrypted track infomation of magcard
 */
typedef struct {
    unsigned char ucNr; ///< count of tracks with data
    unsigned char ucTrackMask; ///< bismasks of tracks with data. Refer to MAG_TRACKx_MASK
    unsigned char ucTrk1Len;   ///< Length of track 1 data
    unsigned char ucTrk2Len;   ///< Length of track 1 data
    unsigned char ucTrk3Len;   ///< Length of track 1 data
    unsigned char ucTrkVLen;   ///< Length of track view
    unsigned char aucTrack1[MAG_TRACK1_SIZE];    ///< track 1 data
    unsigned char aucTrack2[MAG_TRACK2_SIZE];    ///< track 1 data
    unsigned char aucTrack3[MAG_TRACK3_SIZE];    ///< track 1 data
    unsigned char aucTrackView[MAG_TRACK2_SIZE]; ///< track 2 string
} MagEncryptTrack_T;


/**
 * @brief Open magcard module
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int MagCardOpenRev(void);

/**
 * @brief Close magcard module
 * @retval  0: SUCCESS, <0: FAIL
 * @pre None
 */
int MagCardCloseRev(void);

/**
 * @brief Read magcard data
 * @param [out] pstTracks: Magcard tracks information
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int MagCardReadRev(MagTrack_T *pstTracks);

/**
 * @brief Read encrypted magcard data
 * @param [in] iTtkIdx:   TTK index
 * @param [in] iMode:     Mode of encrypt
 *                            0x00:  ECB mode, padding by 0x00
 *                            0x01:  CBC mode, padding by 0x00
 *                            0x02:  CNCUP mode
 * @param [out] pstTracks: Encrypted magcard tracks information
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedMagCardEncryptReadRev(int iTtkIdx, int iMode, MagEncryptTrack_T *pstTracks);

/** @} Magcard */


/**
 * @defgroup Picc Picc
 * @brief Picc module APIs
 * @{
 */
//=============================================================
//#include "bw_picc.h"
//=============================================================


#define PICC_APDU_LEN_MIN   4   ///< Minimum bytes of C-APDU
#define PICC_APDU_LEN_MAX   260 ///< Maximum bytes of C-APDU
#define PICC_SW_SIZE        2   ///< Bytes of Status-Word

/**
 * @brief TAG enum for PICC transparent transfer command.
 */
typedef enum {
    PICC_TAG_BDR_PCD = 0x61, ///< 0x61, Baudrate of PCD->PICC, n*106000
    PICC_TAG_BDR_PICC,       ///< 0x62, Baudrate of PICC->PCD, n*106000
    PICC_TAG_TYPE,           ///< 0x63, Type of PICC
    PICC_TAG_DATA_SND,       ///< 0x64, Data to send
    PICC_TAG_DATA_RCV,       ///< 0x65, Data of receive
    PICC_TAG_FRAME,          ///< 0x66, Frame type
    PICC_TAG_FWT,            ///< 0x67, Frame wait time
    PICC_TAG_FSGT,           ///< 0x68, Frame guard time
    PICC_TAG_FSC,            ///< 0x69, Frame size
    PICC_TAG_CRC_EN,         ///< 0x6A, CRC by RF-chip
} TagPicc_t;

/*******************TAG ���� �� ��ض���*********************/

#define TAG_CMD_AUTH        'A' ///< Authenticate
#define TAG_CMD_RAED        'R' ///< Read block
#define TAG_CMD_WRITE       'W' ///< Write block
#define TAG_CMD_PAGE        'P' ///< Write page
#define TAG_CMD_INC         '+' ///< Value increment
#define TAG_CMD_DEC         '-' ///< Value decrement
#define TAG_CMD_RESTORE     '>' ///< Value restore

#define TAG_IDX_AUTH_KEYA           'A'     ///< M1 KeyA
#define TAG_IDX_AUTH_KEYB           'B'     ///< M1 KeyB
#define TAG_IDX_TRANSPARENT_MODE    0x90    ///< For define transparent mode
#define TAG_PSEUDO_APDU_CLS         TAG_IDX_TRANSPARENT_MODE    ///< 


#define TAG_M1_KEY_LEN      6    ///< Key length of M1
#define TAG_M1_BLOCK_LEN    0x10 ///< Block length of M1
#define TAG_M1_VALUE_LEN    4    ///< Value length of M1


#define MIFARE_OPT_BUF_LEN      128 ///< PICC TAG card buffer size
/**
 * @brief PICC TAG card command and response structure
 */
typedef struct ST_TAG_OPT {
    unsigned char ucOptCmd;    ///< Operation command: 'R', 'W', 'P', 'A', '+', '-', '>', ...
    unsigned char ucOptIdx;    ///< Operation index: 'A', 'B' for M1 authenticate, 0x90 for transparent APDU mode.
    unsigned char ucOptSrc;    ///< Operation block source: For Authen, read, write, write page, '+', '-', '>'.
    unsigned char ucOptDest;   ///< Operation block destination: For '+', '-', '>'.
    unsigned char ucOptValLen; ///< Operation Length: Bytes to read or in optVal.
    unsigned char aucOptVal[MIFARE_OPT_BUF_LEN]; ///< Operation data.
} TagOptType;

/**
 * @brief PICC card information
 */
typedef struct PICC_INFO_ST {
    unsigned char ucPiccCardType;   ///< Type of PICC
    unsigned char ucPiccSlot;       ///< PICC logical channel number
    unsigned char ucPiccSnLen;      ///< Length of PICC serial number
    unsigned char ucPiccInfoLen;    ///< Length of PICC information
    unsigned char aucPiccSN[12];    ///< PICC serial number
    unsigned char aucPiccInfo[128]; ///< PICC information
} PiccInfo_T;

/**
 * @brief Open PICC module
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PiccOpen(void);

/**
 * @brief Detect PICC
 * @param [in]  ucMode:
 * -#               0x01: EMV mode
 * -#               'A': TypeA CPU mode
 * -#               'B': TypeB CPU mode
 * -#               'M': Mifare mode
 * @param [out] pstPiccInfo: PICC card information
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PiccDetect(unsigned char ucMode, PiccInfo_T *pstPiccInfo);

/**
 * @brief PICC APDU exchange
 * @param [in] pucCmd:   C-APDU
 * @param [in] uiCmdLen: Length of C-APDU
 * @param [in] pucRsp:   R-APDU
 * @param [in] pucSW:    Status-Word (2 bytes)
 * @retval  >=0: Success, Length of R-APDU
 * @retval  <0: Fail
 * @pre None
 */
int PiccApduExchange(unsigned char *pucCmd, unsigned int uiCmdLen, unsigned char *pucRsp, unsigned char *pucSW);

/**
 * @brief Remove PICC
 * @param [in] ucMode:
 * -#               'E': EMV mode
 * -#               'S': Stop mode
 * -#               'H': Halt mode
 * @param [in] ucSlot: card slot number. @see:: PiccInfo_T
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PiccRemove(unsigned char ucMode, unsigned char ucSlot);

/**
 * @brief Close PICC module
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PiccClose(void);


/**
 * @brief PICC transparent transfer interface
 * @param [in]  pucCmd:    Data to send
 * @param [in]  uiCmdLen:  Length of Data to send
 * @param [out] pucRsp:    Data received
 * @param [out] puiRspLen: Length of Data received
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PiccSidTransceiveRev(unsigned char* pucCmd, unsigned int uiCmdLen, unsigned char *pucRsp, unsigned int *puiRspLen);


/**
 * @brief M1 Authication with SN checked
 * @param [in] keyType:   One of TAG_IDX_AUTH_KEYA and TAG_IDX_AUTH_KEYB
 * @param [in] blockNo:   Block number to authenticate
 * @param [in] keyLen:    Length of KEY
 * @param [in] pKey:      KEY for authenticate
 * @param [in] seriNoLen: Length of SN
 * @param [in] pSeriNo:   SN of M1
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_KeyAuth_With_SN_Rev(unsigned int keyType, unsigned int blockNo, unsigned int keyLen,
                    unsigned char *pKey, int seriNoLen, unsigned char *pSeriNo);

/**
 * @brief M1 Authication
 * @param [in] keyType: One of TAG_IDX_AUTH_KEYA and TAG_IDX_AUTH_KEYB
 * @param [in] blockNo: Block number to authenticate
 * @param [in] keyLen:  Length of KEY
 * @param [in] pKey:    KEY for authenticate
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_KeyAuthRev(unsigned int keyType, unsigned int blockNo, unsigned int keyLen, unsigned char *pKey);

/**
 * @brief Read a block data from M1
 * @param [in]  blockNo:   Block to read
 * @param [out] pDataRead: Block data
 * @retval  >=0: Success, Length of Data(will be TAG_M1_BLOCK_LEN)
 * @retval  <0: Fail
 * @pre None
 */
int Picc_M1_ReadBlockRev(unsigned int blockNo, unsigned char *pDataRead);

/**
 * @brief Read valud of M1 block
 * @param [in]  blkNo:   Value block
 * @param [out] piCents: Value(unit: cent)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_ReadValueRev(unsigned int blkNo, int *piCents);

/**
 * @brief Write a block data to M1 
 * @param [in] blkNo:         Block to write
 * @param [in] iDataWriteLen: Length of data to write(Should be TAG_M1_BLOCK_LEN)
 * @param [in] pDataWrite:    Data to write
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_WriteBlockRev(unsigned int blkNo, unsigned int iDataWriteLen, unsigned char *pDataWrite);

/**
 * @brief Initial a value to block
 * @param [in] blkNo:  Block to initial a value
 * @param [in] iCents: Value(unit: cent)
 * @param [in] ucAdr:  A check byte of value block(Generally, it's the block number the value in)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_InitValueRev(unsigned int blkNo, int iCents, unsigned char ucAdr);

/**
 * @brief Increase value to M1
 * @param [in] blkNoSrc:   The source value block
 * @param [in] blkNoDst:   The destination value block
 * @param [in] uiCentsInc: Cents to increase
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_IncrementRev(unsigned int blkNoSrc, unsigned int blkNoDst, unsigned int uiCentsInc);

/**
 * @brief Decrease value to M1
 * @param [in] blkNoSrc:   The source value block
 * @param [in] blkNoDst:   The destination value block
 * @param [in] uiCentsDec: Cents to decrease
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_DecrementRev(unsigned int blkNoSrc, unsigned int blkNoDst, unsigned int uiCentsDec);

/**
 * @brief Restore a value block
 * @param [in] blkNoSrc: The source value block
 * @param [in] blkNoDst: The destination value block
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_M1_RestoreRev(unsigned int blkNoSrc, unsigned int blkNoDst);


/**
 * @brief RF TAG card transparent transfer interface
 * @param [in] pucCmd:   TAG command
 * @param [in] uiCmdLen: Length of TAG command
 * @param [in] pucResp:  TAG response
 * @retval  >=0: Success, Length of response
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_Tag_Iso14443_TransparentMode(unsigned char *pucCmd, unsigned int uiCmdLen, unsigned char *pucResp);

/**
 * @brief RF TAG card transparent transfer interface in APDU format
 * @param [in] pucCapdu:   C-APDU: CLA: 0x90, INS: TagCmd, P1: Ignored, P2: Ignored, P3: Lc
 * @param [in] uiCapduLen: Length of C-APDU
 * @param [in] pucRapdu:   R-APDU
 * @param [in] pucSW:      Status-Word(2 bytes)
 * @retval  >=0: Success, Length of response
 * @retval  <0: FAIL
 * @pre None
 */
int Picc_Tag_Iso14443_PseudoAPDU(unsigned char *pucCapdu, unsigned int uiCapduLen,
                unsigned char *pucRapdu, unsigned char *pucSW);


/** @} Picc */


/**
 * @defgroup GuoMi GouMi
 * @brief GuoMi module APIs
 * @{
 */
//=============================================================
//#include "bw_sm.h"
//=============================================================

#define SM4_ECB     0x01    ///< ECB mode of SM4
#define SM4_CBC     0x02    ///< CBC mode of SM4

/**
 * @brief Generate SM2 key pair
 * @param [out] outdata: SM2 key pair[pub(64 bytes) + pri(32 bytes)]
 * @retval >=0: Success, Length of SM2 key pair, <0: Fail
 * @pre None
 */
int SM2_KeyGenRev(unsigned char *outdata);


/**
 * @brief SM2 encrypt
 * @param [in]  ecpoint_PBx: X string of public key
 * @param [in]  ecpoint_PBy: Y string of public key
 * @param [in]  M:           Message
 * @param [in]  mLen:        Length of Message
 * @param [out] encdata:     Result of enctyption
 * @retval  >=0: Success, Length of Result
 * @retval  <0: Fail
 * @pre None
 */
int SM2_EncryptRev(char *ecpoint_PBx, char *ecpoint_PBy, const char *M, int mLen, unsigned char *encdata);

/**
 * @brief SM2 Decrypt
 * @param [in]  decdata:    Ciphertext
 * @param [in]  decdataLen: Length of ciphertext
 * @param [in]  dB:         Private key string
 * @param [out] M:          Plaintext of message
 * @retval  >=0: Success, Length of message
 * @retval  <0: Fail
 * @pre None
 */
int SM2_DecryptRev(const char *decdata, int decdataLen, const char *dB, unsigned char *M);

/**
 * @brief SM2 signature
 * @param [in]  dA:        Private key string
 * @param [in]  dgst:      Data to sign
 * @param [in]  dlen:      Length of data to sign
 * @param [out] signature: Signature
 * @param [out] sig_len:   Length of signature
 * @retval  >=0: Success, Length of signature
 * @retval  <0: Fail
 * @pre None
 */
int SM2_SignRev(char *dA, unsigned char *dgst, int dlen, unsigned char *signature, unsigned int *sig_len);

/**
 * @brief SM2 signature verify
 * @param [in] dgst:     Pretreatment result by public key
 * @param [in] dgst_len: Length of pretreatment result(should be 32)
 * @param [in] sigbuf:   Signature
 * @param [in] sig_len:  Length of signature(should be 64)
 * @param [in] PAx:      X string of public key
 * @param [in] PAy:      Y string of public key
 * @retval  0: Success
 * @retval  <0: Fail
 * @pre None
 */
int SM2_VerifyRev(unsigned char *dgst, int dgst_len, unsigned char *sigbuf, int sig_len, char *PAx, char *PAy);

/**
 * @brief Pretreatment of signaure verify
 * @param [in]  PAx:      X string of public key
 * @param [in]  PAy:      Y string of public key
 * @param [in]  Id:       Signature id(Default: "1234567812345678")
 * @param [in]  id_len:   Length of signature id
 * @param [in]  signdata: Signature(data to pretreatment)
 * @param [in]  sign_len: Length of signature(length of data to pretreatment)
 * @param [out] dgst:     Pretreatment result
 * @retval  >=0: Success, Length of pretreatment result
 * @retval  <0: Fail
 * @pre None
 */
int SM2_DigestRev(char *PAx, char *PAy, char *Id, int id_len, unsigned char *signdata, int sign_len, unsigned char *dgst);

/**
 * @brief SM3
 * @param [in]  indata:     Message
 * @param [in]  indata_len: Length of Message
 * @param [out] outdata:    SM3 result
 * @retval  >=0: Success, Lendgth of SM3(should be 32)
 * @retval  <0: Fail
 * @pre None
 */
int SM3Rev(unsigned char *indata, int indata_len, unsigned char *outdata);

/**
 * @brief SM4 enctypt
 * @param [in]  sm4_key:   SM4 key
 * @param [in]  mode:      ECB/CBC (Refer to SM4_ECB/SM4_CBC)
 * @param [in]  indata:    Plaintext
 * @param [in]  indatalen: Length of Plaintext
 * @param [in]  iv:        IV of cbc mode
 * @param [in]  ivlen:     IV length of cbc mode
 * @param [out] outdata:   Ciphertext
 * @retval  >=0: Success, Length of ciphertext
 * @retval  <0: Fail
 * @pre None
 */
int SM4_EncryptRev(char *sm4_key, char mode, const char *indata, int indatalen, unsigned char *iv, int ivlen, unsigned char *outdata);

/**
 * @brief SM4 decrypt
 * @param [in]  sm4_key:   SM4 key
 * @param [in]  mode:      ECB/CBC (Refer to SM4_ECB/SM4_CBC)
 * @param [in]  indata:    Cihpertext
 * @param [in]  indatalen: Length of Ciphertext
 * @param [in]  iv:        IV of cbc mode
 * @param [in]  ivlen:     IV length of cbc mode
 * @param [out] outdata:   Plaintext
 * @retval  >=0: Success, Length of plaintext
 * @retval  <0: Fail
 * @pre None
 */
int SM4_DecryptRev(char *sm4_key, char mode, const char *indata, int indatalen, unsigned char *iv, int ivlen, unsigned char *outdata);

/** @} GouMi */


/**
 * @defgroup SpSys SpSys
 * @brief SP system APIs
 * @{
 */
//=============================================================
//#include "bw_spsys.h"
//=============================================================


#define RF_LED_RED          0x80 ///< control bitmask of RF RED LED
#define RF_LED_YELLOW       0x40 ///< control bitmask of RF YELLOW LED
#define RF_LED_GREEN        0x20 ///< control bitmask of RF GREEN LED
#define RF_LED_BLUE         0x10 ///< control bitmask of RF BLUE LED

#define SP_HW_ALLCHECK      (1 << 0) ///< SP HW check bitmask of all
#define SP_HW_MAGCHECK      (1 << 0) ///< SP HW check bitmask of MAG
#define SP_HW_ICCCHECK      (1 << 1) ///< SP HW check bitmask of ICC
#define SP_HW_PICCCHECK     (1 << 2) ///< SP HW check bitmask of PICC
#define SP_HW_FLASHCHECK    (1 << 3) ///< SP HW check bitmask of FLASH
#define SP_HW_KEYPADCHECK   (1 << 4) ///< SP HW check bitmask of KEYPAD

#define ATTACK_LOG_LEN_MAX          0x200 ///< Max length of attack log

#define TAG_SP_SYSINFO_BATTVOLT     0xA1 ///< TAG of SP backup battery voltage

/**
 * @brief SP Hardward self check
 * @param [in] ucModuleMsk: bitmasks of SP modules, Refer to  SP HW check bitmask
 * @see:: SP_HW_ALLCHECK
 * @see:: SP_HW_MAGCHECK
 * @see:: SP_HW_ICCCHECK
 * @see:: SP_HW_PICCCHECK
 * @see:: SP_HW_FLASHCHECK
 * @see:: SP_HW_KEYPADCHECK
 * @retval  >=0: Bitmasks of normal module
 * @retval  <0: Fail
 * @pre None
 */
int SpSysSelfCheck(unsigned char ucModuleMsk);


/**
 * @brief SP parameter set
 * @param [in] pucTlv:   parameter TLVs to set
 * @param [in] uiTlvLen: Length of parameter TLVs to set
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysParaSet(unsigned char *pucTlv, unsigned int uiTlvLen);

/**
 * @brief SP parameter set/get
 * @param [in]  pucTlvSet   parameter TLVs to set
 * @param [in]  uiTlvSetLen Length of parameter TLVs to set
 * @param [out] pucTlvGet   parameter TLVs got
 * @retval  >=0: Length of TLVs got
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysParaSetExt(unsigned char *pucTlvSet, unsigned int uiTlvSetLen, unsigned char *pucTlvGet);

/** 
 * @brief Sensor active
 * @param [out] pucSnsInfo: Sensor innormal information (Len + SnsInfo + TLVs)
 * @param [out] uiInfoLen:  Length of information 
 * @param [in]  uiSize:     Size of buffer(pucSnsInfo, 32 bytes is recommended)
 * @retval  0           : Success
 * @retval -1   (0xFFFF): Fail, Already active
 * @retval -2   (0xFFFE): Fail, Sensor open
 * @retval -4370(0xEEEE): Fail, Sensor triggered
 * @retval <0: Fail
 */
int SpSysSensorActive(unsigned char *pucSnsInfo, unsigned int *uiInfoLen, unsigned int uiSize);

/** 
 * @brief Sensor active
 * @param [in]  pucSnsDis  Bitmask of sensor not active, 4 bytes in Big-endian
 * @param [out] pucSnsInfo: Sensor innormal information (Len + SnsInfo + TLVs)
 * @param [out] uiInfoLen:  Length of information 
 * @param [in]  uiSize:     Size of buffer(pucSnsInfo, 32 bytes is recommended)
 * @retval  0           : Success
 * @retval -1   (0xFFFF): Fail, Already active
 * @retval -2   (0xFFFE): Fail, Sensor open
 * @retval -4370(0xEEEE): Fail, Sensor triggered
 * @retval <0: Fail
 */
int SpSysSensorActiveExt(unsigned char *pucSnsDis, unsigned char *pucSnsInfo, unsigned int *uiInfoLen, unsigned int uiSize);

/**
 * @brief Sensor check
 * @param [out] pucSnsInfo: Sensor innormal information (Len + SnsInfo + TLVs)
 * @param [out] uiInfoLen:  Length of information 
 * @param [in]  uiSize:     Size of buffer(pucSnsInfo, 32 bytes is recommended)
 * @retval  0           : Success
 * @retval -1   (0xFFFF): Fail, Already active
 * @retval -2   (0xFFFE): Fail, Sensor open
 * @retval -4370(0xEEEE): Fail, Sensor triggered
 * @retval <0: Fail
 */
int SpSysSensorCheck(unsigned char *pucSnsInfo, unsigned int *uiInfoLen, unsigned int uiSize);

/**
 * @brief Get attack log
 * @param [out] pucAttackLog: Attack log buffer. 512 bytes is recommended.
 * @param [out] puiLogLen: Length of attack log.
 * @retval 0: SUCCESS, <0: FAIL
 * @pre ��
 */
int SpSysGetAttackLog(unsigned char *pucAttackLog, unsigned int *puiLogLen);

/**
 * @brief Get sensor register information
 * @param [out] pcSenRegInfo: Sensor register information string
 * @param [in]  uiSize:       Size of buffer(pcSenRegInfo)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 */
int PedGetTamperRegisterInfoRev(char *pcSenRegInfo, unsigned int uiSize);

/**
 * @brief SP Simple unlock
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysUnLock(void);

/**
 * @brief Baudrate set
 * @param [in] uiBdr: Baudrate
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysSetBaudRate(unsigned int uiBdr);

/**
 * @brief Judge whether QPBOC L2 have been broken
 * @retval  0: No
 * @retval !0: Yes (have been broken)
 * @pre None
 */
int SysGetCurrentDev(void);


/**
 * @brief Get the external KeyPad version
 * @retval  !NULL: Success, Ext-KP Version
 * @retval  NULL: Fail
 */
char* GetExtKpdFwVersion(void);

/**
 * @brief Get SP version
 * @param [out] pcSpVer: SP version
 * @retval  >=0: Success, Length of version
 * @retval  <0: Fail
 * @pre None
 */
int SpSysGetSpVersion(char *pcSpVer);


/**
 * @brief SP transparent transfer interface
 * @param [in] ucCmd:     Command
 * @param [in] pucData:   Data of command
 * @param [in] uiDataLen: Length of data
 * @param [out] pucResp:  Response of command
 * @retval  >=0: Success, Length of response
 * @retval  <0: Fail
 * @pre None
 */
int SpSysExchangeCmd(unsigned char ucCmd, unsigned char *pucData, unsigned int uiDataLen, unsigned char *pucResp);


/**
 * @brief Get RTC from SP
 * @param [out] pucRtc: RTC, Format: Year+Month+Day+Hour+Minute+Second [+Week], 6Bytes [or 7Bytes]
 * @retval  >=0: Success, Length of RTC
 * @retval  <0: Fail
 * @pre None
 */
int SpSysGetRTC(unsigned char *pucRtc);



/**
 * @brief Set RTC to SP
 * @param [in] pucRtc: RTC, Format: Year+Month+Day+Hour+Minute+Second, 6Bytes (BCD, eg: 180201151232)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysSetRTC(unsigned char *pucRtc);

/**
 * @brief Led on
 * @param [in] ucLedOnMsk: bitmasks of LED on. Refer to RF_LED_xxx
 * @see:: RF_LED_RED
 * @see:: RF_LED_YELLOW
 * @see:: RF_LED_GREEN
 * @see:: RF_LED_BLUE
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysLedOn(unsigned char ucLedOnMsk);

/**
 * @brief Led off
 * @param [in] ucLedOffMsk: bitmasks of LED off. Refer to RF_LED_xxx
 * @see:: RF_LED_RED
 * @see:: RF_LED_YELLOW
 * @see:: RF_LED_GREEN
 * @see:: RF_LED_BLUE
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysLedOff(unsigned char ucLedOffMsk);

/**
 * @brief Led flash
 * @param [in] ucLedFlshMsk:  bitmasks of LED flash. Refer to RF_LED_xxx
 * @see:: RF_LED_RED
 * @see:: RF_LED_YELLOW
 * @see:: RF_LED_GREEN
 * @see:: RF_LED_BLUE
 * @param [in] uiOnMs: Led time(MS) on
 * @param [in] uiOffMs: Led time(MS) off
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysLedFlash(unsigned char ucLedFlshMsk, unsigned int uiOnMs, unsigned int uiOffMs);

/**
 * @brief Beep off
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysBeepOff(void);

/**
 * @brief Beep on
 * @param [in] uiFreq: Frequency of beep pwm
 * @param [in] uiOnMs: Beep time(MS)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysBeepOn(unsigned int uiFreq, unsigned int uiOnMs);

/**
 * @brief ���ذ���������
 * @param [in] on   ���� 0: ��, 1: ��
 * @param [in] uiFreq ������Ƶ�� (0 ��ʾ��������Ƶ��)
 * @param [in] uiOnMs ����ʱ��( <= 150, 0 ��ʾ��������ʱ��ֵ)
 * @retval 0: SUCCESS, <0: FAIL
 * @pre ��
 */
int SpSysKbBeepSetting(int on, unsigned int uiFreq, unsigned int uiOnMs);

/**
 * @brief Get information of SP
 * @param [in]  ucInfoTag:  Information TAG. Refer to TAG_SP_SYSINFO_xxx
 * @see:: TAG_SP_SYSINFO_BATTVOLT
 * @param [out] pacSysInfo: Information string
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysGetInformation(unsigned char ucInfoTag, unsigned char *pacSysInfo);

/**
 * @brief Echo
 * @param [in]  pucSnd: Echo out
 * @param [in]  uiLen:  Length of echo out
 * @param [out] pucRcv: Echo in
 * @retval  >=0: Success, Length of echo in
 * @retval  <0: Fail
 * @pre None
 */
int SpSysEcho(unsigned char *pucSnd, unsigned int uiLen, unsigned char *pucRcv);

/**
 * @brief Sleep
 * @param [in]  uiWaitMs: Waitting time(MS) before enter sleep. 
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int SpSysSleep(unsigned int uiWaitMs);

/** @} SpSys */


/**
 * @defgroup Ped Ped
 * @brief Ped APIs
 * @{
 */
//=============================================================
//#include "bw_ped.h"
//=============================================================

/************* Key usage ****************/
#define PED_TLK     0x01 ///< TLK (Loading Key)
#define PED_TMK     0x02 ///< TMK (master key)
#define PED_TPK     0x03 ///< TPK PIN Key
#define PED_TAK     0x04 ///< TAk MAC Key
#define PED_TDK     0x05 ///< TDK DES Key (Decrypt key)
#define PED_TEK     0x06 ///< TEK DES Key (Encrypt key)
#define PED_TTK     0x09 ///< TTK Dukpt Key

/************* encrypt algorithm of key writting ****************/
#define PED_TDES    0x00  ///< TDES
#define PED_AES     0x10  ///< AES
#define PED_SM4     0x20  ///< SM4


#define PED_ECB_DEC 0x00 ///< ecb decrypt
#define PED_ECB_ENC 0x01 ///< ecb encrypt
#define PED_CBC_DEC 0x02 ///< cbc decrypt
#define PED_CBC_ENC 0x03 ///< cbc encrypt

#define PED_ECB_SINGLE_DEC 0x10 ///< ecb decrypt(single DES)
#define PED_ECB_SINGLE_ENC 0x11 ///< ecb encrypt(single DES)
#define PED_CBC_SINGLE_DEC 0x12 ///< cbc decrypt(single DES)
#define PED_CBC_SINGLE_ENC 0x13 ///< cbc encrypt(single DES)


/**
 * @brief Symmetric encrypt/decrypt mode
 */
typedef enum {
    PED_SYMM_MODE_ECB = 0,  ///< ECB mode
    PED_SYMM_MODE_CBC = 1,  ///< CBC mode
} ped_symm_mode_t;

/**
 * @brief function of algorithm
 */
typedef enum {
    PED_FUNC_DECRYPT = 0,   ///< Decrypt
    PED_FUNC_ENCRYPT = 1,   ///< Encrypt
} ped_func_t;

/**
 * @brief Architecture of KEY
 */
typedef enum {
    KEY_ARCH_MKSK  = 0x01,  ///< MKSK
    KEY_ARCH_DUKPT = 0x02,  ///< DUKPT
} Key_Arch_Type;

/**
 * @brief Function of administator
 */
typedef enum {
    ADMIN_MODE_UNLOCK = 0x80,   ///< Unlock PWD
    ADMIN_MODE_VERIDY_PARTA,    ///< Admin PWD-A
    ADMIN_MODE_VERIDY_PARTB,    ///< Admin PWD-B
    ADMIN_MODE_ACTIVE,          ///< 
    ADMIN_MODE_NEW_UNLOCK,      ///< New unlock PWD
    ADMIN_MODE_NEW_PARTA,       ///< New admin PWD-A
    ADMIN_MODE_NEW_PARTB,       ///< New admin PWD-B
} ADMIN_MODE_TYPE;


#define PINBLOCK_MODE_16B_MASK          0x10 ///< Bitmask of 16 Bytes key PINBLOCK mode
#define PINBLOCK_MODE_KSNINC_MASK       0x20 ///< Bitmask of KSN increase PINBLOCK mode
#define PINBLOCK_MODE_DERIVE_MASK       0x40 ///< Bitmask of derive key PINBLOCK mode

/**
 * @brief Mode of PINBLOCK
 * @brief may be used with PINBLOCK_MODE_XXX_MASK if need
 */
typedef enum {
    PINBLOCK_MODE_ISO9564_FMT0 = 0x00, ///< ISO9564 Format 0
    PINBLOCK_MODE_ISO9564_FMT1 = 0x01, ///< ISO9564 Format 1
    PINBLOCK_MODE_ISO9564_FMT3 = 0x02, ///< ISO9564 Format 2
    PINBLOCK_MODE_HK_EPS       = 0x03, ///< HK EPS format
    PINBLOCK_MODE_ISO9564_FMT4 = 0x04, ///< ISO9564 Format 4
} Pin_Block_Mode_Type;

/**
 * @brief Mode of offline PIN
 */
typedef enum {
    OFFLINE_MODE_DEF = 0x0, ///< Offline PIN mode.
} Offline_Mode_Type;

/**
 * @brief Event of PINBLOCK
 * @see:: Pin_Block_Data
 * @see:: Pin_Block_Data_Ext
 * @see:: Offline_Pin_Data
 */
typedef enum {
    PIN_EVENT_NONE = 0x0,   ///< None PIN event
    PIN_EVENT_LEN,          ///< A valid PIN inputted event.                 Refer to event data: ucPinLen
    PIN_EVENT_PINBLOCK,     ///< PIN complete event.                         Refer to event data: ucPinBlkLen, ucKsnLen, aucPinBlock, aucKsn
    PIN_EVENT_COMPLETE = PIN_EVENT_PINBLOCK, ///< Offline PIN complete event, same as PIN_EVENT_PINBLOCK.
    PIN_EVENT_PINFREE,      ///< Directly 'ENTER' without any PIN inputted.  Refer to event data: ucPinBlkLen, ucKsnLen, aucPinBlock, aucKsn
    PIN_EVENT_INVALID,      ///< An invalid PIN inputted event.              Refer to event data: none
    PIN_EVENT_EXIT,         ///< 'CANCEL' inputted event.                    Refer to event data: none
    PIN_EVENT_ERR,          ///< Other error event.                          Refer to event data: iErrCode
} Pin_Block_Event;

/**
 * @brief Event of PWD
 * @see:: Pwd_Event_Data
 */
typedef enum {
    PWD_EVENT_NONE = 0x0,   ///< None PWD event.
    PWD_EVENT_LEN,          ///< A valid PWD inputted event.    Refer to event data: ucPwdLen
    PWD_EVENT_OVER,         ///< PWD complete event.            Refer to event data: iErrCode
    PWD_EVENT_INVALID,      ///< An invalid PWD inputted event. Refer to event data: none
    PWD_EVENT_EXIT,         ///< 'CANCEL' inputted event.       Refer to event data: none
    PWD_EVENT_ERR,          ///< Other error event.             Refer to event data: aucEvtResp, iErrCode
} Pwd_Event;

/**
 * @brief Event data of PINBLOCK
 * @see:: Pin_Block_Event
 */
typedef struct {
    unsigned char ucPinLen;         ///< when event is PIN_EVENT_LEN, indicate the PIN length inputted
    unsigned char ucPinBlkLen;      ///< when event is PIN_EVENT_PINBLOCK or PIN_EVENT_PINFREE, indicate the length of pinblock
    unsigned char ucKsnLen;         ///< when event is PIN_EVENT_PINBLOCK or PIN_EVENT_PINFREE and using DUKPT, indicate the length of KSN
    int iErrCode;                   ///< when event is PIN_EVENT_ERR, indicate the error
    unsigned char aucPinBlock[32];  ///< when event is PIN_EVENT_PINBLOCK or PIN_EVENT_PINFREE, is PINBLOCK
    unsigned char aucKsn[10];       ///< when event is PIN_EVENT_PINBLOCK or PIN_EVENT_PINFREE and using DUKPT, is KSN
} Pin_Block_Data;

/**
 * @brief Event data of PSAM PINBLOCK
 * @see:: Pin_Block_Event
 */
typedef struct {
    unsigned char ucPinLen;         ///< when event is PIN_EVENT_LEN, indicate the PIN length inputted
    unsigned char ucRespLen;        ///< when event is PIN_EVENT_PINBLOCK, indicate the length of pinblock
    int iErrCode;                   ///< when event is PIN_EVENT_ERR, indicate the error
    unsigned char aucResp[256];     ///< when event is PIN_EVENT_PINBLOCK, is PINBLOCK
} Pin_Block_Data_Ext;

/**
 * @brief Event data of PWD
 * @see:: Pwd_Event
 */
typedef struct {
    unsigned char ucPwdLen;         ///< when event is PWD_EVENT_LEN, indicate the PWD length inputted
    int iErrCode;                   ///< when event is PWD_EVENT_ERR, indicate the error
    unsigned char aucEvtResp[10];   ///< when event is PIN_EVENT_ERR or PWD_EVENT_EXIT, is event data
} Pwd_Event_Data;

/**
 * @brief Material of PINBLOCK
 */
typedef struct {
    unsigned char KeyArch;          ///< Refer to Key_Arch_Type
    unsigned char KeyIdx;           ///< key index
    unsigned char Mode;             ///< Pin_Block_Mode_Type
    unsigned char PanLen;           ///< Length of PAN
    unsigned char TradeInfoLen;     ///< Length of Trade information
    unsigned char ListLen;          ///< Length of PIN LEN list
    unsigned long TimeoutMs;        ///< Timeout
    unsigned char Pan[20];          ///< PAN with check byte; Check byte should be set 0x00 if APP doesn't get it.
    unsigned char TradeInfo[8];     ///<  Trade information
    unsigned char ExpPinLenList[12];///< Length of PIN permit.
} Pin_Block_Material_Type;

/**
 * @brief Material of PSAM PINBLOCK
 */
typedef struct {
    unsigned char Slot;             ///< PSAM slot
    unsigned char Mode;             ///< Refer to Pin_Block_Mode_Type
    unsigned char PanLen;           ///< Length of PAN
    unsigned char TradeInfoLen;     ///< Length of trade information
    unsigned char ListLen;          ///< Length of PIN length list 
    unsigned char CmdLen;           ///< Length of APDU command
    unsigned long TimeoutMs;        ///< Ms of timeout
    unsigned char Pan[20];          ///< PAN with check byte; Check byte should be set 0x00 if APP doesn't get it.
    unsigned char TradeInfo[8];     ///< Trade information
    unsigned char ExpPinLenList[12]; ///< PIN length list
    unsigned char ApduCmd[256];     ///< Shall be case3(with Lc, without Le)
} Pin_Block_Psam_Material_Type;

/**
 * @brief Material of offline plain PIN
 */
typedef struct {
    unsigned char Slot;             ///< card slot
    unsigned char Mode;             ///< Offline_Mode_Type
    unsigned char ListLen;          ///< Length of PIN length list 
    unsigned long TimeoutMs;        ///< Ms of timeout
    unsigned char ExpPinLenList[12]; ///< PIN length list
} Plain_Pin_Material_Type;

/**
 * @brief Material of offline cipher PIN
 */
typedef struct {
    unsigned char Slot;             ///< card slot
    unsigned char Mode;             ///< Offline_Mode_Type
    unsigned char ListLen;          ///< Length of PIN length list 
    unsigned char PubModLen;        ///< Length of public key modulus
    unsigned char PubExpLen;        ///< Length of public key exponent
    unsigned char CardRndLen;       ///< Length of random number
    unsigned long TimeoutMs;        ///< Ms of timeout
    unsigned char ExpPinLenList[12]; ///< PIN length list
    unsigned char PubMod[256];      ///< Public modulus
    unsigned char PubExp[4];        ///< Public exponent
    unsigned char CardRnd[8];       ///< Random number
} Cipher_Pin_Material_Type;

/**
 * @brief Event data of offline PIN
 * @see:: Pin_Block_Event
 */
typedef struct {
    unsigned char ucPinLen;         ///< when event is PIN_EVENT_LEN, indicate the PIN length inputted
    unsigned char ucRespLen;        ///< when event is PIN_EVENT_PINBLOCK, indicate the length of aucRespData
    unsigned char aucRespData[2];   ///< when event is PIN_EVENT_PINBLOCK, Status-Word of card.
    int iErrCode;                   ///< when event is PIN_EVENT_ERR, indicate the error.
} Offline_Pin_Data;

/**
 * @brief PinBlockEvent callback prototype.
 * @warning Never block and never do time-consuming things.
 */
typedef void (*PinBlockEventCB)(Pin_Block_Event , Pin_Block_Data *);
/**
 * @brief PinBlockPsamEvent callback prototype.
 * @warning Never block and never do time-consuming things.
 */
typedef void (*PinBlockPsamEventCB)(Pin_Block_Event , Pin_Block_Data_Ext *);
/**
 * @brief PwdEvent callback prototype.
 * @warning Never block and never do time-consuming things.
 */
typedef void (*PwdEventCB)(Pwd_Event , Pwd_Event_Data*);
/**
 * @brief OfflinePinEvent callback prototype.
 * @warning Never block and never do time-consuming things.
 */
typedef void (*OfflinePinEventCB)(Pin_Block_Event , Offline_Pin_Data *);

/**
 * @brief Key information
 * @details Key information for under key write in
 */
typedef struct {
    unsigned char ucSrcKeyType; ///< Upper key type: PED_TLK,PED_TMK,PED_TPK,PED_TAK,PED_TDK, should not lower then ucDstKeyType
    unsigned char ucDstKeyType; ///< Under key type: PED_TLK,PED_TMK,PED_TPK,PED_TAK,PED_TDK
    unsigned char ucSrcKeyIdx;  ///< Upper key index. Generally start from 1. Index=0 means that no upper key used and plaintext to write in.  
    unsigned char ucDstKeyIdx;  ///< Under key index.
    unsigned char ucDstKeyLen;  ///< Length of under key. Only permit: 8, 16, 24, 32
    unsigned char Algorithm;    ///< Algorithm: PED_TDEA, PED_AES, PED_SM4
    unsigned char RFU[10];      ///< RFU
    unsigned char ucDstKeyValue[32]; ///< Under key
} ST_KEY_INFO;


/**
 * @brief KCV information
 */
typedef struct {
/**
  * Check mode:
  * -# 0x00 - Do not check KCV;
  * -# 0x01 - Mode 1: KCV is the result of using key to TDES encrypt all zero;
  * -# 0x02 - Key odd check and then as mode 1;
  * -# 0x03 - Key even check and then as mode 1;
  * -# 0x04 - ICBC mode, KCV is the X9.19 MAC result of data([under key + ICBC-index] padding to multiple of 8)using Upper key;
  * -# 0x05 - CMAC mode;
  * -# 0x80 - TR-31 mode.
 */
    int iCheckMode; 
    int iDataLen; ///< Length of check data
    unsigned char szCheckBuf[128];  ///< Check data
} ST_KCV_INFO;

/**
 * @brief RSA key
 * @details RSA key for wirtting
 */
typedef struct {
    int iModulusLen;                ///< Length of modulus
    unsigned char aucModulus[512];  ///< Modulus, padding 00 on the right
    int iExponentLen;               ///< Length of exponent
    unsigned char aucExponent[512]; ///< Exponent, padding 00 on the right
    unsigned char aucKeyInfo[128];  ///< Key information
} ST_RSA_KEY;


/**
 * @brief mode of RSA public key exponent
 */
typedef enum{
    RSA_PUBLIC_EXP_MODE_01 = 0, ///< Length of RSA public key exponent is 1
    RSA_PUBLIC_EXP_MODE_03 ,    ///< Length of RSA public key exponent is 3
} RSA_PUBLIC_EXP_MODE;


/**
 * @brief RSA key
 * @details RSA key for generation
 */
typedef struct {
    int bits;                   ///< Bits of RSA modulus
    int modulusLen;             ///< Length of modulus
    unsigned char modulus[512]; ///< Modulus, padding 00 on the right
    int pubExpLen;              ///< Length of public key exponent
    unsigned char pubExp[3];    ///< Public key exponent, padding 00 on the right
    int priExpLen;              ///< Length of private key exponent
    unsigned char priExp[512];  ///< Private key exponent, padding 00 on the right
} ST_GEN_RSA_KEY;


/**
 * @brief hash algorithm type
 */
typedef enum {
    PED_HASH_ALGO_SHA1 = 0, ///< SHA1
    PED_HASH_ALGO_SHA256,   ///< SHA256
    PED_HASH_ALGO_MD5,      ///< MD5
    PED_HASH_ALGO_SM3,      ///< SM3
} ped_hash_t;

/**
 * @brief hash algorithm step
 */
typedef enum {
    HASH_STEP_INIT = 0, ///< Hash step: init
    HASH_STEP_UPDATE,   ///< Hash step: update
    HASH_STEP_FINISH,   ///< Hash step: finish
} hash_step_t;

/**
 * @brief hash algorithm context
 */
typedef struct  {
    unsigned char hashAlgo; ///< Hash algorithm, @see:: ped_hash_t
    unsigned char hashStep; ///< Hash step, @see:: hash_step_t
} PedHashCtx;

/**
 * @brief remote authentication algorithm type
 */
typedef enum {
    MODE_RSA1024_SHA1 = 0,  ///< remote authentication algorithm use RSA1024+SHA1
    MODE_RSA1024_SHA256,    ///< remote authentication algorithm use RSA1024+SHA256
    MODE_RSA2048_SHA1,      ///< remote authentication algorithm use RSA2048+SHA1
    MODE_RSA2048_SHA256,    ///< remote authentication algorithm use RSA2048+SHA256
} remote_auth_algo_t;


/**
 * @brief Stop PIN/PWD input
 * @retval 0: SUCCESS, <0: FAIL
 * @pre None
 */
int PedInputCancelRev(void);


/**
 * @brief Get PINBLOCK
 * @param [in] pstMaterial: PINBLOCK material
 * @param [in] callback:    PIN event callback function
 * @param [in] pData:       PIN event data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetPinBlockRev(Pin_Block_Material_Type *pstMaterial, PinBlockEventCB callback, Pin_Block_Data *pData);


/**
 * @brief Offline plain pin verify
 * @param [in] pstMaterial: PINBLOCK material
 * @param [in] cbFunc:      PIN event callback function
 * @param [in] pData:       PIN event data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedVerifyOfflinePlainRev(Plain_Pin_Material_Type *pstMaterial, OfflinePinEventCB cbFunc, Offline_Pin_Data *pData);

/**
 * @brief Offline cipher pin verify
 * @param [in] pstMaterial: PINBLOCK material
 * @param [in] cbFunc:      PIN event callback function
 * @param [in] pData:       PIN event data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedVerifyOfflineCipherRev(Cipher_Pin_Material_Type *pstMaterial, OfflinePinEventCB cbFunc, Offline_Pin_Data *pData);

/**
 * @brief Get PINBLOCK encrypted by PSAM
 * @param [in] pstMaterial: PINBLOCK material
 * @param [in] cbFunc:      PIN event callback function
 * @param [in] pData:       PIN event data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetPsamPinBlockRev(Pin_Block_Psam_Material_Type *pstMaterial, PinBlockPsamEventCB cbFunc, Pin_Block_Data_Ext *pData);

/**
 * @brief PED administrator function
 * @param [in] ucCmd:  ADMIN_MODE_TYPE
 * @param [in] cbFunc: PWD event callback function
 * @param [in] pData:  PWD event data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedAdminManageRev(unsigned char ucCmd, PwdEventCB cbFunc, Pwd_Event_Data *pData);

/**
 * @brief Key inject
 * @param [in] pstKeyInfoIn: Key info
 * @param [in] pstKcvInfoIn: KCV info
 * @param [in] uiTimeOut:    Timeout in Ms
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedWriteKeyExtRev(ST_KEY_INFO *pstKeyInfoIn, ST_KCV_INFO *pstKcvInfoIn, unsigned int uiTimeOut);

/**
 * @brief  Key inject
 * @param [in] pstKeyInfoIn: Key info
 * @param [in] pstKcvInfoIn: KCV info
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedWriteKeyRev(ST_KEY_INFO *pstKeyInfoIn, ST_KCV_INFO *pstKcvInfoIn);


/**
 * @brief DUKPT TIK inject
 * @param [in] ucGrpIdx:     DUKPT group index, permit [1,10]
 * @param [in] ucSrcKeyIdx:  TLK index
 * @param [in] ucKeyLen:     Length of TIK ciphertext
 * @param [in] pucKeyValIn:  TIK ciphertext
 * @param [in] pucKsnIn:     Initial KSN
 * @param [in] pucKcvInfoIn: KCV info
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedWriteTIKRev(unsigned char ucGrpIdx, unsigned char ucSrcKeyIdx, unsigned char ucKeyLen,
        unsigned char *pucKeyValIn, unsigned char *pucKsnIn, ST_KCV_INFO *pucKcvInfoIn);

/**
 * @brief MAC
 * @param [in]  ucKeyIdx:  TAK (MAC Key) index
 * @param [in]  ucMode: Mode
 * -#               00H -ANSI9.9
 * -#               01H - XOR-ECB-MAC
 * -#               02H - X9.19
 * @param [in]  pucDataIn: Message
 * @param [in]  usDataLen: Length of message
 * @param [out] pucMAC:    MAC
 * @retval  >=0: Length of MAC
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetMacRev(unsigned char ucKeyIdx, unsigned char ucMode, unsigned char *pucDataIn, unsigned short usDataLen, unsigned char *pucMAC);


/**
 * @brief DES
 * @param [in]  pucKey:       DES/TDES key
 * @param [in]  ucKeyLen:     Length of key in Bytes: 8/16/24
 * @param [in]  pucDataIn:    input data to calc
 * @param [in]  ucDataInLen:  length of input data, hava to mutiple of 8
 * @param [out] pucDataOut:   Output data after calc
 * @param [in]  uiSize:       Max size of dataOut
 * @param [in]  ucMode:       Refer to ped_symm_mode_t
 * @param [in]  ucEnc:        Refer to ped_func_t
 * @retval  >=0: Length of data out
 * @retval  <0: FAIL
 */
int PedCalcDesDPARev(unsigned char *pucKey, unsigned char ucKeyLen, unsigned char *pucDataIn, unsigned char ucDataInLen, 
            unsigned char *pucDataOut, unsigned int uiSize, unsigned char ucMode, unsigned char ucEnc);

/**
 * @brief AES
 * @param [in]  pucKey:       AES key
 * @param [in]  ucKeyLen:     Length of key in Bytes: 8/16/24
 * @param [in]  pucDataIn:    Message
 * @param [in]  ucDataInLen:  Length of Message(must be a mutiple of 8)
 * @param [out] pucDataOut:   Result
 * @param [in]  uiSize:       Size of buffer(pucDataOut)
 * @param [in]  ucMode:       Refer to ped_symm_mode_t
 * @param [in]  ucEnc:        Refer to ped_func_t
 * @retval  >=0: Length of data out
 * @retval  <0: FAIL
 */
int PedCalcAesDPARev(unsigned char *pucKey, unsigned char ucKeyLen, unsigned char *pucDataIn, unsigned char ucDataInLen, 
            unsigned char *pucDataOut, unsigned int uiSize, unsigned char ucMode, unsigned char ucEnc);


/**
 * @brief Enctypt/Decrypt
 * @param [in]  ucKeyIdx:    TDK index
 * @param [in]  ucMode:      mode.
 * @see:: PED_ECB_DEC
 * @see:: PED_CBC_DEC
 * @see:: PED_ECB_ENC
 * @see:: PED_CBC_ENC
 * @param [in]  pucDataIn:   Message
 * @param [in]  usDataInLen: Length of Message
 * @param [out] pucDataOut:  Enctypt/Decrypt result
 * @retval  >=0: Length of result
 * @retval  <0: FAIL
 * @pre None
 */
int PedCalcDESRev(unsigned char ucKeyIdx, unsigned char ucMode, unsigned char *pucDataIn, unsigned short usDataInLen, unsigned char *pucDataOut);


/**
 * @brief DUKPT MAC
 * @param [in] ucGrpIdx    Dukpt group index
 * @param [in] ucMode      mode.
 * @see:: PED_ECB_DEC
 * @see:: PED_CBC_DEC
 * @see:: PED_ECB_ENC
 * @see:: PED_CBC_ENC
 * @param [in] pucDataIn   Message
 * @param [in] usDataInLen Length of Message
 * @param [out] pucMAC     MAC
 * @param [out] pucMACLen  Length of MAC
 * @param [out] pucKSN     KSN
 * @param [out] pucKSNLen  Length of KSN
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetMacDukptRev(unsigned char ucGrpIdx, unsigned char ucMode, unsigned char *pucDataIn, unsigned short usDataInLen,
                    unsigned char *pucMAC, unsigned char *pucMACLen, unsigned char *pucKSN, unsigned char *pucKSNLen);


/**
 * @brief DUKPT encrypt/decrypt
 * @param [in]  ucGrpIdx:    DUKPT group ID
 * @param [in]  ucKeyType:   DUKPT key type
 * -#                           0x00: MAC key
 * -#                           0x01: DES key
 * @param [in]  ucMode:      Bitmask of mode:
 * -#                           BIT[0]: 0 - decrypt, 1 - encrypt;
 * -#                           BIT[1]: 0 - EBC,     1 - CBC
 * @param [in]  pucIV:       IV
 * @param [in]  uiIvLen:     Length of IV
 * @param [in]  pucDataIn:   Message
 * @param [in]  usDataInLen: Length of message
 * @param [out] pucDataOut:  Encrypt/Decrypt result
 * @param [out] pusDataOutLen: Length of result
 * @param [out] pucKSN:      KSN
 * @param [out] pucKSNLen:   Length of KSN
 * @retval  >0: Length of result+KSN
 * @retval  <0: Fail
 * @pre None
 */
int PedDukptDesRev(unsigned char ucGrpIdx, unsigned char ucKeyType, unsigned char ucMode,
        unsigned char *pucIV, unsigned int uiIvLen, unsigned char *pucDataIn, unsigned short usDataInLen,
        unsigned char *pucDataOut, unsigned short *pusDataOutLen, unsigned char *pucKSN, unsigned char *pucKSNLen);

/**
 * @brief Read KSN
 * @param [in]  ucGrpIdx:   DUKPT group index
 * @param [out] pucKSN:     KSN
 * @param [out] pucKsnLen:  Length of KSN
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetDukptKsnRev(unsigned char ucGrpIdx, unsigned char *pucKSN, unsigned char *pucKsnLen);

/**
 * @brief Increase KSN
 * @param [in] ucGrpIdx:    DUKPT group ID
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedDukptIncreaseKsnRev(unsigned char ucGrpIdx);

/**
 * @brief Get KCV
 * @param [in]  ucKeyType:  Key type
 * @param [in]  ucKeyIdx:   Key index
 * @param [out] pstKcvInfo: KCV mode and check data
 * @param [out] pucKcvOut:  KCV
 * @retval  >=0: Length of KCV
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetKcvRev(unsigned char ucKeyType, unsigned char ucKeyIdx, ST_KCV_INFO *pstKcvInfo, unsigned char *pucKcvOut);

/**
 * @brief Key variant
 * @param [in] ucKeyType:   Key type
 * @param [in] ucDstKeyIdx: Key index
 * @param [in] pucVar:      Variant for XOR
 * @param [in] ucVarLen:    Length of variant
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedWriteKeyVarRev(unsigned char ucKeyType, unsigned char ucDstKeyIdx, unsigned char *pucVar, unsigned char ucVarLen);

/**
 * @brief  Key interval time setting
 * @param [in] ulTPKIntervalTimeMs TPK: TPK interval time in MS
 * @param [in] ulTAKIntervalTimeMs TAK: TAK interval time in MS
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedSetIntervaltimeRev(unsigned long ulTPKIntervalTimeMs, unsigned long ulTAKIntervalTimeMs);

/**
 * @brief  Key tag setting
 * @param [in] pucKeyTagIn: Tag for key
 * @param [in] uiLen:       Length of key tag
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedSetKeyTagRev(unsigned char *pucKeyTagIn, unsigned int uiLen);

/**
 * @brief Key Erase
 * @param [in] pucTlv: Tlv of key to erase(Generally, NULL to erase all keys)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedEraseRev(unsigned char *pucTlv);


/**
 * @brief Write RSA key
 * @param [in] ucRsaKeyIdx: RSA key index
 * @param [in] pstRsakeyIn: RSA key
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre None
 */
int PedWriteRsaKeyRev(unsigned char ucRsaKeyIdx, ST_RSA_KEY* pstRsakeyIn);

/**
 * @brief RSA encrypt/decrypt
 * @param [in]  ucRsaKeyIdx: RSA key index
 * @param [in]  pucDataIn:   Message
 * @param [in]  uiDataInLen: Length of message (must less then RSA modulus)
 * @param [out] pucDataOut:  RSA result
 * @retval  >=0: Success, Length of result
 * @retval  <0: FAIL
 * @pre None
 */
int PedRsaRecoverRev(unsigned char ucRsaKeyIdx, unsigned char *pucDataIn, unsigned int uiDataInLen, unsigned char *pucDataOut);


/*
 *@brief RSA key generate
 *@param [in] ucPriIdx:   Private key index[0-4]
 *@note  0->not store
 *@param [in] ucPubIdx:   Public key index [0-4]
 *@note  0->not store
 *@warning Index of private and public should not be same except 0. Else, private key will be covered.
 *@param [in] uiRsaBits:  RSA modulus bits
 *@param [in] expMode:    Public key exponent mode
 *@see:: RSA_PUBLIC_EXP_MODE
 *@param [out] pstRsaKey: RSA key pair
 * @retval  >=0: Success, Length of data
 * @retval  <0: FAIL
 */
int PedRsaGenerateKeyRev(unsigned char ucPriIdx, unsigned char ucPubIdx,
            unsigned int uiRsaBits, RSA_PUBLIC_EXP_MODE expMode, ST_GEN_RSA_KEY *pstRsaKey);

/**
 * @brief Get random number
 * @param [out] pucRnd: Random number
 * @param [in]  uiLen:  Length of random number to get
 * @retval  >=0: Success, Length of random data
 * @retval  <0: FAIL
 * @pre None
 */
int PedGetRandomRev(unsigned char *pucRnd, unsigned int uiLen);

/**
 * @brief Initialize hash context
 * @param [in] enHashAlgo: Hash algorithm.
 * @see:: ped_hash_t
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 */
int PedHashInitRev(ped_hash_t enHashAlgo);

/**
 * @brief Update hash algorithm data
 * @param [in] enHashAlgo: Hash algorithm.
 * @see:: ped_hash_t
 * @param [in] pucData:    Data
 * @param [in] usDataLen:  Length of data
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre    PedHashInitRev
 */
int PedHashUpdateRev(ped_hash_t enHashAlgo, unsigned char *pucData, unsigned short usDataLen);

/**
 * @brief Finish Hash
 * @param [in]    enHashAlgo: Hash algorithm.
 * @see:: ped_hash_t
 * @param [out]   pucHash:    Hash result
 * @param [inout] pusHashLen: 
 * -#               [in]      Size of result Buffer(pucHash)
 * -#               [out]     Length of hash result
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 * @pre    PedHashInitRev and PedHashUpdate
 */
int PedHashFinalRev(ped_hash_t enHashAlgo, unsigned char *pucHash, unsigned short *pusHashLen);

/**
 * @brief Remote authentication mode setting
 * @param [in] mode: Remote authentication mode.
 * @see:: remote_auth_algo_t
 * retval none
 */
void PedSetRmtAuthAlgo(unsigned char mode);

/**
 * @brief Get remote authentication mode
 * @retval Remote authentication mode.
 * @see:: remote_auth_algo_t
 */
unsigned char PedGetRmtAuthAlgo(void);

/**
 * @brief Get remote authenticate request code
 * @param [out] pucReqSeq: Request code
 * @param [out] uiLen:     Length of request code
 * @param [in]  uiSize:    Size of buffer(pucReqSeq)
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 */
int PedGetRmtAuthReqCodeRev(unsigned char *pucReqSeq, unsigned int *uiLen, unsigned int uiSize);

/**
 * @brief Verify remote authentication code
 * @param [in] pucAuthCode: Authentication code
 * @param [in] usLen:       Length of authentication code
 * @retval  0: SUCCESS
 * @retval  <0: FAIL
 */
int PedVerifyAuthCodeRev(unsigned char *pucAuthCode, unsigned short usLen);

/** @} Ped */

/**
 * @defgroup SpDev SpDev
 * @brief SP dev APIs
 * @{
 */
//=============================================================
//#include "bw_spdev.h"
//=============================================================

/**
 * @brief prototype of card event callback
 * @warning Never block and never do time-consuming things.
 * @param [in] event: 0x7C: MagCard evnt, 0x7D: ICCard event
 */
typedef void (*cardevent_callback)(int event);


/**
 * @brief Card event callback register
 * @param cb [in] callback for card event
 */
int RegisterCardEventCallback(cardevent_callback cb);


/**
 * @brief SP power on/off
 * @param [in] onoff: 0: power off, 1: power on
 */
void BWSP_Power(int onoff);

/**
 * @brief SP firmware update
 * @param [in] fwfile:     FW file name
 * @param [in] rescb:      Result callback
 * @param [in] process_cb: Progress callback (Progress from 0 to 100)
 * @retval  0: Success
 * @retval  <0: Fail
 */
int BWSP_FirmwareUpdateStart(char *fwfile, void (*rescb)(int result), void (*process_cb)(int percent));


/**
 * @brief SP bridge mode set
 * @param [in] onoff:
 * -#           0: unbridge
 * -#           1: bridged
 * @retval None
 */
void BWSP_SetBridgeMode(int onoff);

/**
 * @brief Send raw data to SP
 * @param [in] pucData: Raw data
 * @param [in] uiLen:   Length of data
 * @retval  0: Success
 * @retval  <0: Fail
 * @pre
 */
int BWSP_SendSPRaw(unsigned char *pucData, unsigned int uiLen);

/**
 * @brief Receive raw data from SP
 * @param [out] pucBuf:     Raw data from SP
 * @param [in] uiSize:      Size of receive buffer(pucBuf)
 * @param [out] piLen:      Length of raw data
 * @param [in] uiTimeoutMs: Timeout for receive
 * @retval  0: Success
 * @retval  <0: Fail.
 * @pre   BWSP_SetBridgeMode, It must set to bridge mode before and set to unbridge mode after.
 */
int BWSP_RecvSPRaw(unsigned char *pucBuf, unsigned int uiSize, int *piLen, unsigned int uiTimeoutMs);

/** @} SpDev */

/** @} SP */

/**
 * @defgroup port_bridge port_bridge
 * @brief Port Bridge related interface
 * @{
 */

//=============================================================
// "port_bridge.h"
//=============================================================
/** @brief �˿��豸����**/
/** @brief Port Device Definition**/
typedef enum {
    PORT_USB_AT,  ///< USB-AT�˿� (USB - AT port)
    PORT_UART_0,  ///< UART0
    PORT_UART_1   ///< UART1
} port_dev_t;

/**
 * @brief Bridge the serial port A and B
 * @param portA [in] Serial Port A. refer port_dev_t
 * @param portB [in] Serial Port B. refer port_dev_t
 * @param pstComCfg [in] Physical serial port configuration
 * @retval 0 Success
 * @retval -1 Fail
 */
int port_bridge_start_ex(port_dev_t portA, port_dev_t portB, COM_CONFIG_T *pstComCfg);

/**
 * @brief Bridge the serial port A and B, baudrate 115200.
 * @param portA [in] Serial Port A. refer port_dev_t
 * @param portB [in] Serial Port B. refer port_dev_t
 * @retval 0 Success
 * @retval -1 Fail
 */
int port_bridge_start(port_dev_t portA, port_dev_t portB);

/**
 * @brief Stop Port Bridge
 * @brief �ر��Ž�
 * @retval 0 Success (return value 0: success)
 * @retval -1 Fail (return value -1: fail)
 */
int port_bridge_stop(void);
/** @} port_bridge */

/**
 * @defgroup softtimer softtimer
 * @brief timer related interface
 * @{
 */
//=============================================================
//#include "softtimer.h"
//=============================================================

/**
 * @brief Timer data structure
 * @brief ��ʱ�����ݽṹ
 */
typedef struct {
    unsigned long start;  ///< ��ʼ������ (time start)
    unsigned long timeout; ///< ��ʱʱ�� (time out)
    unsigned long (*tick_fun)(void); ///< ��ʱ��callback (timer call back)
} T_SOFTTIMER;

/**
 * @brief Timer setup
 * @brief ���ü�ʱ��
 * @param tm [in] T_SOFTTIMERָ�� (T_SOFTTIMER pointer)
 * @param lms [in] ��ʱ������ (time length in ms)
 */
void s_TimerSet(T_SOFTTIMER *tm, unsigned long lms);

/**
 * @brief Check Timer remain time
 * @brief ����ʱ��ʣ���ʱ��
 * @param tm [in] T_SOFTTIMERָ�� (T_SOFTTIMER pointer)
 * @retval 0 ��ʱ���Ѿ����� (return value 0: timer end)
 * @retval !0 ��ʱ��ʣ���ms�� (return value !0: remain time)
 */
unsigned long s_TimerCheck(T_SOFTTIMER *tm);
/** @} softtimer */

/**
 * @defgroup filesystem filesystem
 * @brief filesystem related interface
 * @{
 */
 
/**
 * @defgroup basefileapi basefileapi
 * @brief Basic file operation related interface
 * @{
 */ 
//=============================================================
//#include "bwfs.h"
//=============================================================

#define O_RDWR          0x01 ///< ��дģʽ���ļ������Ѿ����� (Read and Write Mode, file must exist)
#define O_CREATE        0x02 ///< �½�ģʽ���ļ�������ʱ�Զ����� (Create new file Mode, will auto-create new file if not exist)
#define O_RO            0x03 ///< ֻ��ģʽ���ļ������Ѿ����� (Read Only Mode, file must exist)

#define SEEK_CUR        0 ///< �ӵ�ǰλ�ÿ�ʼ (From current position)
#define SEEK_SET        1 ///< ��ָ��λ�ÿ�ʼ���� (From specified position) 
#define SEEK_END        2 ///< ���ļ�β��ʼ (From the end of file)

#define BWFS_ERR_BASE        (-5800)           ///< �ļ�ϵͳ��������ʼ��� (File system error code initial number)
#define FS_ERR_FILENAME_SIZE (BWFS_ERR_BASE-1) ///< �ļ�����С���� (File name size error)
#define FS_ERR_PARAM         (BWFS_ERR_BASE-2) ///< �������� (Parameter error)
#define FS_ERR_WRITE         (BWFS_ERR_BASE-3) ///< д�ļ����� (File write error)
#define FS_ERR_READ          (BWFS_ERR_BASE-4) ///< ���ļ����� (File read error)
#define FS_ERR_SEEK          (BWFS_ERR_BASE-5) ///< �����ļ�ָ����� (File pointer setting error)
#define FS_ERR_MAXFILE_OPEN  (BWFS_ERR_BASE-6) ///< �������ļ������� (Maximum file opened error)
#define FS_ERR_OPEN          (BWFS_ERR_BASE-7) ///< ���ļ�ʧ�� (Open file fail)
#define FS_ERR_NOT_OPEN      (BWFS_ERR_BASE-8) ///< �ļ���δ�� (File not open yet error)

/**
 * @brief Initialize File System
 * @retval 0 Success
 * @retval !0 Fail
 */
int BWFS_Init(void);

/**
 * @brief ���ļ�
 * @brief Open File
 * @param filename [in] �ļ�����������16���ַ� (File name, no more than 16 character)
 * @param mode [in] ��ģʽ����ѡ O_RDWR, O_CREATE �� O_RO (Open mode: O_PDWR, O_CREATE or O_RO)
 * @retval >=0: Success,�ļ������� (return value >= 0: open file success, file descriptor)
 * @retval ��0 Fail (return value != 0: open file fail)
 * @pre BWFS_Init
 */
int FsOpen(const char *filename, unsigned char mode);

/**
 * @brief �ر��Ѵ򿪵��ļ�
 * @brief Close opened file
 * @param fd [in] �ļ������� (file descriptor)
 * @retval 0 Success (return value 0: close file success)
 * @retval <0: Fail (return value <0: close file fail)
 * @pre FsOpen
 */
int FsClose(int fd);

/**
 * @brief ���Ѿ��򿪵��ļ�д������
 * @brief Write data into opened file
 * @param fd [in] �ļ������� (file descriptor)
 * @param dat [in] Ҫд������� (data for written)
 * @param len [in] Ҫд��������ֽ��� (length of data for written)
 * @retval >=0: Success,ʵ��д��ĳ��� (return value >=0: : data write in success, length of data written)
 * @retval <0: Fail (return value <0: data write in fail)
 * @pre FsOpen
 */
int FsWrite(int fd, unsigned char *dat, int len);

/**
 * @brief ���Ѿ��򿪵��ļ�������
 * @brief Read data from opened file
 * @param fd [in] �ļ������� (file descriptor)
 * @param dat [out] ���������ݻ����� (buffer for data read)
 * @param len [in] Ҫ�����������ֽ��� (length of date read)
 * @retval >=0: Success,ʵ�ʶ����ĳ��� (return value >= 0: data read success, length of data read)
 * @retval <0: Fail (return value < 0: data read fail)
 * @pre FsOpen
 */
int FsRead(int fd, unsigned char *dat, int len);

/**
 * @brief �����Ѵ��ļ���ָ��λ��
 * @brief Set up pointer position for opened file
 * @param fd [in] �ļ������� (file descriptor)
 * @param offset [in] ƫ���� (offset)
 * @param origin [in] ƫ�����Ĳο�λ�� (origin position)
 * @retval 0 Success,ʵ�ʶ����ĳ��� (return value 0: set up success, real length of data read)
 * @retval <0: Fail (return value 0: set up fail)
 * @pre FsOpen
 */
int FsSeek(int fd, long offset, unsigned char origin);

/**
 * @brief Get current file pointer location
 * @param fd [in] file descriptor
 * @retval >=0: Success, offset from file begin
 * @retval <0: Fail
 */
int FsGetPointer(int fd);

/**
 * @brief Set file size, fill zero if bigger than original file length
 * @param fd [in] file descriptor
 * @param newsize [in] new file size in bytes
 * @retval 0 Success
 * @retval -1 Fail
 */
int FsSetSize(int fd, unsigned int newsize);

/**
 * @brief ɾ���ļ�
 * @brief Delete file
 * @param filename [in] �ļ��� (file name)
 * @retval 0 Success (return value 0: delete success)
 * @retval <0: Fail(return value < 0: delete fail)
 * @pre None
 */
int FsRemove(const char *filename);

/**
 * @brief Rename file from srcname to destname
 * @param srcname [in] the name of source file
 * @param destname [in] the name of destination file
 * @retval 0 Success
 * @retval !0 Fail
 */
int FsRename(char *srcname, char *destname);

/**
 * @brief ��ȡ�ļ���С
 * @brief Get file size
 * @param filename [in] �ļ��� (file name)
 * @retval >=0: Success,�ļ��Ĵ�С (return value >= 0: get size success, file size)
 * @retval <0: Fail (return value < 0: get size fail)
 * @pre None
 */
int FsSize(const char *filename);

/**
 * @brief Get file size from file descriptor
 * @param fd [in] file descriptor
 * @retval >=0: Success, the file size in byte
 * @retval <0: Fail
 */
int FsSizeFd(int fd);

/**
 * @brief Calc SHA256 of file
 * @param filename [in] file path
 * @param hashout [out] HASH output
 * @param hashlen [in] Length of hash buffer in byte
 * @retval 0 Success
 * @retval !0 Fail
 */
int FsFileSha256Calc(char *filename, void *hashout, int hashlen);

/**
 * @brief Verify the SHA256 of specific file
 * @param filename [in] path of file
 * @param hash [in] Expected SHA256 HASH
 * @param hashlen [in] Length of hash in byte
 * @retval 0 Success
 * @retval !0 Fail
 */
int FsFileSha256Check(char *filename, void *hash, int hashlen);

/**
 * @brief �ؽ��ļ�ϵͳ
 * @brief Rebuild file system
 * @retval 0 Success (return value 0: rebuild success)
 * @retval <0: Fail (return value < 0: rebuild fail)
 * @pre BWFS_Init
 */
int FsRebuild(void);

/**
 * @brief ��ȡ�ļ�ϵͳʣ��ռ�
 * @brief Get file system free space
 * @retval >=0: ʣ��ռ�(��λ: �ֽ�) (return value >= 0: Free space, unit: byte)
 * @retval <0 ��ȡʧ�� (return value <0: get free space fail)
 */
int FsGetFreeSpace(void);

/**
 * @brief ��ȡ�ļ�ϵͳ��ʹ�ÿռ�
 * @brief Get file system used space
 * @retval >=0: ��ʹ�ÿռ�(��λ: �ֽ�) (return value >= 0: Used space, unit: byte)
 * @retval <0 ��ȡʧ�� (return value < 0: get used space fail)
 */
int FsGetUsedSpace(void);

/**
 * @brief Create directory
 * @param pathName [in] Directory path
 * @retval 0 Success
 * @retval !0 Fail
 */
int FsCreateDir(const char *pathName);

/** @} basefileapi */

/** @} filesystem */


/**
 * @defgroup lcd lcd
 * @brief LCD operation related interfacce
 * @brief lcd������ؽӿ�
 * @{
 */
//=============================================================
//#include "bwlcd.h"
//=============================================================
#define MERCURY_COLOR_NONE (0xFFFF) ///< ��������ɫ��ʹ��ϵͳ��ɫ (No color setup, using system color)

#define NON_TRANSPARENT (0)		///< ��͸�� (None-transparent)
#define TRANSPARENT (2)			///< ͸�� (Transparent)

#define FONT_SIZE_NORMAL 0		///< normal�����С (Text font size normal)
#define FONT_SIZE_SMALL  1		///< small�����С (Text font size small)
#define FONT_SIZE_BIG    2      ///< small�����С (Text font size big)

/**
 * @brief Data structure that describe text property
 * @brief ��������������ʾ���Ե���������
 */
typedef struct {
    unsigned int fColor; ///< ������ʾʱ��ǰ��ɫ (Text foreground color)
    unsigned int bColor; ///< ������ʾʱ�ı���ɫ (Text background color)
    unsigned char Mode; ///< Mode - ������ʾʱ͸�����ǲ�͸�� (Mode setup for None-transparent or Transparent)
    unsigned char Type; ///< �������� (Font Type)
    unsigned char Size; ///< �����С��� (Font Size)
} tsFont;

/**
 * @brief Data structure that describe a rectangle
 * @brief ��������һ�����ε���������
 */
typedef struct {
    short Left; ///< ������ (Horizontal coordinate)
    short Top; ///< ������ (Vertical coordinate)
    short Width; ///< ��� (Width)
    short Height; ///< �߶� (Height)
} tsRect;

/**
 * @brief Data structure that describe display screen
 * @brief ����������ʾ����������������
 */
typedef struct {
    short Width; ///< ��ʾ���Ŀ�� (��λ: ����) */ (Width, unit: pixel)
    short Height; ///< ��ʾ���ĸ߶� (��λ: ����) (Height, unit: pixel)
} tsScrInfo;

/**
 * @brief Clean up all information on display screen, status bar can not be cleaned
 * @brief �����ʾ��������Ϣ�� ״̬���������
 * @retval  None (no return value)
 * @pre None 
 */
void ScrCls(void);

/**
 * @brief Clean up specified area on display screen
 * @brief ������ʾ��ָ������
 * @note �б���ʱ�ñ���ͼ�ڸǣ������ñ���ɫ�ڸ� (If there is a background picture, use picture to cover. If not, use background color)
 * @note ״̬�������޷����� (status bar can not be cleaned)
 * @param rect [in] Ҫ����ľ������� (Area need to be cleaned up)
 */
void ScrClsArea(tsRect *rect);

/**
 * @brief Get background picture on specified area
 * @brief ��ȡָ������ı���ͼƬ
 * @param rect [in] ָ���ľ������� (specify area)
 * @param buff [out] �þ�������ı������ݻ�����(��ַ����2�ֽڶ���) (Address of buffer that store the information in specified retangle area, Address must be groups of 2 bytes)
 * @param buflen [int] ������buff�����ߴ�(��λ: �ֽ�) (Buffer size, unit: byte)
 * @retval 0 Success (return value 0: success)
 * @retval !0 Fail (return value !0: fail)
 */
int ScrGetBgBitmapArea(tsRect *rect, void *buff, unsigned int buflen);

/**
 * @brief Get address of main interface background picture
 * @brief ��ȡ�����汳��ͼƬ��ַ
 * @note ͼƬ����ʾ���ֱ���һ����,��240x320��320x240 (Picture must be same size with display screen, for example: 240x320 or 320x240)
 * @retval NULL û�б���ͼƬ (return value NULL: no background picture)
 * @retval !NULL ����ͼƬ��BitMap��������ַ (return value !NULL: the address of background picture bitmap buffer
 */
void* ScrGetBgBitmap(void);

/**
 * @brief Setup main interface background picture
 * @brief ����������ı���ͼƬ
 * @note ͼƬ��������ʾ���ֱ���һ����,��240x320��320x240 (Picture must be same size with display screen, for example: 240x320 or 320x240)
 * @param data [in] λͼ��������RGB565��ʽ(ÿ������ռ��2�ֽ�)  (Bitmap storage buffer, Bitmap in RGB565, every pixel take 2 bytes)
 * @retval 0 Success (return value 0: success)
 * @retval !0 ��ַ�Ƿ�������2�ֽڶ��� (return value !0: invalid address, ???)
 */
int ScrSetBgBitmap(void *data);

/**
 * @brief Setup current displaying origin position
 * @brief ָ����ǰ��ʾ��ʼλ��
 * @param [in] x ָ����ʾ�豸�Ϻ�������λ�� (x for horizontal position)
 * @param [in] y ָ����ʾ�豸����������λ�� (y for vertical position)
 * @retval  None (no return value)
 * @pre None 
 */
void ScrGotoXY(unsigned short x, unsigned short y);

/**
 * @brief Get current displaying origin position 
 * @brief ��ȡ��ǰ�ַ���ʾ����ʼλ��
 * @param [out] x ��ǰ�ַ���ʾ�ĺ����� (x for horizontal position)
 * @param [out] y ��ǰ�ַ���ʾ�������� (y for vertical position)
 */
void ScrGetXY(unsigned short *x, unsigned short *y);

/**
 * @brief Display specified text informaion in current location
 * @brief �ڵ�ǰλ�ÿ�ʼ��ʾָ������������
 * @param [in] ptext Ҫ��ʾ���������� (text information)
 * @retval  None (no return value)
 * @pre None
 */
void ScrTextOut(unsigned char *ptext);

/**
 * @brief Setup property for following text
 * @brief ָ��������������ʾ����
 * @param [in] pFont ���ֵ���ʾ���� (text property)
 * @retval  None (no return value)
 * @pre None
 */
void ScrSetFont(tsFont *pFont);

/**
 * @brief Get current text property
 * @brief ��ȡ��ǰ��������ʾ����
 * @param [in] pFont ���ֵ���ʾ���� (text property)
 * @retval  None (no return value)
 * @pre None
 */
void ScrGetFont(tsFont *pFont);

/**
 * @brief Display bitmap in specified area
 * @brief ָ��������ʾָ������ʾBitmap
 * @param [in] pRect ָ���������� (specify area)
 * @param [in] pBitmap Ҫ��ʾ��bitmap���� (bitmap)
 * @retval None (no return value)
 * @pre None
 */
void ScrBitMap(tsRect *pRect, unsigned char *pBitmap);

/**
 * @brief Get display device status
 * @brief ��ȡ��ʾ�豸״̬
 * @param [out] pScrInfo ��ʾ�豸��Ϣ (display device information)
 * @retval None (no return value)
 * @pre None
 */
void ScrGetStatus(tsScrInfo *pScrInfo);

/**
 * @brief Adjust background brightness
 * @brief ���ڱ�������
 * @param [in] level ���ȣ���ΧΪ0-14 (brightness level, from 0 - 14)
 * @retval None (no return value)
 * @pre None
 */
void ScrSetBackLight(unsigned short level);

/**
 * @brief Clean up specified area, keep background picture
 * @brief ����Ļָ������ ��������ͼ
 * @param [in] prect Ҫ����ľ������� (specified area)
 * @retval None no return value
 * @pre None
 */
void ScrRectClear(tsRect *prect);

/**
 * @brief ������Ļ����
 * @brief Refresh Screen
 * @retval None no return value
 * @pre None
 */
void ScrRefresh(void);

/**
 * @brief Setup pixel color on specified coordinate
 * @brief ��ָ����ʾ�������������ص���ɫ
 * @param [in] color ��ʾ��ɫ���ο�: MERCURY_PALETEE_ARRAY_INDEX_E (color, for example: MERCURY_PALETEE_ARRAY_INDEX_E)
 * @retval None no return value
 * @pre None
 */
void ScrSetPixel(unsigned short color);

/**
 * @brief Draw rectangle frame without fill
 * @brief ���ƿ��ľ��ο�
 * @param [in] rect ���β��� rectangle information
 * @param [in] penw �߿��� frame width
 * @param [in] color �߿���ɫ frame color
 * @retval None no return value
 * @pre None
 */
void ScrDrawRect(tsRect *rect, short penw, short color);

/**
 * @brief Fill rectangle
 * @brief ������
 * @param [in] rect ���β��� rectangule information
 * @param [in] color �����ɫ fill color
 * @retval None no return value
 * @pre None
 */
void ScrFillRect(tsRect *rect, short color);

/**
 * @brief Screen displaying string
 * @brief ��Ļ��ʽ������ַ���
 * @param [in] fmt ��ʽ���ַ��� String
 * @param [in] ... �����б� parameter list
 * @retval None no return value
 * @pre None
 */
void ScrPrintf(char *fmt, ...);

/**
 * @brief Generat QR code, store the bitmap into buffer
 * @param paystr [in] string to make QR code
 * @param buf [out] the QR code bitmap buffer (1 dot per bit)
 * @param buflen [in] the max bytes of buf, [out] output bytes of QR code bitmap buffer
 * @param bitmap_width [out] the side length of QRbitmap in dot
 * @retval 0 Success
 * @retval <0: Fail
 */
int QrCodeGenBitmapBuf(char *paystr, void *buf, unsigned int *buflen, unsigned int *bitmap_width);

/**
 * @brief ���ɶ�ά�룬����ʾ��ָ������
 * �����Ķ�ά��λ��ָ����������룬���Դ�1�����صİױ�
 * @brief Generate QR code and display on specified area
 * 		QR code will be sit in the middle of the area with the 1 pixel width white frame
 * @param [in] rect ������ʾ���� rectangle display area
 * @param [in] paystr �ַ��� string
 * @retval 0 Success (return 0: success)
 * @retval <0: Fail (return <0: fail)
 * @pre None
 */
int ScrShowQrCode(tsRect *rect, char *paystr);

/**
 * @brief Generate QR code and display on specified area
 * @brief ���ɶ�ά�룬����ʾ��ָ������
 * @note  QR code will be sit in the middle of the area with the user input pixel width white frame
 * @note  �����Ķ�ά��λ��ָ����������룬�ױ߿���ֶ�ָ��
 * @param [in] rect ������ʾ���� rectangle display area
 * @param [in] paystr �ַ��� string
 * @param [in] marginWidth �ױ߿��(��λ����) width of white frame, unit: pixel
 * @retval 0 Success return 0: success
 * @retval <0: Fail return <0: fail
 * @pre None
 */
int ScrShowQrCodeExt(tsRect *rect, char *paystr, unsigned int marginWidth);

/**
 * @brief Get current main interface background color
 * @brief ��ȡ��ǰ������ı���ɫ
 * @retval ��ǰ������ı���ɫ(MERCURY��ɫ) return value: current main interface background color, in MERCURY color
 */
unsigned short ScrGetMainBgColor(void);

/**
 * @brief Get current main interface foreground color
 * @brief ��ȡ��ǰ�������ǰ��ɫ
 * @retval ��ǰ�������ǰ��ɫ(MERCURY��ɫ) renturn value: current main interface foreground color, in MERCURY color
 */
unsigned short ScrGetMainFgColor(void);

/**
 * @brief Setup main interface background color
 * @brief ����������ı���ɫ
 * @param color [in] MERCURY��ɫ (MERCURY color)
 */
void ScrSetMainBgColor(unsigned short color);

/**
 * @brief Setup main interface foreground color
 * @brief �����������ǰ��ɫ
 * @param color [in] MERCURY��ɫ (MERCURY color)
 */
void ScrSetMainFgColor(unsigned short color);

/**
 * @brief Get current status bar backgroung color
 * @brief ��ȡ��ǰ״̬���ı���ɫ
 * @retval ��ǰ״̬���ı���ɫ(MERCURY��ɫ) return value: MERCURY color
 */
unsigned short ScrGetStatusBarBgColor(void);

/**
 * @brief Get current status bar foreground color
 * @brief ��ȡ��ǰ״̬����ǰ��ɫ
 * @retval ��ǰ״̬����ǰ��ɫ(MERCURY��ɫ) return value: MERCURY color
 */
unsigned short ScrGetStatusBarFgColor(void);

/**
 * @brief Set up status bar background color
 * @brief ����״̬���ı���ɫ
 * @param color [in] MERCURY��ɫ MERCURY color
 */
void ScrSetStatusBarBgColor(unsigned short color);

/**
 * @brief Set up status bar foroground color
 * @brief ����״̬����ǰ��ɫ
 * @param color [in] MERCURY��ɫ MERCURY color
 */
void ScrSetStatusBarFgColor(unsigned short color);

/**
 * @brief Get status bar height
 * @brief ��ȡ״̬���ĸ߶�
 * @retval ��ǰ״̬���ĸ߶�(��λ:����) return value: stats bar height. Unit: pixel
 */
unsigned short ScrGetStatusBarHeight(void);

/**
 * @brief Enable/Disable status bar auto refresh
 * @param onoff [in] 0 - Disable auto-refresh, 1 - Enable auto-refresh
 */
void ScrSetStatusBarAutoRefresh(int onoff);

/**
 * @brief Transfer MERCURY color to RGB color
 * @brief ��MERCURY_PALETTE��ɫת��ΪRGB��ɫ
 * @param [in] color ��ɫ���ο�:MERCURY_PALETEE_ARRAY_INDEX_E (MERCURY color)
 * @retval rgb RGB��ɫ return value: RBG color
 * @pre None
 */
unsigned short MercuryColorToRGB(unsigned short color);

/**
 * @brief Screen color test
 * @brief ��Ļ��ɫ����
 * ��-��-��-��-��
 * RED-GREEN-BLUE-WHITE-BLACK
 */
void ScrTest(void);

/**
 * @brief QR Code display test
 * @retval None
 */
void ScrQrCodeTest(void);

/** @} lcd */


/**
 * @defgroup keyboard keyboard
 * @brief Keyboard operation related interface
 * @brief ����������ؽӿ�
 * @{
 */
//=============================================================
//#include "bwkb.h"
//=============================================================
#define KEY_NONE           (0x00) ///< No Key(�ް��� )
#define KEY_ASCII1         (0x31) ///< Key "1"(����"1"�ļ�ֵ)
#define KEY_ASCII2         (0x32) ///< Key "2"(����"2"�ļ�ֵ)
#define KEY_ASCII3         (0x33) ///< Key "3"(����"3"�ļ�ֵ)
#define KEY_ASCII4         (0x34) ///< Key "4"(����"4"�ļ�ֵ)
#define KEY_ASCII5         (0x35) ///< Key "5"(����"5"�ļ�ֵ)
#define KEY_ASCII6         (0x36) ///< Key "6"(����"6"�ļ�ֵ)
#define KEY_ASCII7         (0x37) ///< Key "7"(����"7"�ļ�ֵ)
#define KEY_ASCII8         (0x38) ///< Key "8"(����"8"�ļ�ֵ)
#define KEY_ASCII9         (0x39) ///< Key "9"(����"9"�ļ�ֵ)
#define KEY_ASCII0         (0x30) ///< Key "0"(����"0"�ļ�ֵ)
#define KEY_ALPHA          (0x04) ///< Key "ZiMu"(����"��ĸ"�ļ�ֵ)
#define KEY_FUNC           (0x05) ///< Key "FUNC"(����"����"�ļ�ֵ)
#define KEY_CANCEL         (0x1B) ///< Key "CANCEL"(����"ȡ��"�ļ�ֵ)
#define KEY_CLEAR          (0x03) ///< Key "CLEAR"(����"���"�ļ�ֵ)
#define KEY_ENTER          (0x0D) ///< Key "ENTER"(����"ȷ��"�ļ�ֵ)
#define KEY_SCAN           (0x0B) ///< Key "SCAN"(����"ɨ��"�ļ�ֵ)
#define KEY_UP             (0x26) ///< Key "UP"(����"UP"�ļ�ֵ)
#define KEY_DOWN           (0x28) ///< Key "DOWN"(����"DOWN"�ļ�ֵ)
#define KEY_00			   (0x08) ///< Key "00"(����"00"�ļ�ֵ)
#define KEY_MENU		   (0x02) ///< Key "MENU"(����"MENU"�ļ�ֵ)
#define KEY_DIV            (0x2F) ///< Key "��"(���� "��")
#define KEY_MUL            (0x2A) ///< Key "x"(���� "��")
#define KEY_ADD            (0x2B) ///< Key "+"(���� "+")
#define KEY_SUB            (0x2D) ///< Key "-"(���� "-")
#define KEY_REPLAY         (0x12) ///< Key "REPLAY"(���� "�ز�")
#define KEY_REFUND         (0x13) ///< Key "REFUND"(���� "�˿�")
#define KEY_COLLECTION     (0x14) ///< Key "COLLECTION"(���� "�տ�")
#define KEY_DOT            (0x2E) ///< Key "."(���� ".")
#define KEY_F1             (0x41) ///< Key "F1"(���� "F1")
#define KEY_F2             (0x42) ///< Key "F2"(���� "F2")
#define KEY_F3             (0x43) ///< Key "F3"(���� "F3")

/**
 * @brief ��հ����������� ����֮ǰ���еİ�����¼
 * @brief Clean up keyboard buffer, clean up all previous press record
 * @retval None no return value
 * @pre None
 */
void KbFlush(void);

/**
 * @brief ��ѯ�Ƿ��а���
 * @brief Check is there keyboard hit record or not
 * @retval  0 �а�����¼ return 0: has hit record
 * @retval  1 �ް�����¼ return 1: no hit record
 * @pre None
 */
int KbHit(void);

/**
 * @brief �ȴ�����
 * @brief Wait for press
 * @param timeoutms [in] ���ʱʱ�� (Maximum wait time)
 *         0: �������� (return right now)
 *        -1: һֱ�ȴ�ֱ���а��� (wait until pressed)
 *        >0: �а���ʱ�������ذ���ֵ���������ȴ�timeoutms���� (when pressed, return pressed value, or wait "timeoutms"
 * @retval KEY_NONE û�а�����ʱ no key pressed or time out
 * @retval KEY_XXXX ʵ�ʼ�ֵ,��KEY_ENTER (key pressed)
 * @pre None
 */
int KbWaitKey(int timeoutms);

/**
 * @brief ��ȡ������ֵ������ģʽ
 * @brief Get key, blocking mode
 * @retval  ʵ�ʼ�ֵ key value
 * @pre None
 */
int KbGetKey(void);

/**
 * @brief ���ð��������
 * @brief Setup key background light
 * @param onoff [in] 0-�أ�1-�� (0 for OFF, 1 for ON)
 */
void KbSetBackLight(int onoff);

/**
 * @brief ������ʾ������
 * @brief Keyboard sound switch
 * @param onoff [in] 0-�أ�1-�� (0 for OFF, 1 for ON)
 */
void KbTone(int onoff);

/**
 * @brief Keyboard sound switch, and store this config to NV
 * @param onoff [in] 0-OFF��1-ON
 */
void KbToneNV(int onoff);

/**
 * @brief Play Keyboard sound
 */
void KbTonePlay(void);

/**
 * @brief �жϵ�ǰ������ʹ��̬
 * @brief Get current keyboard sound switch status
 * @retval 0 δ���������� 0 for keyboard sound OFF
 * @retval 1 �ѿ��������� 1 for keyboard sound ON
 */
int IsKbToneEnable(void);

/**
 * @brief ����ָ�������Ļ��ѹ���
 * @brief Setup system wake up for specified button
 * @param key   [in] ���õİ��� The key
 * @param onoff [in] 0 �������ỽ��ϵͳ, 1 �˰����ỽ��ϵͳ  0 The Key will not wake system, 1 The key will wake system 
 */
void KbWakeEnable(int key, int onoff);

/**
 * @brief ��ȡָ�������Ƿ��ܻ���ϵͳ
 * @brief Get the system wake up status for specified button
 * @param key [in] ����ֵ button
 * @retval 0 �˰������ỽ��ϵͳ 0 for the specified button will NOT wake system up
 * @retval 1 �˰����ỽ��ϵͳ 1 for the specified button will wake system up
 */
int IsKbWakeEnable(int key);

/**
 * @brief ����ص�
 * @brief Encrypted call back
 * @param p [in] ����
 */
typedef void (*KeyHitCallBack)(void* p);

/**
 * @brief ע��һ������ص�����
 * @brief Regist a Encrypted call back
 * @param keystr [in] ���� Encrypted string
 * @param cb [in] �ص�������ΪNULL��ʾע���˰��� Call back function, if NULL, write off the  Encrypted string
 * @param p [in] ����cbʱ����Ĳ��� parameter for running call back function
 * @retval 0 Success 0 for success
 * @retval <0: Fail <0 for fail
 */
int SecretKeyRegister(char *keystr, KeyHitCallBack cb, void *p);

/** @} keyboard */


/**
 * @defgroup scan scan
 * @brief Scanning opreation related interface
 * @brief ɨ�������ؽӿ�
 * @{
 */

//=============================================================
// #include "bwscan.h"
//=============================================================
#define SCANBAR_RLED    (0x01) ///< ��� (RED LED)
#define SCANBAR_WLED    (0x02) ///< �׹⣬Ҳ�в��� (WRITE LED)

/**
 * @brief ScanBar parameter
 */
typedef struct {
    int power_mode; ///< 0 - Abort after success, 1 - Suspend after success
    int scan_mode;  ///< refer BARSCAN_MODE_VALUE_E, Scan mode
    int feature;    ///< refer BARSCAN_FEATURE_CONFIGURE_E, Scan feature config
} scanbar_param_t;

/**
 * @brief Set scan bar parameter
 * @param param [in] the parameter
 * @note After set, the param will take effect immediately till power off
 */
void ScanBarSetParam(scanbar_param_t *param);

/**
 * @brief �����豸��ʼɨ��
 * @brief Start the device and scanning
 * @retval  0 ɨ���豸�����ɹ� 0 for start device success
 * @retval -1 ɨ���豸����ʧ�ܻ���ɨ���豸 -1 for start device fail or no scanning device
 * @pre None
 */
int ScanBarStart(void);

/**
 * @brief Turn on/off the scan success notice tone
 * @note Notice tone is default ON after device power on
 * @param onoff [in] 0-OFF, 1-ON
 */
void ScanBarEnableNoticeTone(int onoff);

/**
 * @brief �����豸��ʼɨ�룬 ����������
 * @brief Start the device and scanning, none-blocking mode
 * @param [out] pdata ���ɨ��ɹ��� ���ɨ���� if scan success, output scan result
 * @param [in] buf_sz Ӧ��ɨ�����ݻ�������С application scanning buffer size
 * @param [in] tov_ms ��ʱʱ�� timeout time
 * @retval >=0: ɨ��ʵ�����ݳ��� return value >=0: length of data scanned
 * @retval <0 ɨ��ʧ�ܻ���ɨ���豸 return value <0: scan fail or no scanning device
 * @pre None
 */
int ScanBarGetData(unsigned char *pdata, int buf_sz, int tov_ms);

/**
 * @brief Pause scanning
 * @note Suspend the scanner
 * @retval =0 Success
 * @retval <0: Fail or no scanner
 */
int ScanBarPause(void);

/**
 * @brief ��ֹɨ��
 * @brief Stop scanning
 * @note Power off the scanner
 * @retval =0 ɨ����ֹ�ɹ� return value = 0: stop scanning success
 * @retval <0 ɨ����ֹʧ�ܻ���ɨ���豸 return value <0: stop scanning fail or no scanning device
 * @pre None
 */
int ScanBarStop(void);

/**
 * @brief ���ú��Ͳ��⣬ Ĭ�ϴ򿪺�⡢ �رղ���
 * @brief Setup RED LED and WHITE LED. RED LED ON and WHITH LED OFF for default
 * @param [in] conf_param 
 *              SCANBAR_RLED ��� (RED LED)
 *              SCANBAR_WLED ���� (WHITE LED)
 * @param [in] onoff
 *              1 �� ON
 *              0 �ر� OFF
 *
 * @retval =0 Success return value = 0: success
 * @retval <0: Fail return value < 0: fail
 * @pre None
 */
int ScanBarLightSet(unsigned int conf_param, unsigned int onoff);

/** @} scan */


/**
 * @defgroup system system
 * @brief System operation related interface
 * @brief ϵͳ������ؽӿ�
 * @{
 */

/**
 * @defgroup bwsys bwsys
 * @brief BW System related interfaces
 * @brief ϵͳ������ؽӿ�
 * @{
 */

//=============================================================
//#include "bwsys.h"
//=============================================================

/**
 * @brief System time
 * @brief ϵͳʱ��
 */
typedef struct {
    unsigned short year;    ///< ��2000 ~ 2049
    unsigned short mon;        ///< ��1 - 12
    unsigned short day;        ///< ��1 - 31
    unsigned short hour;    ///< ʱ0 - 23
    unsigned short min;        ///< ��0 - 59
    unsigned short sec;        ///< ��0 - 59
    unsigned short wday;    ///< ����0 - 6 (week days, from 0 to 6)
} tsSysTime;

/**
 * @brief Sleep Level
 */
typedef enum {
    SLEEP_LEVEL_NOSLEEP = 0, ///< No sleep, screen will not auto turn off
    SLEEP_LEVEL_SYSTEM = 1, ///< Screen auto turn off after timeout, system will enter sleep after screen off.
    SLEEP_LEVEL_DEEP = 2, ///< Screen auto turn off after timeout, subsystem (eg: WIFI) will enter lowpower mode after deep sleep timeout.

    SLEEP_LEVEL_UNINITED = 3 ///< Sleep level has not been set.
} sleep_level_t;

/**
 * @brief ������������ʱ���callback
 * @brief Call back function for reset sleeping time
 * @retval tickcnt ��ǰϵͳ���ļ���ֵ����1ms/tick��
 * @pre None
 */
typedef void (*reset_sleep_timer_cb)(void);

/**
 * @brief �ϱ��¼�callback
 * @brief Call back function for notification
 * @param id [in] ֪ͨ���¼�ID event ID
 * @param pData [in] ֪ͨ���� event information
 * @param dataLen [in] ֪ͨ���ݵĳ��� event information length
 */
typedef void (*class_notify_cb)(WORD id, void *pData, DWORD dataLen);

/**
 * @brief ��Դ�������¼�callback
 * @brief Call back function for long pressing power button
 * @param p [in] ���� parameter
 */
typedef void (*pwrkey_long_press_callback)(void *p);


/**
 * @brief Tamper detect call back prototype
 * @param p [in] (parameter)
 */
typedef void (*tamper_callback)(void* p);

/**
 * @brief Unlock call back prototype
 * @param p [in] (parameter)
 */
typedef void (*unlock_callback)(void* p);

/**
 * ������Ч�ͻ����ص�.
 */
typedef void (*invalid_customer_callback)(void* p);

/**
 * @brief tamper event callback register
 * @param cb [in] callback for tamper
 * @param param [in] paramter for callback
 */
int RegisterTamperCallback(tamper_callback cb, void* param);

/**
 * @brief unlock callback register
 * @param cb [in] callback for unlock
 * @param param [in] paramter for callback
 */
int RegisterUnlockCallback(unlock_callback cb, void* param);


/**
 * @brief ע��ָ�����ϱ��¼���callback
 * @brief Regist call back function for event from specified class
 * @param cls [in] ֪ͨ���¼��� specified class
 * @param cb [in] �¼���Ӧ��callback (call back function related event)
 */
void RegSysClassNotify(WORD cls, class_notify_cb cb);

/**
 * @brief ע���Դ��������callback����
 * @brief Regist call back function for long pressing power button
 * @param cb [in] callback
 * @param param [in] cbʹ�õĲ��� parameter for call back function
 */
void RegisterPowerKeyLongPressCallback(pwrkey_long_press_callback cb,void * param);

/**
 * @brief ��ȡ�豸�ӿ�������ǰ��������ϵͳ���ļ���ֵ
 * @brief Get system tick count from power on to current
 * @retval tickcnt ��ǰϵͳ���ļ���ֵ����1ms/tick�� return value: tick count
 * @pre None
 */
unsigned int GetSysTickCount(void);

/**
 * @brief ��ȡ��ص�����Ϣ�� �Ա��ж��Ƿ���Լ�������
 * @brief Get battery status, in order to check whether devicec can continue transaction or not
 * @retval  0 - ������,���ܽ��ף�1 - ��������,���Խ��� 0 for low battery, can not continue transaction. 1 for battery normal, can continue transaction.
 * @pre None
 */
int GetSysbatteryState(void);

/**
 * @brief ���ñ���ʱ��
 * @brief Setup system local time
 * @param time [in] �������õ�ϵͳʱ������� system time want to set to
 * @retval 0 Success return 0: success
 * @retval <0: Fail return <0: fail
 * @pre None
 */
int SetSysLocalTime(tsSysTime *time);

/**
 * @brief ��ȡ����ʱ��
 * @brief Get system local time
 * @param time [out] ��ȡ��ϵͳʱ�������  system time got
 * @retval 0 Success return 0: success
 * @retval <0: Fail return <0: fail
 * @pre None
 */
int GetSysLocalTime(tsSysTime *time);

/**
 * @brief ��ȡϵͳ��Ϣ
 * @brief Get system information
 * @param info [out] ��ȡ��ϵͳ��Ϣ system information got
 * @param flag [in] ��Ϣ��� 0-ismi, 1-ccid, 2-imei, 3-version (information type)
 * @retval 0 Success return 0: success
 * @retval <0: Fail return <0: fail
 * @pre None
 */
int GetSysInfo(char *info, int flag);

/**
 * @brief ��ȡϵͳ����״̬
 * @brief Get system sleeping status
 * @retval 0 ϵͳ�Ѵ�������״̬ return 0: system sleeping
 * @retval 1 ϵͳ���ڷ�����״̬ return 1: system NOT sleeping
 * @pre None
 */
int GetSysStatus(void);

/**
 * @brief ϵͳ�Ƿ����ڳ��
 * @brief Get system charging status
 * @retval 0 δ��� return 0: NOT charging
 * @retval 1 ����� return 1: charging
 */
int IsCharging(void);

/**
 * @brief Check if the charger existing
 * @retval 0 Charger not exist
 * @retval 1 Charger exist
 */
int IsChargerExist(void);

/**
 * @brief Check if the main battery existing
 * @retval 0 Battery not exist
 * @retval 1 Battery exist
 */
int IsBatteryExist(void);

/**
 * @brief Get main battery voltage in mV
 * @retval The main battery voltage
 */
unsigned int GetBatteryVoltage(void);

/**
 * @brief Get main battery tempreature in degrees Celsius
 * @retval The main battery voltage (-5 to 50)
 */
int GetBatteryTemp(void);

/**
 * @brief Get main battery capacity percentage which estimate from voltage
 * @retval The main battery capacity percentage 
 */
unsigned int GetBatteryPercent(void);

/**
 * @brief Set device sleep level
 * @param sleep_level [in] SLEEP_LEVEL_NOSLEEP/SLEEP_LEVEL_SYSTEM/SLEEP_LEVEL_DEEP
 */
void SetSysSleepLevel(sleep_level_t sleep_level);

/**
 * @brief Get system sleep level
 */
sleep_level_t GetSysSleepLevel(void);

/**
 * @brief ����ϵͳ�����ȴ�ʱ��, ϵͳĬ���޲���ָ�������������
 * @brief Setup system waiting time, will sleep after a none-operation of user specified second
 * @param tsec [in] ����, ��С10�� (seconds, minimum 10 second)
 * @retval None no return value
 * @pre None
 */
void SetSysSleepTime(int tsec);

/**
 * @brief Set system timeout to deep sleep
 * @param tsec [in] timeout seconds, allow 5 to 3600 seconds.
 * @note Device enter into deep sleep only when sleep mode is set to level2.
 */
void SetSysDeepSleepTimeout(int tsec);

/**
 * @brief ϵͳ�����ȴ�ʱ�����ÿ�ʼ����
 * @brief System sleeping timer restart
 * @retval None no return value
 * @pre None
 */
void ResetSysSleepTimer(void);

/**
 * @brief �ȴ�ָ��ʱ��
 * @brief Delay specified ms
 * @param ms [in] ������ (ms)
 * @retval None no return value
 * @pre None
 */
void DelayMs(unsigned int ms);

/**
 * @brief ������UI������߳̾��
 * @brief Setup UI thread handles
 * @param hThread [in] ������UI������߳̾�� UI thread handles
 */
void SetMainUIThread(HANDLE hThread);

/**
 * @brief ��ȡ��UI������߳̾��
 * @brief Get UI thread handles
 * @retval NULL û��������UI�߳� return NULL: no UI thread been setup
 * @retval ��UI�߳� return: UI thread
 */
HANDLE GetMainUIThread(void);

/**
 * @brief ��ͣ��UI�߳�
 * @brief UI thread pause
 */
void SuspendMainUI(void);

/**
 * @brief �ָ���UI�߳�
 * @brief UI thread resume
 */
void ResumeMainUI(void);

/**
 * @brief Check compatable of Mercury Lib version and Platform version
 * @retval 0 Platform version is equal to Mercury lib version
 * @retval >0 Platform version is higher than Mercury lib version
 * @retval <0 Platform version is lower than Mercury lib version
 * @note if platform version is lower, application may be unstable.
 */
int BWSDK_PlatformCompatCheck(void);

/**
 * @brief ϵͳ��ģ��ĳ�ʼ��
 * @brief System blocks initialize
 *  ������Ӧ�ó���һ��ʼ����һ�� (Only run once when application start)
 */
int BWSDK_Init(void);

/**
 * @brief ϵͳ��ģ��ĳ�ʼ��(���ư汾)
 * @brief System blocks initialize(for customize version)
 * @note ������Ӧ�ó���һ��ʼ����һ�� (Only run once when application start)
 * @note ������BWSDK_Init�ظ����� (Can not be used with "BWSDK Init")
 * @param cb1 [in] ����ʱ�Ļص����� Call back function when triggered
 * @param p1 [in] cb1�Ĳ��� Parameter for call back function #1
 * @param cb2 [in] �����豸�Ļص����� Call back function when unlock device
 * @param p2 [in] cb2�Ĳ��� Parameter for call back function #2
 */
int BWSDK_Init_OEM(tamper_callback cb1, void*p1, unlock_callback cb2, void *p2);

/**
 * @brief ϵͳ��ģ��ĳ�ʼ��(���ư汾)
 * @note ������Ӧ�ó���һ��ʼ����һ��
 * @note ������BWSDK_Init�ظ�����
 * @param cb1 [in] ����ʱ�Ļص�����
 * @param p1 [in] cb1�Ĳ���
 * @param cb2 [in] �����豸�Ļص�����
 * @param p2 [in] cb2�Ĳ���
 * @param cb3 [in] ��Ч�ͻ��汾�Ļص�����
 * @param p3 [in] cb3�Ĳ���
 */
int BWSDK_Init_Ex(tamper_callback cb1, void*p1, unlock_callback cb2, void *p2, invalid_customer_callback cb3, void*p3);

/**
 * @brief Get system platform version
 * @retval platform version (Binary code), example 0x00010901 is V1.9.1
 */
unsigned int GetMercuryPlatformVer(void);

/**
 * @brief Get the system lib version
 * @retval string of syslib version
 */
char* BWSDK_GetSysLibVersion(void);

/**
 * @brief ��ȡBWSDK�汾�ţ���01.00.01
 * @brief Get BWSDK version number
 * @param maj �汾�Ÿ�λ high part of version number
 * @param mid �汾����λ middle part of version number
 * @param min �汾�ŵ�λ low part of version number
 * @retval �汾���ַ����������ͷ� return value: version number string, no need to free
 */
char *BWSDK_GetVersion(unsigned char *maj, unsigned char *mid, unsigned char *min);

/**
 * @brief All image type supported
 */
typedef enum
{
    BWIMG_TYPE_MAIN_APP = 0,    ///< Image type of main APP
    BWIMG_TYPE_SP_FW = 1,       ///< Image type of SP firmware

    BWIMG_TYPE_MAX
} bwimg_type;

/**
 * @brief signature verify
 * @param img_type [in] type of image
 * @param img_path [in] image file path
 * @retval 0 signature verify pass
 * @retval !0 signature verify fail
 */
int bwimage_signature_verify(bwimg_type img_type, const char *img_path);


/**
 * @brief ע����Ч�ͻ����ص�
 * @param cb [in] ����ʱ�Ļص�����
 * @param p [in] cb�Ĳ���
 */
void RegisterInvalidCustomerCallback(invalid_customer_callback cb, void* p);

/**
 * @brief ��Ч�ͻ��汾ʱͨ�������������
 * @param password [in] ����
 * @retval ��������� 0 -- �����ɹ��� 1 -- ����ʧ��
 */
int Security_LocalUnlockByInvalidCustomer(const char* password);

/**
 * @brief ���ؼ򵥽���
 * @retval ��������� 0 -- �����ɹ��� 1 -- ����ʧ��
 */
int Security_LocalUnlockByDeviceTampered(void);

/**
 * @brief ��Ч�ͻ���Զ�̽���
 * @retval ��������� 0 -- �����ɹ��� 1 -- ����ʧ��
 */
int Security_RemoteUnlockByInvalidCustomer(void);
 
/**
 * @brief �豸����Զ�̽���
 * @param sensor_result [out] ����ʧ�ܺ�sensor����ֵ
 * @param sensor_result_len [in] sensor_result����
 * @retval ��������� 0 -- �����ɹ��� 1 -- ����ʧ��
 */ 
int Security_RemoteUnlockByDeviceTempered(char* sensor_result, int sensor_result_len);

/**
 * @brief ��Ч����Ӧ��Զ�̽���
 * @retval ��������� 0 -- �����ɹ��� 1 -- ����ʧ��
 */
int Security_RemoteUnlockInvalidApp(void);


/** @} bwsys */


/**
 * @defgroup sysmisc sysmisc
 * @brief System misc related interfaces
 * @brief ϵͳ������ؽӿ�
 * @{
 */

/**
 * @brief audio policy
 */
typedef enum {
    AUDIO_PREFER_POLICY_TTS = 0, ///< TTS first
    AUDIO_PREFER_POLICY_DTMF = 1, ///< DTMF first
    AUDIO_PREFER_POLICY_SINGLE_TONE = 2 //SingleTone first.
} audio_prefer_policy_t;

/**
 * @brief Set audio preference policy
 * @param policy [in] refer to audio_prefer_policy_t
 */
void AudioSetPreferPolicy(audio_prefer_policy_t policy);

/**
 * @brief Set audio volume level
 * @param volume [in] volume level from 1 to 9
 * @param nvstore [in] 0-Do not store this config to NV��1-Store this config to NV
 * @retval 0 Success
 * @retval <0: Fail
 */
int AudioSetVolumeOEM(unsigned int volume, unsigned int nvstore);

/**
 * @brief Get the TTS volume level stored in NV
 * @retval TTS Volume, 0-9, 0 means muted.
 */
unsigned short GetTtsVolNV(void);

/**
 * @brief Get contry code in NV
 * @retval contry code, eg: "US", "CN"
 */
char* GetCountryCodeNV(void);

/**
 * @brief Set contry code in NV
 * @param code [in] contry code, eg: "CN" means CHINA.
 */
void SetCountryCodeNV(const char *code);

/**
 * @brief Get langage code in NV
 * @retval langage code, eg: "en", "zh"
 */
char* GetLangCodeNV(void);

/**
 * @brief Set langage code in NV
 * @param code [in] langage code, eg: "en" means English. 
 */
void SetLangCodeNV(const char *code);

/**
 * @brief Set DTMF volume
 * @param volume [in] volume from 0 to 65535
 * @param nvstore [in] 0-Do not store this config to NV, 1-Store this config to NV
 * @retval 0 Success
 * @retval <0: Fail
 */
int DtmfSetVolumeOEM(unsigned int volume, unsigned int nvstore);

/**
 * @brief ����SingleTone����
 * @param volume [in] ����0-65535
 * @param nvstore [in] 0-�����浽NV��1-���浽NV
 * @retval 0 Success
 * @retval <0 Fail
 */
int SingleToneSetVolumeOEM(unsigned int volume, unsigned int nvstore);

/**
 * @brief Abort DTMF sound, mutex mode
 */
void AudioDtmfAbort_OEM(void);

/**
 * @brief Play DTMF sound, mutex mode
 * @param tone [in] DTMF tone, refer to MERCURY_DTMF_TONE_ID_E
 * @param time_100ms [in] time, unit: 100 millisecond)
 */
int AudioDtmfPlay_OEM(MERCURY_DTMF_TONE_ID_E tone, BYTE time_100ms);

/**
 * @brief Play DTMF sound, mutex mode
 * @param tone [in] DTMF tone, refer to MERCURY_DTMF_TONE_ID_E
 * @param time_100ms [in] time, unit: 100 millisecond)
 * @param blocked [in] 0-Not block while playing, 1-Block while playing
 */
int AudioDtmfPlay_OEM1(MERCURY_DTMF_TONE_ID_E tone, BYTE time_100ms, int blocked);

/**
 * @brief ��ֹ��������(���ⷽʽ)
 */
void AudioSingleToneAbort_OEM(void);

/**
 * @brief ���ŵ���(���ⷽʽ)
 * @note DTMF���޷�������ڲ��ŵ�TTS��
 */
int AudioSingleTonePlay_OEM(unsigned int  freq, BYTE time_100ms);

/**
 * @brief ����DTMF��(���ⷽʽ)
 * @note DTMF���޷�������ڲ��ŵ�TTS��
 */
int AudioSingleTonePlay_OEM1(unsigned int freq, BYTE time_100ms, int blocked);

/**
 * @brief Abort TTS sound, mutex mode
 */
int TTS_Abort_OEM(void);

/**
 * @brief ����TTS��(���ⷽʽ)
 * @brief Play TTS sound, mutex mode
 * @param text [in] Ҫ���ŵ������ַ���(text string to play)
 * @param len [in] �����ַ����ĳ��� (length of text string to play)
 */
int TTS_PlayText_OEM(const uint8 * text,int len);

/**
 * @brief �ȵ�TTS��Ƶ������ɻ�ֱ����ʱ
 * @brief Wait for TTS playing finish or timeout
 * @param timeout_ms [in] ��ȴ�ʱ��(Maximum waiting time)
 */
void WaitTtsComplete(int timeout_ms);

/**
 * @brief Wait until DTMF tone complete or timeout
 * @param timeout_ms [in] Max waiting time
 */
void WaitDtmfComplete(int timeout_ms);

/**
 * @brief �ȴ�������Ƶ������ɻ�ֱ����ʱ
 * @param timeout_ms [in] ��ȴ�ʱ��
 */
void WaitSingleToneComplete(int timeout_ms);

/** @} sysmisc */

/**
 * @defgroup sn sn
 * @brief SN operation related interface
 * @brief SN������ؽӿ�
 * @{
 */
//=============================================================
//#include "bwsn.h"
//=============================================================

#define SN_SIZE_MAX  (64)   ///< SN��󳤶�

/**
 * @brief ��ȡAPģ���ΨһID
 * @brief Get the unique ID of AP module
 * AC35ģ���ΨһID: MercuryID(Unique ID in AC35 module: Mercury ID)
 * @param snData [out] ���к�����, ��������С����С��19�ֽ� Serial number data, buffer size no less than 19 bytes
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetAPSN(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡ�ɵ�PCB-SN��
 * @brief Get old PCB-SN number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetPSN_Prev(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡPCB-SN��
 * @brief Get new PCB-SB number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetPSN(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡ�ɵ�����SN��
 * @brief Get old Device SN number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetDSN_Prev(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡ����SN��(=TUSN)
 * @brief Get device SN number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetDSN(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡ�ɵ�����KSN��
 * @brief Get old device KSN number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetKSN_Prev(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡ�ͻ�SN��(=DSN2)
 * @brief Get customer SN number
 * @param snData [out] ���к����� Serial number data
 * @param len [in] ���к����ݳ��� length of serial number data
 * @retval 0 Success return 0 for success
 * @retval -1 Fail return -1 for fail
 */
int GetKSN(unsigned char *snData, unsigned int len);

/**
 * @brief ��ȡNV�д洢�ķ���ģʽ״̬
 * @brief Get flight mode status stored in NV
 * @retval 0 OnlineMode 
 * @retval 1 FlightMode
 */
int GetFlightModeNV(void);

/**
 * @brief ����NV�д洢�ķ���ģʽ״̬
 * @brief Setup flight mode status stored in NV
 * @param mode [in] 0 OnlineMode, 1 FlightMode
 * @retval 1 FlightMode
 */
void SetFlightModeNV(int mode);

/**
 * @brief ��ȡNV�д洢����Ļ��������
 * @brief Get screen brightness stored in NV
 * @retval ϵͳ��Ļ���� return system screen brightness
 */
unsigned short GetLcdBacklightNV(void);

/**
 * @brief ����NV�д洢����Ļ��������
 * @brief Setup screen brightness stored in NV
 * @param level [in] ��Ļ�������� screen background brightness
 */
void SetLcdBacklightNV(unsigned short level);


/**
 * @brief ��ȡNV�д洢�Ŀͻ���
 * @brief Get customer name stored in NV
 * @param [out] name: �ͻ��������ᳬ��64�ַ������ûд���򷵻ص��ַ�������Ϊ0. customer name, no more than 64 bytes
 * @param [in] len: name�����ߴ磬��λ: �ֽ� maximum length of name, unit: byte
 */
void GetCustomerName(char *name, int len);


/**
 * @brief ��ȡNV�д洢���ӿͻ���
 * @brief Get sub-customer name stored in NV
 * @param [out] name: �ͻ��������ᳬ��64�ַ������ûд���򷵻ص��ַ�������Ϊ0. customer name, no more than 64 bytes. If not written before, will return 0
 * @param [in]  len: name�����ߴ磬��λ: �ֽ� maximum length fo name, unit: byte
 */
void GetSubCustomerName(char *name, int len);

/**
 * @brief Hardware infomation of device
 */
typedef struct {
    unsigned char hw_version[32];   ///< Ӳ���汾
    unsigned char is_spt_gprs;      ///< GPRS
    unsigned char is_spt_wifi;      ///< WIFI
    unsigned char is_spt_bt;        ///< ����
    unsigned char is_spt_printer;   ///< ��ӡ��
    unsigned char is_spt_gm;        ///< ����
    unsigned char is_spt_nfc;       ///< �ǽ�
    unsigned char is_spt_hid;       ///< HID
    unsigned char is_spt_rs232;     ///< RS232����
    unsigned char is_spt_sensor_kb; ///< sensor��������
    unsigned char is_spt_k_type_pa; ///< K�๦��
    unsigned char is_spt_ext_3g;    ///< ����3G
    unsigned char is_hw_nfc_led;    ///< Ӳ��LED
    unsigned char is_hw_beeper;     ///< Ӳ��������
    unsigned char msr_track_mask;   ///< �ŵ���Ч�����룬 bit[0]:�ŵ�1��bit[1]:�ŵ�2, bit[2]:�ŵ�3
    unsigned char sim_cnt;          ///< Number of SIM Slot, 0 - None, 1 - One SIM Slot, 2 - Two SIM Slot
    unsigned char sam_cnt;          ///< Number of SAM Slot, 0 - None, 1 - One SAM Slot, 2 - Two SAM Slot    
    unsigned char sam_drv;          ///< Driver IC of SAM.
    unsigned char is_spt_camera;    ///< Camera.
    unsigned char is_spt_camera_lamp; ///< ɨ���ɫ�����.
    unsigned char is_spt_charging_led; ///< ���ָʾ��
    unsigned char is_no_sp_sensor;    ///< ��sensor����
    unsigned char is_no_sp_battery_check;///< ��spС��ص�ѹ���
} tsDeviceHwInfo;

/**
 * @brief ��ȡӲ��������Ϣ
 * @brief Get hardware information
 * @param hwInfo [out] Hardware information Ӳ��������Ϣ
 * @retval  0: Success  �ɹ�
 * @retval  !0: Fail    ʧ��
 */
int GetDeviceHwInfo(tsDeviceHwInfo* hwInfo);

/**
 * @brief Check if the device is 3G configuration
 * @retval 0 2G Product
 * @retval 1 3G Product
 */
int BWSDK_Is3GProduct(void);

/**
 * @brief Check if specific MSR track is support
 * @param trackid [in] Track ID, 1/2/3 means track1/2/3
 * @retval 0 Track is supported
 * @retval 1 Track is unsupported
 */
int BWSDK_IsMsrTrackSupport(int trackid);

/**
 * @brief Check if the device have Hardware NFC-LED
 * @retval 0 Hardware NFC-LED not exist
 * @retval 1 Hardware NFC-LED exist
 */
int BWSDK_IsHwNfcLedExist(void);

/**
 * @brief Check if the device have Hardware Beeper
 * @retval 0 Hardware Beeper not exist
 * @retval 1 Hardware Beeper exist
 */
int BWSDK_IsHwBeeperExist(void);

/**
 * @brief Check if the device supports esim.
 * @return 0 eSIM not exist
 * @return 1 eSIM exist
 */
int BWSDK_IseSimExists(void);

/**
 * @brief ���STK refresh״̬��ʶ
 * @retval None
 */
void BWSTK_ResetRefreshState(void);

/**
 * @brief ��ȡSTK�Ƿ��Ѹ���
 * @retval 0 -- δ����
 * @retval 1 -- �Ѹ���
 */
int BWSTK_IsRefreshed(void);

/** @} sysmisc */


/**
 * @defgroup usb_at usb_at
 * @brief USB serial port operation related interface
 * @brief usb���ڲ�����ؽӿ�
 * @{
 */
//=============================================================
//#include "bwusbat.h"
//=============================================================
/**
 * @brief USBAT�����ʼ��
 * @brief USBAT command initialize
 */
void USBAT_Init(void);

/**
 * @brief USBAT����ȥ��ʼ��
 * @brief USBAT command deinitialize
 */
void USBAT_Deinit(void);

/**
 * @brief �������ݵ�USBAT�ӿ�
 * @brief Send data to USBAT port
 * @param buff [in] Ҫ���͵����� data to send
 * @param len [in] Ҫ���͵����ݳ��� length of data to send
 */
void USBATSend(BYTE *buff, UINT len);

/**
 * @brief ��USBAT�ӿڻ�ȡ����
 * @brief Get data from USBAT port
 * @param buff [in] ���ջ����� data receiving buffer
 * @param len [in] Ҫ���յ�����ֽ��� maximum length of receiving
 * @param timeout_ms [in] ��ʱʱ�䣬��λ:���� time out in ms
 */
INT USBATGet(BYTE *buff, UINT len, ULONG timeout_ms);

//=============================================================
//#include "bwqcmd.h"
//=============================================================
#define CMD_ERROR_STX_INEXISTENCE (-1) 	///< ����ͷ����
#define CMD_ERROR_BUFFER_OVERFLOW (-2)	///< �������
#define CMD_ERROR_TIMEOUT         (-3)	///< ��ʱ

/** @brief ֧�ֵ�����˿� **/
/** @brief Supported output port **/
typedef enum {
    PORT_USBAT = 0UL,  ///< AT�� AT port
    PORT_UNKNOWN       ///< δ֪�� Unknow port
} hw_port_type;

/**
 * @brief ��ʼ��
 * @brief Initialize
 * @param [in] port: @see:: hw_port_type
 */
void QCMD_Init(hw_port_type port);

/**
 * @brief ȥ��ʼ��
 * @brief Deinitialize
 */
void QCMD_Deinit(void);

/**
 * @brief �Ӷ˿ڻ�ȡ����
 * @brief Get data from port
 * @param [out] buff:    Datas read from port
 * @param [in]  len:     Length of data to read
 * @param [in]  timeout: Ms of timeout to read
 * @retval  >0: Success, Length of data read from port
 * @retval  <=0: Fail
 */
INT QCMD_Get(BYTE *buff, UINT len, ULONG timeout);

/**
 * @brief �Ӷ˿ڷ�������
 * @brief Send data from port
 * @param [in] buff:    Datas send to port
 * @param [in] len:     Length of data to send
 * @retval  none
 */
void QCMD_Send(void *buff, unsigned int len);

/**
 * @brief ��ȡ����
 * @brief Get command
 * @param [out] buff:       Command read from port
 * @param [in]  maxbufsize: Size of command buffer.
 * @retval  >0: Success, Length of command
 * @retval  <0: Fail
 */
INT QCMD_GetCmdData(BYTE *buff, UINT maxbufsize);

/**
 * @brief ��ȡ��־����
 * @brief Get flag size
 * @return Size of configure flag
 */
ULONG QCMD_GetCfgFlagSize(void);

/**
 * @brief ����豸��������
 * @brief Check the code is a device configuration command or not
 * @param [in] code:     The code
 * @param [in] code_len: Length of code
 * @retval <0: The code is not a device configuration command  �����豸��������
 * @retval 0: The code is a device configuration command  ���豸��������
 */
INT QCMD_IsCfgFlag(char *code, ULONG code_len);

/**
 * @brief ��ȡ�豸������Ϣ
 * @brief Get Device configuration information
 * @param [in]  code:         The code
 * @param [in]  code_len:     Length of code
 * @param [out] cfg_info:     The configure information
 * @param [out] cfg_info_len: Length of configure information
 * @retval <0: The code is not a device configuration query command  ���ǻ�ȡ�豸��Ϣ����
 * @retval 0: The code is a device configuration query command  �ǻ�ȡ�豸��Ϣ����
 */
int QCMD_CmdToGetCfg(char *code, ULONG code_len, char *cfg_info, ULONG *cfg_info_len);


/**
 * @brief ����SN��
 * @brief Setup SN number
 * @param [in]  code:         The code
 * @param [in]  code_len:     Length of code
 * @retval <0: The code is not a SN setting command  ��������SN������
 * @retval 0: The code is a SN setting command  ������SN������
 */
INT QCMD_CmdToSetSN(char *code, ULONG code_len);

/**
 * @brief SDM Service start
 * @param port [in] serial port
 * @retval 0 Success
 * @retval <0: Fail
 */
int sdm_start(port_dev_t port);

/**
 * @brief SDM Service stop
 * @param port [in] serial port
 * @retval 0 Success
 * @retval <0: Fail
 */
int sdm_stop(port_dev_t port);

/**
 * @brief Check if the SDM is running
 * @param port [in] serial port
 * @retval 1 Running
 * @retval 0 Not running
 */
int sdm_isrunning(port_dev_t port);

/** @} usb at */

/** @} system */

/**
 * @defgroup net net
 * @brief Network operation related interface
 * @brief ���������ؽӿ�
 * @{
 */
// include "bwnet.h"
//����ͨ�Ŵ�����
//Network Communication Error code
#define NET_ERR_NOSUPPORT		(-5000)			///<�޶��� Not support 
#define NET_ERR_PARAMETER 		(-5001)			///<�������� Parameter error
#define NET_ERR_TIMEOUT 		(-5002)			///<���糬ʱ Net timeout
#define NET_ERR_DISCON 			(-5003)			///<���ӶϿ� Disconnect
#define NET_ERR_SOCKETCREATE 	(-5004)			///<socket����ʧ�� Socket create fail
#define NET_ERR_SOCKETCON 		(-5005)			///<socket����ʧ�� Socket connect fail
#define NET_ERR_NOPDP 			(-5006)			///<PDPʧ�� PDP fail
#define NET_ERR_OPENPDP 		(-5007)			///<��PDPʧ�� Open PDP fail
#define NET_ERR_SETAPN 			(-5008)			///<����APNʧ�� APN setup fail
#define NET_ERR_CONMAX 			(-5009)			///<���ӳ������� Exceed Limit of connection
#define NET_ERR_NONET 			(-5010)			///<������ No network
#define NET_ERR_IP 				(-5011)			///<IP���� Wrong IP

#define NET_ERR_CONNECT_TIMEOUT     (-5012)     ///< Connect to AP timeout  ����AP��ʱ
#define NET_ERR_CONNECT_PASSWORD    (-5013)     ///< Password wrong for connect to AP  ����AP�������
#define NET_ERR_CONNECT_NOAP        (-5014)     ///< The AP to connect is not exist  ���ӵ�AP������
#define NET_ERR_CONNECT_UNKNOW      (-5015)     ///< Unkonwn error while connect to AP  ����APδ֪����
#define NET_ERR_CONNECT_CONNECTING  (-5016)     ///< AP connectting    ����AP��
#define NET_ERR_NO_READY            (-5017)     ///< Device not ready  �豸δ����

#define NET_ERR_SEND                (-5018)     ///< Transmitting error
#define NET_ERR_READ                (-5019)     ///< Receiving error
#define NET_ERR_ADDRINUSE 			(-5020)		///< Port busy �˿ڱ�ռ��

/**
 * @brief Supported Network device type
 * @brief ֧�ֵ������豸����
 */
typedef enum {
    NET_DEV_NONE,   ///< ���豸 no device
    NET_DEV_GPRS,   ///< GPRS���� GPRS network
    NET_DEV_WIFI,   ///< WLAN���� WLAN network
	NET_DEV_SERIAL, ///< ���� Serial port
    NET_DEV_3G,     ///<
    NET_DEV_NUM
} net_dev_t;

/**
 * @brief Supported type of socket connection
 */
typedef enum {
    NET_SOCKET_TYPE_TCP = 0, ///< TCP connection
    NET_SOCKET_TYPE_UDP = 1, ///< UDP connection
    NET_SOCKET_TYPE_MAX      ///<
} net_socket_type;

/**
 * @brief Supported event of net device
 */
typedef enum
{
    NETDEV_EVT_CONN_STATUS_GPRS = 0, ///< The event denote GPRS connection status change. 
    NETDEV_EVT_CONN_STATUS_WIFI = 1, ///< The event denote WLAN connection status change.
    NETDEV_EVT_GPRS_READY = 2,       ///< The event denote GPRS device is ready to open.
    NETDEV_EVT_3G_READY = 3,         ///< The event denote 3G device is ready.
    NETDEV_EVT_CONN_STATUS_3G = 4,   ///<
    NETDEV_EVT_MAX                   ///<
}netdev_evt_t;

/**
 * @brief GPRS device configuration
 * @brief GPRS�豸����
 */
typedef struct {
    net_dev_t devtype; ///< �����豸���� Network device type, @see:: net_dev_t
    char *apn;  ///< APN, ��"CMNET" APN. For example,"CMNET"
    char *user; ///< �����û���������ΪNULL. Dail username, can be NULL
    char *pass; ///< �������룬����ΪNULL. Dail password can be NULL
    gprs_pdp_type pdp_type; ///< ��������, Ĭ��Ϊ0. Dail type can be 0, @see:: gprs_pdp_type
} gprs_dev_param_t;

/**
 * @brief WLAN device configuration
 * @brief WLAN�豸����
 */
typedef struct {
    net_dev_t devtype; ///< �����豸���� Network device type, @see:: net_dev_t
    char *ssid; ///< AP������SSID. Access porint name
    char *pass; ///< AP���룬����ΪNULL. Access point password, can NOT be NULL
    char *mac;  ///< AP��MAC��ַ������ΪNULL Access point Mac address, can be NULL
} wlan_dev_param_t;

/**
 * @brief umts parameter
 * @brief umts ����
 */
typedef struct {
    net_dev_t devtype;  ///< Type of net device, @see:: net_dev_t
    char *apn;          ///< APN
    char *user;         ///< User name
    char *pass;         ///< Password
} umts_dev_param_t;

/**
 * @brief Network Device configuration
 * @brief �����豸����
 */
typedef union {
    net_dev_t devtype; ///< �����豸���� Network device type, @see:: net_dev_t
    gprs_dev_param_t gprs; ///< GPRS�豸���� GPRS device configuration, @see:: gprs_dev_param_t
    wlan_dev_param_t wlan; ///< WLAN�豸���� WLAN device configuration, @see:: wlan_dev_param_t
    umts_dev_param_t umts; ///< umts, @see:: umts_dev_param_t, @see:: umts_dev_param_t
} net_dev_param_t;

/**
 * @brief Network hardware configuration
 * @brief ����Ӳ������
 */
typedef struct {
    char *ipaddr;  ///< ����IP��ַ IP address
    char *mask;    ///< �������� Net mask
    char *gateway; ///< ����IP��ַ Gatway IP address
    char *dns;     ///< ���������� DNS address
    char *mac;     ///< ����MAC��ַ����WIFI��Ч Local Mac address, only valid for WIFI
    char *ap_ssid; ///< SSID, ��WIFI��Ч SSID only valid for WIFI
    char *ap_mac;  ///< ����MAC��ַ, ��WIFI��Ч Gateway Mac address, only valid for WIFI
    int  ap_rssi;  ///< �ź�ǿ��, ��WIFI��Ч RSSI value, only valid for WIFI
    unsigned char ap_ch;    ///< ͨ��, ��WIFI��Ч Channel, only valid for WIFI
    unsigned char station_dhcp_en; ///< station DHCP״̬, ��WIFI��Ч station DHCP status, only valid for WIFI
} net_dev_hwinfo_t;

/**
 * @brief GPRS hardware information
 */
struct netdev_gprs_info {
    net_dev_t devtype; ///< Type of net device, @see:: net_dev_t
    char *ipaddr;  ///< IP address
    char *mask;    ///< Subnet mask
    char *gateway; ///< Gatway IP address
    char *dns;     ///< DNS address
    int sim_state; ///< SIM state, 0 - SIM not ready, 1 - SIM ready
    int rssi;      ///< Signal strength
    char *imei;    ///< IMEI of Device
    char *imsi;    ///< IMSI of SIM card
    char *iccid;   ///< ICCID of SIM card
    char *eid;     ///< eSIM id.
};

/**
 * @brief WLAN module hardware information
 */
struct netdev_wlan_info {
    net_dev_t devtype; ///< Type of net device, @see:: net_dev_t
    char *ipaddr;  ///< IP address
    char *mask;    ///< Subnet mask
    char *gateway; ///< Gatway IP address
    char *dns;     ///< DNS address
    char *mac;     ///< Local Mac address, only valid for WIFI
    char *ap_ssid; ///< SSID, only valid for WIFI
    char *ap_mac;  ///< Gateway Mac address, only valid for WIFI
    int  rssi;     ///< Signal strength
    unsigned char ap_ch;           ///< Channel, only valid for WIFI
    unsigned char station_dhcp_en; ///< station DHCP status, only valid for WIFI
};

/**
 * @brief 3G module hardware information
 */
struct netdev_3g_info {
    net_dev_t devtype; ///< Type of net device, @see:: net_dev_t
    char *ipaddr;  ///< IP address
    char *mask;    ///< Subnet mask
    char *gateway; ///< Gatway IP address
    char *dns;     ///< DNS address
    int sim_state; ///< SIM state, 0 - SIM not ready, 1 - SIM ready
    int  rssi;     ///< Signal strength
    char *imei;    ///< IMEI of Device
    char *imsi;    ///< IMSI of SIM card
    char *iccid;   ///< ICCID of SIM card
};

/**
 * @brief Network device hardware extra information
 */
typedef union {
    net_dev_t devtype; ///< Type of net device, @see:: net_dev_t
    struct netdev_gprs_info gprs; ///< gprs, @see:: netdev_gprs_info
    struct netdev_wlan_info wlan; ///< wlan, @see:: netdev_wlan_info
    struct netdev_3g_info umts;   ///< umts, @see:: netdev_3g_info
} net_dev_hwinfo_ex_t;

/**
 * @brief Net device LBS info
 */
typedef struct _lbs_info {
    int mcc; ///< Mobile Country Code
    int mnc; ///< Mobile Network Code
    int lac; ///< Location Area Code
    int cid; ///< Cell ID
} net_dev_lbs_info;

/**
 * @brief SIM card ID
 */
typedef enum _sim_id_t {
    SIM_ID_1 = 0U, ///< SIM1
    SIM_ID_2 = 1U, ///< SIM2

    SIM_ID_MAX = 2U, ///<
    SIM_ID_INVALID = 0x7FFFFFFF ///< INVALID SIM
} sim_id_t;

/**
 * @brief Get number of SIM slot supported
 * @retval 0 Not support SIM card
 * @retval 1 Suport Only 1 SIM card
 * @retval 2 Suport 2 SIM cards
 */
int NetDeviceGetSIMCount(void);

/**
 * @brief Get current active SIM ID
 * @retval SIM_ID_0 SIM0 is actieve
 * @retval SIM_ID_1 SIM1 is actieve
 * @retval SIM_ID_INVALID No SIM active
 */
sim_id_t NetDeviceGetActiveSIM(void);

/**
 * @brief Active specific SIM slot
 * @param sim [in] SIM ID
 * @param reset [in] 0-Hot switch, 1-Reset modem, 2-System reset
 * @retval 0 Success
 * @retval !0 Fail
 */
int NetDeviceActiveSIM(sim_id_t sim, int reset);

/**
 * @brief ��ȡ��ǰ���ڼ���״̬���豸ID
 * @brief Get current activated device ID
 * @retval NET_DEV_NONE û���豸���ڼ���̬(No activated device ID)
 * @retval NET_DEV_GPRS GPRS���ڼ���̬ (GPRS activated)
 * @retval NET_DEV_WIFI WIFI���ڼ���̬ (WIFI activated)
 * @pre None
 */
net_dev_t NetDeviceGetActive(void);

/**
 * @brief ѡ�񼤻��ĸ��豸
 * @brief Choose to active device
 *  ͬһʱ�̽�����һ���豸��������(Only one device can connect to network at the same time)
 * @param [in] id: Ҫʹ�õ��豸��ţ�NET_DEX_XXX (Device ID)
 * @retval 0 Success return 0 for success
 * @retval <0 ������ retrun <0 for error code
 * @pre None
 */
int NetDeviceActive(net_dev_t id);

/**
 * @brief �򿪼����ͨѶ�豸
 * @brief Open activated communication device
 * @retval 0 �򿪳ɹ� return 0 for open success
 * @retval ��0 ��ʧ�� return !0 for open fail
 * @pre NetDeviceSetParameter
 */
int NetDeviceOpen(void);

/**
 * @brief Open specific communication device
 * @param id [in] NET_DEX_XXX (Device ID)
 * @retval 0 - open success
 * @retval !0 - open fail
 * @pre NetDeviceSetParameter
 */
int NetDeviceOpenEx(net_dev_t id);

/**
 * @brief �ر�ͨѶ�豸
 * @brief Close communication device
 * @retval 0 �رճɹ� return 0 for close success
 * @retval ��0 �ر�ʧ�� return !0 for close fail
 */
int NetDeviceClose(void);

/**
 * @brief Close specific communication device
 * @param id [in] NET_DEX_XXX (Device ID)
 * @retval 0 Close success
 * @retval !0 Close fail
 */
int NetDeviceCloseEx(net_dev_t id);

/**
 * @brief Get WLAN status
 * @retval 0 WLAN close
 * @retval 1 WLAN open
 */
int NetDeviceIsWLANEnable(void);

/**
 * @brief ��ȡ�豸��Ϣ��IP��ַ/����/DNS����Ϣ
 * @brief Get device information, IP/Net mask/DNS and etc
 * @param info [out] Ӳ����Ϣ hardware information
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return <0 for fail, error code
 */
int NetDeviceGetHwInfo(net_dev_hwinfo_t *info);

/**
 * @brief Get net device hardware info, IP/Subnet/DNS/Signal strength/SIM Status etc.
 * @param info [out] Base information, NULL means not need base infomation.
 * @param exinfo [out] Extra information, NULL means not need extra information
 * @retval 0 Success
 * @retval <0: Fail, error code
 */
int NetDeviceGetHwInfoEx(net_dev_hwinfo_t *info, net_dev_hwinfo_ex_t *exinfo);

/**
 * @brief ���õ�ǰ��豸����
 * @brief Setup current device configuration
 * @param param [in] Ҫ���õ��豸���� Device ID
 * @retval 0 Success return 0 for success
 * @retval <0 ������ return <0 for error code
 */
int NetDeviceSetParameter(net_dev_param_t *param);

/**
 * @brief Setup specific device configuration
 * @param param [in] parameters neet to set
 * @retval 0 Success
 * @retval <0 Error code
 */
int NetDeviceSetParameterEx(net_dev_param_t *param);

/**
 * @brief Get LBS info
 * @param dev [in] net device, NET_DEV_NONE means current active dev
 * @param info [out] LBS info, include mcc/mnc/lac/cid
 * @retval 0 Success
 * @retval <0 Error code
 */
int NetDeviceGetLBSInfo(net_dev_t dev, net_dev_lbs_info *info);

/**
 * @brief Get host of specific device
 * @param  [in]  domainName: host name
 * @param  [out] ipAddr: host IP
 * @retval 0 successful
 * @retval other fail.
 */
int NetDeviceGetHostByName(const char* domainName, char* ipAddr);


/**
 * @brief ��ȡ�����豸������״̬
 * @brief Get activated device network status
 * @retval 0 δ���� return 0 for not connected
 * @retval 1 ������ return 1 for connected
 * @retval <0 ���� return < 0 for error
 */
int NetDeviceGetConnectionStatus(void);

/**
 * @brief Flight Mode control
 * @param id [in] NET_DEV_GPRS or NET_DEV_3G
 * @param enable [in] 1: Enter flight mode, 0: Leave flight mode
 * @retval 0 Success
 * @retval !0 Fail
 */
int NetDeviceSetFlightMode(net_dev_t id, int enable);

/**
 * @brief Get specific net device connection status
 * @param id Net device ID
 * @retval 0 Not connected
 * @retval 1 Connected
 * @retval <0 Error code
 */
int NetDeviceGetConnectionStatusEx(net_dev_t id);

/**
 * @brief Get event of specific device
 * @param evt [in] the event need to get
 * @retval -1 Fail
 * @retval event handler
 */
HANDLE NetDeviceGetEvent(netdev_evt_t evt);

/**
 * @brief ����socket����
 * @brief Create socket connection
 * @param type [in] socket���ͣ�TCP����UDP Socket type(TCP of UDP)
 * @param remote_addr [in] Զ������IP��ַ (remote IP address)
 * @param  port [in] Զ�������˿� (Port number)
 * @param flag [in] Զ�˵�ַ���� (remote address type)
 * @retval ����0 ����socket�ɹ� return > 0 for success
 * @retval С��0 ����ʧ�� return <0 for fail
 */
int NetSocketConnect(net_socket_type type, char *remote_addr, unsigned short port, int flag);

/**
 * @brief �ȴ�socket���ӣ�ֱ���ɹ���ʱ
 * @brief Wait for socket connection, until success or timeout
 * @param ctx [in] socket context
 * @param timeout_ms [in] ��ʱʱ��, 0:��������, -1:�ȴ�ֱ������ timeout time
 * @retval 1 socket������ return 1 for socket alreay connected
 * @retval 0 socketδ���� return 0 for socket not connected
 */
int NetSocketWaitConnet(int ctx, int timeout_ms);

/**
 * @brief ����socket����
 * @brief Receiving socket data
 * @param ctx [in] socket context
 * @param recvbuf [out] ����socket���ݵĻ����� buffer for receiving socket data
 * @param len [in] Ԥ�ڽ��յ����ݳ��� expected data length
 * @retval ����0 ���ճɹ� return > 0 for receive success
 * @retval С��0 ����ʧ�� return < 0 for receive fail
 */
int NetSocketRecv(int ctx, void *recvbuf, int len);

/**
 * @brief �ڵ�ǰ������豸�Ͻ���socket����
 * @brief Receiving socket data with timeout
 * @param ctx [in] socket context
 * @param recvbuf [out] ����socket���ݵĻ����� buffer for receiving socket data
 * @param len [in] Ԥ�ڽ��յ����ݳ��� expected data length
 * @param timeout [in] ����������ʱʱ�䣬0��ʾ�������أ�-1��ʾ�ȴ�ֱ��������� Max timeout to wait receive data, 0 means return immediatly, -1 means wait until receive data
 * @retval ����0 ���ճɹ� return > 0 for receive success
 * @retval С��0 ����ʧ�� return < 0 for receive fail
 */
int NetSocketRecvEx(int ctx, void *recvbuf, int len, int timeout);

/**
 * @brief ����socket����
 * @brief Send socket data
 * @param ctx [in] socket context
 * @param sendbuf [in] ����socket���ݵĻ����� buffer for sending socket data
 * @param len [in] Ԥ�ڷ��͵����ݳ��� expected data length
 * @retval ����0 ���ͳɹ� return > 0 for sending success
 * @retval С��0 ����ʧ�� return < 0 for sending fail
 */
int NetSocketSend(int ctx, void *sendbuf, int len);

/**
 * @brief Send data to socket context with specific timeout
 * @param ctx [in] socket context
 * @param sendbuf [in] buffer for sending
 * @param len [in] length of data to send in sendbuf
 * @param timeout_ms [in] sending timeout in millisecond, 0 means return immediately, -1 means wait until send finish.
 * @retval 0 Success
 * @retval <0: Fail
 */
int NetSocketSendEx(int ctx, void *sendbuf, int len, int timeout_ms);

/**
 * @brief �ر�socket����
 * @brief Close socket connection
 * @param ctx [in] socket context
 * @retval 0 �رճɹ� return 0 for close success
 * @retval <0 �ر�ʧ�� return < 0 for close fail
 */
int NetSocketClose(int ctx);

/**
 * @brief ��鵱ǰ�����豸�ϵ�socket����
 * @brief Check socket connection on current activated device
 * @param ctx [in] socket context
 * @retval 0 �Ͽ�״̬ return 0 for disconnected
 * @retval 1 ����״̬ return 1 for connected
 */
int NetSocketCheck(int ctx);

/**
 * @brief ��ȡָ��socket��ָ��ѡ��
 * @brief Get specified option for specified socket connection
 * @param ctx [in] socket context
 * @param opt [in] ָ����ѡ��SOCKET_TXDATA, SOCKET_RXDATA (Specify option: SOCKET_TXDATA, SOCKET_RXDATA)
 * @param pdata [out] ���ص�ѡ������ returned option information
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return <0 for fail, error code
 */
int NetSocketGetOption(int ctx, SOCKET_OPT_E opt, unsigned int *pdata);

/**
 * @brief ��ȡָ��socket�Ĵ�����
 * @brief Get error code for specified socket connection
 * @param ctx [in] socket context
 * @retval Socket������ return error code
 */
int NetSocketErrNo(int ctx);

/**
 * @brief Close all socket on specific net device
 * @param dev [in] net device
 */
void NetSocketCloseDev(net_dev_t dev);

/**
 * @brief ��ȡ�豸��Ϣ��IP��ַ/����/DNS����Ϣ
 * @param dev[in] �豸����
 * @param info [out] ����Ӳ����Ϣ��NULL��ʾ�����ȡ������Ϣ
 * @param exinfo [out] ��ϸӲ����Ϣ��NULL��ʾ�����ȡ��ϸ��Ϣ
 * @retval 0 �ɹ�
 * @retval <0 ʧ�ܣ�������
 */
int NetDeviceGetHwInfoEx2(net_dev_t dev, net_dev_hwinfo_t *info, net_dev_hwinfo_ex_t *exinfo);

/**
 * @brief ��ȡ�豸��Ϣ��IP��ַ/����/DNS����Ϣ
 * @param dev [in] �豸����
 * @param info [out] Ӳ����Ϣ
 * @retval 0 �ɹ�
 * @retval <0 ʧ�ܣ�������
 */
int NetDeviceGetHwInfo2(net_dev_t dev, net_dev_hwinfo_t *info);

/** @} net */

/**
 * @defgroup http http
 * @brief http operation related interface
 * @brief http������ؽӿ�
 * @{
 */
#define HTTP_CONTENT_TYPE_XML	0   ///< Http content is XML
#define HTTP_CONTENT_TYPE_JSON	1   ///< Http content is JSON

#include "utils_httpc.h"
/**
 * @brief http/https��ͨ�ķ��ͽ��սӿ�
 * @brief http/https normal sending and receiving port
 * @param [in] client httpclient_t�ṹָ��,����������� httpclient_t structure pointer, store request data
 * @param [in] url 	  ��������ַ server address
 * @param [in] port 	�������˿� server port
 * @param [in] ca_crt ֤�� certification
 * @param [in] method �������� @see HTTPCLIENT_REQUEST_TYPE (exchange method)
 * @param [in] timeout_ms ��ʱ timeout time
 * @param [in] client_data httpclient_data_t�ṹָ��,��ŷŻ����� (structure pointer, store returned data)
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return <0 for fail, error code
 */
int httpclient_common(httpclient_t *client, const char *url, int port, const char *ca_crt,
                      HTTPCLIENT_REQUEST_TYPE method, uint32_t timeout_ms, httpclient_data_t *client_data);
/**
 * @brief http/https�������ݽӿ�
 * @brief http/https receiving data port
 * @param [in] client httpclient_t�ṹָ��,����������� structure pointer, store request data
 * @param [in] timeout_ms ��ʱ timeout time
 * @param [in] client_data httpclient_data_t�ṹָ��,��ŷŻ����� structure pointer, store returned data
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return <0 for fail, error code
 */
int httpclient_recv_response(httpclient_t *client, uint32_t timeout_ms, httpclient_data_t *client_data);
/**
 * @brief http/https�ر�
 * @brief http/https close
 * @param [in] client httpclient_t�ṹָ��,����������� structure pointer, store request data
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return < 0 for fail, error code
 */
void httpclient_close(httpclient_t *client);
/**
 * @brief http/https post�����ӿ�
 * @brief http/https post exchange port
 * @param [in] client httpclient_t�ṹָ��,����������� structure pointer, store request data
 * @param [in] url 	  ��������ַ server address
 * @param [in] port 	�������˿� server port
 * @param [in] ca_crt ֤�� certification
 * @param [in] client_data httpclient_data_t�ṹָ��,��ŷŻ����� structure pointer, store returned data
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return < 0 for fail, error code
 */
int httpclient_post_data(httpclient_t *client, const char *url, int port, const char *ca_crt, httpclient_data_t *client_data);
/**
 * @brief ��HTTP����ͷ�е�HOST�ֶ�����
 * @brief Assemble HOST data for HTTP message header
 * @param [in] url 	  ��������ַ server address
 * @param [in] scheme 	  urlЭ��ͷ url scheme
 * @param [in] max_scheme_len 	  urlЭ��ͷ��󳤶� url scheme maximum length
 * @param [in] host 	  ��������ַ host address
 * @param [in] maxhost_len  ��������ַ��󳤶� host address maximum length
 * @param [in] port 	�������˿� host port
 * @param [in] path ·�� path
 * @param [in] max_path_len ·����󳤶� maximum path length
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return < 0 for fail, error code
 */
int httpclient_parse_url(const char *url, char *scheme, uint32_t max_scheme_len, 
    char *host, uint32_t maxhost_len, int *port, char *path, uint32_t max_path_len);

/**
 * @brief HTTP/HTTPS context
 * @brief HTTP/HTTPS ������
 */
typedef struct {
    httpclient_t *hc;           ///< http client
    httpclient_data_t *hc_data; ///< http client data
    int httpState;              ///< http state
} HTTP_MODE_CTX;

/**
 * @brief HTTP/HTTPS port initialize
 * @brief HTTP/HTTPS��ʼ���ӿ�
 * @param [in] pp_hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] host 	  ��������ַ Server address
 * @param [in] port 	  �������˿� Server port
 * @param [in] ca_crt 	  ֤�� Certification
 * @param [in] url  	  �ӿ�url Port url
 * @param [in] method 	  Э������ Scheme method
 */
void httpInitEx(HTTP_MODE_CTX **pp_hmc, const char *host, unsigned short port,
        const char *ca_crt, const char *url, int method);

/**
 * @brief HTTP?HTTPS port initialize
 * @brief HTTP/HTTPS��ʼ���ӿ�
 * @param [in] pp_hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] host 	  ��������ַ Server address
 * @param [in] hostSize   ��������ַ���� Server address length
 * @param [in] port 	  �������˿� Server port
 * @param [in] url  	  �ӿ�url Port url
 * @param [in] urlSize  	  �ӿ�url���� Port url length
 * @param [in] method 	  Э������ Scheme method
 * @code
	����(Example):httpInit(&hmc, "111.222.333.444",strlen("111.222.333.444")+1, 80, "/xposp/online/v2/transfers", strlen("/xposp/online/v2/transfers")+1, 1);
 * @endcode
 */
void httpInit(HTTP_MODE_CTX **pp_hmc, const char *host, int hostSize, unsigned short port,
        const char *url, int urlSize, int method);

/**
 * @brief HTTP/HTTPS handshake
 * @brief HTTP/HTTPS����
 * @param [in] host 	  ��������ַ Server address
 * @param [in] port 	  �������˿� Server port
 * @param [in] ca_crt  	  	  ֤�� Certification
 * @param [in] ca_crt_len  	  ֤�鳤�� Certification length
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return < 0 for fail, error code
 */		
int httpsInitHandshake(const char *host, unsigned short port,char *ca_crt, int ca_crt_len);

/**
 * @brief HTTP/HTTPS handshake
 * @brief HTTP/HTTPS����
 * @param [in] host 	  ��������ַ Server address
 * @param [in] port 	  �������˿� Server port
 * @param [in] ca_crt  	  	  ֤�� Certification
 * @param [in] ca_crt_len  	  ֤�鳤�� Certification length
 * @param [in] socketId			���ųɹ��󷵻ص�socket id
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return < 0 for fail, error code
 */		
int httpsInitHandshakeEx(const char *host, unsigned short port, char *ca_crt, int ca_crt_len, int *socketId);

/**
 * @brief Close connection
 * @brief �ر�����
 * @param [in] pp_hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 */
void httpClose(HTTP_MODE_CTX **pp_hmc);

/**
 * @brief Set connection as long time connection or not
 * @brief ���������Ƿ�����
 * @param [in] pp_hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] keepalive  1.������  0.������ (1 for long time connection, 0 for short time connection)
 */
void httpSetAlive(HTTP_MODE_CTX **pp_hmc, int keepalive);

/**
 * @brief Set HTTP message header configuration
 * @brief ����HTTP����ͷ����
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] key 	  �ֶ�����  key
 * @param [in] keySize 	  �ֶ����Ƴ���  key length
 * @param [in] value  	  	  ֵ value
 * @param [in] valueSize  	  ֵ���� value length
 */
void httpHeadPar(HTTP_MODE_CTX *hmc, const char *key, int keySize, const char *value, int valueSize);

/**
 * @brief Set HTTP POST configuration 
 * @brief ����HTTP POST����
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] key 	  �ֶ����� key
 * @param [in] keySize 	  �ֶ����Ƴ��� key length
 * @param [in] value  	  	  ֵ value
 * @param [in] valueSize  	  ֵ���� value length
 */
void httpPar(HTTP_MODE_CTX *hmc, const char *key, int keySize, const char *value, int valueSize);

/**
 * @brief Read HTTP/HTTPS large data
 * @brief ��ȡHTTP/HTTPS������
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] buf 	  �������ָ�� pointer for data storage
 * @param [in] buf_len 	  ������ݿռ��С size of data storage
 * @param [in] p_read_len  	  ��ȡ�������ݳ��� size of data read
 * @retval 0 Success return 0 for success
 * @retval <0 ʧ�ܣ������� return <0 for fail, error code
 */
int httpReadEx(HTTP_MODE_CTX *hmc, char *buf, int buf_len, int *p_read_len);

/**
 * @brief Read HTTP/HTTPS normal data
 * @brief ��ȡHTTP/HTTPSһ������
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] buf 	  �������ָ�� pointer for data storage
 * @param [in] size   ��ȡ�������ݳ��� size of data read
 */
void httpRead(HTTP_MODE_CTX *hmc, char *buf, int *size);

/**
 * @brief Send HTTP/HTTPS data
 * @brief ����HTTP/HTTPS����
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] buf 	  ����������ָ�� pointer for data ready to send
 * @param [in] size   ���ݳ��� length of data ready to send
 */
void httpWrite(HTTP_MODE_CTX *hmc, const char *buf, int size);

/**
 * @brief Get data from HTTP/HTTPS return message header
 * @brief ��ȡHTTP/HTTPS���ر���ͷ�е��ֶ�����
 * @param [in] hmc 	  HTTP_MODE_CTX�ṹָ�� HTTP MODE CTX structure pointer
 * @param [in] header 	 ����ͷ�ֶ��� message header name
 * @param [in] size   ����ͷ�ֶ������� length of message header name
 * @code
 *		����(For example) char *authToken=httpResponseGetHead(hmc,"Cookie",sizeof("Cookie"));
 * @endcode
 * @retval ����ͷ����ָ��,ʧ�ܷ���NULL return pointer for message header data, if fail, return NULL
 */
const char* httpResponseGetHead(HTTP_MODE_CTX *hmc, const char *header, int size);

/**
 * @brief Setup HTTP/HTTPS exchange timeout time
 * @brief ����HTTP/HTTPS������ʱʱ��
 * @param [in] time   ��ʱʱ�� timeout time
 */
void setTimeout(int time);

/** @} http */
/**
 * @defgroup wlan wlan
 * @brief wlan operation related interface
 * @brief wlan������ؽӿ�
 * @{
 */
// include "bwwlan.h"

// ������
#define WLAN_OK			     (0)	///< Normal, Success ����
#define WLAN_ERROR			 (-1)	///< Error ����
#define WLAN_FAIL			 (-2)	///< Fail
#define WLAN_ERR_UNKNOW      (-3)	///< Unknow error δ֪����
#define WLAN_ERR_OTHER       (-4)	///< Other error��������
#define WLAN_ERR_BUSY_S      (-5)   ///< Wlan Busy
#define WLAN_ERR_HW          (-6)   ///< Hardware error
#define WLAN_ERR_BUSY_P      (-7)   ///< 

#define WLAN_ERR_WRITE       (-10)	///< ����ʹ��� Send Command ERR
#define WLAN_ERR_READ        (-11)	///< ������մ��� Receive Command ERR
#define WLAN_ERR_OVERFLOW    (-12)	///< �����С���� Buffer Size ERR
#define WLAN_ERR_NULL        (-13)	///< NULL pointor
#define WLAN_ERR_PARA        (-14)  ///< Wrong parameter
#define WLAN_ERR_SLEEP       (-15)  // Enter sleep command fail
#define WLAN_ERR_WAKEUP      (-16)  // Wakeup command fail
#define WLAN_ERR_STATE       (-17)  // Wrong state
#define WLAN_ERR_RESP        (-18)  // ��Ӧ��

#define WLAN_ERR_SSID_LEN    (-20)	///< Wrong SSID length  ����SSID���ȴ��� 
#define WLAN_ERR_MAC_LEN     (-21)	///< Wrong MAC length   ����MAC���ȴ���
#define WLAN_ERR_NOIP        (-22)	///< No IP 

#define WLAN_ERR_CONNECT_BASE       (-30)   ///< 
#define WLAN_ERR_CONNECT_TIMEOUT    (-30)	///< ���ӳ�ʱ  Connecttion timeout
#define WLAN_ERR_CONNECT_PASSWORD   (-31)	///< �������  Wrong password
#define WLAN_ERR_CONNECT_NOAP       (-32)	///< �Ҳ���Ŀ��AP Can not find targe access point
#define WLAN_ERR_CONNECT_FAIL       (-33)	///< ����ʧ��  Connecttion fail
#define WLAN_ERR_CONNECT_CONNECTING (-34)	///< ������    Connectting
#define WLAN_ERR_NO_CONNECT         (-35)   // δ����AP
#define WLAN_ERR_NO_RECORD          (-36)   // �����Ӽ�¼
#define WLAN_ERR_UPDATE_RECORD      (-37)   // �������Ӽ�¼ʧ��

#define WLAN_ERR_LINK_TYPE          (-40)   ///< �������ͣ�LINK_TYPE_E����  Wrong link type
#define WLAN_ERR_LINK_REMOTE_IP     (-41)   ///< Զ��IP����  Wrong remote IP
#define WLAN_ERR_LINK_STATUS        (-42)   ///< ��ѯ����״̬����  Query link status fail
#define WLAN_ERR_LINK_MODE_SINGLE   (-43)   ///< ��ǰΪ�����ӣ�����ʹ�ö��������� Current: single connect, can not use multi-connection command
#define WLAN_ERR_LINK_MODE_MUX      (-44)   ///< ��ǰΪ�����ӣ�����ʹ�õ��������� Current: multi-connect, can not use single connetion command
#define WLAN_ERR_LINK_ALREADY       (-45)   ///< �ظ�����  Already linked
#define WLAN_ERR_LINK_OVER          (-46)   // ����������������
#define WLAN_ERR_LINK_CLOSE         (-47)   // �����ѹر�

#define WLAN_ERR_SENDEX_NOIPD           (-50)   ///<
#define WLAN_ERR_SENDEX_TIMEOUT         (-51)   ///< 
#define WLAN_ERR_SENDEX_OVERFLOW        (-52)   ///<

#define WLAN_ERR_SENDEX_RXLINKID        (-53)   ///< 
#define WLAN_ERR_SENDEX_RXLEN           (-54)   ///<
#define WLAN_ERR_SENDEX_RXCOLON         (-55)   ///< 
#define WLAN_ERR_SENDEX_RXDATA_OVERFLOW (-56)   ///< 
#define WLAN_ERR_SENDEX_UNKNOW          (-57)   ///< 

#define WLAN_ERR_NEED_RESET             (-58)   ///< 
#define WLAN_ERR_NO_OPEN                (-59)   ///< 
#define WLAN_ERR_NO_READY               (-60)   ///< 

/** @brief wifi encrypt mode **/
typedef enum {
    WIFI_ENCRYPT_MODE_MIN = 0,  ///<
    WIFI_ENCRYPT_MODE_OPEN = 0, ///<
    WIFI_ENCRYPT_MODE_WEP,      ///<
    WIFI_ENCRYPT_MODE_WPA_PSK,  ///<
    WIFI_ENCRYPT_MODE_WPA2_PSK, ///<
    WIFI_ENCRYPT_MODE_WPA_WPA2_PSK, ///<
    WIFI_ENCRYPT_MODE_WPA2_Enterprise, ///<
    WIFI_ENCRYPT_MODE_MAX              ///<
} WIFI_ENCRYPT_MODE_E;


#define WLAN_SSID_SIZE_MAX              (32) // ssid���32���ַ�
#define WLAN_MAC_SIZE                   (17)
#define WLAN_PWD_SIZE_MAX               (32)

#define WLAN_IP_SIZE                    (15)
#define WLAN_NETMASK_SIZE               (15)
#define WLAN_GATEWAY_SIZE               (15)
#define WLAN_DNS_SIZE                   (15)

#define INFO_SSID_SIZE_MAX              WLAN_SSID_SIZE_MAX ///< ssid���32���ַ� 
#define INFO_MAC_SIZE                   WLAN_MAC_SIZE ///< macΪ�̶�17�ֽ�
#define INFO_CHANNEL_MIN                (1)  ///< channel,802.11���14���ŵ�,1-14 For 802.11, Maximum 14 channel.
#define INFO_CHANNEL_MAX                (14) ///< channel,802.11���14���ŵ�,1-14

/** @brief Information of WIFI **/
typedef struct {
    char ssid[WLAN_SSID_SIZE_MAX+1];  ///<
    char mac[WLAN_MAC_SIZE+1];        ///<
    unsigned char ch;                 ///<
    int rssi;                         ///<
    int freq_offset;                  ///<
    int freq_calibration;             ///<
    WIFI_ENCRYPT_MODE_E encrypt_mode; ///<
} WIFI_INFO_T;

typedef struct HOTSPOT_ID_ST {
    char ssid[WLAN_SSID_SIZE_MAX+1];
    char mac[WLAN_MAC_SIZE+1];          // AA:BB:CC:DD:EE:FF
    char pwd[WLAN_PWD_SIZE_MAX+1];
} hotspot_id_t;

typedef struct HOTSPOT_ST {
    char ssid[WLAN_SSID_SIZE_MAX+1];
    char mac[WLAN_MAC_SIZE+1];          // AA:BB:CC:DD:EE:FF
    char pwd[WLAN_PWD_SIZE_MAX+1];
    char ip[WLAN_IP_SIZE+1];            // 110.110.110.110
    char netmask[WLAN_NETMASK_SIZE+1];  // 255.255.255.255
    char gateway[WLAN_GATEWAY_SIZE+1];  // 110.110.110.111
    char dns[WLAN_DNS_SIZE+1];          // xxx.xxx.xxx.xxx
    char dhcp_en;
} hotspot_t;

#define LINK_ID_UONUSE  (-1)///< ������ Single connect
#define LINK_ID_MIN     (0) ///< �����ӣ���СLINK ID (Multi-connect, minimum link ID)
#define LINK_ID_MAX     (4) ///< �����ӣ����LINK ID (Multi-connect, maximum link ID)
#define LINK_ID_MUX_ALL (5) ///< �����ӣ��ر�ȫ�� (Multi-connect, shut down all)

#define TCP_KEPP_ALIVE_MIN (1)      ///<
#define TCP_KEPP_ALIVE_MAX (7200)   ///<
/** @brief ��������**/
/** @brief Connection type**/
typedef enum {
    LINK_TYPE_TCP = 0, 	///<  TCP
    LINK_TYPE_UDP,		///<  UDP
    LINK_TYPE_SSL,		///<  SSL
    LINK_TYPE_UNKNOW	///<  δ֪	Unknown
} LINK_TYPE_E;
/** @brief TE����**/
/** @brief TE type**/
typedef enum {
    TE_TYPE_CLIENT = 0, ///<
    TE_TYPE_SERVER,     ///<
    TE_TYPE_UNKNOW      ///<
} TE_TYPE_E;

#define REMOTE_IP_MAX_SIZE  (15)	///<���IP��ַ���� Maximum IP address size

/** @brief Information of WIFI link **/
typedef struct {
    unsigned char link_id;    ///<
    char remote_ip[REMOTE_IP_MAX_SIZE+1]; ///<
    TE_TYPE_E tetype;         ///<
    LINK_TYPE_E link_type;    ///<
    unsigned int remote_port; ///<
    unsigned int local_port;  ///<
} WIFI_LINK_INFO_T;

#define WLAN_LINK_STATUS_REMOTE_LINKED   (0) ///< �ѽ���TCP��UDP���� Already connected as TCP or UDP
#define WLAN_LINK_STATUS_AP_CONNECTED    (1) ///< ������AP,���ip��ַ Already connected to access point, get IP address
#define WLAN_LINK_STATUS_REMOTE_UNLINKED (2) ///< �ѶϿ�Զ������ Already disconnected
#define WLAN_LINK_STATUS_AP_DISCONNECTED (3) ///< δ����AP Access point not connected
/** @brief ͨѶ����**/
/** @brief Transmission type **/
typedef enum {
    CIPMODE_NORMAL = 0,  ///<
    CIPMODE_PASSTHROUGH, ///< ͸�� Pass through transmission
    CIPMODE_UNKNOW
} CIPMODE_TYPE_E;
/** @brief ��������**/
/** @brief Connection type**/
typedef enum {
    CIPMUX_SINGLE = 0,  ///< ������ Single connect
    CIPMUX_MUX,         ///< ������ Multi-connect
    CIPMUX_UNKNOW       ///<
} CIPMUX_TYPE_E;

/** @brief wlan roaming type**/
typedef enum {
    WLAN_ROAMING_DISABLE = 0,   ///< WLAN roaming disable
    WLAN_ROAMING_ENABLE,        ///< WLAN roaming enable
} WLAN_ROAMING_E;

/**
 * @brief �����ȵ�
 * @param [out]   pstHotSpotList: �ȵ��б�����
 * @param [inout] puiListSize: 
 * -#                       [in]  �ȵ��б�������С
 * -#                       [out] �ȵ����
 * @retval 0 �ɹ�
 * @retval !0 ʧ��
 */
int BW_Wlan_GetWifiList(WIFI_INFO_T *pstHotSpotList, unsigned int *puiListSize);

/**
 * @brief WLAN_SetDHCP
 * @param [in] enable:  !0: �Զ���ȡ Automatic get DHCP, 0: �ֶ����� Manually setup
 * @param [in] ip: ��enable==0, �ò���������ڣ���enable==1,�ò�����Ч (when enable = 0, that value must exist, when enable = 1, that value invalid)
 * @param [in] gateway: ��enable==0, �ò�����ѡ����enable==1,�ò�����Ч (when enable = 0, that value is optional, when enable = 1, that value invalid)
 * @param [in] netmask: ��enable==0, �ò�����ѡ(gateway������������)����enable==1,�ò�����Ч (when enable = 0, that value is optional, when enable = 1, that value invalid)
 * @retval 0 Success
 * @retval !0 ������
 */
int WLAN_SetDHCP(unsigned char enable, char* ip, char* gateway, char* netmask);

/**
 * @brief WLAN_SetDNS
 * @param [in] autoEnable: !0: �Զ���ȡ Automatic get DNS, 0: �ֶ����� Manually setup
 * @param [in] dns_server0: autoEnable==0, �ò�����ѡ����autoEnable==1,�ò�����Ч (when enable = 0, that value is optional, when enable = 1, that value invalid)
 * @param [in] dns_server1: autoEnable==0, �ò�����ѡ����autoEnable==1,�ò�����Ч (when enable = 0, that value is optional, when enable = 1, that value invalid)
 * @note Ĭ��dns������Ϊ208.67.222.222, ����openDNS(Default DNS address is 208.67.222.222, belongs to open DNS)
 * @retval 0 Success return 0 for success
 * @retval !0 ������ return !0 for error code
 */
int WLAN_SetDNS(unsigned char autoEnable, char* dns_server0, char* dns_server1);

/**
 * @brief WLAN�Ŀ���״̬
 * @retval 0 ����
 * @retval !0 ������
 */
int WLAN_NetGetAtStatus(void);

/**
 * @brief WLAN_HotportCheck
 * @param ssid [in] ��ѡ
 * @param mac [in]  ��ѡ����ָ��macʱ��NULL
 * @param ch [in]  ��ѡ����Ч�ŵ�1-14����ָ���ŵ���0
 * @param info [out] WIFI�б���
 * @param info_len [in]  WIFI�б������ֵ
                    [out] ��ȡ����WIFI�б�����
 * @retval 0 Success
 * @retval !0 ������
 *            WLAN_ERR_NULL:ssid��info��info_lenΪNULL
 *            WLAN_ERR_NO_OPEN:wifiģ��δ��
 *            WLAN_ERR_NO_READY��wifiģ��δ����
 *            WLAN_ERR_CONNECT_NOAP:Ŀ��ap������
 */
int WLAN_HotportCheck(char* ssid, char* mac, unsigned char ch, WIFI_INFO_T* info, unsigned int* info_len);

/**
 * @brief Get the hotspots recorded.
 * @param [out] pstHotSpotId: SSID list array
 * @param [in]  uiSize: size of hotspot id list
 * @retval >= 0 Count of SSID in list
 * @retval <0 Fail
 */
int WLAN_GetHotSpotRecord(hotspot_id_t *pstHotSpotId, unsigned int uiSize);

/**
 * @brief Delete the hotspot in record.
 * @param [in] ssid: SSID
 * @param [in] mac:  MAC
 * @retval 0  success
 * @retval <0 Fail
 */
int WLAN_DeleteHotSpotRecord(char *ssid, char *mac);

/**
 * @brief Get space of hotspot record.
 * @retval Number of space.
 */
int WLAN_GetHotSpotRecordSpace(void);

/**
 * @brief Delete the hotspot in record.
 * @param [in] pstHotSpot: hotspot list
 * @param [in] uiSize: size of the list.
 * @retval 0  success
 * @retval <0 Fail
 */
int WLAN_InsertHotSpotRecord(hotspot_t *pstHotSpot, int uiSize);

/**
 * @brief Set WLAN roaming
 * @param [in] en: WLAN roaming disable/enable
 * @retval 0  success
 * @retval <0 Fail
 */
int WLAN_RoamingSet(WLAN_ROAMING_E en);

/**
 * @brief Get WLAN roaming
 * @retval 1: WLAN roaming enabled
 * @retval 0: WLAN roaming disabled
 */
int WLAN_RoamingGet(void);

/**
 * @brief WLAN �汾��Ϣ
  * @param [out] pcWlanVer: pointer to verion buffer.
 * @param [in] uiSize: size of buffer.
 * @retval 0 �ɹ�
 * @retval !0 ʧ��
 */
int WLAN_GetVersion(char *pcWlanVer, unsigned int uiSize);

/** @} wlan */

/**
 * @defgroup bluetooth bluetooth
 * @brief Bluetooth operation related interface
 * @brief ����������ؽӿ�
 * @{
 */
//#include "bwbt.h"
#define BT_NAME_MAX_LEN 20 ///< �����豸����ַ���
#define BT_PIN_MAX_LEN 4   ///< ����PIN������ַ���
#define BT_ADDR_LEN 17     ///< ������ַ�ַ�������


/**
 * @brief configure of bluetooth
 */
typedef struct {
    char *name; ///< Bluetooth name  �����豸�������20���ַ�, ��: "QR150BT" (Bluetooth device name)
    char *addr; ///< Bluetooth address ������ַ������Ϊ17���ֽڣ���: "00:A1:B2:33:44:55"��"00-A1-B2-33-44-55"(Bluetooth device address)
    char *pin;  ///< Bluetooth PIN  ����PIN���룬���4��ASCII�ַ�, ��: "1234" (Bluetooth device pin)
} btconfig_t;

/**
 * @brief Swith Bluetooth module ON/OFF
 * @brief ����BTģ������µ�
 * @param [in] onoff:
 * -#               0 - OFF
 * -#               1 - ON
 * @retval 0: Success
 * @retval !0: Fail
 */
int BW_BlueTooth_Power(int onoff);

/**
 * @brief Get Bluetooth module current connection status
 * @brief ��ȡBTģ�鵱ǰ����״̬
 * @retval 0 Disconnect
 * @retval 1 connected
 */
int BW_BlueTooth_IsConnect(void);

/**
 * @brief Open/Close Bluetooth module command mode
 * @brief ����BTģ�������ģʽ
 * @note When bluetoothed connection detected, please close the command mode
 * @note ����⵽����ģ��������ʱ����ر�����ģʽ
 * @param [in] onoff:
 * -#               0 - OFF
 * -#               1 - ON
 * @retval 0: Success
 * @retval <0: Fail
 */
int BW_BlueToothCmdEnable(int onoff);

/**
 * @brief Get Bluetooth name
 * @brief �����������
 * @retval NULL: Fail
 * @retval !NULL: Bluetooth name, not need to free
 */
char* BW_BlueTooth_GetName(void);

/**
 * @brief Get Bluetooth address
 * @brief ���������ַ
 * @retval NULL: Fail
 * @retval !NULL: Bluetooth address, not need to free
 */
char* BW_BlueTooth_GetAddr(void);

/**
 * @brief Setup Bluetooth module property
 * @brief ����BTģ�����
 * @note  Interface will automatic open command mode
 * @note �ӿڻ����п�������ģʽ
 * @param [in] cfg: bluetooth configuration Ҫ���õ��������� 
 * @retval 0: Success
 * @retval <0: Fail
 */
int BW_BlueTooth_SetConfig(btconfig_t *cfg);

/**
 * @brief Get data from Bluetooth module
 * @brief ������ģ�������
 * @note  if there is no bluetooth connect, wont transfer data through bluetooth
 * @note  δ����ʱ���޷�ͨ������ģ�鴫������ 
 * @param [out] buff: Data output.  ���������� 
 * @param [in]  bufflen: Size of buffer. buff�Ĵ�С 
 * @param [in]  timeout_ms: Timeout(Ms) ��ʱʱ�� 
 * @retval <0: Fail
 * @retval >=0: Length of data output
 */
int BW_BlueTooth_Read(void *buff, unsigned int bufflen, unsigned int timeout_ms);

/**
 * @brief Write data to bluetooth module
 * @brief ������ģ��д����
 * @note  if there is no bluetooth connect, wont transfer data through bluetooth
 * @note  δ����ʱ���޷�ͨ������ģ�鴫������ 
 * @param [in] buff: Data to write  Ҫд������ 
 * @param [in] bufflen: Length of data to write  Ҫд�������ֽ��� 
 * @retval <0: Fail
 * @retval >= 0: Length of data written
 */
int BW_BlueTooth_Write(void *buff, unsigned int bufflen);


/**
 * @brief Flash inside
 * @brief Flash ������
 * @param [in] file_name: File name, no more than 16 bytes  �ļ�����������16���ַ� 
 * @param [in] breakPointMode: Check whether break point mode
 * -#                       1 - yes
 * -#                       0 - no 
 * @retval  0: Success
 * @retval  !0: Fail
 * @pre None
 */
int BWOTA_FlashInside(const char* file_name, int breakPointMode);

/**
 * @brief Flash File System
 * @brief Flash���ļ�ϵͳ����
 * @param filename [in]: File name, no more than 128 bytes �ļ�����������128���ַ� 
 * @retval >= 0: Success, file descriptor
 * @retval !0: Fail
 * @pre BWFS_Init
 */
int BWOTA_FlashFileSystem(const char *filename);

/**
 * @brief Flash sub application
 * @brief Flash��������Ӧ��
 * @param [in] filename: File name, no more than 128 bytes �ļ�����������128���ַ�
 * @retval >=0: Success
 * @retval !0:  Fail
 * @pre BWFS_Init
 */
int BWOTA_FlashSubApp(const char *filename);

/**
 * @brief Get Flash sub application update result
 * @brief ��ȡFlash��������Ӧ�ý��
 * @param [in] filename: File name, no more than 128 bytes �ļ�����������128���ַ�
 * @retval 0: Success
 * @retval !0: Fail
 * @pre BWFS_Init
 */
int BWOTA_GetFlashSubAppResult(const char *filename);

/** @} bluetooth */

/**
 * @defgroup led led
 * @brief LED operation related interface, contactless card reader LED is not controlled by this interface
 * @brief led������ؽӿ�,�ǽӵƲ��ڴ˽ӿ��ڿ���
 * @{
 */
//#include "bwled.h"
/**
 * @brief General LED control 
 * @warning Not for NFC LED
 */
typedef enum {
    LED_CHG_R, ///< ChargLED Red
    LED_CHG_G, ///< ChargLED Green
    LED_CHG_B, ///< ChargLED Blue
    
    LED_SCAN_R, ///< ScanLED Red
    LED_SCAN_G, ///< ScanLED Green
    LED_SCAN_B, ///< ScanLED Blue

    LED_WORK_R, ///< WorkLED Red
    LED_WORK_G, ///< WorkLED Green
    LED_WORK_B, ///< WorkLED Blue

    LED_ID_MAX,	///< ���ID 
} led_id_type;

/**
 * @brief Signale LED switdh
 * @brief ����LEDָʾ�ƵĿ���
 * @param [in] id: LED id, @see:: led_id_type
 * @param [in] onoff:
 * -#           0 - OFF
 * -#           1 - ON
 * @retval 0: Success
 * @retval -1: not supported
 */
int LedCtrl(led_id_type id, int onoff);

/** @} led */


/**
 * @defgroup hid hid
 * @brief hid operation related interface
 * @brief hid������ؽӿ�
 * @{
 */
// #include "bwhid.h"
/**
 * @brief: Send data to USB-HID
 * @brief: �������ݵ�USB-HID
 * @param [in] buff: Data need to be sent Ҫ���͵����� 
 * @param [in] len:  Length of data to be sent Ҫ���͵����ݳ��� 
 */
void USBHIDSend(unsigned char *buff, unsigned int len);

/** @} hid */



/**
 * @defgroup printer printer
 * @brief printer module function
 * @{
 */
//=============================================================
//#include "bw_printer.h"
//=============================================================

/**
 * @brief: Bar code type
 * @brief: ��������
 */
typedef enum 
{
	BARCODE_ANY,      ///<
	BARCODE_CODE128,  ///<
	BARCODE_CODE39,   ///<
	BARCODE_CODE93,   ///<
	BARCODE_CODE11,   ///<
	BARCODE_MSI,      ///<
	BARCODE_I25,      ///<
	BARCODE_EAN8,     ///<
	BARCODE_EAN13,    ///<
	BARCODE_UPCA,     ///<
	BARCODE_UPCE,     ///<
	BARCODE_CODABAR,  ///<
} barcode_t;

/**
 * @brief: Font size
 * @brief: �����С
 */
typedef enum
{
    PRINT_FONT_SIZE_SMALL 	= 16,   ///<
    PRINT_FONT_SIZE_NORMAL 	= 24,   ///<
    PRINT_FONT_SIZE_LARGE  	= 32,   ///<
} fontsize_t;

/**
 * @brief: Font style
 * @brief: ����Ч��
 */
typedef enum
{
    PRINT_FONT_EFFECT_NONE, ///< Normal
    PRINT_FONT_EFFECT_BOLD, ///< Bold
} fonteffect_t;

/**
 * @brief: Align mode
 * @brief: ��ӡ���뷽ʽ
 */
typedef enum 
{
    PRINT_ALIGN_LEFT,   ///< Left align
    PRINT_ALIGN_CENTER, ///< Center align
    PRINT_ALIGN_RIGHT   ///< Right align
} printalign_t;

/**
 * @brief:
 * @brief:��ӡ�ַ���,֧�ֶ����Ի���
 */
typedef enum {
    PRINT_CHARSET_GBK = 0,         ///< GBK charset CP936
    PRINT_CHARSET_LATIN1 = 1,      ///< WEST char set, also named ISO8859-1
    PRINT_CHARSET_ISO_8859_1 = 1,  ///< Charset ISO8859

    PRINT_CHARSET_MAX              ///<
} printcharset_t;

/**
 * @brief: Printer status
 */
typedef enum 
{
    PRINTER_STATUS_IDLE,                ///< Printer is idle
    PRINTER_STATUS_CACHING,             ///< Printer is caching data
    PRINTER_STATUS_PRINTING,            ///< Printer is printing
    PRINTER_STATUS_ERROR_NO_PAPER,      ///< Printer have no paper
    PRINTER_STATUS_ERROR_OVERHEAT,      ///< Printer overheat
    PRINTER_STATUS_ERROR_BMARK,         ///< No black mark detect
    PRINTER_STATUS_ERROR_COMM,          ///< Communication error
    PRINTER_STATUS_ERROR_LOW_BATTERY,   ///< Low battery
    PRINTER_STATUS_ERROR_NO_FONT_LIB,   ///< No font lib
    PRINTER_STATUS_ERROR_NO_CACHE_MEMORY, ///< Memory used out
    PRINTER_STATUS_MAX                  ///<
} printerstatus_t;

/**
 * @brief: printer information
 * @brief: ��ӡ����Ϣ
 */
typedef struct
{
    int type; 			///< Type of printer 0 -- No printer  1 -- Thermal printer
    int pixelX; 		///< Pixel in X  ˮƽ���ص�
    int pixelY; 		///< Pixel in Y  ��ֱ���ص�
    int havePaper; 		///< paper status ֽ״̬ 0 -- No paper  1 -- Normal
    int temperature; 	///< Temperature of printer �¶� ( >= 65 -- overheat)
    char name[10]; 		///< Printer model ��ӡ�����ͺ�
} printer_info_t;

/**
 * @brief: printer parameters
 * @brief: ��ӡ����
 */
typedef struct
{
    fontsize_t fontSize; 	///< Font size �����С
    fonteffect_t fontEffect;///< Font Ч��
    printalign_t printAlign;///< Align ���뷽ʽ
    printcharset_t printCharSet; ///< Charset �ַ���
    int lineSpace; 		    ///< Line space �м��    
    int printGray; 			///< Gray level ��ӡ�Ҷ� (1-5000)
    int printHeatpoint; 	///< Heat point ���ȵ��� (8�ı������ܱ�384���� 8~96)
    int printStep; 			///< Minimum moto step  ���� (1-5000)
} printer_param_t;

/**
 * @brief Check printer and get printer information
 * @brief ����ӡ��
 * @param [out] info: printer information  ��ӡ����Ϣ
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_Check(printer_info_t* info);

/**
 * @brief Open printer
 * @brief �򿪴�ӡ��
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_Open(void);

/**
 * @brief Set printer parameters
 * @brief ���ò���
 * @param [in] param: printer parameter ��ӡ������, @see:: printer_param_t
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_SetParameter(const printer_param_t* param);

/**
 * @brief Get printer parameters ��ȡ����
 * @param [out] param: printer parameter ��ӡ������, @see:: printer_param_t
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_GetParameter(printer_param_t* param);

/**
 * @brief Paper feed
 * @brief ��ֽ
 * @param [in] forward: line to feed ��ֽ����
 * -#                   >0 -- feed forward  ��ֽ
 * -#                   <0 -- feed backward ��ֽ
 * @param [in] markLines �ڱ������  0 -- �����ڱ�  1~1000 �ڱ��ȣ����У�
 * @param [in] markValue �ڱ��ֵⷧ 0 -- ʹ��Ĭ�� 1-1024 �ֶ����÷�ֵ
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_SetPrintCtrlFeed(int forward, int markLines, int markValue);

/**
 * @brief Clean printer cache
 * @brief ��ջ���
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_CleanCache(void);

/**
 * @brief Add text to printer cache
 * @brief ����ĵ�������
 * @param [in] text: text content �ı�
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddText(const char* text);

/**
 * @brief Add BMP to printer cache
 * @brief ���ͼƬ������
 * @param [in] bmpData: BMP data ͼƬ����
 * @param [in] bmpDataLen: Length of BMP data ͼƬ���ݳ���
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBmp(const char* bmpData, int bmpDataLen, int needReverse);

/**
 * @brief Add BMP to printer cache
 * @brief ���ͼƬ������
 * @param [in] bmpPath: BMP path ͼƬ·��
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBmpPath(const char* bmpPath, int needReverse);

/**
 * @brief Add bar code to printer cache
 * @brief ���һά�뵽����
 * @param [in] codeType: Type of bar code ��������
 * @param [in] codeWidth: Width of code ���
 * @param [in] codeHeight: Height of code ���
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBarCode(barcode_t codeType, int codeWidth, int codeHeight, const char* strContent);

/**
 * @brief Add QR code to printer cache
 * @brief ��Ӷ�ά�뵽����
 * @param [in] codeSize: Size of code ���С
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddQRCode(int codeSize, const char* strContent);

/**
 * @brief Print
 * @brief ��ӡ��������
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_Print(void);

/**
 * @brief Print text
 * @brief ��ӡ�ı�
 * @param [in] text: text content �ı�
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintText(const char* text);

/**
 * @brief Print BMP
 * @brief ��ӡͼƬ
 * @param [in] bmpData: BMP data ͼƬ����
 * @param [in] bmpDataLen: Length of BMP data ͼƬ���ݳ���
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintBmp(const char* bmpData, int bmpDataLen, int needReverse);

/**
 * @brief Print BMP
 * @brief ��ӡͼƬ
 * @param [in] bmpPath: BMP path ͼƬ·��
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintBmpPath(const char* bmpPath, int needReverse);

/**
 * @brief Print bar code
 * @brief ��ӡһά��
 * @param [in] codeType: Type of bar code ��������
 * @param [in] codeWidth: Width of code ���
 * @param [in] codeHeight: Height of code ���
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintBarCode(barcode_t codeType, int codeWidth, int codeHeight, const char* strContent);

/**
 * @brief Print QR code
 * @brief ��ӡ��ά��
 * @param [in] codeSize: Size of code ���С
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintQRCode(int codeSize, const char* strContent);

 /**
 * @brief Add text to cache
 * @brief ����������ı�
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] text: text content �ı�
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddTextWithParam(const printer_param_t* param, const char* text);

/**
 * @brief Add BMP to cache
 * @brief ���������ͼƬ
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] bmpData: BMP data ͼƬ����
 * @param [in] bmpDataLen: Length of BMP data ͼƬ���ݳ���
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBmpWithParam(const printer_param_t* param, const char* bmpData, int bmpDataLen, int needReverse);

/**
 * @brief Add BMP to cache
 * @brief ���������ͼƬ
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] bmpPath: BMP path ͼƬ·��
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBmpPathWithParam(const printer_param_t* param, const char* bmpPath, int needReverse);

/**
 * @brief Add bar code to cache
 * @brief ���������һά��
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] codeType: Type of bar code ��������
 * @param [in] codeWidth: Width of code ���
 * @param [in] codeHeight: Height of code ���
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddBarCodeWithParam(const printer_param_t* param, barcode_t codeType, 
	int codeWidth, int codeHeight, const char* strContent);

/**
 * @brief Add QR code to cache  ��������Ӷ�ά��
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] codeSize: Size of code ���С
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_AddQRCodeWithParam(const printer_param_t* param, int codeSize, const char* strContent);

/**
 * @brief Print text
 * @brief ��������ӡ�ı�
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] text �ı�
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintTextWithParam(const printer_param_t* param, const char* text);

 /**
 * @brief Print BMP
 * @brief ��������ӡͼƬ
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] bmpData: BMP data ͼƬ����
 * @param [in] bmpDataLen: Length of BMP data ͼƬ���ݳ���
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
 int BWPrinter_PrintBmpWithParam(const printer_param_t* param, const char* bmpData, int bmpDataLen, int needReverse);

/**
 * @brief Print BMP
 * @brief ��������ӡͼƬ
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] bmpPath: BMP path ͼƬ·��
 * @param [in] needReverse: Color reverse �Ƿ���Ҫ��ת
 * -#                   0 - Not reverse
 * -#                   1 - Reverse
 * @retval 0: Success
 * @retval !0: Fail
 */
 int BWPrinter_PrintBmpPathWithParam(const printer_param_t* param, const char* bmpPath, int needReverse);

/**
 * @brief Print bar code
 * @brief ��������ӡһά��
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] codeType: Type of bar code ��������
 * @param [in] codeWidth: Width of code ���
 * @param [in] codeHeight: Height of code ���
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintBarCodeWithParam(const printer_param_t* param, barcode_t codeType, 
	int codeWidth, int codeHeight, const char* strContent);

/**
 * @brief Print QR code
 * @brief ��������ӡ��ά��
 * @param [in] param: printer parameters ��ӡ����
 * @param [in] codeSize: Size of code ���С
 * @param [in] strContent: Content of code ����
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_PrintQRCodeWithParam(const printer_param_t* param, int codeSize, const char* strContent);

 /**
 * @brief Get printer status ��ȡ��ӡ��״̬
 * @retval ״̬
 */
int BWPrinter_GetStatus(void);

/**
 * @brief Close printer  �رմ�ӡ��
 * @retval 0: Success
 * @retval !0: Fail
 */
int BWPrinter_Close(void);

/** @} printer */

/**
 * @defgroup MainApp MainApp
 * @brief MainApp functions
 * @{
 */
//=============================================================
//#include "BwMain_api.h"
//=============================================================

#define BWMAIN_API_ERR_UNKNOWVER (0x7F) ///<

/**
 * @brief Get Main-APP version
 * @brief ��ȡmainapp�汾
 * @param [out] verBuf: Main App version
 * @param [in]  verBufSize: Size of buffer
 * @retval BWMAIN_API_ERR_UNKNOWVER(0x7F) - ���ڰ汾�ӿڲ�����
 * @retval  0 - Success
 * @retval !0 - Fail
 */
int MainAppApi_GetVer(char* verBuf, unsigned int verBufSize);

/**
 * @brief Get Second-APP update state
 * @brief ��ȡsencondapp����״̬��־
 * @retval  0 - Not need unlock ����Ҫ����
 * @retval  1 - Need unlock     ��Ҫ����
 * @retval BWMAIN_API_ERR_UNKNOWVER(0x7F) - ���ڰ汾�ӿڲ�����
 * @retval -101 - upd.tmp file error  �ļ�����
 * @retval -102 - img file not exist  �ļ�������
 * @retval Other <0 - img file error  �ļ�����
 */
int MainAppApi_GetSencondAppUpdateFlag(void);

/**
 * @brief Get remote authentication request code
 * @brief ��ȡԶ�̽���������
 * @param [in]  mode 0x00 - MODE_RSA1024_SHA1
 *                   0x01 - MODE_RSA1024_SHA256
 * @param [out] pusEnOutLen
 * @param [out] pucEnOut
 * @retval  0 - Success
 * @retval BWMAIN_API_ERR_UNKNOWVER(0x7F) - ���ڰ汾�ӿڲ�����
 * @retval FEBF(-321) - PED_RET_ERROR ͨ�ô���
 * @retval FE9C(-356) - PED_RET_ERR_UNLOCK_TIMEOUT Զ�̽�����ʱ
 * @retval FE9B(-357) - PED_RET_ERR_UNLOCK_PARAM Զ�̽�����������
 * @retval FE9A(-358) - PED_RET_ERR_UNLOCK_NO Զ�̽���APδ���������
 * @retval FE99(-359) - PED_RET_ERR_UNLOCK_CHECK Զ�̽���У���
 * @retval FE98(-360) - PED_RET_ERR_NEED_RESET ��Ҫ����
 * @retval FE97(-361) - PED_RET_ERR_RNG �������������
 */
int MainAppApi_PedReqRemoteUnlock(unsigned char mode, unsigned short* pusEnOutLen, unsigned char *pucEnOut);

/**
 * @brief Remote authentication verify
 * @brief ��֤Զ�̽�����Ȩ��
 * @param [in]  mode 0x00 - MODE_RSA1024_SHA1
 *                   0x01 - MODE_RSA1024_SHA256
 * @param [in] usEnInLen
 * @param [in] pucEnIn
 * @note  ��ʱʱ��Ϊ[ִ��MainAppApi_PedReqRemoteUnlock��5����]
 * @retval  0 - Success
 * @retval BWMAIN_API_ERR_UNKNOWVER(0x7F) - ���ڰ汾�ӿڲ�����
 * @retval FEBF(-321) - PED_RET_ERROR ͨ�ô���
 * @retval FE9C(-356) - PED_RET_ERR_UNLOCK_TIMEOUT Զ�̽�����ʱ
 * @retval FE9B(-357) - PED_RET_ERR_UNLOCK_PARAM Զ�̽�����������
 * @retval FE9A(-358) - PED_RET_ERR_UNLOCK_NO Զ�̽���APδ���������
 * @retval FE99(-359) - PED_RET_ERR_UNLOCK_CHECK Զ�̽���У���
 * @retval FE98(-360) - PED_RET_ERR_NEED_RESET ��Ҫ����
 * @retval FE97(-361) - PED_RET_ERR_RNG �������������
 */
int MainAppApi_PedRemoteUnlock(unsigned char mode, unsigned short usEnInLen, unsigned char *pucEnIn);

/** @} MainApp */

/** @} BWSDK */

#ifdef __cplusplus
}
#endif

#endif

