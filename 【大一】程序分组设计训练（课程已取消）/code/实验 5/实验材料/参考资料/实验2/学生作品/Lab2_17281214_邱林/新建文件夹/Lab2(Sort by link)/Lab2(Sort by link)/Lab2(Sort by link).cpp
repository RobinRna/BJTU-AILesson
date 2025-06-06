// Lab2(Sort by link).cpp: 定义控制台应用程序的入口点。
//

// 程序设计实验二：文本统计.cpp: 定义控制台应用程序的入口点。
//
/****************************************************\
作者信息：
作业完成人：邱林		学号：17281214
版权声明：
版权由北京交通大学计算机与信息技术学院程序设计基础训练课程组所有
模块名称:
CodeForLab2.CPP
摘要:
教学辅助代码，配合实验2
其它说明:

模块历史:
　　林友芳于2011年10月26日创建本模块，email: yflin@bjtu.edu.cn
  　　林友芳于2012年10月19日修改本模块，email: yflin@bjtu.edu.cn
	　林友芳于2013年10月11日修改本模块，email: yflin@bjtu.edu.cn
	 韩升于2017年2月16日修改本模块，email：shhan@bjtu.edu.cn
	 贾彩燕于2018年2月22日修改本模块，email: cyjia@bjtu.edu.cn

	 **********************************************************/
