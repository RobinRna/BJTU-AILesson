#pragma once
/*���������¼����Ƶ�ʺ������ͷ�ļ�*/



char EnglishWord[20];

typedef struct node NODE, *LINK;  //struct node���͵ı�����ָ��

struct node
{
	char word[20];  //����еĵ���
	int count;   //����д˵��ʳ��ֵĴ���
	LINK next;   //����е�ָ����

};

LINK list = NULL;

/*  getword
*	���ܣ����뵥�ʣ�����������ַ�������word[]��
*  ������int limit������޶�, char word[]ȫ�ֱ���
*  ����ֵ:0,��ȡ���ȳ���limit-1���ǿո�ͻس�ʱ,ʧ�ܣ�
��0���ɹ�
*	ģ����ʷ��
*
*/
int getword(int limit, char w[]);

/*  addword
*	���ܣ����µĵ��ʼ���������
*  ������LINK list ���������ͷָ�룬 char w[]��Ҫ����������ӵĵ���

*  ����ֵ:LINK list ���������ͷ���
*	ģ����ʷ��
*
*/
LINK addword(LINK list, char w[]);

/*  makenode
*	���ܣ��������
*  ������char w[]
*  ����ֵ:LINK list ���������ͷ���
*	ģ����ʷ��
*
*/
LINK makenode(char w[]);

/*  printwords
*	���ܣ�����������ӡ
*  ������LINK list �����ͷ���
*  ����ֵ: ��
*	ģ����ʷ��
*
*/
int printwords(LINK list);



/*  linksort
*	���ܣ���ѡ�����򷨶������������
*  ������LINK p ���������ͷָ��
*  ����ֵ:LINK p ���������ͷָ��
*	ģ����ʷ��
*
*/
LINK linksort(LINK p);



void freelink(LINK p);



int ALinkMaker();
