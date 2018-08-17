
#include "../Include/HexGridCell.h"
#include "Math.h"
#include <iostream>

HexGridCell::HexGridCell(){
}

HexGridCell::~HexGridCell()
{

}

void HexGridCell::CrearHexagono(CVector3 centro, const float RADIO, bool ispointy) {
	Radio = RADIO;
	this->centro = centro;
	this->ispointy = ispointy;
	for (int i = 0; i < 6; i++)
	{
		vertice[i].setValues(centro.getX() + Radio * sin(gradRad*(i * ANGULO)), 0, centro.getZ() + Radio * cos(gradRad*(i * ANGULO)));
	}
}

