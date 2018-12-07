#include "../Include/HexGridCell.h"
#define GRAD_RAD 0.0174532925199432957692
#define TEXTURE 0
#ifdef ispointy
#define ANGULO 60
#else
#define ANGULO 30
#endif // ispointy

CHexGridCell::CHexGridCell(CVector3 center, float size, bool isPointy)
{
	m_center = center;
	m_size = size;
	m_isPointy = isPointy;
	Poligono();
}

CHexGridCell::CHexGridCell()
{
	CHexGridCell(CVector3(0.0f,0.0f,0.0f),1.0f,true);
	Poligono();
}

CHexGridCell::~CHexGridCell()
{
}

void CHexGridCell::Poligono()
{
	for (int i = 0; i < m_size; i++)
	{
		m_pVertices[i].setValues(m_center.getX() + (m_size/2) * sin(GRAD_RAD*(i * ANGULO)), 0, m_center.getZ() + (m_size/2) * cos(GRAD_RAD*(i * ANGULO)));
	}
}
