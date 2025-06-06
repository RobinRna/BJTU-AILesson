/****************************************************\
作者信息：
姓名： 张鲡沣  学号：22281052   班级：计算机2202班   学院：计算机与信息技术学院
Email: 22281052@bjtu.edu.cn     电话：13919833035
版权声明：
    版权由北京交通大学计算机与信息技术学院2022级张鲡沣个人所有
模块名称:
    实验4 主入口函数
摘要:
    作业，配合实验4。部分引用Lab3实验程序。
其它说明:
    无。
模块历史:
　　张鲡沣于2023年5月5日创建本模块，email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_fun.h"

/*
 *函数名称：get_filenum
 *函数功能：通过交互界面获取文件记录条数
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-04（Lab3中程序）
 *           repair by Lifeng Zhang, 2023-04-18
 */
void get_filenum(CONF* data, confvod* conf)
{
    char user_number[MAX_STR_LEN] = "no";
    printf("\n请输入你需要生成的数据条数（若使用配置文件/命令行参数请输入no）:\n");
    scanf("%s", user_number);
    clearstdin();

    // 判断用户是否输入合法
    if (strcmp(user_number, "no") != 0)
    {
        while (check_num(user_number,data,conf) == 0)
        {
            printf("Illegal Number!!  输入数字非法!!:\n");
            printf("Please Re-enter!  请重新输入:\n");
            scanf("%s", user_number);
            clearstdin();
            if (strcmp(user_number, "no") == 0)
                break;
        }
        if (check_num(user_number, data, conf) != 0)
            // 前期已经初始化，写入了数据
            printf("Use Configuration Files.  使用配置文件/命令行参数。\n");
    }
    else
        // 前期已经初始化，写入了数据
        printf("Use Configuration Files.  使用配置文件/命令行参数。\n");
}

/*
 *函数名称：get_filename
 *函数功能：通过交互界面获取文件储存路径
 *输入参数：CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-04（Lab3中程序）
 *          repair by Lifeng Zhang, 2023-04-18
 */

void get_filename(CONF* data, confvod* conf)
{

    printf("\n请输入你需要生成的记录文件名称（可带有绝对路径或相对路径，输入no表示使用配置默认文件名）:\n");
    scanf("%s", conf->user_filename);
    clearstdin();

    // 判断用户是否输入合法
    if (strcmp(conf->user_filename, "no") != 0)
    {
        while (check_seper_file(conf->user_filename, data, conf) == 0)
        {
            printf("Illegal path or file name!!  输入路径或文件名非法!!:\n");
            printf("Please Re-enter!  请重新输入:\n");
            scanf("%s", conf->user_filename);
            clearstdin();
            if (strcmp(conf->user_filename, "no") == 0)
                break;
        }
    }
    else
        printf("Use Configuration Files.  使用配置文件。\n");
}

/*
 *函数名称：check_seper_file
 *函数功能：对argv[1]或argv[2]数据是否合法（为正确文件名）进行检查
 *          判断路径为相对路径还是绝对路径，之后切割路径与文件名，进行储存
 *输入参数：char* str:文件路径与文件名
 *          CONF data 数据参数；
 *          confvod* conf 配置文件参数
 *返回值：  int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2023-04-01（Lab3中程序）
 *          repair by Lifeng Zhang, 2023-04-04
 */
