#ifndef __TRACK_H__
#define __TRACK_H__


#include "headfile.h"


#define TRACK_CLK_PORT  GPIOC
#define TRACK_CLK_Pin		GPIO_PIN_14
#define TRACK_DAT_PORT  GPIOC
#define TRACK_DAT_Pin		GPIO_PIN_15


uint8_t Gray_Serial_Read();
#endif
