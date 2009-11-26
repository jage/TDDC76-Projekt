#include "Element.h"

Element::Element(const int& height, const int& width, const PANZER_IMAGE& ImgRef, const int& x,const int& y,const double& angle)
	:height_(height),width_(width),imgRef_(ImgRef),x_(x),y_(y), angle_(angle) {}
