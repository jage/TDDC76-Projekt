#include "Ammunition.h"
#include "Enums.h"

// Abstract ammunition class
Ammunition::Ammunition()
: MovableElement(100, 100, CANNONBALL, 10, 10, 10)
{
}

// Derived ammunition types

// Standard
const double StandardAmmo::get_blastRadius() const
{
	return 10; // for modification	
}

const Collision StandardAmmo::get_collision() const
{
 	Collision coll;
 	coll.x_=x_;
 	coll.y_=y_;
 	coll.blastRadius_=get_blastRadius();
 	
 	return coll;
}

