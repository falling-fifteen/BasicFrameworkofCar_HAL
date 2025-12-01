#include "encoder.h"

int32_t speed_left = 0;	
int32_t speed_right = 0;
//当每10ms读取编码器脉冲数时
//正转占空比50%约为80，占空比100%约为160
int32_t Read_Speed(TIM_HandleTypeDef *htim)
{
	int32_t temp;
	temp = (short)__HAL_TIM_GetCounter(htim);
	__HAL_TIM_SetCounter(htim, 0);
	return temp;
}
