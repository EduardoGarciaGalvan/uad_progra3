/*#pragma once
#include "../Include/World.h"
#include "../Include/CVector3.h"
#include <vector>
using namespace std;

class QuadTreeNode {

public:
	QuadTreeNode();
	~QuadTreeNode();
	void SubDivide();
private:
	CVector3 m_Corner[4];
	vector<HexGridCell> VCells;
	int m_CellLimit = 3;
};*/
