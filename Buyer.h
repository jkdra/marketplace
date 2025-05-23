// Ammar Soliman

#ifndef BUYER_H
#define BUYER_H

#include "project.h"
#include "User.h"
#include "Wallet.h"
#include "Product.h"
#include "Exceptions.h"


class Buyer : public User {
friend class Cache;

public:
    Buyer(const string& name, const string& email, const string& password);
    string getName() const override;
    string getEmail() const override;
    string getPassword() const override;
    string getType() const override;
    void display(std::ostream& os) const override;

    Wallet getWallet() const;
    void addOrder(const shared_ptr<Product> &product);

    // Overloading << operator by Jawad Khadra
    friend ostream& operator<<(ostream& os, const Buyer& buyer);

private:
    Wallet wallet;
    vector<shared_ptr<Product>> myOrders;
};

#endif //BUYER_H
