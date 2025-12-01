#include "pid.h"
pid_t motorL;
pid_t motorR;
pid_t angle;

//角度环角度取绝对值
float Float_Abs(float value)
{
	if (value < 0) 
	{
		return -value;
	} 
	else 
	{
		return value;
	}
}
//角度环误差计算函数
//右转时误差输出应为正，左转时误差输出应为负，-180到0到180之间任意两个角度计算都为距离最近的值：避免在-180到180之间抽搐
float Yaw_Error_Cal(float Target, float Now)
{
	static float error;
	if (Target >= 0) 
	{
		if (Now < 0) 
		{
			//左转：输出为负
			if (Float_Abs(Now) < (180 - Target)) 
			{
				error = -(Float_Abs(Now) + Target);
			}
			//右转：输出为正
			else 
			{
				error = (180 - Target) + (180 - Float_Abs(Now));
			}
		}
		//同时满足左转为负右转为正
		else 
		{
			error = Now - Target;
		}
	} 
	else 
  {
		if (Now >= 0) 
		{
			//左转：输出为负
			if (Now >= (Target + 180))
			{
				error = -((180 - Now) + (180 - Float_Abs(Target)));
			}
			//右转：输出为正
		  else
			{
				error = (Float_Abs(Target) + Now);
			}
		}
		//同时满足左转为负右转为正
		else
		{
			error = Float_Abs(Target) - Float_Abs(Now);
		}
	}
 return error;
}



//速度环PID控制
void Pid_Vertical_Cal(pid_t *pid)
{
	// 计算当前偏差
	pid->error[0] = pid->target - pid->now;

	// 计算输出
	if(pid->pid_mode == DELTA_PID)  // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];

	// 输出限幅
	if(pid->out>=MAX_DUTY)	
		pid->out=MAX_DUTY;
	if(pid->out<=MIX_DUTY)	
		pid->out=MIX_DUTY;
	
}
//角度环PID控制
void Pid_Angle_Cal(pid_t *pid)
{
	// 计算当前偏差
	pid->error[0] = Yaw_Error_Cal(pid->target, pid->now);

	// 计算输出
	if(pid->pid_mode == DELTA_PID)  // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];

	// 输出限幅
	if(pid->out>=MAX_ANGLE)	
		pid->out=MAX_ANGLE;
	if(pid->out<=MIX_ANGLE)	
		pid->out=MIX_ANGLE;
	
}




//PID初始参数设定
void Pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}
