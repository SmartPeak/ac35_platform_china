#ifndef _UTILES_H
#define _UTILES_H

int isUtf8(char *s, int ns);

// 转换成整数
int utilsAsc2Int(char *s);

int utilsAsc2BcdPrefix(unsigned char *ascii, unsigned int ascLen, unsigned char *bcd);

int utilsAsc2Bcd(unsigned char *ascii, unsigned int ascLen, unsigned char *bcd);

int utilsBcd2Asc(unsigned char *bcd, unsigned int bcdLen, unsigned char *ascii);

void utilsLong2Asc(long sour, char nums, char *dest);

/**
 * 将IP字符串转为无符号整数
 */
unsigned long utilsIp2Long(const char *ip);

#endif
