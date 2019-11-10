/**
  ******************************************************************************
  * @file    LIB_Config.c 
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief     This files provide
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
#include <stdio.h>
#include <stdlib.h>
//#include "stm32f4xx_hal.h"

//Platform Configuration


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//uint16_t g_hwDevId = 0;

/* Private function prototypes -----------------------------------------------*/
void system_init(SPI_HandleTypeDef *par_hspi);
static void device_init(void);
static void driver_init(SPI_HandleTypeDef *par_hspi);
static void port_init(void);
static void spi1_init(void);

/**
  * @brief  System initialization.
  * @param  None
  * @retval  None
  */
void system_init(SPI_HandleTypeDef *par_hspi)
{
    device_init();
    driver_init(par_hspi);
}

static void device_init(void)	
{
	port_init();
	spi1_init();
}


static void driver_init(SPI_HandleTypeDef *par_hspi)
{
  lcd_init(par_hspi);
}

static void port_init(void) 
{
/*
 *
 	GPIO_InitTypeDef tGPIO;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);  
	*/
	/*----------------------------------------------------------------------------------*/
	/*
	 * //SPI
	tGPIO.GPIO_Pin = LCD_CLK_PIN | LCD_SDI_PIN | LCD_SDO_PIN;	 //SCK	MOSI  MISO		 
	tGPIO.GPIO_Mode = GPIO_Mode_AF;
  	tGPIO.GPIO_OType = GPIO_OType_PP;
  	tGPIO.GPIO_PuPd = GPIO_PuPd_UP;
  	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &tGPIO);
    */
    /* Connect SCK, MISO and MOSI pins to SPI alternate */
	/*
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1); 
    */
	/*----------------------------------------------------------------------------------*/
	/*
	 * //LCD
	tGPIO.GPIO_Pin = LCD_CS_PIN;   			 
	tGPIO.GPIO_Mode = GPIO_Mode_OUT;
	tGPIO.GPIO_OType = GPIO_OType_PP;
	tGPIO.GPIO_PuPd = GPIO_PuPd_UP;
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(LCD_CS_GPIO, &tGPIO);
    
    tGPIO.GPIO_Pin = LCD_DC_PIN;   			 
	tGPIO.GPIO_Mode = GPIO_Mode_OUT;
	tGPIO.GPIO_OType = GPIO_OType_PP;
	tGPIO.GPIO_PuPd = GPIO_PuPd_UP;
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(LCD_DC_GPIO, &tGPIO);

	tGPIO.GPIO_Pin = LCD_BKL_PIN;  			 
	tGPIO.GPIO_Mode = GPIO_Mode_OUT;
	tGPIO.GPIO_OType = GPIO_OType_PP;
	tGPIO.GPIO_PuPd = GPIO_PuPd_UP;
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(LCD_BKL_GPIO, &tGPIO);

	*/
	/*----------------------------------------------------------------------------------*/
}

/**
  * @brief  SPI initialization.
  * @param  None
  * @retval None
  */
static void spi1_init(void)
{
	/*

  SPI_InitTypeDef tSPI;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	tSPI.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	tSPI.SPI_Mode = SPI_Mode_Master;		
	tSPI.SPI_DataSize = SPI_DataSize_8b;		
	tSPI.SPI_CPOL = SPI_CPOL_High;		
	tSPI.SPI_CPHA = SPI_CPHA_2Edge;	
	tSPI.SPI_NSS = SPI_NSS_Soft;

	*/

	/* SPI baudrate is set to 9 MHz maximum (PCLK2/SPI_BaudRatePrescaler = 72/8 = 9 MHz) 
       to verify these constraints:
          - ST7735R LCD SPI interface max baudrate is 15MHz for write and 6.66MHz for read
            Since the provided driver doesn't use read capability from LCD, only constraint 
            on write baudrate is considered.
          - SD card SPI interface max baudrate is 25MHz for write/read
          - PCLK2 max frequency is 72 MHz 
       */

	/*
	tSPI.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		
	tSPI.SPI_FirstBit = SPI_FirstBit_MSB;	
	tSPI.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI1, &tSPI);  
 
	SPI_Cmd(SPI1, ENABLE); 

	*/
}


/*-------------------------------END OF FILE-------------------------------*/

