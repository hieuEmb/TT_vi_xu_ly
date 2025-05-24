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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint8_t P1;
uint8_t P2;
uint8_t P3;
uint8_t P4;
uint8_t MAN;
uint8_t AUTO;
uint8_t S0;
uint8_t S1;
uint8_t S2;
uint8_t S3;
uint8_t S4;
uint8_t S5;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_1ms(void)
{
 __HAL_TIM_SetCounter(&htim2, 0);
 while (__HAL_TIM_GetCounter(&htim2)<20);
}
void delay_ms(int time)
{
 int i = 0;
 for(i = 0; i < time; i++)
 {
   delay_1ms();
 }
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
// Set timer
		HAL_TIM_Base_Start(&htim2);

// Set K
	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Y3_GPIO_Port,Y3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//Read sensor
		P1 = HAL_GPIO_ReadPin(P1_GPIO_Port,P1_Pin); //P1 tra ve 2 gia tri 0 or 1, neu =0 nghia la nut da duoc nhan.
		P2 = HAL_GPIO_ReadPin(P2_GPIO_Port,P2_Pin); 
		P3 = HAL_GPIO_ReadPin(P3_GPIO_Port,P3_Pin);
		P4 = HAL_GPIO_ReadPin(P4_GPIO_Port,P4_Pin);
		MAN = HAL_GPIO_ReadPin(MAN_GPIO_Port,MAN_Pin);
		AUTO = HAL_GPIO_ReadPin(AUTO_GPIO_Port,AUTO_Pin);
		S0 = HAL_GPIO_ReadPin(S0_GPIO_Port,S0_Pin); 
		S1 = HAL_GPIO_ReadPin(S1_GPIO_Port,S1_Pin); 
		S2 = HAL_GPIO_ReadPin(S2_GPIO_Port,S2_Pin); 
		S3 = HAL_GPIO_ReadPin(S3_GPIO_Port,S3_Pin); 
		S4 = HAL_GPIO_ReadPin(S4_GPIO_Port,S4_Pin);
		S5 = HAL_GPIO_ReadPin(S5_GPIO_Port,S5_Pin); 

//Hoan thanh 1 chu trinh.
//Home
		if (P1==0&&(AUTO==0))
		{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_RESET);	//dong tay gap- vi tri ban dau la dong
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		//tren-duoi(S1-S2)
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); //trai- phai (S3-S4)- Muon o S3 thi tuong tac Y4, con muon o S4- thi tuong tac Y3
		}
			if (P2==0&&(AUTO==0))
		{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
		}
		if (S0==0&&(AUTO==0))
		{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	//ho ra	
			delay_ms(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			
			HAL_GPIO_WritePin(Y3_GPIO_Port,Y3_Pin, GPIO_PIN_RESET); // toi S4
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_RESET);	// xuong duoi
			HAL_Delay(5000);
			
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_RESET);	//dong lai
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);	// len
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); // toi S3
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);	// xuong
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	//ho ra	
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);	// len
			HAL_Delay(5000);
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_RESET);	//dong lai
			HAL_Delay(5000);//cau hinh timer de thay the. Viet mot ham timer.
			if (P2==0&&(AUTO==0))
			{
			HAL_GPIO_WritePin(Y1_GPIO_Port,Y1_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(Y2_GPIO_Port,Y2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Y4_GPIO_Port,Y4_Pin, GPIO_PIN_RESET); 
			}
			//Nhan nut stop de ve vi tri cu.
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 35999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Y1_Pin|Y2_Pin|Y3_Pin|Y4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : D1_Pin */
  GPIO_InitStruct.Pin = D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : D2_Pin */
  GPIO_InitStruct.Pin = D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Y1_Pin Y2_Pin Y3_Pin Y4_Pin */
  GPIO_InitStruct.Pin = Y1_Pin|Y2_Pin|Y3_Pin|Y4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : P4_Pin */
  GPIO_InitStruct.Pin = P4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(P4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : P1_Pin S5_Pin S0_Pin S4_Pin */
  GPIO_InitStruct.Pin = P1_Pin|S5_Pin|S0_Pin|S4_Pin;
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

  /*Configure GPIO pins : S3_Pin S2_Pin S1_Pin */
  GPIO_InitStruct.Pin = S3_Pin|S2_Pin|S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
