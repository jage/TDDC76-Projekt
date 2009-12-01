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

SDL_Surface* GameEngine::load_image(string filename)
{
	SDL_Surface* loadedimage = NULL;
	SDL_Surface* optimizedimage = NULL;

	loadedimage = SDL_LoadBMP(filename.c_str());

	if (loadedimage != NULL) {
		optimizedimage = SDL_DisplayFormat(loadedimage);
	}
	SDL_FreeSurface(loadedimage);
	return optimizedimage;

}


void GameEngine::run()
{
	if((SDL_Init(SDL_INIT_VIDEO) == -1))
		throw logic_error("Gick ej att initera SDL");


	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	if (screen == NULL)
		throw logic_error("Gick ej att initiera SDL screen");
	source_image = load_image("sprite_sheet.bmp");

	SDL_Event event;

	while(currentState_ != EXITGAME)
		{
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
}
