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
string Seller::getCompany() const {
	return company;
}

void Seller::addProduct(std::shared_ptr<Product> product) {
    myProducts.push_back(product);
}

void Seller::removeProduct(const std::string& productName) {
    myProducts.erase(
        std::remove_if(myProducts.begin(), myProducts.end(), [&](const std::shared_ptr<Product>& p)
    {
        return p->getName() == productName;
    }),
        myProducts.end()
    );
}

const std::vector<std::shared_ptr<Product>>& Seller::getProducts() const {
    return myProducts;
}
void Seller::display(std::ostream& os) const {
	os << "Name: " << getName()
		<< "\nEmail: " << getEmail()
		<< "\nType: " << getType()
		<< "\nCompany: " << company;
}

std::ostream& operator<<(std::ostream& os, const Seller& seller) {
    seller.display(os);
    return os;
}

