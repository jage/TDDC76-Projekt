#ifndef PLAYER_H_
#define PLAYER_H_

#include "SDLInclude.h"
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
	 * handle_event() - en ren virtuell funktion
	 * Hämtar en händelse.
	 */
	  SDL_Event& handle_event(SDL_Event& event);
	
	
	
 private:
 	std::string name_;	
 	int health_;
 	int points_;
};

#endif /*PLAYER_H_*/
