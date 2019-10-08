/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_FILE_H_
#define _MERCURY_FILE_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  MCFILE_MAX_PATH 255
/**------------------------------------------------------------------*
 **     mcfile access Mode(bit4-bit7)                                   *
 **     only have following choice:                                  *
 **------------------------------------------------------------------*/
#define     MCFILE_ACCESS_MODE_CREATE_NEW       ((uint32)(0x1<<4))
#define     MCFILE_ACCESS_MODE_CREATE_ALWAYS    ((uint32)(0x2<<4))
#define     MCFILE_ACCESS_MODE_OPEN_EXISTING    ((uint32)(0x3<<4))
#define     MCFILE_ACCESS_MODE_OPEN_ALWAYS      ((uint32)(0x4<<4))
#define     MCFILE_ACCESS_MODE_APPEND           ((uint32)(0x5<<4))
/**------------------------------------------------------------------*
 **     mcfile operation Mode(bit0-bit4)                              \
 **------------------------------------------------------------------*/
#define     MCFILE_OPERATE_MODE_READ                ((uint32)(0x1<<0))
#define     MCFILE_OPERATE_MODE_WRITE               ((uint32)(0x1<<1))
#define     MCFILE_OPERATE_MODE_SHARE_READ      ((uint32)(0x1<<2))
#define     MCFILE_OPERATE_MODE_SHARE_WRITE     ((uint32)(0x1<<3))


#define MCFILE_SEEK_BEGIN       0  /*Beginning of file */
#define MCFILE_SEEK_CUR         1  /*Current position of file */
#define MCFILE_SEEK_END         2  /*End of file   */

// file & dir attr
#define MCFILE_ATTR_FILE 0x20    // FILE
#define MCFILE_ATTR_DIR  0x30    // Directory


typedef enum 
{
    FILESYS_CAPACITY_1M = 1,
    FILESYS_CAPACITY_2M,    
    FILESYS_CAPACITY_3M,
    FILESYS_CAPACITY_4M,
    FILESYS_CAPACITY_5M,    
    FILESYS_CAPACITY_6M,
    FILESYS_CAPACITY_7M,
    FILESYS_CAPACITY_8M,
    FILESYS_CAPACITY_9M,
    FILESYS_CAPACITY_10M,    
    FILESYS_CAPACITY_11M,
    FILESYS_CAPACITY_12M,
    FILESYS_CAPACITY_13M,    
    FILESYS_CAPACITY_14M,
    FILESYS_CAPACITY_15M,
    FILESYS_CAPACITY_16M,
    FILESYS_CAPACITY_MAX,
    MERCURY_ENUM_FILESYS_MAX = 0x7fffffff
}FILESYS_CAPACITY_E;


/*
    Find Data Define.
    The receives information about the found file.
*/
typedef struct 
{
    uint8   mday;       // day of the month - [1,31] 
    uint8   mon;        // months  - [1,12] 
    uint16  year;       // years [1980,2107] 
} MCFILE_DATE_T;

typedef struct 
{
    uint8   sec;        // secondsafter the minute - [0,59] 
    uint8   min;        // minutesafter the hour - [0,59] 
    uint8   hour;       // hours since midnight - [0,23] 
}MCFILE_TIME_T;

typedef struct MCFILE_FIND_DATA_TAG
{
    MCFILE_DATE_T   create_Date;
    MCFILE_TIME_T   create_time;
    MCFILE_DATE_T   modify_Date;
    MCFILE_TIME_T   modify_time;
    MCFILE_DATE_T   access_date;
    uint16          attr;                //  SEE MCFILE_ATTR_***
    uint32          length;
    uint16          name[MCFILE_MAX_PATH+1];
    uint8           short_name[13];      // Reserve
}MCFILE_FIND_DATA_T,*LPMCFILE_FIND_DATA_T;

/*****************************************************************************/
//  Description:   init filesystem before use filesystem api
//  Param
//       startAddr:filesystem start adrr
//       cap:filesystem capacity see FILESYS_CAPACITY_E
//  Return:
//       MCFILE_ERROR_NONE: Success
//       Other: Fail
//  Note: 
/*****************************************************************************/
INT InitFileSystem(uint32 startAddr,FILESYS_CAPACITY_E cap);

/*****************************************************************************/
//  Description:   init filesystem before use filesystem api
//  Param
//       startAddr:filesystem start adrr(sector index)
//       fileSysCap:filesystem capacity see FILESYS_CAPACITY_E
//       spiFlashCap:spiflash capacity see FILESYS_CAPACITY_E

