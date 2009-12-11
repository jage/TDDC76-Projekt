#include "PhysicsEngine.h"
#include <math.h>
#include <stdlib.h>
#define DT 0.014		//Constant that represent 1/fps.


/*
 * update_pos calculate a new position on the given Movabable-element, gravity and wind.
 */
void PhysicsEngine::update_pos(MovableElement* element, const double& gravity, const double& wind) {
	update_x(element);
	update_y(element);
	update_dx(element, wind * 3);
	update_dy(element, gravity);
}

void PhysicsEngine::update_x(MovableElement* element){
	//set new x-pos
	element->set_x(element->get_x_pos() + element->get_dx() * DT);
}
void PhysicsEngine::update_y(MovableElement* element){
	//set new y-pos
	element->set_y(element->get_y_pos() + element->get_dy() * DT);
}

void PhysicsEngine::update_dx(MovableElement* element, const double wind){
	//The wind equation in x direction
	element->set_dx(element->get_dx() +  0.1 * wind * element->get_windFactor() * abs(element->get_dx() - wind) * DT);
}

void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	//gravity equation in y direction
	element->set_dy(element->get_dy() + gravity * 42 * DT);
}

int PhysicsEngine::return_sign(int i){
	return i >= 0 ? 1 : -1;
}
