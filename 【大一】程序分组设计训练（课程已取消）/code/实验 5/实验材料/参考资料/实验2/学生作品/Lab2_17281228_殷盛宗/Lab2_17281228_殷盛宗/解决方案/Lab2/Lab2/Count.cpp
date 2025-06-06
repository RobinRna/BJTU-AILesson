#include "stdafx.h"
#include <stdlib.h>

int isdigit(char ch);
int isspace(char ch);
int isalpha(char ch);
int ispunct(char ch);

int CountFileSize(char * szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "rb");
	if (fp == NULL) {
		fprintf(stderr, "File in open %s\n",
			szFileName);
		exit(EXIT_FAILURE);
	}
	int Size;
	fseek(fp, 0, SEEK_END);
	Size = ftell(fp);

	fclose(fp);

	return Size;
}
int CountFileDgts(char * szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "File in open %s\n",
			szFileName);
		exit(EXIT_FAILURE);
	}
	int	Digits = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF)
		if (isdigit(ch))
			Digits++;

	fclose(fp);

	return Digits;
}
int CountFileSpcs(char * szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "File in open %s\n",
			szFileName);
		exit(EXIT_FAILURE);
	}
	int	Spaces = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (isspace(ch))
			Spaces++;
	}
	fclose(fp);

	return Spaces;
}
int CountFileAlph(char * szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "File in open %s\n",
			szFileName);
		exit(EXIT_FAILURE);
	}
	int	Alphabets = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (isalpha(ch))
			Alphabets++;
	}
	fclose(fp);

	return Alphabets;
}
int CountFileOthr(char * szFileName)
{
	FILE *fp;
	fp = fopen(szFileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "File in open %s\n",
			szFileName);
		exit(EXIT_FAILURE);
	}
	int	Others = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (ispunct(ch))
			Others++;
	}
	fclose(fp);

	return Others;
}

int isdigit(char ch)
{
	if ('0' <= ch && '9' >= ch)
		return 1;
	else
		return 0;
}

int isspace(char ch)
{
	if (' ' == ch || '\n' == ch || '\t' == ch || '\r' == ch)
		return 1;
	else
		return 0;
}

int isalpha(char ch)
{
	if (
		'a' <= ch && 'z' >= ch ||
		'A' <= ch && 'Z' >= ch
		)
		return 1;
	else
		return 0;
}

int ispunct(char ch)
{
	if (
		!isalpha(ch) &&
		!isdigit(ch) &&
		!isspace(ch)
		)
		return 1;
	else
		return 0;
}
