#include "../Include/CAppGrid.h"

CAppGrid::CAppGrid()
{
	cout << "Constructor: CAppGrid()" << endl;
	world = new World();
}

CAppGrid::CAppGrid(int window_width, int window_height)
{
	cout << "Constructor: CAppGrid(int window_width, int window_height)" << endl;
	world = new World();
}

CAppGrid::~CAppGrid()
{
	cout << "Destructor: ~CAppGrid()" << endl;
}

void CAppGrid::initialize()
{

}

void CAppGrid::run()
{
	initialize();

	// Check if CGameWindow object and window library been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPPHEXGRID_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.15f, 0.75f, 0.75f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());
			// Initialize a test cube
			world->initialize(getOpenGLRenderer());
			// Create our menu (add all menu items)
			if (!initializeMenu())
			{
				return;
			}

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

bool CAppGrid::initializeMenu()
{
	cout << "CAppGrid::initializeMenu()" << endl;

	return true;
}

void CAppGrid::update(double deltaTime)
{
}

void CAppGrid::onMouseMove(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
	}
}

void CAppGrid::render()
{
	CGameMenu *menu = getMenu();
	CVector3 objPos2;

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		menu->render(getOpenGLRenderer());
	}
	else // Otherwise, render active object if loaded (or test cube if no object is loaded)
	{
		// White 
		float color[3] = { 1.0f, 1.0f, 1.0f };

		//Render the world
		world->render();
	}
}

void CAppGrid::executeMenuAction()
{
	if (getMenu() != NULL)
	{
	}
}