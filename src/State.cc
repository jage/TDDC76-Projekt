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
//Meny-----------------------------------------------------------//

//Meny::Meny(){}

Meny::Meny(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine, gameworld, audio),
	   nextState_(PLAYER1STATE),
	   quitMeny_(false){
}

Meny::~Meny(){
}


void Meny::render(){
		graphicsengine_ptr_->clearScreenBuffer(1);
		graphicsengine_ptr_->drawBackgroundToScreenBuffer(1);
		graphicsengine_ptr_->drawTextToScreenBuffer("Play",26,100,255,255,255,PAPER_CUT72);
		graphicsengine_ptr_->drawTextToScreenBuffer("Network",26,170,255,255,255,PAPER_CUT72);
		graphicsengine_ptr_->drawTextToScreenBuffer("Options",26,240,255,255,255,PAPER_CUT72);
		graphicsengine_ptr_->drawTextToScreenBuffer("Quit",26,310,255,255,255,PAPER_CUT72);
		graphicsengine_ptr_->drawTextToScreenBuffer("[",0,((nextState_ * 70) + 100), 100,0,255,PAPER_CUT72);
		graphicsengine_ptr_->drawTextToScreenBuffer("]",300,((nextState_ * 70) + 100), 100,0,255,PAPER_CUT72);

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
	 : State(graphicsengine,gameworld, audio), nextState_(PLAYER1STATE), player_ptr_(player) {
		fire_power_ = 0;
	}

Player1State::~Player1State() {}

void Player1State::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawBackgroundToScreenBuffer(0);
	graphicsengine_ptr_->drawTextToScreenBuffer(player_ptr_->get_name(),0,0,125,124,0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_MovableElemets()));
	graphicsengine_ptr_->drawPowerBarToScreenBuffer(5,35,200,20,player_ptr_->get_health());
	graphicsengine_ptr_->drawWindBarToScreenBuffer(320,0,100,5,gameworld_ptr_->get_wind());
	if (fire_power_ != 0)
		graphicsengine_ptr_->drawPowerBarToScreenBuffer(5, 58, 200, 20, fire_power_);
	graphicsengine_ptr_->showScreenBufferOnScreen();
	
}
void Player1State::logic()
{
	nextState_ = PLAYER1STATE;
}

/*
 * Handle SDL_Event, if player is connected to a remote network player, send messages
 */
void Player1State::handle_input(SDL_Event& event){

	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 100)
					fire_power_++;
				player_ptr_->network();
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "enter_pressed");
			break;
			case SDLK_UP:
				gameworld_ptr_->get_leftCannon()->adjust_angle(1);
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "up");
			break;
			case SDLK_DOWN:
				gameworld_ptr_->get_leftCannon()->adjust_angle(-1); 
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "down");
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
					gameworld_ptr_->get_MovableElemets()->push_back(gameworld_ptr_->get_leftCannon()->fire());
					audio_ptr_->playSound(0);
					if (player_ptr_->network())
						Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "enter_released");
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
	 : State(graphicsengine,gameworld, audio), nextState_(PLAYER2STATE), player_ptr_(player) {
		fire_power_ = 0;
	}

Player2State::~Player2State() {}

void Player2State::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawBackgroundToScreenBuffer(0);
	graphicsengine_ptr_->drawTextToScreenBuffer(player_ptr_->get_name(),400,0,125,254,0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_MovableElemets()));
	graphicsengine_ptr_->drawPowerBarToScreenBuffer(405,35,200,20,player_ptr_->get_health());
	graphicsengine_ptr_->drawWindBarToScreenBuffer(320,0,100,5,gameworld_ptr_->get_wind());
	if (fire_power_ != 0)
		graphicsengine_ptr_->drawPowerBarToScreenBuffer(405, 58, 200, 20, fire_power_);
	graphicsengine_ptr_->showScreenBufferOnScreen();
}

void Player2State::logic(){nextState_ = PLAYER2STATE;}

/*
 * Handle SDL_Event, if player is connected to a remote network player, send messages
 */
