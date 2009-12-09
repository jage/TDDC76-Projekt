#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Enums.h"
#include "Structs.h"
#include "Interval.h"

//using namespace std;

class Element
{
public:
	Element(const int&,const int&,const PANZER_IMAGE&,const int& x=0,const int& y=0,const double& angle=0); // w,h,imgRef,x,y,angle
	const int get_x() const;
	const Interval get_xInterval() const;
	void set_x(const int&);
	void set_x(const double&);
	const int get_y() const;
	void set_y(const int&);
	void set_y(const double&);
	void set_angle(const double&);
	const double get_angle() const;
	const int get_height() const;
	const int get_width() const;
	void set_imgRef(const PANZER_IMAGE&);
	const PANZER_IMAGE get_imgRef() const;
	virtual ~Element() {};
protected:
	 int width_;	// width of element
	 int height_; // height of element
	 PANZER_IMAGE imgRef_;	// reference to element image
	 int x_;		// x coordinate
	 int y_;		// y coordinate
	double angle_; // the rotation angle of element
};

#endif /*ELEMENT_H_*/
