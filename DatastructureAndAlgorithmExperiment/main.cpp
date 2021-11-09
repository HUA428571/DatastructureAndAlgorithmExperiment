#pragma once
/******************************************************
 * NJUPT 算法与数据结构设计
 * 20211013
 *
 * Copyright 2021 HuaCL
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <conio.h>
#include "Struct.h"
#include "PrintTree.h"
#include "BinaryTree.h"
using namespace std;

//GUI界面绘制函数
void GUI(PrintForest* pt, Tree* t, char* PreOrderResult);
//存储相关数据到文本文件中
void SaveTreeTXT(Tree* t, FILE* fp, char* PreOrderResult);

int main()
{
	//存储层次遍历的结果以供输出
	char PreOrderResult[MAXSIZE] = "\0";
	//二叉树以链表的方式存储
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));
	FILE* Readfp, * Savefp;
	if ((Readfp = fopen(".\\Data\\PreOrderTreeInput.txt", "r")) == NULL)
	{
		return -1;
	}
	//用先序遍历的方式构造二叉树
	PreMakeTree(bt, Readfp);
	Tree* t = (Tree*)malloc(sizeof(Tree));
	if (t)
	{
		t->treeH = 0;
	}
	else
	{
		exit(1);
	}
	//将二叉树转化为森林并且以双亲表示法存储
	ExchangeBinaryTreeToForest(bt, t);
	PrintForest* pt = (PrintForest*)malloc(sizeof(printTree));
	//计算节点的相对位置，用于后续的树输出
	CalculateTree(pt, t);
	//层次遍历二叉树
	LevelOrderTree(bt, PreOrderResult);
	//启动图形化输出
	GUI(pt, t, PreOrderResult);
	if ((Savefp = fopen(".\\Data\\TreeOutput.txt", "w")) == NULL)
	{
		return -1;
	}
	SaveTreeTXT(t, Savefp, PreOrderResult);
	while (!_kbhit())
	{
		Sleep(20);
	}
	return 0;
}

void GUI(PrintForest* pt, Tree* t, char* PreOrderResult)
{
	//界面的大小根据我们计算得出的树的大小决定
	int WindowWidth = (pt->TreeMAXwidth + 2) * ZOOM;
	int WindowHeight = (pt->TreeMAXheight + 3) * ZOOM;
	//启动图形化界面
	initgraph(WindowWidth, WindowHeight);

	//以下部分都是一些UI优化的部分了
	//设置背景色为淡白色
	setbkcolor(RGB(255, 255, 253));
	setbkmode(TRANSPARENT);
	//用背景色清空屏幕
	cleardevice();
	settextcolor(BLACK);
	LOGFONT format;
	gettextstyle(&format);						// 获取当前字体设置
	format.lfHeight = TEXTSIZE;					// 设置字体高度为20
	format.lfQuality = PROOF_QUALITY;			// 设置输出效果为最高质量  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T(FONT));		// 设置字体为FONT
	settextstyle(&format);						// 设置字体样式
	//字体设置完毕

	setlinecolor(BLACK);			//设置线条
	setorigin(ZOOM, 0);				//设置绘图原点

	DrawTree(pt, t);
	//输出层次遍历的结果
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2, "二叉树层次遍历结果：");
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2 + TEXTSIZE, PreOrderResult);
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2 + TEXTSIZE + TEXTSIZE, "按任意键退出...");
	return;
}
void SaveTreeTXT(Tree* t, FILE* fp, char* PreOrderResult)
{
	fprintf(fp, "注意，我们在存储森林的时候使用一个虚拟的根节点，存储在0号位。每一个树的根都以此为父亲。\n");
	fprintf(fp, "Copyright 2021 HuaCL\n");
	fprintf(fp, "\n");
	fprintf(fp, "\telement\tfather\t\n");
	fprintf(fp, "0\tNULL\t-1\n");
	for (int i = 1; i < t->treeH; i++)
	{
		fprintf(fp, "%d\t%c\t%d\t\n", i, t->Element[i], t->Father[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "二叉树层次遍历结果：\n");
	fprintf(fp, PreOrderResult);
	fclose(fp);
}