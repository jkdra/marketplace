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
	void addProduct(shared_ptr<Product> product);
	void removeProduct(const std::string& productName);
	const std::vector<std::shared_ptr<Product>>& getProducts() const;
	void display(std::ostream& os) const override;

private:
	string company;
};

#endif
