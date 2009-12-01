#include "GameWorld.h"

GameWorld::GameWorld()
{}

GameWorld::~GameWorld()
{}

void GameWorld::add_element(Element new_element)
{
	element_vector_.push_back(new_element);
}

Collision GameWorld::update_world()
{
	physics_engine_.update_pos(element_vector_,gravity_);
	return 1; //dummy
}

std::vector<Element>* GameWorld::get_element_vector()
{
	return &element_vector;
}
