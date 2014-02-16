/*
 * socketException.h
 *
 *  Created on: 2014-02-15
 *      Author: oleg
 */

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include <string>
#include <exception>


class socketException : public std::exception
{
public:
	socketException(std::string err)
	{
		error= err;
	}

	virtual const char* what() const throw()
	{
		return this->error.c_str();
	}


private:
	std::string error;
};

#endif /* SOCKETEXCEPTION_H_ */
