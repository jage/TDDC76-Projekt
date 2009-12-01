#include "Interfaces.h"

Movable::Movable(double& angle_freq = 0)
:angle_freq_(angle_freq){
	set_velocity(0,0);
}

double& Movable::get_angularFreq(){
	return angle_freq;
}

void Movable::set_angularFreq(double& angle_freq_){
	angle_freq_ = angle_freq;
}

Velocity& Movable::get_velocity(){
	return velocity_;
}

void Movable::set_velocity(double& dx_, double& dy_){
	velocity.dx_ = dx;
	velocity.dy_ = dy;
}
