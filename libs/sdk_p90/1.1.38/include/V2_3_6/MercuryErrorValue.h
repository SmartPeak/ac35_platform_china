/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_ERROE_VALUE_H_
#define _MERCURY_ERROE_VALUE_H_


#define ERROR_FAILE                                    -1
/***System Errors ***/
#define ERROR_SUCCESS                               0           /*  The operation completed successfully.   */
#define ERROR_INVALID_FUNCTION                      1           /*  Incorrect function. */
#define ERROR_FILE_NOT_FOUND                        2           /*  The system cannot find the file specified.  */
#define ERROR_PATH_NOT_FOUND                        3           /*  The system cannot find the path specified.  */
#define ERROR_TOO_MANY_OPEN_FILES                   4           /*  The system cannot open the file.    */
#define ERROR_ACCESS_DENIED                         5           /*  Access is denied.   */
#define ERROR_INVALID_HANDLE                        6           /*  The handle is invalid.  */
#define ERROR_ARENA_TRASHED                         7           /*  The storage control blocks were destroyed.  */
#define ERROR_NOT_ENOUGH_MEMORY                     8           /*  Not enough storage is available to process this command.    */
#define ERROR_INVALID_BLOCK                         9           /*  The storage control block address is invalid.   */
#define ERROR_BAD_ENVIRONMENT                       10          /*  The environment is incorrect.   */
#define ERROR_BAD_FORMAT                            11          /*  An attempt was made to load a program with an incorrect format. */
#define ERROR_INVALID_ACCESS                        12          /*  The access code is invalid. */
#define ERROR_INVALID_DATA                          13          /*  The data is invalid.    */
#define ERROR_OUTOFMEMORY                           14          /*  Not enough storage is available to complete this operation. */
#define ERROR_INVALID_DRIVE                         15          /*  The system cannot find the drive specified. */
#define ERROR_CURRENT_DIRECTORY                     16          /*  The directory cannot be removed.    */
#define ERROR_NOT_SAME_DEVICE                       17          /*  The system cannot move the file to a different disk drive.  */
#define ERROR_NO_MORE_FILES                         18          /*  There are no more files.    */
#define ERROR_WRITE_PROTECT                         19          /*  The media is write protected.   */
#define ERROR_BAD_UNIT                              20          /*  The system cannot find the specified device.    */
#define ERROR_NOT_READY                             21          /*  The device is not ready.    */
#define ERROR_BAD_COMMAND                           22          /*  The device does not recognize the command.  */
#define ERROR_CRC                                   23          /*  Data error (cyclic redundancy check).   */
#define ERROR_BAD_LENGTH                            24          /*  The program issued a command but the command length is incorrect.   */
#define ERROR_SEEK                                  25          /*  The drive cannot locate a specific area or track on the disk.   */
#define ERROR_NOT_DOS_DISK                          26          /*  The specified disk or diskette cannot be accessed.  */
#define ERROR_SECTOR_NOT_FOUND                      27          /*  The drive cannot find the sector requested. */
#define ERROR_OUT_OF_PAPER                          28          /*  The printer is out of paper.    */
#define ERROR_WRITE_FAULT                           29          /*  The system cannot write to the specified device.    */
#define ERROR_READ_FAULT                            30          /*  The system cannot read from the specified device.   */
#define ERROR_GEN_FAILURE                           31          /*  A device attached to the system is not functioning. */
#define ERROR_SHARING_VIOLATION                     32          /*  The process cannot access the file because it is being used by another process. */
#define ERROR_LOCK_VIOLATION                        33          /*  The process cannot access the file because another process has locked a portion of the file.    */
#define ERROR_WRONG_DISK                            34          /*  The wrong diskette is in the drive. Insert %2 (Volume Serial Number: %3) into drive %1. */
#define ERROR_SHARING_BUFFER_EXCEEDED               36          /*  Too many files opened for sharing.  */
#define ERROR_HANDLE_EOF                            38          /*  Reached the end of the file.    */
#define ERROR_HANDLE_DISK_FULL                      39          /*  The disk is full.   */
#define ERROR_NOT_SUPPORTED                         50          /*  The network request is not supported.   */
#define ERROR_REM_NOT_LIST                          51          /*  The remote computer is not available.   */
#define ERROR_DUP_NAME                              52          /*  A duplicate name exists on the network. */
#define ERROR_BAD_NETPATH                           53          /*  The network path was not found. */
#define ERROR_NETWORK_BUSY                          54          /*  The network is busy.    */
#define ERROR_DEV_NOT_EXIST                         55          /*  The specified network resource or device is no longer available.    */
#define ERROR_TOO_MANY_CMDS                         56          /*  The network BIOS command limit has been reached.    */
#define ERROR_ADAP_HDW_ERR                          57          /*  A network adapter hardware error occurred.  */
#define ERROR_BAD_NET_RESP                          58          /*  The specified server cannot perform the requested operation.    */
#define ERROR_UNEXP_NET_ERR                         59          /*  An unexpected network error occurred.   */
#define ERROR_BAD_REM_ADAP                          60          /*  The remote adapter is not compatible.   */
#define ERROR_PRINTQ_FULL                           61          /*  The printer queue is full.  */
#define ERROR_NO_SPOOL_SPACE                        62          /*  Space to store the file waiting to be printed is not available on the server.   */
#define ERROR_PRINT_CANCELLED                       63          /*  Your file waiting to be printed was deleted.    */
#define ERROR_NETNAME_DELETED                       64          /*  The specified network name is no longer available.  */
#define ERROR_NETWORK_ACCESS_DENIED                 65          /*  Network access is denied.   */
#define ERROR_BAD_DEV_TYPE                          66          /*  The network resource type is not correct.   */
#define ERROR_BAD_NET_NAME                          67          /*  The network name cannot be found.   */
#define ERROR_TOO_MANY_NAMES                        68          /*  The name limit for the local computer network adapter card was exceeded.    */
#define ERROR_TOO_MANY_SESS                         69          /*  The network BIOS session limit was exceeded.    */
#define ERROR_SHARING_PAUSED                        70          /*  The remote server has been paused or is in the process of being started.    */
#define ERROR_REQ_NOT_ACCEP                         71          /*  No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.  */
#define ERROR_REDIR_PAUSED                          72          /*  The specified printer or disk device has been paused.   */
#define ERROR_FILE_EXISTS                           80          /*  The file exists.    */
#define ERROR_CANNOT_MAKE                           82          /*  The directory or file cannot be created.    */
#define ERROR_FAIL_I24                              83          /*  Fail on interrupt 24 handler.   */
#define ERROR_OUT_OF_STRUCTURES                     84          /*  Storage to process this request is not available.   */
#define ERROR_ALREADY_ASSIGNED                      85          /*  The local device name is already in use.    */
#define ERROR_INVALID_PASSWORD                      86          /*  The specified network password is not correct.  */
#define ERROR_INVALID_PARAMETER                     87          /*  The parameter is incorrect. */
#define ERROR_NET_WRITE_FAULT                       88          /*  A write fault occurred on the network.  */
#define ERROR_NO_PROC_SLOTS                         89          /*  The system cannot start another process at this time.   */
#define ERROR_TOO_MANY_SEMAPHORES                   100         /*  Cannot create another system semaphore. */
#define ERROR_EXCL_SEM_ALREADY_OWNED                101         /*  The exclusive semaphore is owned by another process.    */
#define ERROR_SEM_IS_SET                            102         /*  The semaphore is set and cannot be closed.  */
#define ERROR_TOO_MANY_SEM_REQUESTS                 103         /*  The semaphore cannot be set again.  */
#define ERROR_INVALID_AT_INTERRUPT_TIME             104         /*  Cannot request exclusive semaphores at interrupt time.  */
#define ERROR_SEM_OWNER_DIED                        105         /*  The previous ownership of this semaphore has ended. */
#define ERROR_SEM_USER_LIMIT                        106         /*  Insert the diskette for drive %1.   */
#define ERROR_DISK_CHANGE                           107         /*  The program stopped because an alternate diskette was not inserted. */
#define ERROR_DRIVE_LOCKED                          108         /*  The disk is in use or locked by another process.    */
#define ERROR_BROKEN_PIPE                           109         /*  The pipe has been ended.    */
#define ERROR_OPEN_FAILED                           110         /*  The system cannot open the device or file specified.    */
#define ERROR_BUFFER_OVERFLOW                       111         /*  The file name is too long.  */
#define ERROR_DISK_FULL                             112         /*  There is not enough space on the disk.  */
#define ERROR_NO_MORE_SEARCH_HANDLES                113         /*  No more internal file identifiers available.    */
#define ERROR_INVALID_TARGET_HANDLE                 114         /*  The target internal file identifier is incorrect.   */
#define ERROR_INVALID_CATEGORY                      117         /*  The IOCTL call made by the application program is not correct.  */
#define ERROR_INVALID_VERIFY_SWITCH                 118         /*  The verify-on-write switch parameter value is not correct.  */
#define ERROR_BAD_DRIVER_LEVEL                      119         /*  The system does not support the command requested.  */
#define ERROR_CALL_NOT_IMPLEMENTED                  120         /*  This function is not valid on this platform.    */
#define ERROR_SEM_TIMEOUT                           121         /*  The semaphore time-out period has expired.  */
#define ERROR_INSUFFICIENT_BUFFER                   122         /*  The data area passed to a system call is too small. */
#define ERROR_INVALID_NAME                          123         /*  The file name, directory name, or volume label syntax is incorrect. */
#define ERROR_INVALID_LEVEL                         124         /*  The system call level is not correct.   */
#define ERROR_NO_VOLUME_LABEL                       125         /*  The disk has no volume label.   */
#define ERROR_MOD_NOT_FOUND                         126         /*  The specified module could not be found.    */
#define ERROR_PROC_NOT_FOUND                        127         /*  The specified procedure could not be found. */
#define ERROR_WAIT_NO_CHILDREN                      128         /*  There are no child processes to wait for.   */
#define ERROR_CHILD_NOT_COMPLETE                    129         /*  The %1 application cannot be run in Windows NT mode.    */
#define ERROR_DIRECT_ACCESS_HANDLE                  130         /*  Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O.    */
#define ERROR_NEGATIVE_SEEK                         131         /*  An attempt was made to move the file pointer before the beginning of the file.  */
#define ERROR_SEEK_ON_DEVICE                        132         /*  The file pointer cannot be set on the specified device or file. */
#define ERROR_IS_JOIN_TARGET                        133         /*  A JOIN or SUBST command cannot be used for a drive that contains previously joined drives.  */
#define ERROR_IS_JOINED                             134         /*  An attempt was made to use a JOIN or SUBST command on a drive that has already been joined. */
#define ERROR_IS_SUBSTED                            135         /*  An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted.    */
#define ERROR_NOT_JOINED                            136         /*  The system tried to delete the JOIN of a drive that is not joined.  */
#define ERROR_NOT_SUBSTED                           137         /*  The system tried to delete the substitution of a drive that is not substituted. */
#define ERROR_JOIN_TO_JOIN                          138         /*  The system tried to join a drive to a directory on a joined drive.  */
#define ERROR_SUBST_TO_SUBST                        139         /*  The system tried to substitute a drive to a directory on a substituted drive.   */
#define ERROR_JOIN_TO_SUBST                         140         /*  The system tried to join a drive to a directory on a substituted drive. */
#define ERROR_SUBST_TO_JOIN                         141         /*  The system tried to SUBST a drive to a directory on a joined drive. */
#define ERROR_BUSY_DRIVE                            142         /*  The system cannot perform a JOIN or SUBST at this time. */
#define ERROR_SAME_DRIVE                            143         /*  The system cannot join or substitute a drive to or for a directory on the same drive.   */
#define ERROR_DIR_NOT_ROOT                          144         /*  The directory is not a subdirectory of the root directory.  */
#define ERROR_DIR_NOT_EMPTY                         145         /*  The directory is not empty. */
#define ERROR_IS_SUBST_PATH                         146         /*  The path specified is being used in a substitute.   */
#define ERROR_IS_JOIN_PATH                          147         /*  Not enough resources are available to process this command. */
#define ERROR_PATH_BUSY                             148         /*  The path specified cannot be used at this time. */
#define ERROR_IS_SUBST_TARGET                       149         /*  An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute.    */
#define ERROR_SYSTEM_TRACE                          150         /*  System trace information was not specified in your Config.sys file, or tracing is disallowed.   */
#define ERROR_INVALID_EVENT_COUNT                   151         /*  The number of specified semaphore events for DosMuxSemWait is not correct.  */
#define ERROR_TOO_MANY_MUXWAITERS                   152         /*  DosMuxSemWait did not execute; too many semaphores are already set. */
#define ERROR_INVALID_LIST_FORMAT                   153         /*  The DosMuxSemWait list is not correct.  */
#define ERROR_LABEL_TOO_LONG                        154         /*  The volume label you entered exceeds the label character limit of the target file system.   */
#define ERROR_TOO_MANY_TCBS                         155         /*  Cannot create another thread.   */
#define ERROR_SIGNAL_REFUSED                        156         /*  The recipient process has refused the signal.   */
#define ERROR_DISCARDED                             157         /*  The segment is already discarded and cannot be locked.  */
#define ERROR_NOT_LOCKED                            158         /*  The segment is already unlocked.    */
#define ERROR_BAD_THREADID_ADDR                     159         /*  The address for the thread identifier is not correct.   */
#define ERROR_BAD_ARGUMENTS                         160         /*  The argument string passed to DosExecPgm is not correct.    */
#define ERROR_BAD_PATHNAME                          161         /*  The specified path is invalid.  */
#define ERROR_SIGNAL_PENDING                        162         /*  A signal is already pending.    */
#define ERROR_MAX_THRDS_REACHED                     164         /*  No more threads can be created in the system.   */
#define ERROR_LOCK_FAILED                           167         /*  Unable to lock a region of a file.  */
#define ERROR_BUSY                                  170         /*  The requested resource is in use.   */
#define ERROR_CANCEL_VIOLATION                      173         /*  A lock request was not outstanding for the supplied cancel region.  */
#define ERROR_ATOMIC_LOCKS_NOT_SUPPORTED            174         /*  The file system does not support atomic changes to the lock type.   */
#define ERROR_INVALID_SEGMENT_NUMBER                180         /*  The system detected a segment number that was not correct.  */
#define ERROR_INVALID_ORDINAL                       182         /*  The operating system cannot run %1. */
#define ERROR_ALREADY_EXISTS                        183         /*  Cannot create a file when that file already exists. */
#define ERROR_INVALID_FLAG_NUMBER                   186         /*  The flag passed is not correct. */
#define ERROR_SEM_NOT_FOUND                         187         /*  The specified system semaphore name was not found.  */
#define ERROR_INVALID_STARTING_CODESEG              188         /*  The operating system cannot run %1. */
#define ERROR_INVALID_STACKSEG                      189         /*  The operating system cannot run %1. */
#define ERROR_INVALID_MODULETYPE                    190         /*  The operating system cannot run %1. */
#define ERROR_INVALID_EXE_SIGNATURE                 191         /*  Cannot run %1 in Windows NT mode.   */
#define ERROR_EXE_MARKED_INVALID                    192         /*  The operating system cannot run %1. */
#define ERROR_BAD_EXE_FORMAT                        193         /*  Is not a valid application. */
#define ERROR_ITERATED_DATA_EXCEEDS_64k             194         /*  The operating system cannot run %1. */
#define ERROR_INVALID_MINALLOCSIZE                  195         /*  The operating system cannot run %1. */
#define ERROR_DYNLINK_FROM_INVALID_RING             196         /*  The operating system cannot run this application program.   */
#define ERROR_IOPL_NOT_ENABLED                      197         /*  The operating system is not presently configured to run this application.   */
#define ERROR_INVALID_SEGDPL                        198         /*  The operating system cannot run %1. */
#define ERROR_AUTODATASEG_EXCEEDS_64k               199         /*  The operating system cannot run this application program.   */
#define ERROR_RING2SEG_MUST_BE_MOVABLE              200         /*  The code segment cannot be greater than or equal to 64 KB.  */
#define ERROR_RELOC_CHAIN_XEEDS_SEGLIM              201         /*  The operating system cannot run %1. */
#define ERROR_INFLOOP_IN_RELOC_CHAIN                202         /*  The operating system cannot run %1. */
#define ERROR_ENVVAR_NOT_FOUND                      203         /*  The system could not find the environment option that was entered.  */
#define ERROR_NO_SIGNAL_SENT                        205         /*  No process in the command subtree has a signal handler. */
#define ERROR_FILENAME_EXCED_RANGE                  206         /*  The file name or extension is too long. */
#define ERROR_RING2_STACK_IN_USE                    207         /*  The ring 2 stack is in use. */
#define ERROR_META_EXPANSION_TOO_LONG               208         /*  The global file name characters, "*" or "?," are entered incorrectly or too many global file name characters are specified. */
#define ERROR_INVALID_SIGNAL_NUMBER                 209         /*  The signal being posted is not correct. */
#define ERROR_THREAD_1_INACTIVE                     210         /*  The signal handler cannot be set.   */
#define ERROR_LOCKED                                212         /*  The segment is locked and cannot be reallocated.    */
#define ERROR_TOO_MANY_MODULES                      214         /*  Too many dynamic-link modules are attached to this program or dynamic-link module.  */
#define ERROR_NESTING_NOT_ALLOWED                   215         /*  Cannot nest calls to the LoadModule function.   */
#define ERROR_EXE_MACHINE_TYPE_MISMATCH             216         /*  The image file %1 is valid, but is for a machine type other than the current machine.   */
#define ERROR_BAD_PIPE                              230         /*  The pipe state is invalid.  */
#define ERROR_PIPE_BUSY                             231         /*  All pipe instances are busy.    */
#define ERROR_NO_DATA                               232         /*  The pipe is being closed.   */
#define ERROR_PIPE_NOT_CONNECTED                    233         /*  No process is on the other end of the pipe. */
#define ERROR_MORE_DATA                             234         /*  More data is available. */
#define ERROR_VC_DISCONNECTED                       240         /*  The session was canceled.   */
#define ERROR_INVALID_EA_NAME                       254         /*  The specified extended attribute name was invalid.  */
#define ERROR_EA_LIST_INCONSISTENT                  255         /*  The extended attributes are inconsistent.   */
#define WAIT_TIMEOUT                                258         /*  The wait operation timed out    */
#define ERROR_NO_MORE_ITEMS                         259         /*  No more data is available.  */
#define ERROR_CANNOT_COPY                           266         /*  The copy functions cannot be used.  */
#define ERROR_DIRECTORY                             267         /*  The directory name is invalid.  */
#define ERROR_EAS_DIDNT_FIT                         275         /*  The extended attributes did not fit in the buffer.  */
#define ERROR_EA_FILE_CORRUPT                       276         /*  The extended attribute file on the mounted file system is corrupt.  */
#define ERROR_EA_TABLE_FULL                         277         /*  The extended attribute table file is full.  */
#define ERROR_INVALID_EA_HANDLE                     278         /*  The specified extended attribute handle is invalid. */
#define ERROR_EAS_NOT_SUPPORTED                     282         /*  The mounted file system does not support extended attributes.   */
#define ERROR_NOT_OWNER                             288         /*  Attempt to release mutex not owned by caller.   */
#define ERROR_TOO_MANY_POSTS                        298         /*  Too many posts were made to a semaphore.    */
#define ERROR_PARTIAL_COPY                          299         /*  Only part of a ReadProcessMemory or WriteProcessMemory request was completed.   */
#define ERROR_MR_MID_NOT_FOUND                      317         /*  The system cannot find message text for message number 0x%1 in the message file for %2. */
#define ERROR_INVALID_ADDRESS                       487         /*  Attempt to access invalid address.  */
#define ERROR_ARITHMETIC_OVERFLOW                   534         /*  Arithmetic result exceeded 32 bits. */
#define ERROR_PIPE_CONNECTED                        535         /*  There is a process on other end of the pipe.    */
#define ERROR_PIPE_LISTENING                        536         /*  Waiting for a process to open the other end of the pipe.    */
#define ERROR_EA_ACCESS_DENIED                      994         /*  Access to the extended attribute was denied.    */
#define ERROR_OPERATION_ABORTED                     995         /*  The I/O operation has been aborted because of either a thread exit or an application request.   */
#define ERROR_IO_INCOMPLETE                         996         /*  Overlapped I/O event is not in a signaled state.    */
#define ERROR_IO_PENDING                            997         /*  Overlapped I/O operation is in progress.    */
#define ERROR_NOACCESS                              998         /*  Invalid access to memory location.  */
#define ERROR_SWAPERROR                             999         /*  Error performing inpage operation.  */
#define ERROR_STACK_OVERFLOW                        1001            /*  Recursion too deep; the stack overflowed.   */
#define ERROR_INVALID_MESSAGE                       1002            /*  The window cannot act on the sent message.  */
#define ERROR_CAN_NOT_COMPLETE                      1003            /*  Cannot complete this function.  */
#define ERROR_INVALID_FLAGS                         1004            /*  Invalid flags.  */
#define ERROR_UNRECOGNIZED_VOLUME                   1005            /*  The volume does not contain a recognized file system. Verify that all required file system drivers are loaded and that the volume is not corrupted. */
#define ERROR_FILE_INVALID                          1006            /*  The volume for a file has been externally altered so that the opened file is no longer valid.   */
#define ERROR_FULLSCREEN_MODE                       1007            /*  The requested operation cannot be performed in full-screen mode.    */
#define ERROR_NO_TOKEN                              1008            /*  An attempt was made to reference a token that does not exist.   */
#define ERROR_BADDB                                 1009            /*  The configuration registry database is corrupt. */
#define ERROR_BADKEY                                1010            /*  The configuration registry key is invalid.  */
#define ERROR_CANTOPEN                              1011            /*  The configuration registry key could not be opened. */
#define ERROR_CANTREAD                              1012            /*  The configuration registry key could not be read.   */
#define ERROR_CANTWRITE                             1013            /*  The configuration registry key could not be written.    */
#define ERROR_REGISTRY_RECOVERED                    1014            /*  One of the files in the registry database had to be recovered by use of a log or alternate copy. The recovery was successful.   */
#define ERROR_REGISTRY_CORRUPT                      1015            /*  The registry is corrupted. The structure of one of the files that contains registry data is corrupted, or the system's image of the file in memory is corrupted, or the file could not be recovered because the alternate copy or log was absent or corrupted.  */
#define ERROR_REGISTRY_IO_FAILED                    1016            /*  An I/O operation initiated by the registry failed unrecoverably. The registry could not read in, or write out, or flush, one of the files that contain the system's image of the registry.  */
#define ERROR_NOT_REGISTRY_FILE                     1017            /*  The system has attempted to load or restore a file into the registry, but the specified file is not in a registry file format.  */
#define ERROR_KEY_DELETED                           1018            /*  Illegal operation attempted on a registry key that has been marked for deletion.    */
#define ERROR_NO_LOG_SPACE                          1019            /*  System could not allocate the required space in a registry log. */
#define ERROR_KEY_HAS_CHILDREN                      1020            /*  Cannot create a symbolic link in a registry key that already has subkeys or values. */
#define ERROR_CHILD_MUST_BE_VOLATILE                1021            /*  Cannot create a stable subkey under a volatile parent key.  */
#define ERROR_NOTIFY_ENUM_DIR                       1022            /*  A notify change request is being completed and the information is not being returned in the caller's buffer. The caller now needs to enumerate the files to find the changes.   */
#define ERROR_DEPENDENT_SERVICES_RUNNING            1051            /*  A stop control has been sent to a service that other running services are dependent on. */
#define ERROR_INVALID_SERVICE_CONTROL               1052            /*  The requested control is not valid for this service.    */
#define ERROR_SERVICE_REQUEST_TIMEOUT               1053            /*  The service did not respond to the start or control request in a timely fashion.    */
#define ERROR_SERVICE_NO_THREAD                     1054            /*  A thread could not be created for the service.  */
#define ERROR_SERVICE_DATABASE_LOCKED               1055            /*  The service database is locked. */
#define ERROR_SERVICE_ALREADY_RUNNING               1056            /*  An instance of the service is already running.  */
#define ERROR_INVALID_SERVICE_ACCOUNT               1057            /*  The account name is invalid or does not exist.  */
#define ERROR_SERVICE_DISABLED                      1058            /*  The specified service is disabled and cannot be started.    */
#define ERROR_CIRCULAR_DEPENDENCY                   1059            /*  Circular service dependency was specified.  */
#define ERROR_SERVICE_DOES_NOT_EXIST                1060            /*  The specified service does not exist as an installed service.   */
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL            1061            /*  The service cannot accept control messages at this time.    */
#define ERROR_SERVICE_NOT_ACTIVE                    1062            /*  The service has not been started.   */
#define ERROR_FAILED_SERVICE_CONTROLLER_CONNECT     1063            /*  The service process could not connect to the service controller.    */
#define ERROR_EXCEPTION_IN_SERVICE                  1064            /*  An exception occurred in the service when handling the control request. */
#define ERROR_DATABASE_DOES_NOT_EXIST               1065            /*  The database specified does not exist.  */
#define ERROR_SERVICE_SPECIFIC_ERROR                1066            /*  The service has returned a service-specific error code. */
#define ERROR_PROCESS_ABORTED                       1067            /*  The process terminated unexpectedly.    */
#define ERROR_SERVICE_DEPENDENCY_FAIL               1068            /*  The dependency service or group failed to start.    */
#define ERROR_SERVICE_LOGON_FAILED                  1069            /*  The service did not start due to a logon failure.   */
#define ERROR_SERVICE_START_HANG                    1070            /*  After starting, the service stopped responding (hung) in a start-pending state. */
#define ERROR_INVALID_SERVICE_LOCK                  1071            /*  The specified service database lock is invalid. */
#define ERROR_SERVICE_MARKED_FOR_DELETE             1072            /*  The specified service has been marked for deletion. */
#define ERROR_SERVICE_EXISTS                        1073            /*  The specified service already exists.   */
#define ERROR_ALREADY_RUNNING_LKG                   1074            /*  The system is currently running with the last-known-good configuration. */
#define ERROR_SERVICE_DEPENDENCY_DELETED            1075            /*  The dependency service does not exist or has been marked for deletion.  */
#define ERROR_BOOT_ALREADY_ACCEPTED                 1076            /*  The current boot has already been accepted for use as the last-known-good control set.  */
#define ERROR_SERVICE_NEVER_STARTED                 1077            /*  No attempts to start the service have been made since the last boot.    */
#define ERROR_DUPLICATE_SERVICE_NAME                1078            /*  The name is already in use as either a service name or a service display name.  */
#define ERROR_DIFFERENT_SERVICE_ACCOUNT             1079            /*  The account specified for this service is different from the account specified for other services running in the same process.  */
#define ERROR_END_OF_MEDIA                          1100            /*  The physical end of the tape has been reached.  */
#define ERROR_FILEMARK_DETECTED                     1101            /*  A tape access reached a filemark.   */
#define ERROR_BEGINNING_OF_MEDIA                    1102            /*  The beginning of the tape or partition was encountered. */
#define ERROR_SETMARK_DETECTED                      1103            /*  A tape access reached the end of a set of files.    */
#define ERROR_NO_DATA_DETECTED                      1104            /*  No more data is on the tape.    */
#define ERROR_PARTITION_FAILURE                     1105            /*  Tape could not be partitioned.  */
#define ERROR_INVALID_BLOCK_LENGTH                  1106            /*  When accessing a new tape of a multivolume partition, the current block size is incorrect.  */
#define ERROR_DEVICE_NOT_PARTITIONED                1107            /*  Tape partition information could not be found when loading a tape.  */
#define ERROR_UNABLE_TO_LOCK_MEDIA                  1108            /*  Unable to lock the media eject mechanism.   */
#define ERROR_UNABLE_TO_UNLOAD_MEDIA                1109            /*  Unable to unload the media. */
#define ERROR_MEDIA_CHANGED                         1110            /*  The media in the drive may have changed.    */
#define ERROR_BUS_RESET                             1111            /*  The I/O bus was reset.  */
#define ERROR_NO_MEDIA_IN_DRIVE                     1112            /*  No media in drive.  */
#define ERROR_NO_UNICODE_TRANSLATION                1113            /*  No mapping for the Unicode character exists in the target multibyte code page.  */
#define ERROR_DLL_INIT_FAILED                       1114            /*  A dynamic link library (DLL) initialization routine failed. */
#define ERROR_SHUTDOWN_IN_PROGRESS                  1115            /*  A system shutdown is in progress.   */
#define ERROR_NO_SHUTDOWN_IN_PROGRESS               1116            /*  Unable to abort the system shutdown because no shutdown was in progress.    */
#define ERROR_IO_DEVICE                             1117            /*  The request could not be performed because of an I/O device error.  */
#define ERROR_SERIAL_NO_DEVICE                      1118            /*  No serial device was successfully initialized. The serial driver will unload.   */
#define ERROR_IRQ_BUSY                              1119            /*  Unable to open a device that was sharing an interrupt request (IRQ) with other devices. At least one other device that uses that IRQ was already opened.    */
#define ERROR_MORE_WRITES                           1120            /*  A serial I/O operation was completed by another write to the serial port. The IOCTL_SERIAL_XOFF_COUNTER reached zero.)  */
#define ERROR_COUNTER_TIMEOUT                       1121            /*  A serial I/O operation completed because the time-out period expired. In other words, the IOCTL_SERIAL_XOFF_COUNTER did not reach zero. */
#define ERROR_FLOPPY_ID_MARK_NOT_FOUND              1122            /*  No identifier address mark was found on the floppy disk.    */
#define ERROR_FLOPPY_WRONG_CYLINDER                 1123            /*  Mismatch between the floppy disk sector identifier field and the floppy disk controller track address.  */
#define ERROR_FLOPPY_UNKNOWN_ERROR                  1124            /*  The floppy disk controller reported an error that is not recognized by the floppy disk driver.  */
#define ERROR_FLOPPY_BAD_REGISTERS                  1125            /*  The floppy disk controller returned inconsistent results in its registers.  */
#define ERROR_DISK_RECALIBRATE_FAILED               1126            /*  While accessing the hard disk, a recalibrate operation failed, even after retries.  */
#define ERROR_DISK_OPERATION_FAILED                 1127            /*  While accessing the hard disk, a disk operation failed even after retries.  */
#define ERROR_DISK_RESET_FAILED                     1128            /*  While accessing the hard disk, a disk controller reset was needed, but even that failed.    */
#define ERROR_EOM_OVERFLOW                          1129            /*  Physical end of tape encountered.   */
#define ERROR_NOT_ENOUGH_SERVER_MEMORY              1130            /*  Not enough server storage is available to process this command. */
#define ERROR_POSSIBLE_DEADLOCK                     1131            /*  A potential deadlock condition has been detected.   */
#define ERROR_MAPPED_ALIGNMENT                      1132            /*  The base address or the file offset specified does not have the proper alignment.   */
#define ERROR_SET_POWER_STATE_VETOED                1140            /*  An attempt to change the system power state was vetoed by another application or driver.    */
#define ERROR_SET_POWER_STATE_FAILED                1141            /*  The basic input/output system (BIOS) failed an attempt to change the system power state.    */
#define ERROR_TOO_MANY_LINKS                        1142            /*  An attempt was made to create more links on a file than the file system supports.   */
#define ERROR_OLD_WIN_VERSION                       1150            /*  The specified program requires a newer version of Windows.  */
#define ERROR_APP_WRONG_OS                          1151            /*  The specified program is not a Windows or MS-DOS program.   */
#define ERROR_SINGLE_INSTANCE_APP                   1152            /*  Cannot start more than one instance of the specified program.   */
#define ERROR_RMODE_APP                             1153            /*  The specified program was written for an earlier version of Windows.    */
#define ERROR_INVALID_DLL                           1154            /*  One of the library files needed to run this application is damaged. */
#define ERROR_NO_ASSOCIATION                        1155            /*  No application is associated with the specified file for this operation.    */
#define ERROR_DDE_FAIL                              1156            /*  An error occurred in sending the command to the application.    */
#define ERROR_DLL_NOT_FOUND                         1157            /*  One of the library files needed to run this application cannot be found.    */
#define ERROR_BAD_DEVICE                            1200            /*  The specified device name is invalid.   */
#define ERROR_CONNECTION_UNAVAIL                    1201            /*  The device is not currently connected but it is a remembered connection.    */
#define ERROR_DEVICE_ALREADY_REMEMBERED             1202            /*  An attempt was made to remember a device that had previously been remembered.   */
#define ERROR_NO_NET_OR_BAD_PATH                    1203            /*  No network provider accepted the given network path.    */
#define ERROR_BAD_PROVIDER                          1204            /*  The specified network provider name is invalid. */
#define ERROR_CANNOT_OPEN_PROFILE                   1205            /*  Unable to open the network connection profile.  */
#define ERROR_BAD_PROFILE                           1206            /*  The network connection profile is corrupt.  */
#define ERROR_NOT_CONTAINER                         1207            /*  Cannot enumerate a noncontainer.    */
#define ERROR_EXTENDED_ERROR                        1208            /*  An extended error has occurred. */
#define ERROR_INVALID_GROUPNAME                     1209            /*  The format of the specified group name is invalid.  */
#define ERROR_INVALID_COMPUTERNAME                  1210            /*  The format of the specified computer name is invalid.   */
#define ERROR_INVALID_EVENTNAME                     1211            /*  The format of the specified event name is invalid.  */
#define ERROR_INVALID_DOMAINNAME                    1212            /*  The format of the specified domain name is invalid. */
#define ERROR_INVALID_SERVICENAME                   1213            /*  The format of the specified service name is invalid.    */
#define ERROR_INVALID_NETNAME                       1214            /*  The format of the specified network name is invalid.    */
#define ERROR_INVALID_SHARENAME                     1215            /*  The format of the specified share name is invalid.  */
#define ERROR_INVALID_PASSWORDNAME                  1216            /*  The format of the specified password is invalid.    */
#define ERROR_INVALID_MESSAGENAME                   1217            /*  The format of the specified message name is invalid.    */
#define ERROR_INVALID_MESSAGEDEST                   1218            /*  The format of the specified message destination is invalid. */
#define ERROR_SESSION_CREDENTIAL_CONFLICT           1219            /*  The credentials supplied conflict with an existing set of credentials.  */
#define ERROR_REMOTE_SESSION_LIMIT_EXCEEDED         1220            /*  An attempt was made to establish a session to a network server, but there are already too many sessions established to that server. */
#define ERROR_DUP_DOMAINNAME                        1221            /*  The workgroup or domain name is already in use by another computer on the network.  */
#define ERROR_NO_NETWORK                            1222            /*  The network is not present or not started.  */
#define ERROR_CANCELLED                             1223            /*  The operation was canceled by the user. */
#define ERROR_USER_MAPPED_FILE                      1224            /*  The requested operation cannot be performed on a file with a user-mapped section open.  */
#define ERROR_CONNECTION_REFUSED                    1225            /*  The remote system refused the network connection.   */
#define ERROR_GRACEFUL_DISCONNECT                   1226            /*  The network connection was gracefully closed.   */
#define ERROR_ADDRESS_ALREADY_ASSOCIATED            1227            /*  The network transport endpoint already has an address associated with it.   */
#define ERROR_ADDRESS_NOT_ASSOCIATED                1228            /*  An address has not yet been associated with the network endpoint.   */
#define ERROR_CONNECTION_INVALID                    1229            /*  An operation was attempted on a nonexistent network connection. */
#define ERROR_CONNECTION_ACTIVE                     1230            /*  An invalid operation was attempted on an active network connection. */
#define ERROR_NETWORK_UNREACHABLE                   1231            /*  The remote network is not reachable by the transport.   */
#define ERROR_HOST_UNREACHABLE                      1232            /*  The remote system is not reachable by the transport.    */
#define ERROR_PROTOCOL_UNREACHABLE                  1233            /*  The remote system does not support the transport protocol.  */
#define ERROR_PORT_UNREACHABLE                      1234            /*  No service is operating at the destination network endpoint on the remote system.   */
#define ERROR_REQUEST_ABORTED                       1235            /*  The request was aborted.    */
#define ERROR_CONNECTION_ABORTED                    1236            /*  The network connection was aborted by the local system. */
#define ERROR_RETRY                                 1237            /*  The operation could not be completed. A retry should be performed.  */
#define ERROR_CONNECTION_COUNT_LIMIT                1238            /*  A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.   */
#define ERROR_LOGIN_TIME_RESTRICTION                1239            /*  Attempting to log in during an unauthorized time of day for this account.   */
#define ERROR_LOGIN_WKSTA_RESTRICTION               1240            /*  The account is not authorized to log in from this station.  */
#define ERROR_INCORRECT_ADDRESS                     1241            /*  The network address could not be used for the operation requested.  */
#define ERROR_ALREADY_REGISTERED                    1242            /*  The service is already registered.  */
#define ERROR_SERVICE_NOT_FOUND                     1243            /*  The specified service does not exist.   */
#define ERROR_NOT_AUTHENTICATED                     1244            /*  The operation being requested was not performed because the user has not been authenticated.    */
#define ERROR_NOT_LOGGED_ON                         1245            /*  The operation being requested was not performed because the user has not logged on to the network. The specified service does not exist.    */
#define ERROR_CONTINUE                              1246            /*  Caller to continue with work in progress.   */
#define ERROR_ALREADY_INITIALIZED                   1247            /*  An attempt was made to perform an initialization operation when initialization has already been completed.  */
#define ERROR_NO_MORE_DEVICES                       1248            /*  No more local devices.  */
#define ERROR_NOT_ALL_ASSIGNED                      1300            /*  Not all privileges referenced are assigned to the caller.   */
#define ERROR_SOME_NOT_MAPPED                       1301            /*  Some mapping between account names and security IDs was not done.   */
#define ERROR_NO_QUOTAS_FOR_ACCOUNT                 1302            /*  No system quota limits are specifically set for this account.   */
#define ERROR_LOCAL_USER_SESSION_KEY                1303            /*  No encryption key is available. A well-known encryption key was returned.   */
#define ERROR_NULL_LM_PASSWORD                      1304            /*  The password is too complex to be converted to a LAN Manager password. The LAN Manager password returned is a null string.  */
#define ERROR_UNKNOWN_REVISION                      1305            /*  The revision level is unknown.  */
#define ERROR_REVISION_MISMATCH                     1306            /*  Indicates two revision levels are incompatible. */
#define ERROR_INVALID_OWNER                         1307            /*  This security identifier may not be assigned as the owner of this object.   */
#define ERROR_INVALID_PRIMARY_GROUP                 1308            /*  This security identifier may not be assigned as the primary group of an object. */
#define ERROR_NO_IMPERSONATION_TOKEN                1309            /*  An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client. */
#define ERROR_CANT_DISABLE_MANDATORY                1310            /*  The group cannot be disabled.   */
#define ERROR_NO_LOGON_SERVERS                      1311            /*  There are currently no logon servers available to service the logon request.    */
#define ERROR_NO_SUCH_LOGON_SESSION                 1312            /*  A specified logon session does not exist. It may already have been terminated.  */
#define ERROR_NO_SUCH_PRIVILEGE                     1313            /*  A specified privilege does not exist.   */
#define ERROR_PRIVILEGE_NOT_HELD                    1314            /*  A required privilege is not held by the client. */
#define ERROR_INVALID_ACCOUNT_NAME                  1315            /*  The name provided is not a properly formed account name.    */
#define ERROR_USER_EXISTS                           1316            /*  The specified user already exists.  */
#define ERROR_NO_SUCH_USER                          1317            /*  The specified user does not exist.  */
#define ERROR_GROUP_EXISTS                          1318            /*  The specified group already exists. */
#define ERROR_NO_SUCH_GROUP                         1319            /*  The specified group does not exist. */
#define ERROR_MEMBER_IN_GROUP                       1320            /*  Either the specified user account is already a member of the specified group, or the specified group cannot be deleted because it contains a member.    */
#define ERROR_MEMBER_NOT_IN_GROUP                   1321            /*  The specified user account is not a member of the specified group account.  */
#define ERROR_LAST_ADMIN                            1322            /*  The last remaining administration account cannot be disabled or deleted.    */
#define ERROR_WRONG_PASSWORD                        1323            /*  Unable to update the password. The value provided as the current password is incorrect. */
#define ERROR_ILL_FORMED_PASSWORD                   1324            /*  Unable to update the password. The value provided for the new password contains values that are not allowed in passwords.   */
#define ERROR_PASSWORD_RESTRICTION                  1325            /*  Unable to update the password because a password update rule has been violated. */
#define ERROR_LOGON_FAILURE                         1326            /*  Logon failure — unknown user name or bad password. */
#define ERROR_ACCOUNT_RESTRICTION                   1327            /*  Logon failure — user account restriction.  */
#define ERROR_INVALID_LOGON_HOURS                   1328            /*  Logon failure — account logon time restriction violation.  */
#define ERROR_INVALID_WORKSTATION                   1329            /*  Logon failure — user not allowed to log on to this computer.   */
#define ERROR_PASSWORD_EXPIRED                      1330            /*  Logon failure — the specified account password has expired.    */
#define ERROR_ACCOUNT_DISABLED                      1331            /*  Logon failure — account currently disabled.    */
#define ERROR_NONE_MAPPED                           1332            /*  No mapping between account names and security IDs was done. */
#define ERROR_TOO_MANY_LUIDS_REQUESTED              1333            /*  Too many LUIDs were requested at one time.  */
#define ERROR_LUIDS_EXHAUSTED                       1334            /*  No more LUIDs are available.    */
#define ERROR_INVALID_SUB_AUTHORITY                 1335            /*  The subauthority part of a security identifier is invalid for this particular use.  */
#define ERROR_INVALID_ACL                           1336            /*  The access control list (ACL) structure is invalid. */
#define ERROR_INVALID_SID                           1337            /*  The security identifier structure is invalid.   */
#define ERROR_INVALID_SECURITY_DESCR                1338            /*  The security descriptor structure is invalid.   */
#define ERROR_BAD_INHERITANCE_ACL                   1340            /*  The inherited access control list (ACL) or access control entry (ACE) could not be built.   */
#define ERROR_SERVER_DISABLED                       1341            /*  The server is currently disabled.   */
#define ERROR_SERVER_NOT_DISABLED                   1342            /*  The server is currently enabled.    */
#define ERROR_INVALID_ID_AUTHORITY                  1343            /*  The value provided was an invalid value for an identifier authority.    */
#define ERROR_ALLOTTED_SPACE_EXCEEDED               1344            /*  No more memory is available for security information updates.   */
#define ERROR_INVALID_GROUP_ATTRIBUTES              1345            /*  The specified attributes are invalid, or incompatible with the attributes for the group as a whole. */
#define ERROR_BAD_IMPERSONATION_LEVEL               1346            /*  Either a required impersonation level was not provided, or the provided impersonation level is invalid. */
#define ERROR_CANT_OPEN_ANONYMOUS                   1347            /*  Cannot open an anonymous level security token.  */
#define ERROR_BAD_VALIDATION_CLASS                  1348            /*  The validation information class requested was invalid. */
#define ERROR_BAD_TOKEN_TYPE                        1349            /*  The type of the token is inappropriate for its attempted use.   */
#define ERROR_NO_SECURITY_ON_OBJECT                 1350            /*  Unable to perform a security operation on an object that has no associated security.    */
#define ERROR_CANT_ACCESS_DOMAIN_INFO               1351            /*  Indicates that a Windows NT Server could not be contacted or that objects within the domain are protected such that necessary information could not be retrieved.   */
#define ERROR_INVALID_SERVER_STATE                  1352            /*  The security account manager (SAM) or local security authority (LSA) server was in the wrong state to perform the security operation.   */
#define ERROR_INVALID_DOMAIN_STATE                  1353            /*  The domain was in the wrong state to perform the security operation.    */
#define ERROR_INVALID_DOMAIN_ROLE                   1354            /*  This operation is only allowed for the Primary Domain Controller (PDC) of the domain.   */
#define ERROR_NO_SUCH_DOMAIN                        1355            /*  The specified domain did not exist. */
#define ERROR_DOMAIN_EXISTS                         1356            /*  The specified domain already exists.    */
#define ERROR_DOMAIN_LIMIT_EXCEEDED                 1357            /*  An attempt was made to exceed the limit on the number of domains per server.    */
#define ERROR_INTERNAL_DB_CORRUPTION                1358            /*  Unable to complete the requested operation because of either a catastrophic media failure or a data structure corruption on the disk.   */
#define ERROR_INTERNAL_ERROR                        1359            /*  The security account database contains an internal inconsistency.   */
#define ERROR_GENERIC_NOT_MAPPED                    1360            /*  Generic access types were contained in an access mask that should already be mapped to nongeneric types.    */
#define ERROR_BAD_DESCRIPTOR_FORMAT                 1361            /*  A security descriptor is not in the right format (absolute or self-relative).   */
#define ERROR_NOT_LOGON_PROCESS                     1362            /*  The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process.  */
#define ERROR_LOGON_SESSION_EXISTS                  1363            /*  Cannot start a new logon session with an identifier that is already in use. */
#define ERROR_NO_SUCH_PACKAGE                       1364            /*  A specified authentication package is unknown.  */
#define ERROR_BAD_LOGON_SESSION_STATE               1365            /*  The logon session is not in a state that is consistent with the requested operation.    */
#define ERROR_LOGON_SESSION_COLLISION               1366            /*  The logon session identifier is already in use. */
#define ERROR_INVALID_LOGON_TYPE                    1367            /*  A logon request contained an invalid logon type value.  */
#define ERROR_RXACT_INVALID_STATE                   1369            /*  The transaction state of a registry subtree is incompatible with the requested operation.   */
#define ERROR_RXACT_COMMIT_FAILURE                  1370            /*  An internal security database corruption has been encountered.  */
#define ERROR_SPECIAL_ACCOUNT                       1371            /*  Cannot perform this operation on built-in accounts. */
#define ERROR_SPECIAL_GROUP                         1372            /*  Cannot perform this operation on this built-in special group.   */
#define ERROR_SPECIAL_USER                          1373            /*  Cannot perform this operation on this built-in special user.    */
#define ERROR_MEMBERS_PRIMARY_GROUP                 1374            /*  The user cannot be removed from a group because the group is currently the user's primary group.    */
#define ERROR_TOKEN_ALREADY_IN_USE                  1375            /*  The token is already in use as a primary token. */
#define ERROR_NO_SUCH_ALIAS                         1376            /*  The specified local group does not exist.   */
#define ERROR_MEMBER_NOT_IN_ALIAS                   1377            /*  The specified account name is not a member of the local group.  */
#define ERROR_MEMBER_IN_ALIAS                       1378            /*  The specified account name is already a member of the local group.  */
#define ERROR_ALIAS_EXISTS                          1379            /*  The specified local group already exists.   */
#define ERROR_LOGON_NOT_GRANTED                     1380            /*  Logon failure — the user has not been granted the requested logon type at this computer.   */
#define ERROR_TOO_MANY_SECRETS                      1381            /*  The maximum number of secrets that may be stored in a single system has been exceeded.  */
#define ERROR_SECRET_TOO_LONG                       1382            /*  The length of a secret exceeds the maximum length allowed.  */
#define ERROR_INTERNAL_DB_ERROR                     1383            /*  The local security authority database contains an internal inconsistency.   */
#define ERROR_TOO_MANY_CONTEXT_IDS                  1384            /*  During a logon attempt, the user's security context accumulated too many security IDs.  */
#define ERROR_LOGON_TYPE_NOT_GRANTED                1385            /*  Logon failure — the user has not been granted the requested logon type at this computer.   */
#define ERROR_NT_CROSS_ENCRYPTION_REQUIRED          1386            /*  A cross-encrypted password is necessary to change a user password.  */
#define ERROR_NO_SUCH_MEMBER                        1387            /*  A new member could not be added to a local group because the member does not exist. */
#define ERROR_INVALID_MEMBER                        1388            /*  A new member could not be added to a local group because the member has the wrong account type. */
#define ERROR_TOO_MANY_SIDS                         1389            /*  Too many security IDs have been specified.  */
#define ERROR_LM_CROSS_ENCRYPTION_REQUIRED          1390            /*  A cross-encrypted password is necessary to change this user password.   */
#define ERROR_NO_INHERITANCE                        1391            /*  Indicates an ACL contains no inheritable components.    */
#define ERROR_FILE_CORRUPT                          1392            /*  The file or directory is corrupted and non-readable.    */
#define ERROR_DISK_CORRUPT                          1393            /*  The disk structure is corrupted and non-readable.   */
#define ERROR_NO_USER_SESSION_KEY                   1394            /*  There is no user session key for the specified logon session.   */
#define ERROR_LICENSE_QUOTA_EXCEEDED                1395            /*  The service being accessed is licensed for a particular number of connections. No more connections can be made to the service at this time because there are already as many connections as the service can accept. */
#define ERROR_INVALID_WINDOW_HANDLE                 1400            /*  Invalid window handle.  */
#define ERROR_INVALID_MENU_HANDLE                   1401            /*  Invalid menu handle.    */
#define ERROR_INVALID_CURSOR_HANDLE                 1402            /*  Invalid cursor handle.  */
#define ERROR_INVALID_ACCEL_HANDLE                  1403            /*  Invalid accelerator table handle.   */
#define ERROR_INVALID_HOOK_HANDLE                   1404            /*  Invalid hook handle.    */
#define ERROR_INVALID_DWP_HANDLE                    1405            /*  Invalid handle to a multiple-window position structure. */
#define ERROR_TLW_WITH_WSCHILD                      1406            /*  Cannot create a top-level child window. */
#define ERROR_CANNOT_FIND_WND_CLASS                 1407            /*  Cannot find window class.   */
#define ERROR_WINDOW_OF_OTHER_THREAD                1408            /*  Invalid window, it belongs to another thread.   */
#define ERROR_HOTKEY_ALREADY_REGISTERED             1409            /*  Hot key is already registered.  */
#define ERROR_CLASS_ALREADY_EXISTS                  1410            /*  Class already exists.   */
#define ERROR_CLASS_DOES_NOT_EXIST                  1411            /*  Class does not exist.   */
#define ERROR_CLASS_HAS_WINDOWS                     1412            /*  Class still has open windows.   */
#define ERROR_INVALID_INDEX                         1413            /*  Invalid index.  */
#define ERROR_INVALID_ICON_HANDLE                   1414            /*  Invalid icon handle.    */
#define ERROR_PRIVATE_DIALOG_INDEX                  1415            /*  Using private DIALOG window words.  */
#define ERROR_LISTBOX_ID_NOT_FOUND                  1416            /*  The list box identifier was not found.  */
#define ERROR_NO_WILDCARD_CHARACTERS                1417            /*  No wildcards were found.    */
#define ERROR_CLIPBOARD_NOT_OPEN                    1418            /*  Thread does not have a clipboard open.  */
#define ERROR_HOTKEY_NOT_REGISTERED                 1419            /*  Hot key is not registered.  */
#define ERROR_WINDOW_NOT_DIALOG                     1420            /*  The window is not a valid dialog window.    */
#define ERROR_CONTROL_ID_NOT_FOUND                  1421            /*  Control identifier not found.   */
#define ERROR_INVALID_COMBOBOX_MESSAGE              1422            /*  Invalid message for a combo box because it does not have an edit control.   */
#define ERROR_WINDOW_NOT_COMBOBOX                   1423            /*  The window is not a combo box.  */
#define ERROR_INVALID_EDIT_HEIGHT                   1424            /*  Height must be less than 256.   */
#define ERROR_DC_NOT_FOUND                          1425            /*  Invalid device context (DC) handle. */
#define ERROR_INVALID_HOOK_FILTER                   1426            /*  Invalid hook procedure type.    */
#define ERROR_INVALID_FILTER_PROC                   1427            /*  Invalid hook procedure. */
#define ERROR_HOOK_NEEDS_HMOD                       1428            /*  Cannot set nonlocal hook without a module handle.   */
#define ERROR_GLOBAL_ONLY_HOOK                      1429            /*  This hook procedure can only be set globally.   */
#define ERROR_JOURNAL_HOOK_SET                      1430            /*  The journal hook procedure is already installed.    */
#define ERROR_HOOK_NOT_INSTALLED                    1431            /*  The hook procedure is not installed.    */
#define ERROR_INVALID_LB_MESSAGE                    1432            /*  Invalid message for single-selection list box.  */
#define ERROR_LB_WITHOUT_TABSTOPS                   1434            /*  This list box does not support tab stops.   */
#define ERROR_DESTROY_OBJECT_OF_OTHER_THREAD        1435            /*  Cannot destroy object created by another thread.    */
#define ERROR_CHILD_WINDOW_MENU                     1436            /*  Child windows cannot have menus.    */
#define ERROR_NO_SYSTEM_MENU                        1437            /*  The window does not have a system menu. */
#define ERROR_INVALID_MSGBOX_STYLE                  1438            /*  Invalid message box style.  */
#define ERROR_INVALID_SPI_VALUE                     1439            /*  Invalid system-wide (SPI_*) parameter.  */
#define ERROR_SCREEN_ALREADY_LOCKED                 1440            /*  Screen already locked.  */
#define ERROR_HWNDS_HAVE_DIFF_PARENT                1441            /*  All handles to windows in a multiple-window position structure must have the same parent.   */
#define ERROR_NOT_CHILD_WINDOW                      1442            /*  The window is not a child window.   */
#define ERROR_INVALID_GW_COMMAND                    1443            /*  Invalid GW_* command.   */
#define ERROR_INVALID_THREAD_ID                     1444            /*  Invalid thread identifier.  */
#define ERROR_NON_MDICHILD_WINDOW                   1445            /*  Cannot process a message from a window that is not a multiple-document interface (MDI) window.  */
#define ERROR_POPUP_ALREADY_ACTIVE                  1446            /*  Pop-up menu already active. */
#define ERROR_NO_SCROLLBARS                         1447            /*  The window does not have scroll bars.   */
#define ERROR_INVALID_SCROLLBAR_RANGE               1448            /*  Scroll bar range cannot be greater than 0x7FFF. */
#define ERROR_INVALID_SHOWWIN_COMMAND               1449            /*  Cannot show or remove the window in the way specified.  */
#define ERROR_NO_SYSTEM_RESOURCES                   1450            /*  Insufficient system resources exist to complete the requested service.  */
#define ERROR_NONPAGED_SYSTEM_RESOURCES             1451            /*  Insufficient system resources exist to complete the requested service.  */
#define ERROR_PAGED_SYSTEM_RESOURCES                1452            /*  Insufficient system resources exist to complete the requested service.  */
#define ERROR_WORKING_SET_QUOTA                     1453            /*  Insufficient quota to complete the requested service.   */
#define ERROR_PAGEFILE_QUOTA                        1454            /*  Insufficient quota to complete the requested service.   */
#define ERROR_COMMITMENT_LIMIT                      1455            /*  The paging file is too small for this operation to complete.    */
#define ERROR_MENU_ITEM_NOT_FOUND                   1456            /*  A menu item was not found.  */
#define ERROR_INVALID_KEYBOARD_HANDLE               1457            /*  Invalid keyboard layout handle. */
#define ERROR_HOOK_TYPE_NOT_ALLOWED                 1458            /*  Hook type not allowed.  */
#define ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION    1459            /*  This operation requires an interactive window station.  */
#define ERROR_TIMEOUT                               1460            /*  This operation returned because the time-out period expired.    */
#define ERROR_EVENTLOG_FILE_CORRUPT                 1500            /*  The event tracking file is corrupted.   */
#define ERROR_EVENTLOG_CANT_START                   1501            /*  No event tracking file could be opened, so the event tracking service did not start.    */
#define ERROR_LOG_FILE_FULL                         1502            /*  The event tracking file is full.    */
#define ERROR_EVENTLOG_FILE_CHANGED                 1503            /*  The event tracking file has changed between read operations.    */
#define ERROR_DEVICE_REMOVED                        1617            /*  The device has been removed */
#define RPC_S_INVALID_STRING_BINDING                1700            /*  The string binding is invalid.  */
#define RPC_S_WRONG_KIND_OF_BINDING                 1701            /*  The binding handle is not the correct type. */
#define RPC_S_INVALID_BINDING                       1702            /*  The binding handle is invalid.  */
#define RPC_S_PROTSEQ_NOT_SUPPORTED                 1703            /*  The RPC protocol sequence is not supported. */
#define RPC_S_INVALID_RPC_PROTSEQ                   1704            /*  The RPC protocol sequence is invalid.   */
#define RPC_S_INVALID_STRING_UUID                   1705            /*  The string universal unique identifier (UUID) is invalid.   */
#define RPC_S_INVALID_ENDPOINT_FORMAT               1706            /*  The endpoint format is invalid. */
#define RPC_S_INVALID_NET_ADDR                      1707            /*  The network address is invalid. */
#define RPC_S_NO_ENDPOINT_FOUND                     1708            /*  No endpoint was found.  */
#define RPC_S_INVALID_TIMEOUT                       1709            /*  The time-out value is invalid.  */
#define RPC_S_OBJECT_NOT_FOUND                      1710            /*  The object universal unique identifier (UUID) was not found.    */
#define RPC_S_ALREADY_REGISTERED                    1711            /*  The object universally unique identifier (UUID) has already been registered.    */
#define RPC_S_TYPE_ALREADY_REGISTERED               1712            /*  The type UUID has already been registered.  */
#define RPC_S_ALREADY_LISTENING                     1713            /*  The remote procedure call (RPC) server is already listening.    */
#define RPC_S_NO_PROTSEQS_REGISTERED                1714            /*  No protocol sequences have been registered. */
#define RPC_S_NOT_LISTENING                         1715            /*  The RPC server is not listening.    */
#define RPC_S_UNKNOWN_MGR_TYPE                      1716            /*  The manager type is unknown.    */
#define RPC_S_UNKNOWN_IF                            1717            /*  The interface is unknown.   */
#define RPC_S_NO_BINDINGS                           1718            /*  There are no bindings.  */
#define RPC_S_NO_PROTSEQS                           1719            /*  There are no protocol sequences.    */
#define RPC_S_CANT_CREATE_ENDPOINT                  1720            /*  The endpoint cannot be created. */
#define RPC_S_OUT_OF_RESOURCES                      1721            /*  Not enough resources are available to complete this operation.  */
#define RPC_S_SERVER_UNAVAILABLE                    1722            /*  The RPC server is unavailable.  */
#define RPC_S_SERVER_TOO_BUSY                       1723            /*  The RPC server is too busy to complete this operation.  */
#define RPC_S_INVALID_NETWORK_OPTIONS               1724            /*  The network options are invalid.    */
#define RPC_S_NO_CALL_ACTIVE                        1725            /*  There is not a remote procedure call active in this thread. */
#define RPC_S_CALL_FAILED                           1726            /*  The remote procedure call failed.   */
#define RPC_S_CALL_FAILED_DNE                       1727            /*  The remote procedure call failed and did not execute.   */
#define RPC_S_PROTOCOL_ERROR                        1728            /*  A remote procedure call (RPC) protocol error occurred.  */
#define RPC_S_UNSUPPORTED_TRANS_SYN                 1730            /*  The transfer syntax is not supported by the RPC server. */
#define RPC_S_UNSUPPORTED_TYPE                      1732            /*  The universal unique identifier (UUID) type is not supported.   */
#define RPC_S_INVALID_TAG                           1733            /*  The tag is invalid. */
#define RPC_S_INVALID_BOUND                         1734            /*  The array bounds are invalid.   */
#define RPC_S_NO_ENTRY_NAME                         1735            /*  The binding does not contain an entry name. */
#define RPC_S_INVALID_NAME_SYNTAX                   1736            /*  The name syntax is invalid. */
#define RPC_S_UNSUPPORTED_NAME_SYNTAX               1737            /*  The name syntax is not supported.   */
#define RPC_S_UUID_NO_ADDRESS                       1739            /*  No network address is available to use to construct a universal unique identifier (UUID).   */
#define RPC_S_DUPLICATE_ENDPOINT                    1740            /*  The endpoint is a duplicate.    */
#define RPC_S_UNKNOWN_AUTHN_TYPE                    1741            /*  The authentication type is unknown. */
#define RPC_S_MAX_CALLS_TOO_SMALL                   1742            /*  The maximum number of calls is too small.   */
#define RPC_S_STRING_TOO_LONG                       1743            /*  The string is too long. */
#define RPC_S_PROTSEQ_NOT_FOUND                     1744            /*  The RPC protocol sequence was not found.    */
#define RPC_S_PROCNUM_OUT_OF_RANGE                  1745            /*  The procedure number is out of range.   */
#define RPC_S_BINDING_HAS_NO_AUTH                   1746            /*  The binding does not contain any authentication information.    */
#define RPC_S_UNKNOWN_AUTHN_SERVICE                 1747            /*  The authentication service is unknown.  */
#define RPC_S_UNKNOWN_AUTHN_LEVEL                   1748            /*  The authentication level is unknown.    */
#define RPC_S_INVALID_AUTH_IDENTITY                 1749            /*  The security context is invalid.    */
#define RPC_S_UNKNOWN_AUTHZ_SERVICE                 1750            /*  The authorization service is unknown.   */
#define EPT_S_INVALID_ENTRY                         1751            /*  The entry is invalid.   */
#define EPT_S_CANT_PERFORM_OP                       1752            /*  The server endpoint cannot perform the operation.   */
#define EPT_S_NOT_REGISTERED                        1753            /*  There are no more endpoints available from the endpoint mapper. */
#define RPC_S_NOTHING_TO_EXPORT                     1754            /*  No interfaces have been exported.   */
#define RPC_S_INCOMPLETE_NAME                       1755            /*  The entry name is incomplete.   */
#define RPC_S_INVALID_VERS_OPTION                   1756            /*  The version option is invalid.  */
#define RPC_S_NO_MORE_MEMBERS                       1757            /*  There are no more members.  */
#define RPC_S_NOT_ALL_OBJS_UNEXPORTED               1758            /*  There is nothing to unexport.   */
#define RPC_S_INTERFACE_NOT_FOUND                   1759            /*  The interface was not found.    */
#define RPC_S_ENTRY_ALREADY_EXISTS                  1760            /*  The entry already exists.   */
#define RPC_S_ENTRY_NOT_FOUND                       1761            /*  The entry is not found. */
#define RPC_S_NAME_SERVICE_UNAVAILABLE              1762            /*  The name service is unavailable.    */
#define RPC_S_INVALID_NAF_ID                        1763            /*  The network address family is invalid.  */
#define RPC_S_CANNOT_SUPPORT                        1764            /*  The requested operation is not supported.   */
#define RPC_S_NO_CONTEXT_AVAILABLE                  1765            /*  No security context is available to allow impersonation.    */
#define RPC_S_INTERNAL_ERROR                        1766            /*  An internal error occurred in a remote procedure call (RPC).    */
#define RPC_S_ZERO_DIVIDE                           1767            /*  The RPC server attempted an integer division by zero.   */
#define RPC_S_ADDRESS_ERROR                         1768            /*  An addressing error occurred in the RPC server. */
#define RPC_S_FP_DIV_ZERO                           1769            /*  A floating-point operation at the RPC server caused a division by zero. */
#define RPC_S_FP_UNDERFLOW                          1770            /*  A floating-point underflow occurred at the RPC server.  */
#define RPC_S_FP_OVERFLOW                           1771            /*  A floating-point overflow occurred at the RPC server.   */
#define RPC_X_NO_MORE_ENTRIES                       1772            /*  The list of RPC servers available for the binding of auto handles has been exhausted.   */
#define RPC_X_SS_CHAR_TRANS_OPEN_FAIL               1773            /*  Unable to open the character translation table file.    */
#define RPC_X_SS_CHAR_TRANS_SHORT_FILE              1774            /*  The file containing the character translation table has fewer than 512 bytes.   */
#define RPC_X_SS_IN_NULL_CONTEXT                    1775            /*  A null context handle was passed from the client to the host during a remote procedure call.    */
#define RPC_X_SS_CONTEXT_DAMAGED                    1777            /*  The context handle changed during a remote procedure call.  */
#define RPC_X_SS_HANDLES_MISMATCH                   1778            /*  The binding handles passed to a remote procedure call do not match. */
#define RPC_X_SS_CANNOT_GET_CALL_HANDLE             1779            /*  The stub is unable to get the remote procedure call handle. */
#define RPC_X_NULL_REF_POINTER                      1780            /*  A null reference pointer was passed to the stub.    */
#define RPC_X_ENUM_VALUE_OUT_OF_RANGE               1781            /*  The enumeration value is out of range.  */
#define RPC_X_BYTE_COUNT_TOO_SMALL                  1782            /*  The byte count is too small.    */
#define RPC_X_BAD_STUB_DATA                         1783            /*  The stub received bad data. */
#define ERROR_INVALID_USER_BUFFER                   1784            /*  The supplied user buffer is not valid for the requested operation.  */
#define ERROR_UNRECOGNIZED_MEDIA                    1785            /*  The disk media is not recognized. It may not be formatted.  */
#define ERROR_NO_TRUST_LSA_SECRET                   1786            /*  The workstation does not have a trust secret.   */
#define ERROR_NO_TRUST_SAM_ACCOUNT                  1787            /*  The SAM database on the Windows NT Server does not have a computer account for this workstation trust relationship. */
#define ERROR_TRUSTED_DOMAIN_FAILURE                1788            /*  The trust relationship between the primary domain and the trusted domain failed.    */
#define ERROR_TRUSTED_RELATIONSHIP_FAILURE          1789            /*  The trust relationship between this workstation and the primary domain failed.  */
#define ERROR_TRUST_FAILURE                         1790            /*  The network logon failed.   */
#define RPC_S_CALL_IN_PROGRESS                      1791            /*  A remote procedure call is already in progress for this thread. */
#define ERROR_NETLOGON_NOT_STARTED                  1792            /*  An attempt was made to logon, but the network logon service was not started.    */
#define ERROR_ACCOUNT_EXPIRED                       1793            /*  The user's account has expired. */
#define ERROR_REDIRECTOR_HAS_OPEN_HANDLES           1794            /*  The redirector is in use and cannot be unloaded.    */
#define ERROR_PRINTER_DRIVER_ALREADY_INSTALLED      1795            /*  The specified printer driver is already installed.  */
#define ERROR_UNKNOWN_PORT                          1796            /*  The specified port is unknown.  */
#define ERROR_UNKNOWN_PRINTER_DRIVER                1797            /*  The printer driver is unknown.  */
#define ERROR_UNKNOWN_PRINTPROCESSOR                1798            /*  The print processor is unknown. */
#define ERROR_INVALID_SEPARATOR_FILE                1799            /*  The specified separator file is invalid.    */
#define ERROR_INVALID_PRIORITY                      1800            /*  The specified priority is invalid.  */
#define ERROR_INVALID_PRINTER_NAME                  1801            /*  The printer name is invalid.    */
#define ERROR_PRINTER_ALREADY_EXISTS                1802            /*  The printer already exists. */
#define ERROR_INVALID_PRINTER_COMMAND               1803            /*  The printer command is invalid. */
#define ERROR_INVALID_DATATYPE                      1804            /*  The specified data type is invalid. */
#define ERROR_INVALID_ENVIRONMENT                   1805            /*  The environment specified is invalid.   */
#define RPC_S_NO_MORE_BINDINGS                      1806            /*  There are no more bindings. */
#define ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT     1807            /*  The account used is an interdomain trust account. Use your global user account or local user account to access this server. */
#define ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT     1808            /*  The account used is a computer account. Use your global user account or local user account to access this server.   */
#define ERROR_NOLOGON_SERVER_TRUST_ACCOUNT          1809            /*  The account used is a server trust account. Use your global user account or local user account to access this server.   */
#define ERROR_DOMAIN_TRUST_INCONSISTENT             1810            /*  The name or security identifier (SID) of the domain specified is inconsistent with the trust information for that domain.   */
#define ERROR_SERVER_HAS_OPEN_HANDLES               1811            /*  The server is in use and cannot be unloaded.    */
#define ERROR_RESOURCE_DATA_NOT_FOUND               1812            /*  The specified image file did not contain a resource section.    */
#define ERROR_RESOURCE_TYPE_NOT_FOUND               1813            /*  The specified resource type cannot be found in the image file.  */
#define ERROR_RESOURCE_NAME_NOT_FOUND               1814            /*  The specified resource name cannot be found in the image file.  */
#define ERROR_RESOURCE_LANG_NOT_FOUND               1815            /*  The specified resource language identifier cannot be found in the image file.   */
#define ERROR_NOT_ENOUGH_QUOTA                      1816            /*  Not enough quota is available to process this command.  */
#define RPC_S_NO_INTERFACES                         1817            /*  No interfaces have been registered. */
#define RPC_S_CALL_CANCELLED                        1818            /*  The server was altered while processing this call.  */
#define RPC_S_BINDING_INCOMPLETE                    1819            /*  The binding handle does not contain all required information.   */
#define RPC_S_COMM_FAILURE                          1820            /*  Communications failure. */
#define RPC_S_UNSUPPORTED_AUTHN_LEVEL               1821            /*  The requested authentication level is not supported.    */
#define RPC_S_NO_PRINC_NAME                         1822            /*  No principal name registered.   */
#define RPC_S_NOT_RPC_ERROR                         1823            /*  The error specified is not a valid Windows NT RPC error value.  */
#define RPC_S_UUID_LOCAL_ONLY                       1824            /*  A UUID that is valid only on this computer has been allocated.  */
#define RPC_S_SEC_PKG_ERROR                         1825            /*  A security package specific error occurred. */
#define RPC_S_NOT_CANCELLED                         1826            /*  Thread is not canceled. */
#define RPC_X_INVALID_ES_ACTION                     1827            /*  Invalid operation on the encoding/decoding handle.  */
#define RPC_X_WRONG_ES_VERSION                      1828            /*  Incompatible version of the serializing package.    */
#define RPC_X_WRONG_STUB_VERSION                    1829            /*  Incompatible version of the RPC stub.   */
#define RPC_X_INVALID_PIPE_OBJECT                   1830            /*  The idl pipe object is invalid or corrupted.    */
#define RPC_X_INVALID_PIPE_OPERATION                1831            /*  The operation is invalid for a given idl pipe object.   */
#define RPC_X_WRONG_PIPE_VERSION                    1832            /*  The Interface Definition Language (IDL) pipe version is not supported.  */
#define RPC_S_GROUP_MEMBER_NOT_FOUND                1898            /*  The group member was not found. */
#define EPT_S_CANT_CREATE                           1899            /*  The endpoint mapper database could not be created.  */
#define RPC_S_INVALID_OBJECT                        1900            /*  The object UUID is the nil UUID.    */
#define ERROR_INVALID_TIME                          1901            /*  The specified time is invalid.  */
#define ERROR_INVALID_FORM_NAME                     1902            /*  The specified form name is invalid. */
#define ERROR_INVALID_FORM_SIZE                     1903            /*  The specified form size is invalid. */
#define ERROR_ALREADY_WAITING                       1904            /*  The specified printer handle is already being waited on */
#define ERROR_PRINTER_DELETED                       1905            /*  The specified printer has been deleted. */
#define ERROR_INVALID_PRINTER_STATE                 1906            /*  The state of the printer is invalid.    */
#define ERROR_PASSWORD_MUST_CHANGE                  1907            /*  The user must change his password before he logs on the first time. */
#define ERROR_DOMAIN_CONTROLLER_NOT_FOUND           1908            /*  Could not find the domain controller for this domain.   */
#define ERROR_ACCOUNT_LOCKED_OUT                    1909            /*  The referenced account is currently locked out and may not be logged on to. */
#define OR_INVALID_OXID                             1910            /*  The object exporter specified was not found.    */
#define OR_INVALID_OID                              1911            /*  The object specified was not found. */
#define OR_INVALID_SET                              1912            /*  The object resolver set specified was not found.    */
#define RPC_S_SEND_INCOMPLETE                       1913            /*  Some data remains to be sent in the request buffer. */
#define ERROR_INVALID_PIXEL_FORMAT                  2000            /*  The pixel format is invalid.    */
#define ERROR_BAD_DRIVER                            2001            /*  The specified driver is invalid.    */
#define ERROR_INVALID_WINDOW_STYLE                  2002            /*  The window style or class attribute is invalid for this operation.  */
#define ERROR_METAFILE_NOT_SUPPORTED                2003            /*  The requested metafile operation is not supported.  */
#define ERROR_TRANSFORM_NOT_SUPPORTED               2004            /*  The requested transformation operation is not supported.    */
#define ERROR_CLIPPING_NOT_SUPPORTED                2005            /*  The requested clipping operation is not supported.  */
#define ERROR_BAD_USERNAME                          2202            /*  The specified user name is invalid. */
#define ERROR_NOT_CONNECTED                         2250            /*  This network connection does not exist. */
#define ERROR_OPEN_FILES                            2401            /*  This network connection has files open or requests pending. */
#define ERROR_ACTIVE_CONNECTIONS                    2402            /*  Active connections still exist. */
#define ERROR_DEVICE_IN_USE                         2404            /*  The device is in use by an active process and cannot be disconnected.   */
#define ERROR_UNKNOWN_PRINT_MONITOR                 3000            /*  The specified print monitor is unknown. */
#define ERROR_PRINTER_DRIVER_IN_USE                 3001            /*  The specified printer driver is currently in use.   */
#define ERROR_SPOOL_FILE_NOT_FOUND                  3002            /*  The spool file was not found.   */
#define ERROR_SPL_NO_STARTDOC                       3003            /*  A StartDocPrinter call was not issued.  */
#define ERROR_SPL_NO_ADDJOB                         3004            /*  An AddJob call was not issued.  */
#define ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED     3005            /*  The specified print processor has already been installed.   */
#define ERROR_PRINT_MONITOR_ALREADY_INSTALLED       3006            /*  The specified print monitor has already been installed. */
#define ERROR_INVALID_PRINT_MONITOR                 3007            /*  The specified print monitor does not have the required functions.   */
#define ERROR_PRINT_MONITOR_IN_USE                  3008            /*  The specified print monitor is currently in use.    */
#define ERROR_PRINTER_HAS_JOBS_QUEUED               3009            /*  The requested operation is not allowed when there are jobs queued to the printer.   */
#define ERROR_SUCCESS_REBOOT_REQUIRED               3010            /*  The requested operation is successful. Changes will not be effective until the system is rebooted.  */
#define ERROR_SUCCESS_RESTART_REQUIRED              3011            /*  The requested operation is successful. Changes will not be effective until the service is restarted.    */
#define ERROR_WINS_INTERNAL                         4000            /*  WINS encountered an error while processing the command. */
#define ERROR_CAN_NOT_DEL_LOCAL_WINS                4001            /*  The local WINS cannot be deleted.   */
#define ERROR_STATIC_INIT                           4002            /*  The importation from the file failed.   */
#define ERROR_INC_BACKUP                            4003            /*  The backup failed. Was a full backup done before?   */
#define ERROR_FULL_BACKUP                           4004            /*  The backup failed. Check the directory to which you are backing the database.   */
#define ERROR_REC_NON_EXISTENT                      4005            /*  The name does not exist in the WINS database.   */
#define ERROR_RPL_NOT_ALLOWED                       4006            /*  Replication with a nonconfigured partner is not allowed.    */
#define ERROR_NO_BROWSER_SERVERS_FOUND              6118            /*  The list of servers for this workgroup is not currently available.  */



