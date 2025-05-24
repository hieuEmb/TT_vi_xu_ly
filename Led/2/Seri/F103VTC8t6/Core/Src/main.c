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
#include <string.h>
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

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char button1 =0, button2 = 0 , button3 = 0 ,button4 =0 ;
char data165 = 0xFF;
static uint32_t startTime = 0;
static uint32_t endTime = 0;
static uint16_t count =0;
uint8_t ledValues[4];
//luu tru tg troi giua 2 lan nhan nut
static uint32_t elapsedTime = 0;
//------------------------------------------------------

unsigned char maled_cc[10] = {0xAF, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xCF, 0xA2, 0xEF, 0xEB};
unsigned char led_position[5] = { 0x08, 0x10,0x20,0x40,0x80};  //Vi Tri Quet Led
void led(uint8_t vi_tri, uint8_t sang_led)
{
	for( uint8_t i=0; i<8;i++)
	{
		HAL_GPIO_WritePin(DATA_GPIO_Port,DATA_Pin,(led_position[vi_tri]&(0x80>>i)));
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
	}
	for( uint8_t i=0; i<8;i++)
	{
		HAL_GPIO_WritePin(DATA_GPIO_Port,DATA_Pin,(maled_cc[sang_led]&(0x80>>i)));
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0, GPIO_PIN_RESET);
}

//timer
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
void get_data165(){
	HAL_GPIO_WritePin( LATCH_B_GPIO_Port,LATCH_B_Pin,1);
	HAL_GPIO_WritePin( LATCH_B_GPIO_Port,LATCH_B_Pin,0);
	HAL_GPIO_WritePin( LATCH_B_GPIO_Port,LATCH_B_Pin,1);
	for(uint8_t i = 0; i<=7; i++){
		if(HAL_GPIO_ReadPin( 	MISO_GPIO_Port, MISO_Pin)==0)
			data165 &=~(1<<(7-i));
		else data165 |=(1<<(7-i));
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
	}
}
uint32_t raise_value()
{
    get_data165();
		static uint32_t previousCount = 0; // Bi?n d? luu tr? giá tr? count tru?c dó

    // Luu tr? giá tr? tru?c c?a count
    uint32_t tempCount = count;
		if((data165 & (1<<5)) == 0 && button2==0)
			{
				button2 = 1; 
			}
//    uint32_t elapsedTime = 0;
//    if ((data165 & (1 << 5)) == 0 && button2 == 0)
//   {
//        startTime = __HAL_TIM_GET_COUNTER(&htim2);
//        while ((data165 & (1 << 5)) == (1 << 5) && button2 == 1);
//        endTime = __HAL_TIM_GET_COUNTER(&htim2);
//        elapsedTime = endTime - startTime;
				// Làm tròn giá tr? elapsedTime
//				float roundedElapsedTime = round(elapsedTime); 
//        startTime = 0;
        // Delay to avoid bouncing ;
//					float roundedElapsedTime = round(count); 
//				return elapsedTime;
		return count;
}
//	

	


void displayTimeOn7Segment(uint32_t time) {
    char displayBuffer[8];
    sprintf(displayBuffer, "%04lu", (unsigned long) time);
		for(int i = 0; i < 5; i++) {
       	ledValues[i] = displayBuffer[i] - '0'; // Luu giá tri LED vào mang				
    }
}

// ham quet led
void scanLEDs() {
    for(int i = 0; i < 5; i++) {
        led(i, ledValues[i]); // Su dung giá tri LED trong mang ledValues
        HAL_Delay(1); // Delay de hien thi LED
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2, GPIO_PIN_RESET);
  while (1)
  {
		led(0, 0);
		//delay_ms(1);
		led(1, 0);
		//delay_ms(1);
		led(2, 0);
		//delay_ms(1);
		led(3, 0);
		//delay_ms(1);
		led(4, 0);
		//delay_ms(1);
		led(5, 0);
		//delay_ms(1);
		
		
		//raise_value();
		//raise_value();
		//displayTimeOn7Segment(count);		
		//scanLEDs();
//	vitri	
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);

//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//	
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		
////	led	
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, GPIO_PIN_RESET);
//		
//		
//	
//		
//		
//		
//		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0, GPIO_PIN_RESET);
//	
//		
//		while(1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|LATCH_Pin|LATCH_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CLK_Pin|DATA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 LATCH_Pin LATCH_B_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_2|LATCH_Pin|LATCH_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CLK_Pin DATA_Pin */
  GPIO_InitStruct.Pin = CLK_Pin|DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MISO_Pin */
  GPIO_InitStruct.Pin = MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MISO_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    // Th?c hi?n các thao tác c?n thi?t khi timer 2 k?t thúc n?a chu k?
    count++; // Ví d?: Tang bi?n a lên 1

    // Thêm các thao tác khác t?i dây n?u c?n
  }

  // Tránh c?nh báo v? bi?n chua du?c s? d?ng
  UNUSED(htim);
}

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
