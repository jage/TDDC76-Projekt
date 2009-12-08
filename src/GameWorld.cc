#include "GameWorld.h"
#include <iostream>
#include <exception>

GameWorld::GameWorld(const double& gravity,const double& wind)
	:gravity_(gravity),wind_(wind) 
{
	// allocate some memory
	try
	{
		physEngine_= new PhysicsEngine();
		cannon1_ = new Cannon();
		cannon2_= new Cannon();
	}
	catch (bad_alloc)
	{
		throw GameWorldException("Can't allocate memory");	
	}
	
	// add cannons to element vector
	add_element(cannon1_);
	add_element(cannon2_);	
}

GameWorld::~GameWorld()
{
	delete cannon1_;
	delete cannon2_;
	delete physEngine_;
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
		physEngine_->update_pos(movElem,gravity_,wind_);
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

Cannon* GameWorld::get_cannon1() const
{
	return cannon1_;	
}

Cannon* GameWorld::get_cannon2() const
{
	return cannon2_;	
}

bool GameWorld::generate_world(const int& width,const int& height, const int& res)
{
	if (width % res !=0) return false; // width must be an even multiple of the resolution 
	
	int maxHeight((int)height*(2/3)); // max height
	int minHeight((int)height*(1/10)); // min height of a rectangle
	int offset(minHeight); // offset between two rectangles
	int noElements((int)width/res);
	int* randomHeights;
	
	try
	{
		// allocate array
		randomHeights = new int [noElements-1];
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
	int rightCannonX(cannon2_->get_x());
	int currX(0); // current x-coord
	
	for (int i =0;i<noElements;i++)
	{
		// check if one cannon is placed on current x-coord
		try
		{
			if (CANNON_WIDTH-currX>0 || rightCannonX-currX<0)add_element(new Concrete(res,randomHeights[i],currX,height-randomHeights[i]));
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
