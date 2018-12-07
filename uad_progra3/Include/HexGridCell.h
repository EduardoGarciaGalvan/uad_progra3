#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class CHexGridCell {
public:
	CHexGridCell(CVector3 center, float size, bool isPointy);
	CHexGridCell();
	~CHexGridCell();
private:
	void Poligono();
	CVector3 m_pVertices[6];
	bool m_isPointy;
	CVector3 m_center;
	float m_size;
};