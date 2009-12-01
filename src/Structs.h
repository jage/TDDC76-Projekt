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
	bool has_collided_;
	double x_;
	double y_;
	double blast_radius_;
};

#endif /*STRUCTS_H_*/