/****Net errors***/
#define NERR_NetNotStarted                          2102            /*  The workstation driver is not installed.    */
#define NERR_UnknownServer                          2103            /*  The server could not be located.    */
#define NERR_ShareMem                               2104            /*  An internal error occurred. The network cannot access a shared memory segment.  */
#define NERR_RemoteOnly                             2106            /*  This operation is not supported on workstations.    */
#define NERR_DevNotRedirected                       2107            /*  The device is not connected.    */
#define NERR_ServerNotStarted                       2114            /*  The Server service is not started.  */
#define NERR_ItemNotFound                           2115            /*  The queue is empty. */
#define NERR_UnknownDevDir                          2116            /*  The device or directory does not exist. */
#define NERR_RedirectedPath                         2117            /*  The operation is invalid on a redirected resource.  */
#define NERR_DuplicateShare                         2118            /*  The name has already been shared.   */
#define NERR_NoRoom                                 2119            /*  The server is currently out of the requested resource.  */
#define NERR_TooManyItems                           2121            /*  Requested addition of items exceeds the maximum allowed.    */
#define NERR_InvalidMaxUsers                        2122            /*  The Peer service supports only two simultaneous users.  */
#define NERR_BufTooSmall                            2123            /*  The API return buffer is too small. */
#define NERR_RemoteErr                              2127            /*  A remote API error occurred.    */
#define NERR_LanmanIniError                         2131            /*  An error occurred when opening or reading the configuration file.   */
#define NERR_NetworkError                           2136            /*  A general network error occurred.   */
#define NERR_WkstaInconsistentState                 2137            /*  The Workstation service is in an inconsistent state. Restart the computer before restarting the Workstation service.    */
#define NERR_WkstaNotStarted                        2138            /*  The Workstation service has not been started.   */
#define NERR_BrowserNotStarted                      2139            /*  The requested information is not available. */
#define NERR_InternalError                          2140            /*  An internal Windows NT error occurred.  */
#define NERR_BadTransactConfig                      2141            /*  The server is not configured for transactions.  */
#define NERR_InvalidAPI                             2142            /*  The requested API is not supported on the remote server.    */
#define NERR_BadEventName                           2143            /*  The event name is invalid.  */
#define NERR_DupNameReboot                          2144            /*  The computer name already exists on the network. Change it and restart the computer.    */
#define NERR_CfgCompNotFound                        2146            /*  The specified component could not be found in the configuration information.    */
#define NERR_CfgParamNotFound                       2147            /*  The specified parameter could not be found in the configuration information.    */
#define NERR_LineTooLong                            2149            /*  A line in the configuration file is too long.   */
#define NERR_QNotFound                              2150            /*  The printer does not exist. */
#define NERR_JobNotFound                            2151            /*  The print job does not exist.   */
#define NERR_DestNotFound                           2152            /*  The printer destination cannot be found.    */
#define NERR_DestExists                             2153            /*  The printer destination already exists. */
#define NERR_QExists                                2154            /*  The printer queue already exists.   */
#define NERR_NoNetworkResource                      2155            /*  A network resource shortage occurred.   */
#define NERR_QNoRoom                                2155            /*  No more printers can be added.  */
#define NERR_JobNoRoom                              2156            /*  No more print jobs can be added.    */
#define NERR_DestNoRoom                             2157            /*  No more printer destinations can be added.  */
#define NERR_DestIdle                               2158            /*  This printer destination is idle and cannot accept control operations.  */
#define NERR_DestInvalidOp                          2159            /*  This printer destination request contains an invalid control function.  */
#define NERR_ProcNoRespond                          2160            /*  The print processor is not responding.  */
#define NERR_SpoolerNotLoaded                       2161            /*  The spooler is not running. */
#define NERR_DestInvalidState                       2162            /*  This operation cannot be performed on the print destination in its current state.   */
#define NERR_QInvalidState                          2163            /*  This operation cannot be performed on the printer queue in its current state.   */
#define NERR_JobInvalidState                        2164            /*  This operation cannot be performed on the print job in its current state.   */
#define NERR_SpoolNoMemory                          2165            /*  A spooler memory allocation failure occurred.   */
#define NERR_DriverNotFound                         2166            /*  The device driver does not exist.   */
#define NERR_DataTypeInvalid                        2167            /*  The data type is not supported by the print processor.  */
#define NERR_ProcNotFound                           2168            /*  The print processor is not installed.   */
#define NERR_ServiceTableLocked                     2180            /*  The service database is locked. */
#define NERR_ServiceTableFull                       2181            /*  The service table is full.  */
#define NERR_ServiceInstalled                       2182            /*  The requested service has already been started. */
#define NERR_ServiceEntryLocked                     2183            /*  The service does not respond to control actions.    */
#define NERR_ServiceNotInstalled                    2184            /*  The service has not been started.   */
#define NERR_BadServiceName                         2185            /*  The service name is invalid.    */
#define NERR_ServiceCtlTimeout                      2186            /*  The service is not responding to the control function.  */
#define NERR_ServiceCtlBusy                         2187            /*  The service control is busy.    */
#define NERR_BadServiceProgName                     2188            /*  The configuration file contains an invalid service program name.    */
#define NERR_ServiceNotCtrl                         2189            /*  The service could not be controlled in its present state.   */
#define NERR_ServiceKillProc                        2190            /*  The service ended abnormally.   */
#define NERR_ServiceCtlNotValid                     2191            /*  The requested pause or stop is not valid for this service.  */
#define NERR_NotInDispatchTbl                       2192            /*  The service control dispatcher could not find the service name in the dispatch table.   */
#define NERR_BadControlRecv                         2193            /*  The service control dispatcher pipe read failed.    */
#define NERR_ServiceNotStarting                     2194            /*  A thread for the new service could not be created.  */
#define NERR_AlreadyLoggedOn                        2200            /*  This workstation is already logged on to the local-area network.    */
#define NERR_NotLoggedOn                            2201            /*  The workstation is not logged on to the local-area network. */
#define NERR_BadUsername                            2202            /*  The user name or group name parameter is invalid.   */
#define NERR_BadPassword                            2203            /*  The password parameter is invalid.  */
#define NERR_UnableToAddName_W                      2204            /*  The logon processor did not add the message alias.  */
#define NERR_UnableToAddName_F                      2205            /*  The logon processor did not add the message alias.  */
#define NERR_UnableToDelName_W                      2206            /*  The logoff processor did not delete the message alias.  */
#define NERR_UnableToDelName_F                      2207            /*  The logoff processor did not delete the message alias.  */
#define NERR_LogonsPaused                           2209            /*  Network logons are paused.  */
#define NERR_LogonServerConflict                    2210            /*  A centralized logon-server conflict occurred.   */
#define NERR_LogonNoUserPath                        2211            /*  The server is configured without a valid user path. */
#define NERR_LogonScriptError                       2212            /*  An error occurred while loading or running the logon script.    */
#define NERR_StandaloneLogon                        2214            /*  The logon server was not specified. Your computer will be logged on as STANDALONE.  */
#define NERR_LogonServerNotFound                    2215            /*  The logon server could not be found.    */
#define NERR_LogonDomainExists                      2216            /*  There is already a logon domain for this computer.  */
#define NERR_NonValidatedLogon                      2217            /*  The logon server could not validate the logon.  */
#define NERR_ACFNotFound                            2219            /*  The security database could not be found.   */
#define NERR_GroupNotFound                          2220            /*  The group name could not be found.  */
#define NERR_UserNotFound                           2221            /*  The user name could not be found.   */
#define NERR_ResourceNotFound                       2222            /*  The resource name could not be found.   */
#define NERR_GroupExists                            2223            /*  The group already exists.   */
#define NERR_UserExists                             2224            /*  The user account already exists.    */
#define NERR_ResourceExists                         2225            /*  The resource permission list already exists.    */
#define NERR_NotPrimary                             2226            /*  This operation is only allowed on the primary domain controller of the domain.  */
#define NERR_ACFNotLoaded                           2227            /*  The security database has not been started. */
#define NERR_ACFNoRoom                              2228            /*  There are too many names in the user accounts database. */
#define NERR_ACFFileIOFail                          2229            /*  A disk I/O failure occurred.    */
#define NERR_ACFTooManyLists                        2230            /*  The limit of 64 entries per resource was exceeded.  */
#define NERR_UserLogon                              2231            /*  Deleting a user with a session is not allowed.  */
#define NERR_ACFNoParent                            2232            /*  The parent directory could not be located.  */
#define NERR_CanNotGrowSegment                      2233            /*  Unable to add to the security database session cache segment.   */
#define NERR_SpeGroupOp                             2234            /*  This operation is not allowed on this special group.    */
#define NERR_NotInCache                             2235            /*  This user is not cached in user accounts database session cache.    */
#define NERR_UserInGroup                            2236            /*  The user already belongs to this group. */
#define NERR_UserNotInGroup                         2237            /*  The user does not belong to this group. */
#define NERR_AccountUndefined                       2238            /*  This user account is undefined. */
#define NERR_AccountExpired                         2239            /*  This user account has expired.  */
#define NERR_InvalidWorkstation                     2240            /*  The user is not allowed to log on from this workstation.    */
#define NERR_InvalidLogonHours                      2241            /*  The user is not allowed to log on at this time. */
#define NERR_PasswordExpired                        2242            /*  The password of this user has expired.  */
#define NERR_PasswordCantChange                     2243            /*  The password of this user cannot change.    */
#define NERR_PasswordHistConflict                   2244            /*  This password cannot be used now.   */
#define NERR_PasswordTooShort                       2245            /*  The password is shorter than required.  */
#define NERR_PasswordTooRecent                      2246            /*  The password of this user is too recent to change.  */
#define NERR_InvalidDatabase                        2247            /*  The security database is corrupted. */
#define NERR_DatabaseUpToDate                       2248            /*  No updates are necessary to this replicant network/local security database. */
#define NERR_SyncRequired                           2249            /*  This replicant database is outdated; synchronization is required.   */
#define NERR_UseNotFound                            2250            /*  The network connection could not be found.  */
#define NERR_BadAsgType                             2251            /*  This asg_type is invalid.   */
#define NERR_DeviceIsShared                         2252            /*  This device is currently being shared.  */
#define NERR_NoComputerName                         2270            /*  The computer name could not be added as a message alias. The name may already exist on the network. */
#define NERR_MsgAlreadyStarted                      2271            /*  The Messenger service is already started.   */
#define NERR_MsgInitFailed                          2272            /*  The Messenger service failed to start.  */
#define NERR_NameNotFound                           2273            /*  The message alias could not be found on the network.    */
#define NERR_AlreadyForwarded                       2274            /*  This message alias has already been forwarded.  */
#define NERR_AddForwarded                           2275            /*  This message alias has been added but is still forwarded.   */
#define NERR_AlreadyExists                          2276            /*  This message alias already exists locally.  */
#define NERR_TooManyNames                           2277            /*  The maximum number of added message aliases has been exceeded.  */
#define NERR_DelComputerName                        2278            /*  The computer name could not be deleted. */
#define NERR_LocalForward                           2279            /*  Messages cannot be forwarded back to the same workstation.  */
#define NERR_GrpMsgProcessor                        2280            /*  An error occurred in the domain message processor.  */
#define NERR_PausedRemote                           2281            /*  The message was sent.   */
#define NERR_BadReceive                             2282            /*  The message was sent but not received.  */
#define NERR_NameInUse                              2283            /*  The message alias is currently in use. Try again later. */
#define NERR_MsgNotStarted                          2284            /*  The Messenger service has not been started. */
#define NERR_NotLocalName                           2285            /*  The name is not on the local computer.  */
#define NERR_NoForwardName                          2286            /*  The forwarded message alias could not be found on the network.  */
#define NERR_RemoteFull                             2287            /*  The message alias table on the remote station is full.  */
#define NERR_NameNotForwarded                       2288            /*  Messages for this alias are not currently being forwarded.  */
#define NERR_TruncatedBroadcast                     2289            /*  The broadcast message was truncated.    */
#define NERR_InvalidDevice                          2294            /*  This is an invalid device name. */
#define NERR_WriteFault                             2295            /*  A write fault occurred. */
#define NERR_DuplicateName                          2297            /*  A duplicate message alias exists on the network.    */
#define NERR_DeleteLater                            2298            /*  This message alias will be deleted later.   */
#define NERR_IncompleteDel                          2299            /*  The message alias was not successfully deleted from all networks.   */
#define NERR_MultipleNets                           2300            /*  This operation is not supported on computers with multiple networks.    */
#define NERR_NetNameNotFound                        2310            /*  This shared resource does not exist.    */
#define NERR_DeviceNotShared                        2311            /*  This device is not shared.  */
#define NERR_ClientNameNotFound                     2312            /*  A session does not exist with that computer name.   */
#define NERR_FileIdNotFound                         2314            /*  There is not an open file with that identification number.  */
#define NERR_ExecFailure                            2315            /*  A failure occurred when executing a remote administration command.  */
#define NERR_TmpFile                                2316            /*  A failure occurred when opening a remote temporary file.    */
#define NERR_TooMuchData                            2317            /*  The data returned from a remote administration command has been truncated to 64 KB. */
#define NERR_DeviceShareConflict                    2318            /*  This device cannot be shared as both a spooled and a nonspooled resource.   */
#define NERR_BrowserTableIncomplete                 2319            /*  The information in the list of servers may be incorrect.    */
#define NERR_NotLocalDomain                         2320            /*  The computer is not active in this domain.  */
#define NERR_IsDfsShare                             2321            /*  The share must be removed from the Dfs before it can be deleted.    */
#define NERR_DevInvalidOpCode                       2331            /*  The operation is invalid for this device.   */
#define NERR_DevNotFound                            2332            /*  This device cannot be shared.   */
#define NERR_DevNotOpen                             2333            /*  This device was not open.   */
#define NERR_BadQueueDevString                      2334            /*  This device name list is invalid.   */
#define NERR_BadQueuePriority                       2335            /*  The queue priority is invalid.  */
#define NERR_NoCommDevs                             2337            /*  There are no shared communication devices.  */
#define NERR_QueueNotFound                          2338            /*  The queue you specified does not exist. */
#define NERR_BadDevString                           2340            /*  This list of devices is invalid.    */
#define NERR_BadDev                                 2341            /*  The requested device is invalid.    */
#define NERR_InUseBySpooler                         2342            /*  This device is already in use by the spooler.   */
#define NERR_CommDevInUse                           2343            /*  This device is already in use as a communication device.    */
#define NERR_InvalidComputer                        2351            /*  This computer name is invalid.  */
#define NERR_MaxLenExceeded                         2354            /*  The specified string and prefix are too long.   */
#define NERR_BadComponent                           2356            /*  This path component is invalid. */
#define NERR_CantType                               2357            /*  Could not determine the type of input.  */
#define NERR_TooManyEntries                         2362            /*  The buffer for types is not big enough. */
#define NERR_ProfileFileTooBig                      2370            /*  Profile files cannot exceed 64 KB.  */
#define NERR_ProfileOffset                          2371            /*  The start offset is out of range.   */
#define NERR_ProfileCleanup                         2372            /*  The system cannot delete current connections to network resources.  */
#define NERR_ProfileUnknownCmd                      2373            /*  The system was unable to parse the command line in this file.   */
#define NERR_ProfileLoadErr                         2374            /*  An error occurred while loading the profile file.   */
#define NERR_ProfileSaveErr                         2375            /*  Errors occurred while saving the profile file. The profile was partially saved. */
#define NERR_LogOverflow                            2377            /*  Log file %1 is full.    */
#define NERR_LogFileChanged                         2378            /*  This log file has changed between reads.    */
#define NERR_LogFileCorrupt                         2379            /*  Log file %1 is corrupt. */
#define NERR_SourceIsDir                            2380            /*  The source path cannot be a directory.  */
#define NERR_BadSource                              2381            /*  The source path is illegal. */
#define NERR_BadDest                                2382            /*  The destination path is illegal.    */
#define NERR_DifferentServers                       2383            /*  The source and destination paths are on different servers.  */
#define NERR_RunSrvPaused                           2385            /*  The Run server you requested is paused. */
#define NERR_ErrCommRunSrv                          2389            /*  An error occurred when communicating with a Run server. */
#define NERR_ErrorExecingGhost                      2391            /*  An error occurred when starting a background process.   */
#define NERR_ShareNotFound                          2392            /*  The shared resource you are connected to could not be found.    */
#define NERR_InvalidLana                            2400            /*  The LAN adapter number is invalid.  */
#define NERR_OpenFiles                              2401            /*  There are open files on the connection. */
#define NERR_ActiveConns                            2402            /*  Active connections still exist. */
#define NERR_BadPasswordCore                        2403            /*  This share name or password is invalid. */
#define NERR_DevInUse                               2404            /*  The device is being accessed by an active process.  */
#define NERR_LocalDrive                             2405            /*  The drive letter is in use locally. */
#define NERR_AlertExists                            2430            /*  The specified client is already registered for the specified event. */
#define NERR_TooManyAlerts                          2431            /*  The alert table is full.    */
#define NERR_NoSuchAlert                            2432            /*  An invalid or nonexistent alert name was raised.    */
#define NERR_BadRecipient                           2433            /*  The alert recipient is invalid. */
#define NERR_AcctLimitExceeded                      2434            /*  A user's session with this server has been deleted because the user's logon hours are no longer valid.  */
#define NERR_InvalidLogSeek                         2440            /*  The log file does not contain the requested record number.  */
#define NERR_BadUasConfig                           2450            /*  The user accounts database is not configured correctly. */
#define NERR_InvalidUASOp                           2451            /*  This operation is not permitted when the Netlogon service is running.   */
#define NERR_LastAdmin                              2452            /*  This operation is not allowed on the last administrative account.   */
#define NERR_DCNotFound                             2453            /*  Could not find domain controller for this domain.   */
#define NERR_LogonTrackingError                     2454            /*  Could not set logon information for this user.  */
#define NERR_NetlogonNotStarted                     2455            /*  The Netlogon service has not been started.  */
#define NERR_CanNotGrowUASFile                      2456            /*  Unable to add to the user accounts database.    */
#define NERR_TimeDiffAtDC                           2457            /*  This server's clock is not synchronized with the primary domain controller's clock. */
#define NERR_PasswordMismatch                       2458            /*  A password mismatch has been detected.  */
#define NERR_NoSuchServer                           2460            /*  The server identification does not specify a valid server.  */
#define NERR_NoSuchSession                          2461            /*  The session identification does not specify a valid session.    */
#define NERR_NoSuchConnection                       2462            /*  The connection identification does not specify a valid connection.  */
#define NERR_TooManyServers                         2463            /*  There is no space for another entry in the table of available servers.  */
#define NERR_TooManySessions                        2464            /*  The server has reached the maximum number of sessions it supports.  */
#define NERR_TooManyConnections                     2465            /*  The server has reached the maximum number of connections it supports.   */
#define NERR_TooManyFiles                           2466            /*  The server cannot open more files because it has reached its maximum number.    */
#define NERR_NoAlternateServers                     2467            /*  There are no alternate servers registered on this server.   */
#define NERR_TryDownLevel                           2470            /*  Try the down-level, or remote admin protocol, version of API instead.   */
#define NERR_UPSDriverNotStarted                    2480            /*  The UPS driver could not be accessed by the UPS service.    */
#define NERR_UPSInvalidConfig                       2481            /*  The UPS service is not configured correctly.    */
#define NERR_UPSInvalidCommPort                     2482            /*  The UPS service could not access the specified communications port. */
#define NERR_UPSSignalAsserted                      2483            /*  The UPS indicated a line fail or low battery situation. Service not started.    */
#define NERR_UPSShutdownFailed                      2484            /*  The UPS service failed to perform a system shut down.   */
#define NERR_BadDosRetCode                          2500            /*  The program below returned an MS-DOS error code.    */
#define NERR_ProgNeedsExtraMem                      2501            /*  The program below needs more memory.    */
#define NERR_BadDosFunction                         2502            /*  The program below called an unsupported MS-DOS function.    */
#define NERR_RemoteBootFailed                       2503            /*  The workstation failed to boot. */
#define NERR_BadFileCheckSum                        2504            /*  The file below is corrupt.  */
#define NERR_NoRplBootSystem                        2505            /*  No loader is specified in the boot-block definition file.   */
#define NERR_RplLoadrNetBiosErr                     2506            /*  NetBIOS returned an error — the NCB and SMB are dumped above.  */
#define NERR_RplLoadrDiskErr                        2507            /*  A disk I/O error occurred.  */
#define NERR_ImageParamErr                          2508            /*  Image parameter substitution failed.    */
#define NERR_TooManyImageParams                     2509            /*  Too many image parameters cross disk sector boundaries. */
#define NERR_NonDosFloppyUsed                       2510            /*  The image was not generated from an MS-DOS diskette formatted with the /S option.   */
#define NERR_RplBootRestart                         2511            /*  Remote boot will be restarted later.    */
#define NERR_RplSrvrCallFailed                      2512            /*  The call to the Remoteboot server failed.   */
#define NERR_CantConnectRplSrvr                     2513            /*  Cannot connect to the Remoteboot server.    */
#define NERR_CantOpenImageFile                      2514            /*  Cannot open image file on the Remoteboot server.    */
#define NERR_CallingRplSrvr                         2515            /*  Connecting to the Remoteboot server.    */
#define NERR_StartingRplBoot                        2516            /*  Connecting to the Remoteboot server.    */
#define NERR_RplBootServiceTerm                     2517            /*  Remote boot service was stopped; check the error log for the cause of the problem.  */
#define NERR_RplBootStartFailed                     2518            /*  Remote boot startup failed; check the error log for the cause of the problem.   */
#define NERR_RPL_CONNECTED                          2519            /*  A second connection to a Remoteboot resource is not allowed.    */
#define NERR_BrowserConfiguredToNotRun              2550            /*  The browser service was configured with MaintainServerList=No.  */
#define NERR_RplNoAdaptersStarted                   2610            /*  Service failed to start because none of the network adapters started with this service. */
#define NERR_RplBadRegistry                         2611            /*  Service failed to start due to bad startup information in the registry. */
#define NERR_RplBadDatabase                         2612            /*  Service failed to start because its database is absent or corrupt.  */
#define NERR_RplRplfilesShare                       2613            /*  Service failed to start because RPLFILES share is absent.   */
#define NERR_RplNotRplServer                        2614            /*  Service failed to start because RPLUSER group is absent.    */
#define NERR_RplCannotEnum                          2615            /*  Cannot enumerate service records.   */
#define NERR_RplWkstaInfoCorrupted                  2616            /*  Workstation record information has been corrupted.  */
#define NERR_RplWkstaNotFound                       2617            /*  Workstation record was not found.   */
#define NERR_RplWkstaNameUnavailable                2618            /*  Workstation name is in use by some other workstation.   */
#define NERR_RplProfileInfoCorrupted                2619            /*  Profile record information has been corrupted.  */
#define NERR_RplProfileNotFound                     2620            /*  Profile record was not found.   */
#define NERR_RplProfileNameUnavailable              2621            /*  Profile name is in use by some other profile.   */
#define NERR_RplProfileNotEmpty                     2622            /*  There are workstations using this profile.  */
#define NERR_RplConfigInfoCorrupted                 2623            /*  Configuration record information has been corrupted.    */
#define NERR_RplConfigNotFound                      2624            /*  Configuration record was not found. */
#define NERR_RplAdapterInfoCorrupted                2625            /*  Adapter id record information has been corrupted.   */
#define NERR_RplInternal                            2626            /*  An internal service error has occurred. */
#define NERR_RplVendorInfoCorrupted                 2627            /*  Vendor id record information has been corrupted.    */
#define NERR_RplBootInfoCorrupted                   2628            /*  Boot block record information has been corrupted.   */
#define NERR_RplWkstaNeedsUserAcct                  2629            /*  The user account for this workstation record is missing.    */
#define NERR_RplNeedsRPLUSERAcct                    2630            /*  The RPLUSER local group could not be found. */
#define NERR_RplBootNotFound                        2631            /*  Boot block record was not found.    */
#define NERR_RplIncompatibleProfile                 2632            /*  Chosen profile is incompatible with this workstation.   */
#define NERR_RplAdapterNameUnavailable              2633            /*  Chosen network adapter id is in use by some other workstation.  */
#define NERR_RplConfigNotEmpty                      2634            /*  There are profiles using this configuration.    */
#define NERR_RplBootInUse                           2635            /*  There are workstations. */
#define NERR_RplBackupDatabase                      2636            /*  Service failed to backup Remoteboot database.   */
#define NERR_RplAdapterNotFound                     2637            /*  Adapter record was not found.   */
#define NERR_RplVendorNotFound                      2638            /*  Vendor record was not found.    */
#define NERR_RplVendorNameUnavailable               2639            /*  Vendor name is in use by some other vendor record.  */
#define NERR_RplBootNameUnavailable                 2640            /*  The boot name or vendor identifier is in use by some other boot block record.   */
#define NERR_RplConfigNameUnavailable               2641            /*  Configuration name is in use by some other configuration.   */
#define NERR_DfsInternalCorruption                  2660            /*  The internal database maintained by the Dfs service is corrupt. */
#define NERR_DfsVolumeDataCorrupt                   2661            /*  One of the records in the internal Dfs database is corrupt. */
#define NERR_DfsNoSuchVolume                        2662            /*  There is no volume whose entry path matches the input entry path.   */
#define NERR_DfsVolumeAlreadyExists                 2663            /*  A volume with the given name already exists.    */
#define NERR_DfsAlreadyShared                       2664            /*  The server share specified is already shared in the Dfs.    */
#define NERR_DfsNoSuchShare                         2665            /*  The indicated server share does not support the indicated Dfs volume.   */
#define NERR_DfsNotALeafVolume                      2666            /*  The operation is not valid on a non-leaf volume.    */
#define NERR_DfsLeafVolume                          2667            /*  The operation is not valid on a leaf volume.    */
#define NERR_DfsVolumeHasMultipleServers            2668            /*  The operation is ambiguous because the volume has multiple servers. */
#define NERR_DfsCantCreateJunctionPoint             2669            /*  Unable to create a junction point.  */
#define NERR_DfsServerNotDfsAware                   2670            /*  The server is not Dfs Aware.    */
#define NERR_DfsBadRenamePath                       2671            /*  The specified rename target path is invalid.    */
#define NERR_DfsVolumeIsOffline                     2672            /*  The specified Dfs volume is offline.    */
#define NERR_DfsNoSuchServer                        2673            /*  The specified server is not a server for this volume.   */
#define NERR_DfsCyclicalName                        2674            /*  A cycle in the Dfs name was detected.   */
#define NERR_DfsNotSupportedInServerDfs             2675            /*  The operation is not supported on a server-based Dfs.   */
#define NERR_DfsInternalError                       2690            /*  Dfs internal error. */


