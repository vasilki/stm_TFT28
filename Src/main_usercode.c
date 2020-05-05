#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "LCD.h"
#include "timers.h"
#include "uart.h"
#include "dwt_stm32_delay.h"

extern UART_HandleTypeDef huart1; /*declared in main.c*/
//extern ADC_HandleTypeDef hadc1; /*declared in main.c*/
extern TIM_HandleTypeDef htim9;
extern SPI_HandleTypeDef hspi1;


static void main_Init(void);
static void main_heartbeat(void);
static void main_draw(void);
static void main_buttons(void);


void main_usercode(void)
{

  uint8_t loc_buff[20];
  unsigned int loc_time;
  unsigned int loc_time_ms = 0;
  unsigned int loc_time_sec = 0;
  static unsigned int loc_prev_time_ms=0;
  static unsigned int loc_prev_time_sec=0;
  uint8_t loc_srbyte = 1;

  main_Init();

  tim_UpdatePeriod();
  loc_time = tim_GetPeriod();
  loc_time_sec = tim_GetTimeFromStartSEC();
  
  
  /*HeartBeat*/
  main_heartbeat();
  main_draw();
  /*Running LED*/
  if(loc_time_sec != loc_prev_time_sec)
  {

  }
  else
  {
    /*nothing to do*/
  }

  //loc_adc_val = adc_GetValue(&hadc1);


  loc_prev_time_sec = loc_time_sec;
  loc_prev_time_ms = loc_time_ms;
  
  return;
}
extern void lcd_init(SPI_HandleTypeDef *par_hspi);
void main_Init(void)
{
  static uint8_t loc_B_IsFirstTime = 0;

  if(loc_B_IsFirstTime == 0)
  {
    /*TIM init*/
    tim_InitTimer(&htim9);

    /*DWT init*/
    DWT_Delay_Init();
    
    /*UART init*/
    uart_Init(&huart1);
    uart_PrintfBuildVersion();

    /*TFT2.8 init*/
    lcd_init(&hspi1);


    loc_B_IsFirstTime = 1;
  }
  else
  {
    /*nothing to do*/
  }


  return;
}


void main_heartbeat(void)
{
  uint32_t loc_time_sec;
  static uint32_t loc_prev_time_sec = 0;

  loc_time_sec = tim_GetTimeFromStartSEC();
  
  if(loc_prev_time_sec != loc_time_sec)
  {
    UART_PRINTFINTEGER(loc_time_sec,"DEC")


      
    /*
     * LED2 is occupied by SCI
    if((loc_time_sec % 2) == 0)
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    }
    */
    loc_prev_time_sec = loc_time_sec;
  }
  else
  {
    /*nothing to do*/
  }
  
  
  return;
}


void main_draw(void)
{
/*
  lcd_draw_rect(1, 1, 50, 50, RED);

  lcd_draw_rect(30, 40, 150, 100, RED);
  lcd_draw_circle(120, 160, 50, BLUE);
  lcd_draw_line(30, 40, 180, 140, RED);

  lcd_draw_line(30, 220, 210, 240, RED);
  lcd_draw_line(30, 220, 120, 280, RED);
  lcd_draw_line(120, 280, 210, 240, RED);
*/

  return;
}

void main_buttons()
{

  
  return;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
