#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "Keyboardinput.h"
#include "Player.h"

#include <string>

class LocalPlayer : public Player {
public:
	LocalPlayer(const std::string& = " ", const int = 0, const int = 0) ;
	virtual ~LocalPlayer();
	
	
	
};

#endif /*LOCALPLAYER_H_*/
