/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
	��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
	ʵ��3 Lab3_fun�������躯������������ͷ�ļ�����
ժҪ:
	��ҵ�����ʵ��3
����˵��:
	�ޡ�
ģ����ʷ:
������������2023��4��1�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#define random(x) (rand() % x)	// ��������������к궨��
#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���

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
