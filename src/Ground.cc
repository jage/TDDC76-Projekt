#include "Ground.h"
#include "Enums.h"
#include "Interval.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

Ground::Ground(const int& width,const  int& height,const int& x, const int& y)
	:Element(width,height,GROUND,x,y) {}
	
void Ground::deform(const Explosion& expl)
{
	// in region of hit
	if (expl.intersect(get_x(),get_y()))
	{
			cout <<"Deform me!" << endl;
	}
}

Ground::~Ground()
{
}