/***RAS Error Values****/
#define PENDING                                     600         /*An operation is pending  */
#define ERROR_INVALID_PORT_HANDLE                   601         /*An invalid port handle was detected.  */
#define ERROR_PORT_ALREADY_OPEN                     602         /* The specified port is already open. */
#define ERROR_BUFFER_TOO_SMALL                      603         /* The caller's buffer is too small. */
#define ERROR_WRONG_INFO_SPECIFIED                  604         /* Incorrect information was specified. */
#define ERROR_CANNOT_SET_PORT_INFO                  605         /*  The port information cannot be set. */
#define ERROR_PORT_NOT_CONNECTED                    606         /*The specified port is not connected.  */
#define ERROR_EVENT_INVALID                         607         /*  An invalid event was detected. */
#define ERROR_DEVICE_DOES_NOT_EXIST                 608         /** A device was specified that does not exist.   */
#define ERROR_DEVICETYPE_DOES_NOT_EXIST             609         /* * A device type was specified that does not exist. */
#define ERROR_BUFFER_INVALID                        610         /* * An invalid buffer was specified.  */
#define ERROR_ROUTE_NOT_AVAILABLE                   611         /* * A route was specified that is not available. */
#define ERROR_ROUTE_NOT_ALLOCATED                   612         /* * A route was specified that is not allocated.  */
#define ERROR_INVALID_COMPRESSION_SPECIFIED         613         /** An invalid compression was specified.   */
#define ERROR_OUT_OF_BUFFERS                        614         /** There were insufficient buffers available.   */
#define ERROR_PORT_NOT_FOUND                        615         /** The specified port was not found.   */
#define ERROR_ASYNC_REQUEST_PENDING                 616         /** An asynchronous request is pending.   */
#define ERROR_ALREADY_DISCONNECTING                 617         /** The modem (or other connecting device) is already disconnecting.   */
#define ERROR_PORT_NOT_OPEN                         618         /* * The specified port is not open.  */
#define ERROR_PORT_DISCONNECTED                     619         /** The specified port is not connected.   */
#define ERROR_NO_ENDPOINTS                          620         /** No endpoints could be determined.   */
#define ERROR_CANNOT_OPEN_PHONEBOOK                 621         /* The system could not open the phone book file.   */
#define ERROR_CANNOT_LOAD_PHONEBOOK                 622         /** The system could not load the phone book file.   */
#define ERROR_CANNOT_FIND_PHONEBOOK_ENTRY           623         /* * The system could not find the phone book entry for this connection.  */
#define ERROR_CANNOT_WRITE_PHONEBOOK                624         /* * The system could not update the phone book file.  */
#define ERROR_CORRUPT_PHONEBOOK                     625         /** The system found invalid information in the phone book file.   */
#define ERROR_CANNOT_LOAD_STRING                    626         /* * A string could not be loaded.  */
#define ERROR_KEY_NOT_FOUND                         627         /* * A key could not be found.  */
#define ERROR_DISCONNECTION                         628         /* * The connection was closed.  */
#define ERROR_REMOTE_DISCONNECTION                  629         /** The connection was closed by the remote computer.   */
#define ERROR_HARDWARE_FAILURE                      630         /* * The modem (or other connecting device) was disconnected due to hardware failure.  */
#define ERROR_USER_DISCONNECTION                    631         /* * The user disconnected the modem (or other connecting device).  */
#define ERROR_INVALID_SIZE                          632         /* * An incorrect structure size was detected.  */
#define ERROR_PORT_NOT_AVAILABLE                    633         /* * The modem (or other connecting device) is already in use or is not configured properly.  */
#define ERROR_CANNOT_PROJECT_CLIENT                 634         /** Your computer could not be registered on the remote network.   */
#define ERROR_UNKNOWN                               635         /** There was an unknown error.   */
#define ERROR_WRONG_DEVICE_ATTACHED                 636         /** The device attached to the port is not the one expected.   */
#define ERROR_BAD_STRING                            637         /*  * A string was detected that could not be converted. */
#define ERROR_REQUEST_TIMEOUT                       638         /* * The request has timed out.  */
#define ERROR_CANNOT_GET_LANA                       639         /** No asynchronous net is available.   */
#define ERROR_NETBIOS_ERROR                         640         /* * An error has occurred involving NetBIOS.  */
#define ERROR_SERVER_OUT_OF_RESOURCES               641         /* * The server cannot allocate NetBIOS resources needed to support the client.  */
#define ERROR_NAME_EXISTS_ON_NET                    642         /*  * One of your computer's NetBIOS names is already registered on the remote network. */
#define ERROR_SERVER_GENERAL_NET_FAILURE            643         /*  * A network adapter at the server failed. */
#define WARNING_MSG_ALIAS_NOT_ADDED                 644         /* * You will not receive network message popups.  */
#define ERROR_AUTH_INTERNAL                         645         /** There was an internal authentication error.  */
#define ERROR_RESTRICTED_LOGON_HOURS                646         /*   The account is not permitted to log on at this time of day. */
#define ERROR_ACCT_DISABLED                         647         /** The account is disabled. */
#define ERROR_PASSWD_EXPIRED                        648         /*  * The password for this account has expired. */
#define ERROR_NO_DIALIN_PERMISSION                  649         /*  * The account does not have permission to dial in. */
#define ERROR_SERVER_NOT_RESPONDING                 650         /* * The remote access server is not responding.  */
#define ERROR_FROM_DEVICE                           651         /* * The modem (or other connecting device) has reported an error.  */
#define ERROR_UNRECOGNIZED_RESPONSE                 652         /*  * There was an unrecognized response from the modem (or other connecting device). */
#define ERROR_MACRO_NOT_FOUND                       653         /* * A macro required by the modem (or other connecting device) was not found in the device.INF file.  */
#define ERROR_MACRO_NOT_DEFINED                     654         /*  * A command or response in the device.INF file section refers to an undefined macro. */
#define ERROR_MESSAGE_MACRO_NOT_FOUND               655         /*  * The <message> macro was not found in the device.INF file section. */
#define ERROR_DEFAULTOFF_MACRO_NOT_FOUND            656         /*  * The <default off> macro in the device.INF file section contains an undefined macro. */
#define ERROR_FILE_COULD_NOT_BE_OPENED              657         /*  * The device.INF file could not be opened. */
#define ERROR_DEVICENAME_TOO_LONG                   658         /*  * The device name in the device.INF or media.INI file is too long. */
#define ERROR_DEVICENAME_NOT_FOUND                  659         /* * The media.INI file refers to an unknown device name.  */
#define ERROR_NO_RESPONSES                          660         /* * The device.INF file contains no responses for the command.  */
#define ERROR_NO_COMMAND_FOUND                      661         /*  * The device.INF file is missing a command. */
#define ERROR_WRONG_KEY_SPECIFIED                   662         /*  * There was an attempt to set a macro not listed in device.INF file section. */
#define ERROR_UNKNOWN_DEVICE_TYPE                   663         /*  * The media.INI file refers to an unknown device type. */
#define ERROR_ALLOCATING_MEMORY                     664         /*  * The system has run out of memory. */
#define ERROR_PORT_NOT_CONFIGURED                   665         /* * The modem (or other connecting device) is not properly configured.  */
#define ERROR_DEVICE_NOT_READY                      666         /* * The modem (or other connecting device) is not functioning.  */
#define ERROR_READING_INI_FILE                      667         /*  * The system was unable to read the media.INI file. */
#define ERROR_NO_CONNECTION                         668         /* * The connection was terminated.  */
#define ERROR_BAD_USAGE_IN_INI_FILE                 669         /*  * The usage parameter in the media.INI file is invalid. */
#define ERROR_READING_SECTIONNAME                   670         /* * The system was unable to read the section name from the media.INI file.  */
#define ERROR_READING_DEVICETYPE                    671         /* * The system was unable to read the device type from the media.INI file.  */
#define ERROR_READING_DEVICENAME                    672         /** The system was unable to read the device name from the media.INI file.   */
#define ERROR_READING_USAGE                         673         /* * The system was unable to read the usage from the media.INI file.  */
#define ERROR_READING_MAXCONNECTBPS                 674         /* * The system was unable to read the maximum connection BPS rate from the media.INI file.  */
#define ERROR_READING_MAXCARRIERBPS                 675         /* * The system was unable to read the maximum carrier connection speed from the media.INI file.  */
#define ERROR_LINE_BUSY                             676         /** The phone line is busy.   */
#define ERROR_VOICE_ANSWER                          677         /** A person answered instead of a modem (or other connecting device).   */
#define ERROR_NO_ANSWER                             678         /** There was no answer.   */
#define ERROR_NO_CARRIER                            679         /* * The system could not detect the carrier.  */
#define ERROR_NO_DIALTONE                           680         /** There was no dial tone.   */
#define ERROR_IN_COMMAND                            681         /** The modem (or other connecting device) reported a general error.   */
#define ERROR_WRITING_SECTIONNAME                   682         /** There was an error in writing the section name.   */
#define ERROR_WRITING_DEVICETYPE                    683         /* * There was an error in writing the device type.  */
#define ERROR_WRITING_DEVICENAME                    684         /* * There was an error in writing the device name.  */
#define ERROR_WRITING_MAXCONNECTBPS                 685         /*  * There was an error in writing the maximum connection speed. */
#define ERROR_WRITING_MAXCARRIERBPS                 686         /*  * There was an error in writing the maximum carrier speed. */
#define ERROR_WRITING_USAGE                         687         /*  * There was an error in writing the usage. */
#define ERROR_WRITING_DEFAULTOFF                    688         /*  * There was an error in writing the default-off. */
#define ERROR_READING_DEFAULTOFF                    689         /*  * There was an error in reading the default-off. */
#define ERROR_EMPTY_INI_FILE                        690         /* *ERROR EMPTY INI FILE  */
#define ERROR_AUTHENTICATION_FAILURE                691         /* * Access was denied because the username and/or password was invalid on the domain.  */
#define ERROR_PORT_OR_DEVICE                        692         /* * There was a hardware failure in the modem (or other connecting device).  */
#define ERROR_NOT_BINARY_MACRO                      693         /* ERROR NOT BINARY MACRO */
#define ERROR_DCB_NOT_FOUND                         694         /*  ERROR DCB NOT FOUND*/
#define ERROR_STATE_MACHINES_NOT_STARTED            695         /* * The state machines are not started.  */
#define ERROR_STATE_MACHINES_ALREADY_STARTED        696         /* * The state machines are already started.  */
#define ERROR_PARTIAL_RESPONSE_LOOPING              697         /* * The response looping did not complete.  */
#define ERROR_UNKNOWN_RESPONSE_KEY                  698         /* * A response keyname in the device.INF file is not in the expected format.  */
#define ERROR_RECV_BUF_FULL                         699         /* * The modem (or other connecting device) response caused a buffer overflow.  */
#define ERROR_CMD_TOO_LONG                          700         /* * The expanded command in the device.INF file is too long.  */
#define ERROR_UNSUPPORTED_BPS                       701         /* * The modem moved to a connection speed not supported by the COM driver.  */
#define ERROR_UNEXPECTED_RESPONSE                   702         /*  * Device response received when none expected. */
#define ERROR_INTERACTIVE_MODE                      703         /* * The connection needs information from you, but the application does not allow user  */
#define ERROR_BAD_CALLBACK_NUMBER                   704         /* * The callback number is invalid.  */
#define ERROR_INVALID_AUTH_STATE                    705         /* * The authorization state is invalid.  */
#define ERROR_WRITING_INITBPS                       706         /* Initializing BPS error  */
#define ERROR_X25_DIAGNOSTIC                        707         /* * There was an error related to the X.25 protocol.  */
#define ERROR_ACCT_EXPIRED                          708         /* * The account has expired.  */
#define ERROR_CHANGING_PASSWORD                     709         /* * There was an error changing the password on the domain. The password might have been too short or might have matched a previously used password.  */
#define ERROR_OVERRUN                               710         /*  * Serial overrun errors were detected while communicating with the modem. */
#define ERROR_RASMAN_CANNOT_INITIALIZE              711         /* * The Remote Access Service Manager could not start. Additional information is provided in the event log.  */
#define ERROR_BIPLEX_PORT_NOT_AVAILABLE             712         /*  * The two-way port is initializing. Wait a few seconds and redial. */
#define ERROR_NO_ACTIVE_ISDN_LINES                  713         /* * No active ISDN lines are available.  */
#define ERROR_NO_ISDN_CHANNELS_AVAILABLE            714         /*  * No ISDN channels are available to make the call. */
#define ERROR_TOO_MANY_LINE_ERRORS                  715         /* * Too many errors occurred because of poor phone line quality.  */
#define ERROR_IP_CONFIGURATION                      716         /** The Remote Access Service IP configuration is unusable.   */
#define ERROR_NO_IP_ADDRESSES                       717         /** No IP addresses are available in the static pool of Remote Access Service IP addresses.   */
#define ERROR_PPP_TIMEOUT                           718         /** The connection timed out waiting for a valid response from the remote computer.   */
#define ERROR_PPP_REMOTE_TERMINATED                 719         /** The connection was terminated by the remote computer.   */
#define ERROR_PPP_NO_PROTOCOLS_CONFIGURED           720         /* * The connection attempt failed because your computer and the remote computer could not agree on PPP control protocols.  */
#define ERROR_PPP_NO_RESPONSE                       721         /* * The remote computer is not responding.  */
#define ERROR_PPP_INVALID_PACKET                    722         /** Invalid data was received from the remote computer. This data was ignored.   */
#define ERROR_PHONE_NUMBER_TOO_LONG                 723         /*  * The phone number, including prefix and suffix, is too long. */
#define ERROR_IPXCP_NO_DIALOUT_CONFIGURED           724         /* * The IPX protocol cannot dial out on the modem (or other connecting device) because this computer is not configured for dialing out (it is an IPX router).  */
#define ERROR_IPXCP_NO_DIALIN_CONFIGURED            725         /* * The IPX protocol cannot dial in on the modem (or other connecting device) because this computer is not configured for dialing in (the IPX router is not installed).  */
#define ERROR_IPXCP_DIALOUT_ALREADY_ACTIVE          726         /*  * The IPX protocol cannot be used for dialing out on more than one modem (or other connecting device) at a time. */
#define ERROR_ACCESSING_TCPCFGDLL                   727         /* * Cannot access TCPCFG.DLL.  */
#define ERROR_NO_IP_RAS_ADAPTER                     728         /* * The system cannot find an IP adapter.  */
#define ERROR_SLIP_REQUIRES_IP                      729         /* * SLIP cannot be used unless the IP protocol is installed.  */
#define ERROR_PROJECTION_NOT_COMPLETE               730         /*  * Computer registration is not complete. */
#define ERROR_PROTOCOL_NOT_CONFIGURED               731         /* * The protocol is not configured.  */
#define ERROR_PPP_NOT_CONVERGING                    732         /**Your computer and the remote computer could not agree on PPP control protocols.   */
#define ERROR_PPP_CP_REJECTED                       733         /* * Your computer and the remote computer could not agree on PPP control protocols.  */
#define ERROR_PPP_LCP_TERMINATED                    734         /*  * The PPP link control protocol was terminated. */
#define ERROR_PPP_REQUIRED_ADDRESS_REJECTED         735         /* * The requested address was rejected by the server.  */
#define ERROR_PPP_NCP_TERMINATED                    736         /*  * The remote computer terminated the control protocol. */
#define ERROR_PPP_LOOPBACK_DETECTED                 737         /* * Loopback was detected.  */
#define ERROR_PPP_NO_ADDRESS_ASSIGNED               738         /* * The server did not assign an address.  */
#define ERROR_CANNOT_USE_LOGON_CREDENTIALS          739         /* * The authentication protocol required by the remote server cannot use the stored password. Redial, entering the password explicitly.  */
#define ERROR_TAPI_CONFIGURATION                    740         /* * An invalid dialing rule was detected.  */
#define ERROR_NO_LOCAL_ENCRYPTION                   741         /*  * The local computer does not support the required data encryption type. */
#define ERROR_NO_REMOTE_ENCRYPTION                  742         /* * The remote computer does not support the required data encryption type.  */
#define ERROR_REMOTE_REQUIRES_ENCRYPTION            743         /* * The remote computer requires data encryption.  */
#define ERROR_IPXCP_NET_NUMBER_CONFLICT             744         /** The system cannot use the IPX network number assigned by the remote computer. Additional information is provided in the event log.   */
#define ERROR_INVALID_SMM                           745         /* The Session Management Module (SMM) is invalid. */
#define ERROR_SMM_UNINITIALIZED                     746         /* The SMM is uninitialized */
#define ERROR_NO_MAC_FOR_PORT                       747         /* No MAC for port. */
#define ERROR_SMM_TIMEOUT                           748         /*The SMM timed out.  */
#define ERROR_BAD_PHONE_NUMBER                      749         /*  A bad phone number was specified. */
#define ERROR_WRONG_MODULE                          750         /*  The wrong SMM was specified.*/
#define ERROR_PPP_MAC                               751         /* ERROR PPP MAC */
#define ERROR_PPP_LCP                               752         /* ERROR PPP LCP  */
#define ERROR_PPP_AUTH                              753         /*  ERROR PPP AUTH*/
#define ERROR_PPP_NCP                               754         /* ERROR PPP NCP */
#define ERROR_POWER_OFF                             755         /*  The serial device returned indication that power had been turned off.*/
#define ERROR_POWER_OFF_CD                          756         /* The serial device returned indication that power had been turned off,
                                                                                                        * and that Carrier Detect was currently asserted.
                                                                                                        * This is an indication that we are still in the docking station.
                                                                                                        */


