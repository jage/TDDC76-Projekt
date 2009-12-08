#ifndef PLAYER_H_
#define PLAYER_H_

#include "LocalPlayer.h"
#include "NetworkPlayer.h"
#include <string>

/*
 * Player - abstrakt basklass för alla trädnodsklasser.
 */

class Player
{
public:
	Player(std::string& , int& , int& );
	 virtual ~Player();
	 
	 	/*
	 * get_name()
	 * Hämtar en spelares(Players) namn.
	 */
	const std::string& get_name() const;
	
	/*
	 * set_name()
	 * Sätter en spelares(Player) namn.
	 */
	void set_name(const string& name);
	 
	/*
	 * get_health()
	 * Hämtar en spelares(Players) hälsa i form av ett heltal. 
	 */
	int get_health();
	
	/*
	 * set_health(int)
	 * Sätter en spelares(Player) hälsa. 
	 */
	int set_health(int);
	
	/*
	 * get_points()
	 * Hämtar en spelares(Player) poäng.
	 */
	int get_points();
	
	/*
	 * set_points()
	 * Sätter en spelares(Player) poäng.
	 */
	void set_points();	
	
	/*
	 * get_event() - en ren virtuell funktion
	 * Hämtar en händelse.
	 */
	virtual event get_event();
	
	
	
 private:
 	std::string name_;	
 	int health_;
 	int points_;
 	
};

#endif /*PLAYER_H_*/
