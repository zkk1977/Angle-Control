#include "usart.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "led.h"
#include "pid.h"
/* USER CODE BEGIN 0 */

static u8 MessagePro_Flag = 0;      //��Ϣ�����־λ
//���ڻ����ֽ�
u8 Usart1_Rx_Buff[Usart_Rx_MaxLen];	//����1���ݽ��ջ����� 
u8 Usart1_Tx_Buff[Usart_Tx_MaxLen]; //����1���ݷ��ͻ����� 
u8 Usart1_Message_Buff[Usart_Rx_MaxLen] = {0x00};//����1��Ϣ�������� 

u8 Usart2_Rx_Buff[Usart_Rx_MaxLen];	//����2���ݽ��ջ����� 
u8 Usart2_Tx_Buff[Usart_Tx_MaxLen]; //����2���ݷ��ͻ����� 
u8 Usart2_Message_Buff[Usart_Rx_MaxLen]= {0x00};//����2��Ϣ�������� 

//u8 Usart3_Rx_Buff[Usart_Rx_MaxLen];	//����3���ݽ��ջ����� 
//u8 Usart3_Tx_Buff[Usart_Tx_MaxLen]; //����3���ݷ��ͻ����� 



//���ڽṹ�������ֵ
Usart_t Usart =
{
  0,0,          //�����ֽ���
 Usart1_Rx_Buff,  //���ջ���
 Usart1_Tx_Buff,  //���ͻ���
	
 Usart2_Rx_Buff,  //���ջ���
 Usart2_Tx_Buff,  //���ͻ���
	
// Usart3_Rx_Buff,  //���ջ���
// Usart3_Tx_Buff,  //���ͻ���
	
 Hal_USART1_UART_Init,      //����1��ʼ��
 Hal_USART2_UART_Init,      //����2��ʼ��
// Usart3_Init,      //����3��ʼ��
	
 Hal_SendString,      //�����ַ���
 Hal_SendData,        //��������
 Hal_Usart1_Printf,
 Hal_Usart2_Printf,
// Usart3_Printf,
};

 
#if 0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((huart1.Instance->SR&0X40)==0);//ѭ������,ֱ���������   
    huart1.Instance->DR = (u8) ch;      
	return ch;
}
#endif 
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;


/*******************************************************************************
* ������  : USER_UART_RxCpltCallback
* ����    : ���ڻص�����--�û����ݴ�����ֱ�Ӷ�Usartx_Message_Buff���д���
* ����    : *huart���˿ں�
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void USER_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char Target1[Usart_Rx_MaxLen];
	char Target2[Usart_Rx_MaxLen];
		/*����1���ݴ���*/
	if(huart->Instance==USART1)
	{
		if(strstr((char *)Usart1_Message_Buff,"T"))	
      {
				strncpy((char *)Target1,(char *)Usart1_Message_Buff+1,Usart_Rx_MaxLen);
				pid.set=atof((char *)Target1);   //�������趨ֵ����PID����
				LED_ON;
			}
			memset((char *)Target1,'\0',	Usart_Rx_MaxLen);
			memset((char *)Usart1_Message_Buff,'\0',	Usart_Rx_MaxLen);
  }


	/*����2���ݴ���*/
	if(huart->Instance==USART2)
	{
		if(strstr((char *)Usart2_Message_Buff,"P"))	
      {
				LED_ON;
				strncpy((char *)Target2,(char *)Usart2_Message_Buff+1,Usart_Rx_MaxLen);
				pid.curr=atof((char *)Target2);   //���Ƕȶ���PID����
			}
		  memset((char *)Target2,'\0',	Usart_Rx_MaxLen);
			memset((char *)Usart2_Message_Buff,'\0',Usart_Rx_MaxLen);
  }
	MessagePro_Flag = 0;    //��Ϣ�������
}




