#include "pid_control.h"
//PID执行函数
void Pid_Control()
{
	/********************角度环***********************/
	//设置目标角度:右转为负，左转为正
	angle.target = yaw_target;
	//设置当前角度
	angle.now = Yaw;
	//经过PID控制
	Pid_Angle_Cal(&angle);
	//输出电机目标速度：右转左轮正速度、右轮负速度；左转相反(但为确保传入参数均为正数，这里提取方向保留数据)
	if(angle.out > 0)
	{
		motorL_dir = 1;
		motorR_dir = -1;
		motorL.target = angle.out;
		motorR.target = angle.out;
	}
	else
	{
		motorL_dir = -1;
		motorR_dir = 1;
		motorL.target = -angle.out;
		motorR.target = -angle.out;
	}
	/********************速度环***********************/
	//设置目标速度：上方角度环已设置，下方注释代码为调试代码
//	if(target_speed >= 0)
//	{
//		motorL_dir = 1;
//		motorR_dir = -1;
//		motorL.target = target_speed;
//		motorR.target = target_speed;
//	}
//	else
//	{
//		motorL_dir = -1;
//		motorR_dir = 1;
//		motorL.target = -target_speed;
//		motorR.target = -target_speed;
//	}
	//获取当前速度(但为确保传入参数均为正数，这里根据方向取数据绝对值)
	motorL.now = abs(speed_left);
	motorR.now = abs(speed_right);
	//经过PID控制
	Pid_Vertical_Cal(&motorL);
	Pid_Vertical_Cal(&motorR);
	//输出电机占空比
	Set_MotorL_Speed((int)motorL_dir*motorL.out);
	Set_MotorR_Speed((int)motorR_dir*motorR.out);
}