/*****NTE error******/
/***The following shows NTE error values generated by the specific cryptographic service providers (CSP).***/
#define NTE_BAD_UID                                 0x80090001            /*  Bad UID.    */
#define NTE_BAD_HASH                                0x80090002            /*  Bad hash.   */
#define NTE_BAD_KEY                                 0x80090003            /*  Bad key.    */
#define NTE_BAD_LEN                                 0x80090004            /*  Bad length. */
#define NTE_BAD_DATA                                0x80090005            /*  Bad data.   */
#define NTE_BAD_SIGNATURE                           0x80090006            /*  Invalid signature.  */
#define NTE_BAD_VER                                 0x80090007            /*  Bad version of provider.    */
#define NTE_BAD_ALGID                               0x80090008            /*  Invalid algorithm specified.    */
#define NTE_BAD_FLAGS                               0x80090009            /*  Invalid flags specified.    */
#define NTE_BAD_TYPE                                0x8009000A            /*  Invalid type specified. */
#define NTE_BAD_KEY_STATE                           0x8009000B            /*  Key not valid for use in specified state.   */
#define NTE_BAD_HASH_STATE                          0x8009000C            /*  Hash not valid for use in specified state.  */
#define NTE_NO_KEY                                  0x8009000D            /*  Key does not exist. */
#define NTE_NO_MEMORY                               0x8009000E            /*  Insufficient memory available for the operation.    */
#define NTE_EXISTS                                  0x8009000F            /*  Object already exists.  */
#define NTE_PERM                                    0x80090010            /*  Access denied.  */
#define NTE_NOT_FOUND                               0x80090011            /*  Object was not found.   */
#define NTE_DOUBLE_ENCRYPT                          0x80090012            /*  Data already encrypted. */
#define NTE_BAD_PROVIDER                            0x80090013            /*  Invalid provider specified. */
#define NTE_BAD_PROV_TYPE                           0x80090014            /*  Invalid provider type specified.    */
#define NTE_BAD_PUBLIC_KEY                          0x80090015            /*  Invalid provider public key.    */
#define NTE_BAD_KEYSET                              0x80090016            /*  Keyset does not exist   */
#define NTE_PROV_TYPE_NOT_DEF                       0x80090017            /*  Provider type not defined.  */
#define NTE_PROV_TYPE_ENTRY_BAD                     0x80090018            /*  Invalid registration for provider type. */
#define NTE_KEYSET_NOT_DEF                          0x80090019            /*  The keyset not defined. */
#define NTE_KEYSET_ENTRY_BAD                        0x8009001A            /*  Invalid keyset registration.    */
#define NTE_PROV_TYPE_NO_MATCH                      0x8009001B            /*  Provider type does not match registered value.  */
#define NTE_SIGNATURE_FILE_BAD                      0x8009001C            /*  Corrupt digital signature file. */
#define NTE_PROVIDER_DLL_FAIL                       0x8009001D            /*  Provider DLL failed to initialize correctly.    */
#define NTE_PROV_DLL_NOT_FOUND                      0x8009001E            /*  Provider DLL not found. */
#define NTE_BAD_KEYSET_PARAM                        0x8009001F            /*  Invalid keyset parameter.   */
#define NTE_FAIL                                    0x80090020            /*  Internal error occurred.    */
#define NTE_SYS_ERR                                 0x80090021            /*  Base error occurred.    */


