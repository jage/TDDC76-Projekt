#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_


#include "Element.h"
#include "Enums.h"
#include "MovableElement.h"
#include "PhysicsEngine.h"
#include "Cannon.h"
#include "Ground.h"
#include "Concrete.h"
#include "PanzerException.h"
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
	Cannon* get_cannon1() const;
	Cannon* get_cannon2() const;
	bool generate_world(const int&,const int&,const int&);
private:
	double gravity_;
	double wind_;
	PhysicsEngine* physEngine_;
	ElementVector elements_;
	MovableElementVector movableElements_;
	Cannon* cannon1_;
	Cannon* cannon2_;
};

class GameWorldException
	:PanzerException
{
public:
	explicit GameWorldException(const std::string& what_arg) throw()
		:PanzerException(what_arg) {}			
};

#endif
