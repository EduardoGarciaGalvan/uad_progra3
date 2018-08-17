#include "../Include/World.h"



World::World()
{
	grid = new Hexgrid();
}


World::~World()
{
}

bool World::initialize(COpenGLRenderer * renderer)
{
	this->renderer = renderer;
	return grid->initialize(renderer);
}

void World::render() {
	float HexColor[3] = { 200.0f, 160.0f, 16.0f }; // Color
	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CVector3(-8, -8, -17));
	renderer->renderWireframeObject(grid->getWireframeID(),
		grid->getArrayID(),
		4 * DIMENSIONES*DIMENSIONES, HexColor, &modelMatrix);

}