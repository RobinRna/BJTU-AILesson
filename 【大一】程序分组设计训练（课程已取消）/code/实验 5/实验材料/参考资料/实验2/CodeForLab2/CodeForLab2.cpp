/****************************************************\
������Ϣ��
     ��ҵ����ˣ�		ѧ�ţ�
��Ȩ������
     ��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ������ƻ���ѵ���γ�������
ģ������: 
    CodeForLab2.CPP
ժҪ:
    ��ѧ�������룬���ʵ��2
����˵��:

ģ����ʷ:
�������ѷ���2011��10��26�մ�����ģ�飬email: yflin@bjtu.edu.cn
�������ѷ���2012��10��19���޸ı�ģ�飬email: yflin@bjtu.edu.cn
�������ѷ���2013��10��11���޸ı�ģ�飬email: yflin@bjtu.edu.cn
    ������2017��2��16���޸ı�ģ�飬email��shhan@bjtu.edu.cn
	�ֲ�����2018��2��22���޸ı�ģ�飬email: cyjia@bjtu.edu.cn

**********************************************************/
#include "stdafx.h"
#include "CodeForLab1.h"
#include "stdio.h"

#include "malloc.h"




/*  AllocateSpaceForTextFilesInfo
 *	���ܣ�����FILESINFO������Ĵ洢�ռ�
 *  �������ļ�ͳ����Ϣ�ṹ�����
 *  ע�⣺
 *		1.�ڵ��øú���ǰ�����ȸ���pMyfiles���ļ���ĿnFileNumber
 *		2.����������Ҫ�޸ģ���ֱ��ʹ��
 *  ����ֵ: 0�� �ɹ���-1���������Ϸ���-2���洢�ռ䲻��
 *	ģ����ʷ��
 *	 
 */
 
int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles)
{
	//�����Ϸ����ж�
	if (NULL == pMyFiles || pMyFiles->nFileNumber <= 0)
		return -1;

	//������pMyFiles->nFileNumber��TEXTFILEINFO���ͽṹ������Ĵ洢�ռ�
	//���������뵽��pMyFiles->nFileNumber * sizeof(TEXTFILEINFO)���ֽڵ�
	//�洢�ռ��׵�ַ��ŵ�pMyFiles->pFileInfos��
	pMyFiles->pFileInfos = (TEXTFILEINFO *)malloc(pMyFiles->nFileNumber * sizeof(TEXTFILEINFO));

	if (NULL == pMyFiles->pFileInfos)
		return -2;
	
	return 0;

}
/***********************************************\
��������:
	CountWordsOfEuropeanTxtFile
��������:
	ͳ��ŷ�������ı��ļ��дʵĸ���
��������:
	char *szFileName �ļ���
����ֵ:
	int �ʵĸ���
ģ����ʷ:
  	
\**********************************************/

int CountWordsOfEuropeanTxtFile(char *szFileName)
{
	int nWords = 0;//�ʼ�����������ʼֵΪ0
	FILE *fp; //�ļ�ָ��
	char carrBuffer[1024];//ÿ���ַ����壬ÿ�����1024���ַ�

	//���ļ�
	if ((fp = fopen(szFileName,  "r")) == NULL)
	{
		return -1;	//�ļ��򿪲��ɹ��Ƿ���-1
	}

	while (!feof(fp))//���û�ж����ļ�ĩβ 
	{
		//���ļ��ж�һ��
		if (fgets(carrBuffer, sizeof(carrBuffer),fp) != NULL)
			//ͳ��ÿ�д���
			nWords += CountWordsInOneLine(carrBuffer);
	}

	//�ر��ļ�
	fclose(fp);

	return nWords;
}
/*
 *  ��������:
 *		CountWordsInOneLine
 *	���ܣ�ͳ��һ��ŷ�����������дʵĸ���
 *	������const char *szLine һ��ŷ����������
 *	����ֵ��
 *	int ������
 */
 
int CountWordsInOneLine(const char *szLine)
{
	int nWords = 0;
	
	//��Ӵ����󲹳����


	return nWords;
}


/*
 *	��������PrepareBasicInfoOfFiles
 *	���ܣ�׼�������ļ��Ļ�����Ϣ
 *      1. ����ʵ�����ı��ļ��ĸ���
 *      2. ��������ļ�������FILESINFO������Ĵ洢�ռ�
 *		3. �������������ļ���
 *  ������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int
 *	ģ����ʷ��
 */	

int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//���ڴ����󲹳����

	return 0;
}

/*
 *	��������CountFilesInfo
 *	���ܣ�ͳ�Ƹ�����Ϣ
 *		1. ͳ�Ƹ����ļ��е�Ӣ�Ĵʸ���
 *		2. ͳ�Ƹ����ļ��и��������ַ�����
 *	������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int  
 *		     0--����
 *           ������������
 *	 
 */
int CountFilesInfo(FILESINFO *pFilesInfo)
{
	//���ڴ˴����󲹳����


	return 0;
}

