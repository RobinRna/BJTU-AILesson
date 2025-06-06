/****************************************************\
作者信息：
     作业完成人：		学号：
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
#include "CodeForLab1.h"
#include "stdio.h"

#include "malloc.h"




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
	if ((fp = fopen(szFileName,  "r")) == NULL)
	{
		return -1;	//文件打开不成功是返回-1
	}

	while (!feof(fp))//如果没有读到文件末尾 
	{
		//从文件中读一行
		if (fgets(carrBuffer, sizeof(carrBuffer),fp) != NULL)
			//统计每行词数
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
 
int CountWordsInOneLine(const char *szLine)
{
	int nWords = 0;
	
	//请从此往后补充代码


	return nWords;
}


/*
 *	函数名：PrepareBasicInfoOfFiles
 *	功能：准备各个文件的基本信息
 *      1. 给定实验用文本文件的个数
 *      2. 申请给定文件个数的FILESINFO的所需的存储空间
 *		3. 给定或读入各个文件名
 *  参数：FILESINFO *pFilesInfo，文件统计信息结构体指针
 *	返回值：int
 *	模块历史：
 */	

int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//请在此往后补充代码

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
	
	//补充必要的变量说明

	//打开文件
	if ((fp = fopen(pTextFileInfo->szFileName,  "r")) == NULL)
	{
		return -1;	//文件打开不成功时返回-1
	}

	//请补充从文件中读并统计的其他代码
	//提示：可以调用函数fgetc从文件中读一个字符



	


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
	fprintf(fp,"<HTML>\n<HEAD>\n<TITLE>文件统计结果</TITLE>\n" );
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



	
	return;
}
