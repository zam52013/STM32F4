/**
  ******************************************************************************
  * @file    flash.h 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for flash.h module
  ******************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H


#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "stm32f4xx.h"
		FLASH_Status Boot_Flash_ErasePage(uint32_t FLASH_Sector);
		 void Boot_Flash_Write(uint32_t Addr,uint32_t *date,uint16_t num);
		 void Boot_Flash_Read(uint32_t Addr,uint32_t *date,uint16_t num);
		
	#ifdef __cplusplus
		}
	#endif
#endif


