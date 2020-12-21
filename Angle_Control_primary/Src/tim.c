/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "pid.h"

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim2;



void Hal_TIM2_Init(u16 arr,u16 psc)
{  
    htim2.Instance=TIM2;                          //通用定时器2
    htim2.Init.Prescaler=psc;                     //分频系数
    htim2.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    htim2.Init.Period=arr;                        //自动装载值
    htim2.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&htim2);

    HAL_TIM_Base_Start_IT(&htim2); //使能定时器2和定时器2更新中断：TIM_IT_UPDATE   

}

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,0,2);    //设置中断优先级，抢占优先级0，子优先级2
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //开启ITM2中断   
	}
}

//定时器2中断服务函数
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

//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
    {
      PEout(5)=!PEout(5);
			pidcalc_10ms++;
			pid_calc();//200毫秒计算一次
    }
}

/******************************************************PWM输出部分************************************************/

/*TIM3 PWM output function*/
void Tim_PwmOutPut(TIM_HandleTypeDef htimx,u16 Pwm_Value)
{
  
  htimx.Instance->CCR2 = Pwm_Value;//改变比较值就是改变有效电平的占空比

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

  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);//使能PWM输出
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

