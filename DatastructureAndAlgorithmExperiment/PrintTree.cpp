#pragma once
#include<stdio.h>
#include <windows.h>
#include"Struct.h"
#include "PrintTree.h"
using namespace std;
#define ZOOM 20//��ͼ��������Ϊ20
#define FONT "����"

void CalculateTree(PrintTree* pt, Tree *t)
{
	float XL = 0, XR = 0;
		int H = 1;
	int node;//Ҫ����Ľڵ��±�
	//�Ӹ��ڵ����µ����꿪ʼ����
	CalculateTreeXY(0, t, pt, XL, XR, 2);
}

//ע�� H��1��ʼ
void CalculateTreeXY(int node,Tree *t,PrintTree*pt, float & XL, float & XR, int H)
{
	//�����Լ����ӽڵ����
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
	//// ���ñ���ɫΪ����ɫ
	//setbkcolor(RGB(255, 255, 253));
	////setbkmode(TRANSPARENT);
	//// �ñ���ɫ�����Ļ
	//cleardevice();
	//settextcolor(BLACK);
	//LOGFONT format;
	//gettextstyle(&format);						// ��ȡ��ǰ��������
	//format.lfHeight = 20;						// ��������߶�Ϊ 25
	//format.lfQuality = PROOF_QUALITY;			// �������Ч��Ϊ�������  
	//format.lfPitchAndFamily = FIXED_PITCH;
	//_tcscpy_s(format.lfFaceName, _T(FONT));		// ��������ΪFONT
	//settextstyle(&format);						// ����������ʽ

	int DrawX, DrawY,FatherX,FatherY;
	//����������ڵ�
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