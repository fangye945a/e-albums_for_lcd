#ifndef __LCD_H__
#define __LCD_H__

#include "common.h"

extern int Lcd_init();				//液晶屏初始化
extern int touch_init();	//触摸屏初始化 
extern int get_X_Y(int *,int *);	//获得坐标值
extern int two_X_Y(int *,int *,int *,int *);	//获初末坐标值
extern int end_lcd(int); 		//结束显示 

#endif
