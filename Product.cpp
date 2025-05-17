#include "Product.h"
#include <iostream>

Product::Product(const std::string& name, double price)
  : name(name), price(price)
{}

// Accessors
std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

// Equality( same name, price and runtime type)
bool Product::operator==(const Product& other) const {
    return name == other.name
        && price == other.price
        && getType() == other.getType();
}

// Stream‐insert (delegate to polymorphic display() )
std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.display(os);
    return os;
}
