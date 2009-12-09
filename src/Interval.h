#ifndef INTERVAL_H_
#define INTERVAL_H_

class Interval
{
public:
	Interval(const int&,const int&);
	const bool belongs(const int&) const;
	const int get_middle() const;
	virtual ~Interval() {};
private:
	int lower_;
	int upper_;
};

#endif /*INTERVAL_H_*/
