#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>
#include "MovableElement.h"

class PhysicsEngine {
	
	public:
		// void update_pos update the given Movableelement, given gravity and wind
		void update_pos(MovableElement*, const double&, const double&);

	private:
		// void update_x, update the x-position on a Movable-element
		void update_x(MovableElement*);

		// void update_y, update the x-position on a Movable-element
		void update_y(MovableElement*);

		// void update_dx, update the x-position on a Movable-element
		void update_dx(MovableElement*, const double);

		// void update_dy, update the x-position on a Movable-element
		void update_dy(MovableElement*, const double);


		// return the sign on a given integer
		int return_sign(int);
};
#endif /*PHYSICSENGINE_H_*/

