/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验2 run函数所需函数申明与所需头文件储存
摘要:
    作业，配合实验2
其它说明:
    无。
模块历史:
　　张鲡沣于2023年3月7日创建本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年3月20日修改本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

void create_1(FILE*, int*, char* argv[]);
void create_2(FILE*, int*, char* argv[]);

int run(int argc, char* argv[]);