/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	实验4 主入口函数
摘要:
	作业，配合实验4。部分引用Lab3实验程序。
其它说明:
	无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_checkfile.h"

/*
 *函数名称：get_filename
 *函数功能：通过交互界面获取文件储存路径
 *输入参数：htmldata* data 文件参数
 *          count 命令行参数得到参数个数
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-04（Lab3中程序）
 *          repair by Lifeng Zhang, 2023-05-30
 */

void get_filename(htmldata* data, int count)
{
	char user_filename[MAX_STR_LEN];

	if (count == 1)
	{
		printf("\n请输入：输入txt路径（可带有绝对路径或相对路径，输入no表示使用配置默认文件名）:\n");
		scanf("%s", data->input_file);
		strcpy(user_filename, data->input_file);
	}
	else
	{
		printf("\n请输入：输出html路径（可带有绝对路径或相对路径，输入no表示使用配置默认文件名）:\n");
		scanf("%s", data->output_file);
		strcpy(user_filename, data->output_file);
	}
	clearstdin();

	// 判断用户是否输入合法
	while (check_seper_file(user_filename, count) == 0)
	{
		printf("Illegal path or file name!!  输入路径或文件名非法!!:\n");
		printf("Please Re-enter!  请重新输入:\n");
		scanf("%s", user_filename);
		clearstdin();
	}

	if (count == 1)
		strcpy(data->input_file, user_filename);
	else
		strcpy(data->output_file, user_filename);
}

/*
 *函数名称：check_seper_file
 *函数功能：对str数据是否合法（为正确文件名）进行检查
 *          判断路径为相对路径还是绝对路径，切割路径与文件名
 *输入参数：char* str:文件路径与文件名
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-01（Lab3中程序）
 *          repair by Lifeng Zhang, 2023-05-30
 */
int check_seper_file(char* str, int count)
{
	int len = strlen(str);
	//_MAX_DRIVE、_MAX_DIR、_MAX_FNAME、_MAX_EXT 在配置中已有定义
	//_MAX_DRIVE==3，_MAX_DIR==_MAX_FNAME==_MAX_EXT==256
	char disk[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char way[MAX_STR_LEN];

	// void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
	// 第一个是待处理的完整的文件名路径
	// 四个参数分别代表四个需要从原始文件路径中截取的字符串，有驱动器盘符(drive)，中间的路径（dir），文件名(fname)，和后缀名（ext）
	_splitpath(str, disk, dir, fname, ext);

	// 实验要求文件以.txt或者.html结尾
	if (count == 1)
		if (strcmp(ext, ".txt") != 0)
			return 0;

	if (count == 2)
		if (strcmp(ext, ".html") != 0)
			return 0;

	if (*str == '\\') // 不能以"\\"开头
		return 0;

	// 不能以"\\"或"/"结尾，若以此结尾则认为文件名为空
	char* index1 = strrchr(str, '\\');
	char* index2 = strrchr(str, '/');
	if (index1 - str + 1 == strlen(str) || index2 - str + 1 == strlen(str))
		return 0;

	// 进行合并，以便后续处理
	char* index;
	if (index2 > index1)
		index = index2;
	else
		index = index1;

	// 判断输入路径为绝对路径还是相对路径
	char* p1 = strstr(str, ":\\");
	char* p2 = strstr(str, ":/");

	if (p1 || p2) // 输入的是绝对路径
	{

		_splitpath(str, disk, dir, fname, ext);

		// 判断disk在电脑中是否存在
		if (access(disk, 0) != 0)
		{
			printf("%s is no exist! disk在电脑中不存在 \n", disk);
			return 0;
		}

		// 判断路径中是否有非法字符
		if (strstr(dir, "*") || strstr(dir, "?") || strstr(dir, "<") || strstr(dir, ">") || strstr(dir, "|") || strstr(dir, ":"))
			return 0;
		if (strstr(fname, "*") || strstr(fname, "?") || strstr(fname, "<") || strstr(fname, ">") || strstr(fname, "|") || strstr(dir, ":"))
			return 0;

		_makepath(way, disk, dir, NULL, NULL);
		if (access(way, 0) == -1) // 路径不存在，创建新路径
			_mkdir(way);
	}

	else if (p1 == NULL || p2 == NULL) // 仅仅是文件名
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(str, ":"))
			return 0;
	}

	else // 相对路径
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(dir, ":"))
			return 0;

		// 储存路径、文件名
		_makepath(way, disk, dir, NULL, NULL);
		_chdir(dir);
	}
	return 1;
}

/*
 *函数名称：clearstdin
 *函数功能：对scanf输入进行缓存清除
 *输入参数：无
 *返回值：int(本程序无实际意义)
 *版本信息：create by Lifeng Zhang, 2022-03-17（Lab3中程序）
 */
int clearstdin()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	return 0;
}

/*
 *函数名称：check_num
 *函数功能：对输入数据数据是否合法（为纯数字）进行检查
 *输入参数：htmldata* data 文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-30
 *          repair by Lifeng Zhang, 2023-05-30
 */
void check_num(htmldata* data)
{
	int check = 1;
	if (data->mode == 1 || data->mode == 0)
		check = 0;
	while (check)
	{
		scanf("%d", &data->mode);
		if (data->mode == 1 || data->mode == 0)
			check = 0;
		else
			printf("输入有误，请重新输入！\n请输入：工作模式（0为自动模式、1为静默模式）\n");
	}
}