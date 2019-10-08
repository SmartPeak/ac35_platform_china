/*****************************************************************************
*  QR and P90 Basic applib file IO definition header                         *
*  Copyright (C) 2019 Shanghai Basewin Technology Co.,Ltd.                   *
*                                                                            *
*  This file is part of applib.                                              *
*                                                                            *
*  @file     uFile.h                                                         *
*  @brief    applib file IO definition                                       *
*  Details.                                                                  *
*                                                                            *
*  @author   XuZhou.Chen                                                     *
*  @version  1.0.0                                                           *
*  @date     25/10/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  25/10/2018 | 1.0.0     | XuZhou.Chen    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef UFILE_H
#define UFILE_H


/**
 * @defgroup file file
 * @brief applib file IO related interface
 * @{
 */
 
 /**
 * @defgroup struct struct
 * @brief applib file IO related enum
 * @{
 */
 
typedef enum
{
    DBA_RFile = 0,      ///< file type (read)
    DFA_DataDB,         ///< trans db (read/write)
    DFA_RecordDB        ///< trans data table (read/write)
}DATA_FILE_ATTR;

typedef struct
{
    unsigned short fileVer;     ///< version(+1 while changed)
    DATA_FILE_ATTR attr;
    char fileName[30];
    unsigned char *fileData;
    unsigned int fileSize;
    int (*loadDefData)(unsigned int fileIndex);
}DATA_FILE_INFO;

typedef struct _DB_EXEC
{
    unsigned char   exitLoop;           /*!< flag: exit exec loop */
    unsigned int    count;              /*!< */
    unsigned int    currIndex;
    unsigned char   *recordData;
    unsigned int    recordDataSize;
    unsigned char   *inData;
    unsigned char   *outData;
    int (*execFunc)(struct _DB_EXEC *pExec);
}tsDBExec;

/*!< file error code */
typedef enum
{
    UFILE_UPDATE_FAIL   = -11,  /*!< update file fail */
    UFILE_NO_EXIST      = -10,  /*!< file exist*/
    UFILE_PARAERROR     = -9,   /*!< param error */
    UFILE_NO_RECORD     = -8,   /*!< record no find */
    UFILE_REMOVE_FAIL   = -7,   /*!< remove file fail */
    UFILE_CLOSE_FAIL    = -6,   /*!< close file fail */
    UFILE_DELETE_FAIL   = -5,   /*!< delete file record fail */
    UFILE_READ_FAIL     = -4,   /*!< read file fail */
    UFILE_WRITE_FAIL    = -3,   /*!< write file fail */
    UFILE_CREATE_FAIL   = -2,   /*!< file create fail */
    UFILE_OPEN_FAIL     = -1,   /*!< file open fail */
    UFILE_SUCCESS       = 0     /*!< success */
}FileRet;

/** @} */

/**
 * @defgroup interface interface
 * @brief file related interface
 * @{
 */
 
/**
 * @brief get file error code
 * @retval error code
 */
int UFile_GetErrCode(void);

/**
 * @brief check file exist
 * @param fileIndex [in] file index
 * @retval FileRet
 */
int UFile_CheckValidFile(unsigned int fileIndex);

/**
 * @brief check file exist of all
 * @param fileInfoList [in] file lists
 * @param fileCount [in] number of files
 * @retval FileRet
 */
int UFile_CheckAllValidFiles(DATA_FILE_INFO fileInfoList[], unsigned int fileCount);

/**
 * @brief read file
 * @param _fileName [in] file name
 * @param _offset   [in] offse
 * @param _fileData [out] file pointer address
 * @param _fileSize [in] read size
 * @retval FileRet
 */
int UFile_ReadFileEx(const char *_fileName, unsigned int _offset, unsigned char *_fileData, unsigned int _fileSize);

/**
 * @brief read file
 * @param _fileName [in] file name
 * @param _offset   [in] offse
 * @param _fileData [out] file pointer address
 * @param _fileSize [in] write data size
 * @retval FileRet
 */
