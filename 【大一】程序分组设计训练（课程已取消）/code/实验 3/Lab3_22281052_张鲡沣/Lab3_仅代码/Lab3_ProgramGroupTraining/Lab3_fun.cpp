/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	实验3 封装函数集合区
摘要:
	作业，配合实验3
其它说明:
	无。
模块历史:
　　张鲡沣于2023年4月1日创建本模块，email: 22281052@bjtu.edu.cn
	张鲡沣于2023年4月4日修改本模块，email: 22281052@bjtu.edu.cn
	张鲡沣于2023年4月11日修改本模块，email: 22281052@bjtu.edu.cn
	张鲡沣于2023年4月17日修改本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab3_fun.h"

/*
 *函数名称：ini_read
 *函数功能：前期配饰文件
 *输入参数：CONF* data:结构体指针data
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-03-17
 */
void ini_read(CONF* data)
{
	FILE* fp = fopen("D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_3_Experiments/Lab3_ProgramGroupTraining/set/conf.ini", "r"); // 将文件地址打开，读取内容
	if (fp)
	{
		// 将对应行的内容读入结构体
		fscanf(fp, "%s%s%d%d%d%d%d%d%d",
			data->filesavepath,
			data->filename,
			&data->number,
			&data->maxvalue1,
			&data->minvalue1,
			&data->maxvalue2,
			&data->minvalue2,
			&data->recordcount1,
			&data->recordcount2);
		fclose(fp); // 关闭文件
		fflush(fp); // 清缓存，防止爆栈
	}
	else
	{
		printf("未能打开打开文件conf.ini,系统自动配置相关文件\n");
		// 程序给出默认值进行配置
		strcpy(data->filesavepath, "output/");
		strcpy(data->filename, "Default.txt");
		data->number = 5;
		data->maxvalue1 = 20;
		data->minvalue1 = 1;
		data->maxvalue2 = 100;
		data->minvalue2 = 1;
		data->recordcount1 = 200;
		data->recordcount2 = 50;
	}
}

/*
 *函数名称：create_1
 *函数功能：用户未输入数据情况、创建文件
 *输入参数：FILE*fp:文件指针、int* num:argv[1]文件条数、char* argv[]:命令行参数值
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-03-17
 */
void create_1(FILE* fp, int* num, char* argv[], CONF* data)
{
	get_filenum(data); // 获取文件数目

	char crea[4];
	printf("Whether to enter the file path yourself?  Please input yes / no.\n");
	printf("是否自行输入文件路径？  请输入yes/no.\n");
	scanf("%s", crea);
	clearstdin();

	if (strcmp(crea, "no") == 0) // 不自行输入
	{
		printf("Use Configuration Files.  使用配置文件。\n");
		_mkdir("output/");
		strcpy(user_filename, "../Default.txt");
	}

	else
		get_filename(data); // 获取文件名

	// 创建文档
	if ((fp = fopen(user_filename, "w+")) == NULL)
		printf("Error on open filet    未成功创建文件\n"); // 如果没有成功创建文档，进行报错提示
	else
	{
		*num = data->number;
		writenum(fp, data, user_filename);
	}
}

/*
 *函数名称：create_2
 *函数功能：用户已输入数据情况、创建文件
 *输入参数：FILE*fp:文件指针、int* num:文件条数、char* argv[]:命令行参数值、CONF data:结构体数组地址
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */
void create_2(FILE* fp, int* num, char* argv[], CONF* data)
{
	char* name_file = NULL; // 初始化定义，以便后续判断
	get_filenum(data);		// 获取文件数目

	if (check_num(data, argv[1]) == 0) // 检查用户输入参数
	{
		// 输入参数是路径，检查数据
		
		if (check_seper_file(argv[1], data) == 0)
		{
			printf("Illegal Command Line Arguments!  命令行参数非法！\n");
			printf("Program ending!  程序结束！\n");
		}
		else
		{
			strcpy(user_filename, argv[1]);
			name_file = argv[1];
		}
	}
	else // 输入参数是数目，检查文件名
	{
		get_filename(data); // 获取文件名
		name_file = user_filename;
	}
	if (name_file == NULL)
		;
	else // 用户输入正确
	{
		// 创建文档
		if ((fp = fopen(name_file, "w")) == NULL)
			printf("Error on open filet    未成功创建文件\n"); // 如果没有成功创建文档，进行报错提示
		else
		{
			*num = data->number;
			writenum(fp, data, user_filename);
		}
	}
}

