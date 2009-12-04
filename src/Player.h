#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

/*
 * Player - abstrakt basklass för alla trädnodsklasser.
 */

class Player
{
public:
	Player(const std::string&, const int, const int);
	virtual ~Player(){};
	 
	 /*
	  * get_name()
	  * Hämtar en spelares(Players) namn.
	  */
	const std::string& get_name() const;
	
	/*
	 * set_name()
	 * Sätter en spelares(Player) namn.
	 */
	void set_name(const std::string& n);
	 
	/*
	 * get_health()
	 * Hämtar en spelares(Players) hälsa i form av ett heltal. 
	 */
	const int& get_health() const;
	
	/*
	 * set_health(int)
	 * Sätter en spelares(Player) hälsa. 
	 */
	void set_health(const int);
	
	/*
	 * get_points()
	 * Hämtar en spelares(Player) poäng.
	 */
	const int& get_points() const;
	
	/*
	 * set_points()
	 * Sätter en spelares(Player) poäng.
	 */
	void set_points(const int);	
	
	/*
	 * get_event() - en ren virtuell funktion
	 * Hämtar en händelse.
	 */
	//virtual SDL_Event get_event();
	
	
	
 private:
 	int health_;
 	int points_;
 	std::string name_;	
};

#endif /*PLAYER_H_*/
