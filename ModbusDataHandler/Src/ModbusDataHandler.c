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
   

 uint8_t LOCK_LODBUS_CMD = 0;
 
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
			case MB_START_CMD_REG:
				
			  OutputValue =  (uint16_t)start_first_flag;
				break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   		
			case MB_STOP_CMD_REG:
				
			   OutputValue =  (uint16_t)start_second_flag;
				break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE_REG:
			
        OutputValue = (uint16_t)work_time;
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		case MB_TIME_VALUE_REG + 1:
			
       OutputValue =  (uint16_t)((uint32_t)(work_time >> 16));
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1_REG:
			
		   OutputValue = (uint16_t)update_value_1;			
		break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER1_REG + 1: 
			
       OutputValue = (uint16_t)((uint32_t)(update_value_1 >> 16));
 		break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2_REG:
			
	   	   OutputValue = (uint16_t)update_value_2;
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2_REG + 1: 
			
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
			 
			 case MB_START_CMD_REG:
         
			   if(RegValue == 1)
				  { 
						
					 if (LOCK_LODBUS_CMD == 0)	 
						{
							LOCK_LODBUS_CMD = 1;
							
						   stop_first_flag   = OFF_FLAG;
						   stop_second_flag  = OFF_FLAG; 
						   start_second_flag = OFF_FLAG;
						
				       start_first_flag = ON_FLAG;
							
							 counter_1 = 0;
						   counter_2 = 0;
							
						   HAL_TIM_Base_Start_IT(&htim6); 
						   set_LED_STM();
							
							LOCK_LODBUS_CMD = 1;
						}
				  }
				 
				 break;
			/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
			 case  MB_STOP_CMD_REG:
				 
			 
			  if(RegValue == 2)
				  {	  
						
				   if (LOCK_LODBUS_CMD == 0)	 
						{
							LOCK_LODBUS_CMD = 1;
						
					    start_first_flag = OFF_FLAG;     
					
					    stop_first_flag = ON_FLAG;       
					
					    HAL_TIM_Base_Stop_IT(&htim6); 
					
					    update_value_1 = counter_1;
					    update_value_2 = counter_2;
						
					    counter_1 = 0;
					    counter_2 = 0;
					    reset_LED_STM();
							
			 	
						  LOCK_LODBUS_CMD = 1;
						}
					}
				 break;
			 
			/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/     
      case MB_TIME_VALUE_REG:
				
		 	    work_time = (uint16_t)RegValue; //16
			    work_time *= 1000;
			break;
		  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/   
		 case MB_TIME_VALUE_REG  + 1:
			 
			    work_time |=  (uint32_t)(RegValue << 16); //16
		 
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER1_REG: 
			 
			 update_value_1   =  (uint32_t)0; 
		 
			
		   	break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER1_REG + 1: 
			 
		 
			break;
		/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		 case MB_COUNTER2_REG:
			 
			update_value_2   =  (uint32_t)0; 
		  
			break; 
		 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
		case MB_COUNTER2_REG  + 1: 
			
			
    break; 
     }
 }
	 