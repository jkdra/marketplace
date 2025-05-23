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

// Stream insertion operator - delegates to virtual display
std::ostream& operator<<(std::ostream& os, const User& user) {
    user.display(os);
    return os;
}
