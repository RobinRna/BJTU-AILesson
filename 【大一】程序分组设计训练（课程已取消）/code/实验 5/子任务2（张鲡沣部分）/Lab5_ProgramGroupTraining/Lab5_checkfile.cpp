/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
	��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
	ʵ��4 ����ں���
ժҪ:
	��ҵ�����ʵ��4����������Lab3ʵ�����
����˵��:
	�ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_checkfile.h"

/*
 *�������ƣ�get_filename
 *�������ܣ�ͨ�����������ȡ�ļ�����·��
 *���������htmldata* data �ļ�����
 *          count �����в����õ���������
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04��Lab3�г���
 *          repair by Lifeng Zhang, 2023-05-30
 */

void get_filename(htmldata* data, int count)
{
	char user_filename[MAX_STR_LEN];

	if (count == 1)
	{
		printf("\n�����룺����txt·�����ɴ��о���·�������·��������no��ʾʹ������Ĭ���ļ�����:\n");
		scanf("%s", data->input_file);
		strcpy(user_filename, data->input_file);
	}
	else
	{
		printf("\n�����룺���html·�����ɴ��о���·�������·��������no��ʾʹ������Ĭ���ļ�����:\n");
		scanf("%s", data->output_file);
		strcpy(user_filename, data->output_file);
	}
	clearstdin();

	// �ж��û��Ƿ�����Ϸ�
	while (check_seper_file(user_filename, count) == 0)
	{
		printf("Illegal path or file name!!  ����·�����ļ����Ƿ�!!:\n");
		printf("Please Re-enter!  ����������:\n");
		scanf("%s", user_filename);
		clearstdin();
	}

	if (count == 1)
		strcpy(data->input_file, user_filename);
	else
		strcpy(data->output_file, user_filename);
}

/*
 *�������ƣ�check_seper_file
 *�������ܣ���str�����Ƿ�Ϸ���Ϊ��ȷ�ļ��������м��
 *          �ж�·��Ϊ���·�����Ǿ���·�����и�·�����ļ���
 *���������char* str:�ļ�·�����ļ���
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-01��Lab3�г���
 *          repair by Lifeng Zhang, 2023-05-30
 */
int check_seper_file(char* str, int count)
{
	int len = strlen(str);
	//_MAX_DRIVE��_MAX_DIR��_MAX_FNAME��_MAX_EXT �����������ж���
	//_MAX_DRIVE==3��_MAX_DIR==_MAX_FNAME==_MAX_EXT==256
	char disk[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char way[MAX_STR_LEN];

	// void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
	// ��һ���Ǵ�������������ļ���·��
	// �ĸ������ֱ�����ĸ���Ҫ��ԭʼ�ļ�·���н�ȡ���ַ��������������̷�(drive)���м��·����dir�����ļ���(fname)���ͺ�׺����ext��
	_splitpath(str, disk, dir, fname, ext);

	// ʵ��Ҫ���ļ���.txt����.html��β
	if (count == 1)
		if (strcmp(ext, ".txt") != 0)
			return 0;

	if (count == 2)
		if (strcmp(ext, ".html") != 0)
			return 0;

	if (*str == '\\') // ������"\\"��ͷ
		return 0;

	// ������"\\"��"/"��β�����Դ˽�β����Ϊ�ļ���Ϊ��
	char* index1 = strrchr(str, '\\');
	char* index2 = strrchr(str, '/');
	if (index1 - str + 1 == strlen(str) || index2 - str + 1 == strlen(str))
		return 0;

	// ���кϲ����Ա��������
	char* index;
	if (index2 > index1)
		index = index2;
	else
		index = index1;

	// �ж�����·��Ϊ����·���������·��
	char* p1 = strstr(str, ":\\");
	char* p2 = strstr(str, ":/");

	if (p1 || p2) // ������Ǿ���·��
	{

		_splitpath(str, disk, dir, fname, ext);

		// �ж�disk�ڵ������Ƿ����
		if (access(disk, 0) != 0)
		{
			printf("%s is no exist! disk�ڵ����в����� \n", disk);
			return 0;
		}

		// �ж�·�����Ƿ��зǷ��ַ�
		if (strstr(dir, "*") || strstr(dir, "?") || strstr(dir, "<") || strstr(dir, ">") || strstr(dir, "|") || strstr(dir, ":"))
			return 0;
		if (strstr(fname, "*") || strstr(fname, "?") || strstr(fname, "<") || strstr(fname, ">") || strstr(fname, "|") || strstr(dir, ":"))
			return 0;

		_makepath(way, disk, dir, NULL, NULL);
		if (access(way, 0) == -1) // ·�������ڣ�������·��
			_mkdir(way);
	}

	else if (p1 == NULL || p2 == NULL) // �������ļ���
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(str, ":"))
			return 0;
	}

	else // ���·��
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(dir, ":"))
			return 0;

		// ����·�����ļ���
		_makepath(way, disk, dir, NULL, NULL);
		_chdir(dir);
	}
	return 1;
}

/*
 *�������ƣ�clearstdin
 *�������ܣ���scanf������л������
 *�����������
 *����ֵ��int(��������ʵ������)
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-17��Lab3�г���
 */
int clearstdin()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	return 0;
}

/*
 *�������ƣ�check_num
 *�������ܣ����������������Ƿ�Ϸ���Ϊ�����֣����м��
 *���������htmldata* data �ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-30
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
			printf("�����������������룡\n�����룺����ģʽ��0Ϊ�Զ�ģʽ��1Ϊ��Ĭģʽ��\n");
	}
}