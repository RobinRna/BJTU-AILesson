/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放与排序功能相关功能函数的函数声明
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

int cmpArray2D(const void*, const void*);
void sortArray2D(int, confvod*); // 二维数组

int cmpStructArray(const void*, const void*);
void sortStructArray(int, confvod*); // 结构体数组

int cmpFingerArray(const void*, const void*);
void sortFingerArray(int, confvod*); // 结构体指针数组

LINKNODE* getpar(LINKNODE* begin, LINKNODE* end);
void sortLink1(int, confvod*);                 // 链表（冒泡）
void sortLink2(LINKNODE* begin, LINKNODE* end); // 链表（快速排序）
