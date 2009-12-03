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
 	coll.x_=x_;
 	coll.y_=y_;
 	
 	return coll;
}

