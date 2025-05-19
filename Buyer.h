// Ammar Soliman

#ifndef BUYER_H
#define BUYER_H

#include "project.h"
#include "User.h"

class Buyer : public User {
public:
    Buyer(const string& name, const string& email, const string& password);
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    string getType() const;
};

#endif //BUYER_H
