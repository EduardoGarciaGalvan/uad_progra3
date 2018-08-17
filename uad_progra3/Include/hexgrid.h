#pragma once
#include "HexGridCell.h"
#include "COpenGLRenderer.h"

#define DIMENSIONES 3
#define RADIO 1
#define CENTROX 0
#define CENTROY 0
#define CENTROZ 0
#define ISPOINTY true

class Hexgrid {
public:

	Hexgrid();
	~Hexgrid();
	bool initialize(COpenGLRenderer * renderer);

	unsigned int* getWireframeID();
	unsigned int* getArrayID();
private:

	void CrearDimensiones();
	CVector3 centro;
	const float Hight = sqrt(3)*(RADIO);
	const float Width = (2 * RADIO);
	const float horDist = Width * (3 / 4);
	const float verDist = Hight;
	HexGridCell * HexGrid[DIMENSIONES][DIMENSIONES];
	unsigned short vertexIndices[4 * 3 * DIMENSIONES*DIMENSIONES];
	float *verticesRaw;
	unsigned int vertexArrayObjectID;
	unsigned int WireframeID;
};