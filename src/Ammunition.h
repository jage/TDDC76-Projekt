#ifndef AMMUNITION_H_
#define AMMUNITION_H_

#include "MovableElement.h"
#include "Structs.h"
#include "Explosion.h"

class Ammunition : public MovableElement
{
public:
	Ammunition();
	virtual const int get_blastRadius() const =0;
	virtual const Explosion get_explosion() const=0;
	virtual Ammunition* clone() const=0;
	virtual ~Ammunition(){};
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
		const int get_blastRadius() const;
		StandardAmmo* clone() const;
		const Explosion get_explosion() const;
		const double get_windFactor() const;
};

#endif /*AMMUNITION_H_*/
