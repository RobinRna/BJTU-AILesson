// Lab1_1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
int CountWordsInOneLine(const char *szLine);

int main()
{
	const char str[500] = "ease with which a human reader can comprehend the purpose, control flow, and operation of source code.It affects the aspects of quality above, including portability, usability and most importantly maintainability.Readability is important because programmers spend the majority of their time reading, trying";
	printf("%d\n", CountWordsInOneLine(str));
    return 0;
}

int CountWordsInOneLine(const char *szLine)
{
	int num=0;
	char tempchar;
	for (tempchar = *szLine; tempchar != '\0'; szLine++,tempchar=*szLine)
	{
		if ((tempchar <= 'Z'&&tempchar >= 'A' || tempchar <= 'z'&&tempchar >= 'a') && !(*(szLine + 1) <= 'Z'&&*(szLine + 1) >= 'A' || *(szLine + 1) <= 'z'&&*(szLine + 1) >= 'a'))num++;
	}
	return num;
}