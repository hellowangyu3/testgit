/******* exit() Vs _exit() *****************************************************
 * 函数名1：void _exit(int status);
 * 函数名2：void exit(int status);
 * 功能：终止一个进程，并且返回一个值给系统
 * 参数：
 *      status：要返回的值，只有低八位有效
 * 
 * 区别：
 *  1.exit()结束当前进程，并且返回一个低八位值，-----"会"刷新缓存区数据-----，在调用sysexit()退出进程
 *  2._exit()结束当前进程，并且返回一个低八位值，-----"不会"刷新缓存区数据-----，直接调用sysexit()退出进程
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    //stdout(1)输出流，是一个行缓冲
    printf("你好，世界，我是行缓冲的数据集");
    
#if 0   //exit()
    exit(0);     //1.exit()结束当前进程，并且返回一个低八位值，"会"刷新缓存区数据，在调用sysexit()退出进程

#else   //_exit()
    _exit(0);   //2._exit()结束当前进程，并且返回一个低八位值，"不会"刷新缓存区数据，直接调用sysexit()退出进程

#endif

    printf("结束操作，此行不会打印，因为进程已经结束，我的程序还未运行到这儿!\n");
    return 0;
}



