/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放数据显示模块相关函数的函数声明
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

int showmainmenu(confvod*);          // 显示输出实验4程序的主菜单
void showArray2D(int, confvod*);     // 将二维数组显示到屏幕上
void showStructArray(int, confvod*); // 将结构体数组显示到屏幕上
void showFingerArray(int, confvod*); // 将结构体指针数组显示到屏幕上
void showLink(int, confvod*);        // 将链表显示到屏幕上
int show14menu();                    // 显示功能14的修改菜单
