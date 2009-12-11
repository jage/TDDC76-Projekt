#include "Cannon.h"
#include "Enums.h"
#include "math.h"
#include <iostream>

Cannon::Cannon(Player* player, Ammunition* ptrAmmo,const bool& leftCannon)
	: Element(50,58, LEFT_CANNON),power_(0),ptr_ammunition_(ptrAmmo), player_(player)
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

	newAmmo->set_dx(10*power_*cos(3.14/180 * get_angle()));
	newAmmo->set_dy(-10*power_*sin(3.14/180 * get_angle()));

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

void Cannon::deform(const Explosion& exp)
{
	double exp_distance = exp.distance(get_x(), get_y());
	if (exp_distance < exp.get_radius())
	{
		player_->set_health(player_->get_health() - exp_distance / exp.get_radius() * 100);
	}
}
