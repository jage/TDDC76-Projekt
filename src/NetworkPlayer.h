#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "Network.h"
#include "Player.h"
#include "SDLInclude.h"

#include <string>

class NetworkPlayer : public Player {
public:
	NetworkPlayer(const std::string& = " ", const int = 0, const int = 0) ;
	virtual ~NetworkPlayer();
	
	/*
	 *	handle_event
	 *  Hanterar en h�ndelse och retunerar h�ndelsen om det �r en keyboard h�ndelse, annars returneras inget!?!? 
	 */
	 
	SDL_Event& handle_event(SDL_Event& event);
	
};

#endif /*LOCALPLAYER_H_*/