/*****CRYPT Error********/
/***The following defintion shows error codes that a cryptographic function might generate.***/
#define CRYPT_E_MSG_ERROR                           0x80091001            /*  An error was encountered doing a cryptographic message operation.   */
#define CRYPT_E_UNKNOWN_ALGO                        0x80091002            /*  The cryptographic algorithm is unknown. */
#define CRYPT_E_OID_FORMAT                          0x80091003            /*  The object identifier is badly formatted.   */
#define CRYPT_E_INVALID_MSG_TYPE                    0x80091004            /*  The message type is invalid.    */
#define CRYPT_E_UNEXPECTED_ENCODING                 0x80091005            /*  Unexpected message encoding.    */
#define CRYPT_E_AUTH_ATTR_MISSING                   0x80091006            /*  Missing an expected authenticated attribute.    */
#define CRYPT_E_HASH_VALUE                          0x80091007            /*  Incorrect hash value.   */
#define CRYPT_E_INVALID_INDEX                       0x80091008            /*  Invalid index value.    */
#define CRYPT_E_ALREADY_DECRYPTED                   0x80091009            /*  Message content already decrypted.  */
#define CRYPT_E_NOT_DECRYPTED                       0x8009100A            /*  Message content not yet decrypted.  */
#define CRYPT_E_RECIPIENT_NOT_FOUND                 0x8009100B            /*  Enveloped-data message missing the specified recipient. */
#define CRYPT_E_CONTROL_TYPE                        0x8009100C            /*  Invalid control type.   */
#define CRYPT_E_ISSUER_SERIALNUMBER                 0x8009100D            /*  Invalid issuer or serial number.    */
#define CRYPT_E_SIGNER_NOT_FOUND                    0x8009100E            /*  Original signer not found.  */
#define CRYPT_E_ATTRIBUTES_MISSING                  0x8009100F            /*  Message missing requested attributes.   */
#define CRYPT_E_STREAM_MSG_NOT_READY                0x80091010            /*  Streamed message is note yet able to return the requested data. */
#define CRYPT_E_STREAM_INSUFFICIENT_DATA            0x80091011            /*  Streamed message needs more data.   */
#define CRYPT_E_BAD_LEN                             0x80092001            /*  Insufficient output data length specified.  */
#define CRYPT_E_BAD_ENCODE                          0x80092002            /*  Error while encoding or decoding.   */
#define CRYPT_E_FILE_ERROR                          0x80092003            /*  Error while reading or writing to the file  */
#define CRYPT_E_NOT_FOUND                           0x80092004            /*  Object or property not found.   */
#define CRYPT_E_EXISTS                              0x80092005            /*  Object or property already exists.  */
#define CRYPT_E_NO_PROVIDER                         0x80092006            /*  No provider specified for store or object.  */
#define CRYPT_E_SELF_SIGNED                         0x80092007            /*  Specified certificate is self-signed.   */
#define CRYPT_E_DELETED_PREV                        0x80092008            /*  Previous certificate or CRL context deleted.    */
#define CRYPT_E_NO_MATCH                            0x80092009            /*  No match when trying to find the object.    */
#define CRYPT_E_UNEXPECTED_MSG_TYPE                 0x8009200A            /*  The type of the cryptographic message being decoded is different than what was expected.    */
#define CRYPT_E_NO_KEY_PROPERTY                     0x8009200B            /*  The certificate doesn't have a private key property */
#define CRYPT_E_NO_DECRYPT_CERT                     0x8009200C            /*  No certificate was found having a private key property to use for decrypting.   */
#define CRYPT_E_BAD_MSG                             0x8009200D            /*  Not a cryptographic message, or incorrectly formatted.  */
#define CRYPT_E_NO_SIGNER                           0x8009200E            /*  The signed message doesn't have a signer for the specified signer index */
#define CRYPT_E_PENDING_CLOSE                       0x8009200F            /*  Final closure is pending until additional frees or closes.  */
#define CRYPT_E_REVOKED                             0x80092010            /*  The certificate or signature has been revoked   */
#define CRYPT_E_NO_REVOCATION_DLL                   0x80092011            /*  No Dll or exported function found to verify revocation. */
#define CRYPT_E_NO_REVOCATION_CHECK                 0x80092012            /*  Called function unable to perform revocation check. */
#define CRYPT_E_REVOCATION_OFFLINE                  0x80092013            /*  Because the revocation server was offline, the called function wasn't able to complete the revocation check.    */
#define CRYPT_E_NOT_IN_REVOCATION_DATABASE          0x80092014            /*  The certificate or signature not found in the revocation server database.   */
#define CRYPT_E_INVALID_NUMERIC_STRING              0x80092020            /*  The string contains a non-numeric character.    */
#define CRYPT_E_INVALID_PRINTABLE_STRING            0x80092021            /*  The string contains a non-printable character.  */
#define CRYPT_E_INVALID_IA5_STRING                  0x80092022L           /*  The string contains a character not in the 7 bit ASCII character set.   */
#define CRYPT_E_INVALID_X500_STRING                 0x80092023            /*  The string contains an invalid X500 name attribute key, OID, value or delimiter.    */
#define CRYPT_E_NOT_CHAR_STRING                     0x80092024            /*  The dwvaluetype for CERT_NAME_VALUE not one of the character strings.   */
#define CRYPT_E_FILERESIZED                         0x80092025            /*  Put operation cannot continue. The file needs to be resized.    */
#define CRYPT_E_SECURITY_SETTINGS                   0x80092026            /*  The cryptography operation failed due to a local security option setting.   */
#define CRYPT_E_NO_VERIFY_USAGE_DLL                 0x80092027            /*  No DLL or exported function found to verify subject usage.  */
#define CRYPT_E_NO_VERIFY_USAGE_CHECK               0x80092028            /*  The called function was not able to do a usage check on the subject.    */
#define CRYPT_E_VERIFY_USAGE_OFFLINE                0x80092029            /*  Because the server was offline, the called function was not able to complete the usage check.   */
#define CRYPT_E_NOT_IN_CTL                          0x8009202A            /*  The subject not found in a Certificate Trust List.  */
#define CRYPT_E_NO_TRUSTED_SIGNER                   0x8009202B            /*  No trusted signer found.    */
#define CRYPT_E_OSS_ERROR                           0x80093000            /*  OSS Certificate encode/decode error code base. See asn1code.h.  */



