/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
	��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
	ʵ��3 ��װ����������
ժҪ:
	��ҵ�����ʵ��3
����˵��:
	�ޡ�
ģ����ʷ:
������������2023��4��1�մ�����ģ�飬email: 22281052@bjtu.edu.cn
	��������2023��4��4���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
	��������2023��4��11���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
	��������2023��4��17���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab3_fun.h"

/*
 *�������ƣ�ini_read
 *�������ܣ�ǰ�������ļ�
 *���������CONF* data:�ṹ��ָ��data
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-03-17
 */
void ini_read(CONF* data)
{
	FILE* fp = fopen("D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_3_Experiments/Lab3_ProgramGroupTraining/set/conf.ini", "r"); // ���ļ���ַ�򿪣���ȡ����
	if (fp)
	{
		// ����Ӧ�е����ݶ���ṹ��
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
		fclose(fp); // �ر��ļ�
		fflush(fp); // �建�棬��ֹ��ջ
	}
	else
	{
		printf("δ�ܴ򿪴��ļ�conf.ini,ϵͳ�Զ���������ļ�\n");
		// �������Ĭ��ֵ��������
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
 *�������ƣ�create_1
 *�������ܣ��û�δ������������������ļ�
 *���������FILE*fp:�ļ�ָ�롢int* num:argv[1]�ļ�������char* argv[]:�����в���ֵ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-03-17
 */
void create_1(FILE* fp, int* num, char* argv[], CONF* data)
{
	get_filenum(data); // ��ȡ�ļ���Ŀ

	char crea[4];
	printf("Whether to enter the file path yourself?  Please input yes / no.\n");
	printf("�Ƿ����������ļ�·����  ������yes/no.\n");
	scanf("%s", crea);
	clearstdin();

	if (strcmp(crea, "no") == 0) // ����������
	{
		printf("Use Configuration Files.  ʹ�������ļ���\n");
		_mkdir("output/");
		strcpy(user_filename, "../Default.txt");
	}

	else
		get_filename(data); // ��ȡ�ļ���

	// �����ĵ�
	if ((fp = fopen(user_filename, "w+")) == NULL)
		printf("Error on open filet    δ�ɹ������ļ�\n"); // ���û�гɹ������ĵ������б�����ʾ
	else
	{
		*num = data->number;
		writenum(fp, data, user_filename);
	}
}

/*
 *�������ƣ�create_2
 *�������ܣ��û���������������������ļ�
 *���������FILE*fp:�ļ�ָ�롢int* num:�ļ�������char* argv[]:�����в���ֵ��CONF data:�ṹ�������ַ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */
void create_2(FILE* fp, int* num, char* argv[], CONF* data)
{
	char* name_file = NULL; // ��ʼ�����壬�Ա�����ж�
	get_filenum(data);		// ��ȡ�ļ���Ŀ

	if (check_num(data, argv[1]) == 0) // ����û��������
	{
		// ���������·�����������
		
		if (check_seper_file(argv[1], data) == 0)
		{
			printf("Illegal Command Line Arguments!  �����в����Ƿ���\n");
			printf("Program ending!  ���������\n");
		}
		else
		{
			strcpy(user_filename, argv[1]);
			name_file = argv[1];
		}
	}
	else // �����������Ŀ������ļ���
	{
		get_filename(data); // ��ȡ�ļ���
		name_file = user_filename;
	}
	if (name_file == NULL)
		;
	else // �û�������ȷ
	{
		// �����ĵ�
		if ((fp = fopen(name_file, "w")) == NULL)
			printf("Error on open filet    δ�ɹ������ļ�\n"); // ���û�гɹ������ĵ������б�����ʾ
		else
		{
			*num = data->number;
			writenum(fp, data, user_filename);
		}
	}
}

/*
 *�������ƣ�create_3
 *�������ܣ��û���������������������ļ�
 *���������FILE*fp:�ļ�ָ�롢int* num:�ļ�������char* argv[]:�����в���ֵ��CONF data:�ṹ�������ַ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-01
 *          repair by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */
void create_3(FILE* fp, int* num, char* argv[], CONF* data)
{
	char* num_flie = NULL;
	char* name_file;   // ��ʼ�����壬�Ա�����ж�
	get_filenum(data); // ��ȡ�ļ���Ŀ

	if (check_num(data, argv[1]) == 0) // ����û������һ������
	{
		if (check_num(data, argv[2]) == 0) // �����һ�������Ƿ����֣����ڶ�������
		{
			printf("The number of records parameter could not be found in the input parameter!  ����������Ҳ�����¼����������\n");
			printf("Program ending!  ���������\n");
		}
		else
		{
			strcpy(user_filename, argv[1]);
			if (check_seper_file(argv[1], data) == 0)
			{
				printf("Illegal Command Line Arguments!  �����в����Ƿ���\n");
				printf("Program ending!  ���������\n");
			}
			else
				name_file = argv[2]; // �ڶ�������ΪΪ�ļ��������д���
		}
	}
	else // �û������һ������������
	{
		if (check_seper_file(argv[2], data) == 0)
		{
			printf("Illegal Command Line Arguments!  �����в����Ƿ���\n");
			printf("Program ending!  ���������\n");
		}
		else
		{
			strcpy(user_filename, argv[2]);
			name_file = argv[2]; // �ڶ�������ΪΪ�ļ��������д���
		}
	}

	if (char* name_file = NULL)
		;
	else // �û�������ȷ
	{
		// �����ĵ�
		if ((fp = fopen(user_filename, "w")) == NULL)
			printf("Error on open filet    δ�ɹ������ļ�\n"); // ���û�гɹ������ĵ������б�����ʾ
		else
		{
			*num = data->number;
			writenum(fp, data, user_filename);
		}
	}
}

/*
 *�������ƣ�get_filenum
 *�������ܣ�ͨ�����������ȡ�ļ���¼����
 *���������CONF data:�ṹ�������ַ
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04
 *           repair by Lifeng Zhang, 2023-04-18
 */
void get_filenum(CONF* data)
{
	char user_number[MAX_STR_LEN] = "no";
	printf("\n����������Ҫ���ɵ�������������ʹ�������ļ�/�����в���������no��:\n");
	scanf("%s", user_number);
	clearstdin();

	// �ж��û��Ƿ�����Ϸ�
	if (strcmp(user_number, "no") != 0)
	{
		while (check_num(data, user_number) == 0)
		{
			printf("Illegal Number!!  �������ַǷ�!!:\n");
			printf("Please Re-enter!  ����������:\n");
			scanf("%s", user_number);
			clearstdin();
			if (strcmp(user_number, "no") == 0)
				break;
		}
		if (check_num(data, user_number) != 0)
			// ǰ���Ѿ���ʼ����д��������
			printf("Use Configuration Files.  ʹ�������ļ�/�����в�����\n");
	}
	else
		// ǰ���Ѿ���ʼ����д��������
		printf("Use Configuration Files.  ʹ�������ļ�/�����в�����\n");
}

/*
 *�������ƣ�get_filename
 *�������ܣ�ͨ�����������ȡ�ļ�����·��
 *���������char* str:�ļ�·�����ļ���   CONF data:�ṹ�������ַ
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04
 *          repair by Lifeng Zhang, 2023-04-18
 */

void get_filename(CONF* data)
{

	printf("\n����������Ҫ���ɵļ�¼�ļ����ƣ��ɴ��о���·�������·��������no��ʾʹ������Ĭ���ļ�����:\n");
	scanf("%s", user_filename);
	clearstdin();

	// �ж��û��Ƿ�����Ϸ�
	if (strcmp(user_filename, "no") != 0)
	{
		while (check_seper_file(user_filename, data) == 0)
		{
			printf("Illegal path or file name!!  ����·�����ļ����Ƿ�!!:\n");
			printf("Please Re-enter!  ����������:\n");
			scanf("%s", user_filename);
			clearstdin();
			if (strcmp(user_filename, "no") == 0)
				break;
		}
	}
	else
		printf("Use Configuration Files.  ʹ�������ļ���\n");
		
}

/*
 *�������ƣ�check_seper_file
 *�������ܣ���argv[1]��argv[2]�����Ƿ�Ϸ���Ϊ��ȷ�ļ��������м��
 *          �ж�·��Ϊ���·�����Ǿ���·����֮���и�·�����ļ��������д���
 *���������char* str:�ļ�·�����ļ���   CONF data:�ṹ�������ַ
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-01
 *          repair by Lifeng Zhang, 2023-04-04
 */
int check_seper_file(char* str, CONF* data)
{
	int len = strlen(str);
	//_MAX_DRIVE��_MAX_DIR��_MAX_FNAME��_MAX_EXT �����������ж���
	//_MAX_DRIVE==3��_MAX_DIR==_MAX_FNAME==_MAX_EXT==256
	char disk[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char way[MAX_STR_LEN];
	char file[MAX_STR_LEN];
	char filename_t[MAX_STR_LEN] = "";

	// ʵ��Ҫ���ļ���.txt��β
	if (str[len - 1] != 't' && str[len - 2] != 'x' && str[len - 3] != 't' && str[len - 4] != '.')
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
		// void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
		// ��һ���Ǵ�������������ļ���·��
		// �ĸ������ֱ�����ĸ���Ҫ��ԭʼ�ļ�·���н�ȡ���ַ��������������̷�(drive)���м��·����dir�����ļ���(fname)���ͺ�׺����ext��
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

		// ����·�����ļ���
		// void _makepath( const char *path, char *drive, char *dir, char *fname, char *ext);  #include <direct.h>
		// ��һ����Ҫ����ĵ��������ļ���·��
		// �ĸ������ֱ�����ĸ���Ҫ�ӽ���ַ��������������̷�(drive)���м��·����dir�����ļ���(fname)���ͺ�׺����ext��
		_makepath(way, disk, dir, NULL, NULL);
		_makepath(file, NULL, NULL, fname, ext);

		strcpy(data->filesavepath, way);
		strcpy(data->filename, file);

		if (access(data->filesavepath, 0) == -1) // ·�������ڣ�������·��
			_mkdir(data->filesavepath);
	}

	else if (p1 == NULL || p2 == NULL) // �������ļ���
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(str, ":"))
			return 0;
		_splitpath(str, disk, dir, fname, ext);

		_makepath(way, disk, dir, NULL, NULL);
		_makepath(file, NULL, NULL, fname, ext);

		strcpy(data->filesavepath, way);
		strcpy(data->filename, file);

		if (access(data->filesavepath, 0) == -1) // ·�������ڣ�������·��
			_mkdir(data->filesavepath);

	}

	else // ���·��
	{
		if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(dir, ":"))
			return 0;

		// ����·�����ļ���
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
 * �������ƣ�int writenum
 * �������ܣ��ж���Ҫ�Ĵ洢��ʽ��д���ļ�����
 * ���������CONF* data: �ṹ��ָ��data; char* temp:�ļ���
 * ����ֵ��int(����0������˴�����)
 * �汾��Ϣ��create by Lifeng Zhang, 2023-04-17
 *           repair by Lifeng Zhang, 2023-04-18
 */
int writenum(FILE* fp, CONF* data, char* temp) // temp �ļ���
{
	int way = 0;
	printf("�������ʵ��3����\n");
	printf("  1.�������ݼ�¼�ļ���ʹ�ö�ά����洢��\n");
	printf("  2.�������ݼ�¼�ļ���ʹ�ýṹ������洢��\n");
	printf("��������Ҫִ�еĹ��ܵı��\n");
	scanf("%d", &way); // �ж���Ҫ�Ĵ洢��ʽ
	clearstdin();
	if (way == 1) // ��һ�ַ�ʽ��ʹ�ö�ά����洢
	{
		int num[500][3] = { 0 };
		creat_randnumber_byshuzu(fp, data, num); // �������������
		if ((fp = fopen(temp, "w+")) == NULL)
		{
			printf("�����ļ�ʧ��\n");
			return 0;
		}

		fprintf(fp, "%d\n", data->number);
		for (int i = 0; i < data->number; i++) // ���뵽�ļ���
		{
			fprintf(fp, "%d %d %d\n", num[i][0], num[i][1], num[i][2]);
			printf("%d %d %d\n", num[i][0], num[i][1], num[i][2]);
		}
		fclose(fp); // �ر��ļ�
	}

	if (way == 2) // �ڶ��ַ�ʽ��ʹ�ýṹ������洢
	{
		DATAITEM* number; // �ö�̬�滮���ֽṹ��Ŀռ�
		number = (DATAITEM*)malloc(data->number * sizeof(DATAITEM));

		creat_randnumber_byjiegou(data, number); // �ýṹ��洢��������
		if ((fp = fopen(temp, "w")) == NULL)
			printf("�����ļ�ʧ��\n");

		fprintf(fp, "%d\n", data->number);
		for (int i = 0; i < data->number; i++) // ����������䵽�ļ���
		{
			fprintf(fp, "%d %d %d\n", number[i].item1, number[i].item2, number[i].item3);
			printf("%d %d %d\n", number[i].item1, number[i].item2, number[i].item3);
		}

		fclose(fp);	  // �ر��ļ���
		free(number); // �ͷ��ڴ�
	}
}

/*
 * �������ƣ�creat_randnumber_byshuzu
 * �������ܣ�����������ɺ󴢴浽������
 * ���������CONF* data: �ṹ��ָ��data;a[][3]
 * ����ֵ��int(��ʵ������)
 * �汾��Ϣ��create by Lifeng Zhang, 2023-04-17
 */
void creat_randnumber_byshuzu(FILE* fp, CONF* data, int num[][3])
{
	srand((int)time(0));
	int i, temp1 = 0, temp2 = 0, temp3 = 0;
	for (i = 0; i < data->number; i++)
	{
		// ���չ涨����ֵ��Χ���л���
		temp1 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);

		if (temp1 == temp2) // ����ȵ�ʱ���ٴ�����
			temp2 = random((data->maxvalue1 - data->minvalue1) + data->minvalue1);
		else
			temp3 = random((data->maxvalue2 - data->minvalue2) + data->minvalue2);

		// ���������
		num[i][0] = temp1;
		num[i][1] = temp2;
		num[i][2] = temp3;
	}
}

/*
 * �������ƣ�creat_randnumber_byjiegou
 * �������ܣ�����̬������ɵ���������ɺ󴢴浽�ṹ����
 * ���������CONF* data: �ṹ��ָ�� data;  DATAITEM* item: �洢���ݼ�¼�ṹ��
 * ����ֵ��int(��ʵ������)
 * �汾��Ϣ��create by Lifeng Zhang, 2023-04-17
 */
int creat_randnumber_byjiegou(CONF* data, DATAITEM* item)
{
	srand((int)time(0));
	int i, temp1 = 0, temp2 = 0, temp3 = 0;
	for (i = 0; i < data->number; i++)
	{
		// ����Ԥ�ȵķ�Χ���������
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
 *�������ƣ�clearstdin
 *�������ܣ���scanf������л������
 *�����������
 *����ֵ��int(��������ʵ������)
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-17
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
 *�����������
 *����ֵ��int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2022-04-01
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