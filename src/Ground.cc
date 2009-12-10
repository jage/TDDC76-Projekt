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
	// do i intersect with explosion area?
	if (expl.intersect(get_x(),get_y()))
	{
		// do some deformation	
		int new_y(expl.newY(get_x(),get_y()));
		cout << "- - - - - - " << endl;
		cout << "pos: " << get_x() << " " << get_y() << " distance to expl: " << expl.distance(get_x(),get_y()) << endl;
		height_=height_-(new_y-get_y());
		cout << "new y: " << new_y << " new height: " << height_ <<  endl;
		y_=new_y;
	}
}

Ground::~Ground()
{
}
