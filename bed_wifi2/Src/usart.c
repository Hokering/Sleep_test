/**
  ******************************************************************************
  * File Name          : USART.c
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
unsigned char UART1_Rx_Buf[MAX_REC_LENGTH];
unsigned char UART1_Rx_flg ;
unsigned int  UART1_Rx_cnt ;
unsigned char UART1_temp[REC_LENGTH];
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart3,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
//重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

//重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{		
	int ch;
	HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}


uint32_t count = 0;
uint8_t u3_get_flag = 0;
//UART.c
/**
  * @brief 串口中断回调函数
  * @param 调用回调函数的串口
  * @note  串口每次收到数据以后都会关闭中断，如需重复使用，必须再次开启
  * @retval None
  */  
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART1)
  {
	   u3_get_flag = 1;
//	HAL_UART_Transmit_IT( &huart1 , (uint8_t *)UART3_temp, 1);
//	HAL_GPIO_WritePin(RELAY1_GPIO_Port,RELAY1_Pin,GPIO_PIN_RESET); 
	  UART1_Rx_Buf[count++] = UART1_temp[0];
//	  if(count>1023)count = 0;
//	  My_String_Printf1(UART3_temp);
  }
    HAL_UART_Receive_IT(&huart1,(uint8_t *)UART1_temp,REC_LENGTH);
}



void My_String_Printf1( uint8_t* String ) 
{  
	while( *String != '\0' )
	{   
		HAL_UART_Transmit( &huart1 , (uint8_t *)(String++), 1,0xff);  
	} 
}

unsigned char mod[]="AT+CWMODE=1\r\n";																		//设置wifi模式为STA模式
unsigned char rst[]="AT+RST\r\n";																					//复位
unsigned char wico[]="AT+CWJAP=\"EnmaAi\",\"123456789\"\r\n";				//连接wifi的wifi名称和密码
unsigned char sili[]="AT+CIPMUX=0\r\n";																		//设置单链接
unsigned char sev[]="AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n";				//连接onenet服务器
unsigned char mods[]="AT+CIPMODE=1\r\n";																	//打开透传模式
unsigned char sen[]="AT+CIPSEND\r\n";	
unsigned char send_buff[2048]="";	


void esp8266Init()
{
	My_String_Printf1(mod);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(rst);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(wico);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(sili);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(sev);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(mods);																					//连接wifi
	HAL_Delay(3000);
	My_String_Printf1(sen);																					//连接wifi
	HAL_Delay(3000);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
