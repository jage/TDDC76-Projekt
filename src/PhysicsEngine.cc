#include "PhysicsEngine.h"
#include <math.h>
#include <stdlib.h>


double dt_ = 0.0125;
/*
 * update_pos beräknar den nya positionen för ett givet MovableElement-objekt samt en given gravitation.
 */
void PhysicsEngine::update_pos(MovableElement* element, const double& gravity, const double& wind) {
	update_dx(element, wind);
	update_dy(element, gravity);
	update_x(element);
	update_y(element);
}

void PhysicsEngine::update_x(MovableElement* element){
	element->set_x(element->get_x() + element->get_dx() * dt_);
}
void PhysicsEngine::update_y(MovableElement* element){
	element->set_y(element->get_y() + element->get_dy() * dt_);
}

void PhysicsEngine::update_dx(MovableElement* element, const double wind){
	element->set_dx(element->get_dx() - wind * abs(element->get_dx()) * element->get_windFactor() * dt_);
}

void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	element->set_dy(element->get_dy() - gravity * dt_ * 100);
}
