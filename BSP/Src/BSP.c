/**
******************************************************************************
* @file      BSP.c
* @author    MTL  Application Team
* @version   
* @brief     
*/       
/* ------------------------Includes ----------------------------------*/
#include "BSP.h"
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h" 
#include "task.h"
#include "main.h"
/* ------------------------External variables -------------------------*/
extern  uint16_t timeout_Timer7 ;
extern volatile uint16_t counter_Timer7;
extern void prvvTIMERExpiredISR( void );
/* ------------------------Global variables----------------------------*/
uint32_t volatile counter_1 = 0;
uint32_t volatile counter_2 = 0;

uint32_t volatile update_value_1 = 0;
uint32_t volatile update_value_2 = 0;

uint16_t  first_start_flag  = OFF_FLAG; 
uint16_t  second_start_flag = OFF_FLAG; 
uint16_t  first_stop_flag   = OFF_FLAG; 
uint16_t  second_stop_flag  = OFF_FLAG;

uint32_t work_time = 0;
uint32_t update_time_value = 0;
/* ------------------------Locale variables----------------------------*/

/* ------------------------Functions-----------------------------------*/


void enable_TX(void)
  {
	  HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin , GPIO_PIN_SET);
	}
void enable_RX(void)
  {
	  HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin , GPIO_PIN_RESET);
	}	
	

	void set_TEST_LED1(void)
  {
	  HAL_GPIO_WritePin(PULSE_1_GPIO_Port, PULSE_1_Pin, GPIO_PIN_SET); 	
	}

void reset_TEST_LED1(void)
  {
	  HAL_GPIO_WritePin(PULSE_1_GPIO_Port, PULSE_1_Pin, GPIO_PIN_RESET); 	
	}

void set_TEST_LED2(void)
  {
	  HAL_GPIO_WritePin(PULSE_2_GPIO_Port, PULSE_2_Pin, GPIO_PIN_SET); 	
	}
	

void reset_TEST_LED2(void)
  {
	  HAL_GPIO_WritePin(PULSE_2_GPIO_Port, PULSE_2_Pin, GPIO_PIN_RESET); 	
	}
	
	
void reset_LED_STM(void)
  {
	  HAL_GPIO_WritePin(LED_STM_GPIO_Port, LED_STM_Pin, GPIO_PIN_RESET); 	
	}
	
 void set_LED_STM(void)
  {
	  HAL_GPIO_WritePin(LED_STM_GPIO_Port, LED_STM_Pin, GPIO_PIN_SET); 	
	}
	
	
	
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
  {
		
   if(GPIO_Pin == INPUT_1_Pin)
   {
		  if (HAL_GPIO_ReadPin(INPUT_1_GPIO_Port,INPUT_1_Pin) == GPIO_PIN_SET)   
      {  
		    set_TEST_LED1();
		
		    if(first_start_flag)
		     {	
           second_start_flag = ON_FLAG;			 
		       counter_1++;
		     }
	    }
			else 
			{ 
				  if(first_stop_flag)   // 3.
					  {
						   second_stop_flag = ON_FLAG;
						}
			     reset_TEST_LED1();	
			}
			
   }
		 
	else if(GPIO_Pin == INPUT_2_Pin)
   {
		 if (HAL_GPIO_ReadPin(INPUT_2_GPIO_Port,INPUT_2_Pin) == GPIO_PIN_SET)   
      {  
		
		    set_TEST_LED1();
		
		    if(second_start_flag)   // 5.
		     {			
		       counter_2++;
		     }
	    }
			else 
			{ 
				if(second_stop_flag)   // 4.
				{
				  second_start_flag = OFF_FLAG;
				}
			   reset_TEST_LED2();	
			} 	  
	 }

	}	
/**
* @brief  HAL_TIM_PeriodElapsedCallback 
* @param  structure of timer
* @retval None
*/

/************************ (C) COPYRIGHT MTL *****END OF FILE****/



