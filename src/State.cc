/*
 * State.cpp
 *
 *  Created on: Nov 23, 2009
 *      Author: rosjo
 */

#include "State.h"
#include <iostream>
#include <string>

using namespace std;

//State---------------------------------------------------------//
State::State(GraphicsEngine* graphicengine, GameWorld* gameworld)
	: graphicsengine_ptr_(graphicengine), gameworld_ptr_(gameworld){}

State::~State() {}
//--------------------------------------------------------------//



//Temporär funktion Graphics engine bör ta hand om allt
SDL_Surface* load_image( std::string filename )
	  {
	      //Temporary storage for the image that's loaded
	      SDL_Surface* loadedImage = NULL;

	      //The optimized image that will be used
	      SDL_Surface* optimizedImage = NULL;

	      //Load the image
	      loadedImage = IMG_Load( filename.c_str() );

	      //If nothing went wrong in loading the image
	      if( loadedImage != NULL )
	      {
	          //Create an optimized image
	          optimizedImage = SDL_DisplayFormat( loadedImage );

	          //Free the old image
	          SDL_FreeSurface( loadedImage );
	      }
	      else
	    	  cerr << "Image not found!" << endl;

	      //Return the optimized image
	      return optimizedImage;
	  }


//Meny-----------------------------------------------------------//

//Meny::Meny(){}

Meny::Meny(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld),
	   nextState_(MENY),
	   rendermeny_(true),
	   quitMeny_(false){
	play_ = load_image("play.png");
	network_ = load_image("network.png");
	options_ = load_image("options.png");
	quit_ = load_image("quit.png");
	marker_ = load_image("grundmarker.png");
}

Meny::~Meny(){
	SDL_FreeSurface(play_);
	SDL_FreeSurface(network_);
	SDL_FreeSurface(options_);
	SDL_FreeSurface(quit_);
	SDL_FreeSurface(marker_);
}


void Meny::renderMenyGfx()
{
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(play_,50,50);
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(network_,50,100);
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(options_,50,150);
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(quit_,50,200);

	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(marker_,0,(50 + 50 * nextState_));

}


void Meny::render(){
	if(rendermeny_)
	{
		cout << "Press an arrow key\n"
			 << "q - finished the 'game' \n"
			 << "p - changes to the player state\n"
			 << "Meny eats memory, please be gentle..." << flush;
		graphicsengine_ptr_->clearScreenBuffer(0);
		renderMenyGfx();
		rendermeny_ = false;
	}
}


void Meny::handle_input(SDL_Event& event){


	if( event.type == SDL_KEYDOWN )
	{
		rendermeny_ = true;
		switch( event.key.keysym.sym )
			{
				case SDLK_UP: nextState_ = EXITGAME; break;
				case SDLK_DOWN: nextState_ = PLAYER1STATE; break;

				case SDLK_p: nextState_ = PLAYER1STATE; break;
				case SDLK_q: {cout << "quit" << endl; nextState_ = EXITGAME; quitMeny_ = true;} ; break;
				case SDLK_RETURN: quitMeny_= true; break;
				default: break;
			}
	}
	else if( event.type == SDL_QUIT )
	{
		nextState_ = EXITGAME;
		quitMeny_ = true;
	}
}

PANZER_STATES Meny::next_state()
{
	if(quitMeny_)
		return nextState_;
	else
		return MENY;
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


