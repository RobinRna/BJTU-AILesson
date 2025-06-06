/****************************************************\
������Ϣ��
������ ������  ѧ�ţ�22281052   �༶�������2202��   ѧԺ�����������Ϣ����ѧԺ
Email: 22281052@bjtu.edu.cn     �绰��13919833035
��Ȩ������
    ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ2022���������������
ģ������:
    ʵ��4 ������ݶ�ȡ�����ݼ�����ع�������ĺ���
ժҪ:
    ��ҵ�����ʵ��4����������Lab3ʵ�����
����˵��:
    �ޡ�
ģ����ʷ:
������������2023��5��12�մ�����ģ�飬email: 22281052@bjtu.edu.cn
**********************************************************/
#include "Lab4_loadfile.h"

/*
 *�������ƣ�int loadToArray2D
 *�������ܣ��������ļ����ص���ά����
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��int �������ݼ�¼����
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-12
 */
int loadToArray2D(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)// �Զ�ģʽ
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
            printf("�������ļ�ʧ��\n");

        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->Array2D = (int*)malloc(conf->record_num * 3 * sizeof(int));  // ��̬�ڴ����
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(fp, "%d %d %d\n", (conf->Array2D + i * 3), (conf->Array2D + i * 3 + 1), (conf->Array2D + i * 3 + 2));
            fclose(fp);
        }
        else
            printf("ָ���ļ�������\n");
    }

    else if (conf->sys_method == 2) // ����ģʽ
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
                printf("��lab3�����ļ�ʧ��\n");
            fclose(fp2);
        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");

        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);
            conf->Array2D = (int*)malloc(conf->record_num * 3 * sizeof(int));// ��̬�ڴ����
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(f, "%d %d %d\n", (conf->Array2D + i * 3), (conf->Array2D + i * 3 + 1), (conf->Array2D + i * 3 + 2));
        }

        else
            printf("ָ���ļ�������\n");
    }
    return conf->record_num;
}

/*
 *�������ƣ�int loadToStructArray
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��int �������ݼ�¼����
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-12
 */
int loadToStructArray(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)// �Զ�ģʽ
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
            printf("�������ļ�ʧ��\n");
        
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->StructArray = (DATAITEM*)malloc(conf->record_num * sizeof(DATAITEM));            // ��̬�ڴ����
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(fp, "%d %d %d\n", &(conf->StructArray + i)->item1, &(conf->StructArray + i)->item2, &(conf->StructArray + i)->item3);
            fclose(fp);
        }
        else
            printf("ָ���ļ�������\n");
        
    }

    else if (conf->sys_method == 2) // ����ģʽ
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
                printf("��lab3�����ļ�ʧ��\n");
            
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
            printf("ָ���ļ�������\n");
    }
    return conf->record_num;
}

/*
 *�������ƣ�int loadToFingerArray
 *�������ܣ������ݼ��ص��ṹ��ָ������
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��int �������ݼ�¼����
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-12
 */
int loadToFingerArray(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)
    { // �Զ�ģʽ
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
            printf("�������ļ�ʧ��\n");
        }
        fclose(ft);
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);
            conf->FingerArray = (DATAITEM**)malloc(conf->record_num * sizeof(DATAITEM*));            // ��̬�ڴ����
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
            printf("ָ���ļ�������\n");
        }
  
    }

    else if (conf->sys_method == 2) // ����ģʽ
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
                printf("��lab3�����ļ�ʧ��\n");
            }

        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");
        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);

            conf->FingerArray = (DATAITEM**)malloc(conf->record_num * sizeof(DATAITEM*));            // ��̬�ڴ����
            for (int i = 0; i < conf->record_num; ++i)
            {
                conf->FingerArray[i] = (DATAITEM*)malloc(sizeof(DATAITEM));
            }
            for (int i = 0; i < conf->record_num; ++i)
                fscanf(f, "%d %d %d\n", &conf->FingerArray[i]->item1, &conf->FingerArray[i]->item2, &conf->FingerArray[i]->item3);
        }
        else
            printf("ָ���ļ�������\n");
    }
    return conf->record_num;
}

/*
 *�������ƣ�int loadToLink
 *�������ܣ������ݼ��ص�����
 *���������CONF data ���ݲ�����
 *          confvod* conf �����ļ�����
 *����ֵ��int �������ݼ�¼����
 *�汾��Ϣ��create by Lifeng Zhang, 2023-05-12
 */
int loadToLink(CONF* data, confvod* conf)
{
    if (conf->sys_method == 1)
    { // �Զ�ģʽ
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
            printf("�������ļ�ʧ��\n");


        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, filet, "r");
        if (err == 0)
        {
            fscanf(fp, "%d\n", &conf->record_num);

            LINKNODE* tail = NULL;            // ��ʼ�����������ݼ��ص�����
            for (int i = 0; i <= conf->record_num; ++i)
            {
                LINKNODE* newdata;
                newdata = (LINKNODE*)malloc(sizeof(LINKNODE));
                
                if (conf->LinkHead == NULL)// ͷָ�벻װ���ݣ�ֻ������һ���ڵ��λ��
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
            printf("ָ���ļ�������\n");

    }

    else if (conf->sys_method == 2)// ����ģʽ
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
                printf("��lab3�����ļ�ʧ��\n");

        }

        FILE* f;
        errno_t err2;
        err2 = fopen_s(&f, conf->filepath, "r");

        if (err2 == 0)
        {
            fscanf(f, "%d\n", &conf->record_num);

            LINKNODE* tail = NULL;            // ��ʼ�����������ݼ��ص�����
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