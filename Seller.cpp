// Ammar Soliman

#include "Seller.h"

using namespace std;
Seller::Seller(const string& name, const string& email, const string& password, const string& company)
    : User(name, email, password), company(company) {
}
string Seller::getName() const {
    return name;
}
string Seller::getEmail() const {
    return email;
}
string Seller::getPassword() const {
    return password;
}
string Seller::getType() const {
    return "Seller";
}
