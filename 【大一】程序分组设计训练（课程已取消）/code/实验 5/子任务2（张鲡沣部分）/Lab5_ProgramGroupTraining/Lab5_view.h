/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	读入实验5任务1中生成文件
摘要:
	作业，配合实验5
其它说明:
	无。
模块历史:
　　张鲡沣于2023年5月30日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

#include "Lab5_HeaderFile.h"
#include "Lab5_checkfile.h"

void create_html(htmldata*);
void loadfile(htmldata*, int);
void html_open(htmldata*);
void html_basic(FILE*);
