#include "PhysicsEngine.h"
#include <math.h>
#include <stdlib.h>
#define DT 0.007		//Constant that represent 1/fps.


/*
 * update_pos calculate a new position on the given Movabable-element, gravity and wind.
 */
void PhysicsEngine::update_pos(MovableElement* element, const double& gravity, const double& wind) {
	update_x(element);
	update_y(element);
	update_dx(element, wind * 2);
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
	element->set_dx(element->get_dx() + return_sign(wind) * element->get_windFactor() *abs((pow((element->get_dx() * wind != 0 ? element->get_dx() * wind : 2*wind)/(element->get_dx() + wind),2))) * DT);
}

void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	//gravity equation in y direction
	element->set_dy(element->get_dy() + gravity * 120 * DT);
}

int PhysicsEngine::return_sign(int i){
	return i >= 0 ? 1 : -1;
}