void Player2State::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_RETURN:
				if (fire_power_ != 100)
					fire_power_++;
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "enter_pressed");
			break;
			case SDLK_UP:
				gameworld_ptr_->get_rightCannon()->adjust_angle(1);
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "up");
			break;
			case SDLK_DOWN:
				gameworld_ptr_->get_rightCannon()->adjust_angle(-1); 
				if (player_ptr_->network())
					Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "down");
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
					gameworld_ptr_->get_rightCannon()->set_power(fire_power_);
					gameworld_ptr_->get_MovableElemets()->push_back(gameworld_ptr_->get_rightCannon()->fire());
					audio_ptr_->playSound(0);
					if (player_ptr_->network())
						Network::send(player_ptr_->get_hostname(), player_ptr_->get_port(), "enter_released");
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
	graphicsengine_ptr_->drawBackgroundToScreenBuffer(0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_elements()));
	graphicsengine_ptr_->drawTextToScreenBuffer("FIRE",0,0,255,0,0);
	graphicsengine_ptr_->drawToScreenBuffer(*(gameworld_ptr_->get_MovableElemets()));
	graphicsengine_ptr_->drawWindBarToScreenBuffer(320,0,100,5,gameworld_ptr_->get_wind());
	graphicsengine_ptr_->showScreenBufferOnScreen();
}

void Fire::logic(){
	gameworld_ptr_->update_world();
	gameworld_ptr_->get_leftCannon()->disarm();
	gameworld_ptr_->get_rightCannon()->disarm();
}

PANZER_STATES Fire::next_state()
{
	if(gameworld_ptr_->check_collision())
	{
		audio_ptr_->playSound(1);
		if (gameworld_ptr_->getPlayer1Health() < 0) {
			return POSTMATCH;
		}
		else if (gameworld_ptr_->getPlayer2Health() < 0) {
			return POSTMATCH;
		}
			return FIREEND;
	}
	else
	{
		return FIRE;
	}
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
	 : State(graphicsengine,gameworld, audio), nextState_(NETWORKSTATE), input_(""), port_("12345"), switchinput_(true) {}

void NetworkState::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawTextToScreenBuffer("Enter toggles IP/Port input",0,0,255,255,255,LAZY26);
	graphicsengine_ptr_->drawTextToScreenBuffer("z exits",0,40,255,255,255,LAZY26);
	graphicsengine_ptr_->drawTextToScreenBuffer("IP: " ,0,80,255,255,255,LAZY26);
	graphicsengine_ptr_->drawTextToScreenBuffer(input_,50,80,0,255,255,LAZY26);
	graphicsengine_ptr_->drawTextToScreenBuffer("Port: " ,0,120,255,255,255,LAZY26);
	graphicsengine_ptr_->drawTextToScreenBuffer( port_ ,80,120,255,0,255,LAZY26);
}

void NetworkState::logic()
{
	nextState_ = NETWORKSTATE;
}

void NetworkState::handle_input(SDL_Event& event){

	SDL_EnableUNICODE(1);
	if (event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym > 27)
		{
			if(switchinput_)
				input_.push_back(char(event.key.keysym.unicode));
			else
				port_.push_back(char(event.key.keysym.unicode));
		}
		if(event.key.keysym.sym == SDLK_RETURN)
			{
				switchinput_ = !switchinput_;
				if(switchinput_)
					input_.clear();
				else
					port_.clear();
			}
		if(event.key.keysym.sym == SDLK_z)
				nextState_ = MENY;

	}
}

PANZER_STATES NetworkState::next_state(){
	return nextState_;
}
//OptionsState-------------------------------------------------//
OptionState::OptionState(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio)
	 : State(graphicsengine, gameworld, audio), nextState_(SETNAMESTATE), quitOptions_(false){}

