/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUTTON_PRESSED 0  //nhan nut, tin hieu doc vao la 0.
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t P1;
uint8_t P2;
uint8_t P3;
uint8_t P4;
uint8_t MAN;
uint8_t AUTO;
uint8_t S1;
uint8_t S2;

// bien uart
uint8_t rx_data;
uint8_t index_rx=0; 
uint8_t rx_buffer[4];

// bien timer
uint16_t count;
uint16_t ms =0;

// bien giu
uint8_t final_station;
uint8_t SP =0;

// bien nhan uart
char Stop[] = "stop";
char Start[] = "start";
char Pause[] = "pause";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t docSoTuMang(uint8_t mang[], int doDai) {
        for (int i = 0; i < doDai; i++) {
        ms = ms * 10 + mang[i];
    }
    return ms;
}


//Ham truyen du lieu
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        if (rx_data == '\n') {
            HAL_UART_Transmit(&huart1, (uint8_t *)rx_buffer, index_rx, 100); // gui du lieu da nhan           
            memset(rx_buffer, 0, sizeof(rx_buffer)); // xoa du lieu trong mang rx_buffer
            index_rx = 0; // dat lai index_rx chuan bi cho du lieu tiep theo
        } else {
            rx_buffer[index_rx++] = rx_data; // luu ky tu vao mang rx_bufer
            // Kiem tra xem mang dã day chua
            if (index_rx >= sizeof(rx_buffer)) {
                // Neu da day, không làm gì cho xu lý tùy ý
            }
        }
        HAL_UART_Receive_IT(&huart1, &rx_data, 1); // Ti?p t?c nh?n d? li?u
    }
}


//Ham gui len uart
void UART_Send_Value(const char* value) {
    HAL_UART_Transmit(&huart1, (uint8_t *)value, strlen(value), HAL_MAX_DELAY); // G?i chu?i qua UART
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	// Ham goi uart
	HAL_UART_Receive_IT(&huart1, &rx_data, 1);
	
	// Ham Set ban dau
	HAL_GPIO_WritePin(K_GPIO_Port,K_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		// 1 tac dong trong 1 truong hop.
		P1 = HAL_GPIO_ReadPin(P1_GPIO_Port,P1_Pin); //P1 tra ve 2 gia tri 0 or 1, neu =0 nghia la nut da duoc nhan.
		P2 = HAL_GPIO_ReadPin(P2_GPIO_Port,P2_Pin); 
		P3 = HAL_GPIO_ReadPin(P3_GPIO_Port,P4_Pin);
		P4 = HAL_GPIO_ReadPin(P4_GPIO_Port,P4_Pin);
		MAN = HAL_GPIO_ReadPin(MAN_GPIO_Port,AUTO_Pin);
		AUTO = HAL_GPIO_ReadPin(AUTO_GPIO_Port,AUTO_Pin);
		S1 = HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin); // Khi co vat S1 tra ve 0 // co vat
		S2 = HAL_GPIO_ReadPin(S2_GPIO_Port,S2_Pin); // Khi co vat S2 tra ve 1 khi co vat, s1, s2 trai nguoc nhau, s1 tra ve gi, thi s2 tra ve nguoc lai
		HAL_StatusTypeDef status = HAL_UART_Receive_IT(&huart1, &rx_data, 1);
		
		if (strcmp((char *)rx_buffer, Start)==0) {
			HAL_GPIO_WritePin(K_GPIO_Port,K_Pin, GPIO_PIN_RESET);
		}
				
		if ((S2==1)&& (AUTO==0))
		{
			SP++;			
			UART_Send_Value("stop");									
		}
				
		if (strcmp((char *)rx_buffer, Pause)==0) {
			HAL_GPIO_WritePin(K_GPIO_Port,K_Pin, GPIO_PIN_SET);	
			HAL_Delay(3000);
			if(((S1==0)|(S2==1))&&AUTO==0)
			{
				HAL_GPIO_WritePin(K_GPIO_Port,K_Pin, GPIO_PIN_RESET);
				// gui nguoc lai len terminal chuoi stop.
			}
		}
			
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 249;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, K_Pin|D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : D1_Pin */
  GPIO_InitStruct.Pin = D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : K_Pin D2_Pin */
  GPIO_InitStruct.Pin = K_Pin|D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : P4_Pin */
  GPIO_InitStruct.Pin = P4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(P4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : P1_Pin S2_Pin S1_Pin */
  GPIO_InitStruct.Pin = P1_Pin|S2_Pin|S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : P2_Pin P3_Pin AUTO_Pin */
  GPIO_InitStruct.Pin = P2_Pin|P3_Pin|AUTO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : MAN_Pin */
  GPIO_InitStruct.Pin = MAN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MAN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
