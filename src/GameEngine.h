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
#include "Audio.h"

//Dummyclasses
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
	Audio soundplayer_;
	Player* player1_ptr_;
	Player* player2_ptr_;
	unsigned int ticks_;

	//Tillst�nd
	PANZER_STATES currentState_;
	PANZER_STATES playerTurn_;
	std::vector<State*> stateVector_;

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

    /*
     * return_to_meny()
     * Avbryter spelet, och vi återvändet till meny.
     */
    void return_to_meny();

	// Kopiering och tilldelning till�ts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);



};



#endif /* GAMEENGINE_H_ */
