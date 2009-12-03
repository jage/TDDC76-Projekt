#include "GameWorld.h"
#include "MovableElement.h"

GameWorld::GameWorld():gravity(9.82)
{}

GameWorld::~GameWorld()
{}

void GameWorld::add_element(Element new_element)
{
	element_vector_.push_back(new_element);
}

Collision GameWorld::update_world()
{
	vector<MovableElement*>::iterator it = movable_element_vector_.begin();
	while(it != movable_element_vector_.end())
	{
		physics_engine_.update_pos(*it,gravity);
		++it;
	}
	return Collision(); //dummy
}

std::vector<Element>* GameWorld::get_element_vector()
{
	return &element_vector_;
}
