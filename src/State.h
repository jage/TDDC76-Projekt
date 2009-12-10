/*
 * State.h
 *
 *  Created on: Nov 23, 2009
 *      Author: rosjo
 */

#ifndef STATE_H_
#define STATE_H_

#include "GraphicsEngine.h"
#include "GameWorld.h"
#include "SDLInclude.h"
#include <iostream>
#include "Audio.h"



class State {
public:

	State(GraphicsEngine*, GameWorld*, Audio*);

	virtual ~State();


	/*
	 * render()
	 * Rita tillst�ndsspecifik grafik p� sk�rmen
	 * OBS Uppdaterar inte spelskärmen, GameEngine gör detta
	 */
	virtual void render() = 0;

	/*
	 * logic()
	 * Definerar tillståndes logik
	 */
	virtual void logic() = 0;

	/*
	 * handle_input()
	 * Bestämmer hur tillståndet svara på användarens interaktion
	 */
	virtual void handle_input(SDL_Event&) = 0;

	/*
	 * next_state()
	 * Returnerar nästa tillstånd som ska köras efter det nurvarande
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
	//Meny();
	Meny(GraphicsEngine*, GameWorld*, Audio*);
	~Meny();

	void render();

	void logic(){};

	void handle_input(SDL_Event&);

	void handle_keystates(Uint8*);

	PANZER_STATES next_state();

private:
 PANZER_STATES nextState_;
 bool quitMeny_;

 void changeState(bool);

 void renderMenyGfx();




private:

};

class Player1State : public State
{

public:
	Player1State(GraphicsEngine*, GameWorld*, Audio*);
	~Player1State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	void handle_keystates(Uint8*);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;

};

class Player2State : public State
{

public:
	//Meny();
	Player2State(GraphicsEngine*, GameWorld*, Audio*);
	~Player2State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	void handle_keystates(Uint8*);

	PANZER_STATES next_state();


private:
	PANZER_STATES nextState_;
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

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state(){return MENY;};

private:

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

#endif /* STATE_H_ */
