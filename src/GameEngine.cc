#include <iostream>
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "State.h"
#include "Enums.h"
#include "SDLInclude.h"
#include "Player.h"
#include <stdexcept>
#include <vector>

using namespace std;

GameEngine::GameEngine() {
	player1_ptr_ = new Player();
	player2_ptr_ = new Player();

	stateVector_.push_back(new Player1State(&graphicsengine_, &gameworld_, &soundplayer_, player1_ptr_));
	stateVector_.push_back(new NetworkState(&graphicsengine_, &gameworld_, &soundplayer_));
	stateVector_.push_back(new OptionState(&graphicsengine_, &gameworld_, &soundplayer_));
	stateVector_.push_back(new ExitGame(&graphicsengine_, &gameworld_, &soundplayer_));
	stateVector_.push_back(new Fire(&graphicsengine_, &gameworld_, &soundplayer_));
	stateVector_.push_back(new Meny(&graphicsengine_, &gameworld_, &soundplayer_));
	stateVector_.push_back(new Player2State(&graphicsengine_,&gameworld_, &soundplayer_, player2_ptr_));
	stateVector_.push_back(new InitState(&graphicsengine_,&gameworld_, &soundplayer_));
	stateVector_.push_back(new SetNameState(&graphicsengine_,&gameworld_,&soundplayer_,player1_ptr_,player2_ptr_));
	stateVector_.push_back(new SelectLevelState(&graphicsengine_,&gameworld_,&soundplayer_));

	currentState_ = INITSTATE;
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

	//sound_.playMusic(0,1);
	SDL_Event event;
	//soundplayer_.playMusic(0,0);

	while(currentState_ != EXITGAME)
		{
			ticks_ = SDL_GetTicks();
			stateVector_.at(currentState_) ->render();
			graphicsengine_.showScreenBufferOnScreen();

			stateVector_.at(currentState_) ->logic();

			while(SDL_PollEvent(&event))
			{
				if((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_q)))
					currentState_ = EXITGAME;
				else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
					return_to_meny();
				else
					stateVector_.at(currentState_) ->handle_input(event);
			}

			currentState_ = stateVector_.at(currentState_)->next_state();

				if((playerTurn_ == PLAYER1STATE) && (currentState_ == FIREEND))
				{
					playerTurn_ = PLAYER2STATE;
					currentState_ = PLAYER2STATE;
					gameworld_.set_wind(.1*((rand()%200) - 100));
				}
				else if(currentState_ == FIREEND)
				{
					playerTurn_ = PLAYER1STATE;
					currentState_ = PLAYER1STATE;
					gameworld_.set_wind(.1*((rand()%200) - 100));
				}

			regulate_fps();

		}

	cleanup();
}


bool GameEngine::init_SDL()
{
	return !(SDL_Init(SDL_INIT_VIDEO) == -1);
}


void GameEngine::cleanup()
{

	cout << "Running SDL_Quit()";
	soundplayer_.uninit();

	SDL_Quit();
	cout << "    [OK]" << endl;
	}


void GameEngine::return_to_meny()
	{
		if((currentState_ == PLAYER1STATE) || (currentState_ == PLAYER2STATE))
		{	graphicsengine_.clearScreenBuffer(0);
			graphicsengine_.showScreenBufferOnScreen();
			graphicsengine_.drawTextToScreenBuffer("Game aborted - returning to game meny", 0,0, 255,255,255);
			graphicsengine_.showScreenBufferOnScreen();
			SDL_Delay(1000);
			currentState_ = MENY;
		}
	}




