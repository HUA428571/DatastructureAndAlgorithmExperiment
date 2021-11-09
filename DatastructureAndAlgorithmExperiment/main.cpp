#pragma once
/******************************************************
 * NJUPT �㷨�����ݽṹ���
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

//GUI������ƺ���
void GUI(PrintForest* pt, Tree* t, char* PreOrderResult);
//�洢������ݵ��ı��ļ���
void SaveTreeTXT(Tree* t, FILE* fp, char* PreOrderResult);

int main()
{
	//�洢��α����Ľ���Թ����
	char PreOrderResult[MAXSIZE] = "\0";
	//������������ķ�ʽ�洢
	BinaryTree* bt = (BinaryTree*)malloc(sizeof(BinaryTree));
	FILE* Readfp, * Savefp;
	if ((Readfp = fopen(".\\Data\\PreOrderTreeInput.txt", "r")) == NULL)
	{
		return -1;
	}
	//����������ķ�ʽ���������
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
	//��������ת��Ϊɭ�ֲ�����˫�ױ�ʾ���洢
	ExchangeBinaryTreeToForest(bt, t);
	PrintForest* pt = (PrintForest*)malloc(sizeof(printTree));
	//����ڵ�����λ�ã����ں����������
	CalculateTree(pt, t);
	//��α���������
	LevelOrderTree(bt, PreOrderResult);
	//����ͼ�λ����
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
	//����Ĵ�С�������Ǽ���ó������Ĵ�С����
	int WindowWidth = (pt->TreeMAXwidth + 2) * ZOOM;
	int WindowHeight = (pt->TreeMAXheight + 3) * ZOOM;
	//����ͼ�λ�����
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
	//�����α����Ľ��
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2, "��������α��������");
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2 + TEXTSIZE, PreOrderResult);
	outtextxy(-ZOOM + 20, WindowHeight - ZOOM * 2 + TEXTSIZE + TEXTSIZE, "��������˳�...");
	return;
}
void SaveTreeTXT(Tree* t, FILE* fp, char* PreOrderResult)
{
	fprintf(fp, "ע�⣬�����ڴ洢ɭ�ֵ�ʱ��ʹ��һ������ĸ��ڵ㣬�洢��0��λ��ÿһ�����ĸ����Դ�Ϊ���ס�\n");
	fprintf(fp, "Copyright 2021 HuaCL\n");
	fprintf(fp, "\n");
	fprintf(fp, "\telement\tfather\t\n");
	fprintf(fp, "0\tNULL\t-1\n");
	for (int i = 1; i < t->treeH; i++)
	{
		fprintf(fp, "%d\t%c\t%d\t\n", i, t->Element[i], t->Father[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "��������α��������\n");
	fprintf(fp, PreOrderResult);
	fclose(fp);
}