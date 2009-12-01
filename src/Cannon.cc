#include "Cannon.h"
#include "Enums.h"

Cannon::Cannon(Ammunition* ptrAmmo=0)
	:Element(10,10, CANNON),fireAngle_(0),power_(0),ptr_ammunition_(ptrAmmo)	{}
	
void Cannon::set_angle(const double& value)
{
	fireAngle_=value;
}

void Cannon::adjust_angle(const double& delta)
{
	fireAngle_+=delta;
}

const double& Cannon::get_angle() const
{
	return fireAngle_;	
}

void Cannon::set_power(const int& value)
{
	power_=value;	
}

void Cannon::change_ammunition(Ammunition* newAmmo)
{
	delete ptr_ammunition_;
	ptr_ammunition_=newAmmo;
}

Ammunition* Cannon::get_ammunition() const
{
	return ptr_ammunition_;	
}

const bool Cannon::fired() const
{
	return fired_;	
}

void Cannon::fire()
{
	fired_=true;
}

Cannon::~Cannon()
{
	delete ptr_ammunition_;
}
