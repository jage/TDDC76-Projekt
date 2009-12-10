#include "Cannon.h"
#include "Enums.h"
#include "math.h"
#include "iostream"

Cannon::Cannon(Ammunition* ptrAmmo,const bool& leftCannon)
	:Element(50,58, LEFT_CANNON),power_(0),ptr_ammunition_(ptrAmmo)
{
	// set right cannon if not left
	if(!leftCannon) {
		set_imgRef(RIGHT_CANNON);
		Element::set_angle(180);
	}
}

void Cannon::adjust_angle(const double& delta)
{
	if (imgRef_ == LEFT_CANNON) {
		Element::set_angle(get_angle() + delta);
	}
	else {
		Element::set_angle(get_angle() - delta);
	}
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
	Ammunition* newAmmo = ptr_ammunition_->clone();

	newAmmo->set_x(get_x() + 65*cos(3.14/180 * get_angle()));
	newAmmo->set_y(get_y() - 65*sin(3.14/180 * get_angle()) - 20);

	std::cout <<"x: " << newAmmo->get_x() <<std::endl;
	std::cout <<"y: " << newAmmo->get_y() <<std::endl;


	newAmmo->set_dx(power_*cos(3.14/180 * get_angle()));
	newAmmo->set_dy(-power_*sin(3.14/180 * get_angle()));

	std::cout <<"vinkel: " << get_angle() <<std::endl;

	std::cout <<"dx: " << newAmmo->get_dx() <<std::endl;
	std::cout <<"dy: " << newAmmo->get_dy() <<std::endl <<std::endl;

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
