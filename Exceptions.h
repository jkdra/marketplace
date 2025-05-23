#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "project.h"

#include <stdexcept>

// Justin Dodd
class CacheException : public std::runtime_error {
	public:
	
	CacheException() : std::runtime_error("invalid cache") {}
};

// Jawad Khadra
class InsufficientFundsException : public std::runtime_error {
public:
InsufficientFundsException() : std::runtime_error("Insufficient funds") {}
}

// Jawad Khadra
class ProductNotFoundException : public std::runtime_error {
public:
ProductNotFoundException() : std::runtime_error("Product not found") {}
}

// Jawad Khadra
class UnauthorizedActionException : public std::runtime_error {
public:
UnauthorizedActionException() : std::runtime_error("Unauthorized action") {}
}

#endif // EXCEPTIONS_H
