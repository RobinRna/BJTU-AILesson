#pragma once
/*关于链表记录单词频率和排序的头文件*/



char EnglishWord[20];

typedef struct node NODE, *LINK;  //struct node类型的变量和指针

struct node
{
	char word[20];  //结点中的单词
	int count;   //结点中此单词出现的次数
	LINK next;   //结点中的指针域

};

LINK list = NULL;

/*  getword
*	功能：读入单词，并将其组成字符串存入word[]中
*  参数：int limit单词最长限度, char word[]全局变量
*  返回值:0,读取长度超过limit-1或是空格和回车时,失败；
非0，成功
*	模块历史：
*
*/
int getword(int limit, char w[]);

/*  addword
*	功能：将新的单词加入链表中
*  参数：LINK list 整个链表的头指针， char w[]所要向链表中添加的单词

*  返回值:LINK list 整个链表的头结点
*	模块历史：
*
*/
LINK addword(LINK list, char w[]);

/*  makenode
*	功能：创建结点
*  参数：char w[]
*  返回值:LINK list 整个链表的头结点
*	模块历史：
*
*/
LINK makenode(char w[]);

/*  printwords
*	功能：遍历链表并打印
*  参数：LINK list 链表的头结点
*  返回值: 无
*	模块历史：
*
*/
int printwords(LINK list);



/*  linksort
*	功能：用选择排序法对链表进行排序
*  参数：LINK p 整个链表的头指针
*  返回值:LINK p 整个链表的头指针
*	模块历史：
*
*/
LINK linksort(LINK p);



void freelink(LINK p);



int ALinkMaker();