/******CERTSRV Error Codes ********/
#define CERTSRV_E_BAD_REQUESTSUBJECT                0x80094001            /*  The request subject name is invalid or too long.    */
#define CERTSRV_E_NO_REQUEST                        0x80094002            /*  The request does not exist. */
#define CERTSRV_E_BAD_REQUESTSTATUS                 0x80094003            /*  The requests current status does not allow this operation.  */
#define CERTSRV_E_PROPERTY_EMPTY                    0x80094004            /*  The requested property value is empty.  */
#define CERTDB_E_JET_ERROR                          0x80095000            /*  Jet error code. See jet.h.  */


/******TRUST Error Codes ********/
#define TRUST_E_SYSTEM_ERROR                        0x80096001            /*  A system-level error occured while verifying trust. */
#define TRUST_E_NO_SIGNER_CERT                      0x80096002            /*  The certificate for the signer of the message is invalid or not found.  */
#define TRUST_E_COUNTER_SIGNER                      0x80096003            /*  Invalid counter signer. */
#define TRUST_E_CERT_SIGNATURE                      0x80096004            /*  The signature of the certificate cannot be verified.    */
#define TRUST_E_TIME_STAMP                          0x80096005            /*  The time stamp signer and or certificate could not be verified or is malformed. */
#define TRUST_E_BAD_DIGEST                          0x80096010            /*  The objects digest did not verify.  */
#define TRUST_E_BASIC_CONSTRAINTS                   0x80096019            /*  Certificate basic constraints invalid or missing.   */
#define TRUST_E_FINANCIAL_CRITERIA                  0x8009601E            /*  The certificate does not meet or contain the Authenticode financial extensions. */

