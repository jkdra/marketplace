#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "project.h"

#include <stdexcept>

// Justin Dodd
class CacheException : public std::runtime_error {
	public:
	
	CacheException() : std::runtime_error("invalid cache") {}
};

#endif // EXCEPTIONS_H
