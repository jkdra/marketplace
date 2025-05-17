#ifndef WALLET_H
#define WALLET_H
#include "project.h"
#include <stdexcept>

class Wallet {
public:
    explicit Wallet(double balance = 0.0);

    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;

private:
    double balance;
};

#endif //WALLET_H
