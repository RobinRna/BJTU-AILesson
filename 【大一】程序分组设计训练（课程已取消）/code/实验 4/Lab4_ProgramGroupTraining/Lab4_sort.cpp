/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放与排序功能相关的功能函数
摘要:
    作业，配合实验4
其它说明:
    无
模块历史:
　　张鲡沣于2023年5月16日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_sort.h"

clock_t start, stop;
double duration;

/*
 *函数名称：cmpArray2D
 *函数功能：二维数组排序比较函数
 *输入参数：const void* a, const void* b
 *返回值：int
 *版本信息：create by Lifeng Zhang, 2023-05-16
 */
int cmpArray2D(const void* a, const void* b)
{
    return (*((int*)a + 2) - *((int*)b + 2));
}
/*
 *函数名称：void sortArray2D
 *函数功能：二维数组排序qsort函数
 *输入参数：int n 生成数据条数
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortArray2D(int n, confvod* conf)
{
    start = clock();
    qsort(conf->Array2D, n, 3 * sizeof(conf->Array2D[0]), cmpArray2D);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n二维数组排序用时：%f s \n\n", duration);
    system("pause");  //暂停显示结果
}

/*
 *函数名称：int cmpStructArray
 *函数功能：结构体数组排序比较函数
 *输入参数：const void* a, const void* b
 *返回值：int
 *版本信息：create by Lifeng Zhang, 2023-05-16
 */
int cmpStructArray(const void* a, const void* b)
{
    DATAITEM* aa = (DATAITEM*)a;
    DATAITEM* bb = (DATAITEM*)b;
    return ((aa->item3) > (bb->item3) ? 1 : -1);
}
/*
 *函数名称：void sortStructArray
 *函数功能：结构体数组排序qsort函数
 *输入参数：int n 生成数据条数
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortStructArray(int n, confvod* conf)
{
    start = clock();
    qsort(conf->StructArray, n, sizeof(conf->StructArray[0]), cmpStructArray);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n结构体数组排序用时：%f s \n\n", duration);
    system("pause");  //暂停显示结果
}

/*
 *函数名称：int cmpFingerArray
 *函数功能：结构体指针数组排序排序比较函数
 *输入参数：const void* a, const void* b
 *返回值：int
 *版本信息：create by Lifeng Zhang, 2023-05-16
 */
int cmpFingerArray(const void* a, const void* b)
{
    DATAITEM** aa = (DATAITEM**)a;
    DATAITEM** bb = (DATAITEM**)b;
    return (((*aa)->item3) > ((*bb)->item3) ? 1 : -1);
}
/*
 *函数名称：void sortFingerArray
 *函数功能：结构体指针数组排序qsort函数
 *输入参数：int n 生成数据条数
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortFingerArray(int n, confvod* conf)
{
    start = clock();
    qsort(conf->FingerArray, n, sizeof(conf->FingerArray[0]), cmpFingerArray);
    stop = clock();
    duration = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\n\n结构体指针数组排序用时：%f s \n\n", duration);
    system("pause");  //暂停显示结果
}

/*
 *函数名称：sortLink1
 *函数功能：链表排序——冒泡排序
 *输入参数：int n 生成数据条数
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
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
        A = conf->LinkHead->next; // A指向第一个结点
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
    printf("\n\n链表排序——冒泡排序用时：%f s \n\n", duration);
    system("pause");  //暂停显示结果
}

/*
 *函数名称：LINKNODE* getpar
 *函数功能：链表排序——快排比较程序1
 *输入参数：LINKNODE* begin, LINKNODE* end
 *返回值：LINKNODE*
 *版本信息：create by Lifeng Zhang, 2023-05-16
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
            // 进行值交换
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
 *函数名称：void sortLink2
 *函数功能：链表排序——快排比较程序2
 *输入参数：LINKNODE* begin, LINKNODE* end
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-22
 */
void sortLink2(LINKNODE* begin, LINKNODE* end) // 进行值交换
{

    if (begin != end) // 递归
    {
        

        LINKNODE* par = getpar(begin, end);
        sortLink2(begin, par);
        sortLink2(par->next, end);
    }

}
