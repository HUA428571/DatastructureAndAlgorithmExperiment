#pragma once
#include "BinaryTree.h"
using namespace std;

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

//��д��������Թ�������ת��ʹ��
//i�����±ꡢj��Ԫ�ء�k��ǰԪ��
void BinaryTreeToForest(BTNode* p, Tree* t, int& i, int j, int k)
{
	if (!p)
		return;
	//ע������һ������Ҳ����˵����ڵ������������һ���µ��������ǰ���һ����һ������˳����
	// �������ȴ���������
	//���ӡ����ֵܣ��������ӣ��丸��ΪjҲ���Ǳ�Ԫ��
	if (p->lChild)
	{
		i++;
		t->Element[i] = p->lChild->element;
		t->Father[i] = k;
		t->treeH++;
		//�����ݹ�
		BinaryTreeToForest(p->lChild, t, i, k, i);//����������
	}
	//���ӡ����ֵܣ������ֵܣ�i++�����������һ�У�ͬʱ�õ�ĸ��׺͵�ǰ����ͬ��
	if (p->rChild)
	{
		i++;
		t->Element[i] = p->rChild->element;
		t->Father[i] = j;
		t->treeH++;
		//����丸���Ƿ�Ϊ-1���������Ϊ����ϱ�ǩ
		//�����ݹ�
		BinaryTreeToForest(p->rChild, t, i, j, i);//����������
	}
}
void ExchangeBinaryTreeToForest(BinaryTree* bt, Tree* t)
{
	BTNode* p = bt->root;
	//iΪ��ǰ���������У�jΪ��ǰ�ְ�
	//����ɭ����һ����������������ʹ��һ������ڵ㣬������ɭ�ֵĸ��ڵ�������һ��
	//�������ڵ��λ��Ϊ-1
	int i = 0, j = -1;
	t->Element[i] = ' ';//��������ڵ������
	t->Father[i] = -1;
	t->treeH++;
	i++;
	t->Element[i] = p->element;//���Ȼ�ȡ���ڵ������
	t->Father[i] = 0;
	t->treeH++;
	//�������������������ת��Ϊ���洢��������
	BinaryTreeToForest(p, t, i, 0, 1);
}

//��α���
void LevelOrderTree(BinaryTree* tree, char* PreOrderResult)
{
	int i = 0;
	if (!tree->root)
		return;
	queue<BTNode*> Q;// Q�����ڴ洢 BTNode ������͵Ķ���
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
	Clear(t->lChild);//���������
	Clear(t->rChild);//���������
	free(t);//������ڵ�
}

//�����������������
//ע�������˳����Ҫ��ÿһ�������Ľ�β���ϱ�Ƿ�#
BTNode* PreCreateBT(BTNode* t, FILE* fp)
{
	char ch;
	ch = fgetc(fp); //�������� �����µ�ǰ�������ڵ��Ԫ��
	if (ch == '$')
	{
		return t;
	}
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
		t->lChild = PreCreateBT(t->lChild, fp); //����������
		t->rChild = PreCreateBT(t->rChild, fp); //����������
	}
	return t;
}
void PreMakeTree(BinaryTree* bt, FILE* fp)
{
	bt->root = PreCreateBT(bt->root, fp);
	fclose(fp);
}