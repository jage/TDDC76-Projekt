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
 	coll.x=x_;
 	coll.y=y_;
 	coll.blastRadius=get_blastRadius();
 	
 	return coll;
}

