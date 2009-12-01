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
#include "State.h"
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
	virtual void handle_input(std::istream&) = 0;

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
	void handle_input(std::istream&);

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

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
	void handle_input(std::istream&){};

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
	void handle_input(std::istream&){};

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
	 * Saknar egentlig funktion
	 */
	void logic(){};

	/*
	 * handle_event()
	 * Svarar på användarens knapptryckningar
	 */
	void handle_input(std::istream&){};

	/*
	 * next_state()
	 * Nästa tillstånd för Meny
	 */
	PANZER_STATES next_state();

private:

};

#endif /* STATE_H_ */
