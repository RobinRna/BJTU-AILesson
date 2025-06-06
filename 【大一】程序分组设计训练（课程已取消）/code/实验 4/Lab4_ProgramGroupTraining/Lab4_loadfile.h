/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4存放数据加载相关函数的函数声明
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

#include "Lab4_HeaderFile.h"
#include "lab4_fun.h"

int loadToArray2D(CONF*, confvod*);     // 将数据文件加载到二维数组
int loadToStructArray(CONF*, confvod*); // 将数据文件加载到结构体数组
int loadToFingerArray(CONF*, confvod*); // 将数据文件加载到结构体指针数组
int loadToLink(CONF*, confvod*);        // 将数据文件加载到链表