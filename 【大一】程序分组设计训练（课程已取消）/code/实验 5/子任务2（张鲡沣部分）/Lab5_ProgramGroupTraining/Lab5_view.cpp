/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	实验5 加载任务1程序,生成html文件
摘要:
	作业，配合实验5
其它说明:
	无。
模块历史:
　　张鲡沣于2023年5月30日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_view.h"

/*
 *函数名称：create_html
 *函数功能：打开html文件写入相关信息
 *输入参数：htmldata* data 文件参数, FILE* infile 程序文件1指针
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-06-01
 */
void create_html(htmldata* data, FILE* infile)
{
	FILE* outfile = NULL;
	if ((outfile = fopen(data->output_file, "w+")) == NULL)
	{
		printf("创建文件失败\n");
		exit(0);
	}

	html_basic(outfile); // 录入html文件初步代码

	char line[MAX_STR_LEN];
	while (fgets(line, sizeof(line), infile)) // 行式读入
	{
		char item[MAX_STR_LEN];
		int count;
		sscanf(line, "%s  %d", item, &count);
		fprintf(outfile, "        <tr>\n");
		fprintf(outfile, "            <td width=\"40%% \" align=\"center\" valign=\"middle\"><strong>%s</strong></td>\n", item);
		fprintf(outfile, "            <td width=\"60%% \" align=\"center\" valign=\"middle\"><strong>%d</strong></td>\n", count);
		fprintf(outfile, "        </tr>\n");
	}

	fprintf(outfile, "</table>\n");
	fprintf(outfile, "</body>\n");
	fprintf(outfile, "</html>\n");

	fclose(infile);
	fclose(outfile);

	html_open(data);
}

/*
 *函数名称：loadfile
 *函数功能：加载实验5-1生成文件
 *输入参数：htmldata* data 文件参数，count 命令行参数得到参数个数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-06-01
 */
void loadfile(htmldata* data, int count)
{
	FILE* infile = NULL;

	while ((infile = fopen(data->input_file, "r+")) == NULL)
	{
		printf("找寻文件失败\n");
		get_filename(data, count);
	}

	create_html(data, infile); // 打开html文件写入相关信息
}

/*
 *函数名称：html_open
 *函数功能：打开html文件
 *输入参数：htmldata* data 文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-06-01
 */
void html_open(htmldata* data)
{

	char* buffer = NULL;
	char buffer1[MAX_STR_LEN];
	char command[MAX_STR_LEN] = "start ";

	// 也可以将buffer作为输出参数
	if ((buffer = getcwd(NULL, 0)) == NULL)
		perror("getcwd error");
	else
		strcpy(buffer1, buffer);

	if (data->mode == 0) // 自动模式结果展示
	{
		printf("成功生成网页\n");

		strcat(command, data->output_file);
		system(command); // 调用系统函数system打开html文件
	}
	if (data->mode == 1) // 静默模式结果展示
	{
		strcat(buffer1, "\\");
		strcat(buffer1, data->output_file);
		printf("html文件生成在: %s\n", buffer1);
	}
}

/*
 *函数名称：html_basic
 *函数功能：录入html文件初步代码
 *输入参数：FILE* outfile html文件指针
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-06-01
 */
void html_basic(FILE* outfile)
{
	fprintf(outfile, "<!DOCTYPE html>\n");
	fprintf(outfile, "<html lang=\"en\">\n");
	fprintf(outfile, "<head>\n");
	fprintf(outfile, "    <meta charset=\"GBK\">\n");
	fprintf(outfile, "    <meta http-equiv=\"X-UA- Compatible\" content=\"IE = edge\">\n");
	fprintf(outfile, "    <meta name=\"viewport\" content=\"width =device width, initial-scale1.0\">\n");
	fprintf(outfile, "    <title>程序分组设计训练Lab5作业</title>\n");
	fprintf(outfile, "    <style type=\"text/css\">\n");
	fprintf(outfile, "        body{\n");
	fprintf(outfile, "                background-image: url(\"background.jpg\") ;\n");
	fprintf(outfile, "                background-repeat:repeat-x;\n");
	fprintf(outfile, "            }\n");
	fprintf(outfile, "    </style>\n");
	fprintf(outfile, "    <body background=\"background.jpg\" style=\"background-repeat:no-repeat\n");
	fprintf(outfile, "                   background-attachmentfixed;\n");
	fprintf(outfile, "                   background-size:100% 100%; \" > \n");
	fprintf(outfile, "</head>\n");
	fprintf(outfile, "<body>\n");
	fprintf(outfile, "    <table width=\"5%% \" align=\"center\" >\n");
	fprintf(outfile, "        <tr>\n");
	fprintf(outfile, "            <td><img src=\"R-C.jpg\" width=\"358\" height=\"112\" /></td>\n");
	fprintf(outfile, "        </tr>\n");
	fprintf(outfile, "    </table>\n");
	fprintf(outfile, "    <br>\n");
	fprintf(outfile, "    <table width=\"40%% \" border=\"1\" align=\"center\">\n");
	fprintf(outfile, "        <tr>\n");
	fprintf(outfile, "            <td width=\"26%% \" align=\"center\" valign=\"middle\"><strong>学院</strong></td>\n");
	fprintf(outfile, "            <td width=\"74%% \" align=\"center\" valign=\"middle\"><strong>计算机与信息技术学院</strong></td>\n");
	fprintf(outfile, "        </tr>\n");
	fprintf(outfile, "        <tr>\n");
	fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>学号</strong></td>\n");
	fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>22281030 22281031 22281052</strong></td>\n");
	fprintf(outfile, "        </tr>\n");
	fprintf(outfile, "        <tr>\n");
	fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>姓名</strong></td>\n");
	fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>陈静文 陈俊男 张鲡沣</strong></td>\n");
	fprintf(outfile, "        </tr>\n");
	fprintf(outfile, "        <tr>\n");
	fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>班级</strong></td>\n");
	fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>计算机2202班</strong></td>\n");
	fprintf(outfile, "        </tr>\n");
	fprintf(outfile, "    </table>\n");
	fprintf(outfile, "</body>\n");
	fprintf(outfile, "    <br><br>\n");
	fprintf(outfile, "<body>\n");
	fprintf(outfile, "    <tr>\n");
	fprintf(outfile, "        <h1 align=\"center\">文本统计</h2>\n");
	fprintf(outfile, "        <h3 align=\"center\">Text Statistics</h3>\n");
	fprintf(outfile, "    </tr>\n");
	fprintf(outfile, "    <table width=\"20%% \" border=\"1\" align=\"center\">\n");
}