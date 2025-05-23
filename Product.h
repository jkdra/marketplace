// Product.h
// Gio

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Discount.h"
#include <iostream>
#include <string>

class Product {
public:
    Product(const std::string& name, double price);
    virtual ~Product() = default;

    // ID access
    const std::string& getId() const;

    virtual std::string getType() const = 0;
    virtual void display(std::ostream& os) const = 0;

    std::string getName() const;
    double getPrice(int quantity = 1) const; // apply to discounts
    
    // Discount setter
    // Astrid Shao
    void setDiscount(std::unique_ptr<Discount> newDiscount);
    bool hasDiscount() const; // for displaying discount info

    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    bool operator==(const Product& other) const;

protected:
    // for subclasses to use if they want to include the ID in display()
    std::string id;
    std::string name;
    double price;
    std::unique_ptr<Discount> discount;

private:
    static std::size_t nextId;
    static std::string makeId();
};

#endif //PRODUCT_H
