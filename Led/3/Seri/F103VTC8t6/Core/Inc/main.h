/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LOA_Pin GPIO_PIN_3
#define LOA_GPIO_Port GPIOE
#define D4_Pin GPIO_PIN_0
#define D4_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_1
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_2
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_3
#define D7_GPIO_Port GPIOD
#define EN_Pin GPIO_PIN_5
#define EN_GPIO_Port GPIOD
#define CS_Pin GPIO_PIN_7
#define CS_GPIO_Port GPIOD
#define CLK_Pin GPIO_PIN_3
#define CLK_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_4
#define MISO_GPIO_Port GPIOB
#define DATA_Pin GPIO_PIN_5
#define DATA_GPIO_Port GPIOB
#define LATCH_Pin GPIO_PIN_0
#define LATCH_GPIO_Port GPIOE
#define LATCH_B_Pin GPIO_PIN_1
#define LATCH_B_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