/*
 *	��������CountDifferentCharactersInFile
 *	���ܣ�ͳ�Ƹ����ļ��и����ַ��ĸ���
 *		1. �����ļ���Ϣ�ṹ��ָ��pTextFileInfo���������ļ��������ļ�
 *		2. ˳������ļ��е��ַ���ͳ���и����ַ���
 *		3. �ر��ļ�
 *  ������TEXTFILEINFO *pTextFileInfo
 *	����ֵ��0 �ɹ�  -1 �޷����ļ�
 */

int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo)
{
	FILE *fp; //�ļ�ָ��
	
	//�����Ҫ�ı���˵��

	//���ļ�
	if ((fp = fopen(pTextFileInfo->szFileName,  "r")) == NULL)
	{
		return -1;	//�ļ��򿪲��ɹ�ʱ����-1
	}

	//�벹����ļ��ж���ͳ�Ƶ���������
	//��ʾ�����Ե��ú���fgetc���ļ��ж�һ���ַ�



	


	//�ر��ļ�
	fclose(fp);

	return 0;
}

/*  ��������ExportFilesInfoToWebPage
 *	���ܣ����ļ�ͳ����Ϣ�����һ��HTML�ļ���
 *  ������
 *		FILESINFO *pMyFiles �����ļ���ͳ����Ϣ�ṹ��ָ��
 *		char *szHtmlFile ��ҳ�ļ���
 *  ����ֵ��0�ɹ���-1���޷������ļ�
 *	
 */ 

int ExportFilesInfoToWebPage(FILESINFO *pMyFiles, char *szHtmlFile)
{
	FILE *fp;  //����һ���ļ�ָ��
	int i; //ѭ������

	fp = fopen(szHtmlFile, "w+"); //���ļ�
	if (NULL == fp) //�жϴ��Ƿ�ɹ�
	{
		printf("�޷������ļ���\n");  //���ɹ�
		return -1;
	}
	//��ʼ���ļ���д����
	//����һЩ��Ҫ��html��ʽ����
	fprintf(fp,"<HTML>\n<HEAD>\n<TITLE>�ļ�ͳ�ƽ��</TITLE>\n" );
	fprintf(fp, "<BODY>\n");

	
	fprintf(fp, "<H4>ʵ��7�ļ���Ϣͳ�ƽ�����£�</H6>\n");	

	//����һ�����
	fprintf(fp, "<table border=""2"">\n");
	//��ͷ
	fprintf(fp, "<td>���</td><td>�ļ���</td><td>���ʸ���</td><td>�ļ���С</td>"
		"<td>���ָ���</td><td>�հ��ַ���</td><td>Ӣ���ַ���</td><td>�����ַ���</td>\n");

	//ѭ������ÿһ��
	for (i = 0; i < pMyFiles->nFileNumber; ++i)
	{
		fprintf(fp, "<tr>"); //����һ��
		
		//��ÿһ���ļ���ͳ����Ϣ����Ŀ���ַ�����д���ļ���
		fprintf(fp, "<td>%4d</td>"
			"<td>%s</td>"
			"<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>\n",
			i + 1,
			pMyFiles->pFileInfos[i].szFileName,
			pMyFiles->pFileInfos[i].nWords,
			pMyFiles->pFileInfos[i].nSize,
			pMyFiles->pFileInfos[i].nDigits,
			pMyFiles->pFileInfos[i].nSpaces,
			pMyFiles->pFileInfos[i].nAlphabets,
			pMyFiles->pFileInfos[i].nOthers
			);
		fprintf(fp, "</tr>\n");//����һ��
	}
	//����������
	fprintf(fp, "</table>\n");

	fprintf(fp, "<H4>�����ʵ��˶�ͳ�ƽ���Ƿ���ȷ��</H6><BR>\n");	
	//�����Ҫ��html������־
	fprintf(fp, "</BODY>\n</HEAD>\n</HTML>\n");

	fclose(fp); //�ر��ļ�

	return 0;//���سɹ���־
}
/*
 *	��������TestCountFilesInfo
 *	���ܣ����Ժ���ʵ��1�ļ���Ϣͳ�Ƶ������Ժ���
 *	��������
 *	����ֵ����
 *	ģ����ʷ��
 */

void TestCountFilesInfo()
{
	
	//׼���������ļ���ͳ����Ϣ�Ľṹ�����
	FILESINFO MyFilesInfo;
	char szHtmlFile[120] = "FileInfoResult.html";


	//�ļ�������Ϣ׼��
	PrepareBasicInfoOfFiles(&MyFilesInfo);
	
	//����ͳ�ƺ���
	CountFilesInfo(&MyFilesInfo);
	
	//��ͳ�ƽ���������Web Page��
	ExportFilesInfoToWebPage(&MyFilesInfo, szHtmlFile);

	//�벹����룬ʵ�ִ򿪴洢ͳ�ƽ������ҳ�ļ�
	//��ʾ�����ղο������е����ݵ����ⲿ�������ҳ�ļ�



	
	return;
}