/******NV Error Codes ********/
#define ERROR_NV_NONE                                                 0x800a0000
#define ERROR_NV_SYSTEM                                             0x800a0001 /* System error, e.g. hardware failure */
#define ERROR_NV_INVALID_PARAM                               0x800a0002
#define ERROR_NV_NO_ENOUGH_RESOURCE                   0x800a0003
#define ERROR_NV_NOT_EXIST                                        0x800a0004
#define ERROR_NV_ACCESS_DENY                                   0x800a0005
#define ERROR_NV_INCOMPATIBLE                                  0x800a0006
#define ERROR_NV_NOT_OPENED                                     0x800a0007
/******TIMER Error Codes ********/
#define ERROR_TIMER_NO_EXIST                                                 0x800b0000

/******RTC DATE Error Codes ********/
#define ERROR_TM_NONE                                                           0x800c0000
#define ERROR_TM_PNULL                                                           0x800c0001
#define ERROR_TM_WRONG_DATE                                                0x800c0002
#define ERROR_TM_WRONG_TIME                                               0x800c0003
#define ERROR_TM_ALARM_WRONG_TIME                                0x800c0004
#define ERROR_TM_ALARM_TIME_IS_EXPIRED                          0x800c0005

/******AUDIO Error Codes ********/

#define ERROR_AUDIO_NO_ERROR                                   0x800d0000  /*!<Operation success.*/
#define ERROR_AUDIO_LINKLIST_NULL                           0x800d0001    /*!<The link list is null.*/
#define ERROR_AUDIO_UNOPENED_HANDLE                    0x800d0002     /*!<This handle has not been opened.*/
#define ERROR_AUDIO_PLAYING                                      0x800d0003        /*!<This audio is being played.*/
#define ERROR_AUDIO_PAUSING                                      0x800d0004      /*!<This audio has been paused.*/
#define ERROR_AUDIO_NOT_PAUSING                             0x800d0005          /*!<This audio has not been paused.*/
#define ERROR_AUDIO_HANDLE_IS_INVALID                  0x800d0006                 /*!<The handle is invalid.*/
#define ERROR_AUDIO_HANDLE_NOT_EXIST                   0x800d0007                 /*!<This handle is not exist.*/
#define ERROR_AUDIO_FILE_ERROR                                0x800d0008       /*!<The file operation is error.*/
#define ERROR_AUDIO_FORMAT_ERROR                          0x800d0009     /*!<Audio format can't be supported.*/
#define ERROR_AUDIO_MULTI_STOP                                0x800d000a        /*!<The destination audio has been stopped.*/
#define ERROR_AUDIO_ERROR_MODULE_HANDLE           0x800d000b                     /*!<This handle's module type is unconformity.*/
#define ERROR_AUDIO_ERROR_HANDLE_TYPE                 0x800d000c                 /*!<This handle's handle type is unconformity.*/
#define ERROR_AUDIO_ERROR_SUB_HANDLE_TYPE        0x800d000d                           /*!<This handle's sub-handle typeis unconformity.*/
#define ERROR_AUDIO_NO_ENOUGH_MEMORY                 0x800d000e                  /*!<System can't provide enough memory space.*/
#define ERROR_AUDIO_CONFLICT                                    0x800d000f        /*!<Audio play conflict.*/
#define ERROR_AUDIO_NO_OPERATION                           0x800d0010        /*!<Don't exist this operation.*/
#define ERROR_AUDIO_NO_CODECHANDLE                      0x800d0011           /*!<Codec handle is not exist.*/
#define ERROR_AUDIO_VB_TRACK_FULL                         0x800d0012         /*!<Voiceband track number is full.*/
#define ERROR_AUDIO_PARAM_ERROR                            0x800d0013           /*!<Parameter error.*/
#define ERROR_AUDIO_CM_OPERATION_FAILURE           0x800d0014                    /*!<Collision management operation failure.*/
#define ERROR_AUDIO_CM_CAN_PLAY                             0x800d0015              /*!<Collision arbitration pass. */
#define ERROR_AUDIO_CM_CANNOT_PLAY                      0x800d0016            /*!<Collision arbitration reject.*/
#define ERROR_AUDIO_CM_PARA_ERROR                        0x800d0017          /*!<Collision management operation parameter error.*/
#define ERROR_AUDIO_PM_NO_EXT_OPE_SYMBOL         0x800d0018                     /*!<This extend operation symbol is not exist.*/
#define ERROR_AUDIO_NO_EXPHANDLE                           0x800d0019       /*!<This handle is not exist.*/
#define ERROR_AUDIO_INVALID_GAIN                            0x800d001a        /*!<The digital gain from codec is invalid.*/
#define ERROR_AUDIO_INVALID_SAMPLERATE               0x800d001b                /*!<The samplerate from codec is invalid.*/
#define ERROR_AUDIO_SEEK_ERROR                               0x800d001c                                     /*!<The seek operation in codec is wrong.*/

