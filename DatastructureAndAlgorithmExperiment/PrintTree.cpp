#pragma once
#include<stdio.h>
#include <windows.h>
#include"Struct.h"
#include "PrintTree.h"
using namespace std;

//�����ң�Ϊʲô����Ҫ�鵽һ��ͼ�λ�������Ŀ��
void CalculateTree(PrintForest* pt, Tree *t)
{
	float XL = 0, XR = 0;
	int H = 1;
	pt->TreeMAXheight=0;
	int node;//Ҫ����Ľڵ��±�
	//�Ӹ��ڵ����µ����꿪ʼ����
	CalculateTreeXY(0, t, pt, XL, XR, 0);
	pt->TreeMAXwidth = XR-1;
}

//ע�� H��0��ʼ
//(��ǰ�ڵ��±꣬����������꿪ʼ���Ҳ�����������ߣ�
void CalculateTreeXY(int node,Tree *t,PrintForest*pt, float XL, float & XR, int H)
{
	//�����Լ����ӽڵ����
	//�趨һ�������洢���к����꣬������겻�ᱻ�ݹ麯���ı䡣
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
	//û�к��ӣ�Ϊ���ڵ�
	if(SonCount==0)
	{
		pt->Tree[node].element=t->Element[node];
		pt->Tree[node].y = H;
		pt->Tree[node].x = XR;
		//�������ڵ㣬�ҽڵ�λ�ü�����һ
		XR++;
		//�������ĸ߶�
		if (H > pt->TreeMAXheight)
			pt->TreeMAXheight = H;
		return;
	}
	else
	{
		//�ݹ����λ�ú������㺯��
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
	//����������ڵ�
	//û�뵽�ɣ����ڵ�������ڵ��������Ҫ���
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