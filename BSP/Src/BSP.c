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
/* ------------------------External variables -------------------------*/
extern  uint16_t timeout_Timer7 ;
extern volatile uint16_t counter_Timer7;
extern void prvvTIMERExpiredISR( void );
/* ------------------------Global variables----------------------------*/
volatile uint32_t  counter_1 = 0;
volatile uint32_t  counter_2 = 0;

uint32_t volatile update_value_1 = 0;
uint32_t volatile update_value_2 = 0;


volatile uint16_t  start_first_flag  = OFF_FLAG; 
volatile uint16_t  start_second_flag = OFF_FLAG; 
volatile uint16_t  stop_first_flag   = OFF_FLAG ; 
volatile uint16_t  stop_second_flag  = OFF_FLAG;

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
		  if (HAL_GPIO_ReadPin(INPUT_1_GPIO_Port,INPUT_1_Pin) == GPIO_PIN_SET)       // rising input_1
      {  
		    set_TEST_LED1();
		
		    if(start_first_flag)
		     {	
           start_second_flag = ON_FLAG;			 
		       counter_1++;
		     }
	    }
			else                                                                       //falling input_1
			{ 
				  if(stop_first_flag)   
					  {
						   stop_second_flag = ON_FLAG;
						}
			     reset_TEST_LED1();	
			}
			
   }
		 
	else if(GPIO_Pin == INPUT_2_Pin)                                               // rising input_2
   {
		 if (HAL_GPIO_ReadPin(INPUT_2_GPIO_Port,INPUT_2_Pin) == GPIO_PIN_SET)   
      {  
		
		    set_TEST_LED2();
		
		    if(start_second_flag)   
		     {			
		       counter_2++;
		     }
	    }
			else                                                                        //falling input_2
			{ 
				if(stop_second_flag)      
				{
					start_first_flag  = OFF_FLAG;                                          //  STOP counter_1
				  start_second_flag = OFF_FLAG;                                          //  STOP counter_2
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



