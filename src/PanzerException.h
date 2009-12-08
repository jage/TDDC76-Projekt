#ifndef PANZEREXCEPTION_H_
#define PANZEREXCEPTION_H_

#include <stdexcept>

class PanzerException
	: public std::logic_error
{
public:
	explicit PanzerException(const std::string& what_arg) throw()
		: std::logic_error(what_arg) {}
};

#endif /*PANZEREXCEPTION_H_*/
