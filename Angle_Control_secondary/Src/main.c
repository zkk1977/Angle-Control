/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "hmilcd.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "string.h"
/**************************接口说明**********************

PWM输出：PB5
USART1:PA9(TX)  PA10(RX)
USART2:PA2(TX)  PA3(RX)
MPU6050:
SCL:PB10   SDA:PB11  INT:PA4   ADO:PA

*********************************************************/
int main(void)
{
	float *yaw,*roll,*pitch;
	char Temp[20];
  HAL_Init();
  SystemClock_Config();
	Hal_Delay_init();
//  Hal_Led_Init();
  Usart.Hal_Usart1_Init(9600);
//	Usart.Hal_Usart2_Init(9600);
//  Hal_TIM3_Pwm_Init(999,71);
//	Hal_TIM2_Init(999,7199); //100ms中断
	MPU_Init();
  while (1)
  {
		mpu_dmp_get_data(pitch,roll,yaw);
	  sprintf(Temp,"P%.1f",*pitch);  //将角度转为字符串发送
		printf("%s\r\n",Temp);
		Hal_Delay_ms(100);		
  }

}


