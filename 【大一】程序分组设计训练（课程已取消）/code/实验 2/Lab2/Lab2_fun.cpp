/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验2 封装函数集合区
摘要:
    作业，配合实验2
其它说明:
    无。
模块历史:
　　张鲡沣于2023年3月7日创建本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年3月14日修改本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年3月17日修改本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年3月20日修改本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年3月21日修改本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#include "Lab2_fun.h"

/*
 *函数名称：create_1
 *函数功能：用户未输入数据情况、创建文件
 *输入参数：FILE*fp:文件指针、int* num:argv[1]文件条数、char* argv[]:命令行参数值
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2022-03-17
 */
void create_1(FILE* fp, int* num, char* argv[])
{
    int number;
    printf("Please input the date of number  请输入数据行的个数:");
    scanf("%d", &number);
    clearstdin(); // 清缓存，防止爆栈
    if ((fp = fopen("output.txt", "w")) == NULL)
        // 创建一个名称是“output”的txt文档
        printf("Error on open output.txt   未成功创建output.txt文件\n"); // 如果没有成功创建文档，进行报错提示
    else
    {
        *num = number;
        data(fp, num, argv);
    }
}

/*
 *函数名称：create_2
 *函数功能：用户已输入数据情况、创建文件
 *输入参数：FILE*fp:文件指针、int* num:argv[1]文件条数、char* argv[]:命令行参数值
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2022-03-17
 */
void create_2(FILE* fp, int* num, char* argv[])
{
    if (check(argv[1]) == 0) // 用户输入第一个的非数字参数，数据有问题
        printf("Input error!  输入错误！\nProgram ending!  程序结束！\n");
    else // 用户输入正确
    {
        if ((fp = fopen(argv[2], "w")) == NULL)
            // 创建一个名称是输入的agrv[2]的txt文档
            printf("Error on open put.txt    未成功创建output.txt文件\n"); // 如果没有成功创建文档，进行报错提示
        else
        {
            *num = atoi(argv[1]); // 将输入的char型数据转换为int型
            data(fp, num, argv);
        }
    }
}

/*
 *函数名称：data
 *函数功能：进行随机数输出
 *输入参数：FILE*fp:文件指针、int* num:argv[1]文件条数、char* argv[]:命令行参数值
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2022-03-14
 *          repair by Lifeng Zhang, 2022-03-21
 */
void data(FILE* fp, int* num, char* argv[])
{
    int i, data_3[10000][3];
    fprintf(fp, "%d\n", *num); // 输出总的数字个数
    fflush(fp);                // 清缓存，防止爆栈
    for (i = 0; i < *num; i++)// 将数据存入数组
    {
        data_3[i][0] = random(1000); data_3[i][1] = random(1000); data_3[i][2] = random(1000);
    }
    for (i = 0; i < *num; i++)// 将数据数据写入文件
        fprintf(fp, "%d,%d,%d\n", data_3[i][0], data_3[i][1], data_3[i][2]);
    if ((fclose(fp)) == EOF) // 如果没有成功关闭文档，进行报错提示
        printf("Error close the file  文件关闭异常\n");
    
    printf("%d\n", *num);
    for (i = 0; i < *num; i++) //输出数组数据，用于比对
        printf("%d,%d,%d\n", data_3[i][0], data_3[i][1], data_3[i][2]);
}

/*
 *函数名称：clearstdin
 *函数功能：对scanf输入进行缓存清除
 *输入参数：无
 *返回值：int(本程序无实际意义)
 *版本信息：create by Lifeng Zhang, 2022-03-17
 */
int clearstdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 0;
}

/*
 *函数名称：check
 *函数功能：对argv[1]数据是否合法进行检查
 *输入参数：无
 *返回值：int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2022-03-20
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
