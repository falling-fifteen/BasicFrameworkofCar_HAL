#include "track.h"


//循迹串行获取数据
uint8_t Gray_Serial_Read()
{
	uint8_t ret = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		/* 输出时钟下降沿 */
		HAL_GPIO_WritePin(TRACK_CLK_PORT, TRACK_CLK_Pin,GPIO_PIN_RESET);
		Delay_us(2);
		//避免GPIO翻转过快导致反应不及时
		ret |= HAL_GPIO_ReadPin(TRACK_DAT_PORT, TRACK_DAT_Pin) << i;

		/* 输出时钟上升沿,让传感器更新数据*/
		HAL_GPIO_WritePin(TRACK_CLK_PORT, TRACK_CLK_Pin,GPIO_PIN_SET);
	
		/* 延迟需要在5us左右 */
		Delay_us(5);
	}
	
	return ret;
}