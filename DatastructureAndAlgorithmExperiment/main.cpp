#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include <iostream>
using namespace std;
#define QUEUESIZE 127
#define MAXSIZE 127

//�������Ǵ����ݽṹʵ���г���һ���ִ���
typedef char ElemType;
typedef struct btnode
{
	ElemType element;
	struct btnode* lChild;
	struct btnode* rChild;
}BTNode;
typedef struct BinaryTree
{
	BTNode* root;
}BinaryTree;

void Create(BinaryTree* bt);
BTNode* NewNode(ElemType x, BTNode* ln, BTNode* rn);
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right);
void PreOrderTree(BinaryTree* bt);
void PreOrder(BTNode* t);
void InOrderTree(BinaryTree* bt);
void InOrder(BTNode* t);
void PostOrderTree(BinaryTree* bt);
void PostOrder(BTNode* t);
void Exchange(BTNode* t, ElemType tree[MAXSIZE][2], ElemType& i, ElemType j);
void TreeClear(BinaryTree* bt);
void Clear(BTNode* t);
int TreeSize(BinaryTree* bt);
int Size(BTNode* t);
void LevelOrderTree(BinaryTree* tree);
void ExchangeThre(BinaryTree* bt, ElemType btByParent[MAXSIZE][2]);
//�����¶�����
void Create(BinaryTree* bt)
{
	bt->root = NULL;
}
//����һ���µĽڵ㣬���ظýڵ�ĵ�ַ
BTNode* NewNode(ElemType x, BTNode* ln, BTNode* rn)
{
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));
	if (p == NULL)
	{
		exit(1);
	}
	p->element = x;
	p->lChild = ln;
	p->rChild = rn;
	return p;
}
//��bt�ڵ��²�������
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right)
{
	if (bt->root || left == right)//�����ж�bt�Ƿ�Ϊ�գ�������ڵ�����ҽڵ�
		return;
	bt->root = NewNode(e, left->root, right->root);
	left->root = right->root = NULL;
}
//�������
void PreOrderTree(BinaryTree* bt)
{
	PreOrder(bt->root);
	printf("\n");
}
void PreOrder(BTNode* t)
{
	if (!t)
		return;
	printf("%c", t->element);//���ʸ��ڵ�
	PreOrder(t->lChild);//�������������
	PreOrder(t->rChild);//�������������
}
//�������
void InOrderTree(BinaryTree* bt)
{
	InOrder(bt->root);
	printf("\n");
}
void InOrder(BTNode* t)
{
	if (!t)
		return;
	InOrder(t->lChild);//�������������
	printf("%c", t->element);//���ʸ��ڵ�
	InOrder(t->rChild);//�������������
}
//�������
void PostOrderTree(BinaryTree* bt)
{
	PostOrder(bt->root);
	printf("\n");
}
void PostOrder(BTNode* t)
{
	if (!t)
		return;
	PostOrder(t->lChild);//�������������
	PostOrder(t->rChild);//�������������
	printf("%c", t->element);//���ʸ��ڵ�
}
//��д��������Թ�������ת��ʹ��
//i�����±ꡢj��Ԫ�ء�k��ǰԪ��
void Exchange(BTNode* t, ElemType tree[MAXSIZE][2], ElemType& i, ElemType j, ElemType k)
{
	if (!t)
		return;
	//printf("%c", t->element);//���ʸ��ڵ�
	//���ӡ����ֵܣ��������ӣ��丸��ΪjҲ���Ǳ�Ԫ��
	if (t->lChild)
	{
		i++;
		tree[i][0] = t->lChild->element;
		tree[i][1] = k;
		//�����ݹ�
		Exchange(t->lChild, tree, i, k, i);//����������
	}
	//���ӡ����ֵܣ������ֵܣ�i++�����������һ�У�ͬʱ�õ�ĸ��׺͵�ǰ����ͬ��
	if (t->rChild)
	{
		i++;
		tree[i][0] = t->rChild->element;
		tree[i][1] = j;
		//�����ݹ�
		Exchange(t->rChild, tree, i, j, i);//����������
	}
}
//��α���
void LevelOrderTree(BinaryTree* tree)
{
	if (!tree->root)
		return;
	queue<BTNode*> Q;// Q�����ڴ洢 BTNode ������͵Ķ���
	BTNode* p = tree->root;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		printf("%c", p->element);
		if (p->lChild)
			Q.push(p->lChild);
		if (p->rChild)
			Q.push(p->rChild);
	}
}
void ExchangeThre(BinaryTree* bt, ElemType btByParent[MAXSIZE][2])
{
	BTNode* p = bt->root;
	//iΪ��ǰ���������У�jΪ��ǰ�ְ�
	ElemType i = 0, j = -1;
	btByParent[i][0] = p->element;//���Ȼ�ȡ���ڵ������
	btByParent[i][1] = j;
	//�������������������ת��Ϊ���洢��������
	Exchange(p, btByParent, i, -1, 0);
}
//�����������
void TreeClear(BinaryTree* bt)
{
	Clear(bt->root);
}
void Clear(BTNode* t)
{
	if (!t)
		return;
	Clear(t->lChild);//���������
	Clear(t->rChild);//���������
	free(t);//������ڵ�
}
//�����������������
//ע�������˳����Ҫ��ÿһ�������Ľ�β���ϱ�Ƿ�#
BTNode* PreCreateBT(BTNode* t)
{
	char ch;
	ch = getchar(); //�������� �����µ�ǰ�������ڵ��Ԫ��
	if (ch == '#') //����Ϊ#��ʾ���ｨ���ն��������������㷨�Ŀղ���
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		if (t)
		{
			t->element = ch;//��������
		}
		else
		{
			exit(1);
		}
		t->lChild = PreCreateBT(t->lChild); //����������
		t->rChild = PreCreateBT(t->rChild); //����������
	}
	return t;
}
void PreMakeTree(BinaryTree* bt)
{
	bt->root = PreCreateBT(bt->root);
}
//�������ĸ߶�
int TreeSize(BinaryTree* bt)
{
	return Size(bt->root);
	printf("\n");
}
int Size(BTNode* t)
{
	if (!t)
		return 0;
	else
		return Size(t->lChild) + Size(t->rChild) + 1;
}
BTNode* Exchange(BTNode* t)                           //����������������
{
	if (t == NULL)
		return NULL;
	BTNode* q = (BTNode*)malloc(sizeof(BTNode));
	if (q)
	{
		q->element = t->element;
	}
	else
	{
		exit(1);
	}
	q->lChild = Exchange(t->rChild);
	q->rChild = Exchange(t->lChild);
	return q;
}

int main()
{
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));
	PreMakeTree(bt);
	ElemType tree[MAXSIZE][2];
	ExchangeThre(bt, tree);



	//printf("%d", TreeSize(bt));
	return 0;
}