/****************************************************\
作者信息：
作业完成人：孙嘉葳		学号：17281219
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
#include "CODEFORLAB2.h"
#include "stdio.h"
#include"stdlib.h"
#include "malloc.h"
#include"linkh.h"
#include"string.h"
#include"ctype.h"



	  /*  AllocateSpaceForTextFilesInfo
	  *	功能：申请FILESINFO的所需的存储空间
	  *  参数：文件统计信息结构体变量
	  *  注意：
	  *		1.在调用该函数前，请先给定pMyfiles的文件数目nFileNumber
	  *		2.本函数不需要修改，请直接使用
	  *  返回值: 0， 成功，-1，参数不合法，-2，存储空间不足
	  *	模块历史：
	  *
	  */
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


/***********************************************\
函数名称:
CountWordsOfEuropeanTxtFile
功能描述:
统计欧洲语言文本文件中词的个数
函数参数:
char *szFileName 文件名
返回值:
int 词的个数
模块历史:

\**********************************************/
int CountWordsOfEuropeanTxtFile(char *szFileName)
{
	int nWords = 0;//词计数变量，初始值为0
	FILE *fp; //文件指针
	char carrBuffer[1024];//每行字符缓冲，每行最多1024个字符

						  //打开文件
	if ((fp = fopen(szFileName, "r")) == NULL)
	{
		fprintf(stderr,"未成功打开文件\n");
		return -1;	//文件打开不成功是返回-1
	}

	while (!feof(fp))//如果没有读到文件末尾 
	{
		//从文件中读一行
		if (fgets(carrBuffer, sizeof(carrBuffer), fp) != NULL)
			//统计每行词数//fgets读到换行符时停止读入
			nWords += CountWordsInOneLine(carrBuffer);
	}

	//关闭文件
	fclose(fp);

	return nWords;
}



