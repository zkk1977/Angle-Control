/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "sys.h"
/* USER CODE BEGIN Includes */
#define Usart_Rx_MaxLen 1024	//最大接收数据长度
#define Usart_Tx_MaxLen 1024	//最大发送数据长度
/* USER CODE END Includes */



/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */



void Hal_USART1_UART_Init(u32 bound);
void Hal_USART2_UART_Init(u32 bound);
//void Usart3_Init(u32 bound);
void Hal_SendString(char* s,UART_HandleTypeDef huartx);
void Hal_SendData(u8 data,UART_HandleTypeDef huartx);
void Hal_Usart1_Printf (char *fmt, ...);
void Hal_Usart2_Printf (char *fmt, ...);
//void Usart3_Printf (char *fmt, ...);


typedef struct
{
  unsigned char Usart1_Count;
	unsigned char Usart2_Count;
//	unsigned char Usart3_Count;
	
  unsigned char *Usart1_Rx_Buff;
	unsigned char *Usart1_Tx_Buff;
	
	unsigned char *Usart2_Rx_Buff;
	unsigned char *Usart2_Tx_Buff;
	
//	unsigned char *Usart3_Rx_Buff;
//	unsigned char *Usart3_Tx_Buff;
  void (*Hal_Usart1_Init)(unsigned int bound);
	void (*Hal_Usart2_Init)(unsigned int bound);
//	void (*Usart3_Init)(unsigned int bound);
	
	void (*Hal_SendString)(char *s,UART_HandleTypeDef huartx);
	void (*Hal_SendData)(unsigned char data,UART_HandleTypeDef huartx);
	void (*Hal_Usart1_Printf)(char *fmt,...);
	void (*Hal_Usart2_Printf)(char *fmt,...);
//	void (*Usart3_Printf)(char *fmt,...);
  
}Usart_t;


extern Usart_t  Usart;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/* USER CODE END Prototypes */

#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
