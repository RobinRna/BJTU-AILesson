/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 �������������ع��ܺ����ĺ�������
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���

#include "Lab4_HeaderFile.h"

int cmpArray2D(const void*, const void*);
void sortArray2D(int, confvod*); // ��ά����

int cmpStructArray(const void*, const void*);
void sortStructArray(int, confvod*); // �ṹ������

int cmpFingerArray(const void*, const void*);
void sortFingerArray(int, confvod*); // �ṹ��ָ������

LINKNODE* getpar(LINKNODE* begin, LINKNODE* end);
void sortLink1(int, confvod*);                 // ����ð�ݣ�
void sortLink2(LINKNODE* begin, LINKNODE* end); // ������������
