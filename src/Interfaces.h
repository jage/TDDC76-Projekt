#ifndef INTERFACES_H_
#define INTERFACES_H_

#include "Enums.h"

using namespace std;

// abstract class for use with movable game objects
class Movable
{
public:
	const double& get_windFactor() const=0;
	const Velocity& get_velocity() const=0
	void set_velocity(const Velocity&)=0;
	const double& get_angularFreq() const=0;
	void set_angularFreq()=0;
}

// abstract class for use with destructable game objects,
class Destructable
{
public:
	virtual deform(const Collision&)=0;
}

#endif /*INTERFACES_H_*/
