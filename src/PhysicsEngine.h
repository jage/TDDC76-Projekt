#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>
#include "MovableElement.h"

using namespace std;

class PhysicsEngine {
	
	public:
		//PhysicsEngine(){};
		void update_pos(MovableElement*, const double, const double); 		//indata: (element, gravitation, wind)
	private:
		void update_dx(MovableElement*, const double);						//indata: (element, gravitation)
		void update_dy(MovableElement*, const double);						//indata: (element, gravitation)
		void update_x(MovableElement*, const double);						//indata: (element, gravitation)
		void update_y(MovableElement*, const double);						//indata: (element, gravitation)
		void wind_effect(MovableElement*, const double);					//indata: (element, wind)
};
#endif /*PHYSICSENGINE_H_*/

