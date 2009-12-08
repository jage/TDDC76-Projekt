#include "GameWorld.h"

GameWorld::GameWorld(const double& gravity,const double& wind)
	:gravity_(gravity),wind_(wind) {}

GameWorld::~GameWorld()
{}

ElementVector* GameWorld::get_elements()
{
	return &elements_;
}

void GameWorld::add_element(Element* ptr_newElement)
{
	elements_.push_back(ptr_newElement);
}

bool GameWorld::update_world()
{
	vector<MovableElement*>::iterator it = movableElements_.begin();
	while(it != movableElements_.end())
	{
		MovableElement* movElem = *it;
		physEngine_.update_pos(movElem,gravity_,wind_);
		++it;
	}
	return 1; //dummy
}

const double& GameWorld::get_gravity() const
{
	return gravity_;	
}

void GameWorld::set_gravity(const double& gravity)
{
	gravity_=gravity;	
}

const double& GameWorld::get_wind() const
{
	return wind_;	
}

void GameWorld::set_wind(const double& wind)
{
	wind_=wind;	
}
