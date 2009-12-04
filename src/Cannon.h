#ifndef CANNON_H_
#define CANNON_H_

#include "Element.h"
#include "Ammunition.h"

class Cannon : public Element
{
public:
	Cannon(Ammunition* ammo=0);
	void set_angle(const double&);	// sets fire angle
	void adjust_angle(const double&); // increase/decrease fire angle
	const double& get_angle() const;
	void set_power(const int&);
	const double& get_power() const;
	void change_ammunition(Ammunition*); // change ammunition
	Ammunition* get_ammunition() const; // get pointer to current ammunition
	void fire();	// fire the cannon
	const bool fired() const; // is the cannon fired?
	virtual ~Cannon();
private:
	double fireAngle_;
	int power_;
	bool fired_;
	Ammunition* ptr_ammunition_; // pointer to current ammunition object 
};

#endif /*CANNON_H_*/
