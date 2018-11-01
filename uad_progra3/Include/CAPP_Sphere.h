#pragma once
#include "CVector3.h"
#include "CAppParcial2.h"

class Sphere : public CAppParcial2{
public:
	Sphere();
	~Sphere();
	void CreateSphere(CVector3 center, float radio, int heightsegments, int widthsegments);
	CVector3* m_Position;
	float m_heightangle, m_widthangle;
};