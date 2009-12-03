#include "MovableElement.h"

MovableElement::MovableElement(double angle_freq = 0)
:angle_freq_(angle_freq){
	set_velocity(0,0);
}

double& MovableElement::get_angularFreq(){
	return angle_freq;
}

void MovableElement::set_angularFreq(double angle_freq){
	angle_freq_ = angle_freq;
}

Velocity& MovableElement::get_velocity(){
	return velocity_;
}

void MovableElement::set_velocity(double dx, double dy){
	velocity_.dx_ = dx;
	velocity_.dy_ = dy;
}

