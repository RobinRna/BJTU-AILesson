#pragma once
#ifndef LIST_H_
#define LIST_H_
#define MAXLEN 101

typedef struct item {
	char word[MAXLEN];
	int count;
}Item;


typedef struct node//�������ӽṹ
{
	Item word;
	struct node * Next;
}Node;
typedef struct list {
	Node * Head;
	int number;
}List;


/*
*	��������ListAppend
*	���ܣ������㹹�캯��
*	������List * ,Item
*	����ֵ���ɹ�������0;
ʧ�ܣ�����1;
*/
int ListAppend(List * mylist, Item ItemAppend);


/*
*	��������ListSet
*	���ܣ���������
*	������
*	����ֵ��
*/
int ListSet(List * mylist);


/*
*	���������Զ���Ҳ�ɵ���ϵͳ����qsort���鿴����������ѧ��������
*	���ܣ���������
*	������
*	����ֵ��
*/
int ListSort(List * mylist);


/*
*	���������Զ���
*	���ܣ���������
*	������
*	����ֵ��
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