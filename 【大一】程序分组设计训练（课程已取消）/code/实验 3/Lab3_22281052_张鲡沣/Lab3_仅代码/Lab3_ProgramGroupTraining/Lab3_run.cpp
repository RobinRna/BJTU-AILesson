/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验3 函数主体部分
摘要:
    作业，配合实验3
其它说明:
    无。
模块历史:
　　张鲡沣于2023年4月1日创建本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年4月4日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab3_run.h"

/*
 *函数名称：run
 *函数功能：实验2函数大体框架
 *输入参数：int argc：命令行参数个数、char* argv[]:命令行参数值
 *返回值：int(此处无实际含义)
 *版本信息：create by Lifeng Zhang, 2023-04-01
 *          repair by Lifeng Zhang, 2023-04-04
 */
int run(int argc, char* argv[])
{
    int number = 0;
    int* num = &number;
    FILE* fp = NULL;
    srand((int)time(0)); // 设置随机数种子

    
    CONF data;//创建相关数据结构体，存储所需要的相关数据

    /*先进行数据的初始化，这样如果在后面的过程中需要使用初始化内容，
     *不用操作，后续直接使用文件中的内容。
     */
    ini_read(&data);

    switch (argc)        // 检查输入参数数目是否正确
    {
    case 1: // 用户无数据处理时
        create_1(fp, num, argv, &data);
        break;

    case 2: // 用户输入一个数据
        create_2(fp, num, argv, &data);
        break;

    case 3: // 用户数据2个数据
        create_3(fp, num, argv, &data);
        break;

    default: // 3个及以上命令行参数，输入参数过多
        printf("Too Many Input Parameters!  输入参数过多！\nProgram ending!  程序结束！\n");
    }
    return 0;
}