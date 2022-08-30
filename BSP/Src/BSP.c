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

uint16_t volatile start_flag = OFF_FLAG; 
uint16_t volatile stop_flag = OFF_FLAG; 

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
	

/**
* @brief  HAL_TIM_PeriodElapsedCallback 
* @param  structure of timer
* @retval None
*/

/************************ (C) COPYRIGHT MTL *****END OF FILE****/



