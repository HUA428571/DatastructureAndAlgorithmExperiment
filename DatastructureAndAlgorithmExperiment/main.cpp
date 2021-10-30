#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include <iostream>
#include"Struct.h"
#include"PrintTree.h"
#include"BinaryTree.h"
#include "main.h"
using namespace std;

void GUI(PrintForest* pt, Tree* t, char* PreOrderResult);
void SaveTreeTXT(Tree* t, FILE* fp);

int main()
{
	char PreOrderResult[MAXSIZE]="\0";
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));
	FILE* Readfp, *Savefp;
	if ((Readfp = fopen(".\\Data\\PreOrderTreeInput.txt", "r")) == NULL)
	{
		return -1;
	}	
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

	ExchangeBinaryTreeToForest(bt, t);
	PrintForest* pt = (PrintForest*)malloc(sizeof(printTree));
	CalculateTree(pt,t);
	LevelOrderTree(bt, PreOrderResult);
	GUI(pt, t, PreOrderResult);
	if ((Savefp = fopen(".\\Data\\TreeOutput.txt", "w")) == NULL)
	{
		return -1;
	}
	SaveTreeTXT(t, Savefp);
	return 0;
}

void GUI(PrintForest* pt, Tree* t, char* PreOrderResult)
{
	int WindowWidth = (pt->TreeMAXwidth + 2) * ZOOM;
	int WindowHeight = (pt->TreeMAXheight + 3) * ZOOM;
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
	outtextxy(10, WindowHeight - ZOOM*2, "层次遍历结果：");
	outtextxy(10, WindowHeight - ZOOM*2+ TEXTSIZE, PreOrderResult);
	Sleep(10000);
	return;
}
void SaveTreeTXT(Tree* t, FILE* fp)
{
	fprintf(fp, "element\tfather\t\n");
	fprintf(fp, "NULL\t-1\n");
	for (int i = 1; i < t->treeH; i++)
	{
		fprintf(fp, "%c\t%d\t\n",t->Element[i],t->Father[i]);
	}
	fclose(fp);
}