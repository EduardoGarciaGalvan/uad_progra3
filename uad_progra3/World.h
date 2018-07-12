#pragma once
#include "Include\CAppGrid.h"

class World
{
public:
	World();
	~World();
	void initialize();
private:
	CAppGrid Hexgrid;
};

