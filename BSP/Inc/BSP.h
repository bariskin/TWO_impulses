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

extern uint16_t volatile start_flag; 

  /** @addtogroup template_file
  * @{
  */

  /**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif  /* _TEMPLATE_FILE_H */