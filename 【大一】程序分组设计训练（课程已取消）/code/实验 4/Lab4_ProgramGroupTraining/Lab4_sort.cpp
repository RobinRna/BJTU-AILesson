/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 �������������صĹ��ܺ���
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    ��
ģ����ʷ:
������������2023��5��16�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_sort.h"

clock_t start, stop;
double duration;

/*
 *�������ƣ�cmpArray2D
 *�������ܣ���ά��������ȽϺ���
 *���������const void* a, const void* b
 *����ֵ��int
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 */
int cmpArray2D(const void* a, const void* b)
{
    return (*((int*)a + 2) - *((int*)b + 2));
}
/*
 *�������ƣ�void sortArray2D
 *�������ܣ���ά��������qsort����
 *���������int n ������������
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortArray2D(int n, confvod* conf)
{
    start = clock();
    qsort(conf->Array2D, n, 3 * sizeof(conf->Array2D[0]), cmpArray2D);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n��ά����������ʱ��%f s \n\n", duration);
    system("pause");  //��ͣ��ʾ���
}

/*
 *�������ƣ�int cmpStructArray
 *�������ܣ��ṹ����������ȽϺ���
 *���������const void* a, const void* b
 *����ֵ��int
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 */
int cmpStructArray(const void* a, const void* b)
{
    DATAITEM* aa = (DATAITEM*)a;
    DATAITEM* bb = (DATAITEM*)b;
    return ((aa->item3) > (bb->item3) ? 1 : -1);
}
/*
 *�������ƣ�void sortStructArray
 *�������ܣ��ṹ����������qsort����
 *���������int n ������������
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortStructArray(int n, confvod* conf)
{
    start = clock();
    qsort(conf->StructArray, n, sizeof(conf->StructArray[0]), cmpStructArray);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n�ṹ������������ʱ��%f s \n\n", duration);
    system("pause");  //��ͣ��ʾ���
}

/*
 *�������ƣ�int cmpFingerArray
 *�������ܣ��ṹ��ָ��������������ȽϺ���
 *���������const void* a, const void* b
 *����ֵ��int
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 */
int cmpFingerArray(const void* a, const void* b)
{
    DATAITEM** aa = (DATAITEM**)a;
    DATAITEM** bb = (DATAITEM**)b;
    return (((*aa)->item3) > ((*bb)->item3) ? 1 : -1);
}
/*
 *�������ƣ�void sortFingerArray
 *�������ܣ��ṹ��ָ����������qsort����
 *���������int n ������������
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortFingerArray(int n, confvod* conf)
{
    start = clock();
    qsort(conf->FingerArray, n, sizeof(conf->FingerArray[0]), cmpFingerArray);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n�ṹ��ָ������������ʱ��%f s \n\n", duration);
    system("pause");  //��ͣ��ʾ���
}

/*
 *�������ƣ�sortLink1
 *�������ܣ��������򡪡�ð������
 *���������int n ������������
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortLink1(int n, confvod* conf)
{
    int i, j, cnt = 0;
    LINKNODE* A, * B = NULL, * t = NULL;
    A = (LINKNODE*)malloc(sizeof(LINKNODE));
    start = clock();
    for (i = 0; i < n; ++i)
    {
        A = conf->LinkHead->next; // Aָ���һ�����
        B = A->next;
        t = conf->LinkHead;
        for (j = 0; j < n - i - 1; ++j)
        {
            if (A->record.item3 < B->record.item3)
            {
                A->next = B->next;
                B->next = A;
                t->next = B;
            }
            t = t->next;
            A = t->next;
            B = A->next;
        }
    }
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n�������򡪡�ð��������ʱ��%f s \n\n", duration);
    system("pause");  //��ͣ��ʾ���
}

/*
 *�������ƣ�LINKNODE* getpar
 *�������ܣ��������򡪡����űȽϳ���1
 *���������LINKNODE* begin, LINKNODE* end
 *����ֵ��LINKNODE*
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 */
LINKNODE* getpar(LINKNODE* begin, LINKNODE* end)
{
    int key = begin->record.item3;
    int t;
    LINKNODE* p = begin;
    LINKNODE* q = p->next;

    while (q != end)
    {
        if (q->record.item3 > key)
        {
            p = p->next;
            // ����ֵ����
            t = p->record.item1;
            p->record.item1 = q->record.item1;
            q->record.item1 = t;
            t = p->record.item2;
            p->record.item2 = q->record.item2;
            q->record.item2 = t;
            t = p->record.item3;
            p->record.item3 = q->record.item3;
            q->record.item3 = t;
        }
        q = q->next;
    }
    t = p->record.item1;
    p->record.item1 = begin->record.item1;
    begin->record.item1 = t;
    t = p->record.item2;
    p->record.item2 = begin->record.item2;
    begin->record.item2 = t;
    t = p->record.item3;
    p->record.item3 = begin->record.item3;
    begin->record.item3 = t;
    return p;
}

/*
 *�������ƣ�void sortLink2
 *�������ܣ��������򡪡����űȽϳ���2
 *���������LINKNODE* begin, LINKNODE* end
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortLink2(LINKNODE* begin, LINKNODE* end) // ����ֵ����
{

    if (begin != end) // �ݹ�
    {
        

        LINKNODE* par = getpar(begin, end);
        sortLink2(begin, par);
        sortLink2(par->next, end);
    }

}
