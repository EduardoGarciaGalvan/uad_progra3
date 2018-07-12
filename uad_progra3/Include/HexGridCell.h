#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class HexGridCell :public C3DModel
{
public:
	HexGridCell(int DimensionX, int DimensionY);
	~HexGridCell();
	void CrearHexagono();

private:
	CVector3 Center;
	CVector3 vertice[5];
	unsigned int Texture = 0;
	C3DModel *Object = NULL;
};