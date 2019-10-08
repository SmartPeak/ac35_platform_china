#ifndef SECRETKEY_H_
#define SECRETKEY_H_

///< soft encryption on-off
#define SECRETKEY_SOFTDES           0

#if SECRETKEY_SOFTDES
/**
* @brief struct definition of soft encryption
*/
typedef struct {
    unsigned char SMKey[16 + 1];
    unsigned char tlKey[16 + 1];
    unsigned char tlKeyLen;
    unsigned char MainKey[16 + 1];
    unsigned char MainKeyLen;
    unsigned char pinKey[16 + 1];
    unsigned char pinKeyLen;
    unsigned char macKey[16 + 1];
    unsigned char macKeyLen;
    unsigned char tdkKey[16 + 1];
    unsigned char tdkKeyLen;
} tsSoftSp;
#endif

///< load SM4 SN Key
int SecretKey_LoadTestSNKey(unsigned char *pKeyValue, unsigned char len);

///< save new TLK
int SecretKey_LoadTLK(unsigned char *pKeyValue, unsigned char len);

///< load TMK
int SecretKey_LoadTMK(unsigned char bTLKdecrypt, unsigned char index, unsigned char *buff, unsigned char len);

///< save new work key
int SecretKey_SaveNewKey(unsigned char encryptType, unsigned char *pInData, unsigned short iInLen);

///< ¼ÆËãMAC ECBÄ£Ê½
int SecretKey_MacECB(unsigned char *pDataIn, unsigned int inLen, unsigned char *pDataOut);

///< PIN data encrypt
int SecretKey_EncryptPINData(unsigned char *pPINData, unsigned char *pDataOut);

///< bit 59 SN encrypt
int SecretKey_Bit59_CalcMAC(unsigned char *pInData, unsigned short uiInLen, unsigned char *pKey, unsigned char *pOutMAC);

///< track data encrypt
int SecretKey_EcryptTrack(unsigned char *pTrackData, unsigned short usLen, int *pOutLen);

///< master key manage menu
int POS_KeyManageMenu(void);


#endif /* SECRETKEY_H_ */

