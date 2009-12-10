#include "Cannon.h"
#include "Enums.h"
#include "math.h"
#include "iostream"

Cannon::Cannon(Ammunition* ptrAmmo,const bool& leftCannon)
	:Element(50,58, LEFT_CANNON),power_(0),ptr_ammunition_(ptrAmmo)
{
	// set right cannon if not left
	if(!leftCannon) set_imgRef(RIGHT_CANNON);
}

void Cannon::adjust_angle(const double& delta)
{
	Element::set_angle(get_angle() + delta);
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

Ammunition* Cannon::fire()
{
	//std::cout << ptr_ammunition_->get_dx();
	Ammunition* newAmmo;
	*newAmmo = *ptr_ammunition_;


	newAmmo->set_dx(power_*cos(get_angle()));
	newAmmo->set_dy(power_*sin(get_angle()));
	fired_=true;
	return newAmmo;
}

void Cannon::disarm()
{
	fired_=false;
}

Cannon::~Cannon()
{
	delete ptr_ammunition_;
}
