/*********************************************************
 > File name : common.h
 > Create time : 2016-10-14 星期5 15:08
 > Author : 方烨
 > Function:    
 ********************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "jpeglib.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include<sys/mman.h>
#include<linux/input.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX_flash 6			//特效种数
#define MAX_name 40			//文件名最大长度
#define MAX 40				//最大可读取的图片数量

extern int *ptr;
#endif
