#ifndef __TASK_H__
#define __TASK_H__

#include "headfile.h"
extern uint8_t led_flag;
extern uint8_t angle_control_flag;
extern uint8_t finish_flag;

typedef enum
{
	FINISH = 0,
	QUESTION_1 = 1,
	QUESTION_2 = 2,
	QUESTION_3 = 3,
	QUESTION_4 = 4,
	QUESTION_5 = 5
}task;

void Task1();
#endif
