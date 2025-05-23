// Ammar Soliman

#ifndef SELLER_H
#define SELLER_H

#include "project.h"
#include "User.h"
#include "Product.h"

class Seller : public User {
friend class Cache;
public:
    Seller(const string& name, const string& email, const string& password, const string& company);
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    string getType() const;
	string getCompany() const;
    void addProduct(shared_ptr<Product> product);
    void removeProduct(const std::string& productName);
    const std::vector<std::shared_ptr<Product>>& getProducts() const;
    void display(std::ostream& os) const override;
    // Overloading << operator by Jawad Khadra
    friend std::ostream& operator<<(std::ostream& os, const Seller& seller);

private:
    string company;
	vector<shared_ptr<Product>> myProducts;
};

#endif
