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
#define K_Pin GPIO_PIN_0
#define K_GPIO_Port GPIOB
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOB
#define P4_Pin GPIO_PIN_14
#define P4_GPIO_Port GPIOE
#define P1_Pin GPIO_PIN_11
#define P1_GPIO_Port GPIOD
#define S2_Pin GPIO_PIN_12
#define S2_GPIO_Port GPIOD
#define S1_Pin GPIO_PIN_13
#define S1_GPIO_Port GPIOD
#define P2_Pin GPIO_PIN_6
#define P2_GPIO_Port GPIOC
#define P3_Pin GPIO_PIN_7
#define P3_GPIO_Port GPIOC
#define AUTO_Pin GPIO_PIN_8
#define AUTO_GPIO_Port GPIOC
#define MAN_Pin GPIO_PIN_15
#define MAN_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
