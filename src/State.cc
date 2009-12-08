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



//Tempor�r funktion Graphics engine b�r ta hand om allt
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
}

Meny::~Meny(){
}


void Meny::renderMenyGfx()
{
		graphicsengine_ptr_->drawFixedWidthButton("Play",20,100,200,(nextState_ == 0), LAZY26,255,255,255);
		graphicsengine_ptr_->drawFixedWidthButton("Network",20,150,200,(nextState_ == 1),LAZY26,255,255,255);
		graphicsengine_ptr_->drawFixedWidthButton("Options",20,200,200,(nextState_ == 2),LAZY26,255,255,255);
		graphicsengine_ptr_->drawFixedWidthButton("Quit",20,250,200,(nextState_ == 3),LAZY26,255,255,255);
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
				nextState_ = EXITGAME;
			else
				nextState_ = NETWORKSTATE;
		} break;
		case NETWORKSTATE:
		{
			if(up)
				nextState_ = PLAYER1STATE;
			else
				nextState_ = OPTIONSTATE;
		} break;

		case OPTIONSTATE:
		{
			if(up)
				nextState_ = NETWORKSTATE;
			else
				nextState_ = EXITGAME;
		}break;

		case EXITGAME:
		{
			if(up)
				nextState_ = OPTIONSTATE;
			else
				nextState_ = PLAYER1STATE;
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

}

PANZER_STATES Meny::next_state()
{
	if(quitMeny_)
	{   quitMeny_ = false;
		graphicsengine_ptr_->clearScreenBuffer(0);//Töm skärmen för ny grafik
		return nextState_;
	}
	else
		return MENY;
}
//---------------------------------------------------------------//

//Player1State-----------------------------------------------------------//



Player1State::Player1State(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld), nextState_(PLAYER1STATE) {}

Player1State::~Player1State(){}

void Player1State::render(){
	graphicsengine_ptr_->drawTextToScreenBuffer("Player 1 turn",0,0,125,124,0);
}
void Player1State::logic(){nextState_ = PLAYER1STATE;}

void Player1State::handle_input(SDL_Event& event){

		if(event.type == SDL_KEYDOWN)
			{
				switch( event.key.keysym.sym )
					{
						case SDLK_UP:{graphicsengine_ptr_->clearScreenBuffer(0); graphicsengine_ptr_->drawTextToScreenBuffer("Player 1 pushed up",100,100,254,254,254);} ; break;
						case SDLK_DOWN:{graphicsengine_ptr_->clearScreenBuffer(0); graphicsengine_ptr_->drawTextToScreenBuffer("Player 1 pushed down",100,100,254,254,254);}; break;
						case SDLK_RETURN: nextState_ = FIRE; break;
						default: break;
					}
			}

}


PANZER_STATES Player1State::next_state()
{
			return nextState_;
}
//---------------------------------------------------------------//

//Player2State-----------------------------------------------------------//

Player2State::Player2State(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld), nextState_(PLAYER2STATE) {}

Player2State::~Player2State(){}

void Player2State::render(){
graphicsengine_ptr_->drawTextToScreenBuffer("Player 2 turn",0,0,125,254,0);
}

void Player2State::logic(){nextState_ = PLAYER2STATE;}

void Player2State::handle_input(SDL_Event& event){

if(event.type == SDL_KEYDOWN)
	{
		switch( event.key.keysym.sym )
			{
				case SDLK_UP: {graphicsengine_ptr_->clearScreenBuffer(0); graphicsengine_ptr_->drawTextToScreenBuffer("Player 2 pushed up",100,100,254,254,254);} ; break;
				case SDLK_DOWN: {graphicsengine_ptr_->clearScreenBuffer(0); graphicsengine_ptr_->drawTextToScreenBuffer("Player 2 pushed down",100,100,254,254,254);}; break;
				case SDLK_RETURN: nextState_ = FIRE ; break;
				default: break;
			}
	}
}



PANZER_STATES Player2State::next_state()
{
	return nextState_;
}


//Fire-----------------------------------------------------------//



Fire::Fire(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld) {}

Fire::~Fire(){}

void Fire::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->showScreenBufferOnScreen();
}

void Fire::logic(){ SDL_Delay(2000);}

PANZER_STATES Fire::next_state()
{
	return FIREEND;
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
//OptionsState-------------------------------------------------//
OptionState::OptionState(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld), nextState_(OPTIONSTATE){}

void OptionState::render(){
	graphicsengine_ptr_->drawTextToScreenBuffer("Press space to change generate a level!",0,0,255,255,255);
}

void OptionState::logic(){nextState_ = OPTIONSTATE;}

void OptionState::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
				{
					case SDLK_SPACE:
						{
							gameworld_ptr_->generate_world(640,480,1);
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
						}; break;
					case SDLK_RETURN:
					{
						nextState_ = MENY;
					}
					default: break;
				}
		}
}

PANZER_STATES OptionState::next_state(){
	return nextState_;
}

//OptionsState-----------------------------------------------//

//InitState--------------------------------------------------//
InitState::InitState(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	: State(graphicsengine,gameworld){}

void InitState::render(){
	graphicsengine_ptr_->drawTextToScreenBuffer("Starting the game...",0,0,255,0,0);
}

void InitState::logic(){
	gameworld_ptr_->generate_world(640,480,1);
	cout << "Level generated, we wait so we se the beutiful splash screen..." << endl;
	SDL_Delay(700);
}

PANZER_STATES InitState::next_state(){
	return MENY;
}

