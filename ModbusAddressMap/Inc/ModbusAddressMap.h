/**
******************************************************************************
* @file      ModbusAddressMap.h
* @author    telegram: @bariskin
* @version   
* @brief     This file contains defines for  Modbus address map
******************************************************************************
*/	
#ifndef  _MODBUS_ADDRESS_MAP_H
#define  _MODBUS_ADDRESS_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------ Includes -----------------------------------*/
#include "stm32f4xx_hal.h"
/* ------------------------ Defines ------------------------------------*/
  
#define MB_START_ADDR_REG                           (uint16_t)(0x9D0A)                        /*40202  */        
 
#define MB_START_CMD                                (uint16_t)MB_START_ADDR_REG               /*40202  */
 
#define MB_STOP_FLAG                                (uint16_t)(MB_START_CMD    + 0x01)        /*40203  */ // 40202

#define MB_TIME_VALUE                               (uint16_t)(MB_STOP_FLAG    + 0x01)        /*40204  */

#define MB_COUNTER1                                 (uint16_t)(MB_TIME_VALUE   + 0x02)        /*40206  */

#define MB_COUNTER2                                 (uint16_t)(MB_COUNTER1     + 0x02)        /*40208  */

/* ------------------------ External variables -------------------------*/

/* ------------------------ Function prototypes ---------------------------*/


#ifdef __cplusplus
}
#endif

#endif
