// Ammar Soliman

#ifndef SELLER_H
#define SELLER_H

#include "project.h"
#include "User.h"


class Seller : public User {
public:
    Seller(const string& name, const string& email, const string& password, const string& company);
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    string getType() const;
private:
    string company;
};

#endif
