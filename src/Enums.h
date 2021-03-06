#ifndef ENUMS_H_
#define ENUMS_H_

enum PANZER_STATES
{
	PLAYER1STATE = 0,
	NETWORKSTATE,
	OPTIONSTATE,
	EXITGAME,
	FIRE,
	MENY,
	PLAYER2STATE,
	INITSTATE,
	SETNAMESTATE,
	SELECTLEVEL,
	POSTMATCH,
	FIREEND

};

enum PANZER_IMAGE
{
	GROUND,
	CONCRETE,
	LEFT_CANNON,
	RIGHT_CANNON,
	CANNONBALL
};

enum PANZER_ALIGNMENT
{
	LEFT,
	RIGHT,
	CENTER
};

enum PANZER_FONT
{
	LAZY32,
	LAZY26,
	PAPER_CUT72
};

#endif
