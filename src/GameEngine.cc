/*
 * GameEngine.cpp
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#include "iostream"
#include "GameEngine.h"
#include "State.h"
#include "Enums.h"
#include <vector>

using namespace std;

GameEngine::GameEngine() {

	stateVector_.push_back(new Meny(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Player1State(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new Fire(&graphicsengine_, &gameworld_));
	stateVector_.push_back(new ExitGame(&graphicsengine_, &gameworld_));

	currentState_ = MENY;

}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

void GameEngine::run()
{
	while(currentState_ != EXITGAME)
		{
			stateVector_[currentState_] ->render();
			currentState_ = stateVector_[currentState_]->next_state();
		};

	cout << "Thanks for using pantzer" << endl;
}
