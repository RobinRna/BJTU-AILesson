// Lab2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CodeForLab2.h"

char * gets(char * szLine);

int main()
{
	TestCountFilesInfo();
    return 0;
}
char * gets(char * szLine)
{
	while ((*szLine = getchar()) != '\n') szLine++;
	*szLine = '\0';
	return szLine;
}
