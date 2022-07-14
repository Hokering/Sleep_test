/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* USER CODE BEGIN Includes */
#define REC_LENGTH  1
#define MAX_REC_LENGTH  4096 
  
extern unsigned char UART1_Rx_Buf[MAX_REC_LENGTH];
extern unsigned char UART1_Rx_flg ;
extern unsigned int  UART1_Rx_cnt ;
extern unsigned char UART1_temp[REC_LENGTH];
extern unsigned char send_buff[2048];	
extern uint8_t u3_get_flag ;
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void Usart_SendString(uint8_t *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void My_String_Printf1( uint8_t* String ) ;
void esp8266Init(void);
extern uint32_t count ;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
