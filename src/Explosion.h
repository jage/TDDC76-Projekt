#ifndef EXPLOSION_H_
#define EXPLOSION_H_

class Explosion
{
public:
	Explosion(const int&,const int&,const int&);
	const int distance(const int&,const int&) const;	// get distance from explosion epicentrum
	const bool intersect(const int&,const int&) const; // is the point in the "explosion circle"
	const int deceasedHeight(const int&)	// get new decreased height if in radius
	virtual ~Explosion() {}
private:
	int x_;
	int y_;
	int radius_;
};

#endif /*EXPLOSION_H_*/
