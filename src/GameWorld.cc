#include "GameWorld.h"
#include <iostream>
#include <exception>
#include <cstdlib>
using namespace std;

GameWorld::GameWorld(const double& gravity,const double& wind)
	:gravity_(gravity),wind_(wind) 
{
	// allocate some memory
	try
	{
		ptr_physEngine_= new PhysicsEngine();
		ptr_cannonL_ = new Cannon();
		ptr_cannonR_= new Cannon();
	}
	catch (bad_alloc)
	{
		throw GameWorldException("Can't allocate memory");	
	}
	
	// add cannons to element vector
	add_element(ptr_cannonL_);
	add_element(ptr_cannonR_);	
}

GameWorld::~GameWorld()
{
	delete ptr_cannonL_;
	delete ptr_cannonR_;
	delete ptr_physEngine_;
}

ElementVector* GameWorld::get_elements()
{
	return &elements_;
}

void GameWorld::add_element(Element* ptr_newElement)
{
	elements_.push_back(ptr_newElement);
}

bool GameWorld::update_world()
{
	vector<MovableElement*>::iterator it = movableElements_.begin();
	while(it != movableElements_.end())
	{
		MovableElement* movElem = *it;
		ptr_physEngine_->update_pos(movElem,gravity_,wind_);
		++it;
	}
	return 1; //dummy
}

const double& GameWorld::get_gravity() const
{
	return gravity_;	
}

void GameWorld::set_gravity(const double& gravity)
{
	gravity_=gravity;	
}

const double& GameWorld::get_wind() const
{
	return wind_;	
}

void GameWorld::set_wind(const double& wind)
{
	wind_=wind;	
}

Cannon* GameWorld::get_leftCannon() const
{
	return ptr_cannonL_;	
}

Cannon* GameWorld::get_rightCannon() const
{
	return ptr_cannonR_;	
}

bool GameWorld::generate_world(const int& width,const int& height, const int& res)
{
	if (width % res !=0) return false; // width must be an even multiple of the resolution 
	
	int maxHeight((int)height*(2.0/3.0)); // max height
	int minHeight((int)height*(1.0/10.0)); // min height of a rectangle
	int offset(minHeight * 0.1); // offset between two rectangles
	int noElements((int)width/res);
	int* randomHeights;
	
	try
	{
		// allocate array
		randomHeights = new int [noElements];
	}
	catch (bad_alloc)
	{
		throw GameWorldException("Can't allocate enough memory");	
	}
	
	int randomHeight(0);
	int prevHeight(0);
	
	// now generate random heights of rectangles
	for (int i =0;i<noElements;i++)
	{	
		// generate new height and check if its ok
		do 
		{
			randomHeight= rand() % maxHeight + minHeight;
			
			// i=0
			if (prevHeight==0) prevHeight=randomHeight;
		}
		while(abs(randomHeight-prevHeight)>offset);
		
		// we got a ok height, store it
		randomHeights[i]=randomHeight;
		prevHeight = randomHeight;
	}
	
	// create ground elements
	int rightCannonX(ptr_cannonR_->get_x());
	int currX(0); // current x-coord
	
	for (int i =0;i<noElements;i++)
	{
		// check if one cannon is placed on current x-coord
		try
		{
			if (CANNON_WIDTH-currX>0 || rightCannonX-currX<0)add_element(new Concrete(randomHeights[i], res, currX,height-randomHeights[i]));
			else add_element(new Ground(res,randomHeights[i],currX,height-randomHeights[i]));
		}
		catch (bad_alloc)
		{
			delete [] randomHeights;
			throw GameWorldException("Can't allocate enough memory");	
		}
		
		currX+=res;
	}
	
	delete []randomHeights;
	return true;
}
