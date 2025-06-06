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
#include "CodeForLab2.h"
#include "stdio.h"
#include <windows.h>
#include "malloc.h"

int wordsnumber = 0;


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
	-1	���ɹ�
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
	//int nWords = 0;
	
	//��Ӵ����󲹳����
	int num = 0;
	char tempchar;
	for (tempchar = *szLine; tempchar != '\0'; szLine++, tempchar = *szLine)
	{
		if ((tempchar <= 'Z'&&tempchar >= 'A' || tempchar <= 'z'&&tempchar >= 'a') && !(*(szLine + 1) <= 'Z'&&*(szLine + 1) >= 'A' || *(szLine + 1) <= 'z'&&*(szLine + 1) >= 'a'))num++;
	}
	return num;

	//return nWords;
}

int LinkNodeCreat(NODE * pNode)
{
	pNode = (NODE *)calloc(1, sizeof(pNode));
	pNode->next = NULL;
	wordsnumber++;
	return 0;
}

int LinkCreat(NODE * pNode)
{
	return 0;
}

void AllAroundLink(NODE * pNode, char * WordToFind)
{
	if (pNode == NULL)
	{
		if (LinkNodeCreat(pNode) == -1)printf("Around error!\n");
		strcpy(pNode->word, WordToFind);
		pNode->count++;
	}
	else if (strcmp(pNode->word, WordToFind) != 0)AllAroundLink(pNode->next, WordToFind);
	else pNode->count++;
}

void TestCoundWords()
{
	
	const char *files[5] = { "DataMining.txt" ,"Example.txt" ,"Programming.txt" ,"Readability.txt" ,"reality.txt" };
	for (int i = 0; i < 5; i++)
	{
		FILE *fp;
		fp=fopen(files[i], "r");
		//FindWords(fp, pNode);
		fclose(fp);
	}
	//����һ����������
	//PrintWords(pNode);
}

void FindWords(FILE * fp, NODE * pNode)
{
	char temp[20], tempchar;
	for (;;)
	{
		temp[0] = 0;
		for (;;)
		{
			if ((tempchar = fgetc(fp))==EOF)break;
			if (tempchar <= 'z'&&tempchar >= 'a' || tempchar <= 'Z'&&tempchar >= 'A')
			{
				temp[0]++;
				temp[temp[0]] = tempchar;
			}
			else break;
		}
		if (temp[0] == 0)continue;
		else if (tempchar == EOF)break;
		temp[temp[0] + 1] = '\0';
		AllAroundLink(pNode, temp+1);
	}
}

void PrintWords(NODE * pNode)
{
	FILE *fp;
	fp = fopen("wordsfrequency.txt", "w");
	PrintOneWord(pNode, fp);
	fclose(fp);
}

void PrintOneWord(NODE * pNode, FILE * fp)
{
	printf("%s %d\n", pNode->word, pNode->count);
	if (pNode->next != NULL)PrintOneWord(pNode->next, fp);
}

void newTestCountWords()
{
	NodeHead *pNodeHead;
	pNodeHead = (NodeHead*)malloc(sizeof(NodeHead));
	pNodeHead->number = 0;
	char Words[30];
	const char *files[5] = { "DataMining.txt" ,"Example.txt" ,"Programming.txt" ,"Readability.txt" ,"reality.txt" };
	for (int i = 0; i < 5; i++)
	{
		FILE *fp;
		fp = fopen(files[i], "r");
		NewGetWords(fp, pNodeHead);
		fclose(fp);
	}
	qsort(pNodeHead->pNode, pNodeHead->number, sizeof(NODE), CompareNode);
	NewPrintWords(pNodeHead);
}

void NewGetWords(FILE * fp, NodeHead *pNodeHead)
{
	char temp[20], tempchar;
	for (;;)
	{
		temp[0] = 0;
		for (;;)
		{
			if ((tempchar = fgetc(fp)) == EOF)break;
			if (tempchar <= 'z'&&tempchar >= 'a' || tempchar <= 'Z'&&tempchar >= 'A')
			{
				temp[0]++;
				temp[temp[0]] = tempchar;
			}
			else break;
		}
		if (tempchar == EOF)break;
		else if (temp[0] == 0)continue;
		temp[temp[0] + 1] = '\0';
		NewFindWords(pNodeHead, temp + 1);
	}
}

