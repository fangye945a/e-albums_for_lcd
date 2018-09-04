/*********************************************************
 > File name : main.c
 > Create time : 2016-10-11 星期2 11:34
 > Author : 方烨
 > Function:  电子相册
 ********************************************************/
#include<stdio.h>
#include "func.h"
#include "lcd.h"
#include "common.h"
#include "find_file.h"
#include "flash.h"


int *ptr;
/*****************************************************************************************
*************************************    主函数       ************************************
******************************************************************************************/
int main(int argc,char *argv[])
{
	char filename[MAX][MAX_name];//图片文件名
	int fd,ret;
	int count=0;

	fd = Lcd_init();	//液晶初始化

	printf("fd=%d\n",fd);

	count = read_picture(".",filename);//读入图片名称和数量

	ret = cycle_read(filename,count); //循环读取文件	
	if(ret == -1)
		printf("cycle read fail!\n");

	end_lcd(fd);//结束显示

	return 0;
}
