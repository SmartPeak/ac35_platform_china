/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author: 
#########################################################################*/

#ifndef _MERCURY_I2C_H_
#define _MERCURY_I2C_H_

#include "MercuryDef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum NI2C_DEV_E_TAG
{
    I2C_DEV_0,   // i2c 2
    I2C_DEV_CAM, // i2c 0
    I2C_DEV_NUM,
    MERCURY_ENUM_I2CDEV_MAX = 0x7fffffff
}I2C_DEV_E;

typedef struct
{
    /*logic id, which presentes as a specific i2c bus and the i2c slave device connects to this bus. */
    uint32 id;
    /*i2c slave device's working freqency */
    uint32 freq;
    /*i2c slave device's write address, whose length is 8 bits, not 7bits.*/
    uint8 slave_addr;
    /*i2c slave device's internal register length */
    uint8 reg_addr_num;

} I2C_DEV;


#define I2C_CTL_G_FREQ   0x20 /*get frequency*/
#define I2C_CTL_S_FREQ   0x21 /*set frequency*/
#define I2C_CTL_G_PORT   0x22 /*get port*/
#define I2C_CTL_S_PORT   0x23 /*set port*/
#define I2C_CTL_STOP_BUS 0x24 /*stop i2c bus*/


/*********************************************************************************************************
** Function name: I2C_Init
** Descriptions: This function will initialize the i2c controller, 
**                    and return a handler for the i2c slave device.
** input parameters:
**     dev - pointer of i2c slave dev
**
** Returned value: 
**     Success:  return a handle, whose value is more than or equal to 0.
**     Fail:  return -1
*********************************************************************************************************/
INT I2C_Init (I2C_DEV *dev);

/*********************************************************************************************************
** Function name:I2C_Deinit
** Descriptions:This function will close the i2c controller.
** input parameters:
**     handle:the i2c slave device has gotten by calling I2C_Init

** Returned value:
**     Success:  return 0.
**     Fail:  return -1
*********************************************************************************************************/
INT I2C_Deinit (uint32 handle);

/*********************************************************************************************************
** Function name:I2C_Read
** Descriptions:This function is used to start a read transfer.
** input parameters:
**     Handle:  an i2c slave device has gotten by calling I2C_Init.
**     reg_addr:  the buffer to store i2c slave device's internal register address.
**     bytes:  the number of reading data.
**     buffer:These buffers will store the data, read from i2c slave device

** Returned value:
**     Success:  return the number of reading data.
**     Fail:  return 0.
*********************************************************************************************************/
INT I2C_Read (uint32 handle, uint8 *reg_addr, uint8 *buffer, uint32 bytes);

/*********************************************************************************************************
** Function name:I2C_Write
** Descriptions:This function is used to start a write transfer.
** input parameters:
**     Handle:  an i2c slave device has gotten by calling I2C_Init.
**     reg_addr:  the buffer to store i2c slave device's internal register address.
**     buffer:  These buffers will store the data, write to i2c slave device
**     bytes:  the number of writing data.

** Returned value:
**     Success:  return the number of writing data.
**     Fail:  return 0.
*********************************************************************************************************/
INT I2C_Write (uint32 handle, uint8 *reg_addr, uint8 *buffer, uint32 bytes);

/*********************************************************************************************************
** Function name:I2C_Ioctl
** Descriptions:This function will set i2c controller or get some status.
** input parameters:
**    Handle:  a i2c slave device has gotten by calling I2C_Init.
**    command:  Command type is defined in i2c_drvapi.h
**    arg:  command parameter

** Returned value:Don't care the return value, currently this function will always succeed.
*********************************************************************************************************/

INT I2C_Ioctl (uint32 handle, uint32 cmd, uint32 *arg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MERCURY_I2C_H_
