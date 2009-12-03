#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_


#include "Element.h"
#include "Enums.h"
#include "MovableElement.h"
#include "PhysicsEngine.h"
#include <vector>


class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void add_element(Element);
	Collision update_world();
	std::vector<Element>* get_element_vector();

	std::vector<Element> element_vector_;
	std::vector<MovableElement*> movable_element_vector_;

private:
	PhysicsEngine physics_engine_;
	//Wind
	const double gravity;
	//Cannon cannon1
	//Cannon cannon2
};

#endif
