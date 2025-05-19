// Ammar Soliman
#ifndef USER_H
#define USER_H
#include "project.h"
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

protected:
    string name;
    string email;
    string password;
};
class storeUser {
private:
    vector<User*> users;
public:
    ~storeUser();
    void addUser(User* user);


};

#endif //USER_H
