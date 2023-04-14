/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include<stdlib.h>
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void UART_PRINT_VAL(double value);
void UART_PRINT_TEXT(uint8_t* MSG);

void UM7_INIT(void);
uint32_t UM7_GET_DATA(uint8_t addr);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  	double xAccel = 0;
	double yAccel = 0;
	double zAccel = 0;
	double xMag = 0;
	double yMag = 0;
	double zMag = 0;
	double xGyro = 0;
	double yGyro = 0;
	double zGyro = 0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	HAL_Delay(250);
	UM7_INIT();
	HAL_Delay(250);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //xAccel = UM7_GET_DATA(0x65);
	  //yAccel = UM7_GET_DATA(0X66);
	  //zAccel = UM7_GET_DATA(0x67);

	  uint8_t rx_data[11] = {0};
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	  HAL_UART_Receive(&huart1, rx_data, 11, 50);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	  UART_PRINT_TEXT(rx_data);
	  UART_PRINT_TEXT("\n");
	  //UART_PRINT_TEXT("Accelerometer: ");
	  //UART_PRINT_TEXT("( ");
	  //UART_PRINT_VAL(xAccel);
	  //UART_PRINT_TEXT(", ");
	  //UART_PRINT_VAL(yAccel);
	  //UART_PRINT_TEXT(", ");
	  //UART_PRINT_VAL(zAccel);
	  //UART_PRINT_TEXT(" )\n");
	  /*
	  UART_PRINT_TEXT("Magnetometer: ");
	  UART_PRINT_TEXT("( ");
	  UART_PRINT_VAL(xMag);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(yMag);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(zMag);
	  UART_PRINT_TEXT(" )\n");
	  UART_PRINT_TEXT("Gyro: ");
	  UART_PRINT_TEXT("( ");
	  UART_PRINT_VAL(xGyro);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(yGyro);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(zGyro);
	  */
	  //UART_PRINT_TEXT(" )\n");
	  HAL_Delay(30);
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

void UART_PRINT_VAL(double value){
	char total[50];
	sprintf(total, "%i", (int)value);
	strcat(total, ".");
	char temp[10];
	double currentVal = (value - (int) value);
	for(int a=0;a<1;a++){
		currentVal *= 10;
		sprintf(temp, "%i", abs((int)currentVal));
		strcat(total, temp);
		currentVal -= (int)currentVal;
	}
	HAL_UART_Transmit(&huart2, total, strlen(total), 100);
}
void UART_PRINT_TEXT(uint8_t* MSG){
	HAL_UART_Transmit(&huart2, MSG, strlen(MSG), 100);
}

void UM7_INIT(void){
	uint8_t tx_data2[4] = {0x00, 0x00, 0x00, 0x00};
	uint8_t tx_data1[4] = {0x00, 0x00, 0x00, 0xff};
	uint8_t tx_data3[4] = {0x00, 0x00, 0x00, 0xff};
	UM7_WRITE(0xac, tx_data2); // reset to factory settings
	HAL_Delay(1);
	//UM7_WRITE(0x02, tx_data2); // raw data rate (Hz)
	//UM7_WRITE(0x04, tx_data2); // processed data rate (Hz)
	uint8_t tx_data4[4] = {0x00, 0x00, 0x00, 0x00};
	UM7_WRITE(0x07, tx_data4);
	HAL_Delay(5);
}
void UM7_WRITE(uint8_t addr, uint8_t data[4]){
	uint8_t tx_data[11];
	tx_data[0] = 's';
	tx_data[1] = 'n';
	tx_data[2] = 'p';
	tx_data[3] = 0b10000000;
	tx_data[4] = addr;
	tx_data[5] = data[0];
	tx_data[6] = data[1];
	tx_data[7] = data[2];
	tx_data[8] = data[3];
	uint16_t sum = 0;
	for(int a=0;a<9;a++){
		sum += tx_data[a];
	}
	tx_data[9] = sum>>8;
	tx_data[10] = sum;
	HAL_UART_Transmit(&huart1, tx_data, 11, 100);
}
uint32_t UM7_GET_DATA(uint8_t addr){
	uint16_t sum = 0;
	sum = 's' + 'n' + 'p' + addr;
	uint8_t front = sum>>8;
	uint8_t back = sum;
	uint8_t tx_data[11] = {'s', 'n', 'p', 0x00, addr, 0x00, 0x00, 0x00, 0x00, front, back};
	uint8_t rx_data[11];
	HAL_UART_Transmit(&huart1, tx_data, 11, 100);
	HAL_UART_Receive(&huart1, rx_data, 11, 100);
	return ((rx_data[5]<<24 | rx_data[6]<<16) | (rx_data[7]<<8 | rx_data[8]));
}
// SPI MODE STUFF COMMENTED OUT
/*
void UM7_WRITE(uint8_t addr, uint8_t data[4]){
	uint8_t tx_data[6] = {0x01, addr, data[0], data[1], data[2], data[3]};
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_data, 6, 100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}
double UM7_GET_DATA(uint8_t addr){
	double val = 0;
	double value_exp = 0;
	double value_frac = 0;
	uint8_t tx_data[6] = {0x00, addr, 0x00, 0x00, 0x00, 0x00};
	uint8_t rx_data[6];
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	//HAL_SPI_Transmit(&hspi1, tx_data, 2, 100);
	//HAL_SPI_Receive(&hspi1, rx_data, 4, 100);
	HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 6, HAL_MAX_DELAY);
	//HAL_SPI_Receive_IT(&hspi1, rx_data, 4);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	value_exp = ((rx_data[2] & 0x7f) << 1) | (rx_data[3] >> 7);
	value_frac = ((rx_data[3] & 0x7f) << 16) | (rx_data[4] << 8 | rx_data[5]);
	//calc1 = power(2.0,value_exp - 127);
	val = (1.0 + value_frac / 10000000.0) * pow(2.0,value_exp - 127);
	return val;
}
*/
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
