#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <string>
#include <sstream>

class Interval
{
public:
	Interval(const int&,const int&);
	const bool belongs(const int&) const;
	const bool intersect(const Interval&) const;
	const int get_middle() const;
	const std::string str() const;
	virtual ~Interval() {};
private:
	int lower_;
	int upper_;
};

#endif /*INTERVAL_H_*/
