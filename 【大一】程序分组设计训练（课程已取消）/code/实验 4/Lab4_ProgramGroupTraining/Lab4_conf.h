/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放修改配置文件相关功能函数的函数声明
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
    张鲡沣于2023年5月15日修改本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”
#include "Lab4_HeaderFile.h"
#include "Lab4_fun.h"

void modifyfilesavepath(CONF*, confvod*);
void modifyfilename(CONF*, confvod*);
void modify12(CONF*, confvod*);
void modify3(CONF*, confvod*);
void modifynum(CONF*, confvod*);
void modifysysmethod(CONF*, confvod*);

void freedata(int, CONF*, confvod*);

void free2d(confvod*);
void freestruct(confvod*);
void freeFingerArray(confvod*);
void freelink(confvod*);