#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

/*
 *  Player
 */
class Player
{
public:
	Player(const std::string& = "", const int  = 100, const int = 0, const std::string& hostname = "", const std::string& port = "");
	~Player(){}
	 
	 /*
	  * get_name()
	  * Get the name of the player.
	  */
	const std::string& get_name() const;
	
	/*
	 * set_name()
	 * Set the players name.
	 */
	void set_name(const std::string& n);
	 
	/*
	 * get_health()
	 * Get the players health. 
	 */
	const int& get_health() const;
	
	/*
	 * set_health(int)
	 * Set the players health. 
	 */
	void set_health(const int);
	
	/*
	 * get_points()
	 * Get the players points.
	 */
	const int& get_points() const;
	
	/*
	 * set_points()
	 * Set the players points.
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
