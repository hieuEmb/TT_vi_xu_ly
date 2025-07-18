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
#include "stm32f2xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D1_Pin GPIO_PIN_7
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_1
#define D2_GPIO_Port GPIOB
#define Y1_Pin GPIO_PIN_7
#define Y1_GPIO_Port GPIOE
#define Y2_Pin GPIO_PIN_8
#define Y2_GPIO_Port GPIOE
#define Y3_Pin GPIO_PIN_9
#define Y3_GPIO_Port GPIOE
#define Y4_Pin GPIO_PIN_10
#define Y4_GPIO_Port GPIOE
#define P4_Pin GPIO_PIN_14
#define P4_GPIO_Port GPIOE
#define P1_Pin GPIO_PIN_11
#define P1_GPIO_Port GPIOD
#define S5_Pin GPIO_PIN_12
#define S5_GPIO_Port GPIOD
#define S0_Pin GPIO_PIN_13
#define S0_GPIO_Port GPIOD
#define P2_Pin GPIO_PIN_6
#define P2_GPIO_Port GPIOC
#define P3_Pin GPIO_PIN_7
#define P3_GPIO_Port GPIOC
#define AUTO_Pin GPIO_PIN_8
#define AUTO_GPIO_Port GPIOC
#define MAN_Pin GPIO_PIN_15
#define MAN_GPIO_Port GPIOA
#define S4_Pin GPIO_PIN_7
#define S4_GPIO_Port GPIOD
#define S3_Pin GPIO_PIN_3
#define S3_GPIO_Port GPIOB
#define S2_Pin GPIO_PIN_4
#define S2_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_5
#define S1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
