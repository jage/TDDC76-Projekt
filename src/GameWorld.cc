#include "GameWorld.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <math.h>
#include "Interfaces.h"
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
	
	//clear world
	elements_.clear();
	elements_.push_back(ptr_cannonL_);
	elements_.push_back(ptr_cannonR_);
	movableElements_.clear();
	
	//move cannons to correct x-coords
	ptr_cannonL_->set_x(ptr_cannonL_->get_width()*0.5);
	ptr_cannonR_->set_x(width-ptr_cannonR_->get_width()*0.5);
	
	int startHeight(0);
	int endHeight(0);
	int maxHeight(0);
	int minHeight(0);
	int offset(0);
	int noElements(0);
	
	maxHeight= (int)(height*(2/3.0));
	minHeight= (int)(height*0.1);
	offset=(int)(minHeight*0.2);
	noElements= (int)width/res;
	
	int* calculatedHeights;
	try
	{
		// allocate array
		calculatedHeights = new int [noElements];
	}
	catch (bad_alloc)
	{
		throw GameWorldException("Can't allocate enough memory");	
	}
	
	double calculatedHeight(0);
	
	// now generate heights of rectangles
	
	// feed rand with seed
	srand(time(NULL));
	
	double omega (0);
	double phase(0);	// random generated phase
	double amplitude(0);	// random generated amplitude
			
	omega = 2*PI*(1/(rand() % (width*2) + (0.25*width))); // between (1/4)width and 2*width;
	phase = rand() % 2*omega;		
	amplitude= rand() % maxHeight +minHeight;
	
	// use sinus	
	for (int i =0;i<noElements;i++)
	{	
			// calculate height with sinus
			calculatedHeight = minHeight+amplitude*sin(omega*i+phase);
			
			// if < minHeight -> set minHeight
			if (calculatedHeight<minHeight) calculatedHeight=minHeight;
			
			calculatedHeights[i]=(int)calculatedHeight;
	}
	
	// create ground elements
	Interval currInterval(0,res);
	startHeight = calculatedHeights[ptr_cannonL_->get_xInterval().get_upper()];
	endHeight = calculatedHeights[ptr_cannonR_->get_xInterval().get_lower()];
		
	for (int i =0;i<noElements;i++)
	{
		// check if one cannon is placed on current x-coord
		try
		{
			if(ptr_cannonL_->get_xInterval().intersect(currInterval)) add_element(new Concrete(res,startHeight,i*res,height-startHeight));
			else if(ptr_cannonR_->get_xInterval().intersect(currInterval)) add_element(new Concrete(res,endHeight,i*res,height-endHeight));
			else add_element(new Ground(res,calculatedHeights[i],i*res,height-calculatedHeights[i]));
		}
		catch (bad_alloc)
		{
			delete [] calculatedHeights;
			throw GameWorldException("Can't allocate enough memory");	
		}
		
		currInterval=Interval(i*res,i*res +res);
	}
	
	// place out the cannons on correct heights
	ptr_cannonL_->set_y(height-startHeight);
	ptr_cannonR_->set_y(height-endHeight);
	
		cout << "left cannon x: " << ptr_cannonL_->get_x() << "y: " << ptr_cannonL_->get_y() << endl;
	cout << "right cannon x: " << ptr_cannonR_->get_x() << "y: " << ptr_cannonR_->get_y() << endl;
	
//	 // test deform
//	 vector<Element*>::iterator it;
//	 Collision testColl;
//	 testColl.x_=425;
//	 testColl.blastRadius_ =35;
//	 
//	Destructable* dp;
//	 	
//	while( it != elements_.end() )
//		{
//			dp=dynamic_cast<Destructable*>(*it);
//			
//      		if(dp!=0)
//      		{
//    			dp->deform(testColl);  			
//      		}
//      		++it;
//		}
		
	delete []calculatedHeights;
	return true;
}
