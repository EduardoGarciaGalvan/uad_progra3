#pragma once


#ifndef CAPPGRID_H
#define CAPPGRID_H

#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "World.h"

class CAppGrid : public CApp
{
private:
	World * world;
	int DimensionX, DimensionY;
	bool isPointyHex;
	float Size;
	unsigned int indiceVertex[];

protected:
	// Method to initialize the menu
	bool initializeMenu();


public:
	// Constructors and destructor
	CAppGrid();
	CAppGrid(int window_width, int window_height);
	~CAppGrid();


	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Methods specific to CAppParcial2 only
	// -------------------------------------


	void onMouseMove(float deltaX, float deltaY);

};

#endif // !CAPPGRID_H