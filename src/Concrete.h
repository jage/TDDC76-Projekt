#ifndef CONCRETE_H_
#define CONCRETE_H_

#include "Element.h"

class Concrete : public Element
{
public:
	Concrete(const int&,const int&,const int& x=0,const int& y=0);
	virtual ~Concrete();
};

#endif /*CONCRETE_H_*/