/*
 *函数名称：create_3
 *函数功能：用户已输入数据情况、创建文件
 *输入参数：FILE*fp:文件指针、int* num:文件条数、char* argv[]:命令行参数值、CONF data:结构体数组地址
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-04-01
 *          repair by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */
void create_3(FILE* fp, int* num, char* argv[], CONF* data)
{
	char* num_flie = NULL;
	char* name_file;   // 初始化定义，以便后续判断
	get_filenum(data); // 获取文件数目

	if (check_num(data, argv[1]) == 0) // 检查用户输入第一个参数
	{
		if (check_num(data, argv[2]) == 0) // 输入第一个参数是非数字，检查第二个数据
		{
			printf("The number of records parameter could not be found in the input parameter!  输入参数中找不到记录条数参数！\n");
			printf("Program ending!  程序结束！\n");
		}
		else
		{
			strcpy(user_filename, argv[1]);
			if (check_seper_file(argv[1], data) == 0)
			{
				printf("Illegal Command Line Arguments!  命令行参数非法！\n");
				printf("Program ending!  程序结束！\n");
			}
			else
				name_file = argv[2]; // 第二个参数为为文件名，进行储存
		}
	}
	else // 用户输入第一个参数是数字
	{
		if (check_seper_file(argv[2], data) == 0)
		{
			printf("Illegal Command Line Arguments!  命令行参数非法！\n");
			printf("Program ending!  程序结束！\n");
		}
		else
		{
			strcpy(user_filename, argv[2]);
			name_file = argv[2]; // 第二个参数为为文件名，进行储存
		}
	}

	if (char* name_file = NULL)
		;
	else // 用户输入正确
	{
		// 创建文档
		if ((fp = fopen(user_filename, "w")) == NULL)
			printf("Error on open filet    未成功创建文件\n"); // 如果没有成功创建文档，进行报错提示
		else
		{
			*num = data->number;
			writenum(fp, data, user_filename);
		}
	}
}

/*
 *函数名称：get_filenum
 *函数功能：通过交互界面获取文件记录条数
 *输入参数：CONF data:结构体数组地址
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-04
 *           repair by Lifeng Zhang, 2023-04-18
 */
void get_filenum(CONF* data)
{
	char user_number[MAX_STR_LEN] = "no";
	printf("\n请输入你需要生成的数据条数（若使用配置文件/命令行参数请输入no）:\n");
	scanf("%s", user_number);
	clearstdin();

	// 判断用户是否输入合法
	if (strcmp(user_number, "no") != 0)
	{
		while (check_num(data, user_number) == 0)
		{
			printf("Illegal Number!!  输入数字非法!!:\n");
			printf("Please Re-enter!  请重新输入:\n");
			scanf("%s", user_number);
			clearstdin();
			if (strcmp(user_number, "no") == 0)
				break;
		}
		if (check_num(data, user_number) != 0)
			// 前期已经初始化，写入了数据
			printf("Use Configuration Files.  使用配置文件/命令行参数。\n");
	}
	else
		// 前期已经初始化，写入了数据
		printf("Use Configuration Files.  使用配置文件/命令行参数。\n");
}

/*
 *函数名称：get_filename
 *函数功能：通过交互界面获取文件储存路径
 *输入参数：char* str:文件路径与文件名   CONF data:结构体数组地址
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */

