#pragma once
#include <graphics.h>

void CalculateTree(PrintForest* pt, Tree* t);

void CalculateTreeXY(int node, Tree* t, PrintForest* pt, float XL, float& XR, int H);

void DrawTree(PrintForest* pt, Tree* t);
