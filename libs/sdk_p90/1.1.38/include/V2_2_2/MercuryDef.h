/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/

#ifndef __MERCURY_DEF_H__
#define __MERCURY_DEF_H__

#ifdef MERCURY_GCC
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#else
#include "stdlib.h"
#include "stdarg.h"
#include "rt_fp.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef INT32
typedef signed long INT32;
#endif

#ifndef LONG
typedef signed long LONG;
#endif

#ifndef HANDLE
typedef unsigned int HANDLE;
#endif

#ifndef LPOVERLAPPED
typedef void* LPOVERLAPPED ;
#endif

#ifndef PLONG
typedef signed long  *PLONG;
#endif

#ifndef uint8
typedef unsigned char       uint8;
#endif

#ifndef uint16
typedef unsigned short      uint16;
#endif

#ifndef uint32
typedef unsigned int        uint32;
#endif




#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef BOOLEAN
typedef int BOOLEAN;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef FLOAT
typedef float FLOAT;
#endif

#ifndef PFLOAT
typedef FLOAT *PFLOAT;
#endif

#ifndef PBOOL
typedef BOOL  *PBOOL;
#endif

#ifndef LPBOOL
typedef BOOL  *LPBOOL;
#endif

#ifndef PBYTE
typedef BYTE  *PBYTE;
#endif

#ifndef LPBYTE
typedef BYTE  *LPBYTE;
#endif

#ifndef PINT
typedef int  *PINT;
#endif

#ifndef LPINT
typedef int  *LPINT;
#endif

#ifndef PWORD
typedef WORD  *PWORD;
#endif

#ifndef LPWORD
typedef WORD  *LPWORD;
#endif

#ifndef LPLONG
typedef long  *LPLONG;
#endif

#ifndef PDWORD
typedef DWORD  *PDWORD;
#endif

#ifndef LPDWORD
typedef DWORD  *LPDWORD;
#endif

#ifndef LPVOID
typedef  void*   LPVOID;
#endif

#ifndef LPCVOID
typedef const void  *LPCVOID;
#endif

#ifndef INT
typedef int INT;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef PUINT
typedef unsigned int *PUINT;
#endif

#ifndef LPTSTR
typedef const char* LPTSTR;
#endif

#ifndef LPCTSTR
typedef const unsigned short* LPCTSTR;
#endif

#ifndef HLOCAL
typedef void* HLOCAL;
#endif

#ifndef PVOID
typedef void* PVOID;
#endif

#ifndef VOID
typedef void VOID;
#endif

#ifndef SIZE_T
typedef size_t SIZE_T;
#endif

#ifndef HWND
typedef void* HWND;
#endif

#ifndef ULONG_PTR
typedef unsigned long* ULONG_PTR;
#endif

#ifndef ULONG
typedef  unsigned long  ULONG;
#endif

typedef void* TIMER_PTR;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTE;

typedef  SECURITY_ATTRIBUTE* LPSECURITY_ATTRIBUTES;

#define TRUE     1
#define FALSE    0

typedef WORD wchar;

typedef struct
{
    //ARM string.h
    void*    (*Memcpy)   ( void *dst, const void *src, size_t count );
    void*    (*Memmove)  ( void *dst, const void *src, size_t count );
    char*    (*Strcpy)   ( char *dst, const char *src );
    char*    (*Strncpy)  ( char *dst, const char *src, size_t count );
    char*    (*Strcat)   ( char *dst, const char *src );
    char*    (*Strncat)  ( char *dst, const char *src, size_t count );
    int      (*Memcmp)   ( const void *src1, const void *src2, size_t count );
    int      (*Strcmp)   ( const char *src1, const char *src2 );
    int      (*Strncmp)  ( const char *src1, const char *src2, size_t count );
    int      (*Strcoll)  ( const char *src1, const char *src2 );
    size_t   (*Strxfrm)  ( char *dst, const char *src, size_t count );
    void*    (*Memchr)   ( const void * src, int ch, size_t count );
    char*    (*Strchr)   ( const char *src, int ch );
    size_t   (*Strcspn)  ( const char *src1, const char *src2 );
    char*    (*Strpbrk)  ( const char *src1, const char *src2 );
    char*    (*Strrchr)  ( const char *src, int ch );
    size_t   (*Strspn)   ( const char *src1, const char *src2 );
    char*    (*Strstr)   ( const char *src1, const char *src2 );
    char*    (*Strtok)   ( char *src1, const char *src2 );
    void*    (*Memset)   ( void *dst, int value, size_t count );
    char*    (*Strerror) ( int errnum );
    size_t   (*Strlen)   ( const char *src );

    //ARM ctype.h
    int      (*Isalpha)  ( int ch );
    int      (*Iscntrl)  ( int ch );
    int      (*Isgraph)  ( int ch );
    int      (*Islower)  ( int ch );
    int      (*Isprint)  ( int ch );
    int      (*Ispunct)  ( int ch );
    int      (*Isspace)  ( int ch );
    int      (*Isupper)  ( int ch );
    int      (*Isxdigit) ( int ch );
    int      (*Tolower)  ( int ch );
    int      (*Toupper)  ( int ch );

    //ARM stdlib.h
    int      (*Atoi)     ( const char *string );
    long int (*Atol)     ( const char *string );
    long int (*Strtol)   ( const char * nptr, char ** endptr, int base );
    unsigned long int  (*Strtoul) (const char * nptr,char ** endptr, int base );
    int      (*Rand)     ( void );
    void     (*Srand)    ( unsigned int seed );
    void     (*Qsort)    ( void * base, size_t num, size_t size,int (* compar)( const void *, const void * ) );

     //ARM stdio.h
    int      (*Sprintf)  ( char *string, const char *format, ... );
    int      (*Vsprintf) ( char *string, const char *format, va_list arg );
    int      (*Vsnprintf)(char* str, size_t size, const char* format, va_list ap);

    //wstring
    wchar*   (*Wstrcpy)  ( wchar *dst, const wchar *src );
    wchar*   (*Wstrncpy) ( wchar *dst, const wchar *src, size_t count );
    wchar*   (*Wstrcat)  ( wchar *dst, const wchar *src );
    wchar*   (*Wstrncat) ( wchar *dst, const wchar *src, size_t count );
    int      (*Wstrcmp)  ( const wchar *src1, const wchar *src2 );
    int      (*Wstrncmp) ( const wchar *src1, const wchar *src2, size_t count );
    size_t   (*Wstrlen)  ( const wchar *src );

    //Exceptions
    void (*rt_raise)(int /*sig*/, int /*type*/);
}MERCURY_C_STD_FUN_S;

