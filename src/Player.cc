#include "Player.h"
#include "State.h"

using namespace std;

Player::Player(const string& name, const int health, const int points)
 : name_(name), health_(health), points_(points) {}

const string& Player::get_name() const
{
	return name_;
}

void Player::set_name(const string& name)
{
	name_ = name;
}

const int& Player::get_health() const
{
	return health_;
}

void Player::set_health(const int health)
{
	health_ = health;
}

const int& Player::get_points() const
{
	return points_;
}

void Player::set_points(const int points)
{
	points_ = points;
}

