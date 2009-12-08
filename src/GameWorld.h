#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_


#include "Element.h"
#include "Enums.h"
#include "MovableElement.h"
#include "PhysicsEngine.h"
#include "Cannon.h"
#include <vector>

typedef std::vector<Element*> ElementVector;
typedef std::vector<MovableElement*> MovableElementVector;

class GameWorld
{
public:
	GameWorld(const double& gravity=9.82,const double& wind =0);
	~GameWorld();

	void add_element(Element*);
	bool update_world();
	const double& get_wind() const;
	void set_wind(const double&);
	const double& get_gravity() const;
	void set_gravity(const double&);
	ElementVector* get_elements();
private:
	double gravity_;
	double wind_;
	PhysicsEngine physEngine_;
	ElementVector elements_;
	MovableElementVector movableElements_;
	Cannon cannon1_;
	Cannon cannon2_;
};

#endif
