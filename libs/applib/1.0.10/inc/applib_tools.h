#ifndef TOOLS_H_
#define TOOLS_H_

void tools_asc_bcd(unsigned char *pucDest, unsigned int uiDestLen, unsigned char *pucSrc, unsigned int uiSrcLen);
void tools_asc_hex(unsigned char *pucDest, unsigned int uiDestLen, unsigned char *pucSrc, unsigned int uiSrcLen);
unsigned long tools_asc_long(unsigned char *pucSrc, unsigned int uiLen);
void tools_bcd_asc(unsigned char *pucDest, unsigned char *pucSrc, int uiDestLen);
unsigned long tools_bcd_long(unsigned char *pucSrc, unsigned int uiSrcLen);
void tools_bcd_str(unsigned char *pucDest, unsigned char *pucSrc, int uiDestLen);
void tools_char_asc(unsigned char *pucDest, unsigned char ucLen, unsigned char *pucSrc);
void tools_char_bcd(unsigned char *pucDest, unsigned char ucLen, unsigned char *pucSrc);
void tools_char_str(unsigned char *pucDest, unsigned char ucLen, unsigned char *pucSrc);
unsigned char tools_char_hex(unsigned char ucCh);
void tools_hex_asc(unsigned char *pucDest, unsigned char *pucSrc, unsigned int uiLen);
void tools_hex_str(unsigned char *pucDest, unsigned char *pucSrc, unsigned int uiLen);
unsigned long tools_hex_long(unsigned char *pucSrc, unsigned int uiLen);
void tools_int_asc(unsigned char *pucDest, unsigned int uiLen, unsigned int *puiSrc);
void tools_int_bcd(unsigned char *pucDest, unsigned int uiLen, unsigned int *puiSrc);
void tools_int_hex(unsigned char *pucDest, unsigned int uiLen, unsigned int *puiSrc);
void tools_int_str(unsigned char *pucDest, unsigned int uiLen, unsigned int *puiSrc);
void tools_long_asc(unsigned char *pucDest, unsigned int uiLen, unsigned long *pulSrc);
void tools_long_bcd(unsigned char *pucDest, unsigned int uiLen, unsigned long *pulSrc);
void tools_long_hex(unsigned char *pucDest, unsigned int uiLen, unsigned long *pulSrc);
void tools_long_str(unsigned char *pucDest, unsigned int uiLen, unsigned long *pulSrc);
void tools_short_asc(unsigned char *pucDest, unsigned int uiLen, unsigned short *puiSrc);
void tools_short_bcd(unsigned char *pucDest, unsigned int uiLen, unsigned short *puiSrc);
void tools_short_hex(unsigned char *pucDest, unsigned int uiLen, unsigned short *puiSrc);
void tools_short_str(unsigned char *pucDest, unsigned int uiLen, unsigned short *puiSrc);
void tools_str_bcd(unsigned char *pucDest, unsigned int uiDestLen, unsigned char *pucSrc);
void tools_str_hex(unsigned char *pucDest, unsigned int uiDestLen, unsigned char *pucSrc);
unsigned long tools_str_long(unsigned char *pucSrc);
void tools_str_lowcase(char *pcStr);
void tools_str_uppercase(char *pcStr);


#endif

