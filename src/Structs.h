#ifndef STRUCTS_H_
#define STRUCTS_H_

// Contains useful structs

// Velocity
struct Velocity
{
	double dx;
	double dy;
};

// Collision
struct Collision
{
	bool has_collided;
	double x;
	double y;
	double blast_radius;
};

#endif /*STRUCTS_H_*/