void NewFindWords(NodeHead * pNodeHead, char * Words)
{
	int i;
	if (pNodeHead->number == 0)
	{
		pNodeHead->pNode = (NODE *)malloc(sizeof(NODE));
		strcpy(pNodeHead->pNode[0].word, Words);
		pNodeHead->pNode->count = 1;
		pNodeHead->number++;
	}
	else {
		int temp = pNodeHead->number;
		for (i = 0; i < pNodeHead->number; i++)
		{
			if (strcmp(pNodeHead->pNode[i].word, Words) != 0)continue;
			else
			{
				pNodeHead->pNode[i].count++;
				temp = i;
				break;
			}
		}
		if (temp == pNodeHead->number)
		{
			pNodeHead->pNode = (NODE *)realloc(pNodeHead->pNode, (pNodeHead->number + 1) * sizeof(NODE));
			pNodeHead->pNode[temp - 1].count = 1;
			strcpy(pNodeHead->pNode[temp - 1].word, Words);
			pNodeHead->number++;
		}
	}
}

void NewPrintWords(NodeHead *pNodeHead)
{
	FILE *fp;
	fp = fopen("wordsfrequency.txt", "w");
	for (int i = 0; i < pNodeHead->number-1; i++)
	{
		fprintf(fp, "%s %d\n", pNodeHead->pNode[i].word, pNodeHead->pNode[i].count);
	}
	fclose(fp);
}

int CompareNode(const void *p2, const void *p1)
{
	if (((NODE*)p1)->count - ((NODE*)p2)->count == 0)
	{
		return strcmp(((NODE*)p1)->word, ((NODE*)p2)->word);
	}
	else
		return ((NODE*)p1)->count - ((NODE*)p2)->count;
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
	pFilesInfo->nFileNumber = 5;//��5��ʵ�����ı�
	if (AllocateSpaceForTextFilesInfo(pFilesInfo) == -1)return -1;
	//���ʵ���ı���ַ����
	strcpy(pFilesInfo->pFileInfos->szFileName, "DataMining.txt");
	strcpy((pFilesInfo->pFileInfos + 1)->szFileName, "Example.txt");
	strcpy((pFilesInfo->pFileInfos + 2)->szFileName, "Programming.txt");
	strcpy((pFilesInfo->pFileInfos + 3)->szFileName, "Readability.txt");
	strcpy((pFilesInfo->pFileInfos + 4)->szFileName, "reality.txt");

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
	int i;
	for (i = 0; i < pFilesInfo->nFileNumber; i++)
	{
		if (((pFilesInfo->pFileInfos + i)->nWords = CountWordsOfEuropeanTxtFile((pFilesInfo->pFileInfos + i)->szFileName)) == -1)return -1;
		if (CountDifferentCharactersInFile(pFilesInfo->pFileInfos + i) == -1)return -1;
	}

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
	char temp;	//��ʱ�ַ����
	pTextFileInfo->nAlphabets = pTextFileInfo->nDigits = pTextFileInfo->nOthers = pTextFileInfo->nSize = pTextFileInfo->nSpaces = 0;
	//���

	//���ļ�
	if ((fp = fopen(pTextFileInfo->szFileName,  "r")) == NULL)
	{
		return -1;	//�ļ��򿪲��ɹ�ʱ����-1
	}

	//�벹����ļ��ж���ͳ�Ƶ���������
	//��ʾ�����Ե��ú���fgetc���ļ��ж�һ���ַ�
	for (;;)
	{
		if ((temp = fgetc(fp)) == -1) break;
		pTextFileInfo->nSize++;
		if (temp <= 'Z'&&temp >= 'A' || temp <= 'z'&&temp >= 'a')pTextFileInfo->nAlphabets++;
		else if (temp <= '9'&&temp >= '0')pTextFileInfo->nDigits++;
		else if (temp == '\t' || temp == '\r' || temp == '\n')pTextFileInfo->nSpaces++;
		else pTextFileInfo->nOthers++;
	}

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

	newTestCountWords();

	//�벹����룬ʵ�ִ򿪴洢ͳ�ƽ������ҳ�ļ�
	//��ʾ�����ղο������е����ݵ����ⲿ�������ҳ�ļ�
	ShellExecute(NULL,TEXT( "open"), TEXT(szHtmlFile), NULL, NULL, SW_SHOWNORMAL);//TEXT��ʾ�ַ�����ǿ��ת��
	
	return;
}

