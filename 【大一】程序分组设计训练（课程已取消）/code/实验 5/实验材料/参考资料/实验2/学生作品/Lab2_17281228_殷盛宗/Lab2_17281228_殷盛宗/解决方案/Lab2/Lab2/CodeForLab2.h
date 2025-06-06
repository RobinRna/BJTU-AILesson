/****************************************************\
作者信息：
姓名：林友芳
版权声明：
版权由北京交通大学计算机与信息技术学院程序设计基础训练课程组所有
模块名称:
CodeForLab2.h
摘要:
教学辅助代码，配合实验1
其它说明:

模块历史:
　　林友芳于2010年10月26日创建本模块，email: yflin@bjtu.edu.cn
  　　林友芳于2012年10月19日修改本模块，email: yflin@bjtu.edu.cn
	林友芳于2015.11.10修改本模块
	韩升于2016年2月16日修改本模块，email：shhan@bjtu.edu.cn
	韩升于2018年2月26日修改本模块，email：shhan@bjtu.edu.cn

	**********************************************************/
	//此处防止因重复包含头文件引的类型重复定义
#ifndef CODEFORLAB7_H_  


#define CODEFORLAB7_H_


	//文本文件统计信息结构体
	//提示：通过typedef使TEXTFILEINFO等价于struct TextFileInfo
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


//所有文件统计信息结构体，该结构中存放各个文本文件的统计信息
//各个文件信息的结构顺序存放
typedef struct FilesInfo
{
	TEXTFILEINFO *pFileInfos;
	//首个文件的统计信息结构体首地址，其他nFileNumber-1个文件的信息顺序连续存放
	//提示，在使用pFileInfos时可将其看成一个数组来使用,如pFileInfos[i]

	int nFileNumber; //文件数目
	int nNewwords;  //所有文件新词总数
}FILESINFO;



/*  函数名：AllocateSpaceForTextFileInfos
*	功能：申请FILESINFO的所需的存储空间
*  参数：文件统计信息结构体指针
*  返回值: 1， 成功，0，不成功
*/
int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles);



/*
*	函数名：PrepareBasicInfoOfFiles
*	功能：准备各个文件的基本信息
*      1. 给定文件个数
*      2. 申请给个文件数的FILESINFO的所需的存储空间
*		3. 给定或读入各个文件名
*  参数：FILESINFO *pFilesInfo，文件统计信息结构体指针
*	返回值：int
*/
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo);

/*
*	函数名：CountFilesInfo
*	功能：统计各项信息
*		1. 统计各个文件中的英文词个数
*		2. 统计各个文件中各个类别的字符个数
*	参数：FILESINFO *pFilesInfo，文件统计信息结构体指针
*	返回值：int
*/
int CountFilesInfo(FILESINFO *pFilesInfo);

/*
*	函数名：CountDifferentCharactersInFile
*	功能：功能给定文件中各类字符的个数
*		1. 根据文件信息结构体指针pTextFileInfo中所给的文件名，打开文件
*		2. 顺序读出文件中的字符，统计中各类字符数
*		3. 关闭文件
*  参数：TEXTFILEINFO *pTextFileInfo
*	返回值：0 成功  -1 无法打开文件
*/

int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo);

/*  函数名：ExportFilesInfoToWebPage
*	功能：将输出文件统计信息到一个HTML文件中
*  参数：
*		FILESINFO *pMyFiles 所有文件的统计信息结构体指针
*		char *szHtmlFile 网页文件名
*  返回值：0成功，-1，无法建立文件
*/
int ExportFilesInfoToWebPage(FILESINFO *pMyFiles, char *szHtmlFile);

/*
*	函数名：TestCountFilesInfo
*	功能：测试函数实验7文件信息统计的主测试函数
*	参数：无
*	返回值：无
*
*/
void TestCountFilesInfo();


/*
*	函数名：CountWordsOfEuropeanTxtFile
*	功能：统计欧洲语言文本文件中词的个数
*	参数：char *szFileName 文件名
*	返回值：单词数
*/

int CountWordsOfEuropeanTxtFile(char *szFileName);//统计欧洲语言文本文件中词的个数

												  /*
												  *	函数名：CountWordsInOneLine
												  *	功能：统计一行欧洲语言正文中词的个数
												  *	参数：const char *szLine 一行欧洲语言正文
												  *	返回值：单词数
												  */
int CountWordsInOneLine(char *szLine);





#endif