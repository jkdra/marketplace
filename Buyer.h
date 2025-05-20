// Ammar Soliman

#ifndef BUYER_H
#define BUYER_H

#include "project.h"
#include "User.h"
#include "Wallet.h"
#include "Product.h"


class Buyer : public User {
public:
    Buyer(const string& name, const string& email, const string& password);
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    string getType() const;
    Wallet& getWallet();
    void addOrder(shared_ptr<Product> product);
    void display(std::ostream& os) const override;

private:
    Wallet myWallet;
    vector<shared_ptr<Product>> myOrders;
};

#endif //BUYER_H
