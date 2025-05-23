// Ammar Soliman
#ifndef USER_H
#define USER_H
#include "project.h"
#include <memory>
#include <vector>

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

class storeUser {
private:
	vector<shared_ptr<User>> users;
public:
	~storeUser();
	void addUser(shared_ptr<User> user);
	// storeUser.h
	shared_ptr<User> findUserByEmail(const string& email);

	void displayAllUsers() const {
		if (users.empty()) {
			cout << "No users registered." << endl;
			return;
		}
		
		for (const auto& user : users) cout << *user << endl;
	}
};

#endif //USER_H
