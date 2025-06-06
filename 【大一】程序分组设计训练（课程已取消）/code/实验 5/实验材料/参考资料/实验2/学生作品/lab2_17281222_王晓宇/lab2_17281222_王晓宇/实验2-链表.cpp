// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//
#include "stdlib.h"
#include "stdafx.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#define strcpy strcpy_s
#define  MAXLEN  20
typedef struct TextFileInfo
{
	char szFileName[120]; //the file name, should be less than 120 characters
	int nWords; //the number of words separated by spaces
	int nSize; //the size of file in bytes
	int nDigits; //the number of digital charactors
	int nSpaces; //the number of spaces including space , ‘\t’, ‘\r’, ‘\n’
	int nAlphabets; //the number of charactors 'A'--'Z', 'a'--'z'
	int nOthers; //the number of other characters
}TEXTFILEINFO;
typedef   struct FilesInfo
{
	TEXTFILEINFO    *pFileInfos;
	int    nFileNumber; //文件数目
	int    nNewwords;  //所有文件新词总数
}FILESINFO;
typedef struct node  NODE;
typedef struct node  *LINK;
struct node//定义链接结构
{
	char word[MAXLEN];
	int count;
	LINK next;
};
int getword(int limit,int filenum, char* word, TEXTFILEINFO* MyFilesInfo);
LINK addwordL(LINK list, char w[]);
void printwords(LINK l);
int CountWordsInOneLine(const char *szLine);
int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo);
LINK SortNode(LINK list);
static LINK list = NULL;
char word[MAXLEN];
int CountWordsOfEuropeanTxtFile(char *szFileName)
{
	int nWords = 0;//词计数变量，初始值为0
	int a;
	FILE *fp; //文件指针
	char carrBuffer[1024];//每行字符缓冲，每行最多1024个字符

						  //打开文件
	if ((a = fopen_s(&fp, szFileName, "r")) != NULL)
	{
		return -1;	//文件打开不成功是返回-1
	}

	while (!feof(fp))//如果没有读到文件末尾 
	{
		//从文件中读一行
		if (fgets(carrBuffer, sizeof(carrBuffer), fp) != NULL)
			//统计每行词数
			nWords += CountWordsInOneLine(carrBuffer);
	}

	//关闭文件
	fclose(fp);

	return nWords;
}
int CountWordsInOneLine(const char *szLine)
{
	int nWords = 0, a = 0;

	//请从此往后补充代码
	while ((*szLine != '\n') && (*szLine != 0))
	{
		if ((*szLine == ' ') || (*szLine == '\t'))
		{
			a = 0;
		}
		else if ((!a) && (((*szLine >= 'a') && (*szLine <= 'z')) || ((*szLine >= 'A') && (*szLine <= 'Z'))))
		{
			nWords++;
			a = 1;
		}
		szLine++;
	}
	return nWords;
}
int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles)
{
	//参数合法性判断
	if (NULL == pMyFiles || pMyFiles->nFileNumber <= 0)
	{
		return -1;
	}
	pMyFiles->pFileInfos = (TEXTFILEINFO *)malloc(pMyFiles->nFileNumber * sizeof(TEXTFILEINFO));
	if (NULL == pMyFiles->pFileInfos)
	{
		return -2;
	}
	return 0;
}
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//请在此往后补充代码
	int i = 5, j = 0;
	char a[] = { "DataMining.txt" }, b[] = { "Example.txt" }, c[] = { "Programming.txt" };
	char d[] = { "Readability.txt" }, e[] = { "reality.txt" };;
	pFilesInfo->nFileNumber = i;
	AllocateSpaceForTextFilesInfo(pFilesInfo);
	strcpy(pFilesInfo->pFileInfos[0].szFileName, a);
	strcpy(pFilesInfo->pFileInfos[1].szFileName, b);
	strcpy(pFilesInfo->pFileInfos[2].szFileName, c);
	strcpy(pFilesInfo->pFileInfos[3].szFileName, d);
	strcpy(pFilesInfo->pFileInfos[4].szFileName, e);
	return 0;
}
int CountFilesInfo(FILESINFO *pFilesInfo)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		pFilesInfo->pFileInfos[i].nWords = CountWordsOfEuropeanTxtFile(pFilesInfo->pFileInfos[i].szFileName);
		CountDifferentCharactersInFile(&(pFilesInfo->pFileInfos[i]));
	}
	return 0;
}
int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo)
{
	int Size = 0, Digits = 0, Spaces = 0, Alphabets = 0, Others = 0;
	char c;
	FILE *fp; //文件指针

			  //补充必要的变量说明

			  //打开文件
	if ((fopen_s(&fp, pTextFileInfo->szFileName, "r")) != NULL)
	{
		return -1;
	}
	c = fgetc(fp);
	while (!feof(fp))
	{
		if ((c >= '0') && (c <= '9'))
		{
			Digits++;
		}
		else if (c == ' ' || c == '\t' || c == '\n')
		{
			Spaces++;
		}
		else if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		{
			Alphabets++;
		}
		else
		{
			Others++;
		}
		c = fgetc(fp);
	}
	fseek(fp, 0L, SEEK_END);
	Size = ftell(fp);
	//Size += (Digits * sizeof(int));
	//Size += ((Spaces + Alphabets + Others) * sizeof(char));
	pTextFileInfo->nAlphabets = Alphabets;
	pTextFileInfo->nDigits = Digits;
	pTextFileInfo->nOthers = Others;
	pTextFileInfo->nSize = Size;
	pTextFileInfo->nSpaces = Spaces;
	//关闭文件
	fclose(fp);

	return 0;
}
LINK SortNode(LINK list)
{
	int tem;
	char tword[MAXLEN];
	LINK tmp,p;
	tmp = list;
	if (list == NULL)
	{
		return NULL;
	}
	for (;tmp != NULL; tmp = tmp->next)
	{
		for (p = list; p->next != NULL; p = p->next)
		{
			if (p->count < p->next->count)
			{
				tem = p->count;
				p->count = p->next->count;
				p->next->count = tem;
				strcpy(tword, p->word);
				strcpy(p->word, p->next->word);
				strcpy(p->next->word, tword);
			}
		}
	}
	return list;
}
FILESINFO* TestCountFilesInfo()
{

	FILESINFO* MyFilesInfo;
	MyFilesInfo = (FILESINFO*)malloc(sizeof(FILESINFO));
	PrepareBasicInfoOfFiles(MyFilesInfo);
	CountFilesInfo(MyFilesInfo);
	return MyFilesInfo;
}
int main()
{
	int newwords = 0,i,words = 0;
	FILESINFO* MyFilesInfo;
	MyFilesInfo = TestCountFilesInfo();
	for (i = 0; i < 5; i++)
	{
		while (getword(MyFilesInfo->pFileInfos[i].nWords,i, word, &(MyFilesInfo->pFileInfos[i])) != 0)
		{
			list = addwordL(list, word);
			words++;
		}
	}
	MyFilesInfo->nNewwords = words;
	list = SortNode(list);
	printwords(list);
	free(MyFilesInfo);
	return 0;
}