void OptionState::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawBackgroundToScreenBuffer(0);
	graphicsengine_ptr_->drawBackgroundToScreenBuffer();
	graphicsengine_ptr_->drawTextToScreenBuffer("Set Player Name",26,100,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("Select Level",26,170,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("Meny",26,240,255,255,255,PAPER_CUT72);
 		if (nextState_ == 8){
 			graphicsengine_ptr_->drawTextToScreenBuffer("[",0,100, 100,0,255,PAPER_CUT72);
			graphicsengine_ptr_->drawTextToScreenBuffer("]",600,100, 100,0,255,PAPER_CUT72);
 		}
 		if (nextState_ == 9){
 			graphicsengine_ptr_->drawTextToScreenBuffer("[",0,170, 100,0,255,PAPER_CUT72);
			graphicsengine_ptr_->drawTextToScreenBuffer("]",600,170, 100,0,255,PAPER_CUT72);
 		}
 		if (nextState_ == 5){
 			graphicsengine_ptr_->drawTextToScreenBuffer("[",0,240, 100,0,255,PAPER_CUT72);
			graphicsengine_ptr_->drawTextToScreenBuffer("]",600,240, 100,0,255,PAPER_CUT72);
 	}
 	
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
	 : State(graphicsengine, gameworld, audio), nextState_(SETNAMESTATE), player1_ptr_(player1), player2_ptr_(player2), playertemp_(0){}

void SetNameState::render(){
	
	/*graphicsengine_ptr_->drawBackgroundToScreenBuffer();*/
	graphicsengine_ptr_->drawTextToScreenBuffer("Press the number of your character:",0,0,255,255,255);
	/*graphicsengine_ptr_->drawTextToScreenBuffer("1- D.A",26,100,255,255,255,PAPER_CUT72);*/
	graphicsengine_ptr_->drawTextToScreenBuffer("1-D.A",0,40,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("2-J.R",0,110,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("3-J.W",0,180,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("4-J.R",0,250,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("5-V.D",0,320,255,255,255,PAPER_CUT72);
	graphicsengine_ptr_->drawTextToScreenBuffer("6-J.E",0,390,255,255,255,PAPER_CUT72);
	

}

void SetNameState::logic(){nextState_ = SETNAMESTATE;}

void SetNameState::handle_input(SDL_Event& event){
	if(event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
				{
					case SDLK_1:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Daniel - the Bloodseeker",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Daniel - the Bloodseeker");
						}; break;
						
						case SDLK_2:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Johannes - the Earthshaker",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Johannes - Earthshaker");
						}; break;
						case SDLK_3:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Johan - the Doombringer",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Johan - the Doombringer");
						}; break;
						case SDLK_4:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Jonas - the Slayer",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Jonas - the Slayer");
						}; break;
						case SDLK_5:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Viktor - the Soul Keeper",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Viktor - the Soul Keeper");
						}; break;
						case SDLK_6:
						{
							graphicsengine_ptr_->clearScreenBuffer(0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Johan - the Lifestealer",200,200,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Choose your destiny?",220,300,255,0,0);
							graphicsengine_ptr_->drawTextToScreenBuffer("Press enter",220,350,255,0,0);
							player1_ptr_->set_name("Johan - the Lifestealer");
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
	gameworld_ptr_->set_wind(.1*((rand()%200) - 100));
	gameworld_ptr_->setPlayer1Health(100);
	gameworld_ptr_->setPlayer2Health(100);
	cout << "Level generated, we wait so we see the splash screen..." << endl;

}

PANZER_STATES InitState::next_state(){
	return MENY;
}
//InitState-------------------------------------------------//

//PostMatch-------------------------------------------------//
PostMatch::PostMatch(GraphicsEngine* graphicsengine, GameWorld* gameworld, Audio* audio, Player* player1_ptr_, Player* player2_ptr_):
	State(graphicsengine,gameworld,audio), player1_ptr_(player1_ptr_), player2_ptr_(player2_ptr_) {}

void PostMatch::render(){
	graphicsengine_ptr_->clearScreenBuffer(0);
	graphicsengine_ptr_->drawBackgroundToScreenBuffer(2);
	if(player1_ptr_->get_health() < 0)
		graphicsengine_ptr_->drawTextToScreenBuffer(player2_ptr_->get_name() +"  is the winner",0,0,255,255,255,LAZY32);
	else
		graphicsengine_ptr_->drawTextToScreenBuffer(player1_ptr_->get_name() +"  is the winner",0,0,255,255,255, LAZY32);

}
void PostMatch::logic(){ SDL_Delay(2000);}

PANZER_STATES PostMatch::next_state(){
	return INITSTATE;
}


