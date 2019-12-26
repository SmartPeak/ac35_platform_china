#ifndef _UTILES_H
#define _UTILES_H

int isUtf8(char *s, int ns);

// ת��������
int utilsAsc2Int(char *s);

int utilsAsc2BcdPrefix(unsigned char *ascii, unsigned int ascLen, unsigned char *bcd);

int utilsAsc2Bcd(unsigned char *ascii, unsigned int ascLen, unsigned char *bcd);

int utilsBcd2Asc(unsigned char *bcd, unsigned int bcdLen, unsigned char *ascii);

void utilsLong2Asc(long sour, char nums, char *dest);

/**
 * ��IP�ַ���תΪ�޷�������
 */
unsigned long utilsIp2Long(const char *ip);

#endif
