
//  Discount.h
// Astrid Shao

#ifndef DISCOUNT_H
#define DISCOUNT_H

//#include "Project.h"

class Discount {
public:
    virtual ~Discount() = default;  // This provides both declaration and definition
    virtual double applyDiscount(double price, int quantity) const = 0;
};

#endif
