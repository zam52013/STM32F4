/**
  ******************************************************************************
  * @file    flash.c 
  * @author  zam
  * @version V1.0
  * @date    20-3-2018
  * @brief   Header for flash.c module
  ******************************************************************************/
#include "flash.h"

/*******************************************************************************
函 数 名：void Boot_Flash_ErasePage(void)
功能描述： 擦除flash
入口参数：	地址
返回参数：状态
创建时间: 2018-01-24 by zam
********************************************************************************/
 FLASH_Status Boot_Flash_ErasePage(uint32_t FLASH_Sector)
 {
		FLASH_Status FLASHStatus = FLASH_COMPLETE;
		FLASH_Unlock();
	  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		FLASHStatus = FLASH_EraseSector(FLASH_Sector,VoltageRange_3);
		FLASH_Lock();
	 return FLASHStatus;
 }
 /*******************************************************************************
函 数 名：void Boot_Flash_Write(void)
功能描述： 写flash
入口参数：	Addr 地址  date 数据  num个数
返回参数：无
创建时间: 2018-01-24 by zam
********************************************************************************/

 void Boot_Flash_Write(uint32_t Addr,uint32_t *date,uint16_t num)
 {
	 uint16_t cnt=0;
	 FLASH_Status FLASHStatus = FLASH_COMPLETE;
	 FLASH_Unlock();
	 for(cnt=0;(cnt<num)&&(FLASHStatus == FLASH_COMPLETE);num++)
	 {
			FLASHStatus=FLASH_ProgramWord(Addr+(cnt*2),*(date++));
	 }
	 FLASH_Lock();
 }
  /*******************************************************************************
函 数 名：void Boot_Flash_Read(void)
功能描述： 读flash
入口参数：	Addr 地址  date 数据  num个数
返回参数：无
创建时间: 2018-01-24 by zam
********************************************************************************/
 void Boot_Flash_Read(uint32_t Addr,uint32_t *date,uint16_t num)
 {
	 uint16_t cnt=0;
	 FLASH_Status FLASHStatus = FLASH_COMPLETE;
	 FLASH_Unlock();
	 for(cnt=0;(cnt<num)&&(FLASHStatus == FLASH_COMPLETE);num++)
	 {
			*(date+cnt)=(*(__IO uint32_t*) Addr);
	 }
	 FLASH_Lock();
 }