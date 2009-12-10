#include "Explosion.h"
#include <math.h>

Explosion::Explosion(const int& x;const int& y,const int& radius)
:x_(x),y_(y),radius_(radius) {}

const int Explosion::distance(const int& x,const int& y) const
{
		double d(0);
		
		d= sqrt(pow(x-x_,2)+pow(y-y_,2));
		
		return (int)d;
}

const bool intersect(const int& x,const int& y) const
{
	return distance(x,y)<=radius_;	
}

const int deceasedHeight(const int& x,const int& y) const
{
	// only do calculation if point is in the circle (no imaginary roots please)
	if(intersect(x,y) return (int)ceil(y_+sqrt(pow(radius_,2)-pow(x-x_,2)));
	else return 0
}