//  Return:
//       MCFILE_ERROR_NONE: Success
//       Other: Fail
//  Note: 
/*****************************************************************************/

int InitFileSystemPlus(uint32 startAddr,FILESYS_CAPACITY_E fileSysCap,FILESYS_CAPACITY_E spiFlashCap);


/*****************************************************************************/
//  Description:   uninit filesystem

//  Return:
//       MCFILE_ERROR_NONE: Success
//       Other: Fail
//  Note: 
/*****************************************************************************/
INT UnInitFileSystem(void);

/*****************************************************************************/
//  Description:   Create a directory
//  Param
//       lpPathName:The name of path you want to create ,must be unicode string
//       lpSecurityAttributes:Reserve
//  Return:
//       ERROR_SUCCESS: Success
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
INT CreateDirectory(  LPCTSTR lpPathName,   LPSECURITY_ATTRIBUTES lpSecurityAttributes); 

/*****************************************************************************/
//  Description:   Delete a directory
//  Param
//       path:The name of path you want to create ,must be unicode string
//  Return:
//       ERROR_SUCCESS: Success
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
INT DeleteDirectory(  LPCTSTR lpPathName); 

/*****************************************************************************/
//  Description:   Create or open a file
//  Param
//       lpFileName :The name of path and file ,must be unicode string
//       dwDesiredAccess:MCFILE_ACCESS_*** (only one )and MCFILE_OPERATE_***(mutil)
//       dwShareMode:Reserve set to 0
//       lpSecurityAttributes:Reserve set to NULL
//       dwCreationDisposition:Reserve set to 0
//       dwFlagsAndAttributes:Reserve set to 0
//       hTemplateFile:Reserve set to 0
//  Return:
//       None zero: Success,this value is the handle of file
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
HANDLE CreateFile(
  LPCTSTR lpFileName,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes,
  HANDLE hTemplateFile
);

/*****************************************************************************/
//  Description:   Delete a file
//  Param
//       lpFileName :The name of path and file ,must be unicode string
//  Return:
//       ERROR_SUCCESS: Success
//       MCFILE_ERROR_IO_PENDING:if you call it in asynchronism way,the real result will be given in callback funtion after SFS finish the command
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
INT DeleteFile(  LPCTSTR lpFileName);

/*****************************************************************************/
//  Description:  Find a file that match the param 'find'
//  Param
//       lpFileName:The file name you want to find,such as L"E:\\*.mp3",L"E:\\*.3gp",or L"E:\\123.mp3"...
//       LPMCFILE_FIND_DATA_T: If file is founded ,the infomation of file is stored in this structure 
//  Return:
//       None zero: the file founded ,this find handle can used to find next file match the param 'find'
//       zero: not found
/*****************************************************************************/
HANDLE FindFirstFile(  LPCTSTR lpFileName,  LPMCFILE_FIND_DATA_T lpFindFileData); 

/*****************************************************************************/
//  Description:  Find a next or previous file that match the param 'find' in SFS_FindFirstFile
//  Param
//       hFindFile:The handle returned by SFS_FindFirstFile
//       lpFindFileData: If file is founded ,the infomation of file is stored in this structure 
//  Return:
//       ERROR_SUCCESS: the next or previous file is founded
//       Other: not found
/*****************************************************************************/
INT FindNextFile(   HANDLE hFindFile,  LPMCFILE_FIND_DATA_T lpFindFileData); 

INT FindClose(  HANDLE hFindFile);

/*****************************************************************************/
//  Description:  Flush file
//  Param
//       hFile:The handle returned by SFS_CreateFile
//  Return:
//       ERROR_SUCCESS: Success
//       MCFILE_ERROR_IO_PENDING:if you call it in asynchronism way,the real result will be given in callback funtion after SFS finish the command
//       Other: Fail ,use GetLastError to get detail error msg
//  Note: 
/*****************************************************************************/
INT FlushFileBuffers(HANDLE hFile ); 

/*****************************************************************************/
//  Description:  Get file length
//  Param
//       sfs_handle:The handle returned by CreateFile
//       lpFileSizeHigh:reverse to NULL
//  Return:
//       file size
//  Note: 
/*****************************************************************************/
DWORD GetFileSize(   HANDLE hFile, LPDWORD lpFileSizeHigh); 


/*****************************************************************************/
//  Description:   Rename a file

//  Param
//       sour:The name of path and source file ,must be unicode string
//       dest:The name of path and dest file ,must be unicode string

