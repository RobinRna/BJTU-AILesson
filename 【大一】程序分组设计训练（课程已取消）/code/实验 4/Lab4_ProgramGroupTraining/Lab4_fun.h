/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    存放Lab4_fun.cpp文件所需所有系统头文件
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

#define random(x) (rand() % x) // 对随机数函数进行宏定义

#include "Lab4_HeaderFile.h"

void get_filename(CONF*, confvod*);
void get_filenum(CONF*, confvod*);
int check_seper_file(char*, CONF*, confvod*);

int clearstdin();
int check_num(char*, CONF*, confvod*);
