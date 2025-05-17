#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>

class Product {
public:
    Product(const std::string& name, double price);
    virtual ~Product() = default;

    virtual std::string getType() const = 0;
    virtual void display(std::ostream& os) const = 0;

    std::string getName() const;
    double getPrice() const;

    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    bool operator==(const Product& other) const;

protected:
    std::string name;
    double price;
};
#endif //PRODUCT_H
