/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 存放与修改配置文件相关的功能函数
摘要:
    作业，配合实验4。
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月14日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_conf.h"

/*
 *函数名称：void modifyfilesavepath
 *函数功能：修改文件存储路径
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void modifyfilesavepath(CONF* data, confvod* conf)
{
    char filesp[MAX_ARRAY_LEN] = { '\0' };
    while (1)
    {
        printf("请输入正确的文件存储路径：\n");
        char c = getchar();
        if (*fgets(filesp, MAX_ARRAY_LEN, stdin) == '\n') // 若用户不输入，则重新输入
            continue;
        else
        {
            int f = check_seper_file(conf->filepath, data, conf);
            if (f == 1) // 合法
                break;
            else
                continue;
        }
    }
    strcpy(data->filesavepath, filesp);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("修改失败\n");
    fclose(fp);
}

/*
 *函数名称：void modifyfilename
 *函数功能：修改文件名
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void modifyfilename(CONF* data, confvod* conf)
{
    char filename[MAX_ARRAY_LEN] = { '\0' };
    while (1)
    {
        printf("请输入正确的文件名：\n");
        char c = getchar();
        if (*fgets(filename, MAX_ARRAY_LEN, stdin) == '\n') // 若用户不输入，则重新输入
            continue;
        else
        {
            int f = check_seper_file(conf->filepath, data, conf);
            if (f == 1) // 合法
                break;
            else
                continue;
        }
    }
    strcpy(data->filename, filename);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("修改失败\n");
    fclose(fp);
}

/*
 *函数名称：void modify12
 *函数功能：修改第一二个元素的范围
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void modify12(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("请输入题一二个元素的上限和下限（不输入则使用默认值）\n");
    while (1)
    {
        int cnt = 0;
        printf("请输入上限：\n");
        scanf("%s", max);

        printf("请输入下限：\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
            printf("请重新输入上限：");
        continue;
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("请重新输入下限：");
            continue;
        }
        break;
    }
    if (max[0] != '\n')
        data->maxvalue1 = atoi(max);
    if (max[0] != '\n')
        data->minvalue1 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("修改失败\n");
    fclose(fp);
}

/*
 *函数名称：void modify3
 *函数功能：修改第三个元素的范围
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void modify3(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("请输入题三个元素的上限和下限（不输入则使用默认值）\n");
    while (1)
    {
        int cnt = 0;
        printf("请输入上限：\n");
        scanf("%s", max);

        printf("请输入下限：\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
        {
            printf("请重新输入上限：");
            continue;
        }
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("请重新输入下限：");
            continue;
        }

        break;
    }
    if (max[0] != '\n')
        data->maxvalue2 = atoi(max);
    if (max[0] != '\n')
        data->minvalue2 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("修改失败\n");
    fclose(fp);
}

/*
 *函数名称：void modifynum
 *函数功能：修改数据记录条数的范围
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-15
 */
void modifynum(CONF* data, confvod* conf)
{
    char max[66] = { '\0' }, min[66] = { '\0' };
    printf("请输入题数据记录条数的上限和下限（不输入则使用默认值）\n");
    while (1)
    {
        int cnt = 0;
        printf("请输入上限：\n");
        scanf("%s", max);

        printf("请输入下限：\n");
        scanf("%s", min);

        if (check_num(max, data, conf) || max[0] == '\n')
            cnt++;
        else
        {
            printf("请重新输入上限：");
            continue;
        }
        if (check_num(min, data, conf) || min[0] == '\n')
            cnt++;
        else
        {
            printf("请重新输入下限：");
            continue;
        }
        break;
    }
    if (max[0] != '\n')
        data->recordcount1 = atoi(max);
    if (max[0] != '\n')
        data->recordcount2 = atoi(min);

    FILE* fp;
    errno_t err;
    err = fopen_s(&fp, "set\\conf.ini", "w");
    if (err == 0)
    {
        fprintf(fp, "%s%s%d%d%d%d%d%d%d",
            data->filesavepath,
            data->filename,
            data->number,
            data->maxvalue1,
            data->minvalue1,
            data->maxvalue2,
            data->minvalue2,
            data->recordcount1,
            data->recordcount2);
    }
    else
        printf("修改失败\n");
    fclose(fp);
}

/*
 *函数名称：void modifysysmethod
 *函数功能：修改实验4工作模式
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 */
void modifysysmethod(CONF* data, confvod* conf)
{
    int n;
    printf("请输入实验4的工作模式（1代表自动模式，2代表交互模式）：\n");
    while (true)
    {
        if (scanf("%d", &n) == 1 && n >= 1 && n <= 2)
        {
            FILE* fp;
            errno_t err;
            err = fopen_s(&fp, "set\\zlf_method.ini", "w");
            if (err == 0)
            {
                fprintf(fp, "%d\n", n);
                printf("已修改zlf_method.ini模式文件配置！\n");
            }
            else
                printf("打开lab4配置文件失败\n");
            fclose(fp);
            break;
        }
        else
            printf("请重新输入：\n");
    }
}

/*
 *函数名称：void freedata
 *函数功能：释放动态申请的内存，重新初始化全局变量
 *输入参数：int n 选项；
 *          CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-16
 *          repair by Lifeng Zhang, 2023-05-31
 */
void freedata(int n, CONF* data, confvod* conf)
{
    if (n == 1 || n == 2 || n == 6 || n == 10)
        free2d(conf);

    if (n == 1 || n == 3 || n == 7 || n == 11)
        freestruct(conf);

    if (n == 4 || n == 8 || n == 12)
        freeFingerArray(conf);

    if (n == 5 || n == 9 || n == 13)
        freelink(conf);
}

/*
 *函数名称：void free2d
 *函数功能：释放二维数组的内容
 *输入参数：confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-21
 */
void free2d(confvod* conf)
{
    free(conf->Array2D);
    conf->Array2D = NULL;
}

/*
 *函数名称：void freestruct
 *函数功能：释放结构体数组的内容
 *输入参数：confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-21
 */
void freestruct(confvod* conf)
{
    free(conf->StructArray);
    conf->StructArray = NULL;
}

/*
 *函数名称：void freeFingerArray
 *函数功能：释放结构体指针数组的内容
 *输入参数：confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-21
 */
void freeFingerArray(confvod* conf)
{
    for (int i = 0; i < conf->record_num; ++i)
        free(conf->FingerArray[i]);
    conf->FingerArray = NULL;
}

/*
 *函数名称：void freelink
 *函数功能：释放链表的内容
 *输入参数：confvod* conf 配置文件参数
 *返回值：void
 *版本信息：create by Lifeng Zhang, 2023-05-21
 */
void freelink(confvod* conf)
{
    LINKNODE* p = conf->LinkHead;
    // LINKNODE* q = p->next;
    for (int i = 0; i < conf->record_num; i++)
    {
        LINKNODE* q = p->next;
        free(p);
        p = q;

        conf->LinkHead = NULL;
    }
}