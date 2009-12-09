#include "MovableElement.h"

MovableElement::MovableElement(const int& w, const int& h, PANZER_IMAGE imgRef,
		const int& x, const int& y, const double& angle, double angle_freq, double dx, double dy, double windfactor)
		: Element(w,h,imgRef,x,y,angle){
	set_angularFreq(angle_freq_);
	set_velocity(dx,dy);
	set_windFactor(windfactor);
}

const double& MovableElement::get_angularFreq() const{
	return angle_freq_;
}

void MovableElement::set_angularFreq(double& angle_freq){
	angle_freq_ = angle_freq;
}

const Velocity& MovableElement::get_velocity() const{
	return velocity_;
}
void MovableElement::set_dx(double dx){
	velocity_.dx_ = dx;
}
void MovableElement::set_dy(double dy){
	velocity_.dy_ = dy;
}
void MovableElement::set_velocity(double& dx, double& dy){
	velocity_.dx_ = dx;
	velocity_.dy_ = dy;
}

const double& MovableElement::get_dx() const{
	return velocity_.dx_;
}

const double& MovableElement::get_dy() const{
	return velocity_.dy_;
}

const double& MovableElement::get_windFactor() const{
	return windFactor_;
}

void MovableElement::set_windFactor(double windfactor){
	windFactor_ = windfactor;
}
