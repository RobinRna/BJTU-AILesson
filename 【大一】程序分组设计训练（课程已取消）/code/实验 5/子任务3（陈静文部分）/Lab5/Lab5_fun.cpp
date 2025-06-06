#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”
//#define _CRT_SECURE_NO_WARNINGS 1
#include"Lab5_head.h"


/*************************************************************
函数名称:
menu
功能描述:
打印菜单
函数参数:
无
返回值:
无
*********************************/
void menu()
{
	printf("实验5程序：\n");
	printf("  1. 对单个英文文档进行统计\n");
	printf("  2. 对批量英文文档进行统计\n");
	printf("  0. 退出\n");
	printf("请输入您要执行的程序序号：\n");
}
/*************************************************************
函数名称:
fun1
功能描述:
实现菜单上的功能1
函数参数:
无
返回值:
无
*********************************/
void fun1(int argc, char* argv[])
{
	char filepath[200], filename[200], cmd1[200]="", cmd2[200];
	printf("请输入您要统计的英文文档路径(包含完整路径的文件名)\n");
	fflush(stdin);
	scanf("%s", filepath);
	strcpy(cmd1, "Lab5_task1.exe ");
	strcat(cmd1, argv[1]);
	strcat(cmd1, " ");
	strcat(cmd1, filepath);
	system(cmd1);


	strcpy(cmd2, "Lab5_task2.exe ");
	strcat(cmd2, filepath);
	strcat(cmd2, " ");
	strcat(cmd2, argv[4]);
	strcat(cmd2, " ");
	strcat(cmd2, argv[5]);
	system(cmd2);

}
/*************************************************************
函数名称:
fun2
功能描述:
实现菜单上的功能2
函数参数:
无SS
返回值:
无
*********************************/
void fun2(int argc, char* argv[])
{
	char filepath[200]="", cmd1[200]="", cmd2[200]="", filename_all[200]="", filepath_all[200]="", filename_out[200]="",filename_html[200]="";
	FILE* outfile, * fp;

	printf("请输入待统计文件所在文件夹的路径，文件路径分隔符必须用'\\'\n");
	fflush(stdin);
	scanf("%s", filepath);
	if ((fp = fopen("AllFileName.txt", "w")) == NULL)
	{
		printf("error");
		exit(0);
	}
	outfile = fopen("outcome.html", "w");
	if (outfile == NULL)
	{
		printf("error");
		exit(0);
	}
	else {
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
	}
	fclose(fp);
	
	strcpy(cmd1, "dir /b ");
	strcat(cmd1, filepath);
	strcat(cmd1, ">>");
	strcat(cmd1, "AllFileName.txt");
	system(cmd1);

	if ((fp = fopen("AllFileName.txt", "r")) == NULL)
	{
		printf("error");
		exit(0);
	}

	while (fscanf(fp, "%s", filename_all) != EOF)
	{
		strcpy(filename_out, "D:\\vscode\\Lab5\\Lab5\\files\\");//结果文件路径
		strcat(filename_out, filename_all);

		strcpy(filepath_all, filepath);//文件夹路径
		strcat(filepath_all, "//");
		strcat(filepath_all, filename_all);//filename_all是待处理文件的文件名，filepath_all是待处理文件的文件路径（含文件名）
		strcpy(cmd1, "Lab5_task1.exe ");
		strcat(cmd1,argv[1]);
		strcat(cmd1, " ");
		strcat(cmd1, filename_out);
		system(cmd1);


		strcpy(cmd2, "Lab5_task2.exe ");
		strcat(cmd2, "D:\\vscode\\Lab5\\Lab5\\files\\");
		strcat(cmd2, filename_all);
		strcat(cmd2, " ");
		strcpy(filename_html, "D:\\vscode\\Lab5\\Lab5\\");

		char disk[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(filename_all, disk, dir, fname, ext);
		strcat(fname, "2");
		strcat(filename_html, fname);
		strcat(filename_html, ".html ");
		strcat(cmd2, filename_html);
		strcat(cmd2, " ");
		strcat(cmd2, argv[5]);
		system(cmd2);
		fprintf(outfile, "<a href=\"%s\">跳转到%s的统计页面</a>\n<br>\n", filename_html, filename_all);//TongjiFileName存的是结果文件路径
	}

	fprintf(outfile, "</body>\n");
	fclose(outfile);
	WinExec("C://Program Files (x86)//Microsoft//Edge//Application//MSEDGE.EXE D:\\vscode\\Lab5\\Lab5\\outcome.html", 999); //自动打开浏览器


}