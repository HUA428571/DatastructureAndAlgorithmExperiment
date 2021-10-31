#pragma once
#include "BinaryTree.h"
using namespace std;

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

//重写先序遍历以供二叉树转化使用
//i数组下标、j父元素、k当前元素
void BinaryTreeToForest(BTNode* p, Tree* t, int& i, int j, int k)
{
	if (!p)
		return;
	//注意这是一个树，也就是说其根节点的右子树都是一颗新的树，我们按照一棵树一棵树的顺序存放
	// 即我们先处理左子树
	//左孩子、右兄弟，处理左孩子，其父亲为j也就是本元素
	if (p->lChild)
	{
		i++;
		t->Element[i] = p->lChild->element;
		t->Father[i] = k;
		t->treeH++;
		//继续递归
		BinaryTreeToForest(p->lChild, t, i, k, i);//遍历左子树
	}
	//左孩子、右兄弟，处理兄弟，i++进入数组的下一行，同时该点的父亲和当前点相同。
	if (p->rChild)
	{
		i++;
		t->Element[i] = p->rChild->element;
		t->Father[i] = j;
		t->treeH++;
		//检测其父亲是否为-1，如果是则为其打上标签
		//继续递归
		BinaryTreeToForest(p->rChild, t, i, j, i);//遍历右子树
	}
}
void ExchangeBinaryTreeToForest(BinaryTree* bt, Tree* t)
{
	BTNode* p = bt->root;
	//i为当前数组所在行，j为当前爸爸
	//对于森林这一个特殊的情况，我们使用一个虚拟节点，把所有森林的根节点链接在一起。
	//这个虚拟节点的位置为-1
	int i = 0, j = -1;
	t->Element[i] = ' ';//首先虚拟节点的数据
	t->Father[i] = -1;
	t->treeH++;
	i++;
	t->Element[i] = p->element;//首先获取根节点的数据
	t->Father[i] = 0;
	t->treeH++;
	//先序遍历二叉树并将其转化为树存储在数组中
	BinaryTreeToForest(p, t, i, 0, 1);
}

//层次遍历
void LevelOrderTree(BinaryTree* tree, char* PreOrderResult)
{
	int i = 0;
	if (!tree->root)
		return;
	queue<BTNode*> Q;// Q是用于存储 BTNode 结点类型的队列
	BTNode* p = tree->root;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		PreOrderResult[i] = p->element;
		i++;
		if (p->lChild)
			Q.push(p->lChild);
		if (p->rChild)
			Q.push(p->rChild);
	}
	PreOrderResult[i] = '\0';
}
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
BTNode* PreCreateBT(BTNode* t, FILE* fp)
{
	char ch;
	ch = fgetc(fp); //输人先序 规则下当前子树根节点的元素
	if (ch == '$')
	{
		return t;
	}
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
		t->lChild = PreCreateBT(t->lChild, fp); //构造左子树
		t->rChild = PreCreateBT(t->rChild, fp); //构造右子树
	}
	return t;
}
void PreMakeTree(BinaryTree* bt, FILE* fp)
{
	bt->root = PreCreateBT(bt->root, fp);
	fclose(fp);
}