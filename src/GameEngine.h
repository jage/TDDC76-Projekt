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
	 * TODO Loopen körs tills loppen hamnar i tillståndet
	 * ExitGame
	 */
	void run();

private:

	GameWorld gameworld_;
	GraphicsEngine graphicsengine_;
	Sound sound_;
	Player player1;
	Player player2;


	//Tillstånd
	PANZER_STATES currentState_;
	State* prevState_;
    vector<State*> stateVector_;

	// Kopiering och tilldelning tillåts ej (definieras ej)
    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);


		SDL_Surface* screen;
    	SDL_Surface* source_image;

    	SDL_Surface* load_image(std::string);

};



#endif /* GAMEENGINE_H_ */
