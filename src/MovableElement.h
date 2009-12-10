#ifndef MOVABLEELEMENT_H_
#define MOVABLEELEMENT_H_

#include "Element.h"
#include "Interfaces.h"


class MovableElement: public Element, public Movable {
public:
	MovableElement(const int& w, const int& h, PANZER_IMAGE imgRef,
			const int& x = 0, const int& y = 0, const double& angle = 0, double angle_freq = 0, double dx = 0, double dy = 0, double windfactor = 0);

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