int UFile_WriteFileEx(const char *_fileName, unsigned int _offset, unsigned char *_fileData, unsigned int _fileSize);

/**
 * @brief read file
 * @param fileName [in] file name
 * @param fileData [out] file data pointer address
 * @retval FileRet
 */
int UFile_ReadFileToMalloc(const char *fileName, char **fileData);

/**
 * @brief get resource
 * @param sourceName [in] resource name
 * @param width [out] resource width
 * @param heightth [out] resource height
 * @retval resource data
 */
char *UFile_GetResource(char* sourceName, int* width, int* height);

/**
 * @brief remove file
 * @param fileName [in] file name
 * @retval FileRet
 */
int UFile_RemoveFile(const char *fileName);

/**
 * @brief clear file
 * @param fileName [in] file name
 * @retval FileRet
 */
int UFile_ClearFile(const char *fileName);

/**
 * @brief read file
 * @param fileName [in] file name
 * @param fileData [out] file pointer address
 * @param fileSize [in] read size
 * @retval FileRet
 */
int UFile_ReadFile(const char *fileName, unsigned char *fileData, unsigned int fileSize);

/**
 * @brief write file
 * @param fileName [in] file name
 * @param fileData [in] file pointer address
 * @param fileSize [in] write data size
 * @retval FileRet
 */
int UFile_WriteFile(const char *fileName, unsigned char *fileData, unsigned int fileSize);

/**
 * @brief search record
 * @param fileIndex [in] file name
 * @param pExec [in/out] file exec
 * @retval FileRet
 */
int UFile_SearchRecord(const char *fileName, tsDBExec *pExec);

/**
 * @brief read record
 * @param fileName [in] file name
 * @param recordIndex [in] record index
 * @param dat [out] file pointer address
 * @param datLen [in] read data size
 * @retval FileRet
 */
int UFile_ReadRecord(const char *fileName, unsigned int recordIndex, unsigned char *dat, int datLen);

/**
 * @brief write record
 * @param fileName [in] file name
 * @param recordIndex [in] record index
 * @param dat [in] file pointer address
 * @param datLen [in] write data size
 * @retval FileRet
 */
int UFile_WriteRecord(const char *fileName, unsigned int recordIndex, unsigned char *dat, int datLen);

/**
 * @brief remove file of all
 * @retval FileRet
 */
int UFile_RemoveFileAll(void);

/**
 * @brief remove file
 * @param fileIndex [in] file index
 * @retval FileRet
 */
int UFile_RemoveFileIndexOf(unsigned int fileIndex);

/**
 * @brief clear file
 * @param fileIndex [in] file index
 * @retval FileRet
 */
int UFile_ClearFileIndexOf(unsigned int fileIndex);

/**
 * @brief read file
 * @param fileIndex [in] file index
 * @retval FileRet
 */
int UFile_ReadFileIndexOf(unsigned int fileIndex);

/**
 * @brief write file
 * @param fileIndex [in] file index
 * @retval FileRet
 */
int UFile_WriteFileIndexOf(unsigned int fileIndex);

/**
 * @brief read record
 * @param fileName [in] file name
 * @param recordIndex [in] record index
 * @retval FileRet
 */
int UFile_ReadRecordIndexOf(unsigned int fileIndex, unsigned int recordIndex);

/**
 * @brief write record
 * @param fileIndex [in] file index
 * @param recordIndex [in] record index
 * @retval FileRet
 */
int UFile_WriteRecordIndexOf(unsigned int fileIndex, unsigned int recordIndex);

/**
 * @brief search record
 * @param fileIndex [in] file index
 * @param pExec [in/out] file exec
 * @retval FileRet
 */
int UFile_SearchRecordIndexOf(unsigned int fileIndex, tsDBExec *pExec);

/** @} */

/** @} */

#endif // UFILE_H
