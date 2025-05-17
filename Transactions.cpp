#include "Transaction.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

// Helper to stamp current time
void Transaction::setTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_MSC_VER)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

//  store parties & product, record time
Transaction::Transaction(std::shared_ptr<User> buyer,
                         std::shared_ptr<User> seller,
                         std::shared_ptr<Product> product)
  : buyer(std::move(buyer))
  , seller(std::move(seller))
  , product(std::move(product))
{
    setTimestamp();
}

// Getters
std::shared_ptr<User> Transaction::getBuyer() const {
    return buyer;
}

std::shared_ptr<User> Transaction::getSeller() const {
    return seller;
}

std::shared_ptr<Product> Transaction::getProduct() const {
    return product;
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

// Stream‐insert (human‐readable transaction record)
std::ostream& operator<<(std::ostream& os, const Transaction& tx) {
    os  << "[" << tx.timestamp << "] "
        << "Buyer: "   << *tx.buyer   << ", "
        << "Seller: "  << *tx.seller  << ", "
        << "Product: " << *tx.product;
    return os;
}
