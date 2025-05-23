//
//  BundleDiscount.cpp
// Astrid Shao

#include "BundleDiscount.h"

BundleDiscount::BundleDiscount(int x, int y): buyX(x),getYFree(y){}

double BundleDiscount::applyDiscount(double price, int quantity) const{
    int free = (quantity / buyX) * getYFree;
    return price * (quantity - free);
}

