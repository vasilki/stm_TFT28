/**
  ******************************************************************************
  * @file    LIB_Config.h
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief     This file provides configurations for low layer hardware libraries.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USE_LIB_CONFIG_H_
#define _USE_LIB_CONFIG_H_
//Macro Definition

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "SPI.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

#define LCD_BKL_GPIO   LCD_BKL_GPIO_Port
#define LCD_DC_GPIO    LCD_DC_GPIO_Port
#define LCD_CS_GPIO    LCD_CS_GPIO_Port
#define LCD_CLK_GPIO   GPIOA
#define LCD_SDI_GPIO   GPIOA
#define LCD_SDO_GPIO   GPIOA
#define LCD_RST_GPIO   LCD_RST_GPIO_Port

#define LCD_BKL_PIN    LCD_BKL_Pin
#define LCD_DC_PIN     LCD_DC_Pin
#define LCD_CS_PIN     LCD_CS_Pin
#define LCD_CLK_PIN    GPIO_Pin_5
#define LCD_SDO_PIN    GPIO_Pin_6
#define LCD_SDI_PIN    GPIO_Pin_7
#define LCD_RST_PIN    LCD_RST_Pin


#define __LCD_RST_SET()     HAL_GPIO_WritePin(LCD_RST_GPIO, LCD_RST_PIN, GPIO_PIN_SET)
#define __LCD_RST_CLR()     HAL_GPIO_WritePin(LCD_RST_GPIO, LCD_RST_PIN, GPIO_PIN_RESET)

#define __LCD_BKL_SET()    HAL_GPIO_WritePin(LCD_BKL_GPIO, LCD_BKL_PIN, GPIO_PIN_SET)
#define __LCD_BKL_CLR()    HAL_GPIO_WritePin(LCD_BKL_GPIO, LCD_BKL_PIN, GPIO_PIN_RESET)

#define __LCD_CS_SET()     HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS_PIN, GPIO_PIN_SET)
#define __LCD_CS_CLR()     HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS_PIN, GPIO_PIN_RESET)

#define __LCD_DC_SET()     HAL_GPIO_WritePin(LCD_DC_GPIO, LCD_DC_PIN, GPIO_PIN_SET)
#define __LCD_DC_CLR()     HAL_GPIO_WritePin(LCD_DC_GPIO, LCD_DC_PIN, GPIO_PIN_RESET)

#define __LCD_WRITE_BYTE(__DATA)       spi_read_write_byte(GL_pLCDSPI, __DATA)

/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */


#endif /*_USE_LIB_CONFIG_H_*/

/*-------------------------------END OF FILE-------------------------------*/

