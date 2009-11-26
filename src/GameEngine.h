/*
 * GameEngine.h
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include "GameWorld.h"
#include "GraphicsEngine.h"
#include "State.h"

//Dummyclasses
struct Sound{};
struct Player{};

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	/*
	 * run() - funktionen startar speloopen.
	 * TODO Loopen körs tills loppen hamnar i tillståndet
	 * ExitGame
	 */
	void run();

private:

	GameWorld gameworld_;
	GraphicsEngine graphicengine_;
	Sound sound_;
	Player player1;
	Player player2;


	//Tillstånd
	State* current_state_;
    Meny* meny_ptr_;


	// Kopiering och tilldelning tillåts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);

};



#endif /* GAMEENGINE_H_ */
