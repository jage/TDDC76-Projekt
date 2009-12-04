#ifndef MOVABLEELEMENT_H_
#define MOVABLEELEMENT_H_

#include "Element.h"
#include "Interfaces.h"


class MovableElement: public Element, public Movable {
public:
	MovableElement(const int&, const int&, PANZER_IMAGE,
			const int&, const int&, const double&, double = 0, double = 0, double = 0, double = 0);

	virtual ~MovableElement(){};

	const double& get_angularFreq() const;
	void set_angularFreq(double&);

	const double& get_dx() const;
	const double& get_dy() const;
	const Velocity& get_velocity() const;
	void set_dx(double);
	void set_dy(double);
	void set_velocity(double&,double&);

	const double& get_windFactor() const;
	void set_windFactor(double);

private:
	double angle_freq_;
	Velocity velocity_;
	double windFactor_;

};

#endif /* MOVABLEELEMENT_H_ */
