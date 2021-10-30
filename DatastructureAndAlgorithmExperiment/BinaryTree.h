#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include <iostream>
#include"Struct.h"
using namespace std;

void Create(BinaryTree* bt);
BTNode* NewNode(ElemType x, BTNode* ln, BTNode* rn);
void MakeTree(BinaryTree* bt, ElemType e, BinaryTree* left, BinaryTree* right);
void PreOrderTree(BinaryTree* bt);
void PreOrder(BTNode* t);
void InOrderTree(BinaryTree* bt);
void InOrder(BTNode* t);
void PostOrderTree(BinaryTree* bt);
void PostOrder(BTNode* t);
void TreeClear(BinaryTree* bt);
void Clear(BTNode* t);
BTNode* PreCreateBT(BTNode* t, FILE* fp);
void PreMakeTree(BinaryTree* bt, FILE* fp);
void LevelOrderTree(BinaryTree* tree, char* PreOrderResult);
void BinaryTreeToForest(BTNode* p, Tree* t, int & i, int j, int k);
void ExchangeBinaryTreeToForest(BinaryTree* bt, Tree* t);
