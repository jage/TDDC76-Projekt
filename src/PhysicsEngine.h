#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>
#include "MovableElement.h"

class PhysicsEngine {
	
	public:
		void update_pos(MovableElement*, const double&, const double&); 		//indata: (element, gravitation, wind)

	private:
		/*
		* void update_x uppdaterar x-positionen hos ett Movable-element
		*/
		void update_x(MovableElement*);


		/*
		* void update_y uppdaterar y-positionen hos ett Movable-element
		*/
		void update_y(MovableElement*);

		/*
		* void update_dx uppdaterar dx-variabeln hos ett Movable-element
		*/
		void update_dx(MovableElement*, const double);

		/*
		* void update_dy uppdaterar dy-variabeln hos ett Movable-element
		*/
		void update_dy(MovableElement*, const double);

		/*
		* int return_sign returnerar tecknet på en int-variabel
		*/
		int return_sign(int);
};
#endif /*PHYSICSENGINE_H_*/

