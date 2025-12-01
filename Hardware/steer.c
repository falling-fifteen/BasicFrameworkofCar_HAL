#include "steer.h"

float now_x_angle = 0;//当前舵机角度
float now_y_angle = 0;//当前舵机角度

void Set_X_Servo_Angle(float angle)
{
    if(angle > 180)
    {
        angle = 180; // 限制角度在0到180度之间
    }

    now_x_angle = angle;


    float range = MAX_COUNT - MIN_COUNT;
    float ServoAngle = MIN_COUNT + ((angle / 180.0f) * range);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (unsigned int)(ServoAngle + 0.5f));
}

void Set_Y_Servo_Angle(float angle)
{
    if(angle > 180)
    {
        angle = 180; // 限制角度在0到180度之间
    }

    now_y_angle = angle;

    float range = MAX_COUNT - MIN_COUNT;
    float ServoAngle = MIN_COUNT + ((angle / 180.0f) * range);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (unsigned int)(ServoAngle + 0.5f));
}

float Get_X_Servo_Angle(void)
{
    return now_x_angle;
}


float Get_Y_Servo_Angle(void)
{
    return now_y_angle;
}