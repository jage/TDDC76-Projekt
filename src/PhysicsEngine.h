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
		void update_pos(vector<Element*>, double&);
		void update_pos(Element*, double&);

	private:
		void calc_new_pos(Movable*, double&);

};
#endif /*PHYSICSENGINE_H_*/

