#ifndef STRUCTS_H_
#define STRUCTS_H_

// Contains useful structs

// Velocity
struct Velocity
{
	double dx_;
	double dy_;
};

// Collision
struct Collision
{
	int x_;
	int y_;
	int blastRadius_;
};

#endif /*STRUCTS_H_*/
