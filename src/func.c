#include "find_file.h"
#include "func.h"
#include "flash.h"
/***************************************************************
********************	 显示JPG格式图 *************************
****************************************************************/
int show_jpeg(const char *filename,int flash)
{
	char tmp[800*480*3]={0};
	int k=0;
	struct jpeg_decompress_struct dinfo; //定义了一个jpeg的解压对象
	struct jpeg_error_mgr jerr; 	     //定义一个错误变量
	dinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&dinfo); //初始化这个解压对象
	
/**********************指定要解压缩的图像文件********************/
	FILE *infile;
	infile = fopen(filename,"r");
	if (infile == NULL)
	{
		perror("fopen error");
		return -1;
	}
	else
	{
		printf("Open %s success!!\n",filename);
	}
	jpeg_stdio_src(&dinfo, infile); //为解压对象dinfo指定要解压的文件

/*****************调用jpeg_read_header()获取图像信息*************/
	jpeg_read_header(&dinfo, TRUE);

/**************设置jpeg解压缩对象dinfo的一些参数，可采用默认参数****/
	jpeg_start_decompress(&dinfo); 
	unsigned char *buffer = malloc(dinfo.output_width * dinfo.output_components);
	
	while (dinfo.output_scanline < dinfo.output_height)
	{
		jpeg_read_scanlines(&dinfo, &buffer, 1); 
	//	printf("%d\n",dinfo.output_scanline);
		k=0;
		//得到一行RGB/ARGB的数据
		//deal with scanlines . RGB/ARGB
		int x; //一行的像素点数量
		char *p = buffer;
		for (x = 0; x < dinfo.output_width;x++)
		{
			unsigned char r, g, b, a = 0;
			int color;
			if (dinfo.output_components == 3)
			{
				r = *p++;
				g = *p++;
				b = *p++;	
			} 
			else if (dinfo.output_components == 4)
			{
				a = *p++;
				r = *p++;
				g = *p++;
				b = *p++;	
			}
			tmp[(480-dinfo.output_scanline)*800*3+(k++)]=b; 
			tmp[(480-dinfo.output_scanline)*800*3+(k++)]=g; 
			tmp[(480-dinfo.output_scanline)*800*3+(k++)]=r; 
			if(k > 800*3)
			{
				printf("The Jpg size is not 800*480!!\n");
				return -1;
			}
//	    color = (a << 24) | (r << 16) | (g << 8) |(b) ;
		}
	}
	fclose(infile);//关闭文件
	free(buffer);//释放内存

	switch(flash)
	{
		case 0:
				down_bmp(tmp);	//幕布 从下往上
				break;
		case 1:
				left_bmp(tmp);	//幕布 从下往上
				break;
		case 2:
				byc_bmp(tmp);//百叶窗垂直
				break;
		case 3:
				byc_sp_bmp(tmp);//百叶窗水平
				break;
		case 4:
				dc_bmp(tmp);//百叶窗水平
				break;
		case 5:
				inside_out_bmp(tmp);// 从里到外
				break;
		default: break;
	}
	return 0;
}
/*********************************************************************
********************* 		画点显示jpeg图片    **********************
**********************************************************************/
int LCD_DrawPoint(int x,int y,int color)
{
			ptr[x+800*y]=color;
			return 0;
}

/***************************************************************
********************	 显示图片	   *************************
****************************************************************/
int show_bmp(const char *path,int flash) //读取图片
{
	int x=0,y=0,i=0,j=0;
	int ret =0,fd_bmp;
	char tmp[3*800*480]={0};
	ret=jpeg_or_bmp(path);
	if(2 == ret)
	{
		show_jpeg(path,flash);
		return 0;
	}
	else if(0 == ret)
	{
		return -1;
	}
	else
	{
		fd_bmp =open(path,O_RDONLY); //打开bmp图片文件
		if(fd_bmp == -1)
		{
			printf("Open %s fail!\n",path);
			return 0;
   		}
		else
			printf("Open %s success!!\n",path);
		ret = lseek(fd_bmp,54,SEEK_SET); //将偏移指针偏到图片内容区
		if(ret == -1)
		{
			printf("offset fail!\n");
		}
		ret = read(fd_bmp,tmp,800*480*3);//读取图片文件内容
		if(ret < 0)
		{
			printf("read error!\n");
			return 0;
		}
		else
			printf("read %d word!\n",ret);
		switch(flash)
		{
			case 0:
					down_bmp(tmp);	//幕布 从下往上
					break;
			case 1:
					left_bmp(tmp);	//幕布 从下往上
					break;
			case 2:
					byc_bmp(tmp);//百叶窗垂直
					break;
			case 3:
					byc_sp_bmp(tmp);//百叶窗水平
					break;
			case 4:
					dc_bmp(tmp);//百叶窗水平
					break;
			case 5:
					inside_out_bmp(tmp);// 从里到外
					break;
			default: break;
		}
		close(fd_bmp);	//关闭图片文件
	}
	return 0;
}

