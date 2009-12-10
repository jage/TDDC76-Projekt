#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <vector>
#include "GameWorld.h"
#include "GraphicsEngine.h"
#include "SDLInclude.h"
#include "State.h"
#include "Audio.h"


class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	/*
	 * run()
	 * Starts the game loop
	 */
	void run();

private:

	GameWorld gameworld_;
	GraphicsEngine graphicsengine_;
	Audio soundplayer_;
	unsigned int ticks_;

	PANZER_STATES currentState_;
	PANZER_STATES playerTurn_;
	std::vector<State*> stateVector_;

    /*
     * init()
     * Initr SDL,  return true if SDL_init completed
     */
    bool init_SDL();

    /*
     * cleanup()
     * Cleans the memory after the gam
     */
    void cleanup();

    /*
     * regulate_fps()
     * Regulate the fps, standard setting is 70 frames/second
     */
    void regulate_fps();

    /*
     * return_to_meny()
     * Abort the game and return to meny
     */
    void return_to_meny();

    GameEngine(const GameEngine&);
    GameEngine& operator=(const GameEngine&);



};



#endif /* GAMEENGINE_H_ */