extern MERCURY_C_STD_FUN_S* pCStdFun;

//string
#define memcpy                 pCStdFun->Memcpy
#define memmove                pCStdFun->Memmove
#define strcpy                 pCStdFun->Strcpy
#define strncpy                pCStdFun->Strncpy
#define strcat                 pCStdFun->Strcat
#define strncat                pCStdFun->Strncat
#define memcmp                 pCStdFun->Memcmp
#define strcmp                 pCStdFun->Strcmp
#define strncmp                pCStdFun->Strncmp
#define strcoll                pCStdFun->Strcoll
#define strxfrm                pCStdFun->Strxfrm
#define memchr                 pCStdFun->Memchr
#define strchr                 pCStdFun->Strchr
#define strcspn                pCStdFun->Strcspn
#define strpbrk                pCStdFun->Strpbrk
#define strrchr                pCStdFun->Strrchr
#define strspn                 pCStdFun->Strspn
#define strstr                 pCStdFun->Strstr
#define strtok                 pCStdFun->Strtok
#define memset                 pCStdFun->Memset
#define strerror               pCStdFun->Strerror
#define strlen                 pCStdFun->Strlen

//ctype
#define isalpha                pCStdFun->Isalpha
#define iscntrl                pCStdFun->Iscntrl
#define isgraph                pCStdFun->Isgraph
#define islower                pCStdFun->Islower
#define ispunct                pCStdFun->Ispunct
#define isprint                pCStdFun->Isprint
#define isspace                pCStdFun->Isspace
#define isupper                pCStdFun->Isupper
#define isxdigit               pCStdFun->Isxdigit
#define tolower                pCStdFun->Tolower
#define toupper                pCStdFun->Toupper

//stdlib                      
#define atoi                   pCStdFun->Atoi
#define atol                   pCStdFun->Atol
#define strtol                 pCStdFun->Strtol
#define strtoul                pCStdFun->Strtoul
#define rand                   pCStdFun->Rand
#define srand                  pCStdFun->Srand
#define qsort                  pCStdFun->Qsort

//stdio                    
#define sprintf                pCStdFun->Sprintf
#define vsprintf               pCStdFun->Vsprintf
#define vsnprintf              pCStdFun->Vsnprintf

//wstring
#define wcscpy                 pCStdFun->Wstrcpy
#define wcsncpy                pCStdFun->Wstrncpy
#define wcscat                 pCStdFun->Wstrcat
#define wcsncat                pCStdFun->Wstrncat
#define wcscmp                 pCStdFun->Wstrcmp
#define wcsncmp                pCStdFun->Wstrncmp
#define wcslen                 pCStdFun->Wstrlen

// 以下3个接口是由BWSDK提供的实现，不使用libc中的东西
#define snprintf               BW_snprintf
#define strcasecmp             BW_strcasecmp
#define strncasecmp            BW_strncasecmp

// 以下接口将内存申请释放进行封装，不能直接使用系统提供的接口
void* BWSDK_malloc(UINT uiSize);
void BWSDK_free(void* pvPointer);
void BWSDK_heapInfoDump(void);
char *BWSDK_strdup(const char *s);

#define malloc(uiSize) BWSDK_malloc(uiSize)
#define free(pvPointer) BWSDK_free(pvPointer)
#define heapcheck() BWSDK_heapInfoDump()
#define strdup(s) BWSDK_strdup(s)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
