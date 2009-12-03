#include "PhysicsEngine.h"

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
	wind_dx(element, gravity);
}
void PhysicsEngine::update_dy(MovableElement* element, const double gravity){
	element->velocity_.dy_ = sqrt(sqr(element->velocity_.dy_) - 2*gravity*element->velocity.dy_);
}
void PhysicsEngine::update_x(MovableElement* element, const double gravity){
	element->x_ = element->x_ + element->velocity_.dx_;
}
void PhysicsEngine::update_y(MovableElement* element, const double gravity){
	element->y_ = element->y_ + element->velocity_.dy_;
}

void PhysicsEngine::wind_dx(MovableElement* element, const double wind){
	element->velocity_.dx_ = element->velocity_.dx_ *(1 - wind) * (1 - (element->y_ / 10000));
}
