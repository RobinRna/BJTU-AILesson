/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 主入口函数
摘要:
    作业，配合实验2
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_main.h"

/*
 *函数名称：run
 *函数功能：实验4函数大体框架
 *输入参数：int argc：命令行参数个数、char* argv[]:命令行参数值
 *返回值：int(无实际含义)
 *版本信息：create by Lifeng Zhang, 2023-05-05
 *          repair by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-14
 *          repair by Lifeng Zhang, 2023-05-21
 */
int run(int argc, char* argv[])
{
    int num;
    syscheck(); // 程序自检

    CONF* data = (CONF*)malloc(sizeof(CONF));
    confvod* conf = (confvod*)malloc(sizeof(confvod));

    sysinit(data, conf); // 初始化及加载系统参数

    FILE* fp = NULL;
    srand((int)time(0)); // 设置随机数种子

    clock_t start, stop;
    double duration;


    /*先进行数据的初始化，这样如果在后面的过程中需要使用初始化内容，
     *不用操作，后续直接使用文件中的内容。
     */

    while (true)
    {
        int n;
        n = showmainmenu(conf); // 显示菜单
        if (n == 0)
            break;
        else if (n == 1)
        {
            callLab3(data, conf);
        }
        else if (n == 2)
        {
            num = loadToArray2D(data, conf); // 将数据文件加载到二维数组
            showArray2D(num, conf);
        }
        else if (n == 3)
        {
            num = loadToStructArray(data, conf);
            showStructArray(num, conf);
        }
        else if (n == 4)
        {
            num = loadToFingerArray(data, conf);
            showFingerArray(num, conf);
        }
        else if (n == 5)
        {
            num = loadToLink(data, conf);
            showLink(num, conf);
        }
        else if (n == 6)
        {
            callLab3(data, conf);
            num = loadToArray2D(data, conf); // 将数据文件加载到二维数组
            showArray2D(num, conf);
        }
        else if (n == 7)
        {
            callLab3(data, conf);
            num = loadToStructArray(data, conf);
            showStructArray(num, conf);
        }
        else if (n == 8)
        {
            callLab3(data, conf);
            num = loadToFingerArray(data, conf);
            showFingerArray(num, conf);
        }
        else if (n == 9)
        {
            callLab3(data, conf);
            num = loadToLink(data, conf);
            showLink(num, conf);
        }
        else if (n == 10)
        {
            callLab3(data, conf);
            num = loadToArray2D(data, conf); // 将数据文件加载到二维数组
            sortArray2D(num, conf);
            showArray2D(num, conf);
        }
        else if (n == 11)
        {
            callLab3(data, conf);
            num = loadToStructArray(data, conf);
            sortStructArray(num, conf);
            showStructArray(num, conf);
        }
        else if (n == 12)
        {
            callLab3(data, conf);
            num = loadToFingerArray(data, conf);
            sortFingerArray(num, conf);
            showFingerArray(num, conf);
        }
        else if (n == 13)
        {
            callLab3(data, conf);
            num = loadToLink(data, conf);
            sortLink1(num, conf);  //冒泡
            
            // 快排
            /*
            start = clock();
            sortLink2(conf->LinkHead->next, NULL);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("\n链表排序——快排比较程序用时：%f s \n", duration);
            system("pause");  //暂停显示结果 
            */

            showLink(num, conf);
        }

        else if (n == 14)
        {
            while (true)
            {
                int m;
                m = show14menu();
                if (m == 0)
                    break;
                else if (m == 1)
                    modifyfilesavepath(data, conf);
                else if (m == 2)
                    modifyfilename(data, conf);
                else if (m == 3)
                    modify12(data, conf);
                else if (m == 4)
                    modify3(data, conf);
                else if (m == 5)
                    modifynum(data, conf);
                else if (m == 6)
                    modifysysmethod(data, conf);
                else
                    printf("请重新输入：\n");
            }
        }
        else
        {
            printf("请重新输入：\n");
        }
        // 释放动态申请的内存，重新初始化全局变量
        freedata(n, data, conf);
        fflush(stdin);  //清缓存
    }
    return 0;
}