#ifndef GROUND_H_
#define GROUND_H_

#include "Interfaces.h"
#include "Element.h"
#include "Structs.h"
#include "Explosion.h"

class Ground : public Destructable, public Element
{
public:
	Ground(const int&,const int&, const int&x=0, const int&y=0);
	void deform(const Explosion&);
	virtual ~Ground();
};

#endif /*GROUND_H_*/
