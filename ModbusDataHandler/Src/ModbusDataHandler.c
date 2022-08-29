/**
  ******************************************************************************
  * @file      ModbusDataHandler.c
  * @author    @bariskin
  * @version   
  * @brief     This file provides  common functions for modbus data handler
               get data from modbus stack 
  ******************************************************************************
*/

/* ------------------------Includes ----------------------------------*/

#include "ModbusDataHandler.h"
#include "cmsis_os.h"
/* ------------------------External variables -------------------------*/


/* ------------------------Global variables----------------------------*/


/* ------------------------Local variables----------------------------*/
   

 
/* ModBus mutex flag */
uint8_t mod_bus_mutex_flag = 0; 

/**
  * @brief  Set modbus mutex flag
  * @param  None
  * @retval None
 */      
void  MODBUS_EnterLock(void)
 {
   mod_bus_mutex_flag = 1;
 }
 
/**
  * @brief  Reset modbus mutex flag 
  * @param  None
  * @retval None
 */
void MODBUS_LeaveLock(void)
 {
  mod_bus_mutex_flag = 0;
 }


	/**
		* @brief  Write parameters to modbus stack
		* @param  modbus registers index
		* @retval OutputValue: value for ModBus register
	 */
	uint16_t WriteParamToModbusStack(uint16_t MBregIdx)
	{
		uint16_t OutputValue = 0x0000;
		
		uint16_t MBRegAddr = MB_START_ADDR_REG + MBregIdx;
		
		switch(MBRegAddr)
		{   
		 
		case MB_TIME_VALUE:
			
		  //OutputValue = FIRST_ROW_CAL;
			
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE + 1:
			
			//OutputValue = VIBRO_STATE;
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1: 
			
			//OutputValue = BAT_VOLTAGE ;
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1 + 1: 
			
		//	OutputValue = STATUS_1;
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2:
			
		//	OutputValue = STATUS_2;
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2 + 2: 
			
			//OutputValue = ENCODER_STATE_H;
			break;
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/ 
	
	
		}
		return OutputValue;
	}

/**
  * @brief  Read parameters from modbus stack
  * @param  modbus registers index
  * @param  registers value 
  * @retval None
 */
	
void ReadParamFromModbusStack(uint16_t MBregIdx, uint16_t RegValue)
   {
     uint16_t MBRegAddr = MB_START_ADDR_REG  + MBregIdx;
    
     
     switch(MBRegAddr)
     {   
      case MB_TIME_VALUE:
				
			
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE  + 1:
			
			 
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1: 
			
		
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1 + 1: 
			
	   
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2:
			
		  
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2  + 1: 
			
		
    break; 
     }
 }
	 

 
 	 