#include "PhysicsEngine.h"

using namespace std;


/*
 * Konstruktor till PhysicsEngine
 */
PhysicsEngine::PhysicsEngine() {
}


/*
 * update_pos(std::vector<Element*> vec_element, double& gravity)
 * updaterar positionen hos Element-objekt av typen Movable, givet en viss gravitation.
 */
void PhysicsEngine::update_pos(std::vector<Element*> vec_element, double& gravity) {
	
	std::iterator it = vec_element.begin();

	while(it != vec_element.end())
	{
		if (dynamic_cast<Movable*>(*it))
		{
			calc_new_pos(*it, gravity);		//använder calc_new_pos för enstaka element
		}
	}
}


/*
 * update_pos(Element* element, double& gravity)
 * updaterar positionen om Element-objektet är av typen Movable, givet en viss gravitation.
 */
void PhysicsEngine::update_pos(Element* element, double& gravity) {

	if (dynamic_cast<Movable*>(element))
	{
		calc_new_pos(element, gravity);		//använder calc_new_pos om element är av typen Movable
	}
}


/*
 * calc_new_pos beräknar den nya positionen för ett givet Movable-objekt samt en given gravitation.
 */
void PhysicsEngine::calc_new_pos(Movable* element, double& gravity) {
	element->set_velocity(
			element->get_velocity().dx_,
			sqrt(sqr(element->get_velocity().dy_) - 2*gravity*element->get_velocity().dy_)
			);
}