#include "stdafx.h"
#include"CodeForLab2.h"
#include "stdio.h"
#include <windows.h>
#include "malloc.h"
#include "stdlib.h"
char *name(char szFileName[],char);
char *name(char szFileName[],char *p)
{
	char name[100]="G://DataForLab2//";
	strcpy(name + 17, szFileName);
	p = name;
	return p;
}
int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles)
{
	//参数合法性判断
	if (NULL == pMyFiles || pMyFiles->nFileNumber <= 0)
		return -1;

	//申请存放pMyFiles->nFileNumber个TEXTFILEINFO类型结构体所需的存储空间
	//并将新申请到的pMyFiles->nFileNumber * sizeof(TEXTFILEINFO)个字节的
	//存储空间首地址存放到pMyFiles->pFileInfos中
	pMyFiles->pFileInfos = (TEXTFILEINFO *)malloc(pMyFiles->nFileNumber * sizeof(TEXTFILEINFO));

	if (NULL == pMyFiles->pFileInfos)
		return -2;

	return 0;

}
int CountWordsOfEuropeanTxtFile(char *szFileName)
{
	int nWords = 0;//词计数变量，初始值为0
	FILE *fp; //文件指针
	char carrBuffer[1024];//每行字符缓冲，每行最多1024个字符

						  //打开文件
	if (fopen_s(&fp, szFileName, "r") != 0)
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
	int nWords = 0;
	//请从此往后补充代码
	int n = strlen(szLine), i, count = 0, state = 0;//初始化状态为未遇到字符
	for (i = 0; i < n; i++)
	{
		if (szLine[i] == ' ' || szLine[i] == '\t')
		{
			state = 0;//遇到空格或者制表符，进入out
		}
		else if (state == 0)//表示上一句if语句将字母之间的空格都一个个过掉，终于遇到字母，才开始计数
		{
			state = 1;//遇到了一个字母代表遇到了一个单词，避免重复计数
			++count;
		}
	}
	return count;


	return nWords;
}
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//请在此往后补充代码
	system("dir /b G:\\DataForLab2 >>G:\\文件目录.txt");
	FILE *fp;
	fopen_s(&fp, "G:\\文件目录.txt", "r");
	pFilesInfo->nFileNumber = 0;
	char c;
	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')pFilesInfo->nFileNumber++;
	}
	fseek(fp, 0, SEEK_SET);
	AllocateSpaceForTextFilesInfo(pFilesInfo);
	int i = 0;
	for (; i < pFilesInfo->nFileNumber; i++)
	{
		fgets((pFilesInfo->pFileInfos[i].szFileName), 100, fp);//从文件里面读一行送入szfilename	
		int n = strlen(pFilesInfo->pFileInfos[i].szFileName);
		pFilesInfo->pFileInfos[i].szFileName[n - 1] = '\0';
	}
	fclose(fp);
	fopen_s(&fp, "G:\\文件目录.txt", "w");//用完文件目录.txt后将该文本清空
	fclose(fp);
	return 0;
}
/*
*	函数名：CountFilesInfo
*	功能：统计各项信息
*		1. 统计各个文件中的英文词个数
*		2. 统计各个文件中各个类别的字符个数
*	参数：FILESINFO *pFilesInfo，文件统计信息结构体指针
*	返回值：int
*		     0--正常
*           其他，不正常
*       char name[100] = "G://DataForLab2//";
strcpy(name+17,(pFilesInfo->pFileInfos[i].szFileName));
*/
int CountFilesInfo(FILESINFO *pFilesInfo)
{
	//请在此处往后补充代码
	FILE *fp;
	int i = 0;
	for (; i < pFilesInfo->nFileNumber; i++)
	{
		char name[100] = "G://DataForLab2//";
		strcpy(name + 17, pFilesInfo->pFileInfos[i].szFileName);
		fopen_s(&fp, name, "r");
		int count = 0, state = 0;
		char s[1024];
		while (!feof(fp))
		{
			fgets(s, 1024, fp);
			count += CountWordsInOneLine(s);
		}
		pFilesInfo->pFileInfos[i].nWords = count;
		fclose(fp);
		CountDifferentCharactersInFile(&pFilesInfo->pFileInfos[i]);

	}
	return 0;
}
/*
*	函数名：CountDifferentCharactersInFile
*	功能：统计给定文件中各类字符的个数
*		1. 根据文件信息结构体指针pTextFileInfo中所给的文件名，打开文件
*		2. 顺序读出文件中的字符，统计中各类字符数
*		3. 关闭文件
*  参数：TEXTFILEINFO *pTextFileInfo
*	返回值：0 成功  -1 无法打开文件
*/
int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo)
{

	FILE *fp; //文件指针
	char c;
	int nDigits, nSpacesn, Alphabets, nOthers, All;		  //补充必要的变量说明
	nDigits = nSpacesn = Alphabets = nOthers = All = 0;
	//打开文件
	char name[100] = "G://DataForLab2//";
	strcpy(name + 17, pTextFileInfo->szFileName);
	if (fopen_s(&fp, name, "r") != 0)
	{
		return -1;	//文件打开不成功时返回-1
	}
	//请补充从文件中读并统计的其他代码
	//提示：可以调用函数fgetc从文件中读一个字符
	while ((c = fgetc(fp)) != EOF)
	{
		if (c >= '0'&&c <= '9') nDigits++;
		else if (c == ' ' || c == '\t' || c == '\n') nSpacesn++;
		else if ((c >= 'A'&&c <= 'Z') || (c >= 'a'&&c <= 'z')) Alphabets++;
		else nOthers++;
	}
	pTextFileInfo->nAlphabets = Alphabets;
	pTextFileInfo->nDigits = nDigits;
	pTextFileInfo->nOthers = nOthers;
	pTextFileInfo->nSpaces = nSpacesn;
	fseek(fp, 0, SEEK_SET);
	while ((c = fgetc(fp)) != EOF) All++;
	pTextFileInfo->nSize = All;
	//关闭文件 pTextFileInfo->nSize = ftell(fp);
	fclose(fp);
	return 0;
}
/*  函数名：ExportFilesInfoToWebPage
*	功能：将文件统计信息输出到一个HTML文件中
*  参数：
*		FILESINFO *pMyFiles 所有文件的统计信息结构体指针
*		char *szHtmlFile 网页文件名
*  返回值：0成功，-1，无法建立文件
*
*/
int ExportFilesInfoToWebPage(FILESINFO *pMyFiles, char *szHtmlFile)
{
	FILE *fp;  //声明一个文件指针
	int i; //循环变量

	fopen_s(&fp, szHtmlFile, "w+"); //打开文件
	if (NULL == fp) //判断打开是否成功
	{
		printf("无法创建文件！\n");  //不成功
		return -1;
	}
	//开始往文件中写内容
	//生成一些必要的html格式代码
	fprintf(fp, "<HTML>\n<HEAD>\n<TITLE>文件统计结 果</TITLE>\n");
	fprintf(fp, "<BODY>\n");


	fprintf(fp, "<H4>实验2文件信息统计结果如下：</H6>\n");

	//生成一个表格
	fprintf(fp, "<table border=""2"">\n");
	//表头
	fprintf(fp, "<td>序号</td><td>文件名</td><td>单词个数</td><td>文件大小</td>"
		"<td>数字个数</td><td>空白字符数</td><td>英文字符数</td><td>其他字符数</td>\n");

	//循环生成每一行
	for (i = 0; i < pMyFiles->nFileNumber; ++i)
	{
		fprintf(fp, "<tr>"); //新起一行

							 //将每一条文件的统计信息生成目标字符串，写入文件中
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
		fprintf(fp, "</tr>\n");//结束一行
	}
	//表格生成完毕
	fprintf(fp, "</table>\n");

	fprintf(fp, "<H4>请根据实验核对统计结果是否正确！</H6><BR>\n");
	//输出必要的html结束标志
	fprintf(fp, "</BODY>\n</HEAD>\n</HTML>\n");

	fclose(fp); //关闭文件

	return 0;//返回成功标志
}
/*
*	函数名：TestCountFilesInfo
*	功能：测试函数实验1文件信息统计的主测试函数
*	参数：无
*	返回值：无
*	模块历史：
*/
void TestCountFilesInfo()
{

	//准备好所有文件的统计信息的结构体变量
	FILESINFO MyFilesInfo;
	char szHtmlFile[120] = "FileInfoResult.html";


	//文件基本信息准备
	PrepareBasicInfoOfFiles(&MyFilesInfo);

	//调用统计函数
	CountFilesInfo(&MyFilesInfo);

	//将统计结果输出到下Web Page中
	ExportFilesInfoToWebPage(&MyFilesInfo, szHtmlFile);

	//请补充代码，实现打开存储统计结果的网页文件
	ShellExecute(NULL, "open", szHtmlFile, NULL, NULL, SW_SHOWNORMAL);
	//提示：参照参考资料中的内容调用外部程序打开网页文件
	free(&MyFilesInfo);



	return;
}
int Getword(TEXTFILEINFO *pTextFileInfo, char word[],FILE *fp)
{
	
	int i = 0;
	char c;
	while (i < MAXLEN - 2 && (c = fgetc(fp)) != EOF && c != '\n' && c != ' '&& c != '\t')
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		{
			word[i] = c;
			++i;
		}
	word[i] = '\0';
	return i;

}
int i = 0;

