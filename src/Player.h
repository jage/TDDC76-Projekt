#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

/*
 * Player - abstrakt basklass f�r alla tr�dnodsklasser.
 */

class Player
{
public:
	Player(int& , std::string&, int&);
	 virtual ~Player();
	 
	 	/*
	 * get_name()
	 * H�mtar en spelares(Players) namn.
	 */
	const std::string& get_name() const;
	
	/*
	 * set_name()
	 * S�tter en spelares(Player) namn.
	 */
	void set_name(const string& n);
	 
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
	virtual event get_event();
	
	
	
 private:
 	int health_;
 	int points_;
 	std::string name_;	
};

#endif /*PLAYER_H_*/
