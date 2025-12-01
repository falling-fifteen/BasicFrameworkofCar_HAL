#include "bus_servo.h"
float range = MAX_COUNT - MIN_COUNT;
uint8_t uart_buf[20];
float now_x_angle;
float now_y_angle;
uint8_t get_x_angle_flag = 0;
uint8_t get_y_angle_flag = 0;
uint8_t rx_state;
//按键控制扭力释放与恢复
uint8_t toggle_power_flag;

//编号001
void Set_Bus_Servo_X_Angle(float angle)
{
	//限制角度在0到270度之间
	if(angle > 270)
	{
			angle = 270;
	}
	if(angle < 0)
	{
		angle = 0;
	}
	uint16_t duty = MIN_COUNT + ((angle / 270.0f) * range);

	//串口发送
	sprintf((char *)uart_buf, "#001P%04dT0000!", duty);
	HAL_UART_Transmit(&huart1, uart_buf, 20, 10);
}

//编号000
void Set_Bus_Servo_Y_Angle(float angle)
{
	//限制角度在0到243度之间
	if(angle > 243)
	{
			angle = 243;
	}
	if(angle < 13.5)
	{
		angle = 13.5;
	}
	uint16_t duty = MIN_COUNT + ((angle / 270.0f) * range);
	//串口发送
	sprintf((char *)uart_buf, "#000P%04dT0000!", duty);
	HAL_UART_Transmit(&huart1, uart_buf, 20, 10);
}

void Release_X_Servo(void)
{
	sprintf((char *)uart_buf, "#001PULK!");
	HAL_UART_Transmit(&huart1, uart_buf, 9, 10);
}

void Release_Y_Servo(void)
{
	sprintf((char *)uart_buf, "#000PULK!");
	HAL_UART_Transmit(&huart1, uart_buf, 9, 10);
}

void Restor_X_Servo(void)
{
	sprintf((char *)uart_buf, "#001PULR!");
	HAL_UART_Transmit(&huart1, uart_buf, 9, 10);
}

void Restor_Y_Servo(void)
{
	sprintf((char *)uart_buf, "#000PULR!");
	HAL_UART_Transmit(&huart1, uart_buf, 9, 10);
}

void Get_X_Servo_Angle(void)
{
	get_x_angle_flag = 1;
	sprintf((char *)uart_buf, "#001PRAD!");
	HAL_UART_Transmit(&huart1, uart_buf, 10, 10);
	memset(uart_buf, 0, sizeof(uart_buf));
}

void Get_Y_Servo_Angle(void)
{
	get_y_angle_flag = 1;
	sprintf((char *)uart_buf, "#000PRAD!");
	HAL_UART_Transmit(&huart1, uart_buf, 10, 10);
	memset(uart_buf, 0, sizeof(uart_buf));
}

//服务总线舵机串口，中断调用，用于获取当前转动角度
void Analysis_Rx_Data(uint8_t *rx_data)
{
//	//长度不对
//	if(sizeof(rx_data) != 10)
//	{
//		rx_state = -1;
//	}
//	//格式不对
//	if (rx_data[0] != '#' || rx_data[1] != '0' || rx_data[2] != '0' || 
//		  rx_data[4] != 'P' || rx_data[6] != '!') {
//			rx_state = -2;
//	}
	// 提取四位数字字符
	uint8_t index = 0;
	for(uint8_t i=0; i<10; i++)
	{
		if(rx_data[i] == 'P')
		{
			index = i;
			break;
		}
	}
	char num_str[4] = {0};
	memcpy(num_str, &rx_data[index + 1], 4);
	//转为数字
	uint16_t duty = atoi(num_str);
	//转为角度
	if(get_x_angle_flag)
	{
		now_x_angle = ((duty-MIN_COUNT)/(float)range)*270.f;
//		sprintf((char *)uart_buf, "now_x_angle:%.2f", now_x_angle);
//		HAL_UART_Transmit(&huart3, uart_buf, 20, 10);
	}
	if(get_y_angle_flag)
	{
		now_y_angle = ((duty-MIN_COUNT)/(float)range)*270.f;
//		sprintf((char *)uart_buf, "now_y_angle:%.2f", now_y_angle);
//		HAL_UART_Transmit(&huart3, uart_buf, 20, 10);
	}
}



