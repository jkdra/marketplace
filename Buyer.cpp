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

std::ostream& operator<<(std::ostream& os, const Buyer& buyer) {
	os << static_cast<const User&>(buyer)
		<< "\nWallet Balance: $" << buyer.getWallet().getBalance();
	return os;
}

Wallet Buyer::getWallet() const {
	return wallet;
}

void Buyer::addOrder(const shared_ptr<Product>& product) {
	if (wallet.getBalance() >= product->getPrice()) {
		myOrders.push_back(product);
		wallet.withdraw(product->getPrice());
	}
	else throw InsufficientFundsException();
}

void Buyer::display(std::ostream& os) const {
	os << "Name: " << getName()
		<< "\nEmail: " << getEmail()
		<< "\nType: " << getType()
		<< "\nWallet Balance: $" << getWallet().getBalance();
}
void Buyer::depositToWallet(double amount) {
	wallet.deposit(amount);
}
const vector<shared_ptr<Product>>& Buyer::getOrders() const {
	return myOrders;
}
