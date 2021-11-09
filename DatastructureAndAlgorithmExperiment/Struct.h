#pragma once
#define QUEUESIZE 999
#define MAXSIZE 999
#define ZOOM 50//绘图缩放因子为20
#define FONT "黑体"
#define TEXTSIZE 20

//首先我们从数据结构实验中抄来一部分代码
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

//然后折磨我们的环节终于开始了
//让我们愉快的画一棵树吧！首先我们为了这件事先建立一个结构体，用来存储一切所需要的信息
//注意这里的x，y等均为点阵坐标，在实际画图时候需要转化为屏幕坐标（乘上放缩系数）。
typedef struct printTreeNode
{
	ElemType element;
	float x;		//x坐标，相对于左上角
	float y;		//y坐标
	int father;		//他爸的下标
}PrintTreeNode;
typedef struct printTree
{
	int TreeMAXheight;	//树的最大高度，用于构建图形化界面时确定大小
	int TreeMAXwidth;	//树的最大宽度，用于构建图形化界面时确定大小
	PrintTreeNode Tree[MAXSIZE];
}PrintForest;