#include "motor.h"
//1为正转 -1为反转
int8_t motorL_dir = 1;
int8_t motorR_dir = 1;
// 绝对值函数
int myabs(int a)
{
    return (a >= 0) ? a : -a;
}
// 速度限制函数
void Limit(int *motor_speed)
{
    if (*motor_speed > PWM_MAX)
        *motor_speed = PWM_MAX;
    if (*motor_speed < PWM_MIN)
        *motor_speed = PWM_MIN;
}

//整体赋值
void Set_Speed(int motor_l, int motor_r)
{
    // 限制速度范围
    Limit(&motor_l);
		Limit(&motor_r);
    // 左电机控制 (PB11, PB12)
    if (motor_l >= 0)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN2_PIN, GPIO_PIN_SET);   
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_L_PWM_CHANNEL, motor_l);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN1_PIN, GPIO_PIN_SET);   
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_L_PWM_CHANNEL, myabs(motor_l));
    }

    // 右电机控制 (PB2, PB10)
    if (motor_r >= 0)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN1_PIN, GPIO_PIN_RESET); 
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN2_PIN, GPIO_PIN_SET);  
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_R_PWM_CHANNEL, motor_r);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN1_PIN, GPIO_PIN_SET);  
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_R_PWM_CHANNEL, myabs(motor_r));
    }
}

//单独赋值
void Set_MotorL_Speed(int motor_l)
{
		Limit(&motor_l);
    // 左电机控制
    if (motor_l >= 0)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN2_PIN, GPIO_PIN_SET);   
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_L_PWM_CHANNEL, motor_l);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN1_PIN, GPIO_PIN_SET);   
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_L_IN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_L_PWM_CHANNEL, myabs(motor_l));
    }
}

void Set_MotorR_Speed(int motor_r)
{
		Limit(&motor_r);
    // 右电机控制
    if (motor_r >= 0)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN1_PIN, GPIO_PIN_RESET); 
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN2_PIN, GPIO_PIN_SET);  
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_R_PWM_CHANNEL, motor_r);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN1_PIN, GPIO_PIN_SET);  
        HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_R_IN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_R_PWM_CHANNEL, myabs(motor_r));
    }
}