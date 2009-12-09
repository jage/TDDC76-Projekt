#include "LocalPlayer.h"
#include "SDLInclude.h"

using namespace std;

LocalPlayer::LocalPlayer(const string& name, const int health, const int points)
 : Player(name, health, points) {}

	SDL_Event& LocalPlayer::handle_event(SDL_Event& event)
	{
		if(event.type == SDL_KEYDOWN)
			{
				return event;
			}	
	}


LocalPlayer::~LocalPlayer()
{
}
