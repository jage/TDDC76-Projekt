#include "Element.h"

// Constructor
Element::Element(const int& width, const int& height, const PANZER_IMAGE& ImgRef, const int& x,const int& y,const double& angle)
	:width_(width),height_(height),imgRef_(ImgRef),x_(x),y_(y), angle_(angle) {}
	
void Element::set_x(const int& x)
{
	x_=x;	
}

void Element::set_x(const double& x)
{
	x_=(int)x;	
}

const int Element::get_x() const
{
	return x_;
}

const Interval Element::get_xInterval() const
{
	return Interval(x_-(int)(width_/2),x_+(int)(width_/2));	
}

void Element::set_y(const int& y)
{
	y_=y;	
}

void Element::set_y(const double& y)
{
	y_=(int)y;	
}

const int Element::get_y() const
{
	return y_;
}

void Element::set_angle(const double& angle)
{
	angle_=angle;	
}

const double Element::get_angle() const
{
	return angle_;
}

const int Element::get_width() const
{
	return width_;
}

const int Element::get_height() const
{
	return height_;
}

const PANZER_IMAGE Element::get_imgRef() const
{
	return imgRef_;
}
