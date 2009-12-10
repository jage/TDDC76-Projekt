#ifndef PLAYER_H_
#define PLAYER_H_

#include "SDLInclude.h"
#include <string>
#include <iostream>

/*
 * Player - abstrakt basklass f�r alla tr�dnodsklasser.
 */

class Player
{
public:
	Player(const std::string& = "", const int  = 100, const int = 0, const std::string& hostname = "", const std::string& port = "");
	virtual ~Player(){};
	 
	 /*
	  * get_name()
	  * H�mtar en spelares(Players) namn.
	  */
	const std::string& get_name() const;
	
	/*
	 * set_name()
	 * S�tter en spelares(Player) namn.
	 */
	void set_name(const std::string& n);
	 
	/*
	 * get_health()
	 * H�mtar en spelares(Players) h�lsa i form av ett heltal. 
	 */
	const int& get_health() const;
	
	/*
	 * set_health(int)
	 * S�tter en spelares(Player) h�lsa. 
	 */
	void set_health(const int);
	
	/*
	 * get_points()
	 * H�mtar en spelares(Player) po�ng.
	 */
	const int& get_points() const;
	
	/*
	 * set_points()
	 * S�tter en spelares(Player) po�ng.
	 */
	void set_points(const int);	
	
	/*
	 * network()
	 * true if the opponent is a remote player
	 */
	bool network();
	
	/*
	 *
	 */
	void set_hostname(const std::string&);
	void set_port(const std::string&);
	const std::string& get_hostname() const;
	const std::string& get_port() const;

 private:
 	std::string name_;	
 	int health_;
 	int points_;
	std::string hostname_;
	std::string port_;
};

#endif /*PLAYER_H_*/
