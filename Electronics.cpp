#include "Electronics.h"
#include <iostream>

using namespace std;

// Constructor
Electronics::Electronics(const string& name,
                         double price,
                         const string& brand,
                         const string& model,
                         int warrantyMonths)
  : Product(name, price)
  , brand(brand)
  , model(model)
  , warrantyMonths(warrantyMonths)
{}

// Type tag
string Electronics::getType() const {
    return "Electronics";
}

// Print all details
void Electronics::display(ostream& os) const {
    os  << "[Electronics] "
        << brand
        << " "
        << name
        << " (Model: "
        << model
        << ", "
        << warrantyMonths
        << "-month warranty) - $"
        << price;

     if (hasDiscount()) { // if discount has been applied
            os << "\n  Discounted Price: $" << getPrice()
               << "\n  You Save: $" << (price - getPrice());
        }
        os << "\n";
}

// Overloading << operator by Jawad Khadra
ostream& operator<<(ostream& os, const Electronics& electronics) {
    electronics.display(os);
    return os;
}

// Accessors
const string& Electronics::getBrand() const {
    return brand;
}

const string& Electronics::getModel() const {
    return model;
}

int Electronics::getWarrantyMonths() const {
    return warrantyMonths;
}
