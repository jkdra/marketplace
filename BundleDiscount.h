//
//  BundleDiscount.h

#ifndef BUNDLE_DISCOUNT_H
#define BUNDLE_DISCOUNT_H

#include "Discount.h"

class BundleDiscount : public Discount {
    int buyX;
    int getYFree;
public:
    BundleDiscount(int x, int y);
    double applyDiscount(double price, int quantity) const override;
};
#endif
