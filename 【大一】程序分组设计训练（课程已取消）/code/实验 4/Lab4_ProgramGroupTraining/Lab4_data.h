/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ���ʵ��4��������Ľṹ������������������ȫ�ֱ�������
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // ��ֹVS2022�汾��Ϊ����ȫ�Ա���

#define MAX_ARRAY_LEN 4000
#define MAX_STR_LEN 4000

typedef struct configinfo
{
    char filesavepath[MAX_ARRAY_LEN]; // ���ڴ�����ݼ�¼�ļ��Ĵ洢Ŀ¼
    char filename[MAX_ARRAY_LEN];     // ���ڴ洢���ݼ�¼�ļ����ļ�����Ϣ
    int number;                       // ���ڴ�����ɵļ�¼����
    int maxvalue1;                    // ���ڴ�����ɵ����ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������
    int minvalue1;                    // ���ڴ�����ɵ����ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������
    int maxvalue2;                    // ���ڴ�������ɵ����ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������
    int minvalue2;                    // ���ڴ�������ɵ����ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������
    int recordcount1;                 // ���ڴ�����ݼ�¼�ļ���Ҫ������ɼ�¼����ʱ����ֵ������
    int recordcount2;                 // ���ڴ�����ݼ�¼�ļ���Ҫ������ɼ�¼����ʱ����ֵ������
} CONF;

typedef struct DataItem
{
    int item1; // ���ݼ�¼��Ԫ���һ��Ԫ��
    int item2; // ���ݼ�¼��Ԫ��ڶ���Ԫ��
    int item3; // ���ݼ�¼��Ԫ�������Ԫ��
} DATAITEM;

// ����
typedef struct LinkNode
{
    DATAITEM record;
    struct LinkNode* next; // ָ����һ��λ��
} LINKNODE;

// ȫ�ֱ���������

typedef struct Conf
{
    int sys_method;               // ʵ��4����ģʽ������1��ʾ�Զ�ģʽ��2��ʾ����ģʽ
    char filepath[MAX_ARRAY_LEN]; // ����ģʽ�´����û�������ļ�����·��
    int record_num;               // ����ģʽ�´洢�û���������ݼ�¼����
    int* Array2D;                 // ��ά����
    DATAITEM* StructArray;        // �ṹ��������ָ��
    DATAITEM** FingerArray;       // ָ��������ָ��
    LINKNODE* LinkHead;           // ����ͷָ��

    char user_filename[MAX_STR_LEN];
} confvod;