void get_filename(CONF* data)
{

	printf("\n请输入你需要生成的记录文件名称（可带有绝对路径或相对路径，输入no表示使用配置默认文件名）:\n");
	scanf("%s", user_filename);
	clearstdin();

	// 判断用户是否输入合法
	if (strcmp(user_filename, "no") != 0)
	{
		while (check_seper_file(user_filename, data) == 0)
		{
			printf("Illegal path or file name!!  输入路径或文件名非法!!:\n");
			printf("Please Re-enter!  请重新输入:\n");
			scanf("%s", user_filename);
			clearstdin();
			if (strcmp(user_filename, "no") == 0)
				break;
		}
	}
	else
		printf("Use Configuration Files.  使用配置文件。\n");
		
}

/*
 *函数名称：check_seper_file
 *函数功能：对argv[1]或argv[2]数据是否合法（为正确文件名）进行检查
 *          判断路径为相对路径还是绝对路径，之后切割路径与文件名，进行储存
 *输入参数：char* str:文件路径与文件名   CONF data:结构体数组地址
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-01
 *          repair by Lifeng Zhang, 2023-04-04
 */
int check_seper_file(char* str, CONF* data)
{
	int len = strlen(str);
	//_MAX_DRIVE、_MAX_DIR、_MAX_FNAME、_MAX_EXT 在配置中已有定义
	//_MAX_DRIVE==3，_MAX_DIR==_MAX_FNAME==_MAX_EXT==256
	char disk[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char way[MAX_STR_LEN];
	char file[MAX_STR_LEN];
	char filename_t[MAX_STR_LEN] = "";

	// 实验要求文件以.txt结尾
	if (str[len - 1] != 't' && str[len - 2] != 'x' && str[len - 3] != 't' && str[len - 4] != '.')
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
		// void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
		// 第一个是待处理的完整的文件名路径
		// 四个参数分别代表四个需要从原始文件路径中截取的字符串，有驱动器盘符(drive)，中间的路径（dir），文件名(fname)，和后缀名（ext）
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

		// 储存路径、文件名
		// void _makepath( const char *path, char *drive, char *dir, char *fname, char *ext);  #include <direct.h>
		// 第一个是要储存的的完整的文件名路径
		// 四个参数分别代表四个需要从结合字符串，有驱动器盘符(drive)，中间的路径（dir），文件名(fname)，和后缀名（ext）
		_makepath(way, disk, dir, NULL, NULL);
		_makepath(file, NULL, NULL, fname, ext);

		strcpy(data->filesavepath, way);
		strcpy(data->filename, file);

		if (access(data->filesavepath, 0) == -1) // 路径不存在，创建新路径
			_mkdir(data->filesavepath);
	}

	else if (p1 == NULL || p2 == NULL) // 仅仅是文件名
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(str, ":"))
			return 0;
		_splitpath(str, disk, dir, fname, ext);

		_makepath(way, disk, dir, NULL, NULL);
		_makepath(file, NULL, NULL, fname, ext);

		strcpy(data->filesavepath, way);
		strcpy(data->filename, file);

		if (access(data->filesavepath, 0) == -1) // 路径不存在，创建新路径
			_mkdir(data->filesavepath);

	}

	else // 相对路径
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(dir, ":"))
			return 0;

		// 储存路径、文件名
		_splitpath(str, disk, dir, fname, ext);

		_makepath(way, disk, dir, NULL, NULL);
		_makepath(file, NULL, NULL, fname, ext);

		strcpy(data->filesavepath, way);
		strcpy(data->filename, file);
		_chdir(dir);
	}
	return 1;
}

/*
 * 函数名称：int writenum
 * 函数功能：判断需要的存储方式、写入文件数据
 * 输入参数：CONF* data: 结构体指针data; char* temp:文件名
 * 返回值：int(返回0则结束此处程序)
 * 版本信息：create by Lifeng Zhang, 2023-04-17
 *           repair by Lifeng Zhang, 2023-04-18
 */
int writenum(FILE* fp, CONF* data, char* temp) // temp 文件名
{
	int way = 0;
	printf("张鲡沣的实验3程序：\n");
	printf("  1.生成数据记录文件（使用二维数组存储）\n");
	printf("  2.生成数据记录文件（使用结构体数组存储）\n");
	printf("请输入您要执行的功能的编号\n");
	scanf("%d", &way); // 判断需要的存储方式
	clearstdin();
	if (way == 1) // 第一种方式，使用二维数组存储
	{
		int num[500][3] = { 0 };
		creat_randnumber_byshuzu(fp, data, num); // 数组生成随机数
		if ((fp = fopen(temp, "w+")) == NULL)
		{
			printf("创建文件失败\n");
			return 0;
		}

		fprintf(fp, "%d\n", data->number);
		for (int i = 0; i < data->number; i++) // 输入到文件里
		{
			fprintf(fp, "%d %d %d\n", num[i][0], num[i][1], num[i][2]);
			printf("%d %d %d\n", num[i][0], num[i][1], num[i][2]);
		}
		fclose(fp); // 关闭文件
	}

	if (way == 2) // 第二种方式，使用结构体数组存储
	{
		DATAITEM* number; // 用动态规划划分结构体的空间
		number = (DATAITEM*)malloc(data->number * sizeof(DATAITEM));

		creat_randnumber_byjiegou(data, number); // 用结构体存储数据内容
		if ((fp = fopen(temp, "w")) == NULL)
			printf("创建文件失败\n");

		fprintf(fp, "%d\n", data->number);
		for (int i = 0; i < data->number; i++) // 将随机数传输到文件里
		{
			fprintf(fp, "%d %d %d\n", number[i].item1, number[i].item2, number[i].item3);
			printf("%d %d %d\n", number[i].item1, number[i].item2, number[i].item3);
		}

		fclose(fp);	  // 关闭文件夹
		free(number); // 释放内存
	}
}

/*
 * 函数名称：creat_randnumber_byshuzu
 * 函数功能：将随机数生成后储存到数组里
 * 输入参数：CONF* data: 结构体指针data;a[][3]
 * 返回值：int(无实际意义)
 * 版本信息：create by Lifeng Zhang, 2023-04-17
 */
void creat_randnumber_byshuzu(FILE* fp, CONF* data, int num[][3])
{
	srand((int)time(0));
	int i, temp1 = 0, temp2 = 0, temp3 = 0;
	for (i = 0; i < data->number; i++)
	{
		// 按照规定的数值范围进行划分
		temp1 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);

		if (temp1 == temp2) // 当相等的时候再次生成
			temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		else
			temp3 = random((data->maxvalue2 - data->minvalue2) + data->minvalue2);

		// 存入随机数
		num[i][0] = temp1;
		num[i][1] = temp2;
		num[i][2] = temp3;
	}
}

/*
 * 函数名称：creat_randnumber_byjiegou
 * 函数功能：将动态随机生成的随机数生成后储存到结构体里
 * 输入参数：CONF* data: 结构体指针 data;  DATAITEM* item: 存储数据记录结构体
 * 返回值：int(无实际意义)
 * 版本信息：create by Lifeng Zhang, 2023-04-17
 */
int creat_randnumber_byjiegou(CONF* data, DATAITEM* item)
{
	srand((int)time(0));
	int i, temp1 = 0, temp2 = 0, temp3 = 0;
	for (i = 0; i < data->number; i++)
	{
		// 按照预先的范围生成随机数
		temp1 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		if (temp1 == temp2)
			temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		else
			temp3 = random((data->maxvalue2 - data->minvalue2) + data->minvalue2);
		item[i].item1 = temp1;
		item[i].item2 = temp2;
		item[i].item3 = temp3;
	}
	return 0;
}

/*
 *函数名称：clearstdin
 *函数功能：对scanf输入进行缓存清除
 *输入参数：无
 *返回值：int(本程序无实际意义)
 *版本信息：create by Lifeng Zhang, 2022-03-17
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
 *输入参数：无
 *返回值：int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2022-04-01
 *          repair by Lifeng Zhang, 2023-04-18
 */
int check_num(CONF* data, char* str)
{
	int len = strlen(str);
	int i;
	for (i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	data->number = atoi(str);
	return 1;
}