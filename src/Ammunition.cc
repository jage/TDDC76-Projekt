#include "Ammunition.h"

// Abstract ammunition class
Ammunition::Ammunition()
{
}

// Derived ammunition types

// Standard
const double& StandardAmmo::get_blastRadius() const
{
	return 10;	
}

const Collision& StandardAmmo::get_collision() const
{
 	Collision coll;
 	coll.x=get_x;
 	coll.y=get_y;	
}

