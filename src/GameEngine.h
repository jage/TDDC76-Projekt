#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include "SDL.h"
#include "GraphicsEngine.h"
#include "Element.h"
#include "GameWorld.h"
#include <list>
#include <iostream>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void run();
private:
	GraphicsEngine gfx;
	GameWorld gameworld;
};
#endif