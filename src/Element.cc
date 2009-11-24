#include "Element.h"

Element::Element(const int& height, const int& width, const PANZER_IMAGE& ImgRef, const int& x,const int& y,const double& angle)
	:height_(height),width_(width),ImgRef_(ImgRef),x_(x),y_(y), _angle(angle) {}
