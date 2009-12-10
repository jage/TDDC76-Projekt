#ifndef CANNON_H_
#define CANNON_H_

#include "Element.h"
#include "Ammunition.h"

class Cannon : public Element
{
public:
	Cannon(Ammunition* ammo=new StandardAmmo(),const bool& leftCannon=true);
	void set_angle(const double&);	// sets fire angle
	void adjust_angle(const double&); // increase/decrease fire angle
	void set_power(const int&);
	const double get_power() const;
	void change_ammunition(Ammunition*); // change ammunition
	Ammunition* get_ammunition() const; // get pointer to current ammunition
	Ammunition* fire();	// fire the cannon
	void disarm();
	const bool fired() const; // is the cannon fired?
	virtual ~Cannon();
private:
	int power_;
	bool fired_;
	Ammunition* ptr_ammunition_; // pointer to current ammunition object 
};

#endif /*CANNON_H_*/
