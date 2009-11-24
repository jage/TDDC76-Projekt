#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Enums.h"

using namespace std;

class Element
{
public:
	Element(const int&,const int&,const PANZER_IMAGE&,const int& x=0,const int& y=0,const double& angle=0); // x,y,imgRef,width,height,angle
	const int& get_x();
	void set_x(const int&);
	const int& get_y();
	void set_y(const int&);
	const double& get_angle();
	void set_angle(const double&);
	const int& get_height();
	const int& get_width();
	const PANZER_IMAGE& get_imgRef();
	virtual ~Element(){};
private:
	int x_;		// x coordinate
	int y_;		// y coordinate
	int width_;	// width of element
	int height_; // height of element
	double angle_; // the rotation angle of element
	PANZER_IMAGE imgRef;	// reference to element image 
};

#endif /*ELEMENT_H_*/
