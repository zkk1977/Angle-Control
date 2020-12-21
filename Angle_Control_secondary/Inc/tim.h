/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H


/* Includes ------------------------------------------------------------------*/
#include "sys.h"


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;

void Hal_TIM2_Init(u16 arr,u16 psc);
void Hal_TIM3_Pwm_Init(u16 Arr,u16 Pre);                       
void Tim_PwmOutPut(TIM_HandleTypeDef htimx,u16 Pwm_Value);
                    

#endif
