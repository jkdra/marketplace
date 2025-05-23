#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "project.h"
#include <stdexcept>

using namespace std;

// Justin Dodd
class CacheException : public exception {
	public:
	CacheException() {}
	const char* what() const noexcept override { return "Invalid Cache"; }
};

// Jawad Khadra
class InsufficientFundsException : public exception {
public:
	InsufficientFundsException() {}
	const char* what() const noexcept override { return "Insufficient Funds"; }
};

// Jawad Khadra
class ProductNotFoundException : public exception {
public:
	ProductNotFoundException() {}
	const char* what() const noexcept override { return "Product Not Found"; }
};

// Jawad Khadra
class UnauthorizedActionException : public exception {
public:
	UnauthorizedActionException() {}
	const char* what() const noexcept override { return "Unauthorized Action"; }
};

#endif // EXCEPTIONS_H
