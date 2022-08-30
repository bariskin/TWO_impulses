/**
******************************************************************************
* @file      TemplateFile.c
* @author    MTL  Application Team
* @version   
* @brief     This file provides common functions for the  
*            finite - state machine triggering.   
*/       
/* ------------------------Includes ----------------------------------*/
#include "BSP.h"
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h" 
#include "task.h"
/* ------------------------External variables -------------------------*/
extern  uint16_t timeout_Timer7 ;
extern volatile uint16_t counter_Timer7;
extern void prvvTIMERExpiredISR( void );
/* ------------------------Global variables----------------------------*/
uint32_t counter_1 = 0;
uint32_t counter_2 = 0;
/* ------------------------Locale variables----------------------------*/

/* ------------------------Functions-----------------------------------*/

/**
* @brief  HAL_TIM_PeriodElapsedCallback 
* @param  structure of timer
* @retval None
*/
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  /*  timer6 for ModBus RTU */	
//  if(htim->Instance == TIM7) 
//  {
//    
//    if((++counter_Timer7)>=timeout_Timer7)
//    {
//      counter_Timer7= 0;
//      prvvTIMERExpiredISR( );
//    }
//  } 

//}
/************************ (C) COPYRIGHT MTL *****END OF FILE****/



