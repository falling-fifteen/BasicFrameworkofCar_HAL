#ifndef __BUS_SERVO_H__
#define __BUS_SERVO_H__

#include "headfile.h"
/******************************************************************
   配置占空比 范围 2500~1500~500对应270~135~0
	 角度增大方向为逆时针
	 实际Y轴可调范围：2300~600即243度~13.5度(会顶到平台)
	 实际X轴可调范围：2500~500即270度~0度
******************************************************************/

#define MIN_COUNT  500
#define MAX_COUNT  2500
extern float now_x_angle;
extern float now_y_angle;
extern uint8_t get_x_angle_flag;
extern uint8_t get_y_angle_flag;
extern uint8_t toggle_power_flag;

void Set_Bus_Servo_X_Angle(float angle);
void Set_Bus_Servo_Y_Angle(float angle);
void Release_X_Servo(void);
void Release_Y_Servo(void);
void Restor_X_Servo(void);
void Restor_Y_Servo(void);
void Get_X_Servo_Angle(void);
void Get_Y_Servo_Angle(void);
void Analysis_Rx_Data(uint8_t *rx_data);
#endif
