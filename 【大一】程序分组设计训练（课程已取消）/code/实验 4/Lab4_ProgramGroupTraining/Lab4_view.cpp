/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 进行交互模式
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_view.h"


/*
 *函数名称：int showmainmenu
 *函数功能：显示输出实验4程序的主菜单
 *输入参数：confvod* conf 配置文件参数
 *返回值：int 返回选项
 *版本信息：create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-22
 */
int showmainmenu(confvod* conf)
{
    int n;

    printf("张鲡沣的实验4程序：\n");
    printf("1.调用实验3程序生成记录文件\n");
    printf("2.读取指定数据记录文件（二维数组存储方式）\n");
    printf("3.读取指定数据记录文件（结构体数组存储方式）\n");
    printf("4.读取指定数据记录文件（指针数组存储方式）\n");
    printf("5.读取指定数据记录文件（链表存储方式）\n");
    printf("6.调用实验3程序生成记录文件，同时读取数据记录文件（二维数组存储方式）\n");
    printf("7.调用实验3程序生成记录文件，同时读取数据记录文件（结构体数组存储方式）\n");
    printf("8.调用实验3程序生成记录文件，同时读取数据记录文件（指针数组存储方式）\n");
    printf("9.调用实验3程序生成记录文件，同时读取数据记录文件（链表存储方式）\n");
    printf("10.调用实验3程序生成记录文件，同时读取数据记录文件并排序（二维数组存储方式）\n");
    printf("11.调用实验3程序生成记录文件，同时读取数据记录文件并排序（结构体数组存储方式）\n");
    printf("12.调用实验3程序生成记录文件，同时读取数据记录文件并排序（指针数组存储方式）\n");
    printf("13.调用实验3程序生成记录文件，同时读取数据记录文件并排序（链表存储方式）\n");
    printf("14.重新设置配置参数值\n");
    printf("0.退出\n");
    printf("请输入您想要执行的程序序号:\n");

    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 0 && n <= 14)
            return n;
        else
            printf("输入错误请重新输入:\n");
    }
}

/*
 *函数名称：void showArray2D
 *函数功能：将二维数组显示到屏幕上
 *输入参数：int n 生成数据条数, confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showArray2D(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", *(conf->Array2D + i * 3), *(conf->Array2D + i * 3 + 1), *(conf->Array2D + i * 3 + 2));
}

/*
 *函数名称：void showStructArray
 *函数功能：将结构体数组显示到屏幕上
 *输入参数：int n 生成数据条数, confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showStructArray(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", (conf->StructArray + i)->item1, (conf->StructArray + i)->item2, (conf->StructArray + i)->item3);
}

/*
 *函数名称：void showFingerArray
 *函数功能：将结构体指针数组显示到屏幕上
 *输入参数：int n 生成数据条数, confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-21
 */
void showFingerArray(int n, confvod* conf)
{
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", conf->FingerArray[i]->item1, conf->FingerArray[i]->item2, conf->FingerArray[i]->item3);
}

/*
 *函数名称：void showLink
 *函数功能：将链表显示到屏幕上
 *输入参数：int n 生成数据条数, confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-09
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
 *函数名称：int show14menu
 *函数功能：显示功能14的修改菜单
 *输入参数：无
 *返回值：int 返回选项序号；
 *版本信息：create by Lifeng Zhang, 2023-05-09
 */
int show14menu()
{
    int n;

    printf("（进入修改模式）请输入想要选择的功能：\n");
    printf("1.修改默认文件存储目录\n");
    printf("2.修改默认文件名\n");
    printf("3.修改第一、二个元素的范围\n");
    printf("4.修改第三个元素的范围\n");
    printf("5.修改数据记录条数的范围\n");
    printf("6.修改实验4的工作模式\n");
    printf("0.退出修改模式\n");

    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 0 && n <= 6)
            return n;
        else
            printf("输入错误请重新输入：");
    }
}