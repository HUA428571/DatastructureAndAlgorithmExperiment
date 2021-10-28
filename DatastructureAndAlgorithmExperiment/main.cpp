#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include <iostream>
#include"Struct.h"
#include "PrintTree.h"
using namespace std;

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
void ExchangeThre(BinaryTree* bt, Tree* t);

//构建新二叉树
void Create(BinaryTree* bt)
{
	bt->root = NULL;
}
//创建一个新的节点，返回该节点的地址
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
//在bt节点下插入新树
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right)
{
	if (bt->root || left == right)//首先判断bt是否为空，或者左节点等于右节点
		return;
	bt->root = NewNode(e, left->root, right->root);
	left->root = right->root = NULL;
}
//先序遍历
void PreOrderTree(BinaryTree* bt)
{
	PreOrder(bt->root);
	printf("\n");
}
void PreOrder(BTNode* t)
{
	if (!t)
		return;
	printf("%c", t->element);//访问根节点
	PreOrder(t->lChild);//先序遍历左子树
	PreOrder(t->rChild);//先序遍历右子树
}
//中序遍历
void InOrderTree(BinaryTree* bt)
{
	InOrder(bt->root);
	printf("\n");
}
void InOrder(BTNode* t)
{
	if (!t)
		return;
	InOrder(t->lChild);//中序遍历左子树
	printf("%c", t->element);//访问根节点
	InOrder(t->rChild);//中序遍历右子树
}
//后序遍历
void PostOrderTree(BinaryTree* bt)
{
	PostOrder(bt->root);
	printf("\n");
}
void PostOrder(BTNode* t)
{
	if (!t)
		return;
	PostOrder(t->lChild);//后序遍历左子树
	PostOrder(t->rChild);//后序遍历右子树
	printf("%c", t->element);//访问根节点
}
//重写先序遍历以供二叉树转化使用
//i数组下标、j父元素、k当前元素
void Exchange(BTNode* p, Tree* t, ElemType& i, ElemType j, ElemType k)
{
	if (!p)
		return;
	//printf("%c", t->element);//访问根节点
	//左孩子、右兄弟，处理左孩子，其父亲为j也就是本元素
	if (p->lChild)
	{
		i++;
		t->tree[i][0] = p->lChild->element;
		t->tree[i][1] = k;
		t->treeH++;
		//继续递归
		Exchange(p->lChild, t, i, k, i);//遍历左子树
	}
	//左孩子、右兄弟，处理兄弟，i++进入数组的下一行，同时该点的父亲和当前点相同。
	if (p->rChild)
	{
		i++;
		t->tree[i][0] = p->rChild->element;
		t->tree[i][1] = j;
		t->treeH++;
		//继续递归
		Exchange(p->rChild, t, i, j, i);//遍历右子树
	}
}
//层次遍历
void LevelOrderTree(BinaryTree* tree)
{
	if (!tree->root)
		return;
	queue<BTNode*> Q;// Q是用于存储 BTNode 结点类型的队列
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
void ExchangeThre(BinaryTree* bt, Tree* t)
{
	BTNode* p = bt->root;
	//i为当前数组所在行，j为当前爸爸
	ElemType i = 0, j = -1;
	t->tree[i][0] = p->element;//首先获取根节点的数据
	t->tree[i][1] = j;
	t->treeH++;
	//先序遍历二叉树并将其转化为树存储在数组中
	Exchange(p, t, i, -1, 0);
}
//void PrintTree(Tree* t)
//{
//	//首先输出根节点
//	printf("%c", t->tree[0][0]);
//	//进入下一行
//	printf("\n");
//	//i为当前根节点
//	for (int i = 0; i < t->treeH; i++)
//	{
//		for (int j = i + 1; j < t->treeH; j++)
//		{
//			if (t->tree[j][1] == i)
//				printf("%c ", t->tree[0][0]);
//		}
//
//	}
//}
//二叉树的清空
void TreeClear(BinaryTree* bt)
{
	Clear(bt->root);
}
void Clear(BTNode* t)
{
	if (!t)
		return;
	Clear(t->lChild);//清除左子树
	Clear(t->rChild);//清楚右子树
	free(t);//清楚根节点
}
//先序遍历构建二叉树
//注意输入的顺序，需要在每一个子树的结尾加上标记符#
BTNode* PreCreateBT(BTNode* t)
{
	char ch;
	ch = getchar(); //输人先序 规则下当前子树根节点的元素
	if (ch == '#') //输人为#表示这里建立空二叉树，即遍历算法的空操作
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		if (t)
		{
			t->element = ch;//构造根结点
		}
		else
		{
			exit(1);
		}
		t->lChild = PreCreateBT(t->lChild); //构造左子树
		t->rChild = PreCreateBT(t->rChild); //构造右子树
	}
	return t;
}
void PreMakeTree(BinaryTree* bt)
{
	bt->root = PreCreateBT(bt->root);
}
//计算树的高度
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
BTNode* Exchange(BTNode* t)                           //交换所有左右子树
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
	Tree* t = (Tree*)malloc(sizeof(Tree));
	if (t)
	{
		t->treeH = 0;
	}
	else
	{
		exit(1);
	}
	ExchangeThre(bt, t);
	PrintTree* pt = (PrintTree*)malloc(sizeof(printTree));
	CalculateTree(pt,t);
	DrawTree(pt, t);

	//printf("%d", TreeSize(bt));
	closegraph();
	return 0;
}