/*
*  函数名称:
*		CountWordsInOneLine
*	功能：统计一行欧洲语言正文中词的个数
*	参数：const char *szLine 一行欧洲语言正文
*	返回值：
*	int 单词数
*/
int CountWordsInOneLine(const char *szLine)//const char是字符型常量，只能读取，不可改变
{
	int nWords = 0;

	//请从此往后补充代码

	for (; *szLine; szLine++)
	{
		char a;
		for (a = *szLine; !((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z')); )//当a=*szLine是英文字母的时候停下

		{
			if (!(*szLine))   return nWords;//末尾全是空格的情况

			szLine++;
			a = *szLine;

		}//此时的szLine记录英文单词的开头的第一个字母

		const char *p = szLine;

		for (a = *p; ((a >= 'a'&&a <= 'z') || (a >= 'A'&&a <= 'Z')); )//当a=*p不是英文字母的时候停下
		{

			p++;
			a = *p;
		}//p记录英文单词末端第一个不是英文字母的字符

		const char * q;
		int i = 0;
		for (q=szLine;q!=p; i++,q++)
		{
			EnglishWord[i] = *q;
		}  //将一个英文单词存储到EnglishWord中
		EnglishWord[i] = '\0';  //构建字符串

		list = addword(list, EnglishWord);  //将word中的单词存入链表中，并改变计数器的值

		szLine = (p - 1);   //将指针指向英文单词末端的最后一个字母
		nWords++;   //计单词的数目加一
	}
	return nWords;
}




/*int CountWordsInOneLine(const char *szLine)
{
	int count = 0, state = OUT;
	for (; *szLine; szLine++)
	{
		if (*szLine == '\n' || *szLine == '\t' || *szLine == ' ')
			state = OUT;  
		else if (state == OUT)
		{
			count++;
			state = IN;
		}
	}
	return count;
}
*/


/*
*	函数名：PrepareBasicInfoOfFiles
*	功能：准备各个文件的基本信息
*      1. 给定实验用文本文件的个数
*      2. 申请给定文件个数的FILESINFO的所需的存储空间
*	   3. 给定或读入各个文件名
*  参数：FILESINFO *pFilesInfo，文件统计信息结构体指针
*	返回值：int
*	模块历史：
*/
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//请在此往后补充代码
	printf("请输入文件的个数");
	scanf("%d", &pFilesInfo->nFileNumber);  //给定实验用文本文件的个数
	AllocateSpaceForTextFilesInfo(pFilesInfo);  //申请给定个数的文件所需要的空间
	printf("请输入文件名");
	int i = 0;
	for (; i < pFilesInfo->nFileNumber; i++)
	{
		scanf("%s", pFilesInfo->pFileInfos[i].szFileName);  //读取文件名
	}

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
*
*/
int CountFilesInfo(FILESINFO *pFilesInfo)
{
	//请在此处往后补充代码
	int i = 0;
	int n;
	for (; i < pFilesInfo->nFileNumber; i++)
	{
		n=CountWordsOfEuropeanTxtFile(pFilesInfo->pFileInfos[i].szFileName);
		pFilesInfo->pFileInfos[i].nWords = n;
		CountDifferentCharactersInFile(&pFilesInfo->pFileInfos[i]);
	}//统计各个文件中的英文词个数并存储到结构体中
	

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

	char c;	  //补充必要的变量说明
	pTextFileInfo->nAlphabets = 0;
	pTextFileInfo->nDigits = 0;
	pTextFileInfo->nOthers = 0;
	pTextFileInfo->nSize = 0;
	pTextFileInfo->nSpaces = 0;

			  //打开文件
	if ((fp = fopen(pTextFileInfo->szFileName, "r")) == NULL)
	{
		return -1;	//文件打开不成功时返回-1
	}

	//请补充从文件中读并统计的其他代码
	//提示：可以调用函数fgetc从文件中读一个字符
	while (!feof(fp))  //如果没有读到文件末尾
	{
		c = fgetc(fp);  //从文件中读取一个字符
		if (c == '\t' || c == '\n' || c == '\r'||c==' ') pTextFileInfo->nSpaces++;
		else if (c >= '0'&&c <= '9') pTextFileInfo->nDigits++;
		else if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))   pTextFileInfo->nAlphabets++;
		else pTextFileInfo->nOthers++;

	}
	pTextFileInfo->nSize = pTextFileInfo->nSpaces + pTextFileInfo->nDigits + pTextFileInfo->nAlphabets + pTextFileInfo->nOthers;
	//关闭文件
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

	fp = fopen(szHtmlFile, "w+"); //打开文件
	if (NULL == fp) //判断打开是否成功
	{
		printf("无法创建文件！\n");  //不成功
		return -1;
	}
	//开始往文件中写内容
	//生成一些必要的html格式代码
	fprintf(fp, "<HTML>\n<HEAD>\n<TITLE>文件统计结果</TITLE>\n");
	fprintf(fp, "<BODY>\n");
	fprintf(fp, "<H4>实验7文件信息统计结果如下：</H6>\n");

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
	//提示：参照参考资料中的内容调用外部程序打开网页文件
	system(szHtmlFile);

}



/*
*	函数名：makenode
*	功能：申请结点内存并改变结点计数器
*	参数：char w[],单词数组的首地址
*	返回值：struct node *
*	模块历史：
*/
LINK makenode(char w[])
{
	LINK p = (LINK)malloc(sizeof(NODE));  //申请结点内存
	if (p != NULL)  //申请成功
	{
		strncpy(p->word, w, 20);   //将w的长度为MAXLEN的内容复制到p->word中
		p->count = 1;   //改变结点计数器
		p->next = NULL;   //makenode的结点总是尾结点（新的结点）

	}
	return p;
}

/*  addword
*	功能：将新的单词加入链表中
*  参数：LINK list 整个链表的头指针， char w[]所要向链表中添加的单词
*  返回值:LINK list 整个链表的头结点
*	模块历史：
*
*/
LINK addword(LINK list, char w[])
{
	if (list == NULL)
	{
		return makenode(w);   //即第一次循环时，创建了第一个结点
	}
	LINK p;
	for (p = list;; p = p->next)   //从头结点找到尾节点
	{
		if (strcmp(p->word, w) == 0)   //如果找到了，就计数加一并结束循环
		{
			p->count++;
			break;
		}
		if (p->next == NULL)   //如果没有找到，就创建一个新的结点并结束循环
		{
			p->next = makenode(w);
			break;
		}
	}
	return list;
}

/*  linksort
*	功能：用选择排序法对链表进行排序
*  参数：LINK p 整个链表的头指针
*  返回值:LINK p 整个链表的头指针
*	模块历史：
*
*/
LINK linksort(LINK p)
{
	LINK i, j, k;
	char temp1[20];
	int temp2;
	for (i = p; (i->next) != NULL; i = i->next)
	{
		k = i;
		for (j = i->next; j != NULL; j = j->next)
		{
			if (k->count < j->count)  k = j;  //记录count最大值时的结点
		}
		if (k != i)  //将两个结点中的单词和计数数字交换
		{
			strcpy(temp1, k->word);
			strcpy(k->word, i->word);
			strcpy(i->word, temp1);
			temp2 = k->count;
			k->count = i->count;
			i->count = temp2;
		}
	}
	return p;
}



/*  printwords
*	功能：将排序后的链表输出到文件
*  参数：LINK p 整个链表的头指针
*  返回值: 0
*	模块历史：
*
*/
int printwords(LINK p)
{

	FILE *fp;  //声明一个文件指针

	fp = fopen("wordsfrequency.txt", "w+"); //打开文件
	if (NULL == fp) //判断打开是否成功
	{
		printf("无法创建文件！\n");  //不成功
		return -1;
	}
	
//开始往文件中写内容
	for (; p != NULL; p = p->next)
	{
		fprintf(fp, "%s %d\n", p->word, p->count);
	}

	fclose(fp); //关闭文件
	return 0;

}

/*  freelink
*	功能：将链表所分配的内存释放
*  参数：LINK p 整个链表的头指针
*  返回值: 无
*	模块历史：
*
*/
void freelink(LINK p)
{
	LINK q=NULL;
	for (q = p; q != NULL;)
	{
		q = q->next;
		free(p);
		p = q;

	}
}



int ALinkMaker()
{

	printwords(list);

	printf("排序后的单词及出现次数如下：\n");

	linksort(list);

	printwords(list);

	freelink(list);

	return 0;
}


