#pragma once
#ifndef LIST_H_
#define LIST_H_
#define MAXLEN 101

typedef struct item {
	char word[MAXLEN];
	int count;
}Item;


typedef struct node//定义链接结构
{
	Item word;
	struct node * Next;
}Node;
typedef struct list {
	Node * Head;
	int number;
}List;


/*
*	函数名：ListAppend
*	功能：链表结点构造函数
*	参数：List * ,Item
*	返回值：成功，返回0;
失败，返回1;
*/
int ListAppend(List * mylist, Item ItemAppend);


/*
*	函数名：ListSet
*	功能：创建链表
*	参数：
*	返回值：
*/
int ListSet(List * mylist);


/*
*	函数名：自定义也可调用系统函数qsort，查看网上资料自学链表排序
*	功能：链表排序
*	参数：
*	返回值：
*/
int ListSort(List * mylist);


/*
*	函数名：自定义
*	功能：遍历链表
*	参数：
*	返回值：
*/
int ListTraverse(List * mylist, void(*func)(Item * item));

Node * ListSearch(List * mylist, Item item);

/*
......
*/
int Sort(Node ** Map, size_t size, int func(const Node *A, const Node *B));

void ListBubbleSort(List * mylist);

int ListClear(List * mylist);

#endif // !LIST_H_