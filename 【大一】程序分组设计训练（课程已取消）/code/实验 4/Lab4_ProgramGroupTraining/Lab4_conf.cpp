/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 ������޸������ļ���صĹ��ܺ���
ժҪ:
    ��ҵ�����ʵ��4��
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��14�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_conf.h"

/*
 *�������ƣ�void modifyfilesavepath
 *�������ܣ��޸��ļ��洢·��
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void modifyfilesavepath(CONF* data, confvod* conf)
{
    char filesp[MAX_ARRAY_LEN] = { '\0' };
    while (1)
    {
        printf("��������ȷ���ļ��洢·����\n");
        char c = getchar();
        if (*fgets(filesp, MAX_ARRAY_LEN, stdin) == '\n') // ���û������룬����������
            continue;
        else
        {
            int f = check_seper_file(conf->filepath, data, conf);
            if (f == 1) // �Ϸ�
                break;
            else
                continue;
        }
    }
    strcpy(data->filesavepath, filesp);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("�޸�ʧ��\n");
    fclose(fp);
}

/*
 *�������ƣ�void modifyfilename
 *�������ܣ��޸��ļ���
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void modifyfilename(CONF* data, confvod* conf)
{
    char filename[MAX_ARRAY_LEN] = { '\0' };
    while (1)
    {
        printf("��������ȷ���ļ�����\n");
        char c = getchar();
        if (*fgets(filename, MAX_ARRAY_LEN, stdin) == '\n') // ���û������룬����������
            continue;
        else
        {
            int f = check_seper_file(conf->filepath, data, conf);
            if (f == 1) // �Ϸ�
                break;
            else
                continue;
        }
    }
    strcpy(data->filename, filename);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("�޸�ʧ��\n");
    fclose(fp);
}

/*
 *�������ƣ�void modify12
 *�������ܣ��޸ĵ�һ����Ԫ�صķ�Χ
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void modify12(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("��������һ����Ԫ�ص����޺����ޣ���������ʹ��Ĭ��ֵ��\n");
    while (1)
    {
        int cnt = 0;
        printf("���������ޣ�\n");
        scanf("%s", max);

        printf("���������ޣ�\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
            printf("�������������ޣ�");
        continue;
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("�������������ޣ�");
            continue;
        }
        break;
    }
    if (max[0] != '\n')
        data->maxvalue1 = atoi(max);
    if (max[0] != '\n')
        data->minvalue1 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("�޸�ʧ��\n");
    fclose(fp);
}

/*
 *�������ƣ�void modify3
 *�������ܣ��޸ĵ�����Ԫ�صķ�Χ
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void modify3(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("������������Ԫ�ص����޺����ޣ���������ʹ��Ĭ��ֵ��\n");
    while (1)
    {
        int cnt = 0;
        printf("���������ޣ�\n");
        scanf("%s", max);

        printf("���������ޣ�\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
        {
            printf("�������������ޣ�");
            continue;
        }
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("�������������ޣ�");
            continue;
        }

        break;
    }
    if (max[0] != '\n')
        data->maxvalue2 = atoi(max);
    if (max[0] != '\n')
        data->minvalue2 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("�޸�ʧ��\n");
    fclose(fp);
}

/*
 *�������ƣ�void modifynum
 *�������ܣ��޸����ݼ�¼�����ķ�Χ
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void modifynum(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("�����������ݼ�¼���������޺����ޣ���������ʹ��Ĭ��ֵ��\n");
    while (1)
    {
        int cnt = 0;
        printf("���������ޣ�\n");
        scanf("%s", max);

        printf("���������ޣ�\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
        {
            printf("�������������ޣ�");
            continue;
        }
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("�������������ޣ�");
            continue;
        }
        break;
    }
    if (max[0] != '\n')
        data->recordcount1 = atoi(max);
    if (max[0] != '\n')
        data->recordcount2 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("�޸�ʧ��\n");
    fclose(fp);
}

/*
 *�������ƣ�void modifysysmethod
 *�������ܣ��޸�ʵ��4����ģʽ
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 */
void modifysysmethod(CONF* data, confvod* conf)
{
    int n;
    printf("������ʵ��4�Ĺ���ģʽ��1�����Զ�ģʽ��2������ģʽ����\n");
    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 1 && n <= 2)
        {
            FILE* fp;
            errno_t err;
            err = fopen_s(&fp, "set\\zlf_method.ini", "w");
            if (err == 0)
            {
                fprintf(fp, "%d\n", n);
                printf("���޸�zlf_method.iniģʽ�ļ����ã�\n");
            }
            else
                printf("��lab4�����ļ�ʧ��\n");
            fclose(fp);
            break;
        }
        else
            printf("���������룺\n");
    }
}

/*
 *�������ƣ�void freedata
 *�������ܣ��ͷŶ�̬������ڴ棬���³�ʼ��ȫ�ֱ���
 *���������int n ѡ�
 *          CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-31
 */
void freedata(int n, CONF* data, confvod* conf)
{
    if (n == 1 || n == 2 || n == 6 || n == 10)
        free2d(conf);

    if (n == 1 || n == 3 || n == 7 || n == 11)
        freestruct(conf);

    if (n == 4 || n == 8 || n == 12)
        freeFingerArray(conf);

    if (n == 5 || n == 9 || n == 13)
        freelink(conf);
}

/*
 *�������ƣ�void free2d
 *�������ܣ��ͷŶ�ά���������
 *���������confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-21
 */
void free2d(confvod* conf)
{
    free(conf->Array2D);
    conf->Array2D = NULL;
}

/*
 *�������ƣ�void freestruct
 *�������ܣ��ͷŽṹ�����������
 *���������confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-21
 */
void freestruct(confvod* conf)
{
    free(conf->StructArray);
    conf->StructArray = NULL;
}

/*
 *�������ƣ�void freeFingerArray
 *�������ܣ��ͷŽṹ��ָ�����������
 *���������confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-21
 */
void freeFingerArray(confvod* conf)
{
    for (int i = 0; i < conf->record_num; ++i)
        free(conf->FingerArray[i]);
    conf->FingerArray = NULL;
}

/*
 *�������ƣ�void freelink
 *�������ܣ��ͷ����������
 *���������confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-21
 */
void freelink(confvod* conf)
{
    LINKNODE* p = conf->LinkHead;
    // LINKNODE* q = p->next;
    for (int i = 0; i < conf->record_num; i++)
    {
        LINKNODE* q = p->next;
        free(p);
        p = q;

        conf->LinkHead = NULL;
    }
}