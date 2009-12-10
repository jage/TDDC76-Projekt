#include "GameWorld.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <math.h>
#include "Interfaces.h"
#include "Ground.h"

using namespace std;

GameWorld::GameWorld(const int& width,const int& height,const double& gravity,const double& wind)
	:width_(width),height_(height),gravity_(gravity),wind_(wind) 
{
	// allocate some memory
	try
	{
		ptr_physEngine_= new PhysicsEngine();
		ptr_cannonL_ = new Cannon(new StandardAmmo(),true);
		ptr_cannonR_= new Cannon(new StandardAmmo(),false);
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

MovableElementVector* GameWorld::get_MovableElemets()
{
	return &movableElements_;
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

const int GameWorld::get_randomSeed() const
{
	return randomSeed_;
}

const int GameWorld::get_width() const
{
	return width_;	
}

const int GameWorld::get_height() const
{
	return height_;	
}

const double GameWorld::get_gravity() const
{
	return gravity_;	
}

void GameWorld::set_gravity(const double& gravity)
{
	gravity_=gravity;	
}

const double GameWorld::get_wind() const
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

bool GameWorld::generate_world(const int& seed)
{	
	//clear world
	elements_.clear();
	elements_.push_back(ptr_cannonL_);
	elements_.push_back(ptr_cannonR_);
	movableElements_.clear();	
	
	//move cannons to correct x-coords
	ptr_cannonL_->set_x(ptr_cannonL_->get_width()*0.5);
	ptr_cannonR_->set_x(width_-ptr_cannonR_->get_width()*0.5);
	
	int startHeight(0);
	int endHeight(0);
	int maxHeight(0);
	int minHeight(0);
	int offset(0);
	int noElements(0);
	
	maxHeight= (int)(height_*(2/3.0));
	minHeight= (int)(height_*0.1);
	offset=(int)(minHeight*0.2);
	noElements= (int)width_;
	
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
	if (seed!=0) randomSeed_=seed;
	randomSeed_=time(NULL);
	
	srand(randomSeed_);
	
	double omega (0);
	double phase(0);	// random generated phase
	double amplitude(0);	// random generated amplitude
			
	omega = 2*PI*(1/(rand() % (width_*2) + (0.25*width_))); // between (1/4)width and 2*width;
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
	startHeight = calculatedHeights[ptr_cannonL_->get_xInterval().get_upper()];
	endHeight = calculatedHeights[ptr_cannonR_->get_xInterval().get_lower()];

	for (int i =0;i<noElements;i++)
	{
		// check if one cannon is placed on current x-coord
		try
		{
			if(ptr_cannonL_->get_xInterval().belongs(i)) add_element(new Concrete(1,startHeight,i,height_-startHeight));
			else if(ptr_cannonR_->get_xInterval().belongs(i)) add_element(new Concrete(1,endHeight,i,height_-endHeight));
			else add_element(new Ground(1,calculatedHeights[i],i,height_-calculatedHeights[i]));
		}
		catch (bad_alloc)
		{
			delete [] calculatedHeights;
			throw GameWorldException("Can't allocate enough memory");	
		}
	}

	// place out the cannons on correct heights
	ptr_cannonL_->set_y(height_-startHeight-15);
	ptr_cannonR_->set_y(height_-endHeight-15);

	/* // test deform
	Explosion testExpl(315,350,48);

	Destructable* dp;

	vector<Element*>::iterator it = elements_.begin();
	while(it != elements_.end())
	{
	Element* elem = *it;
	dp = dynamic_cast<Destructable*>(elem);

	if (dp!=0) dp->deform(testExpl);

	++it;
	}*/

	delete []calculatedHeights;
	return true;
}

bool GameWorld::check_collision(){
	ElementVector::iterator elements_it = elements_.begin();
	MovableElementVector::iterator movableElements_it = movableElements_.begin();

	bool has_collided = false;
	while( movableElements_it != movableElements_.end())
	{
		if((*movableElements_it)->get_y() > 480) {
			movableElements_.erase(movableElements_it);
			return true;
		}
		while(elements_it != elements_.end())
		{
			if(*movableElements_it != *elements_it)
			{
				if(check_collision(*movableElements_it, *elements_it))
				{
					if (Ammunition* ammo_ptr= dynamic_cast<Ammunition*>(*movableElements_it))
					{

						Explosion testExpl(ammo_ptr->get_x(), ammo_ptr->get_y(), ammo_ptr->get_blastRadius());

						Destructable* dp;

						vector<Element*>::iterator it = elements_.begin();
						while(it != elements_.end())
						{
							Element* elem = *it;
							dp = dynamic_cast<Destructable*>(elem);

							if (dp!=0)
							{
								dp->deform(testExpl);
							}
							++it;
						}
					}
					movableElements_.erase(movableElements_it);
					return true;
				}
			}
			++elements_it;
		}
		++movableElements_it;
	}

	return false;
}

bool GameWorld::check_collision(MovableElement* movableElement, Element* element){
	double El = 0, Er = 0, Eu = 0, Ed = 0;
	if(dynamic_cast<Ground*>(element) || dynamic_cast<Concrete*>(element))
	{
		El = element->get_x();
		Er = element->get_x() + element->get_width() - 1;
		Eu = element->get_y();
		Ed = element->get_y() + element->get_height();
	}
	else {
		El = element->get_x() - element->get_width()/2;			//Element left bound
		Er = element->get_x() + element->get_width()/2;			//Element right bound
		Eu = element->get_y() - element->get_height()/2;			//Element upper bound
		Ed = element->get_y() + element->get_height()/2;			//Element down bound
	}

	double Ml = movableElement->get_x() - movableElement->get_width()/2;	//MovableElement left bound
	double Mr = movableElement->get_x() + movableElement->get_width()/2;	//MovableElement right bound
	double Mu = movableElement->get_y() - movableElement->get_height()/2;	//MovableElement upper bound
	double Md = movableElement->get_y() + movableElement->get_height()/2;	//MovableElement down bound

	if(Md < Eu)
		return false;
	if(Ed < Mu)
		return false;
	if(Mr < El )
		return false;
	if(Er < Ml)
		return false;

	return true;
}
