#ifndef AMMUNITION_H_
#define AMMUNITION_H_

#include "Element.h"
#include "Structs.h"

class Ammunition : public MovableElement
{
public:
	Ammunition();
	virtual const double& get_blast_radius() const =0;
	virtual const Collision& get_collision() const=0;
	virtual ~Ammunition();
};

/*
 * Derived ammunition types
 */

/*
 * Standard ammunition
 */
class StandardAmmo: public Ammunition
{
	public:
		const double& get_blastRadius() const;
		const Collision& get_collision() const;
};

#endif /*AMMUNITION_H_*/
