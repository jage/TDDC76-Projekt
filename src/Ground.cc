#include "Ground.h"
#include "Enums.h"
#include "Interval.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

Ground::Ground(const int& width,const  int& height,const int& x, const int& y)
	:Element(width,height,GROUND,x,y) {}
	
void Ground::deform(const Collision& coll)
{
	// define borders
	Interval blastInterval(coll.x-coll.blastRadius,coll.x+coll.blastRadius);
	
	// in region of hit
	if (blastInterval.intersect(get_xInterval()))
	{
		
		//double decrease =coll.blastRadius_*exp(-0.5*(x_-coll.blastRadius_));
		double decrease(5);
		cout << "im deformed! with " << decrease << " pixels." << endl;  
		height_= height_ -(int)decrease;
		y_=y_+(int)decrease;
	}
}

Ground::~Ground()
{
}
