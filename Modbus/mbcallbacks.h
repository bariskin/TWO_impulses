/**
  ******************************************************************************
  * @file      mbcallbacks.h
  * @author    MTL  Application Team
  * @version   
  * @brief     This file contains defines and all the functions prototypes for the mbcallbacks.c      
  ******************************************************************************
*/
#ifndef _MBCALLBACKS_H
#define _MBCALLBACKS_H


#ifdef __cplusplus
extern "C" {
#endif
  
 /* ------------------------Includes ----------------------------------*/  
#include  "mb.h" 
 
#include  "ModbusDataHandler.h"
/* ------------------------Defines ----------------------------------*/ 
   
#define   HOLDING_REG_START_ADDR           (0x9C40)                                       /*! ADDR = 40000*/ 
  

 /** REG_HOLDING_START: start address for holding registers */
//#define REG_HOLDING_START      (MB_START_ADDR_REG - HOLDING_REG_START_ADDR )             /*!  40202 - 40000 */
#define REG_HOLDING_START      (MB_START_ADDR_REG + 1)             /*!  40202 - 40000 */

/** REG_HOLDING_NREGS: number of holding registers */
#define REG_HOLDING_NREGS 8 

   /** OUTPUT array for holding registers */
extern short   OutRegHoldingBuf[REG_HOLDING_NREGS];
 
 /** INPUT array for holding registers */
extern short   InputHoldingBuf[REG_HOLDING_NREGS];
   
extern uint8_t modbus_mutex;

void ModbusBufferInit(void);
  
#ifdef __cplusplus
}
#endif

#endif
