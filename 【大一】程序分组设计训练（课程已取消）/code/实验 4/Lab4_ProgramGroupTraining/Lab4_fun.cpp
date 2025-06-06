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

#include "Lab4_fun.h"

/*
 *�������ƣ�get_filenum
 *�������ܣ�ͨ�����������ȡ�ļ���¼����
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04��Lab3�г���
 *           repair by Lifeng Zhang, 2023-04-18
 */
void get_filenum(CONF* data, confvod* conf)
{
    char user_number[MAX_STR_LEN] = "no";
    printf("\n����������Ҫ���ɵ�������������ʹ�������ļ�/�����в���������no��:\n");
    scanf("%s", user_number);
    clearstdin();

    // �ж��û��Ƿ�����Ϸ�
    if (strcmp(user_number, "no") != 0)
    {
        while (check_num(user_number,data,conf) == 0)
        {
            printf("Illegal Number!!  �������ַǷ�!!:\n");
            printf("Please Re-enter!  ����������:\n");
            scanf("%s", user_number);
            clearstdin();
            if (strcmp(user_number, "no") == 0)
                break;
        }
        if (check_num(user_number, data, conf) != 0)
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
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-04��Lab3�г���
 *          repair by Lifeng Zhang, 2023-04-18
 */

void get_filename(CONF* data, confvod* conf)
{

    printf("\n����������Ҫ���ɵļ�¼�ļ����ƣ��ɴ��о���·�������·��������no��ʾʹ������Ĭ���ļ�����:\n");
    scanf("%s", conf->user_filename);
    clearstdin();

    // �ж��û��Ƿ�����Ϸ�
    if (strcmp(conf->user_filename, "no") != 0)
    {
        while (check_seper_file(conf->user_filename, data, conf) == 0)
        {
            printf("Illegal path or file name!!  ����·�����ļ����Ƿ�!!:\n");
            printf("Please Re-enter!  ����������:\n");
            scanf("%s", conf->user_filename);
            clearstdin();
            if (strcmp(conf->user_filename, "no") == 0)
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
 *���������char* str:�ļ�·�����ļ���
 *          CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��  int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2023-04-01��Lab3�г���
 *          repair by Lifeng Zhang, 2023-04-04
 */
int check_seper_file(char* str, CONF* data, confvod* conf)
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
    char all[MAX_STR_LEN];

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
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);

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
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);

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
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);
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
 *�����������
 *����ֵ��int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2022-04-01��Lab3�г���
 *          repair by Lifeng Zhang, 2023-04-18
 */
int check_num(char* str, CONF* data, confvod* conf)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    data->number = atoi(str);
    conf->record_num = atoi(str);
    return 1;
}