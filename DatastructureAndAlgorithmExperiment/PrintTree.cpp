#pragma once
#include<stdio.h>
#include"Struct.h"
#include "PrintTree.h"
#define ZOOM 10//绘图缩放因子为10
#define FONT "黑体"

void CalculateTree(PrintTree* pt, Tree *t)
{
	int XL = 0, XR = 0, H = 1;
	int node;//要处理的节点下标
	//从根节点以下的坐标开始处理
	CalculateTreeXY(1, t, pt, XL, XR, 2);
}

//注意 H从1开始
void CalculateTreeXY(int node,Tree *t,PrintTree*pt, int& XL, int& XR, int H)
{
	//遍历以计算子节点个数
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
			SonCount--;
		}
		pt->Tree[node].y = H;
		pt->Tree[node].x = (XL + XR) / 2;
		return;
	}
}
void DrawTree(PrintTree* pt, Tree* t)
{
	initgraph(1280, 720);
	// 设置背景色为淡白色
	setbkcolor(RGB(255, 255, 253));
	setbkmode(TRANSPARENT);
	// 用背景色清空屏幕
	cleardevice();
	settextcolor(BLACK);
	LOGFONT format;
	gettextstyle(&format);						// 获取当前字体设置
	format.lfHeight = 20;						// 设置字体高度为 25
	format.lfQuality = PROOF_QUALITY;			// 设置输出效果为最高质量  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T(FONT));		// 设置字体为FONT
	settextstyle(&format);						// 设置字体样式






	return;
}