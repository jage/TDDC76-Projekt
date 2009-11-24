#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "State.h"
#include "SDL.h"
#include <list>
#include <iostream>

using namespace std;

GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{}

void GameEngine::run()
{
//Start SDL
	SDL_Init(SDL_INIT_VIDEO);

	State* currentstate = new MainState(&gfx, &gameworld);

	int ticks = 0;
	int fps = 120;

	Element ball(CANNONBALL, 300,0,300,0,0,1);
	gameworld.add_element(ball);
	Element cannon(CANNON, 0, 0, 0, 0, 0, 0);
	gameworld.add_element(cannon);

	for(int i = 0; i < 500; ++i)
	{
		ticks = SDL_GetTicks();
		currentstate->logic();
		currentstate->render();
		ticks -= SDL_GetTicks();

		if (-ticks < 1000 / fps)
			SDL_Delay(1000 / fps + ticks);
	}

	//Quit SDL
	SDL_Quit();

}