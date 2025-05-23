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

std::ostream& operator<<(std::ostream& os, const Seller& seller) {
	os << static_cast<const User&>(seller)
		<< "\nCompany: " << seller.company;
	return os;
}

Wallet& Buyer::getWallet() const {
	return myWallet;
}
void Buyer::addOrder(shared_ptr<Product> product) {
	if (wallet.getBalance() >= product->getPrice()) {
		myOrders.push_back(product);
		wallet.withdraw(product->getPrice());
	}
	else {
		cout << "Insufficient funds \n";
	}
}
void Buyer::display(std::ostream& os) const {
	os << "Name: " << getName()
		<< "\nEmail: " << getEmail()
		<< "\nType: " << getType()
		<< "\nWallet Balance: $" << myWallet.getBalance();
}
