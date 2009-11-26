/*
 * State.cpp
 *
 *  Created on: Nov 23, 2009
 *      Author: rosjo
 */

#include "State.h"
#include <iostream>

using namespace std;
//State---------------------------------------------------------//
State::State(GraphicEngine* graphicengine, GameWorld* gameworld)
	: graphicengine_ptr_(graphicengine), gameworld_ptr_(gameworld){}
State::~State() {}
//--------------------------------------------------------------//


//Meny-----------------------------------------------------------//

//Meny::Meny(){}

Meny::Meny(GraphicsEngine* graphicsengine, GameWorld* gameworld)
	 : State(graphicsengine,gameworld){}

Meny::~Meny(){}

void Meny::render(){
	cout << "Welcome to Pantzer!\n"
		 << "A, view the abouts\n\n"
		 << "$>";
}

void Meny::handle_input(std::istream& stream){

	char input = 0;
	stream >> input;

	if(input == 'A')
		cout << "Made by lazy students\n\n";
	else
		cout << "Try another key\n";
}

PANZER_STATES Meny::next_state()
{
	return MENY;
}
//---------------------------------------------------------------//


