/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ���Lab4_fun.cpp�ļ���������ϵͳͷ�ļ�
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���

#define random(x) (rand() % x) // ��������������к궨��

#include "Lab4_HeaderFile.h"

void get_filename(CONF*, confvod*);
void get_filenum(CONF*, confvod*);
int check_seper_file(char*, CONF*, confvod*);

int clearstdin();
int check_num(char*, CONF*, confvod*);
