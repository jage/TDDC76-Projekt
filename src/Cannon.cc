#include "Cannon.h"
#include "Enums.h"

Cannon::Cannon(Ammunition* ptrAmmo,const bool& leftCannon)
	:Element(50,58, LEFT_CANNON),fireAngle_(0),power_(0),ptr_ammunition_(ptrAmmo)
{
	// set right cannon if not left
	if(!leftCannon) set_imgRef(RIGHT_CANNON);
}

void Cannon::adjust_angle(const double& delta)
{
	set_angle(get_angle() + delta);
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
