#include "GameWorld.h"

GameWorld::GameWorld()
{}

GameWorld::~GameWorld()
{}

void GameWorld::add_element(Element new_element)
{
	element_vector.push_back(new_element);
}

Collision GameWorld::update_world()
{return Collision();}
/*	// Ska implementeras med PhysicsEngine senare

	for(std::vector<Element>::iterator it = element_vector.begin();
		it != element_vector.end();
		++it)
	{
		(*it).update_element();
	}
	
	Collision coll;
	coll.blast_radius = 0;
	coll.has_collided = false;
	coll.x = 0;
	coll.y = 0;

	return coll;
}*/

std::vector<Element>* GameWorld::get_element_vector()
{
	return &element_vector;
}
