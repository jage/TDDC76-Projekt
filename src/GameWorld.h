#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_


#include "Element.h"
#include "Enums.h"
#include <vector>


class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void add_element(Element);
	Collision update_world();
	std::vector<Element>* get_element_vector();

	std::vector<Element> element_vector;

private:
	PhysicsEngine physics_engine_;
	//Wind
	const double gravity = 9.82;
	//Cannon cannon1
	//Cannon cannon2
};

#endif
