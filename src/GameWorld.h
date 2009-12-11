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
#include "Player.h"

#define PI 3.14159265

typedef std::vector<Element*> ElementVector;
typedef std::vector<MovableElement*> MovableElementVector;

class GameWorld
{
public:
	GameWorld(Player* player1, Player* player2, const int& width=640,const int& height=480,const double& gravity=9.82,const double& wind =0);
	~GameWorld();

	void add_element(Element*);	// Adds element to the world
	bool update_world();	// update all elements
	const int get_randomSeed() const;	// get the seed which populated the world
	const int get_width() const;	// get the width of world (480 px)
	const int get_height() const;	// get the height of world (640 px)
	const double get_wind() const;
	void set_wind(const double&);	
	const double get_gravity() const;
	void set_gravity(const double&);
	ElementVector* get_elements();	// return pointer to element list
	MovableElementVector* get_MovableElemets();	// return pointer to movable-element list
	Cannon* get_leftCannon() const;	// pointer to left cannon
	Cannon* get_rightCannon() const;		// pointer to right cannon
	bool check_collision();	// check if a collision has occured
	bool check_collision(MovableElement*, Element*);	// check if two elements collide
	bool generate_world(const int& seed=0);	// generate the world from a seed
	const int getPlayer1Health() const;
	void setPlayer1Health(const int&);
	const int getPlayer2Health() const;
	void setPlayer2Health(const int&);
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
	Player* player1_;
	Player* player2_;
};

class GameWorldException
	:PanzerException
{
public:
	explicit GameWorldException(const std::string& what_arg) throw()
		:PanzerException(what_arg) {}			
};

#endif
