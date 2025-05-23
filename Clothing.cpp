#include "Clothing.h"
#include <iostream>

// Constructor
Clothing::Clothing(const std::string& name,
                   double price,
                   const std::string& size,
                   const std::string& material,
                   const std::string& brand)
  : Product(name, price)
  , size(size)
  , material(material)
  , brand(brand)
{}

// Type tag
std::string Clothing::getType() const {
    return "Clothing";
}

// Print all details
void Clothing::display(std::ostream& os) const {
    os  << "[Clothing] "
        << brand
        << " "
        << name
        << " (Size: "
        << size
        << ", Material: "
        << material
        << ") - $"
        << price;
  
    // if discount has been applied
    if (hasDiscount()) { 
            os << "\n  Discounted Price: $" << getPrice()
               << "\n  You Save: $" << (price - getPrice());
        }
        os << "\n";
}

// Accessors
const std::string& Clothing::getSize() const {
    return size;
}

const std::string& Clothing::getMaterial() const {
    return material;
}

const std::string& Clothing::getBrand() const {
    return brand;
}
