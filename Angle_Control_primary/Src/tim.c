/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "pid.h"

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim2;



void Hal_TIM2_Init(u16 arr,u16 psc)
{  
    htim2.Instance=TIM2;                          //ͨ�ö�ʱ��2
    htim2.Init.Prescaler=psc;                     //��Ƶϵ��
    htim2.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    htim2.Init.Period=arr;                        //�Զ�װ��ֵ
    htim2.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&htim2);

    HAL_TIM_Base_Start_IT(&htim2); //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE   

}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,0,2);    //�����ж����ȼ�����ռ���ȼ�0�������ȼ�2
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM2�ж�   
	}
}

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
//	if(__HAL_TIM_GET_FLAG(&htim2,TIM_IT_UPDATE )!=RESET)
//	{
//	 __HAL_TIM_CLEAR_FLAG(&htim2, TIM_IT_UPDATE);
//		PEout(5)=!PEout(5);
//	 
//	}
}

//�ص���������ʱ���жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
    {
      PEout(5)=!PEout(5);
			pidcalc_10ms++;
			pid_calc();//200�������һ��
    }
}

/******************************************************PWM�������************************************************/

/*TIM3 PWM output function*/
void Tim_PwmOutPut(TIM_HandleTypeDef htimx,u16 Pwm_Value)
{
  
  htimx.Instance->CCR2 = Pwm_Value;//�ı�Ƚ�ֵ���Ǹı���Ч��ƽ��ռ�ձ�

}

/* TIM3 init function */
void Hal_TIM3_Pwm_Init(u16 Arr,u16 Pre)
{
  
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = Pre;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = Arr;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_PWM_Init(&htim3);
 

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);//ʹ��PWM���
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_AFIO_REMAP_TIM3_PARTIAL();
  /* USER CODE END TIM3_MspPostInit 0 */
		
    /**TIM3 GPIO Configuration    
    PA1     ------> TIM3_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }

}

