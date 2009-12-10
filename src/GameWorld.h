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
#include "Interval.h"
#include <vector>
#include <ctime>

#define PI 3.14159265

typedef std::vector<Element*> ElementVector;
typedef std::vector<MovableElement*> MovableElementVector;

class GameWorld
{
public:
	GameWorld(const int& width=640,const int& height=480,const double& gravity=9.82,const double& wind =0);
	~GameWorld();

	void add_element(Element*);
	bool update_world();
	const int get_randomSeed() const;
	const int get_width() const;
	const int get_height() const;
	const double get_wind() const;
	void set_wind(const double&);
	const double get_gravity() const;
	void set_gravity(const double&);
	ElementVector* get_elements();
	MovableElementVector* get_MovableElemets();
	Cannon* get_leftCannon() const;
	Cannon* get_rightCannon() const;
	bool generate_world(const int& seed=0);
private:
	int width_;
	int height_;
	double gravity_;
	double wind_;
	int randomSeed_;
	PhysicsEngine* ptr_physEngine_;
	ElementVector elements_;
	MovableElementVector movableElements_;
	Cannon* ptr_cannonL_;
	Cannon* ptr_cannonR_;
};

class GameWorldException
	:PanzerException
{
public:
	explicit GameWorldException(const std::string& what_arg) throw()
		:PanzerException(what_arg) {}			
};

#endif
