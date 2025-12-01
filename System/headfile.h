#ifndef __HEADFILE_H__
#define __HEADFILE_H__
/*
当前方案:如下设计后，正转一切数据为正，反转则为负
TIM3CH1(PA6):左侧电机编码器B3
TIM3CH2(PA7):左侧电机编码器A3
TIM4CH1(PB6):右侧电机编码器A4
TIM4CH2(PB7):右侧电机编码器B4
TIM2CH2(PA1):左侧电机PWM
TIM2CH3(PA2):右侧电机PWM
这里的AIN、BIN是tb6612上的，非扩展排针上的
PB12(AIN1)、PB4(AIN2)：左侧电机转向
PB5(BIN2)、PB1(BIN1)：右侧电机转向
PA10:串口RX、总线舵机RX
PA9：串口TX、总线舵机TX
PA3: Key1:偏航角-0.5
PA0：Key2：偏航角+0.5
PA4：任务开始与暂停按钮
PC14：循迹时钟线
PC15：循迹数据线
PB10：JY61P串口TX
PB11：JY61P串口RX
*/


#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "delay.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "oled_menu.h"
#include "oled.h"

#include "track.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "pid_control.h"
#include "pid_upper_computer.h"
#include "jy61p.h"

#include "task.h" 
#include "bus_servo.h"
extern unsigned char display_buf[20];
extern int8_t target_speed;
extern uint8_t gray_data;
extern float yaw_target;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;

#endif
