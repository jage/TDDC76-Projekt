#include "PhysicsEngine.h"

using namespace std;


/*
 * Konstruktor till PhysicsEngine
 */
PhysicsEngine::PhysicsEngine() {
}


/*
 * update_pos på en vektor med element, givet en viss gravitation.
 */
void PhysicsEngine::update_pos(std::vector<Element&> vec_element, double& gravitation) {
	
	std::iterator it = vec_element.begin();

	while(it != vec_element.end())
	{
		if (dynamic_cast<Movable&>(it*))
		{
			update_pos(it*, graviation);		//använder update_pos för enstaka element
		}
	}
}

void PhysicsEngine::update_pos(Element& element, double& gavitation) {


}
