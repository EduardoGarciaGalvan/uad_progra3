#pragma once
#include "C3DModel.h"
#include "CVector3.h"
#define GRAD_RAD 0.0174532925199432957692
#define TEXTURE 0
#ifdef ispointy
#define ANGULO 60
#else
#define ANGULO 30
#endif // ispointy


class HexGridCell
{
public:
	HexGridCell();
	~HexGridCell();
	CVector3 vertice[6];
	void CrearHexagono(CVector3 centro, float RADIO, bool ispointy);
private:
	bool ispointy;
	unsigned int m_textureId;
	const double gradRad = GRAD_RAD;
	CVector3 centro;
	float Radio;
	unsigned int Texture = TEXTURE;
	C3DModel *Object = NULL;
};