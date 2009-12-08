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
#include "GraphicsEngine.h"
#include "SDLInclude.h"
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
	 * Loopen körs tills loppen hamnar i tillståndet
	 * ExitGame
	 */
	void run();

private:

	GameWorld gameworld_;
	GraphicsEngine graphicsengine_;
	Sound sound_;
	Player player1;
	Player player2;
	unsigned int ticks_;

	//Tillst�nd
	PANZER_STATES currentState_;
	PANZER_STATES playerTurn_;
    vector<State*> stateVector_;

    /*
     * init()
     * Initerar SDL, returnerar true ifall vi lyckades
     */
    bool init_SDL();

    /*
     * cleanup()
     * St�dar i minnet n�r spelet avslutas
     */
    void cleanup();

    /*
     * regulate_fps()
     * Reglerar frames/second, s� att vi inte tar all processorkraft
     * Standard �r 100 fps
     */
    void regulate_fps();

	// Kopiering och tilldelning till�ts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);



};



#endif /* GAMEENGINE_H_ */
