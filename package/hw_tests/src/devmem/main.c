/******************************************************************************
* Copyright (c)2017 Rhomb - All rights reserved.
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
* File Name   :  main.c
*
* Description :  This file contains functions to read/write physical register
*
* History     :  May/10/2017, Android Linux Media, Created the file.
*
*******************************************************************************/
#include <common.h>
#include <ctype.h>
#include <termios.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
#define MEMORY_DEVICE	"/dev/mem"

INT32 main(INT32 argc, CHAR **argv)
{
   INT32	iDeviceHandle;
   VOID 	*pMapBase;
   VOID 	*pVirtualAddress;
   UINT32	uReadResult;
   UINT32	uWriteValue;
   INT32	iAccessType = 'w';
   INT32        iReturnVal    = STATUS_SUCCESS;
   off_t	target;

   if(argc < 2)
   {
      fprintf(stderr, "\nUsage:\t%s { address } [ type [ data ] ]\n"
                      "\taddress : memory address to act upon\n"
                      "\ttype    : access operation type : [b]yte, [h]alfword, [w]ord\n"
                      "\tdata    : data to be written\n\n",
                      argv[0]);
		exit(1);
   }
   target = strtoul(argv[1], 0, 0);
   if(argc > 2)
      iAccessType = tolower(argv[2][0]);

   iDeviceHandle = open(MEMORY_DEVICE, O_RDWR | O_SYNC);
   if(DEVICE_OPEN_ERROR == iDeviceHandle)
   {
      ERROR("Failed to open %s device.", MEMORY_DEVICE);
      iReturnVal = DEVICE_OPEN_ERROR;
   }
   else
   {
      /* Map one page */
      pMapBase = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, iDeviceHandle, target & ~MAP_MASK);
      if(pMapBase == (VOID *) -1)
      {
         ERROR("Failed to mmap device.");
         iReturnVal = ERR_MMAP;
      }
      else
      {
         pVirtualAddress = pMapBase + (target & MAP_MASK);
         switch(iAccessType)
         {
            case 'b':
               uReadResult = *((UCHAR *) pVirtualAddress);
               break;
            case 'h':
               uReadResult = *((USHORT *) pVirtualAddress);
               break;
            case 'w':
               uReadResult = *((UINT32 *) pVirtualAddress);
               break;
            default:
               fprintf(stderr, "Illegal data type '%c'.\n", iAccessType);
               exit(2);
         }
         printf("Value at address 0x%X (%p): 0x%X\n", target, pVirtualAddress, uReadResult);
         if(argc > 3)
         {
            uWriteValue = strtoul(argv[3], 0, 0);
            switch(iAccessType)
            {
               case 'b':
                  *((UCHAR *) pVirtualAddress) = uWriteValue;
                  uReadResult = *((UCHAR *) pVirtualAddress);
                  break;
               case 'h':
                  *((USHORT *) pVirtualAddress) = uWriteValue;
                  uReadResult = *((USHORT *) pVirtualAddress);
                  break;
               case 'w':
                  *((UINT32 *) pVirtualAddress) = uWriteValue;
                  uReadResult = *((UINT32 *) pVirtualAddress);
				  break;
            }
            printf("Written 0x%X; readback 0x%X\n", uWriteValue, uReadResult);
         }
      }
      iReturnVal = munmap(pMapBase, MAP_SIZE);
      if(STATUS_FAILURE == iReturnVal)
      {
         ERROR("Failed to Unmap device");
         iReturnVal = ERR_MUNMAP;
      }
      close(iDeviceHandle);
   }
   return iReturnVal;
}

