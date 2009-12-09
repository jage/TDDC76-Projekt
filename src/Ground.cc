#include "Ground.h"
#include "Enums.h"
#include <cstdlib>
#include <math.h>

Ground::Ground(const int& width,const  int& height,const int& x, const int& y)
	:Element(width,height,GROUND,x,y) {}
	
void Ground::deform(const Collision& coll)
{
	// define borders
	int leftBorder=coll.x_-coll.blastRadius_;
	int rightBorder=coll.x_+coll.blastRadius_;
	
	// in region of hit
	if (x_>=leftBorder||x_<=rightBorder)
	{
		double decrease =coll.blastRadius_*exp(-0.5*(x_-coll.blastRadius_)); 
		height_= height_ -(int)decrease;
		x_=x_+(int)decrease;
	}
}

Ground::~Ground()
{
}
