#include "Ammunition.h"

// Abstract ammunition class
Ammunition::Ammunition()
{
}

// Derived ammunition types

// Standard
const double& StandardAmmo::get_blastRadius() const
{
	return 10; // for modification	
}

const Collision& StandardAmmo::get_collision() const
{
 	Collision coll;
 	coll.x_=get_x;
 	coll.y_=get_y;	
}

