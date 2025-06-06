#define _CRT_SECURE_NO_WARNINGS 1
#include"Lab5_head.h"
#include"Lab5_fun.h"
/*exe1的相对路径是1，exe2的相对路径是2，结果文件txt放在3里面，html放在4里面*/
/*************************************************************
函数名称:
run
功能描述:
实现整个项目的总功能
函数参数:
无
返回值:
无
*********************************/
void run(int argc, char* argv[])
{
	int functionnumber;

	while (1)
	{
		menu();
		scanf("%d", &functionnumber);
		if (functionnumber == 1)
		{
			clock_t start, finish;
			double TheTimes;

			start = clock();
			fun1(argc,argv);
			finish = clock();
			TheTimes = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("本次文档统计时间为%lf秒\n", TheTimes);
		}
		else if (functionnumber == 2)
		{
			clock_t start, finish;
			double TheTimes;
			start = clock();
			fun2(argc, argv);
			finish = clock();
			TheTimes = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("本次文档统计时间为%lf秒\n", TheTimes);
		}
		else if (functionnumber == 0)
		{
			printf("实验五程序终止\n");
			exit(1);
		}
		else
		{
			printf("你输入的要执行的程序序号有问题，请重新输入一个程序序号\n");
		}
	}
}