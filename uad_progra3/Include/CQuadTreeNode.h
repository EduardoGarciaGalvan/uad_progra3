#pragma once
#include "CQuadTree.h"

class CQuadTreeNode {
public:
	CQuadTreeNode();
	~CQuadTreeNode();
protected:
	CQuadTree *tree;
	void render();
};