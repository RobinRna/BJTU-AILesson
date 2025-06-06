/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放数据读取、数据加载相关功能所需的函数
摘要:
    作业，配合实验4。部分引用Lab3实验程序。
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月12日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/
#include "Lab4_loadfile.h"

/*
 *函数名称：int loadToArray2D
 *函数功能：将数据文件加载到二维数组
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：int 返回数据记录条数
 *版本信息：create by Lifeng Zhang, 2023-05-12
 */
int loadToArray2D(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)// 自动模式
    { 
        char filet[MAX_ARRAY_LEN] = { '\0' };
        char filen[MAX_ARRAY_LEN] = { '\0' };
        FILE* ft;
        errno_t errt;

        errt = fopen_s(&ft, "set\\conf.ini", "r");
        if (errt == 0)
        {
            fscanf(ft, "%s", filet);
            fscanf(ft, "%s", filen);
            strcat(filet, filen);
            fclose(ft);
        }
        else
            printf("打开配置文件失败\n");

        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->Array2D = (int*)malloc(conf->record_num * 3 * sizeof(int));  // 动态内存分配
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(fp, "%d %d %d\n", (conf->Array2D + i * 3), (conf->Array2D + i * 3 + 1), (conf->Array2D + i * 3 + 2));
            fclose(fp);
        }
        else
            printf("指定文件不存在\n");
    }

    else if (conf->sys_method == 2) // 交互模式
    { 

        int count = 0;
        for (int i = 0; conf->filepath[i] != '\0'; ++i)
        {
            if (conf->filepath[i] == '/' || conf->filepath[i] == '\\')
            {
                count++;
                break;
            }
        }
        if (count == 0)
        {
            FILE* fp2;
            errno_t err;
            err = fopen_s(&fp2, "set\\conf.ini", "r");

            if (err == 0)
            {
                char a[200] = { '\0' };
                fscanf(fp2, "%s", a, 200);
            }
            else
                printf("打开lab3配置文件失败\n");
            fclose(fp2);
        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");

        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);
            conf->Array2D = (int*)malloc(conf->record_num * 3 * sizeof(int));// 动态内存分配
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(f, "%d %d %d\n", (conf->Array2D + i * 3), (conf->Array2D + i * 3 + 1), (conf->Array2D + i * 3 + 2));
        }

        else
            printf("指定文件不存在\n");
    }
    return conf->record_num;
}

/*
 *函数名称：int loadToStructArray
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：int 返回数据记录条数
 *版本信息：create by Lifeng Zhang, 2023-05-12
 */
int loadToStructArray(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)// 自动模式
    { 
        char filet[MAX_ARRAY_LEN] = { '\0' };
        char filen[MAX_ARRAY_LEN] = { '\0' };
        FILE* ft;
        errno_t errt;

        errt = fopen_s(&ft, "set\\conf.ini", "r");
        if (errt == 0)
        {
            fscanf(ft, "%s", filet);
            fscanf(ft, "%s", filen);
            strcat(filet, filen);
            fclose(ft);
        }
        else
            printf("打开配置文件失败\n");
        
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->StructArray = (DATAITEM*)malloc(conf->record_num * sizeof(DATAITEM));            // 动态内存分配
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(fp, "%d %d %d\n", &(conf->StructArray + i)->item1, &(conf->StructArray + i)->item2, &(conf->StructArray + i)->item3);
            fclose(fp);
        }
        else
            printf("指定文件不存在\n");
        
    }

    else if (conf->sys_method == 2) // 交互模式
    {
        int cnt = 0;
        for (int i = 0; conf->filepath[i] != '\0'; ++i)
        {
            if (conf->filepath[i] == '/' || conf->filepath[i] == '\\')
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
        {
            FILE* fp2;
            errno_t err;
            err = fopen_s(&fp2, "set\\conf.ini", "r");
            if (err == 0)
            {
                char a[200] = { '\0' };
                fscanf(fp2, "%s", a, 200);
                fclose(fp2);
            }
            else
                printf("打开lab3配置文件失败\n");
            
        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");

        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);
            conf->StructArray = (DATAITEM*)malloc(conf->record_num * sizeof(DATAITEM));
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(f, "%d %d %d\n", &(conf->StructArray + i)->item1, &(conf->StructArray + i)->item2, &(conf->StructArray + i)->item3);
        }
        else
            printf("指定文件不存在\n");
    }
    return conf->record_num;
}

/*
 *函数名称：int loadToFingerArray
 *函数功能：将数据加载到结构体指针数组
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：int 返回数据记录条数
 *版本信息：create by Lifeng Zhang, 2023-05-12
 */
