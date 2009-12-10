#include "Element.h"
#include "iostream"

// Constructor
Element::Element(const int& width, const int& height, const PANZER_IMAGE& ImgRef, const int& x,const int& y,const double& angle)
	:width_(width),height_(height),imgRef_(ImgRef),x_(x),y_(y), angle_(angle) {}
	
const int Element::get_x() const {
	return (int)(x_ + 0.5);
}
const double Element::get_x_pos() const {
	return x_;
}

void Element::set_x(const int& x){
	x_ = x;
}

const Interval Element::get_xInterval() const
{
	return Interval(x_-(int)(width_/2),x_+(int)(width_/2));	
}

void Element::set_y(const int& y)
{
	y_=y;	
}
void Element::set_x(const double& x){
	x_ = x;
}


const int Element::get_y() const {
	return (int)(y_ + 0.5);
}
const double Element::get_y_pos() const {
	return y_;
}
void Element::set_y(const int& y) {
	y_ = y;
}
void Element::set_y(const double& y) {
	y_ = y;
}


const double Element::get_angle() const {
	return angle_;
}
void Element::set_angle(const double& angle) {
	angle_ = angle;
}


const int Element::get_width() const {
	return width_;
}
const int Element::get_height() const {
	return height_;
}


const PANZER_IMAGE Element::get_imgRef() const {
	return imgRef_;
}