//  Return:
//       MCFILE_ERROR_NONE: Success
//       MCFILE_ERROR_IO_PENDING:if you call it in asynchronism way,the real result will be given in callback funtion after SFS finish the command
//       Other: Fail
//  Note: 
//       the path of sourcename and destname must be same
/*****************************************************************************/
int RenameFile(const uint16 *sour,const uint16 *dest);


/*****************************************************************************/
//  Description:  Set file length
//  Param
//       hFile:The handle returned by CreateFile
//       size:The length you want to set
//  Return:
//       ERROR_NONE: Success
//       Other: Fail
//  Note: 
//       If param size is less than file length ,some data in the tail of file will be lost
/*****************************************************************************/
int SetFileSize(HANDLE hFile, uint32 size);

/*****************************************************************************/
//  Description:  Get current positon in file
//  Param
//       hFile:The handle returned by CreateFile
//       origin:the absolutely you will be find.It can be MCFILE_SEEK_BEGIN ,MCFILE_SEEK_END
//       *currentpos:If api success ,this will stored the relative posion of origin.
//  Return:
//       ERROR_NONE: Success
//       Other: Fail
//  Note: 
/*****************************************************************************/
int GetFilePointer(    HANDLE hFile, uint32 origin, INT* currentpos);


/*****************************************************************************/
//  Description:  Read file
//  Param
//       hFile:The handle returned by SFS_CreateFile
//       lpBuffer:The data has be read will stored in this buffer 
//       nNumberOfBytesToRead:the number you want to read ,unit is byte
//       lpNumberOfBytesRead:the number you has be read infact
//       lpOverlapped:Reserve set to NULL
//  Return:
//       ERROR_SUCCESS: Success
//       MCFILE_ERROR_IO_PENDING:if you call it in asynchronism way,the real result will be given in callback funtion after SFS finish the command
//       Other: Fail ,use GetLastError to get detail error msg
//  Note: 
/*****************************************************************************/
INT ReadFile(
  HANDLE hFile,
  LPVOID lpBuffer,
  DWORD nNumberOfBytesToRead,
  LPDWORD lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
);

/*****************************************************************************/
//  Description:  Set current positon in file
//  Param
//       hFile:The handle returned by SFS_CreateFile
//       lDistanceToMove:the relative posion of origin.
//       lpDistanceToMoveHigh:Reserve set to NULL
//       dwMoveMethod:the absolutely you will be seek.It can be MCFILE_SEEK_BEGIN ,MCFILE_SEEK_CUR,MCFILE_SEEK_END
//  Return:
//       ERROR_SUCCESS: Success
//       Other: Fail ,use GetLastError to get detail error msg
//  Note: 
/*****************************************************************************/
INT SetFilePointer( 
  HANDLE hFile, 
  LONG lDistanceToMove, 
  PLONG lpDistanceToMoveHigh, 
  DWORD dwMoveMethod
); 

/*****************************************************************************/
//  Description:  Write file
//  Param
//       hFile:The handle returned by SFS_CreateFile
//       lpBuffer:The data will be writen is stored in this buffer 
//       nNumberOfBytesToWrite:the number you want to write ,unit is byte
//       lpNumberOfBytesWritten:the number you has be write infact
//       lpOverlapped:set to NULL
//  Return:
//       ERROR_SUCCESS: Success
//       MCFILE_ERROR_IO_PENDING:if you call it in asynchronism way,the real result will be given in callback funtion after SFS finish the command
//       Other: Fail ,use GetLastError to get detail error msg
//  Note: 
/*****************************************************************************/
INT WriteFile( 
  HANDLE hFile, 
  LPCVOID lpBuffer, 
  DWORD nNumberOfBytesToWrite, 
  LPDWORD lpNumberOfBytesWritten, 
  LPOVERLAPPED lpOverlapped
); 

INT CloseHandle(  HANDLE hFile);
// format disk  about 10s
INT FomatDisk(void);

/*****************************************************************************/
//  Description:   Get disk free space
//  Param
//       pDiskFreeSize:set to dev free size
//  Return:
//       MCFILE_ERROR_NONE: Success
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
INT GetDeviceFreeSpace(uint32 * pDiskFreeSize);

/*****************************************************************************/
//  Description:   Get disk used space
//  Param
//       pDiskUsedSize:set to dev used size
//  Return:
//       MCFILE_ERROR_NONE: Success
//       Other: Fail ,use GetLastError to get detail error msg
/*****************************************************************************/
INT GetDeviceUsedSpace(uint32 * pDiskUsedSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif //_MERCURY_FILE_H_

