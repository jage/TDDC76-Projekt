/*
 * GameEngine.cpp
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#include "iostream"
#include "GameEngine.h"
#include "State.h"
#include "Enums.h"
#include "SDL/SDL.h"
#include <stdexcept>
#include <vector>

using namespace std;

GameEngine::GameEngine() {

	stateVector_.push_back(new Meny(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Player1State(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Fire(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new ExitGame(&graphicsengine_, &gameworld_));

	currentState_ = MENY;

}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}


void GameEngine::run()
{
	if(!init_SDL())
		throw logic_error("Gick ej att initera SDL");

	SDL_Event event;

int test = 1600;

	while(currentState_ != EXITGAME)
		{
			graphicsengine_.showScreenBufferOnScreen();

		    stateVector_.at(currentState_) ->render();
			stateVector_.at(currentState_) ->logic();

			while(SDL_PollEvent(&event) == true)
			{
				stateVector_.at(currentState_) ->handle_input(event);
			}

			currentState_ = stateVector_.at(currentState_)->next_state();


			SDL_Delay(30);
		};

	cout << "Thanks for using pantzer" << endl;
	cleanup();
}


bool GameEngine::init_SDL()
{
	return !(SDL_Init(SDL_INIT_VIDEO) == -1);
}


void GameEngine::cleanup()
{
	SDL_Quit();
}