int loadToFingerArray(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)
    { // 自动模式
        char filet[MAX_ARRAY_LEN] = { '\0' };
        char filen[MAX_ARRAY_LEN] = { '\0' };
        FILE* ft;
        errno_t errt;
        errt = fopen_s(&ft, "set\\conf.ini", "r");
        if (errt == 0)
        {
            fscanf(ft, "%s", filet, MAX_ARRAY_LEN);
            fscanf(ft, "%s", filen, MAX_ARRAY_LEN);
            strcat(filet, filen);
        }
        else
        {
            printf("打开配置文件失败\n");
        }
        fclose(ft);
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->FingerArray = (DATAITEM**)malloc(conf->record_num * sizeof(DATAITEM*));            // 动态内存分配
            for (int i = 0; i < conf->record_num; ++i)
            {
                conf->FingerArray[i] = (DATAITEM*)malloc(sizeof(DATAITEM));
            }
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(fp, "%d %d %d\n", &conf->FingerArray[i]->item1, &conf->FingerArray[i]->item2, &conf->FingerArray[i]->item3);
            fclose(fp);
        }
        else
        {
            printf("指定文件不存在\n");
        }
  
    }

    else if (conf->sys_method == 2) // 交互模式
    {
        int cnt = 0;
        for (int i = 0; conf->filepath[i] != '\0'; ++i)
        {
            if (conf->filepath[i] == '/' || conf->filepath[i] == '\\')
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
        {
            FILE* fp2;
            errno_t err;
            err = fopen_s(&fp2, "set\\conf.ini", "r");
            if (err == 0)
            {
                char a[200] = { '\0' };
                fscanf(fp2, "%s", a, 200);
                fclose(fp2);
            }
            else
            {
                printf("打开lab3配置文件失败\n");
            }

        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");
        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);

            conf->FingerArray = (DATAITEM**)malloc(conf->record_num * sizeof(DATAITEM*));            // 动态内存分配
            for (int i = 0; i < conf->record_num; ++i)
            {
                conf->FingerArray[i] = (DATAITEM*)malloc(sizeof(DATAITEM));
            }
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(f, "%d %d %d\n", &conf->FingerArray[i]->item1, &conf->FingerArray[i]->item2, &conf->FingerArray[i]->item3);
        }
        else
            printf("指定文件不存在\n");
    }
    return conf->record_num;
}

/*
 *函数名称：int loadToLink
 *函数功能：将数据加载到链表
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：int 返回数据记录条数
 *版本信息：create by Lifeng Zhang, 2023-05-12
 */
int loadToLink(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)
    { // 自动模式
        char filet[MAX_ARRAY_LEN] = { '\0' };
        char filen[MAX_ARRAY_LEN] = { '\0' };
        FILE* ft;
        errno_t errt;
        errt = fopen_s(&ft, "set\\conf.ini", "r");
        if (errt == 0)
        {
            fscanf(ft, "%s", filet);
            fscanf(ft, "%s", filen);
            strcat(filet, filen);
            fclose(ft);
        }
        else
            printf("打开配置文件失败\n");


        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);

            LINKNODE* tail = NULL;            // 初始化（链表）数据加载到链表
            for (int i = 0; i <= conf->record_num; ++i)
            {
                LINKNODE* newdata;
                newdata = (LINKNODE*)malloc(sizeof(LINKNODE));
                
                if (conf->LinkHead == NULL)// 头指针不装数据，只保存下一个节点的位置
                { 
                    conf->LinkHead = newdata;
                    tail = conf->LinkHead;
                    newdata->next = NULL;
                }
                else
                {
                    fscanf(fp, "%d %d %d\n", &newdata->record.item1, &newdata->record.item2, &newdata->record.item3);
                    tail->next = newdata;
                    tail = newdata;
                    tail->next = NULL;
                }
            }
            fclose(fp);
        }
        else
            printf("指定文件不存在\n");

    }

    else if (conf->sys_method == 2)// 交互模式
    { 
        int cnt = 0;
        for (int i = 0; conf->filepath[i] != '\0'; ++i)
        {
            if (conf->filepath[i] == '/' || conf->filepath[i] == '\\')
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
        {
            FILE* fp2;
            errno_t err;
            err = fopen_s(&fp2, "set\\conf.ini", "r");
            if (err == 0)
            {
                char a[200] = { '\0' };
                fscanf(fp2, "%s", a, 200);
                fclose(fp2);
            }
            else
                printf("打开lab3配置文件失败\n");

        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");

        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);

            LINKNODE* tail = NULL;            // 初始化（链表）数据加载到链表
            for (int i = 0; i < conf->record_num; ++i)
            {
                LINKNODE* newdata;
                newdata = (LINKNODE*)malloc(sizeof(LINKNODE));
                fscanf(f, "%d %d %d\n", &newdata->record.item1, &newdata->record.item2, &newdata->record.item3);
                if (conf->LinkHead == NULL)
                {
                    conf->LinkHead = newdata;
                    tail = conf->LinkHead;
                    newdata->next = NULL;
                }
                else
                {
                    tail->next = newdata;
                    tail = newdata;
                    tail->next = NULL;
                }
            }
        }
    }
    return conf->record_num;
}