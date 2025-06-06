/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
	��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
	ʵ��5 ����ں���
ժҪ:
	��ҵ�����ʵ��5
����˵��:
	�ޡ�
ģ����ʷ:
������������2023��5��30�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab5_main.h"

/*
 *�������ƣ�run
 *�������ܣ�ʵ��5����������
 *���������int argc�������в���������char* argv[]:�����в���ֵ
 *����ֵ��int(��ʵ�ʺ���)
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-30
 */
int run(int argc, char* argv[])
{
	htmldata* data = (htmldata*)malloc(sizeof(htmldata));

	if (argc == 1)
	{
		int count = 1;
		get_filename(data, count); // ���룺����txt·��
		count++;
		get_filename(data, count); // ���룺���html·��

		printf("�����룺����ģʽ��0Ϊ�Զ�ģʽ��1Ϊ��Ĭģʽ��\n");
		check_num(data);
	}

	if (argc == 2)
	{
		printf("��������������������������� <����txt·��> <���html·��> <ģʽ> ��\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<����txt·��> �������\n");
			get_filename(data, count); // ���룺����txt·��
		}

		char disk[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(data->input_file, disk, dir, fname, ext);
		strcat(fname, "1");
		_makepath(data->input_file, disk, dir, fname, ext);

		count++;
		get_filename(data, count); // ���룺���html·��

		printf("�����룺����ģʽ��0Ϊ�Զ�ģʽ��1Ϊ��Ĭģʽ��\n");
		check_num(data);
	}

	if (argc == 3)
	{
		printf("��������������������������� <����txt·��> <���html·��> <ģʽ> ��\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);
		strcpy(data->output_file, argv[2]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<����txt·��> �������\n");
			get_filename(data, count); // ���룺����txt·��
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
			printf("<���html·��> �������\n");
			get_filename(data, count); // ���룺���html·��
		}

		printf("�����룺����ģʽ��0Ϊ�Զ�ģʽ��1Ϊ��Ĭģʽ��\n");
		check_num(data);
	}

	if (argc == 4)
	{
		printf("��������������������������� <����txt·��> <���html·��> <ģʽ> ��\n");
		int count = 1;
		strcpy(data->input_file, argv[1]);
		strcpy(data->output_file, argv[2]);

		if (check_seper_file(data->input_file, count) == 0)
		{
			printf("<����txt·��> �������\n");
			get_filename(data, count); // ���룺����txt·��
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
			printf("<���html·��> �������\n");
			get_filename(data, count); // ���룺���html·��
		}

		data->mode = atoi(argv[3]);
		check_num(data);
	}

	if (argc > 4)
	{
		printf("����������࣬������ֹ��\n");
		exit(0);
	}

	loadfile(data, 1); // ����������1���򡢼���ҳ��������ļ�
}