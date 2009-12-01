#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>
#include "Element.h"
#include "Interfaces.h"

using namespace std;

class PhysicsEngine {
	
	public:
		PhysicsEngine();
		void update_pos(MovableElement, const double);
};
#endif /*PHYSICSENGINE_H_*/

