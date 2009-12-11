#ifndef EXPLOSION_H_
#define EXPLOSION_H_

class Explosion
{
public:
	Explosion(const int&,const int&,const int&);
	const int distance(const int&,const int&) const;	// get distance from explosion epicentrum
	const bool intersect(const int&,const int&) const; // is the point in the "explosion circle"
	const int get_x() const;
	const int get_y() const;
	const int get_radius() const;
	const int newY(const int&,const int&) const;	// get new decreased height if in radius
	virtual ~Explosion() {}
private:
	int x_;
	int y_;
	int radius_;
};

#endif /*EXPLOSION_H_*/
