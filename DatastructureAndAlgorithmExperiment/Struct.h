#pragma once
#define QUEUESIZE 127
#define MAXSIZE 127
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
	ElemType Father[MAXSIZE];
	int treeH = 0;
}Tree;
//然后折磨我们的环节终于开始了
//让我们愉快的画一棵树吧！首先我们为了这件事先建立一个结构体，用来存储一切所需要的信息
typedef struct printTreeNode
{
	ElemType element;
	float x;//x坐标，相对于左上角，注意这里的x，y均为点阵坐标，在实际画图时候需要转化为屏幕坐标。
	float y;//y坐标
	int father;//他爸的下标
}PrintTreeNode;

typedef struct printTree
{
	int TreeMAXheight;
	int TreeMAXwidth;
	int TreeTreeCount;//统计有多少颗树
	int TreeRoot[MAXSIZE];//记录树的根节点所在位置
	PrintTreeNode Tree[MAXSIZE];
}PrintForest;