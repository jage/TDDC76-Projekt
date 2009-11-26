#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

/*
 * Player - abstrakt basklass för alla trädnodsklasser.
 */

class Player
{
public:
	Player(int health, std::string name, int points);
	
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
	 * get_name()
	 * Hämtar en spelares(Players) namn.
	 */
	std::string get_name();
	
	/*
	 * set_name()
	 * Sätter en spelares(Player) namn.
	 */
	void set_name();
	
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
	virtual event get_event();'
	
	virtual ~Player();
	
 private:
 	int health;
 	int points;
 	std::string name;	
};

#endif /*PLAYER_H_*/
