#include "Player.h"

Player::Player(const std::string& name, int& health, int& points):health_(health),name_(name),points_(points){}

const std::string& Player::get_name() const
{
	return name_;
}

void Player::set_name(const string& name)
{
	name_=name;
}

int Player::get_health()
{
	return health_;
}

int Player::set_health()
{
	health_=health;
}

int Player::get_points()
{
	return points_;
}

void Player::set_points()
{
	points_=points;
}

