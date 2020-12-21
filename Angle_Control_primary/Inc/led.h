/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __led_H
#define __led_H


/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_ON    PEout(5)= 0
#define LED_OFF   PEout(5)= 1
/* USER CODE END Private defines */

void Hal_Led_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#endif 

