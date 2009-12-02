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
#include "SDL/SDL_image.h"
#include <string>

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
	   nextState_(MENY),
	   rendermeny_(true){}

Meny::~Meny(){}

void Meny::render(){
	if(rendermeny_)
	{
		cout << "Press an arrow key\n"
			 << "q - finished the 'game' \n"
			 << "p - changes to the player state\n"
			 << "" << flush;
		rendermeny_ = false;
	}

}
SDL_Surface* load_image( std::string filename )
	  {
	      //Temporary storage for the image that's loaded
	      SDL_Surface* loadedImage = NULL;

	      //The optimized image that will be used
	      SDL_Surface* optimizedImage = NULL;

	      //Load the image
	      loadedImage = SDL_LoadBMP( filename.c_str() );

	      //If nothing went wrong in loading the image
	      if( loadedImage != NULL )
	      {
	          //Create an optimized image
	          optimizedImage = SDL_DisplayFormat( loadedImage );

	          //Free the old image
	          SDL_FreeSurface( loadedImage );
	      }

	      //Return the optimized image
	      return optimizedImage;
	  }







void Meny::handle_input(SDL_Event& event){

	if( event.type == SDL_KEYDOWN )
	            {

	                switch( event.key.keysym.sym )
	                {
	                    /*case SDLK_UP:  cout << "up" << endl; break;
	                    case SDLK_DOWN: cout << "down" << endl; break;
	                    case SDLK_LEFT: cout << "left" << endl; break;
						case SDLK_RIGHT: cout << "right" << endl ; break;
						case SDLK_q: {cout << "quit" << endl; nextState_ = EXITGAME;} ; break;
						case SDLK_p: nextState_ = PLAYER1STATE; break;
						default: break;*/

						case SDLK_UP:  graphicsengine_ptr_->clearScreenBuffer(0xff << 16 | 0xff << 8 | 0xff << 0); break;
						case SDLK_DOWN: graphicsengine_ptr_->clearScreenBuffer(0x00 << 16 | 0x00 << 8 | 0x00 << 0) ; break;
						case SDLK_LEFT: graphicsengine_ptr_->clearScreenBuffer(0x0e << 16 | 0x08 << 8 | 0xff << 0); break;
						case SDLK_RIGHT: graphicsengine_ptr_->clearScreenBuffer(0xff << 16 | 0xff << 8 | 0xaa << 0); break;
						case SDLK_p: nextState_ = PLAYER1STATE; break;
						case SDLK_q: {cout << "quit" << endl; nextState_ = EXITGAME;} ; break;
						default: break;
					}
	            }
	else if( event.type == SDL_QUIT )
	                nextState_ = EXITGAME;
}

PANZER_STATES Meny::next_state()
{
	return nextState_;
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

void ExitGame::logic(){}

PANZER_STATES ExitGame::next_state()
{
	return EXITGAME;
}
//---------------------------------------------------------------//


