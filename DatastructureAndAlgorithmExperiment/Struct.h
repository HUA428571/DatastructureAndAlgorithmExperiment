#pragma once
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
typedef struct tree
{
	ElemType tree[MAXSIZE][2];
	int treeH = 0;
}Tree;
//Ȼ����ĥ���ǵĻ������ڿ�ʼ��
//���������Ļ�һ�����ɣ���������Ϊ��������Ƚ���һ���ṹ�壬�����洢һ������Ҫ����Ϣ
typedef struct printTreeNode
{
	ElemType element;
	float x;//x���꣬��������Ͻǣ�ע�������x��y��Ϊ�������꣬��ʵ�ʻ�ͼʱ����Ҫת��Ϊ��Ļ���ꡣ
	float y;//y����
	int father;//���ֵ��±�
}PrintTreeNode;

typedef struct printTree
{
	int TreeMAXheight;
	int TreeMAXwidth;
	int TreeNodeCount;
	PrintTreeNode Tree[MAXSIZE];
}PrintTree;