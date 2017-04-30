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
* Description :  This file contains functions to test functionality of GPIO.
*
* History     :  April/28/2017, Android Linux Media, Created the file.
*
*******************************************************************************/

/*******************************************************************************
*                                Includes
*******************************************************************************/
#include <asm/user_gpio_app.h>
#include <common.h>

/*******************************************************************************
*                                Enum and structure
*******************************************************************************/
typedef enum _GPIO_Direction
{
   DIRECTION_OUT,
   DIRECTION_IN
}GPIO_Direction;

typedef struct _FuncTestGPIOConfig
{
   INT32           iGpioPin;
   INT32           iDeviceHandle;
   GPIO_Direction  eDirection;
   BOOL            bGpioValue;
   BOOL            iSetFlag;
   BOOL            iDirectionFlag;
}FuncTestGPIOConfig;

/*******************************************************************************
*                          Function Declaration
*******************************************************************************/

/* This function will open GPIO device for read write operation. */
static INT32 openGpioDevice();

/* This function will close GPIO device. */
static INT32 closeGpioDevice(INT32 *pDeviceHandle);

/*******************************************************************************
*                                 Defines
*******************************************************************************/
#define GPIO_DEVICE   ("/dev/usr_gpio")

/*******************************************************************************
*                         Function Definitions
*******************************************************************************/
/*******************************************************************************
* Function:     closeGpioDevice
*
* Description:  This function will close GPIO device.
*
* Parameters:   [OUT] INT32 *pDeviceHandle - Reference to GPIO device handle
*
* Return Value: Error or Success code
*******************************************************************************/
static INT32 closeGpioDevice(INT32 *pDeviceHandle)
{
   INT32 iReturnVal = STATUS_SUCCESS;

   /* Validate input arguments */
   if((NULL == pDeviceHandle) || (*(pDeviceHandle) < 0))
   {
      ERROR("Invalid GPIO device handle.");
      iReturnVal = ERR_INVALID_ARGUMENTS;
   }
   else
   {
      iReturnVal = close(*(pDeviceHandle));
      if(DEVICE_CLOSE_ERROR == iReturnVal)
      {
         ERROR("Failed to close GPIO device.");
         iReturnVal = STATUS_FAILURE;
      }
      else
      {
         iReturnVal = STATUS_SUCCESS;
         *(pDeviceHandle) = -1;
      }
   }

   /* Return device handle */
   return(iReturnVal);
}
/*******************************************************************************
* Function:     setGpioValue
*
* Description:  This function set GPIO value
*
* Parameters:   [OUT] INT32 *pGPIOTestCfg - Reference to GPIO configuration
*                                           structure
*
* Return Value: Error or Success code
*******************************************************************************/
static INT32 setGpioValue(FuncTestGPIOConfig *pGPIOTestCfg)
{
   INT32       iReturnVal    = STATUS_SUCCESS;
   gpio_arg_t  sGpioArg      = {0};

   if(NULL == pGPIOTestCfg)
   {
      ERROR("Invalid arguments.");
      iReturnVal = ERR_INVALID_ARGUMENTS;
   }
   else
   {
      sGpioArg.gpio = pGPIOTestCfg->iGpioPin;
      sGpioArg.value = pGPIOTestCfg->bGpioValue;
      iReturnVal = ioctl(pGPIOTestCfg->iDeviceHandle, GPIO_SET_VALUE, &sGpioArg);
   }
   return iReturnVal;
}
/*******************************************************************************
* Function:     getGpioValue
*
* Description:  This function get GPIO value
*
* Parameters:   [OUT] INT32 *pGPIOTestCfg - Reference to GPIO configuration
*                                           structure
*
* Return Value: Error or Success code
*******************************************************************************/
static INT32 getGPioValue(FuncTestGPIOConfig *pGPIOTestCfg)
{
   INT32       iReturnVal    = STATUS_SUCCESS;
   gpio_arg_t  sGpioArg      = {0};

   if(NULL == pGPIOTestCfg)
   {
      ERROR("Invalid arguments.");
      iReturnVal = ERR_INVALID_ARGUMENTS;
   }
   else
   {
      sGpioArg.gpio = pGPIOTestCfg->iGpioPin;
      iReturnVal = ioctl(pGPIOTestCfg->iDeviceHandle, GPIO_GET_VALUE, &sGpioArg);
      printf("GPIO : %d value : %d\n",sGpioArg.gpio,  sGpioArg.value);
   }
   return iReturnVal;
}
/*******************************************************************************
* Function:     setGPioDirection
*
* Description:  This function set GPIO direction input/ouput
*
* Parameters:   [OUT] INT32 *pGPIOTestCfg - Reference to GPIO configuration
*                                           structure
*
* Return Value: Error or Success code
*******************************************************************************/
int setGPioDirection(FuncTestGPIOConfig *pGPIOTestCfg)
{
   INT32       iReturnVal    = STATUS_SUCCESS;
   gpio_arg_t  sGpioArg      = {0};

   if(NULL == pGPIOTestCfg)
   {
      ERROR("Invalid arguments.");
      iReturnVal = ERR_INVALID_ARGUMENTS;
   }
   else
   {
      sGpioArg.gpio = pGPIOTestCfg->iGpioPin;
      sGpioArg.value = pGPIOTestCfg->bGpioValue;
      iReturnVal = ioctl(pGPIOTestCfg->iDeviceHandle, GPIO_SET_DIRECTION, &sGpioArg);
   }
   return iReturnVal;
}
/*******************************************************************************
* Function:     openGpioDevice
*
* Description:  This function will open GPIO device for read write operation.
*
* Parameters:   None.
*
* Return Value: Error or Success code
*******************************************************************************/
static INT32 openGpioDevice()
{
   INT32 iDeviceHandle = DEVICE_OPEN_ERROR;

   iDeviceHandle = open(GPIO_DEVICE, O_WRONLY | O_CREAT);
   if(DEVICE_OPEN_ERROR == iDeviceHandle)
   {
      DEBUG("Failed to open GPIO device.");
      iDeviceHandle = DEVICE_OPEN_ERROR;
   }

   /* Return device handle */
   return(iDeviceHandle);
}
/*******************************************************************************
* Function:     usage
*
* Description:  This function display usage in case of wrong arguments provided
*
* Parameters:   None
*
* Return Value: None
*******************************************************************************/
VOID usage()
{
   printf("For Getting current value of GPIO: \n");
   printf("./gpio_test -g -n <GPIO Number>\n");
   printf("example: ./gpio_test -g -n 1\n\n");
   printf("For Setting current value of GPIO: \n");
   printf("./gpio_test -s -n <GPIO Number> -v <High/low>\n");
   printf("example: ./gpio_test -s -n 1 -v 1\n\n");
   printf("For Setting direction of GPIO: \n");
   printf("./gpio_test -d -s -n <GPIO Number> -v <input/output>\n");
   printf("Here Value 0: Input, 1: Output \n");
   printf("example: ./gpio_test -s -n 1 -v 1\n\n");
}
/*******************************************************************************
* Function:     main
*
* Description:  This function will test functionality of GPIO. This will
*               test GPIO read/write operation. This function will be called
*               when XML configuration is available to execute GPIO test.
*
* Parameters:   [IN] FuncTestGPIOConfig *pGPIOTestCfg - Spi Test configurations
*
* Return Value: Error or Success code
*******************************************************************************/
INT32 main(INT32 argc, CHAR *argv[])
{
   INT32              iReturnVal    = STATUS_SUCCESS;
   INT32              iDeviceHandle = DEVICE_OPEN_ERROR;
   INT32              iOption       = 0;
   FuncTestGPIOConfig sGPIOTestCfg;

   memset(&sGPIOTestCfg, 0, sizeof(sGPIOTestCfg));

   if(argc < 2)
   {
	usage();
	exit(0);
   }
   while ((iOption = getopt(argc, argv,"n:v:sgdh")) != -1)
   {
      switch (iOption)
      {
         case 's' :
            sGPIOTestCfg.iSetFlag  = 1;
         break;
         case 'g' :
           sGPIOTestCfg.iSetFlag  = 0;
         break;
         case 'd' :
           sGPIOTestCfg.iDirectionFlag = 1;
         break;
         case 'n' :
           sGPIOTestCfg.iGpioPin = atoi(optarg);
         break;
         case 'v' :
           sGPIOTestCfg.bGpioValue = atoi(optarg);
         break;
         case 'h' :
           usage();
           exit(0);
         break;
         default:
           usage();
         break;
      }
   }
   sGPIOTestCfg.iDeviceHandle = openGpioDevice();
   if(sGPIOTestCfg.iDirectionFlag)
   {
      if(sGPIOTestCfg.iSetFlag)
      {
         iReturnVal = setGPioDirection(&sGPIOTestCfg);
      }
   }
   else
   {
      if(sGPIOTestCfg.iSetFlag)
      {
         iReturnVal = setGpioValue(&sGPIOTestCfg);
      }
      else
      {
         iReturnVal = getGPioValue(&sGPIOTestCfg);
      }
   }
   iReturnVal |= closeGpioDevice(&(sGPIOTestCfg.iDeviceHandle));

   /* Return error/success code */
   return(iReturnVal);
}

/*******************************************************************************
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
