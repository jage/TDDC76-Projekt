#include "Ground.h"
#include "Enums.h"

Ground::Ground(const int& width,const  int& height,const int& x, const int& y)
	:Element(width,height,GROUND,x,y) {}
	
void Ground::deform(const Collision& collision)
{
	// do some deformation
	return	
}

Ground::~Ground()
{
}
