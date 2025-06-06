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

#include "Lab4_call.h"

/*
 *函数名称：void callLab3
 *函数功能：调用实验3生成数据文件
 *输入参数：int n 生成数据条数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void callLab3(CONF* data, confvod* conf)
{
    char commond[256] = { '\0' };
    if (conf->sys_method == 1)       //自动模式
    {
        sprintf(commond, "D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_4_Experiments/Lab4_ProgramGroupTraining/set/Lab3_ProgramGroupTraining.exe");
        system(commond);
    }
    else if (conf->sys_method == 2)  //交互模式
    {
        get_filename(data, conf);
        fflush(stdin);  //清缓存
        get_filenum(data, conf);
        fflush(stdin);  //清缓存
        sprintf(commond, "D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_4_Experiments/Lab4_ProgramGroupTraining/set/Lab3_ProgramGroupTraining.exe %d %s", conf->record_num, conf->filepath);
        system(commond);
    }
    else
        printf("文件不存在，请运行1项目");
    
}