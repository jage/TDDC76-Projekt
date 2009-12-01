#ifndef INTERFACES_H_
#define INTERFACES_H_

#include "Enums.h"
#include "Structs.h"

using namespace std;

// abstract class for use with movable game objects
class Movable
{
public:
	virtual const double& get_windFactor() const =0;
	virtual const Velocity& get_velocity() const =0;
	virtual void set_velocity(double&, double&) =0;
	virtual const double& get_angularFreq() const =0;
	virtual void set_angularFreq(double&) =0;
};

// abstract class for use with destructable game objects,
class Destructable
{
public:
	virtual void deform(const Collision&)=0;
};

#endif /*INTERFACES_H_*/
