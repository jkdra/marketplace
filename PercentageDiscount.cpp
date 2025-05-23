
//  PercentageDiscount.cpp
// Astird Shao

#include "PercentageDiscount.h"

PercentageDiscount::PercentageDiscount(double percent): percent(percent){}
double PercentageDiscount::applyDiscount(double price, int quantity) const {
    return price * quantity * (1 - percent/100);
}
