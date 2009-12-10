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
#include "Network.h"
#include "Audio.h"

using namespace std;

//State---------------------------------------------------------//
State::State(GraphicsEngine* graphicengine, GameWorld* gameworld, Audio* audio)
: graphicsengine_ptr_(graphicengine), gameworld_ptr_(gameworld), audio_ptr_(audio) {}

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

Meny::Meny(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine, gameworld, audio),
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
		default: break;

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



Player1State::Player1State(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio, Player* player)
	 : State(graphicsengine,gameworld, audio), nextState_(PLAYER1STATE), player_ptr_(player) {}

Player1State::~Player1State() {}

void Player1State::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawTextToScreenBuffer("Player 1 turn",0,0,125,124,0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->showScreenBufferOnScreen();
}
void Player1State::logic()
{
	nextState_ = PLAYER1STATE;
}

void Player1State::handle_input(SDL_Event& event){

	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 100)
					fire_power_++;
				graphicsengine_ptr_->drawPowerBarToScreenBuffer(5, 35, 200, 20, fire_power_);
				graphicsengine_ptr_->showScreenBufferOnScreen();
				Network::send("127.0.0.1", "12346", "enter_pressed");
			break;
			case SDLK_UP:
				gameworld_ptr_->get_leftCannon()->adjust_angle(1);
				Network::send("127.0.0.1", "12346", "up");
			break;
			case SDLK_DOWN:
				gameworld_ptr_->get_leftCannon()->adjust_angle(-1); 
				Network::send("127.0.0.1", "12346", "down");
			break;
			default: break;
		}
	}
	else if(event.type == SDL_KEYUP)
	{		
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 0)
				{
					nextState_ = FIRE;
					gameworld_ptr_->get_leftCannon()->set_power(fire_power_);
					gameworld_ptr_->get_leftCannon()->fire();
					audio_ptr_->playSound(0);
					Network::send("127.0.0.1", "12346", "enter_released");
					fire_power_ = 0;
				}
			break;
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

Player2State::Player2State(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio, Player* player)
	 : State(graphicsengine,gameworld, audio), nextState_(PLAYER2STATE), player_ptr_(player) {}

Player2State::~Player2State(){}

void Player2State::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawTextToScreenBuffer("Player 2 turn",400,0,125,254,0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->showScreenBufferOnScreen();
}

void Player2State::logic(){nextState_ = PLAYER2STATE;}

void Player2State::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 100)
					fire_power_++;
				graphicsengine_ptr_->drawPowerBarToScreenBuffer(405, 35, 200, 20, fire_power_);
				graphicsengine_ptr_->showScreenBufferOnScreen();
			break;
			case SDLK_UP:
				gameworld_ptr_->get_rightCannon()->adjust_angle(1);
			break;
			case SDLK_DOWN:
				gameworld_ptr_->get_rightCannon()->adjust_angle(-1); 
			break;
			default: break;
		}

	}
	else if(event.type == SDL_KEYUP)
	{
		string s;
		stringstream out;
		out << fire_power_;
		s = out.str();
		
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 0)
				{
					nextState_ = FIRE;
					gameworld_ptr_->get_rightCannon()->set_power(fire_power_);
					gameworld_ptr_->get_rightCannon()->fire();
					audio_ptr_->playSound(0);
					fire_power_ = 0;
				}
			break;
			default: break;
		}
	}
}

PANZER_STATES Player2State::next_state()
{
	return nextState_;
}


//Fire-----------------------------------------------------------//



Fire::Fire(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine,gameworld, audio) {}

Fire::~Fire(){}

void Fire::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->drawTextToScreenBuffer("FIRE",0,0,255,0,0);
	graphicsengine_ptr_->showScreenBufferOnScreen();
}

void Fire::logic(){
	gameworld_ptr_->update_world();
	gameworld_ptr_->get_leftCannon()->disarm();
	gameworld_ptr_->get_rightCannon()->disarm();
}

PANZER_STATES Fire::next_state()
{
	return FIREEND;
}
//---------------------------------------------------------------//


//ExitGame----------------------------------------------------------//



ExitGame::ExitGame(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine,gameworld, audio) {}

ExitGame::~ExitGame(){}

void ExitGame::render(){}

void ExitGame::logic(){}

PANZER_STATES ExitGame::next_state()
{
	return EXITGAME;
}
//---------------------------------------------------------------//


//NetworkState--------------------------------------------------//
NetworkState::NetworkState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine,gameworld, audio) {}

