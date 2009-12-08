#include "PhysicsEngine.h"
#include <math.h>

/*
 * update_pos beräknar den nya positionen för ett givet MovableElement-objekt samt en given gravitation.
 */
void PhysicsEngine::update_pos(MovableElement* element, const double gravity, const double wind) {
	update_dx(element, wind);
	update_dy(element, gravity);
	update_x(element, gravity);
	update_y(element,gravity);
}

void PhysicsEngine::update_dx(MovableElement* element, const double wind){
	//wind_effect(element, gravity);
}
void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	element->set_dy( sqrt( pow(element->get_dy(),2) - 2 * gravity * element->get_dy() ));
}
void PhysicsEngine::update_x(MovableElement* element, const double gravity){
	element->set_x(element->get_x() + element->get_dx());
}
void PhysicsEngine::update_y(MovableElement* element, const double gravity){
	element->set_y(element->get_y() + element->get_dy());
}

void PhysicsEngine::wind_effect(MovableElement* element, const double wind){
	element->set_dx(element->get_dx() *(1 - wind) * (1 - (element->get_y()/ 10000)));
}
