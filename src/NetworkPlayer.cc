#include "NetworkPlayer.h"
#include "SDLInclude.h"

using namespace std;

NetworkPlayer::NetworkPlayer(const string& name, const int health, const int points)
 : Player(name, health, points) {}

	SDL_Event& NetworkPlayer::handle_event(SDL_Event& event)
	{
		if(event.type == SDL_KEYDOWN)
			{
				return event;
			}	
	}


NetworkPlayer::~NetworkPlayer()
{
}
