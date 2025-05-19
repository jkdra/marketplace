// Ammar Soliman

#include "Buyer.h"

using namespace std;

Buyer::Buyer(const string& name, const string& email, const string& password)
    : User(name, email, password) {
}
string Buyer::getName() const {
    return name;
}
string Buyer::getEmail() const {
    return email;
}
string Buyer::getPassword() const {
    return password;
}
string Buyer::getType() const {
    return "Buyer";
}