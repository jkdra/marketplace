// Ammar Soliman
#ifndef USER_H
#define USER_H
#include "project.h"
#include "Cache.h"
#include <memory>
#include <vector>
#include <memory>

using namespace std;

class User {
public:
	User(const string& name, const string& email, const string& password);
	virtual ~User() = default;
	virtual string getName() const = 0;
	virtual string getEmail() const = 0;
	virtual string getType() const = 0;
	virtual string getPassword() const = 0;
	virtual void display(ostream& os) const = 0;
	friend ostream& operator<<(ostream& os, const User& user);

protected:
	string name;
	string email;
	string password;
};

#endif //USER_H
