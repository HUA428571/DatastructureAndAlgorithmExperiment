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

	//���²��ֶ���һЩUI�Ż��Ĳ�����
	//���ñ���ɫΪ����ɫ
	setbkcolor(RGB(255, 255, 253));
	setbkmode(TRANSPARENT);
	//�ñ���ɫ�����Ļ
	cleardevice();
	settextcolor(BLACK);
	LOGFONT format;
	gettextstyle(&format);						// ��ȡ��ǰ��������
	format.lfHeight = TEXTSIZE;					// ��������߶�Ϊ20
	format.lfQuality = PROOF_QUALITY;			// �������Ч��Ϊ�������  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T(FONT));		// ��������ΪFONT
	settextstyle(&format);						// ����������ʽ
	//�����������

	setlinecolor(BLACK);			//��������
	setorigin(ZOOM, 0);				//���û�ͼԭ��

	DrawTree(pt, t);
	outtextxy(10, WindowHeight - ZOOM*2, "��α��������");
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