/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 ���н���ģʽ
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_view.h"


/*
 *�������ƣ�int showmainmenu
 *�������ܣ���ʾ���ʵ��4��������˵�
 *���������confvod* conf �����ļ�����
 *����ֵ��int ����ѡ��
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-22
 */
int showmainmenu(confvod* conf)
{
    int n;

    printf("�������ʵ��4����\n");
    printf("1.����ʵ��3�������ɼ�¼�ļ�\n");
    printf("2.��ȡָ�����ݼ�¼�ļ�����ά����洢��ʽ��\n");
    printf("3.��ȡָ�����ݼ�¼�ļ����ṹ������洢��ʽ��\n");
    printf("4.��ȡָ�����ݼ�¼�ļ���ָ������洢��ʽ��\n");
    printf("5.��ȡָ�����ݼ�¼�ļ�������洢��ʽ��\n");
    printf("6.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����ά����洢��ʽ��\n");
    printf("7.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ����ṹ������洢��ʽ��\n");
    printf("8.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ���ָ������洢��ʽ��\n");
    printf("9.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������洢��ʽ��\n");
    printf("10.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨶�ά����洢��ʽ��\n");
    printf("11.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ������򣨽ṹ������洢��ʽ��\n");
    printf("12.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�������ָ������洢��ʽ��\n");
    printf("13.����ʵ��3�������ɼ�¼�ļ���ͬʱ��ȡ���ݼ�¼�ļ�����������洢��ʽ��\n");
    printf("14.�����������ò���ֵ\n");
    printf("0.�˳�\n");
    printf("����������Ҫִ�еĳ������:\n");

    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 0 && n <= 14)
            return n;
        else
            printf("�����������������:\n");
    }
}

/*
 *�������ƣ�void showArray2D
 *�������ܣ�����ά������ʾ����Ļ��
 *���������int n ������������, confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showArray2D(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", *(conf->Array2D + i * 3), *(conf->Array2D + i * 3 + 1), *(conf->Array2D + i * 3 + 2));
}

/*
 *�������ƣ�void showStructArray
 *�������ܣ����ṹ��������ʾ����Ļ��
 *���������int n ������������, confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showStructArray(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", (conf->StructArray + i)->item1, (conf->StructArray + i)->item2, (conf->StructArray + i)->item3);
}

/*
 *�������ƣ�void showFingerArray
 *�������ܣ����ṹ��ָ��������ʾ����Ļ��
 *���������int n ������������, confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showFingerArray(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", conf->FingerArray[i]->item1, conf->FingerArray[i]->item2, conf->FingerArray[i]->item3);
}

/*
 *�������ƣ�void showLink
 *�������ܣ���������ʾ����Ļ��
 *���������int n ������������, confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showLink(int n, confvod* conf)
{
    printf("%d\n", n);
    LINKNODE* t = NULL;
    for (int i = 0; i <= n; ++i)
    {
        if (t == NULL)
        {
            t = conf->LinkHead;
            continue;
        }
        else
            t = t->next;

        printf("%d %d %d\n", t->record.item1, t->record.item2, t->record.item3);
    }
}

/*
 *�������ƣ�int show14menu
 *�������ܣ���ʾ����14���޸Ĳ˵�
 *�����������
 *����ֵ��int ����ѡ����ţ�
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-09
 */
int show14menu()
{
    int n;

    printf("�������޸�ģʽ����������Ҫѡ��Ĺ��ܣ�\n");
    printf("1.�޸�Ĭ���ļ��洢Ŀ¼\n");
    printf("2.�޸�Ĭ���ļ���\n");
    printf("3.�޸ĵ�һ������Ԫ�صķ�Χ\n");
    printf("4.�޸ĵ�����Ԫ�صķ�Χ\n");
    printf("5.�޸����ݼ�¼�����ķ�Χ\n");
    printf("6.�޸�ʵ��4�Ĺ���ģʽ\n");
    printf("0.�˳��޸�ģʽ\n");

    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 0 && n <= 6)
            return n;
        else
            printf("����������������룺");
    }
}