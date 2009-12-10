#include "Ammunition.h"
#include "Enums.h"
#include "Explosion.h"

// Abstract ammunition class
Ammunition::Ammunition()
: MovableElement(10, 10, CANNONBALL)
{
}

// Derived ammunition types

// Standard
const int StandardAmmo::get_blastRadius() const
{
	return 50; // for modification	
}

const Explosion StandardAmmo::get_explosion() const
{
 	Explosion expl(get_x(),get_y(),get_blastRadius());
 	
 	return expl;
}

StandardAmmo* StandardAmmo::clone() const
{
	return new StandardAmmo();	
}