/******SMS Error Codes ********/
#define ERROR_SMS_NONE                                         0x800d0000
#define ERROR_SMS_SIM_NOT_READY                       0x800d0001
#define ERROR_SMS_IS_SENDING                              0x800d0002
#define ERROR_SMS_NUM_ERR                                   0x800d0003
#define ERROR_SMS_MSG_LEN_ERR                           0x800d0004
#define ERROR_SMS_MSG_ERR                                   0x800d0005
#define ERROR_ENCODE_USER_DATA_ERR                0x800d0006
#define ERROR_SMS_SEND_ERR                                 0x800d0007
#define ERROR_SMS_SC_NUM_ERR                           0x800d0008
#define ERROR_SMS_MSG                                          0x800d0009

/******EVENT Error Codes ********/
#define ERROR_EVENT_NONE                                         0x800e0000
#define ERROR_EVENT_FULL                                         0x800e0001    // event数量已最大
#define ERROR_EVENT_NOT_FOUND                              0x800e0002

/******GPRS Error Codes ********/
#define ERROR_GPRS_NO_ERR                                      0x800f0000				//函数调用成功
#define ERROR_GPRS_CALL_FAILURE                           0x800f0001//函数调用失败
#define ERROR_GPRS_INP_NULL                                      0x800f0002//输入的参数为空
#define ERROR_GPRS_OUT_MEMORY                               0x800f0003//内存分配失败
#define ERROR_GPRS_NO_VALID_PARAM                        0x800f0004 //输入参数指示无有效参数
#define ERROR_GPRS_INVALID_PDP_ID                          0x800f0005 //输入pdp上下文标识无效
#define ERROR_GPRS_INVALID_PDP_TYPE                      0x800f0006//输入pdp type参数无效
#define ERROR_GPRS_INVALID_APN                      0x800f0007//输入APN参数无效
#define ERROR_GPRS_INVALID_PDP_ADDR                      0x800f0008//输入PDP ADDR参数无效
#define ERROR_GPRS_NOT_SUPPORT_COMP                      0x800f0009//输入COMP参数不支持
#define ERROR_GPRS_INVALID_PCO                      0x800f000a//输入PCO参数无效
#define ERROR_GPRS_INVALID_RELIABILITY                      0x800f000b//输入RELIABILITY参数无效
#define ERROR_GPRS_INVALID_PEAK                      0x800f000c//输入PEAK参数无效
#define ERROR_GPRS_INVALID_DELAY                      0x800f000d
#define ERROR_GPRS_INVALID_PRECEDENCE                      0x800f000e
#define ERROR_GPRS_INVALID_MEAN                      0x800f000f
#define ERROR_GPRS_INVALID_PARA_LEN                      0x800f0010
#define ERROR_GPRS_INVALID_PDP_STATE                      0x800f0011

/******TTS Error Codes ********/
#define ERROR_TTS_BASE_ERROR        0x80100000              
#define ERROR_TTS_INVALID_HANDLE    ERROR_TTS_BASE_ERROR+1    // tts handle create fail or no create
#define ERROR_TTS_NO_INIT           ERROR_TTS_BASE_ERROR+2    // tts module no init
#define ERROR_TTS_PLAYING           ERROR_TTS_BASE_ERROR+3    // audio playing
#define ERROR_TTS_OVER_TEXT_LEN     ERROR_TTS_BASE_ERROR+4    // over max text len
#define ERROR_TTS_MALLOC            ERROR_TTS_BASE_ERROR+5    // malloc heap fail

/******FILE Error Codes ********/

#define ERROR_FILE_BASE_ERROR          0x80110000     
#define ERROR_FILE_DEVICE              ERROR_FILE_BASE_ERROR+ 0x1        //device error
#define ERROR_FILE_SYSTEM              ERROR_FILE_BASE_ERROR+ 0x2        //os error memory overwrite, memory error.or other unlogic error.
#define ERROR_FILE_INVALID_PARAM       ERROR_FILE_BASE_ERROR+ 0x3        //param you give is invalid
#define ERROR_FILE_NO_ENOUGH_RESOURCE  ERROR_FILE_BASE_ERROR+ 0x4    //no use
#define ERROR_FILE_IO_PENDING          ERROR_FILE_BASE_ERROR+ 0x5        //when you call api in asynchronism ,api will return #define ERROR_FILE_IO_PENDING immediately.Real error message and return value will be given in callback funtion.
#define ERROR_FILE_ACCESS              ERROR_FILE_BASE_ERROR+ 0x6        //can not access the file ,maybe it is being used by other handler. or read data that not exist
#define ERROR_FILE_NOT_EXIST           ERROR_FILE_BASE_ERROR+ 0x7        // file or device not exist
#define ERROR_FILE_HAS_EXIST           ERROR_FILE_BASE_ERROR+ 0x8        // file or device has exist
#define ERROR_FILE_HARDWARE_FAILED     ERROR_FILE_BASE_ERROR+ 0x9        // no use
#define ERROR_FILE_WRITE_CONFLICT      ERROR_FILE_BASE_ERROR+ 0xa   // no use
#define ERROR_FILE_NO_SPACE            ERROR_FILE_BASE_ERROR+ 0xb
#define ERROR_FILE_NOT_EMPTY           ERROR_FILE_BASE_ERROR+ 0x14   //  folder not empty.
#define ERROR_FILE_LONG_DEPTH          ERROR_FILE_BASE_ERROR+ 0x15   //  copy tree or move tree , has exceed too many folder.
#define ERROR_FILE_FOLD_FULL           ERROR_FILE_BASE_ERROR+ 0x16   // fold entry is not enough to  add new file or fold in it
#define ERROR_FILE_ABORT               ERROR_FILE_BASE_ERROR+ 0x17   //  copy or move process is cancelled.
#define ERROR_FILE_NORES_HANDLE        ERROR_FILE_BASE_ERROR+ 0x18   // no handle resource for open new file
#define ERROR_FILE_BUSY                ERROR_FILE_BASE_ERROR+ 0x19   // current sfs task is busy(formating or mountring)
#define ERROR_FILE_INVALID_FORMAT      ERROR_FILE_BASE_ERROR+ 0x1a
#define ERROR_FILE_TOOMANYFILE         ERROR_FILE_BASE_ERROR+ 0x1b
#define ERROR_FILE_REG                 ERROR_FILE_BASE_ERROR+ 0x32   // reg bsd fail
#define ERROR_FILE_INIT                ERROR_FILE_BASE_ERROR+ 0x33   // init filesystem fail
#define ERROR_FILE_UNREG               ERROR_FILE_BASE_ERROR+ 0x34   // unreg bsd fail
#define ERROR_FILE_UNINIT              ERROR_FILE_BASE_ERROR+ 0x35   // uninit filesystem fail
#define ERROR_FILE_INIT_PARAM_NO_SAME_EXIST   ERROR_FILE_BASE_ERROR+ 0x36   //  Init parameters are not the same as before
#define ERROR_FILE_INIT_MEMORY_OVERSIZE       ERROR_FILE_BASE_ERROR+ 0x37   // start addr+size over max memory size
#define ERROR_FILE_INIT_MEMORY_CONFLICT       ERROR_FILE_BASE_ERROR+ 0x38   // FAT32 and Littlefs memory conflit
#define ERROR_FILE_INIT_SPI            ERROR_FILE_BASE_ERROR+ 0x39   //init spi flash failure
#define ERROR_FILE_INIT_SPI_NO_EXIST   ERROR_FILE_BASE_ERROR+ 0x40   //no exist spi flash
#define ERROR_FILE_NOT_OPENED          ERROR_FILE_BASE_ERROR+ 0x41   //lfs file not opened
#define ERROR_FILE_LFS_NOENT            ERROR_FILE_BASE_ERROR + 0x66   // No directory entry
#define ERROR_FILE_LFS_IO               ERROR_FILE_BASE_ERROR + 0x69   // Error during device operation
#define ERROR_FILE_LFS_BADF             ERROR_FILE_BASE_ERROR + 0x6d     // Bad file number
#define ERROR_FILE_LFS_NOMEM            ERROR_FILE_BASE_ERROR + 0x70    //No more memory available
#define ERROR_FILE_LFS_EXIST            ERROR_FILE_BASE_ERROR + 0x75   //Entry already exists
#define ERROR_FILE_LFS_NOTDIR           ERROR_FILE_BASE_ERROR + 0x78     //Entry is not a dir
#define ERROR_FILE_LFS_ISDIR            ERROR_FILE_BASE_ERROR + 0x79     //Entry is a dir
#define ERROR_FILE_LFS_INVAL            ERROR_FILE_BASE_ERROR + 0x7a     //Invalid parameter
#define ERROR_FILE_LFS_FBIG             ERROR_FILE_BASE_ERROR + 0x7f    //File too large
#define ERROR_FILE_LFS_NOSPC            ERROR_FILE_BASE_ERROR + 0x80     //No space left on device
#define ERROR_FILE_LFS_NAMETOOLONG      ERROR_FILE_BASE_ERROR + 0x88     //File name too long
#define ERROR_FILE_LFS_NOTEMPTY         ERROR_FILE_BASE_ERROR + 0x8b     //Dir is not empty
#define ERROR_FILE_LFS_NOATTR           ERROR_FILE_BASE_ERROR + 0xa1     //No data/attr available
#define ERROR_FILE_LFS_CORRUPT          ERROR_FILE_BASE_ERROR+ 0xb8   //Corrupted
#define ERROR_FILE_DRM_ACCESS_DENIED   ERROR_FILE_BASE_ERROR+ 0x3e8 // @681, operation not allowed
#define ERROR_FILE_DRM_NORMAL_FILE     ERROR_FILE_BASE_ERROR+ 0x3e9 // file is normal    
#define ERROR_FILE_DRM_NO_RIGHTS       ERROR_FILE_BASE_ERROR+ 0x3ea // no rights
#define ERROR_FILE_DRM_RIGHTS_EXPIRED  ERROR_FILE_BASE_ERROR+ 0x3eb // rights expired
#define ERROR_FILE_DRM_INVALID_RIGHTS  ERROR_FILE_BASE_ERROR+ 0x3ec // rights file is invalid    
#define ERROR_FILE_DRM_INVALID_FORMAT  ERROR_FILE_BASE_ERROR+ 0x3ed // DRM file format is invalid
#define ERROR_FILE_INVALID_HANDLE      ERROR_FILE_BASE_ERROR+ 0x3ee

/******FOTA Error Codes ********/
#define ERROR_FOTA_NO_INIT                                      0x80120000

/******COM Error Codes ********/
#define ERROR_COM_NO_INIT                                      0x80130000

/******COM Error Codes ********/
#define ERROR_LOGO_UPDATA_BASE_ERROR          					0x80140000
#define ERROR_LOGO_UPDATA_NONSUPPORT							0x80140001
#define ERROR_LOGO_UPDATA_BOOTIMAGEINFO							0x80140002
#define ERROR_LOGO_UPDATA_MAGICNUM								0x80140003
#define ERROR_LOGO_UPDATA_IMAGELEN								0x80140004
#define ERROR_LOGO_UPDATA_CALLBACK								0x80140005
#define ERROR_LOGO_UPDATA_LEN									0x80140006
#define ERROR_LOGO_UPDATA_MALLOC								0x80140007
#define ERROR_LOGO_UPDATA_COPPY									0x80140008


#endif
