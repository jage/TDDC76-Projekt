#ifndef CANNON_H_
#define CANNON_H_

#include "Element.h"
#include "Ammunition.h"

class Cannon : public Element
{
public:
	Cannon(Ammunition*);
	void set_angle(const double&);	// sets the angle
	void adjust_angle(const double&); // increase/decrease the angle
	const double& get_angle() const;
	void set_power(const int&);
	const double& get_power() const;
	void change_ammunition(const Ammunition*);
	const Ammunition* get_ammunition() const;
	void fire(); 
	virtual ~Cannon();
private:
	double fireAngle_;
	int power_;
	Ammunition* ptr_ammunition_; // pointer to current ammunition object 
};

#endif /*CANNON_H_*/
