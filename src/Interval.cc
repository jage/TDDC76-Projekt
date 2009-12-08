#include "Interval.h"

Interval::Interval(const int& lower,const int& upper)
:lower_(lower),upper_(upper) {}

const bool Interval::belongs(const int& value) const
{
	return (value>=lower_ && value<=upper_);
}

const int Interval::get_middle() const
{
	return (int)((upper_+lower_)*0.5);	
}
