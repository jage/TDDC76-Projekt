/*
 * State.cpp
 *
 *  Created on: Nov 23, 2009
 *      Author: rosjo
 */

#include "State.h"
#include <iostream>
#include "SDLInclude.h"
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
	   nextState_(PLAYER1STATE),
	   quitMeny_(false){

	play_ = load_image("play.png");
	network_ = load_image("network.png");
	options_ = load_image("options.png");
	quit_ = load_image("quit.png");
	marker_ = load_image("marker.png");
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
		graphicsengine_ptr_->clearScreenBuffer(0);
		renderMenyGfx();

}

void Meny::changeState(bool up){

	switch(nextState_)
	{
		case PLAYER1STATE:
		{
			if(up)
				{nextState_ = EXITGAME; cout << "play -> exit" << endl;}
			else
				{nextState_ = NETWORKSTATE;; cout << "play -> network" << endl;}
		} break;
		case NETWORKSTATE:
		{
			if(up)
				{nextState_ = PLAYER1STATE; cout << "net -> play" << endl;}
			else
				{nextState_ = OPTIONSTATE; cout << "net -> opt" << endl;}
		} break;

		case OPTIONSTATE:
		{
			if(up)
				{nextState_ = NETWORKSTATE; cout << "opt -> net" << endl;}
			else
				{nextState_ = EXITGAME; cout << "opt -> exit" << endl;}
		}break;

		case EXITGAME:
		{
			if(up)
				{nextState_ = OPTIONSTATE; cout << "exit -> opt" << endl;}
			else
				{nextState_ = PLAYER1STATE; cout << "exit -> play" << endl;}
		}break;

	}
}

void Meny::handle_input(SDL_Event& event){


	if( event.type == SDL_KEYDOWN )
	{
		switch( event.key.keysym.sym )
			{
				case SDLK_UP: changeState(true) ; break;
				case SDLK_DOWN: changeState(false); break;
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
	{   quitMeny_ = false;
		return nextState_;
	}
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


//NetworkState--------------------------------------------------//
NetworkState::NetworkState(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

void NetworkState::render(){
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("underconstruction.png"),0,0);
}

void NetworkState::logic(){
	SDL_Delay(2000);
}

OptionState::OptionState(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

void OptionState::render(){
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("underconstruction.png"),0,0);
}

void OptionState::logic(){
	SDL_Delay(2000);
}
