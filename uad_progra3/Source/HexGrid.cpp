#include "../Include/HexGrid.h"

CHexGrid::CHexGrid():
	CApp(),
world(NULL)
{
}

CHexGrid::~CHexGrid()
{
}

void CHexGrid::buildworld()
{
	world = new CHexGridCell();
	for (int i = 0; i < CELLSIZE; i++)
	{
		for (int j = 0; j < CELLSIZE; j++)
		{
			m_vertexIndices[i + j] = (*world)->m_pVertices[i].getX();
		}
	}
}
