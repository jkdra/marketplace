// Product.cpp
// Gio

#include "Product.h"
#include <iostream>

// static member init
std::size_t Product::nextId = 1;

// A helper to turn counter into a string ID
std::string Product::makeId() {
    return "P" + std::to_string(nextId++);
}

Product::Product(const std::string& name, double price)
  : id(makeId()), name(name), price(price)
{}

// ID accessor
const std::string& Product::getId() const {
    return id;
}

// Accessors
std::string Product::getName() const {
    return name;
}

double Product::getPrice(int quantity) const {
    if (discount){ // if discount has been applied - Astrid Shao
        return discount->applyDiscount(price, quantity);
    }
    return price;
}

// Discount - Setter
// Astrid Shao
void Product::setDiscount(std::unique_ptr<Discount> newDiscount){
    discount = std::move(newDiscount); // transfers ownership
}
bool Product::hasDiscount() const{
    return discount != nullptr;
}

// Equality( same name, price, type, and ID )
bool Product::operator==(const Product& other) const {
    return id == other.id
        && name == other.name
        && price == other.price
        && getType() == other.getType();
}

// Stream‐insert (delegate to polymorphic display() )
std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.display(os);
    return os;
}
