#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���
//#define _CRT_SECURE_NO_WARNINGS 1
#include"Lab5_head.h"


/*************************************************************
��������:
menu
��������:
��ӡ�˵�
��������:
��
����ֵ:
��
*********************************/
void menu()
{
	printf("ʵ��5����\n");
	printf("  1. �Ե���Ӣ���ĵ�����ͳ��\n");
	printf("  2. ������Ӣ���ĵ�����ͳ��\n");
	printf("  0. �˳�\n");
	printf("��������Ҫִ�еĳ�����ţ�\n");
}
/*************************************************************
��������:
fun1
��������:
ʵ�ֲ˵��ϵĹ���1
��������:
��
����ֵ:
��
*********************************/
void fun1(int argc, char* argv[])
{
	char filepath[200], filename[200], cmd1[200]="", cmd2[200];
	printf("��������Ҫͳ�Ƶ�Ӣ���ĵ�·��(��������·�����ļ���)\n");
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
��������:
fun2
��������:
ʵ�ֲ˵��ϵĹ���2
��������:
��SS
����ֵ:
��
*********************************/
void fun2(int argc, char* argv[])
{
	char filepath[200]="", cmd1[200]="", cmd2[200]="", filename_all[200]="", filepath_all[200]="", filename_out[200]="",filename_html[200]="";
	FILE* outfile, * fp;

	printf("�������ͳ���ļ������ļ��е�·�����ļ�·���ָ���������'\\'\n");
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
		fprintf(outfile, "    <title>����������ѵ��Lab5��ҵ</title>\n");
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
		fprintf(outfile, "            <td width=\"26%% \" align=\"center\" valign=\"middle\"><strong>ѧԺ</strong></td>\n");
		fprintf(outfile, "            <td width=\"74%% \" align=\"center\" valign=\"middle\"><strong>���������Ϣ����ѧԺ</strong></td>\n");
		fprintf(outfile, "        </tr>\n");
		fprintf(outfile, "        <tr>\n");
		fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>ѧ��</strong></td>\n");
		fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>22281030 22281031 22281052</strong></td>\n");
		fprintf(outfile, "        </tr>\n");
		fprintf(outfile, "        <tr>\n");
		fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>����</strong></td>\n");
		fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>�¾��� �¿��� ������</strong></td>\n");
		fprintf(outfile, "        </tr>\n");
		fprintf(outfile, "        <tr>\n");
		fprintf(outfile, "            <td height=\"31\" align=\"center\" valign=\"middle\"><strong>�༶</strong></td>\n");
		fprintf(outfile, "            <td align=\"center\" valign=\"middle\"><strong>�����2202��</strong></td>\n");
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
		strcpy(filename_out, "D:\\vscode\\Lab5\\Lab5\\files\\");//����ļ�·��
		strcat(filename_out, filename_all);

		strcpy(filepath_all, filepath);//�ļ���·��
		strcat(filepath_all, "//");
		strcat(filepath_all, filename_all);//filename_all�Ǵ������ļ����ļ�����filepath_all�Ǵ������ļ����ļ�·�������ļ�����
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
		fprintf(outfile, "<a href=\"%s\">��ת��%s��ͳ��ҳ��</a>\n<br>\n", filename_html, filename_all);//TongjiFileName����ǽ���ļ�·��
	}

	fprintf(outfile, "</body>\n");
	fclose(outfile);
	WinExec("C://Program Files (x86)//Microsoft//Edge//Application//MSEDGE.EXE D:\\vscode\\Lab5\\Lab5\\outcome.html", 999); //�Զ��������


}