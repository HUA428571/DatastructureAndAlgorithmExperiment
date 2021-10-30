#pragma once
#include<stdio.h>
#include <windows.h>
#include"Struct.h"
#include "PrintTree.h"
using namespace std;

//告诉我，为什么，我要抽到一个图形化树的题目！
void CalculateTree(PrintForest* pt, Tree *t)
{
	float XL = 0, XR = 0;
	int H = 1;
	pt->TreeMAXheight=0;
	int node;//要处理的节点下标
	//从根节点以下的坐标开始处理
	CalculateTreeXY(0, t, pt, XL, XR, 0);
	pt->TreeMAXwidth = XR-1;
}

//注意 H从0开始
//(当前节点下标，，，左侧坐标开始，右侧坐标结束，高）
void CalculateTreeXY(int node,Tree *t,PrintForest*pt, float XL, float & XR, int H)
{
	//遍历以计算子节点个数
	//设定一个变量存储现有横坐标，这个坐标不会被递归函数改变。
	float LocationXnow=XL;
	int SonCount = 0;
	int Son[MAXSIZE];
	for (int i = node; i < t->treeH; i++)
	{
		if (t->Father[i] == node)
		{
			Son[SonCount] = i;
			SonCount++;
			pt->Tree[i].father = node;
		}
	}
	//没有孩子，为根节点
	if(SonCount==0)
	{
		pt->Tree[node].element=t->Element[node];
		pt->Tree[node].y = H;
		pt->Tree[node].x = XR;
		//遇到根节点，右节点位置计数加一
		XR++;
		//更新数的高度
		if (H > pt->TreeMAXheight)
			pt->TreeMAXheight = H;
		return;
	}
	else
	{
		//递归调用位置函数计算函数
		for (int i = 0; i < SonCount; i++)
		{
			CalculateTreeXY(Son[i], t, pt, XR, XR, H + 1);
		}
		pt->Tree[node].element = t->Element[node];
		pt->Tree[node].y = H;
		pt->Tree[node].x = (LocationXnow + XR-1) / 2;
		return;
	}
}
void DrawTree(PrintForest* pt, Tree* t)
{
	int NodeX,NodeY,FatherX,FatherY;
	int Zoom= TEXTSIZE /5;
	//首先输出根节点
	//没想到吧，根节点是虚拟节点根本不需要输出
	for (int i = 1; i < t->treeH; i++)
	{
		NodeX = pt->Tree[i].x * ZOOM;
		NodeY = pt->Tree[i].y * ZOOM;
		FatherX = pt->Tree[pt->Tree[i].father].x * ZOOM;
		FatherY = pt->Tree[pt->Tree[i].father].y * ZOOM;
		outtextxy(NodeX, NodeY, pt->Tree[i].element);
		if (pt->Tree[i].father != 0)
		{
			line(NodeX + Zoom, NodeY, FatherX + Zoom, FatherY + TEXTSIZE);
		}
	}
	return;
}