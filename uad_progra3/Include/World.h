#pragma once
#include "../Include/C3DModel.h"
#include "../Include/hexgrid.h"

class World
{
public:
	World();
	~World();
	void initialize(COpenGLRenderer * renderer);
	void render();
private:
	COpenGLRenderer * renderer;
	Hexgrid * grid;
	int x, y;
};

