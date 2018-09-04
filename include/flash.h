#ifndef _FLASH_H_
#define _FLASH_H_

#include "common.h"
#include <math.h>

int byc_bmp(char *);    //百叶窗特效
int byc_bmp();    //清除屏幕
int left_bmp(char *);
int dc_bmp(char *);    //淡出特效
int byc_sp_bmp(char *); 
int down_bmp(char *);
int add_color_line(int,int,int,int,int); 	//添加矩形颜色色块
int add_color_round(int,int,int,int,int); 	//添加圆形颜色色块

#endif
