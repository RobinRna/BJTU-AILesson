/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��3 �洢Lab3_run�����ĺ���ʵ��
ժҪ:
    ��ҵ�����ʵ��3
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��4��1�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Lab3_data.h"

void create_1(FILE*, int*, char* argv[], CONF* data);
void create_2(FILE*, int*, char* argv[], CONF* data);
void create_3(FILE*, int*, char* argv[], CONF* data);

int run(int argc, char* argv[]);

void ini_read(CONF* data);