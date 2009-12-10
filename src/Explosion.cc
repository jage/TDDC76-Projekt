#include "Explosion.h"
#include <iostream>
#include <math.h>

using namespace std;

Explosion::Explosion(const int& x,const int& y,const int& radius)
:x_(x),y_(y),radius_(radius) {}

const int Explosion::get_x() const
{
	return x_;	
}

const int Explosion::get_y() const
{
	return y_;	
}

const int Explosion::distance(const int& x,const int& y) const
{
		double d(0);
		
		d= ceil(sqrt(pow(x-(double)x_,2)+pow(y-(double)y_,2)));
		
		return (int)d;
}

const bool Explosion::intersect(const int& x,const int& y) const
{
	return pow(x-(double)x_,2)+pow(y-(double)y_,2)<=pow((double)radius_,2);
}

const int Explosion::newY(const int& x,const int& y) const
{
	int circle_y(0);
	circle_y =y_+(int)sqrt(pow((double)radius_,2)-pow((double)x-(double)x_,2));
	
	return circle_y;
}

const int Explosion::get_radius() const
{
	return radius_;
}