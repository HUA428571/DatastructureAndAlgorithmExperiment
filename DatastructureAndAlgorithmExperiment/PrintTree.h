#pragma once
#include <graphics.h>

void CalculateTree(PrintTree* pt, Tree* t);

void CalculateTreeXY(int node, Tree* t, PrintTree* pt, float & XL, float & XR, int H);

void DrawTree(PrintTree* pt, Tree* t);
