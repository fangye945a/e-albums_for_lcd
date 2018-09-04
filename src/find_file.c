#include "find_file.h"	
/******************************************************************
*******************   判断是jpeg图片还是bmp图片********************
*******************************************************************/
int jpeg_or_bmp(const char *filename)
{
	char str1[]=".bmp";
	char str2[]=".jpg";
	const char *p;
	p = filename;
	while(*(++p) != '.')
	{
		if(*p=='\0')
		{
			p--;
			break;
		}
	}
	if(!strcmp(p,str1))
	{
		return 1;
	}
	else if(!strcmp(p,str2))
	{
		return 2;
	}
	return 0;
}
/******************************************************************
********************* 	查找目录下的图片文件***********************
*******************************************************************/
int read_picture(char *path ,char filename[][MAX_name])
{
	char* p;
	char str1[]=".bmp";
	char str2[]=".jpg";
	int i,count=0;
	DIR *dp;
	struct dirent *st;
	dp = opendir(path);
	if(NULL == dp)
	{
		printf("open fail!!\n");
		return 0;
	}
	while(1)
	{
		st = readdir(dp);
		if (NULL == st)
			break;
		p = st->d_name;
		while(*(++p) != '.')
		{
			if(*p=='\0')
			{
				p--;
				break;
			}
		}
		if(!strcmp(p,str1))
		{
			strcpy(filename[count++],st->d_name);
			printf("%s\n",filename[count-1]);
		}
		else if(!strcmp(p,str2))
		{
			strcpy(filename[count++],st->d_name);
			printf("%s\n",filename[count-1]);
		}
	}
	printf("There are %d pictures!\n",count);
	closedir(dp);
	return count;
}
