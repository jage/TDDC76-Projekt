#include "PhysicsEngine.h"

/*
 * update_pos beräknar den nya positionen för ett givet MovableElement-objekt samt en given gravitation.
 */
void PhysicsEngine::update_pos(MovableElement& element, const double gravity) {
	element.set_velocity(
			element.get_velocity().dx_,
			sqrt(sqr(element.get_velocity().dy_) - 2*gravity*element.get_velocity().dy_)
			);
}




