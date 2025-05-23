// Ammar Soliman
#include "User.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Constructor for User
User::User(const string& name, const string& email, const string& password)
    : name(name), email(email), password(password) {
}

// Destructor for storeUser (no longer needed with smart pointers, but kept for completeness)
storeUser::~storeUser() {
    // Smart pointers clean up automatically; no manual delete required
}

// Add a user to the store
void storeUser::addUser(shared_ptr<User> user) {
    users.push_back(user);
}

// Find user by email
shared_ptr<User> storeUser::findUserByEmail(const std::string& email) {
    for (auto& user : users) {
        if (user->getEmail() == email) {
            return user;
        }
    }
    return nullptr;
}

// Stream insertion operator - delegates to virtual display
std::ostream& operator<<(std::ostream& os, const User& user) {
    user.display(os);
    return os;
}
