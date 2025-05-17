#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <string>
#include <memory>
#include "User.h"
#include "Product.h"

class Transaction {
public:
    Transaction(std::shared_ptr<User> buyer,
                std::shared_ptr<User> seller,
                std::shared_ptr<Product> product);

    std::shared_ptr<User> getBuyer() const;
    std::shared_ptr<User> getSeller() const;
    std::shared_ptr<Product> getProduct() const;
    std::string getTimestamp() const;

    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

private:
    std::shared_ptr<User> buyer;
    std::shared_ptr<User> seller;
    std::shared_ptr<Product> product;
    std::string timestamp;

    void setTimestamp();
};
#endif //TRANSACTIONS_H
