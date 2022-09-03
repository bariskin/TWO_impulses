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
//#include "cmsis_os.h"
#include "BSP.h"
/* ------------------------External variables -------------------------*/
extern uint32_t volatile counter_1;
extern uint32_t volatile counter_2;
extern uint32_t volatile update_value_1;
extern uint32_t volatile update_value_2;

extern uint32_t work_time;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

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
			
		 	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
			case MB_START_CMD:
				
			  OutputValue =  (uint16_t)first_start_flag;
				break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   		
			case MB_STOP_FLAG:
				
			   OutputValue =  (uint16_t)first_stop_flag;
				break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE:
			
        OutputValue = (uint16_t)work_time;
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE + 1:
			
       OutputValue =  (uint16_t)((uint32_t)(work_time >> 16));
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1:
			
		   OutputValue = (uint16_t)update_value_1;			
		break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1 + 1: 
			
       OutputValue = (uint16_t)((uint32_t)(update_value_1 >> 16));
 		break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2:
			
	   	   OutputValue = (uint16_t)update_value_2;
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2 + 2: 
			
	       OutputValue = (uint16_t)((uint32_t)(update_value_2 >> 16));
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
			 
			 case MB_START_CMD:
         
			   if(RegValue == ON_FLAG)
				  { 
						second_start_flag = OFF_FLAG;
						second_stop_flag = OFF_FLAG;
						second_start_flag = OFF_FLAG; 
						
				    first_start_flag = ON_FLAG;
						HAL_TIM_Base_Start_IT(&htim6); 
						set_LED_STM();
				  }
				 
				 break;
			/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
			 case  MB_STOP_FLAG:
				 	 
				 break;
			 
			/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/     
      case MB_TIME_VALUE:
				
		 	    work_time = (uint16_t)RegValue; //16
			break;
		  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		 case MB_TIME_VALUE  + 1:
			 
			    work_time |=  (uint32_t)(RegValue << 16); //16
		 
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER1: 
			
		   	break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER1 + 1: 
			 
		; 
		 
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER2:
			 
			 
		  
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2  + 1: 
			
			
    break; 
     }
 }
	 

 
 	 