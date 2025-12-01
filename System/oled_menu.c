#include "oled_menu.h"
uint8_t key1_flag;//下一项
uint8_t key2_flag;//确定
uint8_t key3_flag;//返回

//一级菜单
int menu1()
{
	uint8_t choice = 1;//记录当前选择
	OLED_ShowString(2, 0, (uint8_t *)"task1", 16);
	OLED_ShowString(2, 2, (uint8_t *)"task2", 16);
	OLED_ShowString(2, 4, (uint8_t *)"task3", 16);
	OLED_ShowString(2, 6, (uint8_t *)"task4", 16);
	while(1)
	{
		//下一项
		if(key1_flag)
		{
			if(++choice == 5)choice = 1;
			key1_flag = 0;
		}
		
		//确认
		if(key2_flag)
		{
			OLED_Clear();
			key2_flag = 0;
			return choice;
		}
		
		//返回，但在这里没有用
		if(key3_flag)
		{
			key3_flag = 0;
		}
		
		//光标移动
		switch(choice)
		{
			case 1:
				OLED_ShowString(0, 0, (uint8_t *)">", 16);
				OLED_ShowString(0, 2, (uint8_t *)" ", 16);
				OLED_ShowString(0, 4, (uint8_t *)" ", 16);
				OLED_ShowString(0, 6, (uint8_t *)" ", 16);
				break;
			case 2:
				OLED_ShowString(0, 0, (uint8_t *)" ", 16);
				OLED_ShowString(0, 2, (uint8_t *)">", 16);
				OLED_ShowString(0, 4, (uint8_t *)" ", 16);
				OLED_ShowString(0, 6, (uint8_t *)" ", 16);
				break;
			case 3:
				OLED_ShowString(0, 0, (uint8_t *)" ", 16);
				OLED_ShowString(0, 2, (uint8_t *)" ", 16);
				OLED_ShowString(0, 4, (uint8_t *)">", 16);
				OLED_ShowString(0, 6, (uint8_t *)" ", 16);
				break;
			case 4:
				OLED_ShowString(0, 0, (uint8_t *)" ", 16);
				OLED_ShowString(0, 2, (uint8_t *)" ", 16);
				OLED_ShowString(0, 4, (uint8_t *)" ", 16);
				OLED_ShowString(0, 6, (uint8_t *)">", 16);
				break;
		}
	}
}

void menu2_task1()
{
	while(1)
	{
		sprintf((char *)display_buf, "message1");
		OLED_ShowString(0, 0, display_buf, 16);
		
		sprintf((char *)display_buf, "message2");
		OLED_ShowString(0, 2, display_buf, 16);
		
		sprintf((char *)display_buf, "message3");
		OLED_ShowString(0, 4, display_buf, 16);
		
		//下一项，但在这里没有用
		if(key1_flag)
		{
			key1_flag = 0;
		}
		
		//确认，但在这里没有用
		if(key2_flag)
		{
			key2_flag = 0;
		}
		
		//返回
		if(key3_flag)
		{
			key3_flag = 0;
			OLED_Clear();
			return;
		}
	}
}

/*
下面的代码放在主循环中
uint8_t menu2_choice = 0;
menu2_choice = menu1();//跳出menu1的while才会执行下面的函数
switch(menu2_choice)
{
	case 1:
		menu2_task1();
		break;
	case 2:
		menu2_task2();
		break;
	case 3:
		menu2_task3();
		break;
	case 4:
		menu2_task4();
		break;
}
*/