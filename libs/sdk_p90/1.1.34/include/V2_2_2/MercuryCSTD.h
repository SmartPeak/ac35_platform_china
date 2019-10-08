/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/

#ifndef __MERCURY_CSTD_H__
#define __MERCURY_CSTD_H__

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef int (* COMPAR)( const void *, const void * );

void* memcpy_m( void *dst, const void *src, size_t count );
void* memmove_m( void *dst, const void *src, size_t count );
char*  strcpy_m( char *dst, const char *src );
char* strncpy_m( char *dst, const char *src, size_t count );
char* strcat_m(char* dst, const char* src);
char* strncat_m(char* dst, const char* src,  size_t count);
int memcmp_m(const void* src1, const void* src2, size_t count);
int strcmp_m(const char* src1, const char* src2);
int strncmp_m(const char* src1, const char* src2, size_t count);
int strcoll_m(const char* src1, const char* src2);
size_t strxfrm_m(char* dst, const char* src, size_t count);
void* memchr_m(const void* src, int ch, size_t count);
char* strchr_m(const char* src, int ch);
size_t strcspn_m(const char* src1, const char* src2);
char* strpbrk_m(const char* src1, const char* src2);
char* strrchr_m(const char* src, int ch);
size_t strspn_m(const char* src1, const char* src2);
char* strstr_m(const char* src1, const char* src2);
char* strtok_m(char* src1, const char* src2);
void* memset_m(void* dst, int value, size_t count);
char* strerror_m(int errnum);
size_t strlen_m(const char* src);

//ARMctype.h
int isalpha_m(int ch);
int iscntrl_m(int ch);
int isgraph_m(int ch);
int islower_m(int ch);
int isprint_m(int ch);
int ispunct_m(int ch);
int isspace_m(int ch);
int isupper_m(int ch);
int isxdigit_m(int ch);
int tolower_m(int ch);
int toupper_m(int ch);

//ARMstdlib.h
int atoi_m(const char*string);
long int atol_m(const char*string);
long int strtol_m(const char*nptr, char** endptr, int base);
unsigned long int strtoul_m(const char* nptr, char** endptr, int base);
int rand_m(void);
void srand_m(unsigned int seed);
void qsort_m(void* base, size_t num, size_t size,  COMPAR par);

//ARMstdio.h
int vsprintf_m(char* string, const char* format, va_list arg);
int vsnprintf_m(char* str, size_t size, const char* format, va_list ap);

//wstring
wchar* wstrcpy_m(wchar* dst, const wchar* src);
wchar* wstrncpy_m(wchar* dst, const wchar* src, size_t count);
wchar* wstrcat_m(wchar* dst, const wchar* src);
wchar* wstrncat_m(wchar* dst, const wchar* src, size_t count);
int wstrcmp_m(const wchar* src1, const wchar* src2);
int wstrncmp_m(const wchar* src1, const wchar* src2, size_t count);
size_t wstrlen_m(const wchar* src);

//Exceptions
void rt_raise(int sig, int type);

#if 0
#define sprintf_m  pCStdFun->Sprintf
#define sprintf  pCStdFun->Sprintf
#define memcpy        memcpy_m
#define memmove       memmove_m
#define strcpy        strcpy_m
#define strncpy       strncpy_m
#define strcat        strcat_m
#define strncat       strncat_m
#define memcmp        memcmp_m
#define strcmp        strcmp_m
#define strncmp       strncmp_m
#define strcoll       strcoll_m
#define strxfrm       strxfrm_m
#define memchr        memchr_m
#define strchr        strchr_m
#define strcspn       strcspn_m
#define strpbrk        strpbrk_m
#define strrchr       strrchr_m
#define strspn        strspn_m
#define strstr        strstr_m
#define strtok        strtok_m
#define memset        memset_m
#define strerror      strerror_m
#define strlen        strlen_m
#define isalpha       isalpha_m
#define iscntrl       iscntrl_m
#define isgraph       isgraph_m
#define islower       islower_m
#define isprint       isprint_m
#define ispunct       ispunct_m
#define isspace       isspace_m
#define isupper       isupper_m
#define isxdigit      isxdigit_m
#define tolower       tolower_m
#define toupper       toupper_m
#define atoi          atoi_m
#define atol          atol_m
#define strtol        strtol_m
#define strtoul       strtoul_m
#define rand          rand_m
#define srand         srand_m
#define qsort         qsort_m
#define vsprintf      vsprintf_m
#define vsnprintf     vsnprintf_m
#define wstrcpy       wstrcpy_m
#define wstrncpy      wstrncpy_m
#define wstrcat       wstrcat_m
#define wstrncat      wstrncat_m
#define wstrcmp       wstrcmp_m
#define wstrncmp      wstrncmp_m
#define wstrlen       wstrlen_m
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
