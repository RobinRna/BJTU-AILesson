/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    存放实验4程序所需的结构体声明、常量声明及全局变量声明
摘要:
    作业，配合实验4
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#pragma once
#pragma warning(disable : 4996) // 防止VS2022版本因为“安全性报错”

#define MAX_ARRAY_LEN 4000
#define MAX_STR_LEN 4000

typedef struct configinfo
{
    char filesavepath[MAX_ARRAY_LEN]; // 用于存放数据记录文件的存储目录
    char filename[MAX_ARRAY_LEN];     // 用于存储数据记录文件的文件名信息
    int number;                       // 用于存放生成的记录条数
    int maxvalue1;                    // 用于存放生成的数据记录三元组中第1、2个元素取值的上限
    int minvalue1;                    // 用于存放生成的数据记录三元组中第1、2个元素取值的下限
    int maxvalue2;                    // 用于存放中生成的数据记录三元组中第3个元素取值的上限
    int minvalue2;                    // 用于存放中生成的数据记录三元组中第3个元素取值的下限
    int recordcount1;                 // 用于存放数据记录文件需要随机生成记录条数时条数值的上限
    int recordcount2;                 // 用于存放数据记录文件需要随机生成记录条数时条数值的下限
} CONF;

typedef struct DataItem
{
    int item1; // 数据记录三元组第一个元素
    int item2; // 数据记录三元组第二个元素
    int item3; // 数据记录三元组第三个元素
} DATAITEM;

// 链表
typedef struct LinkNode
{
    DATAITEM record;
    struct LinkNode* next; // 指向下一个位置
} LINKNODE;

// 全局变量的声明

typedef struct Conf
{
    int sys_method;               // 实验4工作模式变量，1表示自动模式，2表示交互模式
    char filepath[MAX_ARRAY_LEN]; // 交互模式下储存用户输入的文件储存路径
    int record_num;               // 交互模式下存储用户输入的数据记录条数
    int* Array2D;                 // 二维数组
    DATAITEM* StructArray;        // 结构体数组首指针
    DATAITEM** FingerArray;       // 指针数组首指针
    LINKNODE* LinkHead;           // 链表头指针

    char user_filename[MAX_STR_LEN];
} confvod;