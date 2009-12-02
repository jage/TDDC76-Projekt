/*
 * GameEngine.h
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include "GameWorld.h"
#include "SDL/SDL.h"
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
	 * TODO Loopen k√∂rs tills loppen hamnar i tillst√•ndet
	 * ExitGame
	 */
	void run();

private:

	GameWorld gameworld_;
	GraphicsEngine graphicsengine_;
	Sound sound_;
	Player player1;
	Player player2;


	//Tillst√•nd
	PANZER_STATES currentState_;
	State* prevState_;
    vector<State*> stateVector_;

    /*
     * init()
     * Initerar SDL, returnerar true ifall vi lyckades
     */
    bool init_SDL();

    /*
     * cleanup()
     * St‰dar i minnet n‰r spelet avslutas
     */
    void cleanup();

	// Kopiering och tilldelning tillÂts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);



};



#endif /* GAMEENGINE_H_ */
