/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 ����ں���
ժҪ:
    ��ҵ�����ʵ��2
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��5�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/

#include "Lab4_main.h"

/*
 *�������ƣ�run
 *�������ܣ�ʵ��4����������
 *���������int argc�������в���������char* argv[]:�����в���ֵ
 *����ֵ��int(��ʵ�ʺ���)
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-05
 *          repair by Lifeng Zhang, 2023-05-09
 *          repair by Lifeng Zhang, 2023-05-14
 *          repair by Lifeng Zhang, 2023-05-21
 */
int run(int argc, char* argv[])
{
    int num;
    syscheck(); // �����Լ�

    CONF* data = (CONF*)malloc(sizeof(CONF));
    confvod* conf = (confvod*)malloc(sizeof(confvod));

    sysinit(data, conf); // ��ʼ��������ϵͳ����

    FILE* fp = NULL;
    srand((int)time(0)); // �������������

    clock_t start, stop;
    double duration;


    /*�Ƚ������ݵĳ�ʼ������������ں���Ĺ�������Ҫʹ�ó�ʼ�����ݣ�
     *���ò���������ֱ��ʹ���ļ��е����ݡ�
     */

    while (true)
    {
        int n;
        n = showmainmenu(conf); // ��ʾ�˵�
        if (n == 0)
            break;
        else if (n == 1)
        {
            callLab3(data, conf);
        }
        else if (n == 2)
        {
            num = loadToArray2D(data, conf); // �������ļ����ص���ά����
            showArray2D(num, conf);
        }
        else if (n == 3)
        {
            num = loadToStructArray(data, conf);
            showStructArray(num, conf);
        }
        else if (n == 4)
        {
            num = loadToFingerArray(data, conf);
            showFingerArray(num, conf);
        }
        else if (n == 5)
        {
            num = loadToLink(data, conf);
            showLink(num, conf);
        }
        else if (n == 6)
        {
            callLab3(data, conf);
            num = loadToArray2D(data, conf); // �������ļ����ص���ά����
            showArray2D(num, conf);
        }
        else if (n == 7)
        {
            callLab3(data, conf);
            num = loadToStructArray(data, conf);
            showStructArray(num, conf);
        }
        else if (n == 8)
        {
            callLab3(data, conf);
            num = loadToFingerArray(data, conf);
            showFingerArray(num, conf);
        }
        else if (n == 9)
        {
            callLab3(data, conf);
            num = loadToLink(data, conf);
            showLink(num, conf);
        }
        else if (n == 10)
        {
            callLab3(data, conf);
            num = loadToArray2D(data, conf); // �������ļ����ص���ά����
            sortArray2D(num, conf);
            showArray2D(num, conf);
        }
        else if (n == 11)
        {
            callLab3(data, conf);
            num = loadToStructArray(data, conf);
            sortStructArray(num, conf);
            showStructArray(num, conf);
        }
        else if (n == 12)
        {
            callLab3(data, conf);
            num = loadToFingerArray(data, conf);
            sortFingerArray(num, conf);
            showFingerArray(num, conf);
        }
        else if (n == 13)
        {
            callLab3(data, conf);
            num = loadToLink(data, conf);
            sortLink1(num, conf);  //ð��
            
            // ����
            /*
            start = clock();
            sortLink2(conf->LinkHead->next, NULL);
            stop = clock();
            duration = (double)(stop - start) / CLOCKS_PER_SEC;
            printf("\n�������򡪡����űȽϳ�����ʱ��%f s \n", duration);
            system("pause");  //��ͣ��ʾ��� 
            */

            showLink(num, conf);
        }

        else if (n == 14)
        {
            while (true)
            {
                int m;
                m = show14menu();
                if (m == 0)
                    break;
                else if (m == 1)
                    modifyfilesavepath(data, conf);
                else if (m == 2)
                    modifyfilename(data, conf);
                else if (m == 3)
                    modify12(data, conf);
                else if (m == 4)
                    modify3(data, conf);
                else if (m == 5)
                    modifynum(data, conf);
                else if (m == 6)
                    modifysysmethod(data, conf);
                else
                    printf("���������룺\n");
            }
        }
        else
        {
            printf("���������룺\n");
        }
        // �ͷŶ�̬������ڴ棬���³�ʼ��ȫ�ֱ���
        freedata(n, data, conf);
        fflush(stdin);  //�建��
    }
    return 0;
}