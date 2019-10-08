
#ifndef __MERCURY_BASE64_H__
#define __MERCURY_BASE64_H__

/*---------------------------------------------------------------
 *       Include Files
 * ------------------------------------------------------------*/

/* =============function declaration =============== */

/* lenSrc is the length of pSrc, if the pSrc is the string end with 0,
   could assign it to 0. bChng is judge whether is the changed base64,
   about changed base64 please refer to rfc2045. */
int MercuryToBase64(char *pDest, char *pSrc, unsigned int lenSrc, unsigned char bChng);

int MercuryFromBase64(char *pDest, char *pSrc, unsigned int uiOrigSize);

/*get encoded string size from original string*/
unsigned int MercuryBase64EncodeSize(unsigned int iSize);

/*get decoded string size from original string*/
unsigned int MercuryBase64DecodeSize(unsigned int iSize);

#endif /* __MERCURY_BASE64_H__ */

