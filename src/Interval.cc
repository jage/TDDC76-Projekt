#include "Interval.h"

Interval::Interval(const int& lower,const int& upper)
:lower_(lower),upper_(upper) {}

const bool Interval::belongs(const int& value) const
{
	return (value>=lower_ && value<=upper_);
}

const bool Interval::intersect(const Interval& value) const
{
	return belongs(value.lower_) || belongs(value.upper_);	
}

const int Interval::get_upper() const
{
	return (int)upper_;
}

const int Interval::get_lower() const
{
	return (int)lower_;
}

const int Interval::get_middle() const
{
	return (int)((upper_+lower_)*0.5);	
}

const std::string Interval::str() const
{
	std::ostringstream os;

	os << "lower: " << lower_ << " upper: " << upper_;

	return os.str();
}
