/*
 * MovableElement.h
 *
 *  Created on: Dec 1, 2009
 *      Author: jonas
 */

#ifndef MOVABLEELEMENT_H_
#define MOVABLEELEMENT_H_

#include "Element.h"
#include "Interfaces.h"

class MovableElement: public Element, public Movable {
public:
	MovableElement();
	virtual ~MovableElement();
	double get_angularFreq();
	void set_angularFreq(double);
	Velocity& get_velocity();
	void set_velocity(double, double);

private:
	double angle_freq_;
	Velocity velocity_;

};

#endif /* MOVABLEELEMENT_H_ */
