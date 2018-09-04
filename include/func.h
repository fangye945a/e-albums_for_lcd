#ifndef __FUNC_H_
#define __FUNC_H_

#include "common.h"

int show_jpeg(const char *,int);
int LCD_DrawPoint(int,int,int);
int show_bmp(const char *,int);//读取图片
extern int cycle_read(char filename[][MAX_name],int digit);

#endif
