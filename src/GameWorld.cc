#include "GameWorld.h"

GameWorld::GameWorld(const double& gravity,const double& wind)
	:gravity_(gravity),wind_(wind) {}

GameWorld::~GameWorld()
{}

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

std::vector<Element*>* GameWorld::get_elements()
{
	return &elements_;
}
