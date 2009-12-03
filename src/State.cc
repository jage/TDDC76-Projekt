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
	   menyItem1(PLAYMENY),
	   menyItem2(MENYORIGNAL){}

Meny::~Meny(){}


void Meny::renderMenyGfx(MENYIMAGES image, int x, int y)
{
	switch(image)
	{
	case MENYHIGLIGHTED:
			graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("menytest.png"),x,y); break;
	case MENYORIGNAL:
			graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("menytest2.png"),x,y); break;
	case PLAYMENY:
		graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("playmeny.png"),x,y); break;
	case PLAYMENYSELECTED:
		graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("playmenyselected.png"),x,y); break;

	}


}


void Meny::render(){
	if(rendermeny_)
	{
		cout << "Press an arrow key\n"
			 << "q - finished the 'game' \n"
			 << "p - changes to the player state\n"
			 << "Meny eats memory, please be gentle..." << flush;
		rendermeny_ = false;
	}
	renderMenyGfx(menyItem1,40,100);
	renderMenyGfx(menyItem2,40,200);
}


void Meny::handle_input(SDL_Event& event){

	if( event.type == SDL_KEYDOWN )
	            {

	                switch( event.key.keysym.sym )
	                {
						case SDLK_UP: {menyItem1 = MENYHIGLIGHTED; menyItem2 = MENYORIGNAL;}; break;
						case SDLK_DOWN: { menyItem2 = MENYHIGLIGHTED; menyItem1 = MENYORIGNAL;}; break;
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


