/**
  **************************************************************************
  * @file     spi.h
  * @brief    at32f425硬件SPI .h 文件
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "at32f425.h"

/** @defgroup SPI配置函数
  * @{
  */
	
void spi_config(void);
void spi1_writ_byte(uint8_t dat);
	
/**
  * @}
 */
#endif /* __SPI_H */
