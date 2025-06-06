/****************************************************\
作者信息：
姓名：田媚 任课教师
版权声明：
版权由北京交通大学计算机与信息技术学院高级语言程序设计教师拥有
模块名称:
LabFunctions.cpp 与LabFunctions.h配合使用
摘要:
用于教学
其它说明:
　　无
  模块历史:
  　　田媚于2010年9月25日创建本模块，email: mtian@bjtu.edu.cn
	　　田媚于2011年9月18日修改本模块，增加函数ShowWebPageInIE，email: mtian@bjtu.edu.cn
	  田媚于2012年9月17日修改本模块，增加和修改部分注释


	  原实验3第4题
	  4．	编写程序，定义一个字符型二维数组用于表示你自己的网址收藏夹，用于保存自己常用网址的URL，假定最多可以保存30条。
	        编写程序完成如下功能：
	  1)	请将学校网址、学院网址或其它任意网址保存在数组中；
	  2)	调用LabFunctions.cpp中的函数PrintStringArray，以列表方式输出自己的网址收藏夹内容，格式如下：
	  1  http://www.bjtu.edu.cn
	  2  http://computer.bjtu.edu.cn
	  3   ⋯
	  并让用户输入网址编号进行选择，调用LabFunctions.cpp中的函数ShowWebPageInIE打开对应的网址，
	  (1)请学习老师所给函数ShowWebPageInIE中将固定字符串与字符数组中的字符串拼接起来的方法，查阅资料说明函数sprintf的功能。
	  (2)查阅资料说明函数WinExec的功能，并解释为什么LabFunctions中要加#include "windows.h"

	  **********************************************************/
#include "stdafx.h"
#include "stdio.h"
#include "LabFunctions.h"
#include "windows.h" 

	  /***********************************************\
	  函数名称:
	  PrintStringArray
	  功能描述:
	  为实验3的第4道编程题所提供模块
	  输出给出已知行数和行宽的两维字符数组，每行前面加行序号，后面加换行符
	  函数参数:
	  char *pszStrs  二维数组起始地址
	  int nLines  行数
	  int nLineWidth 列数或行宽
	  返回值:
	  无
	  模块历史:
	  创建于2010.09.25, by 田媚
	  \**********************************************/

void PrintStringArray(char *pszStrs, int nLines, int nLineWidth)
{
	int i;

	for (i = 0; i < nLines; i++)
	{
		printf("\t%d\t%-s\n", i + 1, pszStrs + i * nLineWidth);
	}
	return;
}

/***********************************************\
函数名称:
ShowWebPageInIE
功能描述:
为实验3的第4道编程题所提供模块
调用IE，打开相应网站
函数参数:
char *pszWebAddress 网址
返回值:
无
模块历史:
创建于2011.09.18, by 田媚
\**********************************************/
void ShowWebPageInIE(char *pszWebAddress)
{
	char szIECommandLine[1000];  //the buffer for storing command line of IE

								 //Stuff pszWebAddress into the command line
	sprintf(szIECommandLine, "C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE %s",pszWebAddress);

	//Call WinExec to execute IE with parameter pszWebAddress
	WinExec(szIECommandLine, SW_SHOWMAXIMIZED);

	return;
}

