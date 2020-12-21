/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "led.h"
#include "pid.h"
#include "delay.h"
#include "hmilcd.h"
#include "mpu6050.h"
#include "inv_mpu.h"
/**************************接口说明**********************

PWM输出：PB5
USART1:PA9(TX)  PA10(RX)
USART2:PA2(TX)  PA3(RX)
MPU6050:
SCL:PB10   SDA:PB11  INT:PA4   ADO:PA

*********************************************************/
int main(void)
{
//  u8  flag = 1;
//	float *yaw,*roll,*pitch;
	
  HAL_Init();
  SystemClock_Config();
	Hal_Delay_init();
  Hal_Led_Init();
  Usart.Hal_Usart1_Init(9600);
	Usart.Hal_Usart2_Init(9600);
  Hal_TIM3_Pwm_Init(19,0);    
	Hal_TIM2_Init(99,7199); //10ms中断
	MPU_Init();
	PIDParament_Init();
  while (1)
  {
		Hmi_Send_Float("t1",pid.curr,Usart_Port1);//发送当前角度到屏幕
		Hal_Delay_ms(100);
  }

}


