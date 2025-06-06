/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
	��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
	ʵ��5 ��������1����,����html�ļ�
ժҪ:
	��ҵ�����ʵ��5
����˵��:
	�ޡ�
ģ����ʷ:
������������2023��5��30�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_view.h"

/*
 *�������ƣ�create_html
 *�������ܣ���html�ļ�д�������Ϣ
 *���������htmldata* data �ļ�����, FILE* infile �����ļ�1ָ��
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-06-01
 */
void create_html(htmldata* data, FILE* infile)
{
	FILE* outfile = NULL;
	if ((outfile = fopen(data->output_file, "w+")) == NULL)
	{
		printf("�����ļ�ʧ��\n");
		exit(0);
	}

	html_basic(outfile); // ¼��html�ļ���������

	char line[MAX_STR_LEN];
	while (fgets(line, sizeof(line), infile)) // ��ʽ����
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
 *�������ƣ�loadfile
 *�������ܣ�����ʵ��5-1�����ļ�
 *���������htmldata* data �ļ�������count �����в����õ���������
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-06-01
 */
void loadfile(htmldata* data, int count)
{
	FILE* infile = NULL;

	while ((infile = fopen(data->input_file, "r+")) == NULL)
	{
		printf("��Ѱ�ļ�ʧ��\n");
		get_filename(data, count);
	}

	create_html(data, infile); // ��html�ļ�д�������Ϣ
}

/*
 *�������ƣ�html_open
 *�������ܣ���html�ļ�
 *���������htmldata* data �ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-06-01
 */
void html_open(htmldata* data)
{

	char* buffer = NULL;
	char buffer1[MAX_STR_LEN];
	char command[MAX_STR_LEN] = "start ";

	// Ҳ���Խ�buffer��Ϊ�������
	if ((buffer = getcwd(NULL, 0)) == NULL)
		perror("getcwd error");
	else
		strcpy(buffer1, buffer);

	if (data->mode == 0) // �Զ�ģʽ���չʾ
	{
		printf("�ɹ�������ҳ\n");

		strcat(command, data->output_file);
		system(command); // ����ϵͳ����system��html�ļ�
	}
	if (data->mode == 1) // ��Ĭģʽ���չʾ
	{
		strcat(buffer1, "\\");
		strcat(buffer1, data->output_file);
		printf("html�ļ�������: %s\n", buffer1);
	}
}

/*
 *�������ƣ�html_basic
 *�������ܣ�¼��html�ļ���������
 *���������FILE* outfile html�ļ�ָ��
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-06-01
 */
void html_basic(FILE* outfile)
{
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
	fprintf(outfile, "    <tr>\n");
	fprintf(outfile, "        <h1 align=\"center\">�ı�ͳ��</h2>\n");
	fprintf(outfile, "        <h3 align=\"center\">Text Statistics</h3>\n");
	fprintf(outfile, "    </tr>\n");
	fprintf(outfile, "    <table width=\"20%% \" border=\"1\" align=\"center\">\n");
}