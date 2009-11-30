#include "PhysicsEngine.h"

using namespace std;


/*
 * Konstruktor till PhysicsEngine
 */
PhysicsEngine::PhysicsEngine() {
}


/*
 * update_pos(std::vector<Element&> vec_element, double& gravitation)
 * updaterar positionen hos Element-objekt av typen Movable, givet en viss gravitation.
 */
void PhysicsEngine::update_pos(std::vector<Element&> vec_element, double& gravitation) {
	
	std::iterator it = vec_element.begin();

	while(it != vec_element.end())
	{
		if (dynamic_cast<Movable&>(*it))
		{
			calc_new_pos(*it, graviation);		//använder calc_new_pos för enstaka element
		}
	}
}


/*
 * update_pos(Element& element, double& gravitation)
 * updaterar positionen om Element-objektet är av typen Movable, givet en viss gravitation.
 */
void PhysicsEngine::update_pos(Element& element, double& gravitation) {

	if (dynamic_cast<Movable&>(element))
	{
		calc_new_pos(element, graviation);		//använder calc_new_pos om element är av typen Movable
	}
}


/*
 * calc_new_pos beräknar den nya positionen för ett givet Movable-objekt samt en given gravitation.
 */
void PhysicsEngine::calc_new_pos(Movable& element, double& gravitation) {
	element.set_velocity(
			element.get_velocity().dx,
			sqrt(sqr(element.get_velocity().dy) - 2*gravitation*element.get_velocity().dy)
			);
}