/*****************************************************************************************
**********************************    循环读取图片       *********************************
******************************************************************************************/
int cycle_read(char filename[][MAX_name],int digit)
{
	char flag=0;
	int flash=0;
	int ret,count=0;
	int count_flag=0;
	int x=0,y=0;
	int	cycle_flag=0;	
	int x_start=0,y_start=0,x_end=0,y_end=0,color=0,shape=0; 	//添加颜色色块

	while(1)			//循环读取图片
	{
		ret = show_bmp(filename[count],flash);
		if(-1 == ret)
		{
			printf("Show_bmp fail!!\n");
			return -1;
		}
loop:	printf("please input the shell:\n");
		scanf("%c",&flag);	//输入指令
		while('\n'!= getchar()); //吸收过多的字符及回车
		switch(flag)
		{
			case 'n':	
						count++;		//查看下一张	
						flash++;		//使用下一个特效
						if(count > digit-1)//到最后一张则跳到第一张
							count=0;
						if(flash>MAX_flash-1)
							flash=0;
						break;
			case 'N':	
						count--;		//查看上一张
						flash--;		//使用下一个特效
						if(count <0)	//到第一张则跳到最后一张
							count=digit-1;
						if(flash <0)
							flash=MAX_flash-1;
						break;

			case 'q':	// 退出循环读取图片
						return 0;

			case 'i':
						printf("Please input the pos:x_Start y_Start x_End y_End color shape\n");
						scanf("%d %d %d %d %d %d",&x_start,&y_start,&x_end,&y_end,&color,&shape);
						while('\n'!= getchar());			//吸收回车
						if(shape == 0)	//矩形
							ret = add_color_line(x_start,y_start,x_end,y_end,color);
						else if(shape == 1) //圆形
							ret = add_color_round(x_start,y_start,x_end,y_end,color);
						if(-1 == ret)
						{
							printf("please try input again!\n");
							goto loop;
						}
						else
						{
							printf("write success!\n");
							goto loop;
						}
						break;
			case 't':
				loop1:	get_X_Y(&x,&y);
						printf("x=%d,y=%d\n",x,y);
						if(x<250)
						{
							count--;		//查看上一张
							flash++;		//切换特效
							if(count <0)	//到第一张则跳到最后一张
								count=digit-1;
							if(flash > MAX_flash-1)
								flash=0;
							ret = show_bmp(filename[count],flash);
							goto loop1;
						}
						else if(x>550)
						{
							count++;		//查看下一张	
							flash++;		//切换特效	
							if(count >digit-1)//到最后一张则跳到第一张
								count=0;
							if(flash > MAX_flash-1)
								flash=0;
							ret = show_bmp(filename[count],flash);
							goto loop1;
						}
						else
							goto loop;
						break;
			case 'd':
						clean_bmp();
				loop2:	printf("Please input the shape and color:\n");
						scanf("%d %d",&shape,&color);
						while('\n'!= getchar());			//吸收回车
						two_X_Y(&x_start,&y_start,&x_end,&y_end);
						if(x_start >= x_end)  //比较大小   交换两个数的值
						{
							x_start = x_start + x_end;
							x_end   = x_start - x_end;
							x_start = x_start - x_end;
						}
						if(y_start >= y_end)  //比较大小   交换两个数的值
						{
							y_start = y_start + y_end;
							y_end   = y_start - y_end;
							y_start = y_start - y_end;
						}
						if(shape == 0)
							ret = add_color_line(x_start,y_start,x_end,y_end,color);
						else if(shape ==1)
							ret = add_color_round(x_start,y_start,x_end,y_end,color);
						else
						{
							printf("The shape input inllegal!\n");
							goto loop;
						}
						if(-1 == ret)
						{
							printf("please try input again!\n");
							goto loop;
						}
						else
						{
							printf("write success!\n");
							goto loop2;
						}
						break;
			case 'p':
						count_flag=count;   //进入时张数标志赋值
				loop3:	count++;			//查看下一张	
						flash++;			//使用下一个特效
						if(count > digit-1) //到最后一张则跳到第一张
							count=0;
						if(flash > MAX_flash-1)
							flash=0;
						ret = show_bmp(filename[count],flash);
						sleep(2);
						if(count != count_flag) //若循环完一轮则结束，回到等待命令模式
							goto loop3;
						else
							goto loop;
						break;
			default: 
						printf("Error input! please try input again!\n");
						goto loop;
		}
	}
}
