/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��2 ��װ����������
ժҪ:
    ��ҵ�����ʵ��2
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��3��7�մ�����ģ�飬email: 22281052@bjtu.edu.cn
    ��������2023��3��14���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
    ��������2023��3��17���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
    ��������2023��3��20���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
    ��������2023��3��21���޸ı�ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#include "Lab2_fun.h"

/*
 *�������ƣ�create_1
 *�������ܣ��û�δ������������������ļ�
 *���������FILE*fp:�ļ�ָ�롢int* num:argv[1]�ļ�������char* argv[]:�����в���ֵ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-17
 */
void create_1(FILE* fp, int* num, char* argv[])
{
    int number;
    printf("Please input the date of number  �����������еĸ���:");
    scanf("%d", &number);
    clearstdin(); // �建�棬��ֹ��ջ
    if ((fp = fopen("output.txt", "w")) == NULL)
        // ����һ�������ǡ�output����txt�ĵ�
        printf("Error on open output.txt   δ�ɹ�����output.txt�ļ�\n"); // ���û�гɹ������ĵ������б�����ʾ
    else
    {
        *num = number;
        data(fp, num, argv);
    }
}

/*
 *�������ƣ�create_2
 *�������ܣ��û���������������������ļ�
 *���������FILE*fp:�ļ�ָ�롢int* num:argv[1]�ļ�������char* argv[]:�����в���ֵ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-17
 */
void create_2(FILE* fp, int* num, char* argv[])
{
    if (check(argv[1]) == 0) // �û������һ���ķ����ֲ���������������
        printf("Input error!  �������\nProgram ending!  ���������\n");
    else // �û�������ȷ
    {
        if ((fp = fopen(argv[2], "w")) == NULL)
            // ����һ�������������agrv[2]��txt�ĵ�
            printf("Error on open put.txt    δ�ɹ�����output.txt�ļ�\n"); // ���û�гɹ������ĵ������б�����ʾ
        else
        {
            *num = atoi(argv[1]); // �������char������ת��Ϊint��
            data(fp, num, argv);
        }
    }
}

/*
 *�������ƣ�data
 *�������ܣ�������������
 *���������FILE*fp:�ļ�ָ�롢int* num:argv[1]�ļ�������char* argv[]:�����в���ֵ
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-14
 *          repair by Lifeng Zhang, 2022-03-21
 */
void data(FILE* fp, int* num, char* argv[])
{
    int i, data_3[10000][3];
    fprintf(fp, "%d\n", *num); // ����ܵ����ָ���
    fflush(fp);                // �建�棬��ֹ��ջ
    for (i = 0; i < *num; i++)// �����ݴ�������
    {
        data_3[i][0] = random(1000); data_3[i][1] = random(1000); data_3[i][2] = random(1000);
    }
    for (i = 0; i < *num; i++)// ����������д���ļ�
        fprintf(fp, "%d,%d,%d\n", data_3[i][0], data_3[i][1], data_3[i][2]);
    if ((fclose(fp)) == EOF) // ���û�гɹ��ر��ĵ������б�����ʾ
        printf("Error close the file  �ļ��ر��쳣\n");
    
    printf("%d\n", *num);
    for (i = 0; i < *num; i++) //����������ݣ����ڱȶ�
        printf("%d,%d,%d\n", data_3[i][0], data_3[i][1], data_3[i][2]);
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
 *�������ƣ�check
 *�������ܣ���argv[1]�����Ƿ�Ϸ����м��
 *�����������
 *����ֵ��int,�������Ϸ�������ֵΪ1,����Ϊ0
 *�汾��Ϣ��create by Lifeng Zhang, 2022-03-20
 */
int check(char* str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
