#include "..\Include\CAPP_Sphere.h"
#include "math.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

void Sphere::CreateSphere(CVector3 center, float radio, int heightsegments, int widthsegments)
{
	float m_radiotem;
	float m_Positiontem;
	int size = 1;
	m_Position = new CVector3[3];
	m_heightangle = 180 / heightsegments;
	m_widthangle = 360 / widthsegments;
	for (int i = 0; i < heightsegments;i++) {
		m_Position[i].setValues(cos((m_heightangle*i) - 90)*radio, sin((m_heightangle*i) - 90)*radio, 0);
		if (0 != m_Position[i].getX)
		{
			m_radiotem = m_Position[i].getX;
			m_Positiontem = m_Position[i].getY;
			for (int j = 0; j < widthsegments; j++) {
				m_Position[i + size++].setValues(cos((m_widthangle*i) - 90)*m_radiotem, m_Positiontem, sin((m_widthangle*i) - 90)*m_radiotem);
			}
		}
	}
	size += heightsegments;
}
