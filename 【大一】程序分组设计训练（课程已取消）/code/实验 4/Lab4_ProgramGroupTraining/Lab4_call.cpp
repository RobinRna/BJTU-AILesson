/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 �����Լ졢����ϵͳ��������ʼ��ȫ�ֱ���
ժҪ:
    ��ҵ�����ʵ��4
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_call.h"

/*
 *�������ƣ�void callLab3
 *�������ܣ�����ʵ��3���������ļ�
 *���������int n ��������������
 *          confvod* conf �����ļ�����
 *����ֵ��void
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-15
 */
void callLab3(CONF* data, confvod* conf)
{
    char commond[256] = { '\0' };
    if (conf->sys_method == 1)       //�Զ�ģʽ
    {
        sprintf(commond, "D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_4_Experiments/Lab4_ProgramGroupTraining/set/Lab3_ProgramGroupTraining.exe");
        system(commond);
    }
    else if (conf->sys_method == 2)  //����ģʽ
    {
        get_filename(data, conf);
        fflush(stdin);  //�建��
        get_filenum(data, conf);
        fflush(stdin);  //�建��
        sprintf(commond, "D:/Learning_ComputerLanguages/learning_language_c/_2_ProgramGroupTraining/_4_Experiments/Lab4_ProgramGroupTraining/set/Lab3_ProgramGroupTraining.exe %d %s", conf->record_num, conf->filepath);
        system(commond);
    }
    else
        printf("�ļ������ڣ�������1��Ŀ");
    
}