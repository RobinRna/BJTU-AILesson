/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
	版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
	实验3 Lab3_fun函数所需函数申明与所需头文件储存
摘要:
	作业，配合实验3
其它说明:
	无。
模块历史:
　　张鲡沣于2023年4月1日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#define random(x) (rand() % x)	// 对随机数函数进行宏定义
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include "Lab3_data.h"

char user_filename[MAX_STR_LEN];

int run(int argc, char* argv[]);

void ini_read(CONF* data);

void create_1(FILE*, int*, char* argv[], CONF*);
void create_2(FILE*, int*, char* argv[], CONF*);
void create_3(FILE*, int*, char* argv[], CONF*);

void get_filename(CONF*);
void get_filenum(CONF*);
int check_seper_file(char*, CONF*);
int writenum(FILE*, CONF*, char*);
void creat_randnumber_byshuzu(FILE*, CONF*, int a[][3]);
int creat_randnumber_byjiegou(CONF*, DATAITEM*);

int clearstdin();
int check_num(CONF* ,char*);
