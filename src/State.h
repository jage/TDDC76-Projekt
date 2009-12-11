#ifndef STATE_H_
#define STATE_H_

#include "GraphicsEngine.h"
#include "GameWorld.h"
#include "SDLInclude.h"
#include "Network.h"
#include "Audio.h"
#include "Player.h"
#include <iostream>


class State {
public:

	State(GraphicsEngine*, GameWorld*, Audio*);

	virtual ~State();


	/*
	 * render()
	 * Draws graphics on the screen buffert
	 */
	virtual void render() = 0;

	/*
	 * logic()
	 * Run logic for a state
	 */
	virtual void logic() = 0;

	/*
	 * handle_input()
	 * How the state will respond on the users input. Takes a SDL_Event as input
	 */
	virtual void handle_input(SDL_Event&) = 0;

	/*
	 * next_state()
	 * Returns the nextstate after the current. Return type is a PANZER_STATE
	 */
	virtual PANZER_STATES next_state() = 0;

protected:
	GraphicsEngine* graphicsengine_ptr_;
	GameWorld*	   gameworld_ptr_;
	Audio*			audio_ptr_;

};

class Meny : public State
{
public:
	Meny(GraphicsEngine*, GameWorld*, Audio*);
	~Meny();

	void render();

	void logic(){};

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
 PANZER_STATES nextState_;
 bool quitMeny_;

	/*
 	 * changeState()
 	 * Sets active state in the meny. Takes a bool as input true means up one step in meny
 	 */
  void changeState(bool);

private:

};

class Player1State : public State
{

public:
	Player1State(GraphicsEngine*, GameWorld*, Audio*, Player*);
	~Player1State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;
	Player* player_ptr_;
	int fire_power_;
};

class Player2State : public State
{

public:
	//Meny();
	Player2State(GraphicsEngine*, GameWorld*, Audio*, Player*);
	~Player2State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();


private:
	PANZER_STATES nextState_;
	Player* player_ptr_;
	int fire_power_;
};

class Fire : public State
{
public:

	Fire(GraphicsEngine*, GameWorld*, Audio*);
	~Fire();

	void render();

	void logic();

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state();

private:

};

class ExitGame : public State
{

public:
	ExitGame(GraphicsEngine*, GameWorld*, Audio*);
	~ExitGame();

	void render();

	void logic();

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state();

private:

};

class NetworkState : public State
{

public:
	NetworkState(GraphicsEngine*, GameWorld*, Audio*);
	~NetworkState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;
	string	input_;
	string  port_;
	bool switchinput_;

};

class OptionState : public State
{

public:
	OptionState(GraphicsEngine*, GameWorld*, Audio*);
	~OptionState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;
	bool quitOptions_;

	/*
	 * changeState()
	 * Sets active state in the meny. Takes a bool as input true means up one step in meny
	 */
	void changeState(bool);
};


class InitState : public State
{
public:
	InitState(GraphicsEngine*, GameWorld*, Audio*);
	~InitState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state();

};

class SetNameState : public State
{
public:
	SetNameState(GraphicsEngine*, GameWorld*, Audio*, Player*,Player*);
	~SetNameState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;
	Player* player1_ptr_;
	Player* player2_ptr_;
	Player* playertemp_;



};

class SelectLevelState : public State
{
public:
	SelectLevelState(GraphicsEngine*, GameWorld*, Audio*);
	~SelectLevelState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();
private:
	PANZER_STATES nextState_;
};

class PostMatch : public State
{
public:
	PostMatch(GraphicsEngine*, GameWorld*, Audio*, Player*, Player*);
	~PostMatch(){};

	void render();

	void logic();

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state();
private:
	PANZER_STATES nextState_;
	Player* player1_ptr_;
	Player* player2_ptr_;
};


#endif /* STATE_H_ */
