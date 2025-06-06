/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	实验5 主入口函数
摘要:
	作业，配合实验5
其它说明:
	无。
模块历史:
　　张鲡沣于2023年5月30日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_main.h"

/*
 *函数名称：run
 *函数功能：实验5函数大体框架
 *输入参数：int argc：命令行参数个数、char* argv[]:命令行参数值
 *返回值：int(无实际含义)
 *版本信息：create by Lifeng Zhang, 2023-05-30
 */
int run(int argc, char* argv[])
{
	htmldata* data = (htmldata*)malloc(sizeof(htmldata));

	if (argc == 1)
	{
		int count = 1;
		get_filename(data, count); // 输入：输入txt路径
		count++;
		get_filename(data, count); // 输入：输出html路径

		printf("请输入：工作模式（0为自动模式、1为静默模式）\n");
		check_num(data);
	}

	if (argc == 2)
	{
		printf("（若报错，则输出错误，请依次输入 <输入txt路径> <输出html路径> <模式> ）\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<输入txt路径> 输入错误\n");
			get_filename(data, count); // 输入：输入txt路径
		}

		char disk[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(data->input_file, disk, dir, fname, ext);
		strcat(fname, "1");
		_makepath(data->input_file, disk, dir, fname, ext);

		count++;
		get_filename(data, count); // 输入：输出html路径

		printf("请输入：工作模式（0为自动模式、1为静默模式）\n");
		check_num(data);
	}

	if (argc == 3)
	{
		printf("（若报错，则输出错误，请依次输入 <输入txt路径> <输出html路径> <模式> ）\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);
		strcpy(data->output_file, argv[2]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<输入txt路径> 输入错误\n");
			get_filename(data, count); // 输入：输入txt路径
		}

		char disk[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(data->input_file, disk, dir, fname, ext);
		strcat(fname, "1");
		_makepath(data->input_file, disk, dir, fname, ext);

		count++;
		if (check_seper_file(data->output_file, count) == 0)
		{
			printf("<输出html路径> 输入错误\n");
			get_filename(data, count); // 输入：输出html路径
		}

		printf("请输入：工作模式（0为自动模式、1为静默模式）\n");
		check_num(data);
	}

	if (argc == 4)
	{
		printf("（若报错，则输出错误，请依次输入 <输入txt路径> <输出html路径> <模式> ）\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);
		strcpy(data->output_file, argv[2]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<输入txt路径> 输入错误\n");
			get_filename(data, count); // 输入：输入txt路径
		}

		char disk[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(data->input_file, disk, dir, fname, ext);
		strcat(fname, "1");
		_makepath(data->input_file, disk, dir, fname, ext);

		count++;
		if (check_seper_file(data->output_file, count) == 0)
		{
			printf("<输出html路径> 输入错误\n");
			get_filename(data, count); // 输入：输出html路径
		}

		data->mode = atoi(argv[3]);
		check_num(data);
	}

	if (argc > 4)
	{
		printf("输入参数过多，程序终止。\n");
		exit(0);
	}

	loadfile(data, 1); // 载入子任务1程序、加载页面与读入文件
}