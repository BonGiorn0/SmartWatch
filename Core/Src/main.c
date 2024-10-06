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
#include "CircularBuffer.h"
#include "st7735.h"
#include "lsm6d3s.h"
#include "dial.h"
#include "PulseData.h"
#include <stdio.h>


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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

uint32_t time_on_start;
int pulse = 0;
uint32_t pulse_falling_edge_time;
uint32_t between_pulse_interval;
uint32_t pulse_rising_edge_time;
uint32_t pulse_interval;

uint8_t tmp_char = 'a';
uint8_t tmp_char2 = 'a';


char pc_tx_buff[100] = "";
size_t pc_tx_buff_size = 0;

char esp01_tx_buff[100] = "";
size_t esp01_tx_buff_size = 0;

CircularBuffer esp01_rx_cb;

char user_buff[100] = "";
size_t user_buff_size = 0;

int pcIsSent = 1;
int esp01IsSent = 1;
int pcDataReady = 0;
int esp01DataReady = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  circ_buffer_init(&esp01_rx_cb);
  ST7735_Init();
  LSM6DS3_Init();
  ST7735_SetRotation(ST7735_LANDSCAPE);
  ST7735_Backlight_On();
  ST7735_FillScreen(ST7735_BLACK);

  uint32_t time = 14 * 3600 + 42 * 60 + 0;
  time_on_start = HAL_GetTick();
  //drawClockDial(time);



  //ST7735_DrawString(ST7735_GetWidth() / 2 - Font_16x26.width / 2 * 5, ST7735_GetHeight() / 2 - Font_16x26.height / 2, "13:42", Font_16x26, ST7735_WHITE, ST7735_BLACK);

  HAL_UART_Receive_IT(&huart2, &tmp_char, 1);
  HAL_UART_Receive_IT(&huart1, &tmp_char2, 1);


  while (1)
  {
	  /*redrawClockHands(time);
	  time++;
	  HAL_Delay(1000 - 63);*/

	  if(pcIsSent == 1 && pcDataReady == 1){
		  pcIsSent = 0;
		  pcDataReady = 0;
		  char str[80];
		  int size = sprintf(str, "\r>>%s ", pc_tx_buff);
		  //HAL_UART_Transmit_IT(&huart2, str, size);
		  ST7735_DrawString(0, 0, str, Font_7x10, ST7735_WHITE, ST7735_BLACK);
	  }
	  if(esp01IsSent == 1 && esp01DataReady == 1){
	  	  	esp01IsSent = 0;
	  	  	esp01DataReady = 0;
	  	  	char str[80];
	  	  	int size = sprintf(str, "%s\r\n", esp01_tx_buff);
	  	  	HAL_UART_Transmit_IT(&huart1, str, size);


	  }
	  char letter[3] = {'X', 'Y', 'Z'};
	  uint16_t color[3] = {ST7735_RED, ST7735_BLUE, ST7735_GREEN};
	  int16_t raw[3];
	  float xyz[3];
	  char str[10];
	  LSM6DS3_AccGetXYZ(xyz);
	  LSM6DS3_AccGetRawXYZ(raw);
	  for (int i = 0; i < 3; ++i) {
		  sprintf(str, "%c: %.3f", letter[i], xyz[i]);
		  ST7735_DrawString(5, 20 + i * Font_11x18.height + i, str, Font_11x18, color[i], ST7735_BLACK);
	  }
	  HAL_UART_Transmit(&huart2, (uint8_t *)raw, 3 * 2, HAL_MAX_DELAY);

	  /*HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  int raw = HAL_ADC_GetValue(&hadc1);
	  drawPulseGraphDot(raw);*/

	  /*char buf[5] = "";
	  sprintf(buf, "%du", raw);
	  ST7735_DrawString(ST7735_GetWidth() / 2 - Font_16x26.width / 2 * 5, ST7735_GetHeight() / 2 - Font_16x26.height / 2,
			  buf, Font_16x26, ST7735_WHITE, ST7735_BLACK);
	  //HAL_Delay(10);*/
	  /*if(raw > 2090){
		  if(pulse == 0){
			  between_pulse_interval = HAL_GetTick() - pulse_falling_edge_time;
			  pulse_rising_edge_time = HAL_GetTick();
		  }

		  pulse = 1;
		  drawHeart();
	  }else{
		  if(pulse == 1){
			  pulse_interval = HAL_GetTick() - pulse_rising_edge_time;
			  pulse_falling_edge_time = HAL_GetTick();
		  }

		  pulse = 0;
		  ST7735_FillRectangle(130, 10, 20, 20, ST7735_BLACK);
	  }

	  if(HAL_GetTick() - time_on_start > 1000)
	  	drawBPM(60000 / ((pulse_interval + between_pulse_interval)));
	  else
	  	drawBPM(255);

	  HAL_Delay(10);*/



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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 10000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_BLK_Pin|GPIO_PIN_13|ST7735_RES_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_BLK_Pin PB13 ST7735_RES_Pin */
  GPIO_InitStruct.Pin = ST7735_BLK_Pin|GPIO_PIN_13|ST7735_RES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ST7735_DC_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_DC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */



void PC_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(tmp_char == 127){
		if(user_buff_size > 0){
			user_buff_size--;
			user_buff[user_buff_size] = '\0';
			strcpy(pc_tx_buff, user_buff);
			pcDataReady = 1;
		}
	}
	else if(tmp_char == '\r')
	{
		strcpy(esp01_tx_buff, user_buff);
		user_buff_size = 0;
		user_buff[0] = '\0';
		esp01DataReady = 1;
	}
	else
	{
		user_buff[user_buff_size] = tmp_char;
		user_buff_size++;
		user_buff[user_buff_size] = '\0';
		strcpy(pc_tx_buff, user_buff);
		pcDataReady = 1;
	}
	HAL_UART_Receive_IT(&huart2, &tmp_char, 1);

}

void ESP01_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(tmp_char2 == '\n'){
		circ_buffer_put(&esp01_rx_cb, '\n');

		/*do
		{
			circ_buffer_get(&esp01_rx_cb, &data);
			pc_tx_buff[pc_tx_buff_size] = data;
			pc_tx_buff_size++;
		}
		while(data != '\n');*/
		int l;
		if(esp01_rx_cb.head > esp01_rx_cb.tail){
			l = esp01_rx_cb.head - esp01_rx_cb.tail;
		}else{
			l = CIRC_BUFFER_SIZE - esp01_rx_cb.tail + esp01_rx_cb.head;
		}
		for (int i = 0; i < l; ++i) {
			uint8_t data = '\0';
			circ_buffer_get(&esp01_rx_cb, &data);
			pc_tx_buff[pc_tx_buff_size] = data;
			pc_tx_buff_size++;
		}
		pcDataReady = 1;

	}else{
		circ_buffer_put(&esp01_rx_cb, tmp_char2);
	}

	HAL_UART_Receive_IT(&huart1, &tmp_char2, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2)
		PC_UART_RxCpltCallback(huart);
	if(huart->Instance == USART1)
		ESP01_UART_RxCpltCallback(huart);
}

void ESP01_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	esp01IsSent = 1;
	esp01DataReady = 0;
	esp01_tx_buff[0] = '\0';
	esp01_tx_buff_size = 0;
}

void PC_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	pcIsSent = 1;
	pcDataReady = 0;
	pc_tx_buff[0] = '\0';
	pc_tx_buff_size = 0;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2)
			PC_UART_TxCpltCallback(huart);
	if(huart->Instance == USART1)
			ESP01_UART_TxCpltCallback(huart);
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
