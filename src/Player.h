#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

/*
 * Player - abstrakt basklass f�r alla tr�dnodsklasser.
 */

class Player
{
public:
	Player(int health, std::string name, int points);
	virtual ~Player();
	
	/*
	 * get_health()
	 * H�mtar en spelares(Players) h�lsa i form av ett heltal. 
	 */
	int get_health();
	
	/*
	 * set_health(int)
	 * S�tter en spelares(Player) h�lsa. 
	 */
	int set_health(int);
	
	/*
	 * get_name()
	 * H�mtar en spelares(Players) namn.
	 */
	std::string get_name();
	
	/*
	 * set_name()
	 * S�tter en spelares(Player) namn.
	 */
	void set_name();
	
	/*
	 * get_points()
	 * H�mtar en spelares(Player) po�ng.
	 */
	int get_points();
	
	/*
	 * set_points()
	 * S�tter en spelares(Player) po�ng.
	 */
	void set_points();	
	
	/*
	 * get_event() - en ren virtuell funktion
	 * H�mtar en h�ndelse.
	 */
	virtual event get_event();'
	
 private:
 	int health;
 	int points;
 	std::string name;	
};

#endif /*PLAYER_H_*/
