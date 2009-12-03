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
#include "SDL/SDL.h"
#include <iostream>



class State {
public:

	State(GraphicsEngine*, GameWorld*);

	virtual ~State();


	/*
	 * render()
	 * Rita tillst�ndsspecifik grafik p� sk�rmen
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
	 * TODO SDL_Event istället för att läsa på en inström
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


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * Saknar egentlig funktion
	 */
	void logic(){};

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&);

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

private:
 PANZER_STATES nextState_;
 bool quitMeny_;

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
	//Meny();
	Player1State(GraphicsEngine*, GameWorld*);
	~Player1State();


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * Saknar egentlig funktion
	 */
	void logic(){};

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

private:

};

class Fire : public State
{
public:

	Fire(GraphicsEngine*, GameWorld*);
	~Fire();


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * Saknar egentlig funktion
	 */
	void logic(){};

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

private:

};

class ExitGame : public State
{

public:
	ExitGame(GraphicsEngine*, GameWorld*);
	~ExitGame();


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * St�dar i minnet efter SDL
	 */
	void logic();

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

private:

};

class NetworkState : public State
{

public:
	NetworkState(GraphicsEngine*, GameWorld*);
	~NetworkState(){};


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * St�dar i minnet efter SDL
	 */
	void logic();

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state(){return MENY;};

private:

};

class OptionState : public State
{

public:
	OptionState(GraphicsEngine*, GameWorld*);
	~OptionState(){};


	/*
	 * Skriver ut menyalternativ till användaren på standard utsrömmen
	 */
	void render();

	/*
	 * logic()
	 * St�dar i minnet efter SDL
	 */
	void logic();

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(SDL_Event&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state(){return MENY;};

private:

};

#endif /* STATE_H_ */
