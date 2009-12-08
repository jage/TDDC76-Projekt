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



class State {
public:

	State(GraphicsEngine*, GameWorld*);

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

};

class Meny : public State
{
public:
	//Meny();
	Meny(GraphicsEngine*, GameWorld*);
	~Meny();

	void render();

	void logic(){};

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
 PANZER_STATES nextState_;
 bool quitMeny_;
 bool oldgfx_;

 void changeState(bool);

 //Grafiken �r tempor�r b�r integreras med GraphicsEngine

 SDL_Surface* play_;
 SDL_Surface* options_;
 SDL_Surface* network_;
 SDL_Surface* quit_;
 SDL_Surface* marker_;

 void renderMenyGfx();




private:

};

class Player1State : public State
{

public:
	Player1State(GraphicsEngine*, GameWorld*);
	~Player1State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();

private:
	PANZER_STATES nextState_;

};

class Player2State : public State
{

public:
	//Meny();
	Player2State(GraphicsEngine*, GameWorld*);
	~Player2State();

	void render();

	void logic();

	void handle_input(SDL_Event&);

	PANZER_STATES next_state();


private:
	PANZER_STATES nextState_;
};

class Fire : public State
{
public:

	Fire(GraphicsEngine*, GameWorld*);
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
	ExitGame(GraphicsEngine*, GameWorld*);
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
	NetworkState(GraphicsEngine*, GameWorld*);
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
	OptionState(GraphicsEngine*, GameWorld*);
	~OptionState(){};

	void render();

	void logic();

	void handle_input(SDL_Event&){};

	PANZER_STATES next_state(){return MENY;};

private:

};

#endif /* STATE_H_ */