int getword(int limit, int filenum, char* word, TEXTFILEINFO* MyFilesInfo)
{
	static int j[5] = { 0 };
	int i = 0,c;
	FILE *fp;
	fopen_s(&fp, MyFilesInfo->szFileName,"r");
	fseek(fp, j[filenum], 0);
	c = fgetc(fp);
	while ((i < limit - 2) && (!feof(fp)))
	{
		if (c == '\n' || c == ' ')
		{
			j[filenum]++;
			c = fgetc(fp);
		}
		else
		{
			break;
		}
	}
	while ((i < limit-2) && (!feof(fp)) && (c != '\n' || c != ' '))
	{
		if (c == '\n' || c == ' ')
		{
			break;
		}
		*(word+i) = c; 
		i++;
		j[filenum]++;
		c = fgetc(fp);
	}
	word[i] = '\0';
	fclose(fp);
	return i;
}
LINK mknode(char w[])  //创建一个新结点
{
	LINK p = (LINK)malloc(sizeof(NODE));
	if (p != NULL)
	{
		strncpy_s(p->word, w, MAXLEN);
		p->count = 1;
		p->next = NULL;
	}
	return p;
}
LINK addwordL(LINK list, char w[])
//修改结点计数器或将新创建的结点加下链表中
{
	LINK p;
	if (list == NULL) return mknode(w);
	for (p = list; ; p = p->next)
	{
		if (strcmp(p->word, w) == 0)
		{
			p->count++;
			break;
		}
		if (p->next == NULL)
		{
			p->next = mknode(w);
			break;
		}
	}
	return list;
}
void printwords(LINK p)    //遍历打印链表结点
{
	FILE* fp;
	fopen_s(&fp, "wordsfrequency.txt", "w");
	for (; p != NULL; p = p->next)
	{
		fprintf(fp,"%d %s\n", p->count, p->word);
	}
	fclose(fp);
	return;
}
