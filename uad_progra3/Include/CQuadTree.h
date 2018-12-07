#pragma once
#include "CQuadTreeNode.h"
#include "CApp.h"

class CQuadTree {
public:
	CQuadTree();
	~CQuadTree();
private:
	CQuadTreeNode *root;
	CGameCamera *cam;	//SHALLOW POINTER - pasar en ctor
	COpenGLRenderer *renderer;
	void render();
};