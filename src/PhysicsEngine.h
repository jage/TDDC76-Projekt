#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include <iostream>
#include <vector>

using namespace std;

class PhysicsEngine {
	
	public:
		PhysicsEngine();
		void update_pos(vector<Element&>, double&);
		void update_pos(Element&, double&);
	
	private:
		
	
}
#endif /*PHYSICSENGINE_H_*/

