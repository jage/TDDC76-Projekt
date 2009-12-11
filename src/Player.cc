#include "Player.h"

using namespace std;

Player::Player(const string& name, const int health, const int points, const string& hostname, const string& port)
 : name_(name), health_(health), points_(points), hostname_(hostname), port_(port) {}

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
}q

bool Player::network()
{	
	return !hostname_.empty() && !port_.empty();
}

void Player::set_hostname(const std::string& hostname)
{
	hostname_ = hostname;
}

void Player::set_port(const std::string& port)
{
	port_ = port;
}

const string& Player::get_hostname() const
{
	return hostname_;
}

const string& Player::get_port() const
{
	return port_;
}

