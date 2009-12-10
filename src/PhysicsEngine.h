#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>
#include "MovableElement.h"

class PhysicsEngine {
	
	public:
		void update_pos(MovableElement*, const double&, const double&); 		//indata: (element, gravitation, wind)

	private:
		void update_x(MovableElement*);						//indata: (element, gravitation)
		void update_y(MovableElement*);						//indata: (element, gravitation)
		void update_dx(MovableElement*, const double);
		void update_dy(MovableElement*, const double);
		int return_sign(int);
};
#endif /*PHYSICSENGINE_H_*/

