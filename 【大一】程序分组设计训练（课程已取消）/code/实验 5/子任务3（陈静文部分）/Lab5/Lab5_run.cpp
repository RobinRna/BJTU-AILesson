#define _CRT_SECURE_NO_WARNINGS 1
#include"Lab5_head.h"
#include"Lab5_fun.h"
/*exe1�����·����1��exe2�����·����2������ļ�txt����3���棬html����4����*/
/*************************************************************
��������:
run
��������:
ʵ��������Ŀ���ܹ���
��������:
��
����ֵ:
��
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
			printf("�����ĵ�ͳ��ʱ��Ϊ%lf��\n", TheTimes);
		}
		else if (functionnumber == 2)
		{
			clock_t start, finish;
			double TheTimes;
			start = clock();
			fun2(argc, argv);
			finish = clock();
			TheTimes = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("�����ĵ�ͳ��ʱ��Ϊ%lf��\n", TheTimes);
		}
		else if (functionnumber == 0)
		{
			printf("ʵ���������ֹ\n");
			exit(1);
		}
		else
		{
			printf("�������Ҫִ�еĳ�����������⣬����������һ���������\n");
		}
	}
}