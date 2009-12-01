/*
 * State.cpp
 *
 *  Created on: Nov 23, 2009
 *      Author: rosjo
 */

#include "State.h"
#include <iostream>
//#include "SDLInclude.h"
#include "SDL/SDL.h"
using namespace std;
//State---------------------------------------------------------//
State::State(GraphicsEngine* graphicengine, GameWorld* gameworld)
	: graphicsengine_ptr_(graphicengine), gameworld_ptr_(gameworld){}

State::~State() {}
//--------------------------------------------------------------//


//Meny-----------------------------------------------------------//

//Meny::Meny(){}

Meny::Meny(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld),
	   changeState_(false),
	   rendermeny_(true){}

Meny::~Meny(){}

void Meny::render(){
	if(rendermeny_)
	{
		cout << "Press an arrow key" << endl;
		rendermeny_ = false;
	}

}

void Meny::handle_input(SDL_Event& event){

	if( event.type == SDL_KEYDOWN )
	            {

	                switch( event.key.keysym.sym )
	                {
	                    case SDLK_UP:  cout << "up" << endl; break;
	                    case SDLK_DOWN: cout << "down" << endl; break;
	                    case SDLK_LEFT: cout << "left" << endl; break;
						case SDLK_RIGHT: cout << "right" << endl ; break;
						case SDLK_q: {cout << "quit" << endl; changeState_ = true;} ; break;
					}
	            }
	else if( event.type == SDL_QUIT )
	            {
	                //Quit the program
	                changeState_ = true;
	            }
}

PANZER_STATES Meny::next_state()
{
	if(changeState_ == false)
		return MENY;
	else
		return EXITGAME;
}
//---------------------------------------------------------------//

//Player1State-----------------------------------------------------------//



Player1State::Player1State(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

Player1State::~Player1State(){}

void Player1State::render(){
	cout << "Player1 state\n\n"
		 << "next up is.....\n\n";
}


PANZER_STATES Player1State::next_state()
{
	return FIRE;
}
//---------------------------------------------------------------//

//Fire-----------------------------------------------------------//



Fire::Fire(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

Fire::~Fire(){}

void Fire::render(){
	cout << "FIRE\n\n"
		 << "end game.....\n\n";
}


PANZER_STATES Fire::next_state()
{
	return EXITGAME;
}
//---------------------------------------------------------------//


//ExitGame----------------------------------------------------------//



ExitGame::ExitGame(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

ExitGame::~ExitGame(){}

void ExitGame::render(){
	cout << "Ok start over, or... \n";
}


PANZER_STATES ExitGame::next_state()
{
	return EXITGAME;
}
//---------------------------------------------------------------//


