#include "Cannon.h"
#include "Enums.h"

Cannon::Cannon(Ammunition* ptrAmmo)
	:Element(50,58, CANNON),power_(0),ptr_ammunition_(ptrAmmo)	{}
	

void Cannon::adjust_angle(const double& delta)
{
	angle_+=delta;
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
