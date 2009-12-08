/*
 * GameEngine.cpp
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#include "iostream"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "State.h"
#include "Enums.h"
#include "SDLInclude.h"
#include <stdexcept>
#include <vector>

using namespace std;

GameEngine::GameEngine() {


	stateVector_.push_back(new Player1State(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new NetworkState(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new OptionState(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new ExitGame(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Fire(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Meny(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Player2State(&graphicsengine_,&gameworld_));

	currentState_ = MENY;
	playerTurn_ = PLAYER1STATE;
}

GameEngine::~GameEngine() {}

void GameEngine::regulate_fps()
{
	unsigned int fps = 70;

	ticks_ = SDL_GetTicks() - ticks_;

	if(ticks_ < 1000/fps)
	{
		if(ticks_ > 2)
			{	 ++fps;
				//cout << "New fps: " << fps << endl;
			}

		SDL_Delay(1000/fps - ticks_);
	}
	else
	{
		--fps;
		//cout << "New fps: " << fps << endl;
	}
}

void GameEngine::run()
{
	if(!init_SDL())
		throw logic_error("Gick ej att initera SDL");

	SDL_Event event;

	while(currentState_ != EXITGAME)
		{
			ticks_ = SDL_GetTicks();
			stateVector_.at(currentState_) ->render();
			graphicsengine_.showScreenBufferOnScreen();

			stateVector_.at(currentState_) ->logic();

			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					currentState_ = EXITGAME;
				else
					stateVector_.at(currentState_) ->handle_input(event);
			}

			currentState_ = stateVector_.at(currentState_)->next_state();

			if(currentState_ == FIREEND)
			{
				if(playerTurn_ == PLAYER1STATE)
				{
					playerTurn_ = PLAYER2STATE;
					currentState_ = PLAYER2STATE;
				}
				else
				{
					playerTurn_ = PLAYER1STATE;
					currentState_ = PLAYER1STATE;
				}
			}

			regulate_fps();

		};

	cleanup();
}


bool GameEngine::init_SDL()
{
	return !(SDL_Init(SDL_INIT_VIDEO) == -1);
}


void GameEngine::cleanup()
{

	cout << "Running SDL_Quit()";

	SDL_Quit();
	cout << "    [OK]" << endl;
	}





