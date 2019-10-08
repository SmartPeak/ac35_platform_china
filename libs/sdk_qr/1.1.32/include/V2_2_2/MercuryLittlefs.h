/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/
#ifndef _MERCURY_LITTLEFS_H_
#define _MERCURY_LITTLEFS_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// Max name size in bytes
#ifndef LFS_NAME_MAX
#define LFS_NAME_MAX 255
#endif

typedef enum 
{
    LITTLEFS_CAPACITY_1M = 1,
    LITTLEFS_CAPACITY_2M,    
    LITTLEFS_CAPACITY_3M,
    LITTLEFS_CAPACITY_4M,
    LITTLEFS_CAPACITY_5M,    
    LITTLEFS_CAPACITY_6M,
    LITTLEFS_CAPACITY_7M,
    LITTLEFS_CAPACITY_8M,
    LITTLEFS_CAPACITY_9M,
    LITTLEFS_CAPACITY_10M,    
    LITTLEFS_CAPACITY_11M,
    LITTLEFS_CAPACITY_12M,
    LITTLEFS_CAPACITY_13M,    
    LITTLEFS_CAPACITY_14M,
    LITTLEFS_CAPACITY_15M,
    LITTLEFS_CAPACITY_16M,
    LITTLEFS_CAPACITY_MAX,
    MERCURY_ENUM_LITTLEFS_MAX = 0x7fffffff
}LITTLEFS_CAPACITY_E;

// File open flags
enum lfs_open_flags {
    // open flags
    LFS_O_RDONLY = 1,        // Open a file as read only
    LFS_O_WRONLY = 2,        // Open a file as write only
    LFS_O_RDWR   = 3,        // Open a file as read and write
    LFS_O_CREAT  = 0x0100,   // Create a file if it does not exist
    LFS_O_EXCL   = 0x0200,   // Fail if a file already exists
    LFS_O_TRUNC  = 0x0400,   // Truncate the existing file to zero size
    LFS_O_APPEND = 0x0800,   // Move to end of file on every write

    // internally used flags
    LFS_F_DIRTY   = 0x10000, // File does not match storage
    LFS_F_WRITING = 0x20000, // File has been written since last flush
    LFS_F_READING = 0x40000, // File has been read since last flush
    LFS_F_ERRED   = 0x80000, // An error occurred during write
    MERCURY_ENUM_LFS_OPEN_FLAGS = 0x7fffffff
};

// File seek flags
typedef enum lfs_whence_flags {
    LFS_SEEK_SET = 0,   // Seek relative to an absolute position
    LFS_SEEK_CUR = 1,   // Seek relative to the current file position
    LFS_SEEK_END = 2,   // Seek relative to the end of the file
    LFS_WHENCE_FLAGS_MAX = 0x7fffffff
}LFS_WHENCE_FLAGS;


// Type definitions
typedef uint32 lfs_size_t;
typedef uint32 lfs_off_t;
typedef uint32 lfs_ssize_t;
typedef uint32 lfs_soff_t;
typedef uint32 lfs_block_t;
extern struct lfs_config;
extern struct lfs_file_config;
    
typedef struct lfs_free {
    lfs_block_t off;
    lfs_block_t size;
    lfs_block_t index;
    lfs_block_t ack;
    uint32 *buffer;
} lfs_free_t;

typedef struct lfs_cache {
    lfs_block_t block;
    lfs_off_t off;
    uint8 *buffer;
} lfs_cache_t;

typedef struct lfs_file {
    struct lfs_file *next;
    lfs_block_t pair[2];
    lfs_off_t poff;

    lfs_block_t head;
    lfs_size_t size;

    const struct lfs_file_config *cfg;
    uint32 flags;
    lfs_off_t pos;
    lfs_block_t block;
    lfs_off_t off;
    lfs_cache_t cache;
} lfs_file_t;

typedef struct lfs_dir {
    struct lfs_dir *next;
    lfs_block_t pair[2];
    lfs_off_t off;

    lfs_block_t head[2];
    lfs_off_t pos;

    struct lfs_disk_dir {
        uint32 rev;
        lfs_size_t size;
        lfs_block_t tail[2];
    } d;
} lfs_dir_t;

// File types
enum lfs_type {
    LFS_TYPE_REG        = 0x11,
    LFS_TYPE_DIR        = 0x22,
    LFS_TYPE_SUPERBLOCK = 0x2e,
};

// File info structure
struct lfs_info {
    // Type of the file, either LFS_TYPE_REG or LFS_TYPE_DIR
    uint8 type;
    // Size of the file, only valid for REG files
    lfs_size_t size;
    // Name of the file stored as a null-terminated string
    char name[LFS_NAME_MAX+1];
};

// The littlefs type
typedef struct lfs {
    const struct lfs_config *cfg;

    lfs_block_t root[2];
    lfs_file_t *files;
    lfs_dir_t *dirs;

    lfs_cache_t rcache;
    lfs_cache_t pcache;

    lfs_free_t free;
    BOOLEAN deorphaned;
    BOOLEAN moving;
} lfs_t;

extern int LittlefsInit(uint32 offsetBlock, LITTLEFS_CAPACITY_E fileSysCap, LITTLEFS_CAPACITY_E spiFlashCap);
extern int LittlefsDeinit(void);
//多级目录需要一级一级多次创建，不能一次建立
extern int LittlefsCreateDir(const char *path);
extern int LittlefsOpenDir(lfs_dir_t * dir,const char *path);

//有索引到文件返回1，没有则返回0，其他出错
extern int LittlefsReadDir(lfs_dir_t *cwd, struct lfs_info *fileInfo);
extern int LittlefsCloseDir(lfs_dir_t *cwd);
extern int LittlefsOpenFile(lfs_file_t *file, const char *path, int openFlags);
extern int LittlefsReadFile(lfs_file_t *file, void *buffer, uint32 size, uint32 *readLen);
extern int LittlefsWriteFile(lfs_file_t *file,const void *buffer, uint32 size, uint32 *lenWritten);
extern int LittlefsCloseFile(lfs_file_t *file);
extern int LittlefsGetFilePointer(lfs_file_t *file);
extern int LittlefsSetFilePointer(lfs_file_t *file, int offset, int whence, int *position);
extern int LittlefsDelete(char *path);
extern int LittlefsFlushFile(lfs_file_t *file);
extern int LittlefsGetFileSize(lfs_file_t *file);
extern int LittlefsSetFileSize(lfs_file_t *file, uint32 size);
extern int LittlefsRename(const char *oldname, const char *newname);
extern int LittlefsFormat(void);
extern int LittlefsDeviceFreeSpace(uint32 *pFreeSize);
extern int LittlefsDeviceUsedSpace(uint32 *pUsedSize);
extern int LittlefsGetType(lfs_t *littlefs);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*_MERCURY_LITTLEFS_H_*/
