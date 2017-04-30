/*******************************************************************************
* copyright (c)2017 Rhomb - All rights reserved.
*
* This software is authored by Rhomb and is Rhomb'
* intelletual property,including the copyrights in all countries in the world.
* This software is provided under a license to use only with all other rights,
* including ownership rights, being retained by Rhomb.
*
* This file may not be distributed, copied or reproduced in any manner,
* electronic or otherwise, without the written consent of Rhomb.
*******************************************************************************/

/*******************************************************************************
*
* File Name   :  common.h
*
* Description :  This file contains typedef's, defines and error codes which
*                are common for all modules.
*
* History     :  April/24/2017, Android Linux Media, Created the file.
*
*******************************************************************************/
#ifndef _common_H
#define _common_H

/*******************************************************************************
*                      Include Files
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/mman.h>

/*******************************************************************************
*                      Typedef
*******************************************************************************/
typedef signed char         INT8;           /* 8 bit value                    */
typedef signed short int    INT16;          /* 16 bit value                   */
typedef int                 INT32;          /* 32 bit value                   */
typedef long                INT64;          /* 64 bit value                   */
typedef unsigned char       UINT8;          /* 8 bit value                    */
typedef unsigned char       UCHAR;          /* 8 bit value                    */
typedef unsigned short int  UINT16;         /* 16 bit value                   */
typedef unsigned short      USHORT;         /* 16 bit value                   */
typedef unsigned int        UINT32;         /* 32 bit value                   */
typedef unsigned long       UINT64;         /* 64 bit value                   */
typedef unsigned long long  ULINT64;        /* 64 bit value                   */
typedef unsigned int        UINT;           /* 32 bit value                   */
typedef float               FLOAT32;        /* 32 bit value                   */
typedef double              FLOAT64;        /* 64 bit value                   */
typedef short int           BOOL;           /* 16 bit value                   */
typedef char                CHAR;           /* 8 bit value                    */
typedef short               CHAR16;         /* 16 bit value                   */
typedef unsigned short      UCHAR16;        /* 16 bit value                   */
typedef struct timeval      TimeContainer;  /* Time structer                  */
typedef void                VOID;           /* Void                           */
typedef struct termios      Terminal;       /* Terminal I/O interface         */
typedef time_t               Time;           /* Represent simple time value    */
typedef struct tm           LocalTime;      /* Represent calender date & time */
typedef pthread_t           Thread;         /* Thread ID                      */
typedef sem_t               SemaPhore;      /* Sema Phore type                */
typedef struct rtc_time     RTCTime;        /* RTC Time structure             */

/*******************************************************************************
*                      Defines
*******************************************************************************/
#define MAX_STRING_LENGTH   (255)
#define IOCTL_ERROR         (-1)
#define DEVICE_OPEN_ERROR   (-1)
#define DEVICE_CLOSE_ERROR   (-1)
#define DEVICE_RW_ERROR     (-1)

#if !defined (FALSE)
#define FALSE   0
#endif

#if !defined (TRUE)
#define TRUE    1
#endif

#define CLEAR(x) memset(x,0,sizeof(x))

#ifdef _DEBUG
#define DEBUG(X...)     {printf("DEBUG->%s:%s:%d: \n", __FILE__,__func__, __LINE__); \
				             printf(X);                        \
				             printf("\n");}
#else
#define DEBUG(X...)
#endif

#define ERROR(X...)     {printf("ERROR->%s:%d: \n", __FILE__, __LINE__);       \
				             printf(X);                        \
				             printf("\n");}

#define WARNING(X...)   {printf("WARNING->%s:%d: \n", __FILE__, __LINE__);     \
				             printf(X);                        \
				             printf("\n");}

/*******************************************************************************
*                      Error Codes / Enum
*******************************************************************************/
typedef enum _CommonErrorCodes
{
   STATUS_SUCCESS = 0,            /* General success                          */
   STATUS_FAILURE = -1,           /* General failure                          */
   ERR_INVALID_ARGUMENTS = -256,  /* Called with invalid arguments            */
   ERR_CONFIGURATION,             /* Called with invalid configuration params */
   ERR_MEMORY_ALLOCATION,         /* Failed to allocate memory                */
   ERR_MMAP,                      /* Can not map kernel buffer to user space  */
   ERR_MUNMAP,                    /* Cannot unmap kernel buffer               */
   ERR_SOCKET_CREATE,             /* Socket creation fail                     */
   ERR_SOCKET_BIND,               /* Socket bind fail                         */
   ERR_SOCKET_LISTEN,             /* Socket listen fail                       */
   ERR_SOCKET_ACCEPT,             /* Socket accept fail                       */
   ERR_SOCKET_RECV,               /* Socket recv data failed                  */
   ERR_SOCKET_SEND,               /* Socket send data failed                  */
   ERR_SOCKET_CONNECT,            /* Socket connection failed                 */
   ERR_SOCKET_CLOSE,              /* Socket close failed                      */
}CommonErrorCodes;

#endif  /* _common_H  */

/*******************************************************************************
* copyright (c)2017 Rhomb - All rights reserved.
*
* This software is authored by Rhomb and is Rhomb'
* intelletual property,including the copyrights in all countries in the world.
* This software is provided under a license to use only with all other rights,
* including ownership rights, being retained by Rhomb.
*
* This file may not be distributed, copied or reproduced in any manner,
* electronic or otherwise, without the written consent of Rhomb.
*******************************************************************************/
