#pragma once
#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "HexGridCell.h"
#include <iostream>
#define CELLSIZE 3

class CHexGrid : public CApp{
public:
	CHexGrid();
	~CHexGrid();
private:
	CHexGridCell *world;

	unsigned short *m_vertexIndices,
		*m_normalIndices,
		*m_UVindices;

	float *m_verticesRaw,
		*m_normalsRaw,
		*m_uvCoordsRaw;
	void buildworld();
};