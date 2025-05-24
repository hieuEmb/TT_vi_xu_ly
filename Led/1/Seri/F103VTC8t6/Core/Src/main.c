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
#include <stdio.h>
#include <string.h>

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
static int8_t a1=0;
static int8_t a2=0;
static uint8_t seed = 0;	
static uint8_t a3=3;


//------------------------------------------------------
//Ham tao so ngay nhien tu 0-9
uint8_t random_value() {
    seed = (seed * 1103515245 + 12345) % 10;
    return seed;
}

void UART_Send_Value(int value) {
    char buffer[3]; // Tao mang co kieu ky tu chua gia tri, bao gom 2 chu so và ký tu ket thúc chuoi("55 ")
    snprintf(buffer, sizeof(buffer), "%02d", value); // Format gia tri thanh chuoi(55)
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY); // Gui chuoi qua UART (55)
}

// Khai bao ham dua gia tri len Terminal may tinh.
void send_count_to_terminal(int8_t tens, int8_t ones) {
		UART_Send_Value(tens * 10 + ones); // Gui giá tri(55) qua UART
}



//Ham xuat gia tri led ra chan PB5
//Ham doc vi tri led va gia tri led--> ten ham led(doi so vi tri, doi so gia tri led)
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

//Ham lay gia 8 bit doc vao tu chan PB4
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
	
//Ham xu ly khi nhan nut.
void raise_value()
{
//Ham lua chon		
	get_data165();
	//Nut nhan 2(dk_1)
	if((data165 & (1<<5)) == 0 && button2==0)
	{
		//caulenh_1.0
		button2 = 1; a1++ ;
		//dk_1.1
		if(a1==10){
			a1=0; a2++;
		}
		//dk_1.2
		if(a1 == -1) {
			a1 = 9; a2--;
		}
		//caulenh1.3
		send_count_to_terminal(a2, a1); // doi so vao a2=5, a1=5 
	}
	else if((data165 & (1<<5))== (1<<5) && button2 == 1 )
	{
		button2 = 0;
	}
	
	//Nut nhan 3(dk_2)	
	if((data165 & (1<<6)) == 0 && button3==0)
	{
		button3=1 ; a1++ ; 
		if(a1==10){
			a1=0; a2++;
		}
		if(a1 == -1) {
			a1 = 9; a2--;
		}
		send_count_to_terminal(a2, a1); // doi so vao a2=5, a1=5
	}
	else if((data165 & (1<<6)) == (1<<6) && button3 == 1 )
	{
		button3=0; 
	}
	//Nut nhan 4
	if((data165 & (1<<7)) == 0 && button4==0)
	{
		button4 = 1 ; a1-- ; 
		if(a1==10){
			a1=0; a2++;
		}
		if(a1 == -1) {
			a1 = 9; a2--;
		}
		send_count_to_terminal(a2, a1); // doi so vao a2=5, a1=5 
	}
	else if((data165 & (1<<7))== (1<<7) && button4 == 1 )
	{
		button4 = 0; 
	}

////Ham lua chon
//if(a1 == 10) {
//    a1 = 0;
//    a2++;
//}
//if(a1 == -1) {
//  a1 = 9;  
//	a2--;
//}

//Ham thuc thi chinh.
led(0, a2);//a2: hang chuc, a1 hang don vi 
led(1, a1);// Ham tra ve led sang vi tri 0-->2, gia tri moi led tu (0-->9).	

}


//Ham truyen du lieu

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//khoi tao gia tri cho a1 va a2
	a1 = random_value();
  a2 = random_value();
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
		raise_value();		
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
