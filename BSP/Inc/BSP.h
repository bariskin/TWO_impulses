/**
******************************************************************************
* @file      TemplateFile.h
* @author    MTL Application Team
* @version   
* @brief     This file contains defines and all the functions prototypes for the TemplateFile.c
******************************************************************************
*/
#ifndef _TEMPLATE_FILE_H
#define _TEMPLATE_FILE_H

#ifdef __cplusplus
extern "C" {
#endif
  
 /* ------------------------Includes ----------------------------------*/
 #include "stm32f4xx_hal.h"
  /** @defgroup template_file
  * @{
  */
  
  /**
  * @}
  */
 /* ------------------------Defines ----------------------------------*/
#define ON_FLAG     1
#define OFF_FLAG   0
 /* ------------------------External variables -------------------------*/
extern uint32_t volatile counter_1;
extern uint32_t volatile counter_2;


extern volatile uint16_t  start_first_flag; 
extern volatile uint16_t  start_second_flag; 
extern volatile uint16_t  stop_first_flag ; 
extern volatile uint16_t  stop_second_flag;


extern uint32_t update_time_value ;
  /** @addtogroup template_file
  * @{
  */
	
	void enable_TX(void);

  void enable_RX(void);
	
  void init_TEST_LEDS(void);

  void set_TEST_LED1(void);
  void reset_TEST_LED1(void);
  void set_TEST_LED2(void);
  void reset_TEST_LED2(void);
	void reset_LED_STM(void);
  void set_LED_STM(void);
 
	
	

  /**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif  /* _TEMPLATE_FILE_H */
