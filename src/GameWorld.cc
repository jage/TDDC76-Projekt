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
	if ((width-2*ptr_cannonL_->get_width()) % res !=0) return false; // width must be an even multiple of the resolution minus two widths of the cannons
	
	int startHeight(0);
	int endHeight(0);
	int maxHeight(0);
	int minHeight(0);
	int offset(0);
	int noElements(0);
	
	maxHeight= (int)(height*(2/3.0));
	minHeight= (int)(height*(1/10.0));
	offset=(int)(minHeight * 0.1);
	noElements= (int)width/res;
	
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
	
	// feed rand with seed
	srand(time(NULL));
	
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
	Interval leftCannonInterval(0,ptr_cannonL_->get_width());
	Interval rightCannonInterval(width-ptr_cannonR_->get_width(),width);
	
	startHeight = randomHeights[0];
	endHeight = randomHeights[noElements-1];
		
	for (int i =0;i<noElements;i++)
	{
		// check if one cannon is placed on current x-coord
		try
		{
			if(leftCannonInterval.belongs(i*res)) add_element(new Concrete(res,startHeight,i*res,height-startHeight));
			else if(rightCannonInterval.belongs(i*res)) add_element(new Concrete(res,endHeight,i*res,height-endHeight));
			else add_element(new Ground(res,randomHeights[i],i*res,height-randomHeights[i]));
		}
		catch (bad_alloc)
		{
			delete [] randomHeights;
			throw GameWorldException("Can't allocate enough memory");	
		}
	}
	
	// place out the cannons
	ptr_cannonL_->set_y(height-startHeight);
	ptr_cannonL_->set_x(leftCannonInterval.get_middle());
	ptr_cannonR_->set_y(height-endHeight);
	ptr_cannonR_->set_x(rightCannonInterval.get_middle());
	delete []randomHeights;
	return true;
}
