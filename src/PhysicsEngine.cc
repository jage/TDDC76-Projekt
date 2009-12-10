#include "PhysicsEngine.h"
#include <math.h>
#include <stdlib.h>


double dt_ = 0.0125;
/*
 * update_pos beräknar den nya positionen för ett givet MovableElement-objekt samt en given gravitation.
 */
void PhysicsEngine::update_pos(MovableElement* element, const double& gravity, const double& wind) {
	update_x(element);
	update_y(element);
	update_dx(element, wind * 100);
	update_dy(element, gravity);
}

void PhysicsEngine::update_x(MovableElement* element){
	element->set_x(element->get_x_pos() + element->get_dx() * dt_);
}
void PhysicsEngine::update_y(MovableElement* element){
	element->set_y(element->get_y_pos() + element->get_dy() * dt_);
}

void PhysicsEngine::update_dx(MovableElement* element, const double wind){
	element->set_dx(element->get_dx() + return_sign(wind) * wind * element->get_windFactor() * abs(element->get_dx() - wind) * dt_);
}

void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	element->set_dy(element->get_dy() + gravity * 42 * dt_);
}

int PhysicsEngine::return_sign(int i){
	return i >= 0 ? 1 : -1;
}
