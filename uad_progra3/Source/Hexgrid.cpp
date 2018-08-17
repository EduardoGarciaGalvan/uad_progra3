#include "../Include/hexgrid.h"
#include "../Include/COpenGLRenderer.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/Globals.h"
#include "../Include/CVector3.h"
#include <string>
#include <iostream>

Hexgrid::Hexgrid() :
	WireframeID(0),
	verticesRaw(0),
	vertexArrayObjectID(0)
{
	std::cout << "Constructor: HexGrid" << endl;
}

Hexgrid::~Hexgrid() {
	std::cout << "Destructor: HexGrid" << endl;
}

bool Hexgrid::initialize(COpenGLRenderer * renderer) {
	CrearDimensiones();

	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << VERTEX_SHADER_WIREFRAME << endl;
		cout << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		return false;
	}


	renderer->createShaderProgram(&WireframeID, resourceFilenameVS.c_str(), resourceFilenameFS.c_str());
	renderer->allocateGraphicsMemoryForObject(&WireframeID, &vertexArrayObjectID, verticesRaw, DIMENSIONES*DIMENSIONES * 6, vertexIndices, DIMENSIONES*DIMENSIONES * 12);

	return true;
}

void Hexgrid::CrearDimensiones() {
	int vertexiteration = 0;
	int vertexindexiteration = 0;
	int singleHexIndices[] = { 2,1,0,3,5,4,3,0,5,2,0,3 };
	centro.setValues(CENTROX, CENTROY, CENTROZ);
	verticesRaw = new float[DIMENSIONES*DIMENSIONES * 3 * 6];
	for (int i = 0; i < DIMENSIONES; i++)
	{
		for (int j = 0; j < DIMENSIONES; j++)
		{
			centro.setValues (CENTROX + (i % 2)*RADIO + 2 * j*RADIO, CENTROX, CENTROZ + i * ((3 * DIMENSIONES) / 2));
			HexGrid[i][j] = new HexGridCell();
			HexGrid[i][j]->CrearHexagono(centro, RADIO, ISPOINTY);
			for (int k = 0; k < 4 * 3; k++)
			{
				vertexIndices[vertexindexiteration++] = (i * DIMENSIONES * 6 + j * 6 + singleHexIndices[k]);
			}
			for (int  l= 0;  l< 6; l++)
			{
				verticesRaw[vertexiteration++] = HexGrid[i][j]->vertice[l].getX();
				verticesRaw[vertexiteration++] = HexGrid[i][j]->vertice[l].getY();
				verticesRaw[vertexiteration++] = HexGrid[i][j]->vertice[l].getZ();
			}
		}
	}
}

unsigned int* Hexgrid::getWireframeID()
{
	return &WireframeID;
}

unsigned int* Hexgrid::getArrayID()
{
	return &vertexArrayObjectID;;
}