LINK mknode(char w[])  //创建一个新结点
{
	LINK p = (LINK)malloc(sizeof(NODE));
	if (p != NULL)
	{
		strncpy(p->word, w, MAXLEN);
		p->count = 1;
		p->next = NULL;
	}
	i++;
	return p;
}
LINK addwordL(LINK list, char w[])
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
LINK Sort(LINK p)
{
	
	LINK h = NULL,m=NULL,l=NULL;
	char t[100];
	int k=i,f=0,j,o=0;
	LINK s;
	for (j = 0; j < k-1; j++)
	{
		for (f = 0; f < k -1- j; f++)
		{
			if (p->count < p->next->count)
			{
				h = p;
				p = p->next;
				m = p->next;
				p->next = h;
				p->next->next = m;
				if (f != 0)
				{
					l->next = p;
				}
			}
			if (f == 0)
			{
				s = p;
			}
			l = p;
			p = p->next;
		}
		p = s;
	}
		

			/*f = p->count;
			p->count = q->count;
			q->count = f;
			strcpy(t, p->word);
			strcpy(p->word, q->word);
			strcpy(q->word,t);*/
	return s;
}
int printwords(LINK p)    //遍历打印链表结点
{
	FILE *fp;
	int count = 0;
	fopen_s(&fp, "wordsfrequency.txt", "w+");
	for (; p != NULL; p = p->next)
	{
		fprintf(fp,"%s %d\n", p->word, p->count);
		count += p->count;
	}
	return count;
}

void TestLink()
{
	LINK list = NULL,s;
	FILESINFO FilesInfo;
	PrepareBasicInfoOfFiles(&FilesInfo);
	char word[MAXLEN];
	int i,j;
	FILE *fp;
	char Name[100], *p = NULL;
	for (i = 0; i < FilesInfo.nFileNumber; i++)
	{
		strcpy(Name, name(FilesInfo.pFileInfos[i].szFileName, p));
		fopen_s(&fp, Name, "r");
		while(!feof(fp))
		{
			while (Getword(&FilesInfo.pFileInfos[i], word, fp) != 0)
				list = addwordL(list, word);
		}
	}
	s=Sort(list);
	FilesInfo.nNewwords=printwords(s);
}
int main()
{
	TestLink();
	system("pause");
	return 0;
}


