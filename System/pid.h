#ifndef __PID_H__
#define __PID_H__

#include "headfile.h"
#define MAX_DUTY 100
#define MIX_DUTY 0
#define MAX_ANGLE 180
#define MIX_ANGLE -180

/*
该文件用于存放PID计算的底层函数
*/


enum
{
  POSITION_PID = 0,  // 位置式
  DELTA_PID,         // 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;


extern pid_t motorL;
extern pid_t motorR;
extern pid_t angle;
float Float_Abs(float value);
void Pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d);
void Pid_Vertical_Cal(pid_t *pid);
void Pid_Angle_Cal(pid_t *pid);
#endif
