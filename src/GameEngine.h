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
	 * TODO Loopen kÃ¶rs tills loppen hamnar i tillstÃ¥ndet
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

	//Tillstånd
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
     * Städar i minnet när spelet avslutas
     */
    void cleanup();

    /*
     * regulate_fps()
     * Reglerar frames/second, så att vi inte tar all processorkraft
     * Standard är 100 fps
     */
    void regulate_fps();

	// Kopiering och tilldelning tillåts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);



};



#endif /* GAMEENGINE_H_ */
