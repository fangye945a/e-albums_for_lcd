#include "lcd.h"
/******************************************************************
********************* 		液晶屏初始化		*******************
*******************************************************************/
int Lcd_init()
{
	int fd;
	fd = open("/dev/fb0",O_RDWR);	//打开图片读取设备
	if(fd == -1)
	{
		printf("Lcd init fail!\n");
		return -1;
   	}
	ptr = mmap(NULL,480*800*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(NULL == ptr)
	{
		printf("mmap fail!!\n");
		return -1;
	}
	return fd;
}
/*********************************************************************
********************* 		触摸屏初始化        **********************
**********************************************************************/
int touch_init()
{
	int fd;
	fd = open("/dev/event0",O_RDWR);	//打开触摸屏设备
	if(fd < 0)
	{
		printf("touch_init fail!\n");
		return -1;
   	}
	return fd;
}
/********************************************************************
**********************	  获得坐标值	  ***************************
*********************************************************************/
int get_X_Y(int *x,int *y)
{
	int fd;
	struct input_event buffer;
	int ret;
	fd=touch_init();	//触摸初始化
	printf("Please touch the LCD\n");
	while(1)
	{
		ret = read(fd,&buffer,sizeof(buffer));
		if(ret < 0)
		{
			printf("read fail!\n");
			close(fd);
			return -1;
		}

		printf("type=%d code=%d value=%d\n",buffer.type,buffer.code,buffer.value);
		
		if(buffer.type == EV_ABS)   //读取坐标值
		{
			if(buffer.code == ABS_X) //X坐标
			{
				*x=buffer.value;
			}
			else if(buffer.code == ABS_Y)	//y坐标
			{
				*y=479-buffer.value;
			}
			else if(buffer.code == ABS_PRESSURE && buffer.value == 0) //检测是否松手
			{
				ret = read(fd,&buffer,sizeof(buffer));
				if(ret < 0)
				{
					printf("read fail!\n");
					close(fd);
					return -1;
				}
				if(buffer.type ==0 && buffer.code==0 && buffer.value==0)//判断事件结束符
					break;
			}
		}
	}
	close(fd);	//关闭屏幕触摸文件
	return 0;
}
/********************************************************************
**********************	 获得滑动时首末坐标值	**********************
*********************************************************************/
int two_X_Y(int *x,int *y,int *x1,int *y1)
{
	int fd;
	struct input_event buffer;
	int ret,flag_x=0,flag_y=0;
	fd=touch_init();	//触摸初始化
	printf("Please touch the LCD\n");
	while(1)
	{
		ret = read(fd,&buffer,sizeof(buffer));
		if(ret < 0)
		{
			printf("read fail!\n");
			close(fd);
			return -1;
		}

		printf("type=%d code=%d value=%d\n",buffer.type,buffer.code,buffer.value);
		
		if(buffer.type == EV_ABS)   //读取坐标值
		{
			if(buffer.code == ABS_X) //X坐标
			{
				if(0 == flag_x)
				{
					*x=buffer.value;
					flag_x++;
				}
				else
				{
					*x1=buffer.value;
				}
			}
			else if(buffer.code == ABS_Y)	//y坐标
			{
				
				if(0 == flag_y)
				{
					*y=479-buffer.value;
					flag_y++;
				}
				else
				{
					*y1=479-buffer.value;
				}
			}
			else if(buffer.code == ABS_PRESSURE && buffer.value == 0) //检测是否松手
			{
				ret = read(fd,&buffer,sizeof(buffer));
				if(ret < 0)
				{
					printf("read fail!\n");
					close(fd);
					return -1;
				}
				if(buffer.type ==0 && buffer.code==0 && buffer.value==0)//判断事件结束符
				{
					if(0 == *x1 && 0 == *y1) //没有滑动 
						return -1;
					else
						break;
				}
			}
		}
	}
	close(fd);	//关闭屏幕触摸文件
	return 0;
}


/*****************************************************************************************
**********************************     结束显示     **************************************
******************************************************************************************/
int end_lcd(int fd)
{
	munmap(ptr,480*800*4);			//释放映射
	close(fd);					//关闭屏幕显示文件
	return 0;
}
