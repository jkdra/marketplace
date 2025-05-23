#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "project.h"
#include <stdexcept>

using namespace std;

// Justin Dodd
class CacheException : public runtime_error {
	public:
	
	CacheException() : runtime_error("invalid cache") {}
};

// Jawad Khadra
class InsufficientFundsException : public runtime_error {
public:
InsufficientFundsException() : runtime_error("Insufficient funds") {}
}

// Jawad Khadra
class ProductNotFoundException : public runtime_error {
public:
ProductNotFoundException() : runtime_error("Product not found") {}
}

// Jawad Khadra
class UnauthorizedActionException : public runtime_error {
public:
UnauthorizedActionException() : runtime_error("Unauthorized action") {}
}

#endif // EXCEPTIONS_H