void NetworkState::render(){
	graphicsengine_ptr_->drawSDLSurfaceToScreenBuffer(load_image("underconstruction.png"),0,0);
	graphicsengine_ptr_->drawTextToScreenBuffer("You will be a server!",0,0,255,255,255);
}

void NetworkState::logic(){
	SDL_Delay(2000);
}
//OptionsState-------------------------------------------------//
OptionState::OptionState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine, gameworld, audio), nextState_(SETNAMESTATE), quitOptions_(false){}

void OptionState::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawFixedWidthButton("Set player name",20,50,200,(nextState_ == 8),LAZY26,255,255,255);
	graphicsengine_ptr_->drawFixedWidthButton("Select level",20,100,200,(nextState_ == 9),LAZY26,255,255,255);
	graphicsengine_ptr_->drawFixedWidthButton("Meny",20,150,200,(nextState_ == 5),LAZY26,255,255,255);
}

void OptionState::logic(){}

void OptionState::changeState(bool up){

	switch(nextState_)
		{
			case SETNAMESTATE:
			{
				if(up)
					nextState_ = MENY;
				else
					nextState_ = SELECTLEVEL;
			} break;
			case SELECTLEVEL:
			{
				if(up)
					nextState_ = SETNAMESTATE;
				else
					nextState_ = MENY;
			} break;
			case MENY:
			{
				if(up)
					nextState_ = SELECTLEVEL;
				else
					nextState_ = SETNAMESTATE;
			} break;
		}
}


void OptionState::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
				{
					case SDLK_UP: changeState(true); break;
					case SDLK_DOWN: changeState(false); break;
					case SDLK_RETURN:
					{
						quitOptions_ = true;
					}
					default: break;
				}
		}
}

PANZER_STATES OptionState::next_state(){

		if(quitOptions_)
		{   quitOptions_ = false;
			graphicsengine_ptr_->clearScreenBuffer(0);//Töm skärmen för ny grafik
			return nextState_;
		}
		else
			return OPTIONSTATE;
}

//OptionsState-----------------------------------------------//

//SetNameState-------------------------------------------------//
SetNameState::SetNameState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio, Player* player1, Player* player2)
	 : State(graphicsengine, gameworld, audio), nextState_(SETNAMESTATE), player1_ptr_(player1), player2_ptr_(player2){}

void SetNameState::render(){
	graphicsengine_ptr_->drawTextToScreenBuffer("Choose your character:",0,0,255,255,255);
	graphicsengine_ptr_->drawTextToScreenBuffer("",0,0,255,255,255);
	graphicsengine_ptr_->drawTextToScreenBuffer("1.Daniel",0,0,255,255,255);
	graphicsengine_ptr_->drawTextToScreenBuffer("2.Johannes",0,0,255,255,255);
	graphicsengine_ptr_->drawTextToScreenBuffer("3.Johan",0,0,255,255,255);
}

void SetNameState::logic(){nextState_ = SETNAMESTATE;}

void SetNameState::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
				{
					case SDLK_SPACE:
						{
							gameworld_ptr_->generate_world(1);
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
						}; break;
					case SDLK_RETURN:
					{
						nextState_ = OPTIONSTATE;
					}
					default: break;
				}
		}
}

PANZER_STATES SetNameState::next_state(){
	return nextState_;
}

//SetNameState-----------------------------------------------//

//SetNameState-------------------------------------------------//
SelectLevelState::SelectLevelState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine, gameworld, audio), nextState_(SELECTLEVEL){}

void SelectLevelState::render(){
	graphicsengine_ptr_->drawTextToScreenBuffer("Press space to generate a  new level!",0,0,255,255,255);
	graphicsengine_ptr_->drawTextToScreenBuffer("Press enter to save the current level",0,40,255,0,255);
}

void SelectLevelState::logic(){nextState_ = SELECTLEVEL;}

void SelectLevelState::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
				{
					case SDLK_SPACE:
						{
							gameworld_ptr_->generate_world(1);
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
						}; break;
					case SDLK_RETURN:
					{
						nextState_ = OPTIONSTATE;
					}
					default: break;
				}
		}
}

PANZER_STATES SelectLevelState::next_state(){
	return nextState_;
}

//InitState--------------------------------------------------//
InitState::InitState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	: State(graphicsengine,gameworld, audio) {
		SDL_EnableKeyRepeat(100, 10);
	}

void InitState::render(){
	cout << "Initiate the game!" << endl;
}

void InitState::logic(){
	gameworld_ptr_->generate_world(1);
	cout << "Level generated, we wait so we see the splash screen..." << endl;
	//SDL_Delay(700);
}

PANZER_STATES InitState::next_state(){
	return MENY;
}

