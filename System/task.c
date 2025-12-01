#include "task.h"
uint8_t finish_flag = 0;
uint8_t led_flag = 1;
uint8_t angle_control_flag = 0;
//起步动作
void Stsrt()
{
	
}

void Finish_Task()
{
	if(finish_flag)
	{

	}
}

void Task_Loop(task *choice)
{
	switch(*choice)
	{
		case QUESTION_1:
			
			break;
		case QUESTION_2:
			break;
		case QUESTION_3:
			break;
		case QUESTION_4:
			break;
		case QUESTION_5:
			break;
		default:
			break;
	}
}