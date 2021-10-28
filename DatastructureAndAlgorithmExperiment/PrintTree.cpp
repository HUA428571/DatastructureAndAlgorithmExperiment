#pragma once
#include<stdio.h>
#include <windows.h>
#include"Struct.h"
#include "PrintTree.h"
using namespace std;
#define ZOOM 20//绘图缩放因子为20
#define FONT "黑体"

void CalculateTree(PrintTree* pt, Tree *t)
{
	float XL = 0, XR = 0;
		int H = 1;
	int node;//要处理的节点下标
	//从根节点以下的坐标开始处理
	CalculateTreeXY(0, t, pt, XL, XR, 2);
}

//注意 H从1开始
void CalculateTreeXY(int node,Tree *t,PrintTree*pt, float & XL, float & XR, int H)
{
	//遍历以计算子节点个数
	float Xl=XL;
	int SonCount = 0;
	int Son[MAXSIZE];
	for (int i = node; i < t->treeH; i++)
	{
		if (t->tree[i][1] == node)
		{
			Son[SonCount] = i;
			SonCount++;
			pt->Tree[i].father = node;
		}
	}
	if(SonCount==0)
	{
		pt->Tree[node].element=t->tree[node][0];
		pt->Tree[node].y = H;
		pt->Tree[node].x = (XL + XR) / 2;
		return;
	}
	else
	{
		for (int i = 0; i < SonCount; i++)
		{
			XR++;
			CalculateTreeXY(Son[i], t, pt, XR, XR, H + 1);
//			SonCount--;
		}
		pt->Tree[node].element = t->tree[node][0];
		pt->Tree[node].y = H;
		pt->Tree[node].x = (Xl + XR) / 2;
		return;
	}
}
void DrawTree(PrintTree* pt, Tree* t)
{
	initgraph(1280, 720);
	//// 设置背景色为淡白色
	//setbkcolor(RGB(255, 255, 253));
	////setbkmode(TRANSPARENT);
	//// 用背景色清空屏幕
	//cleardevice();
	//settextcolor(BLACK);
	//LOGFONT format;
	//gettextstyle(&format);						// 获取当前字体设置
	//format.lfHeight = 20;						// 设置字体高度为 25
	//format.lfQuality = PROOF_QUALITY;			// 设置输出效果为最高质量  
	//format.lfPitchAndFamily = FIXED_PITCH;
	//_tcscpy_s(format.lfFaceName, _T(FONT));		// 设置字体为FONT
	//settextstyle(&format);						// 设置字体样式

	int DrawX, DrawY,FatherX,FatherY;
	//首先输出根节点
	DrawX = pt->Tree[0].x * ZOOM;
	DrawY = pt->Tree[0].y * ZOOM;
	outtextxy(DrawX, DrawY, pt->Tree[0].element);
	for (int i = 1; i < t->treeH; i++)
	{
		DrawX = pt->Tree[i].x * ZOOM;
		DrawY = pt->Tree[i].y * ZOOM;
		FatherX = pt->Tree[pt->Tree[i].father].x * ZOOM;
		FatherY = pt->Tree[pt->Tree[i].father].y * ZOOM;
		outtextxy(DrawX, DrawY, pt->Tree[i].element);
		line(DrawX, DrawY, FatherX, FatherY);
	}
	Sleep(100000);
	closegraph();
	return;
}
//DrawTreeNode