int check_seper_file(char* str, CONF* data, confvod* conf)
{
    int len = strlen(str);
    //_MAX_DRIVE、_MAX_DIR、_MAX_FNAME、_MAX_EXT 在配置中已有定义
    //_MAX_DRIVE==3，_MAX_DIR==_MAX_FNAME==_MAX_EXT==256
    char disk[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    char way[MAX_STR_LEN];
    char file[MAX_STR_LEN];
    char filename_t[MAX_STR_LEN] = "";
    char all[MAX_STR_LEN];

    // 实验要求文件以.txt结尾
    if (str[len - 1] != 't' && str[len - 2] != 'x' && str[len - 3] != 't' && str[len - 4] != '.')
        return 0;

    if (*str == '\\') // 不能以"\\"开头
        return 0;

    // 不能以"\\"或"/"结尾，若以此结尾则认为文件名为空
    char* index1 = strrchr(str, '\\');
    char* index2 = strrchr(str, '/');
    if (index1 - str + 1 == strlen(str) || index2 - str + 1 == strlen(str))
        return 0;

    // 进行合并，以便后续处理
    char* index;
    if (index2 > index1)
        index = index2;
    else
        index = index1;

    // 判断输入路径为绝对路径还是相对路径
    char* p1 = strstr(str, ":\\");
    char* p2 = strstr(str, ":/");

    if (p1 || p2) // 输入的是绝对路径
    {
        // void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
        // 第一个是待处理的完整的文件名路径
        // 四个参数分别代表四个需要从原始文件路径中截取的字符串，有驱动器盘符(drive)，中间的路径（dir），文件名(fname)，和后缀名（ext）
        _splitpath(str, disk, dir, fname, ext);

        // 判断disk在电脑中是否存在
        if (access(disk, 0) != 0)
        {
            printf("%s is no exist! disk在电脑中不存在 \n", disk);
            return 0;
        }

        // 判断路径中是否有非法字符
        if (strstr(dir, "*") || strstr(dir, "?") || strstr(dir, "<") || strstr(dir, ">") || strstr(dir, "|") || strstr(dir, ":"))
            return 0;
        if (strstr(fname, "*") || strstr(fname, "?") || strstr(fname, "<") || strstr(fname, ">") || strstr(fname, "|") || strstr(dir, ":"))
            return 0;

        // 储存路径、文件名
        // void _makepath( const char *path, char *drive, char *dir, char *fname, char *ext);  #include <direct.h>
        // 第一个是要储存的的完整的文件名路径
        // 四个参数分别代表四个需要从结合字符串，有驱动器盘符(drive)，中间的路径（dir），文件名(fname)，和后缀名（ext）
        _makepath(way, disk, dir, NULL, NULL);
        _makepath(file, NULL, NULL, fname, ext);
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);

        if (access(data->filesavepath, 0) == -1) // 路径不存在，创建新路径
            _mkdir(data->filesavepath);
    }

    else if (p1 == NULL || p2 == NULL) // 仅仅是文件名
    {
        if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(str, ":"))
            return 0;
        _splitpath(str, disk, dir, fname, ext);

        _makepath(way, disk, dir, NULL, NULL);
        _makepath(file, NULL, NULL, fname, ext);
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);

        if (access(data->filesavepath, 0) == -1) // 路径不存在，创建新路径
            _mkdir(data->filesavepath);
    }

    else // 相对路径
    {
        if (strstr(str, "*") || strstr(str, "?") || strstr(str, "<") || strstr(str, ">") || strstr(str, "|") || strstr(dir, ":"))
            return 0;

        // 储存路径、文件名
        _splitpath(str, disk, dir, fname, ext);

        _makepath(way, disk, dir, NULL, NULL);
        _makepath(file, NULL, NULL, fname, ext);
        _makepath(all, disk, dir, fname, ext);

        strcpy(data->filesavepath, way);
        strcpy(data->filename, file);
        strcpy(conf->filepath, all);
        _chdir(dir);
    }
    return 1;
}

/*
 *函数名称：clearstdin
 *函数功能：对scanf输入进行缓存清除
 *输入参数：无
 *返回值：int(本程序无实际意义)
 *版本信息：create by Lifeng Zhang, 2022-03-17（Lab3中程序）
 */
int clearstdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 0;
}

/*
 *函数名称：check_num
 *函数功能：对输入数据数据是否合法（为纯数字）进行检查
 *输入参数：无
 *返回值：int,如果检查后合法，返回值为1,否则为0
 *版本信息：create by Lifeng Zhang, 2022-04-01（Lab3中程序）
 *          repair by Lifeng Zhang, 2023-04-18
 */
int check_num(char* str, CONF* data, confvod* conf)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    data->number = atoi(str);
    conf->record_num = atoi(str);
    return 1;
}