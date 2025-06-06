/****************************************************\
作者信息：
	姓名：邹琪
版权声明：
	版权由北京交通大学计算机与信息技术学院程序设计基础训练课程组所有
模块名称:
	矩阵求鞍点模块
摘要:
	教学辅助代码，配合实验1
其它说明:
	本模块实现矩阵求鞍点功能，用于训练学生理解二维数组、指向二维数组的指针。
模块历史:
　　邹琪于2018年2月26日创建本模块，email: qzou@bjtu.edu.cn
	韩升于2018年12月14日修改本模块，email：shhan@bjtu.edu.cn
	张鲡沣于2023年3月2日进行实验操作，email：22281052@bjtu.edu.cn
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//结构体声明
typedef struct node
{
	int x, y;
}anstype;

//变量声明
int matrix[1000][1000];
anstype ans[1000];
int lenx = 0, leny = -1;

//函数声明
void prepare();
void work();
void printans();

/*
*函数名称：main
*函数功能：实现矩阵鞍点求解
*输入参数：无
*返回值：无
*版本信息：create by hansheng,2018-10-28
*/
int main()
{
	prepare();
	work();
	printans();
	return 0;
}

/*
*函数名称：prepare
*函数功能：获取用户输入的矩阵
*输入参数：无
*返回值：无
*版本信息：create by hansheng,2018-10-28
*/
void prepare()
{
	//声明局部变量
	char tem;        //用于接收用户输入的矩阵数值字符
	int Intem = -1;  //存放用户输入矩阵的最大的列数

	//初始化全局变量
	lenx = 0;
	ans[0].x = 0;

	printf("输入一个矩阵：\n");

	while (1)
	{
		//开启新的一行输入时，将列标重置为0
		leny = 0;

		while (1)
		{
			//如果用户输入空格，就空循环，直到用户输入非空格的字符
			while (tem = getchar(), tem == ' ') {};

			if ((tem == '\n') || (tem == EOF))
			{
				//用户输入回车或EOF时结束对矩阵一行数据的输入
				break;
			}

			//将用户输入的字符转换为数值存入matrix数组
			matrix[lenx][leny] = tem - '0';

			//将列标指向下一列
			leny = leny + 1;
		}

		if (leny > Intem)
		{
			//将最大列号存入Intem变量
			Intem = leny;
		}

		if (tem == EOF)
		{
			//如果用户输入EOF，则退出循环
			break;
		}

		//将行标加1，开启下一行的数据输入
		lenx = lenx + 1;
	}

	//将最大行号写回leny变量，后续函数需要用到
	leny = Intem;
}

/*
*函数名称：check
*函数功能：***********************
*输入参数：int x：*********
		   int y：*********
*返回值：*************************
*版本信息：create by hansheng,2018-10-28
*/
int check(int x, int y)
{
	int i;

	for (i = 0; i < lenx; i = i + 1) {
		if (matrix[i][y] < matrix[x][y]) return 0;
	}

	return 1;
}

/*
*函数名称：remember
*函数功能：***************************
*输入参数：int x：*********
		   int y：*********
*返回值：无
*版本信息：create by hansheng,2018-10-28
*/
void remember(int x, int y)
{
	ans[0].x = ans[0].x + 1;
	ans[ans[0].x].x = x;
	ans[ans[0].x].y = y;
}

/*
*函数名称：work
*函数功能：获取矩阵的鞍点
*输入参数：无
*返回值：无
*版本信息：create by hansheng,2018-10-28
*/
void work()
{
	int i, j;
	int tem;
	int ColIndex[100] = { 0 };

	for (i = 0; i < lenx; i = i + 1)
	{
		tem = 0;
		for (j = 1; j < leny; j = j + 1)
			if (matrix[i][j] > matrix[i][tem])
				tem = j;
		for (j = 0; j < leny; j = j + 1)
		{
			if (matrix[i][j] == matrix[i][tem])
			{
				ColIndex[0] = ColIndex[0] + 1;
				ColIndex[ColIndex[0]] = j;
			}
		}
		for (j = 1; j <= ColIndex[0]; j = j + 1)
		{
			ColIndex[0] = 0;  // ColIndex[0] = ColIndex[0] -1  思想：max逐渐减少/遍历max依次减少
			if (check(i, ColIndex[j]) == 1) remember(i, ColIndex[j]);
		}
	}
}

/*
*函数名称：printans
*函数功能：将获取到的鞍点信息打印输出
*输入参数：无
*返回值：无
*版本信息：create by hansheng,2018-10-28
*/
void printans()
{
	if (ans[0].x == 0)
	{
		printf("no result found\n");
		return;
	}

	int i;

	for (i = 1; i <= ans[0].x; i = i + 1)
	{
		printf("the %dth saddle position is (%d,%d)\n", i, ans[i].x + 1, ans[i].y + 1);
	}
}
