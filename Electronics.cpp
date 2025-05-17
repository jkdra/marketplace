#include "Electronics.h"
#include <iostream>

// Constructor
Electronics::Electronics(const std::string& name,
                         double price,
                         const std::string& brand,
                         const std::string& model,
                         int warrantyMonths)
  : Product(name, price)
  , brand(brand)
  , model(model)
  , warrantyMonths(warrantyMonths)
{}

// Type tag
std::string Electronics::getType() const {
    return "Electronics";
}

// Print all details
void Electronics::display(std::ostream& os) const {
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
}

// Accessors
const std::string& Electronics::getBrand() const {
    return brand;
}

const std::string& Electronics::getModel() const {
    return model;
}

int Electronics::getWarrantyMonths() const {
    return warrantyMonths;
}
