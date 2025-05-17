#include "Wallet.h"
#include <stdexcept>

Wallet::Wallet(double balance)
  : balance(balance)
{}

// Add funds
void Wallet::deposit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Cannot deposit negative amount");
    }
    balance += amount;
}

// Remove funds by throwing an insufficient balance
void Wallet::withdraw(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Cannot withdraw negative amount");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance -= amount;
}

// Check current balance
double Wallet::getBalance() const {
    return balance;
}
