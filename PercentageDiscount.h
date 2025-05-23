
//  PercentageDiscount.h
// Astrid Shao

#ifndef PERCENTAGE_DISCOUNT_H
#define PERCENTAGE_DISCOUNT_H

#include "Discount.h"

class PercentageDiscount : public Discount {
    double percent;
public:
    PercentageDiscount(double percent);
    double applyDiscount(double price, int quantity) const override;
};
#endif
