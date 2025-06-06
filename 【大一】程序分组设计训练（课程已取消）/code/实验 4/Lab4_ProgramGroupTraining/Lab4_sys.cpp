/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 �����Լ졢����ϵͳ��������ʼ��ȫ�ֱ���
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_sys.h"

// ����ȫ�ֱ���
int sys_method;                        // ʵ��4����ģʽ������1��ʾ�Զ�ģʽ��2��ʾ����ģʽ
char filepath[MAX_ARRAY_LEN] = { '\0' }; // ����ģʽ�´����û�������ļ�����·��
int record_num;                        // ����ģʽ�´洢�û���������ݼ�¼����

/*
 *�������ƣ�int syscheck
 *�������ܣ������Լ�
 *�����������
 *����ֵ��int��
 *        ����0��������Լ췢�ִ��󣬽�������
 *        ����1��������Լ�ɹ�����������
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-14
 *          repair by Lifeng Zhang, 2023-05-22
 */
int syscheck()
{
    int count = 0;
    if (access("conf.ini", 0)) // �����ļ�
        count++;
    else
        printf("�����ļ�������1���������ļ�\n");

    if (access("zlf_method.ini", 0)) // ģʽ�ļ�
        count++;
    else
        printf("�����ļ�������2����ģʽ�ļ�\n");

    if (access("Lab3_ProgramGroupTraining.exe", 0)) // Lab3.exe�ļ�
        count++;
    else
        printf("�����ļ�������3����Lab3.exe�ļ�\n");

    if (count == 3)
    {
        printf("�����Լ�ɹ�!\n\n");
        return 1;
    }

    else
    {
        printf("�����ļ�������\n");
        exit(0);
    }
}

/*
 *�������ƣ�int syscheck
 *�������ܣ�����ϵͳ��������ʼ��ȫ�ֱ���
 *���������CONF* data ���ݲ�����
 *          confvod* conf  �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 */

void sysinit(CONF* data, confvod* conf)
{
    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\zlf_method.ini", "r");
    if (err == 0)
        fscanf(fp, "%d", &conf->sys_method); // ����lab4����ģʽ
    else
        printf("��lab4�����ļ�ʧ��\n");
    fclose(fp);

    FILE* fp2;
    errno_t err2;
    err2 = fopen_s(&fp2, "set\\conf.ini", "r");
    if (err2 != 0)
    {
        printf("��lab3�����ļ�ʧ��\n");
        exit(0);
    }
    else
    {
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
    }
    fclose(fp2);

    // ��ʼ��
    record_num = 1;
    conf->Array2D = NULL;
    conf->StructArray = NULL;
    conf->LinkHead = NULL;
}