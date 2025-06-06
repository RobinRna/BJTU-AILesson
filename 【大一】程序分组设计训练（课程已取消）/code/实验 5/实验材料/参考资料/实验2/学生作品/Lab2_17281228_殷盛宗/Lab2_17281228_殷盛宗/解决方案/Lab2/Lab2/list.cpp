#include "stdafx.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>

static void ListMap(List * mylist, Node *** Map);
static void ListByMap(List * mylist, Node ** Map);
static int ItemCompareByCount(const void * A, const void * B);
static void swap(Node * a, Node * b);

int ListAppend(List * mylist, Item ItemAppend)
{
	Node * newnode;
	newnode = (Node *)malloc(sizeof Node);
	if (newnode == NULL) {
		fprintf(stderr, "%s\n", "创建新节点失败");
		exit(EXIT_FAILURE);
	}
	newnode->word = ItemAppend;
	newnode->Next = NULL;
	if (mylist->Head == NULL) {
		mylist->Head = newnode;
	}
	else {
		newnode->Next = mylist->Head;
		mylist->Head = newnode;
	}
	mylist->number++;
	return 0;
}

int ListSet(List * mylist)
{
	mylist->Head = NULL;
	mylist->number = 0;
	printf("List Set \n");
	return 0;
}

int ListSort(List * mylist)
{
	Node ** Map = NULL;
	ListMap(mylist, &Map);
	qsort(Map, mylist->number, sizeof(Map[0]), ItemCompareByCount);
	ListByMap(mylist, Map);
	free(Map);
	printf("List Sort!\n");
	return 0;
}

int ListTraverse(List * mylist, void(*func)(Item * item))
{
	Node * pNode;
	pNode = mylist->Head;
	for (int i = 0; i < mylist->number; i++)
	{
		func(&pNode->word);
		pNode = pNode->Next;
	}
	printf("List Traverse\n");
	return 0;
}

int ListClear(List * mylist)
{
	printf("开始清空链表\n");
	Node * pNode;
	pNode = mylist->Head;
	while (mylist->number > 0)
	{
		mylist->Head = mylist->Head->Next;
		free(pNode);
		mylist->number--;
		pNode = mylist->Head;
	}
	printf("List Clear\n");
	return 0;
}



static void ListMap(List * mylist, Node *** Map)
{
	*Map = (Node **)malloc(mylist->number * sizeof(Node *));
	Node * pNode = mylist->Head;
	for (int i = 0; i < mylist->number; i++) {
		(*Map)[i] = pNode;
		pNode = pNode->Next;
	}
	printf("List Map Create\n");
}
static void ListByMap(List * mylist, Node ** Map)
{
	for (int i = 0; i < mylist->number - 1; i++) {
		Map[i]->Next = Map[i + 1];
	}
	Map[mylist->number - 1] = NULL;
	mylist->Head = Map[0];
}

static int ItemCompareByCount(const void * A, const void * B)
{
	const Node * a = (const Node *)A;
	const Node * b = (const Node *)B;
	return a->word.count - b->word.count;
}

Node * ListSearch(List * mylist, Item item)
{
	Node * pNode;
	for (pNode = mylist->Head; pNode != NULL; pNode = pNode->Next)
	{

	}
	return pNode;
}

int Sort(Node ** Map, size_t size, int func(const Node *A, const Node *B))
{
	int i, j;
	Node * temp;
	for (i = 1; i < size - 1; i++)
	{
		for (j = 0; j < size - i; j++) {
			if (!func(Map[j], Map[j + 1])) {
				temp = Map[j];
				Map[j] = Map[j + 1];
				Map[j + 1] = temp;
			}
		}
	}
	return 0;
}

void ListBubbleSort(List * mylist)
{
	Node * head;
	Node * tem1;
	Node * tem2;
	Node * tem3;
	head = mylist->Head;
	int i, j;
	for (i = 0; i < mylist->number - 1; i++) {
		for (j = 0; j < mylist->number - i - 1; j++) {
			if (head->word.count < head->Next->word.count) {
				tem1 = head;
				head = head->Next;
				tem2 = head->Next;
				head->Next = tem1;
				head->Next->Next = tem2;
				if (j != 0)
					tem3->Next = head;
			}
			if (j == 0)
				mylist->Head = head;
			tem3 = head;
			head = head->Next;
		}
		head = mylist->Head;
	}
}

static void swap(Node * a, Node * b)
{
	a->Next = b->Next;
	b->Next = a;
}