void USART1_IRQHandler(void)                	
{ 
	   u16 i;
   if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET)
	  {
	    __HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
		 	Usart.Usart1_Rx_Buff[Usart.Usart1_Count++] = (u8)(huart1.Instance->DR);
		 if(Usart.Usart1_Count>Usart_Rx_MaxLen) Usart.Usart1_Count = 0;
	  }
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET)
	  {
	    __HAL_UART_CLEAR_IDLEFLAG(&huart1);
				/*����1���ݴ���*/
			if(MessagePro_Flag ==0)
			{
				MessagePro_Flag = 1;
				for(i=0;i<Usart.Usart1_Count;i++)
				  Usart1_Message_Buff[i] = Usart.Usart1_Rx_Buff[i];
		  	USER_UART_RxCpltCallback(&huart1);
			}
			memset((char *)Usart.Usart1_Rx_Buff,'\0',Usart.Usart1_Count);
			Usart.Usart1_Count= 0;
		}
}


void USART2_IRQHandler(void)                	
{   
	   u16 i;
		if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET)
	  {
	    __HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
		 	Usart.Usart2_Rx_Buff[Usart.Usart2_Count++] = (u8)(huart2.Instance->DR);
		 if(Usart.Usart2_Count>Usart_Rx_MaxLen) Usart.Usart2_Count = 0;
	  }
    if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE)!=RESET)
	  {
	    __HAL_UART_CLEAR_IDLEFLAG(&huart2);
			/*����2��Ϣ�������*/
			if(MessagePro_Flag ==0)
			{
				MessagePro_Flag = 1;
				for(i=0;i<Usart.Usart2_Count;i++)
				  Usart2_Message_Buff[i] = Usart.Usart2_Rx_Buff[i];
		  	USER_UART_RxCpltCallback(&huart2);
			}
			memset((char *)Usart.Usart2_Rx_Buff,'\0',Usart.Usart2_Count);
			Usart.Usart2_Count= 0;
		}
		
}


/* USART1 init function */

void Hal_USART1_UART_Init(u32 bound)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = bound;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//�����ж�ʹ��
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);//�����ж�ʹ��

}
/* USART2 init function */

void Hal_USART2_UART_Init(u32 bound)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = bound;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);

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

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
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

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 
/*******************************************************************************
* ������  : Usart1_Printf
* ����    : USART1��������
* ����    : *fmt���ݸ�ʽ,...�����͵�����
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Hal_Usart1_Printf (char *fmt, ...)
{ 
	char Buffer[Usart_Tx_MaxLen+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(Buffer, Usart_Tx_MaxLen+1, fmt, arg_ptr);
	while ((i < Usart_Tx_MaxLen) && (i < strlen(Buffer)))
	{
			while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET); 
		   huart1.Instance->DR = (u8) Buffer[i++];
	}
	va_end(arg_ptr);
}

/*******************************************************************************
* ������  : Hal_Usart2_Printf
* ����    : USART2��������
* ����    : *fmt���ݸ�ʽ,...�����͵�����
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Hal_Usart2_Printf (char *fmt, ...)
{ 
	char Buffer[Usart_Tx_MaxLen+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(Buffer, Usart_Tx_MaxLen+1, fmt, arg_ptr);
	while ((i < Usart_Tx_MaxLen) && (i < strlen(Buffer)))
	{
			while (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == RESET); 
		   huart2.Instance->DR = (u8) Buffer[i++];
	}
	va_end(arg_ptr);
}

/*******************************************************************************
* ������  : Hal_SendString
* ����    : USART�����ַ���
* ����    : *s�ַ���ָ��,huartxָ���Ĵ���
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Hal_SendString(char* s,UART_HandleTypeDef huartx)
{
	while(*s)
	{
		
		while(__HAL_UART_GET_FLAG(&huartx, UART_FLAG_TC)==RESET); 
		  huartx.Instance->DR = *s++;
	}
}

/*******************************************************************************
* ������  : Hal_SendData
* ����    : USART��������
* ����    : data����,huartxָ���Ĵ���
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Hal_SendData(u8 data,UART_HandleTypeDef huartx)
{ 
	while(__HAL_UART_GET_FLAG(&huartx, UART_FLAG_TC)==RESET); 
    huartx.Instance->DR = (u8)data;   

}
