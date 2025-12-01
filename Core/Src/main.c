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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "headfile.h"
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

/* USER CODE BEGIN PV */
//OLED显示变量
unsigned char display_buf[20] = {0};
uint8_t oled_slowtime;
//速度环PID变量
int8_t target_speed = 0;
float yaw_target = -180;
//循迹数据获取
uint8_t gray_data;
//串口1变量：调试/调参/总线舵机接收当前角度
uint8_t head1 = 0x03;
uint8_t head2 = 0xfc;
uint8_t tail1 = 0xfc;
uint8_t tail2 = 0x03;
uint8_t uart_tx_time;
uint8_t uart_rx_data[20] = {0};
//串口3变量：JY61P用
uint8_t jy61p_data;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//上位机波形调PID
void DataVision_Send()
{
	uint8_t target = (uint8_t)motorL.target;
	uint8_t now = (uint8_t)motorL.now;
	HAL_UART_Transmit(&huart1, &head1, 1, 10);
	HAL_UART_Transmit(&huart1, &head2, 1, 10);
	
	HAL_UART_Transmit(&huart1, &target, 1, 10);
	HAL_UART_Transmit(&huart1, &now, 1, 10);
	
	HAL_UART_Transmit(&huart1, &tail1, 1, 10);
	HAL_UART_Transmit(&huart1, &tail2, 1, 10);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		jy61p_ReceiveData(jy61p_data);
		HAL_UART_Receive_IT(&huart3, &jy61p_data, 1);
	}
	
//	//获取舵机当前角度
//	if(huart == &huart1)
//	{
//		if(get_x_angle_flag | get_y_angle_flag)
//		{
//			HAL_UART_Transmit(&huart3, uart_rx_data, sizeof(uart_rx_data), 10);
//			Analysis_Rx_Data(uart_rx_data);
//			get_x_angle_flag = get_y_angle_flag = 0;
//		}
//		HAL_UART_Transmit(&huart3, uart_rx_data, sizeof(uart_rx_data), 10);
//		memset(uart_rx_data, 0, sizeof(uart_rx_data));
//		HAL_UART_Receive_IT(&huart1, uart_rx_data, sizeof(uart_rx_data));

//	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	//获取舵机当前角度
	if(huart == &huart1)
	{
//		if(get_x_angle_flag | get_y_angle_flag)
//		{
////			HAL_UART_Transmit(&huart3, uart_rx_data, sizeof(uart_rx_data), 10);
//			Analysis_Rx_Data(uart_rx_data);
//			get_x_angle_flag = get_y_angle_flag = 0;
//		}
		HAL_UART_Transmit(&huart3, uart_rx_data, sizeof(uart_rx_data), 10);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_data, sizeof(uart_rx_data));
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
	}
}
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
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
//	//开启定时器1中断
//	HAL_TIM_Base_Start_IT(&htim1);
//	//开启JY61P串口中断
//	HAL_UART_Receive_IT(&huart3, &jy61p_data, 1);
//	//开启总线舵机串口中断
//	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_data, sizeof(uart_rx_data));
//	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
////	HAL_UART_Receive_IT(&huart1, uart_rx_data, sizeof(uart_rx_data));
//	//OLED初始化
//	HAL_Delay(20);//OLED上电自动初始化需要时间
//	OLED_Init();
//	OLED_Clear();
//	//电机初始化
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//	//PWM舵机初始化
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
//	//编码器初始化
//	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
//	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
//	//PID初始化
//	Pid_Init(&motorL, DELTA_PID, 3.06, 0.1720, 0.0041);
//	Pid_Init(&motorR, DELTA_PID, 3.058, 0.1715, 0.0045);
//	Pid_Init(&angle, POSITION_PID, 10, 0, 0);
//	Set_Bus_Servo_X_Angle(180);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/********************角度环调试***********************/
//		sprintf((char *)display_buf, "yaw_p:%.2lf  ", Yaw);
//		OLED_ShowString(0, 0, display_buf, 16);
//		sprintf((char *)display_buf, "speed_left:%.d", speed_left);
//		OLED_ShowString(0, 4, display_buf, 16);
//		sprintf((char *)display_buf, "gray_data:%d%d%d%d-%d%d%d%d", (gray_data>>0)&0x01,(gray_data>>1)&0x01,(gray_data>>2)&0x01,(gray_data>>3)&0x01,(gray_data>>4)&0x01,(gray_data>>5)&0x01,(gray_data>>6)&0x01,(gray_data>>7)&0x01);
//		OLED_ShowString(0, 6, display_buf, 16);
//		
//		sprintf((char *)display_buf, "yaw_t:%.0lf  ", yaw_target);
//		OLED_ShowString(0, 2, display_buf, 16);
		/********************速度环目标速度OLED显示***********************/
//		if(++oled_slowtime == 100)
//		{
//			oled_slowtime = 0;
//			sprintf((char *)display_buf, "target_speed:%d   ", target_speed);
//			OLED_ShowString(0, 0, display_buf, 16);
//		}
		/********************舵机当前角度获取***********************/
		sprintf((char *)display_buf, "x_servo:%.2f   ", now_x_angle);
		OLED_ShowString(0, 0, display_buf, 16);
		sprintf((char *)display_buf, "y_servo:%.2f   ", now_y_angle);
		OLED_ShowString(0, 2, display_buf, 16);
		Get_Y_Servo_Angle();
		HAL_Delay(500);
//			OLED_ShowString(0, 0, uart_rx_data, 16);

		/********************上位机调试***********************/
//		if(++uart_tx_time == 10)
//		{
//			uart_tx_time = 0;
//			DataVision_Send();
//		}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
