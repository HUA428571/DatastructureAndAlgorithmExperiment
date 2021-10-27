#pragma once
#include<stdio.h>
#include"Struct.h"
#include "PrintTree.h"
#define ZOOM 10//��ͼ��������Ϊ10
#define FONT "����"

void CalculateTree(PrintTree* pt, Tree *t)
{
	int XL = 0, XR = 0, H = 1;
	int node;//Ҫ����Ľڵ��±�
	//�Ӹ��ڵ����µ����꿪ʼ����
	CalculateTreeXY(1, t, pt, XL, XR, 2);
}

//ע�� H��1��ʼ
void CalculateTreeXY(int node,Tree *t,PrintTree*pt, int& XL, int& XR, int H)
{
	//�����Լ����ӽڵ����
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
	// ���ñ���ɫΪ����ɫ
	setbkcolor(RGB(255, 255, 253));
	setbkmode(TRANSPARENT);
	// �ñ���ɫ�����Ļ
	cleardevice();
	settextcolor(BLACK);
	LOGFONT format;
	gettextstyle(&format);						// ��ȡ��ǰ��������
	format.lfHeight = 20;						// ��������߶�Ϊ 25
	format.lfQuality = PROOF_QUALITY;			// �������Ч��Ϊ�������  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T(FONT));		// ��������ΪFONT
	settextstyle(&format);						// ����������ʽ






	return;
}