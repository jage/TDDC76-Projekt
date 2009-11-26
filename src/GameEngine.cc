/*
 * GameEngine.cpp
 *
 *  Created on: Nov 22, 2009
 *      Author: rosjo
 */

#include "iostream"
#include "GameEngine.h"
#include "State.h"
using namespace std;

GameEngine::GameEngine() {

	meny_ptr_ = new Meny(&graphicengine_,&gameworld_);
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

void GameEngine::run() {
	bool exit_now = false;
	char input = 0;

	while(!exit_now)
	{
		cout << "Pre meny\n";
		cin >> input;
		if(input == 'q')
			exit_now = true;

		//current_state_->render();
		meny_ptr_->render();

	}
	cout << "Thanks for using pantzer" << endl;
}
