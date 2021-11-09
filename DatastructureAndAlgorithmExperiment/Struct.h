#pragma once
#define QUEUESIZE 999
#define MAXSIZE 999
#define ZOOM 50//��ͼ��������Ϊ20
#define FONT "����"
#define TEXTSIZE 20

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
	ElemType Element[MAXSIZE];
	int Father[MAXSIZE];
	int treeH = 0;
}Tree;

//Ȼ����ĥ���ǵĻ������ڿ�ʼ��
//���������Ļ�һ�����ɣ���������Ϊ��������Ƚ���һ���ṹ�壬�����洢һ������Ҫ����Ϣ
//ע�������x��y�Ⱦ�Ϊ�������꣬��ʵ�ʻ�ͼʱ����Ҫת��Ϊ��Ļ���꣨���Ϸ���ϵ������
typedef struct printTreeNode
{
	ElemType element;
	float x;		//x���꣬��������Ͻ�
	float y;		//y����
	int father;		//���ֵ��±�
}PrintTreeNode;
typedef struct printTree
{
	int TreeMAXheight;	//�������߶ȣ����ڹ���ͼ�λ�����ʱȷ����С
	int TreeMAXwidth;	//��������ȣ����ڹ���ͼ�λ�����ʱȷ����С
	PrintTreeNode Tree[MAXSIZE];
}PrintForest;