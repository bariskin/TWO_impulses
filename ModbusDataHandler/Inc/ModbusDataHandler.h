/**
******************************************************************************
* @file      ModbusDataHandler.h
* @author    
* @version   
* @brief     This file contains defines and all the functions prototypes for the ModbusDataHandler.c     
******************************************************************************
*/
#ifndef _MODBUS_DATAHANDLER_H
#define _MODBUS_DATAHANDLER_H

#ifdef __cplusplus
extern "C" {
#endif
  
/* ------------------------Includes ----------------------------------*/  
#include "mbcallbacks.h"
#include "ModbusAddressMap.h"
//#include "ParameterMap.h"


  /** @defgroup ModbusDataHandler
  * @{
  */
  

  /**
  * @}
  */   
  
/* ------------------------Defines ----------------------------------*/   
 
#define RED_LED_MASK    0x001F

#define GREEN_LED_MASK  0x003F

#define BLUE_LED_MASK   0x001F
/* ------------------------External variables -------------------------*/  
  
  /* OUTPUT array for holding registers */
 //extern short   OutRegHoldingBuf[REG_HOLDING_NREGS];
  
  /* INPUT array for holding registers */
 //extern short   InputRegHoldingBuf[REG_HOLDING_NREGS];
    
  /* ModBus mutex flag*/    
 extern  uint8_t mod_bus_mutex_flag;  

 extern  uint8_t ModBusFlagEnable;  

 
 
/**
  * @addtogroup ModbusDataHandler
  * @{
  */
	
  void     ReadParamFromModbusStack(uint16_t MBregIdx, uint16_t RegValue);
  uint16_t WriteParamToModbusStack(uint16_t MBregIdx);
  void     MODBUS_EnterLock(void);
  void     MODBUS_LeaveLock(void);
   

/**
  * @}
  */   
  
#ifdef __cplusplus
}
#endif

#endif  

