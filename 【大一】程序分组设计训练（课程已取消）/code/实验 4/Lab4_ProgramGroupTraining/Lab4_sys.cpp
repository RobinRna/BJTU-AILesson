/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 程序自检、加载系统参数及初始化全局变量
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_sys.h"

// 定义全局变量
int sys_method;                        // 实验4工作模式变量，1表示自动模式，2表示交互模式
char filepath[MAX_ARRAY_LEN] = { '\0' }; // 交互模式下储存用户输入的文件储存路径
int record_num;                        // 交互模式下存储用户输入的数据记录条数

/*
 *函数名称：int syscheck
 *函数功能：程序自检
 *输入参数：无
 *返回值：int；
 *        返回0代表程序自检发现错误，结束程序
 *        返回1代表程序自检成功，继续程序
 *版本信息：create by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-14
 *          repair by Lifeng Zhang, 2023-05-22
 */
int syscheck()
{
    int count = 0;
    if (access("conf.ini", 0)) // 配置文件
        count++;
    else
        printf("所需文件不存在1——配置文件\n");

    if (access("zlf_method.ini", 0)) // 模式文件
        count++;
    else
        printf("所需文件不存在2——模式文件\n");

    if (access("Lab3_ProgramGroupTraining.exe", 0)) // Lab3.exe文件
        count++;
    else
        printf("所需文件不存在3——Lab3.exe文件\n");

    if (count == 3)
    {
        printf("程序自检成功!\n\n");
        return 1;
    }

    else
    {
        printf("所需文件不存在\n");
        exit(0);
    }
}

/*
 *函数名称：int syscheck
 *函数功能：加载系统参数及初始化全局变量
 *输入参数：CONF* data 数据参数；
 *          confvod* conf  配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-09
 */

void sysinit(CONF* data, confvod* conf)
{
    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\zlf_method.ini", "r");
    if (err == 0)
        fscanf(fp, "%d", &conf->sys_method); // 加载lab4工作模式
    else
        printf("打开lab4配置文件失败\n");
    fclose(fp);

    FILE* fp2;
    errno_t err2;
    err2 = fopen_s(&fp2, "set\\conf.ini", "r");
    if (err2 != 0)
    {
        printf("打开lab3配置文件失败\n");
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

    // 初始化
    record_num = 1;
    conf->Array2D = NULL;
    conf->StructArray = NULL;
    conf->LinkHead = NULL;
}