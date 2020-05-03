/**
  ******************************************************************************
  * @file    SPI.c 
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief   This file provides a set of functions to manage the communication between SPI peripherals.
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



/* Includes ------------------------------------------------------------------*/
#include "LIB_Config.h"
#include "SPI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Read or write an byte from or to SPI bus.
  * @param  tSPIx: where x can be 1 , 2 or 3 to select the SPI peripheral.
  * @retval chByte: Receive an byte from SPI bus
  */

uint8_t spi_read_write_byte(SPI_HandleTypeDef *par_SPI, uint8_t chByte)
{		
  uint8_t loc_writebyte = chByte;
  uint8_t loc_readbyte = 0;

  if(par_SPI != NULL)
  {
    HAL_SPI_TransmitReceive(par_SPI,&loc_writebyte,&loc_readbyte,1,10);
  }
  else
  {
    /*nothing to do*/
  }


  return loc_readbyte;

  /*
  uint8_t chRetry = 0;

	uint8_t chTemp = 0;

	while (SPI_I2S_GetFlagStatus(tSPIx, SPI_I2S_FLAG_TXE) == RESET) {
		if (++ chRetry > 200) {
			return 0;
		}
	}

	SPI_I2S_SendData(tSPIx, chByte);

	chRetry=0;
	while (SPI_I2S_GetFlagStatus(tSPIx, SPI_I2S_FLAG_RXNE) == RESET) {
		if (++ chRetry > 200) {
			return 0;
		}
	}

	chTemp = SPI_I2S_ReceiveData(tSPIx);
	*/
	/* Wait until the BSY flag is set */
	/*
	
	while(SPI_I2S_GetFlagStatus(tSPIx, SPI_I2S_FLAG_BSY) != RESET) {
	
	}
	
	return chTemp;

	*/
}

/*-------------------------------END OF FILE-------------------------------*/

