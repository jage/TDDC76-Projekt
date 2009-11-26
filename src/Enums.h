#ifndef ENUMS_H_
#define ENUMS_H_

enum PANZER_STATES
{
	MAINSTATE,
	MENY
};

enum PANZER_IMAGE
{
	CANNONBALL,
	CANNON,
	SUN
};

struct Collision
{
	bool has_collided;
	double x;
	double y;
	double blast_radius;
};

#endif
